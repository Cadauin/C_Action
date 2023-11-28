// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterfaces.h"
#include "Interfaces/AssassinInterface.h"
#include "Components/AttributeComponent.h"
#include "Characters/CharacterTypes.h"
#include "BaseCharacter.generated.h"

class AWeapon;
class UAnimMontage;
class UAttributeComponent;
UCLASS()

class C_ACTION_API ABaseCharacter : public ACharacter,public IHitInterfaces , public IAssassinInterface
{
	GENERATED_BODY()

public:
	
	ABaseCharacter();

	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void SetWeaponCollision(ECollisionEnabled::Type CollisionEnable);
	
	FORCEINLINE TEnumAsByte<EDeathPose> GetDeadPose() const { return DeathPose; }

protected:
	virtual void BeginPlay() override;
	virtual void Attack();
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)override;
	virtual void Assassinated_Implementation(const FVector& ImpactPoint, AActor* Hitter)override;
	virtual bool CanAttack();
	bool IsAlive();



	UFUNCTION(BlueprintCallable)
	virtual	void AttackEnd();

	UFUNCTION(BlueprintNativeEvent)
	void Die();

	void DisableCollision();
	/*
	Components
	*/

	UPROPERTY(VisibleAnywhere)
		UAttributeComponent* Attributes;

	UPROPERTY(Editanywhere, category = "Combat")
		USoundBase* HitSound;

	UPROPERTY(Editanywhere, category = "Combat")
		UParticleSystem* HitParticles;

	UPROPERTY(BlueprintReadOnly)
		TEnumAsByte<EDeathPose> DeathPose;
/*
*Play Montage Funtions
*/
	
	
	
	virtual void PlayHitReactMontage(const FName& SelectionName);
	virtual void DirectionalHitReact(const FVector& ImpactPoint);
	virtual void HandleDamage(float DamageAmount);
	void PlayHitSound(const FVector& ImpactPoint);
	void SpawnParticles(const FVector& ImpactPoint);
	void PlayMontageSection(UAnimMontage* Montage,const FName& SelectionName);
	int32 PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SelectionNames);
	virtual	int32 PlayAttackMontage();
	virtual	int32 PlayDeathMontage();
	void StopAttackMontage();
	void DisableCapsule();
	
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
		AActor* CombatTarget;

	UPROPERTY(Editanywhere, category = "Combat")
		double WarpTargetDistance = 75.f;
	
	UPROPERTY(Editanywhere, category = "Combat")
		float DeathLifeSpan = 8.f;

	UPROPERTY(VisibleAnyWhere, Category = "Weapon")
		AWeapon* EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		UAnimMontage* AssassinatedMontage;



	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		UAnimMontage* HitReactMontage;

	UPROPERTY(Editanywhere, Category = "Combat")
		TArray<FName> AttackMontageSelections;

	UPROPERTY(Editanywhere, Category = "Combat")
		TArray<FName> DeathMontageSelections;

	/*CombatWarp*/
	UFUNCTION(BlueprintCallable)
		FVector GetTranslationWarpTarget();

	UFUNCTION(BlueprintCallable)
		FVector GetRotationWarpTarget();


};
