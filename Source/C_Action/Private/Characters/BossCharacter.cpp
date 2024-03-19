// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BossCharacter.h"
#include "HUD/HealthBarComponent.h"
#include "HUD/LockPointComponent.h"
#include "NiagaraComponent.h"
#include "Niagaras/BaseNiagara.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"

ABossCharacter::ABossCharacter()
{
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Block);
	GetMesh()->SetGenerateOverlapEvents(true);

	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());

	LockPointWidget = CreateDefaultSubobject<ULockPointComponent>(TEXT("LockPoint"));
	LockPointWidget->SetupAttachment(GetRootComponent());
	LockPointWidget->SetWidgetSpace(EWidgetSpace::Screen);
	LockPointWidget->SetRelativeLocation(FVector(0.f, 2.f, 0.f));

	MoveNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MoveNiagara"));
	MoveNiagara->SetupAttachment(GetRootComponent());
	MoveNiagara->Deactivate();
	MoveNiagara->SetVisibility(false);
	
}



void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializeBoss();
	Tags.Add(FName("Boss"));
}

void ABossCharacter::InitializeBoss()
{
	HideHealthBar();
	HideWhitePoint();
	SpawnDefaultWeapon();
}

void ABossCharacter::HideHealthBar()
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}
}

void ABossCharacter::ShowWhitePoint()
{
	if (LockPointWidget)
	{
		LockPointWidget->SetVisibility(true);
	}
}

void ABossCharacter::HideWhitePoint()
{
	if (LockPointWidget)
	{
		LockPointWidget->SetVisibility(false);
	}
}

void ABossCharacter::ShowHealthBar()
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(true);
	}
}

bool ABossCharacter::IsDead()
{
	return BossState == EBossState::EBS_Dead;
}

void ABossCharacter::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	Super::GetHit_Implementation(ImpactPoint, Hitter);
	if (!IsDead()) 
	{
		ShowHealthBar(); 

	}
}

void ABossCharacter::Attack()
{
}

bool ABossCharacter::CanAttack()
{
	return false;
}

void ABossCharacter::AttackEnd()
{
}

void ABossCharacter::StunStart()
{
}

void ABossCharacter::StunEnd()
{
}

float ABossCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	CombatTarget = EventInstigator->GetPawn();
	return DamageAmount;
}

void ABossCharacter::HandleDamage(float DamageAmount)
{
	Super::HandleDamage(DamageAmount);
	if (Attributes && HealthBarWidget)
	{
		HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
	}
}

void ABossCharacter::SpawnDefaultWeapon()
{
	UWorld* World = GetWorld();
	if (World && WeaponClass)
	{
		AWeapon* DefaultWeapon = World->SpawnActor<AWeapon>(WeaponClass);
		DefaultWeapon->Equip(GetMesh(), FName("WeaponSocket"), this, this);
		EquippedWeapon = DefaultWeapon;
	}
}

