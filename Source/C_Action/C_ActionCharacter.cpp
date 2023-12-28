// Copyright Epic Games, Inc. All Rights Reserved.

#include "C_ActionCharacter.h"
#include "Enemy/Enemy.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GroomComponent.h"
#include "Components/AttributeComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/WidgetComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "HUD/SlashHUD.h"
#include "HUD/SlashOverlay.h"
#include "Items/Soul.h"
#include "Items/Treasure.h"
#include "Items/Weapons/Weapon.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"


AC_ActionCharacter::AC_ActionCharacter()
{

	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("InventoryWidgetComponent");

	WidgetComponent->SetupAttachment(CameraBoom);
	WidgetComponent->SetVisibility(false);

	AssassinTarget = nullptr;
}

float AC_ActionCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	SetHealthHUD();
	return DamageAmount;
}

void AC_ActionCharacter::Jump()
{
	if (ActionState == EActionState::EAS_Unoccupied)
	{
		Super::Jump();
	}
}

void AC_ActionCharacter::Die_Implementation()
{
	Super::Die_Implementation();
	ActionState = EActionState::EAS_Dead;
}

void AC_ActionCharacter::SetOverLappingItem(AItem* Item)
{
	OverLappingItem=Item;
}

void AC_ActionCharacter::AddSouls(ASoul* Soul)
{
	if (Attributes&&SlashOverlay)
	{
		Attributes->AddSouls(Soul->GetSouls());
		SlashOverlay->SetSouls(Attributes->GetSouls());
	}
}

void AC_ActionCharacter::AddGold(ATreasure* Treasure)
{
	if (Attributes&&SlashOverlay)
	{
		Attributes->AddGold(Treasure->GetGold());
		SlashOverlay->SetGold(Attributes->GetGold());
	}
}

void AC_ActionCharacter::SetHealthHUD()
{
	if (SlashOverlay && Attributes)
	{
		SlashOverlay->SetHealthBarpercent(Attributes->GetHealthPercent());
	}
}

void AC_ActionCharacter::PickUpItem(AItem* Item)
{
	if (InventoryComponent && WidgetComponent)
	{
		InventoryComponent->PickUp(Item);
	}
}

void AC_ActionCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	Tags.Add(FName("EngageableTarget"));

	InventoryComponent->Init();
	
	InitializeSlashOverlay();


}

void AC_ActionCharacter::Tick(float DeltaTime)
{
	if (Attributes && SlashOverlay)
	{
		Attributes->RegenStamina(DeltaTime);
		SlashOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
	}

	FVector StartLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector EndLocation = StartLocation + (ForwardVector * AssassinDistance);
	FHitResult HitResult;
	ETraceTypeQuery TraceChannel = UEngineTypes::ConvertToTraceType(ECC_Visibility);;
	bool bHit = UKismetSystemLibrary::LineTraceSingle(
		this,
		StartLocation,
		EndLocation,
		TraceChannel,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None,
		HitResult,
		true);
	IsCameraForwardHaveSomething = bHit;
	AssassinHitResult = HitResult;

	if (Controller != nullptr && IsCameraLock && CameraTarget != nullptr)
	{
		FVector TargetLocation = CameraTarget->GetActorLocation();

		FRotator ActorControllerRotator = Controller->GetControlRotation();

		FVector Distance = GetActorLocation() - (CameraTarget->GetActorLocation());
		FRotator TargetRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), FVector(TargetLocation.X, TargetLocation.Y, TargetLocation.Z - 200.f));
		FRotator RinterpRotator = UKismetMathLibrary::RInterpTo(ActorControllerRotator, TargetRotator, GetWorld()->GetDeltaSeconds(), 5.f);

		Controller->SetControlRotation(FRotator(RinterpRotator.Pitch, RinterpRotator.Yaw, ActorControllerRotator.Roll));

		if (Distance.Size() >= CameraLockDistance)
		{
			IsCameraLock = false;
		}
	}
	if (CameraTarget)
	{
		if (CameraTarget->GetHp() <= 0) { CameraTarget = nullptr; }
	}
}


void AC_ActionCharacter::InitializeSlashOverlay()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		ASlashHUD* SlashHUD = Cast<ASlashHUD>(PlayerController->GetHUD());
		if (SlashHUD)
		{
			SlashOverlay = SlashHUD->GetSlashOverlay();
			if (SlashOverlay)
			{
				SlashOverlay->SetHealthBarpercent(Attributes->GetHealthPercent());
				SlashOverlay->SetStaminaBarPercent(1.f);
				SlashOverlay->SetGold(0);
				SlashOverlay->SetSouls(0);
			}
		}
	}
}

