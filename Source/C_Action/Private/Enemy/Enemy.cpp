// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Items/Weapons/Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HUD/HealthBarComponent.h"
#include "AIController.h"
#include "Perception/PawnSensingComponent.h"
#include "Items/Soul.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Block);
	GetMesh()->SetGenerateOverlapEvents(true);
	
	

	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SightRadius = 4000.f;
	PawnSensing->SetPeripheralVisionAngle(45.f);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (PawnSensing)
		{
			//Delegate
			PawnSensing->OnSeePawn.AddDynamic(this, &AEnemy::PawnSeen);
		}
	InitializeEnemy();
	Tags.Add(FName("Enemy"));
}

void AEnemy::InitializeEnemy()
{	EnemyController = Cast<AAIController>(GetController());
	MoveToTarget(PatrolTarget);
	HideHealthBar();
	
	SpawnDefaultWeapon();
}

void AEnemy::SpawnDefaultWeapon()
{
	UWorld* World = GetWorld();
	if (World && WeaponClass)
	{
		AWeapon* DefaultWeapon = World->SpawnActor<AWeapon>(WeaponClass);
		DefaultWeapon->Equip(GetMesh(), FName("WeaponSocket"), this, this);
		EquippedWeapon = DefaultWeapon;
	}
}

void AEnemy::HideHealthBar()
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}
}

void AEnemy::ShowHealthBar()
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(true);
	}
}

void AEnemy::StarPatrolling()
{
	EnemyState = EEenemyState::EES_Patrolling;
	GetCharacterMovement()->MaxWalkSpeed = PatrollingSpeed;
	MoveToTarget(PatrolTarget);
}

bool AEnemy::IsOutsideCombatRadius()
{
	return !IntargetRange(CombatTarget, CombatRadius);
}

void AEnemy::ChaseTarget()
{
	EnemyState = EEenemyState::EES_Chasing;
	GetCharacterMovement()->MaxWalkSpeed = ChasingSpeed;
	MoveToTarget(CombatTarget);
}

void AEnemy::LoseInterest()
{
	CombatTarget = nullptr;
	HideHealthBar();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsDead()){return;}

	if (EnemyState > EEenemyState::EES_Patrolling)
	{
		CheckCombatTarget();
	}
	else 
	{
		CheckPatrolTarget();
	}
}

void AEnemy::CheckPatrolTarget()
{
	if (IntargetRange(PatrolTarget, PatrolRadius))
	{
		PatrolTarget = ChoosePartolTarget();
		const float WaitTime = FMath::RandRange(PatrolWaitMin, PatrolWaitMax);
		GetWorldTimerManager().SetTimer(PatrolTimer, this, &AEnemy::PatrolTimerFinished, WaitTime);
	}
}

bool AEnemy::IsOutsideAttackRadius()
{
	return !IntargetRange(CombatTarget, AttackRadius);
}

void AEnemy::CheckCombatTarget()
{
	if (IsOutsideCombatRadius())
	{
		ClearAttackTimer();
		LoseInterest();
		
		if (!IsEngage())
		{
		StarPatrolling();
		}

	}
	else if (IsOutsideAttackRadius() && !IsChaseing())
	{
		ClearAttackTimer();
		if (!IsEngage())
		{
			ChaseTarget();
		}
	}
	else if (CanAttack())
	{	
		StarAttackTimer();
	}
}
void AEnemy::ClearPatrolTime()
{
	GetWorldTimerManager().ClearTimer(PatrolTimer);
}
void AEnemy::StarAttackTimer()
{
	EnemyState = EEenemyState::EES_Attacking;
	const float AttackTime = FMath::RandRange(AttackMin, AttackMax);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemy::Attack, AttackTime);
}

bool AEnemy::IsChaseing()
{
	return EnemyState == EEenemyState::EES_Chasing;
}

bool AEnemy::IsAttacking()
{
	return EnemyState == EEenemyState::EES_Attacking;
}
bool AEnemy::IsInsideAttackRadius()
{
	return IntargetRange(CombatTarget, AttackRadius);
}



