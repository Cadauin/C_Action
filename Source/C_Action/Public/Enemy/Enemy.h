// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/HitInterfaces.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class UAnimMontage;

UCLASS()
class C_ACTION_API AEnemy : public ACharacter, public IHitInterfaces
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/*
	*Montages
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		UAnimMontage* HitReactMontage;

	UPROPERTY(Editanywhere,category="Sounds")
	USoundBase* HitSound;

	UPROPERTY(Editanywhere, category = "VisualEffect")
		UParticleSystem* HitParticles;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	void DirectionalHitReact(const FVector& ImpactPoint);

	/*
*Play Montage Funtions
*/
	void PlayHitReactMontage(const FName& SelectionName);

};