void AC_ActionCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AC_ActionCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AC_ActionCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AC_ActionCharacter::Look);
		
		EnhancedInputComponent->BindAction(Equip,ETriggerEvent::Triggered,this,&AC_ActionCharacter::EquipKey);

		EnhancedInputComponent->BindAction(Attack, ETriggerEvent::Triggered, this, &AC_ActionCharacter::Attacked);

		EnhancedInputComponent->BindAction(Dodge,ETriggerEvent::Triggered,this,&AC_ActionCharacter::Dodged);

		EnhancedInputComponent->BindAction(AssassinKey, ETriggerEvent::Triggered, this, &AC_ActionCharacter::Assassin);

		EnhancedInputComponent->BindAction(InventoryKey, ETriggerEvent::Triggered, InventoryComponent, &UInventoryComponent::ToggleInventoryWidget);

		EnhancedInputComponent->BindAction(CameraLockKey, ETriggerEvent::Triggered, this, &AC_ActionCharacter::CameraLock);

	}

}

void AC_ActionCharacter::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	Super::GetHit_Implementation(ImpactPoint, Hitter);
	SetWeaponCollision(ECollisionEnabled::NoCollision);
	if (Attributes && Attributes->GetHealthPercent()>0.f)
	{
ActionState = EActionState::EAS_HitReaction;
	}
		
}

void AC_ActionCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	if (ActionState != EActionState::EAS_Unoccupied) { 
		return;
	}
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AC_ActionCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr&&!IsCameraLock)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}

}

void AC_ActionCharacter::EquipKey(const FInputActionValue& Value)
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverLappingItem);
	if (OverlappingWeapon)
	{
		if (EquippedWeapon)
		{
			EquippedWeapon->Destroy();
		}
		EquipWeapon(OverlappingWeapon);
	}
	else
	{

		if (CanDisarm())
		{
			Disarm();
		}
		else if (Canarm()) 
		{
			Arm();
		}
	}
}