void AEnemy::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	Super::GetHit_Implementation(ImpactPoint,Hitter);
	if (!IsDead()){ShowHealthBar();}
	ClearPatrolTime();
	ClearAttackTimer();
	SetWeaponCollision(ECollisionEnabled::NoCollision);
	StopAttackMontage();

	if (IsInsideAttackRadius() && !IsDead())
	{
		StarAttackTimer();
	}
}


float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	CombatTarget = EventInstigator->GetPawn();
	if (IsInsideAttackRadius())
	{
		EnemyState = EEenemyState::EES_Attacking;
	}
	else if (IsOutsideAttackRadius())
	{
		ChaseTarget();
	}
	return DamageAmount;
}

void AEnemy::ClearAttackTimer()
{
	GetWorldTimerManager().ClearTimer(AttackTimer);
}


void AEnemy::Die_Implementation()
{
	Super::Die_Implementation();

	EnemyState = EEenemyState::EES_Dead;
	
	ClearAttackTimer();
	HideHealthBar();
	DisableCapsule();
	SetLifeSpan(DeathLifeSpan);
	GetCharacterMovement()->bOrientRotationToMovement = false;
	SetWeaponCollision(ECollisionEnabled::NoCollision);
	SpawnSoul();
}
void AEnemy::SpawnSoul()
{
	UWorld* World = GetWorld();
	if (World && SoulClass)
	{
		const FVector SpawnLocation = GetActorLocation() + FVector(0.f, 0.f, 125.f);
		ASoul* SpawnedSoul =World->SpawnActor<ASoul>(SoulClass, SpawnLocation, GetActorRotation());
		if (SpawnedSoul) 
		{

			SpawnedSoul->SetSouls(Attributes->GetSouls());
			SpawnedSoul->SetOwner(this);
		}
		
		
	}
}
bool AEnemy::IsDead() 
{
	return EnemyState == EEenemyState::EES_Dead;
}

bool AEnemy::IsEngage()
{
	return EnemyState == EEenemyState::EES_Engaged;
}

bool AEnemy::IntargetRange(AActor* target, double Radius)
{
	if (target == nullptr){return false;}
	const double DistanceToTarget = (target->GetActorLocation() - GetActorLocation()).Size();
	return DistanceToTarget<=Radius;
}

void AEnemy::PatrolTimerFinished()
{
	MoveToTarget(PatrolTarget);
}

void AEnemy::MoveToTarget(AActor* Target)
{
	if (EnemyController == nullptr || Target == nullptr){return;}
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(Target);
		MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
		EnemyController->MoveTo(MoveRequest);
}

AActor* AEnemy::ChoosePartolTarget()
{
	TArray<AActor*> ValidTarget;
		for (AActor* Target : PatrolTargets)
		{
			if (Target != PatrolTarget)
			{
				ValidTarget.AddUnique(Target);
			}
		}
	const int32 NunPartolTarget = ValidTarget.Num();
		if (NunPartolTarget > 0)
		{
			const int32 TargetSelection = FMath::RandRange(0, NunPartolTarget - 1);
			return ValidTarget[TargetSelection];
				
		}
	return nullptr;
}


void AEnemy::AttackEnd()
{
	EnemyState = EEenemyState::EES_NoState;
	CheckCombatTarget();
}

void AEnemy::PawnSeen(APawn* SeenPawn)
{

	const bool bShouldChaseTarget =
		EnemyState != EEenemyState::EES_Dead &&
		EnemyState != EEenemyState::EES_Chasing &&
		EnemyState < EEenemyState::EES_Attacking &&
		SeenPawn->ActorHasTag("EngageableTarget");

	if (bShouldChaseTarget) {
		CombatTarget = SeenPawn;
		ClearPatrolTime();
		ChaseTarget();
	}
}

void AEnemy::Attack()
{	
	Super::Attack();
	if (CombatTarget == nullptr) { return; }
	EnemyState = EEenemyState::EES_Engaged;
	
	PlayAttackMontage();
}



bool AEnemy::CanAttack()
{
	bool CanAttack = IsInsideAttackRadius() && !IsAttacking() &&!IsEngage() && !IsDead();
	return CanAttack;
}

void AEnemy::Destroyed()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();
	}
}

void AEnemy::HandleDamage(float DamageAmount)
{
	Super::HandleDamage(DamageAmount);
	if (Attributes && HealthBarWidget)
	{
		HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
	}
}


