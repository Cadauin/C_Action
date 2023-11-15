// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterfaces.h"
#include "Components/AttributeComponent.h"
#include "BaseCharacter.generated.h"

class AWeapon;
class UAnimMontage;
class UAttributeComponent;
UCLASS()

class C_ACTION_API ABaseCharacter : public ACharacter,public IHitInterfaces
{
	GENERATED_BODY()

public:
	
	ABaseCharacter();

	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void SetWeaponCollision(ECollisionEnabled::Type CollisionEnable);

protected:
	virtual void BeginPlay() override;
	virtual void Attack();
	virtual bool CanAttack();
	bool IsAlive();


	UFUNCTION(BlueprintCallable)
	virtual	void AttackEnd();

	virtual void Die();
	/*
	Components
	*/

	UPROPERTY(VisibleAnywhere)
		UAttributeComponent* Attributes;

	UPROPERTY(Editanywhere, category = "Sounds")
		USoundBase* HitSound;

	UPROPERTY(Editanywhere, category = "VisualEffect")
		UParticleSystem* HitParticles;

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
	void DisableCapsule();
	
	
	UPROPERTY(Editanywhere, category = "Combat")
		float DeathLifeSpan = 8.f;

	UPROPERTY(VisibleAnyWhere, Category = "Weapon")
		AWeapon* EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		UAnimMontage* DeathMontage;

	

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		UAnimMontage* HitReactMontage;

	UPROPERTY(Editanywhere, Category = "Combat")
		TArray<FName> AttackMontageSelections;

	UPROPERTY(Editanywhere, Category = "Combat")
		TArray<FName> DeathMontageSelections;
};