void AC_ActionCharacter::Attacked(const FInputActionValue& value)
{
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

void AC_ActionCharacter::Assassin(const FInputActionValue& value)
{

	if (IsCameraForwardHaveSomething && AssassinHitResult.GetActor()) {

		AActor* HitActor = AssassinHitResult.GetActor();
		if (HitActor && HitActor->ActorHasTag("Enemy"))
		{
			AEnemy* HitEnemy = Cast<AEnemy>(HitActor);
			IAssassinInterface* EnemyInterface = Cast<IAssassinInterface>(HitActor);
			if (EnemyInterface && HitEnemy->EnemyType == EEnemyType::EET_Human && HitEnemy->EnemyState == EEenemyState::EES_Patrolling && ActionState == EActionState::EAS_Unoccupied && AssassinBack(*HitActor))
			{
				EnemyInterface->Execute_Assassinated(AssassinHitResult.GetActor(), GetActorLocation(), GetOwner());
				ActionState = EActionState::EAS_Assassination;
				AssassinTarget = HitEnemy;
				AssassinLocation = HitEnemy->GetTranslationWarpTargetAssassin();
				AssassinRotation = HitEnemy->GetRotationWarpTargetAssassin();

				PlayMontageSection(AssassinatedMontage, FName("Assassin"));
				SetCollisionIgnore();
			}
		}
	}

}

void AC_ActionCharacter::BackPack(const FInputActionValue& value)
{

}

void AC_ActionCharacter::Dodged(const FInputActionValue& value)
{
	
	if (IsOccupied()||!HasEnoughStamina()) { return; }

	PlayMontageSection(DodgeMontage, FName("Dodge"));
	ActionState = EActionState::EAS_Dodge;
	SetCollisionIgnore();
	if (Attributes&&SlashOverlay)
	{
		Attributes->UseStamina(Attributes->GetDodgeCost());
		SlashOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
	}

}

void AC_ActionCharacter::CameraLock(const FInputActionValue& Value)
{

	
	FVector ActorLocation = GetActorLocation();
	FRotator ActorRotaion = GetActorRotation();
	FVector ActorForwardVector = ActorRotaion.Vector();
	FVector StartCameraLockDistance = ActorLocation + ActorForwardVector*CameraLockDistance;


	FRotator CameraRotation = FollowCamera->GetComponentRotation();
	FVector CameraForwardVector = CameraRotation.Vector();

	FVector CameraLocationEnd = ActorLocation +CameraForwardVector* CameraLockDistance;

	FHitResult SphereHitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	bool Sphere = UKismetSystemLibrary::SphereTraceSingle(this, StartCameraLockDistance, CameraLocationEnd,CameraLockDistance, CameraTracetype01, false,
		ActorsToIgnore,EDrawDebugTrace::None, SphereHitResult,false,FLinearColor::Red );

	CameraHitResult = SphereHitResult;
	IsCameraLockBox = Sphere;
	if (IsCameraLockBox&& CameraHitResult.GetActor()->ActorHasTag("Enemy"))
	{
		AActor* HitActor = CameraHitResult.GetActor();
		CameraTarget = Cast<AEnemy>(HitActor);
		IsCameraLock = !IsCameraLock;
	}
}

void AC_ActionCharacter::SetCollisionIgnore()
{	
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	if (EquippedWeapon)
	{
		UStaticMeshComponent* WeaponMesh = EquippedWeapon->FindComponentByClass<UStaticMeshComponent>();
		if (WeaponMesh)
		{
			WeaponMesh->SetVisibility(false);
		}
	}
}

bool AC_ActionCharacter::HasEnoughStamina()
{
	return Attributes && Attributes->GetStaminaPercent() &&Attributes->GetStamina()>Attributes->GetDodgeCost();
}

bool AC_ActionCharacter::IsOccupied()
{
	return ActionState != EActionState::EAS_Unoccupied;
}

void AC_ActionCharacter::EquipWeapon(AWeapon* Weapon)
{
	Weapon->Equip(GetMesh(), FName("RightHandSocket"), this, this);
	CharacterState = ECharacterState::ECS_EquippedOneHandWeapon;
	OverLappingItem = nullptr;
	EquippedWeapon = Weapon;
}


void AC_ActionCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

bool AC_ActionCharacter::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied && 
		CharacterState != ECharacterState::ECS_UnEquip;
}

void AC_ActionCharacter::PlayEquipMontage(const FName& SelectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance&&EquipMontage) {
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SelectionName, EquipMontage);
	}
}


bool AC_ActionCharacter::CanDisarm()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_UnEquip;
}

void AC_ActionCharacter::Disarm()
{
	PlayEquipMontage(FName("UnEquip"));
	ActionState = EActionState::EAS_EquippingWeapon;
	CharacterState = ECharacterState::ECS_UnEquip;
}

bool AC_ActionCharacter::Canarm()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState == ECharacterState::ECS_UnEquip&&
		EquippedWeapon;
}

void AC_ActionCharacter::Arm()
{
	PlayEquipMontage(FName("Equip"));
	ActionState = EActionState::EAS_EquippingWeapon;
	CharacterState = ECharacterState::ECS_EquippedOneHandWeapon;
}

void AC_ActionCharacter::AttachWeaponToBack()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("SpineSocket"));
	}
}

void AC_ActionCharacter::AttachWeaponToHand()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("RightHandSocket"));
	}
}

bool AC_ActionCharacter::AssassinBack(AActor& Actor)
{

	const FRotator SlashRotation = GetActorRotation();
	const FRotator EnemyRotation = Actor.GetActorRotation();

	const float ZDiff = FMath::Abs(SlashRotation.Yaw - EnemyRotation.Yaw);
	if (ZDiff <= 45.f && ZDiff >= 0.f)
	{
		return true;
	}
	return false ;
}

void AC_ActionCharacter::FinishEquipping()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void AC_ActionCharacter::HitReactEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void AC_ActionCharacter::DodgeEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
	ResetMeshCollision();
	if (EquippedWeapon) 
	{
		UStaticMeshComponent* WeaponMesh = EquippedWeapon->FindComponentByClass<UStaticMeshComponent>();
	if (WeaponMesh) 
		{
		WeaponMesh->SetVisibility(true);
		}
	}
	
}

void AC_ActionCharacter::ResetMeshCollision()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

void AC_ActionCharacter::AssassinEnd()
{
	AssassinTarget = NULL;
	ActionState = EActionState::EAS_Unoccupied;
	ResetMeshCollision();
}





