// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "BossCharacter.generated.h"

/**
 * 
 */
class AActor;
class UHealthBarComponent;
class ULockPointComponent;
class UMotionWarpingComponent;
class UNiagaraComponent;
class ABaseNiagara;
class UAnimMontage;
UCLASS()
class C_ACTION_API ABossCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABossCharacter();

	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
	virtual void HandleDamage(float DamageAmount) override;
	virtual void AttackEnd()override;
	virtual void StunStart();
	virtual void StunEnd();

	UPROPERTY(EditAnywhere)
	EBossState BossState = EBossState::EBS_NoState;

	//Attack
	UFUNCTION(BlueprintCallable)
		void MeleeAttack();

	UFUNCTION(BlueprintCallable)
		void BulletAttack();

	UFUNCTION(BlueprintCallable)
		void SpawnBullet(FVector SpellLocation, FVector Target, FRotator MagicRotation);

	UFUNCTION(BlueprintCallable)
		void AroundBulletAttack();

	void SetLocationAndRotation();

	UFUNCTION(BlueprintCallable)
		void SpawnAround(FVector SpellLocation, FVector Target, FRotator MagicRotation);

	UFUNCTION(BlueprintCallable)
		void MagicAttack();

	UFUNCTION()
	void SpawnMagic(FVector Target);

	UFUNCTION(BlueprintCallable)
		void MoveStart();

	void ResetWave();

	UFUNCTION(BlueprintCallable)
	void MoveEnd();

	UFUNCTION(BlueprintCallable)
	void StartBulletTimer();
	UFUNCTION(BlueprintCallable)
	void ClearBulletTimer();
	FTimerHandle BulletTimer;

	UFUNCTION(BlueprintCallable)
	void StartAroundTimer();
	UFUNCTION(BlueprintCallable)
	void ClearAroundTimer();
	FTimerHandle AroundTimer;

	FTimerHandle AreaTimer;

	UFUNCTION(BlueprintCallable)
		void StartAreaTimer();
	UFUNCTION(BlueprintCallable)
		void ClearAreaTimer();

	void ShowWhitePoint();
	void HideWhitePoint();

	void HideHealthBar();
	void ShowHealthBar();

	UFUNCTION(BlueprintCallable)
	float GetHp();

	UPROPERTY(Editanywhere)
		float AttackMin = 0.4f;
	UPROPERTY(Editanywhere)
		float AttackMax = 0.7f;

	UPROPERTY(Editanywhere)
		float AroundMin = 1.f;
	UPROPERTY(Editanywhere)
		float AroundMax = 1.5f;

	UPROPERTY(BlueprintReadWrite)
		FVector BP_SpellLocation;
	UPROPERTY(BlueprintReadWrite)
		FVector BP_TargetLocation;
	UPROPERTY(BlueprintReadWrite)
		FRotator BP_MagicRotation;
private:
	UPROPERTY(VisibleAnywhere)
		UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
		ULockPointComponent* LockPointWidget;

	UPROPERTY(VisibleAnywhere)
		UNiagaraComponent* MoveNiagara;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
		AActor* CharacterTarget;

	UPROPERTY(Editanywhere)
		float BaseSpeed=500.f;

	UPROPERTY(Editanywhere)
		float MoveSpeed = 5000.f;

	/*Bullet*/
	UPROPERTY(Editanywhere, Category = "Bullet")
		TSubclassOf<ABaseNiagara> Bullet;

	UPROPERTY(Editanywhere, Category = "Bullet")
		int32 BulletWave = 5;
		int32 CurrentBulletWave = 0;

	UPROPERTY(Editanywhere, Category = "Bullet")
		int32 BulletCount = 8;

	UPROPERTY(Editanywhere, Category = "Bullet")
		float BulletRotation = 5.f;

	UPROPERTY(Editanywhere, Category = "Bullet")
		float BulletDamage = 5.f;

	UPROPERTY(Editanywhere, Category = "Bullet")
		int32 AroundWave = 3;
		int32 CurrentAroundWave = 0;

	UPROPERTY(Editanywhere, Category = "Bullet")
		int32 AroundCount = 18;

	UPROPERTY(Editanywhere, Category = "Bullet")
		float AroundRotation = 10.f;

	UPROPERTY(Editanywhere, Category = "Bullet")
		int32 AroundDamage = 8;

	UPROPERTY(Editanywhere, Category = "Bullet")
		int32 AreaDamage = 25;

	UPROPERTY(Editanywhere, Category = "Bullet")
		int32 AreaTime = 3;

	/*Melee*/
	UPROPERTY(Editanywhere, Category = "Melee")
		int32 MeleeDamage = 15;

	UPROPERTY(Editanywhere, Category = "Melee")
	int32 MeleeWave = 3;

	UPROPERTY(Editanywhere, Category = "Melee")
		float MeleeRotation = 10.f;

	UPROPERTY(Editanywhere, category = "Niagara")
		TSubclassOf<ABaseNiagara> Area;

	UPROPERTY(Editanywhere, category = "Niagara")
		TSubclassOf<ABaseNiagara> Around;

	UPROPERTY(Editanywhere, category = "Niagara")
		TSubclassOf<ABaseNiagara> Melee;

	UPROPERTY(EditAnyWhere)
		TSubclassOf<class AWeapon> WeaponClass;

	/*Montage*/
	UPROPERTY(EditAnywhere,category="Montage")
		UAnimMontage* BulletMontage;

	UPROPERTY(EditAnywhere, category = "Montage")
		UAnimMontage* AroundMontage;

	void SpawnDefaultWeapon();
protected:
	virtual void BeginPlay()override;
	void InitializeBoss();

	bool IsDead();
	UMotionWarpingComponent* MotionWarping;

	virtual void Die_Implementation() override;
};
