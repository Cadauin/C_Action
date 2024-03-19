// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"



class UHealthBarComponent;
class AAIController;
class UPawnSensingComponent;
class USkeletalMeshComponent;
class ULockPointComponent;
UCLASS()
class C_ACTION_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(EditAnywhere, Category = "Enemy")
		EEenemyState EnemyState = EEenemyState::EES_Patrolling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
		EEnemyType EnemyType;
	


	/*
	AssassinSkeletalMesh
	*/
	UPROPERTY(Editanywhere, category = "Assassin")
		USkeletalMeshComponent* AssassinSkeletalMesh;
	/*AssassinWarp*/
	UFUNCTION(BlueprintCallable)
		FVector GetTranslationWarpTargetAssassin();

	UFUNCTION(BlueprintCallable)
		FRotator GetRotationWarpTargetAssassin();

	void ShowWhitePoint();
	void HideWhitePoint();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void InitializeEnemy();
	void SpawnDefaultWeapon();
	class UMotionWarpingComponent* MotionWarping;

	 
	virtual void Die_Implementation() override;
	void SpawnSoul();
	bool IntargetRange(AActor* target,double Radius);

	UPROPERTY(Editanywhere, category = "Combat")
		double PatrolRadius = 200.f;


	FTimerHandle PatrolTimer;
	void PatrolTimerFinished();

	void MoveToTarget(AActor* Target);
	AActor* ChoosePartolTarget();

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);


	
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void HandleDamage(float DamageAmount) override;
	virtual void AttackEnd()override;

	
	UFUNCTION(BlueprintCallable)
		void Assassin_End();



private:
	/*
	Components
	*/
	UPROPERTY(VisibleAnywhere)
		UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnyWhere)
		UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnyWhere)
		TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere)
		 ULockPointComponent* LockPointWidget;

	

	UPROPERTY(Editanywhere, category = "Combat")
		double CombatRadius=1500.f;

	UPROPERTY(EditAnyWhere, Category = "Combat")
		double AttackRadius = 150.f;

	UPROPERTY(EditAnyWhere, Category = "Combat")
		double AcceptanceRadius = 150.f;
	
	UPROPERTY(EditAnyWhere, Category = "Combat")
		TSubclassOf<class ASoul> SoulClass;
	/*
	Navigation
	*/
	UPROPERTY(EditInstanceOnly,Category="AI Navigation")
		AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly,Category="AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY()
		AAIController* EnemyController;


	UPROPERTY(EditanyWhere, category = "AI Navigation")
		float PatrolWaitMax=10.f;
	UPROPERTY(EditanyWhere, category = "AI Navigation")
		float PatrolWaitMin = 5.f;

	/*
	AI Behavior
	*/
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StarPatrolling();
	void ChaseTarget();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	bool IsChaseing();
	bool IsAttacking();
	bool IsDead();
	bool IsEngage();
	bool IsAssassinated();
	void ClearPatrolTime();

	/*
	Combat
	*/
	void StarAttackTimer();
	void ClearAttackTimer();

	FTimerHandle AttackTimer;

	UPROPERTY(Editanywhere)
		float AttackMin = 0.5f;
	UPROPERTY(Editanywhere)
		float AttackMax = 1.f;


	UPROPERTY(Editanywhere)
		float PatrollingSpeed = 125.f;
	UPROPERTY(Editanywhere)
		float ChasingSpeed = 300.f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CheckPatrolTarget();

	void CheckCombatTarget();

	
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

	virtual void Assassinated_Implementation(const FVector& ImpactPoint, AActor* Hitter)override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

	virtual void Destroyed()override;

	float GetHp();
};