void ABossCharacter::MeleeAttack()
{
	UWorld* World = GetWorld();
	SetLocationAndRotation();
	for (int i = 0; i < MeleeWave;++i)
	{
		if (World)
		{
			BP_MagicRotation.Yaw += (i % 2 == 0) ? (i * MeleeRotation) : ( - i * MeleeRotation);

			ABaseNiagara* MeleeNiagara = World->SpawnActor<ABaseNiagara>(Melee, BP_SpellLocation, BP_MagicRotation);
			if (MeleeNiagara)
			{
				MeleeNiagara->Init(MeleeDamage, this, UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
			}
		}
	}
}

void ABossCharacter::BulletAttack()
{
	SetLocationAndRotation();
		for (int m = 0; m < BulletCount; m++)
		{
			float rand=FMath::RandRange(0,5);
			BP_MagicRotation.Yaw += (m % 2 == 0) ? (m * BulletRotation+rand) : (-m * BulletRotation-rand);
			SpawnBullet(BP_SpellLocation, BP_TargetLocation, BP_MagicRotation);
		}
		CurrentBulletWave++;
		if (CurrentBulletWave >= BulletWave)
		{
			ClearBulletTimer();
		}
}

void ABossCharacter::SpawnBullet(FVector SpellLocation, FVector Target, FRotator MagicRotation)
{
	UWorld* World = GetWorld();
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (World&&Bullet)
	{
		if (AnimInstance && BulletMontage)
		{
			AnimInstance->Montage_Play(BulletMontage);
		}
		ABaseNiagara* SpawnedMagic = World->SpawnActor<ABaseNiagara>(Bullet, SpellLocation, MagicRotation);

		if (SpawnedMagic)
		{
			SpawnedMagic->Init(BulletDamage, this, UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
		}
	}
}

void ABossCharacter::AroundBulletAttack()
{
	SetLocationAndRotation();
	for (int i = 0; i < AroundCount; i++)
	{
		BP_MagicRotation.Yaw += (360 / AroundCount);
		SpawnAround(BP_SpellLocation, BP_TargetLocation, BP_MagicRotation);
	}
	CurrentAroundWave++;
	if (CurrentAroundWave >= AroundWave)
	{
		ClearAroundTimer();
	}
}

void ABossCharacter::SetLocationAndRotation()
{
	BP_SpellLocation = GetActorLocation();
	BP_TargetLocation = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation();
	BP_MagicRotation = FRotationMatrix::MakeFromX(BP_TargetLocation - BP_SpellLocation).Rotator();
}

void ABossCharacter::SpawnAround(FVector SpellLocation, FVector Target, FRotator MagicRotation)
{
	UWorld* World = GetWorld();
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (World)
	{
		if (AnimInstance && AroundMontage)
		{
			AnimInstance->Montage_Play(AroundMontage);
		}
		ABaseNiagara* SpawnedMagic = World->SpawnActor<ABaseNiagara>(Around, SpellLocation, MagicRotation);
		if (SpawnedMagic)
		{
			SpawnedMagic->Init(AroundDamage, this, UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
		}
	}
}

void ABossCharacter::MagicAttack()
{
	FVector Target=UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation();
	UWorld* World = GetWorld();
	FTimerDelegate TimerCallback;
	TimerCallback.BindUFunction(this, FName("SpawnMagic"), Target);
	GetWorldTimerManager().SetTimer(AreaTimer, TimerCallback, 2.0f, false);
}

void ABossCharacter::SpawnMagic(FVector Target)
{
	UWorld* World = GetWorld();
	if (World)
	{
		ABaseNiagara* SpawnedMagic = World->SpawnActor<ABaseNiagara>(Area, Target, UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorRotation());
		SpawnedMagic->SetSpeed(FVector(0.f, 0.f, 0.f));
		if (SpawnedMagic)
		{
			SpawnedMagic->Init(AreaDamage, this, UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
		}
	}
	ClearAreaTimer();
}

void ABossCharacter::MoveStart()
{
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	ClearAroundTimer();
	ClearBulletTimer();
	ResetWave();
	GetMesh()->SetVisibility(false);
	MoveNiagara->SetVisibility(true);
	MoveNiagara->ActivateSystem();
}

void ABossCharacter::ResetWave()
{
	CurrentAroundWave = 0;
	CurrentBulletWave = 0;
}

void ABossCharacter::MoveEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
	GetMesh()->SetVisibility(true);
	MoveNiagara->Deactivate();
	MoveNiagara->SetVisibility(false);
}

void ABossCharacter::StartBulletTimer()
{
	const float AttackTime = FMath::RandRange(AttackMin, AttackMax);
	GetWorldTimerManager().SetTimer(BulletTimer, this, &ABossCharacter::BulletAttack, AttackTime, true);
}

void ABossCharacter::ClearBulletTimer()
{
	GetWorldTimerManager().ClearTimer(BulletTimer);
}

void ABossCharacter::StartAroundTimer()
{
	const float AttackTime = FMath::RandRange(AroundMin, AroundMax);
	GetWorldTimerManager().SetTimer(AroundTimer, this, &ABossCharacter::AroundBulletAttack, AttackTime,true);
}

void ABossCharacter::ClearAroundTimer()
{
	GetWorldTimerManager().ClearTimer(AroundTimer);
}

void ABossCharacter::StartAreaTimer()
{
	GetWorldTimerManager().SetTimer(AreaTimer, this, &ABossCharacter::MagicAttack, AreaTime, true);
}

void ABossCharacter::ClearAreaTimer()
{
	GetWorldTimerManager().ClearTimer(AreaTimer);
}

float ABossCharacter::GetHp()
{
	return Attributes->GetHealth();
}

void ABossCharacter::Die_Implementation()
{
	Super::Die_Implementation();
	BossState = EBossState::EBS_Dead;
	HideHealthBar();
	ClearAroundTimer();
	ClearBulletTimer();
	DisableCapsule();
	SetLifeSpan(5.f);
	GetCharacterMovement()->bOrientRotationToMovement = false;
	HideWhitePoint();
}
