// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseNiagara.generated.h"

class UNiagaraComponent;
class USphereComponent;
class UProjectileMovementComponent;
UCLASS()
class C_ACTION_API ABaseNiagara : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseNiagara();
	virtual void Tick(float DeltaTime) override;
	virtual void Init(float WeaponDamage, AActor* Create, AActor* Target);
	virtual void SetDamage(float NewDamage);
	void SetTargetActor(AActor* TargetActor) { NiagaraTargetActor = TargetActor; };
	void SetCreateActor(AActor* CreateActor) { NiagaraCreateActor = CreateActor; };
	void SetAActorTag(const FName& Tag);
	void SetSpeed(FVector Speed);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(Editanywhere, Category = "Niagara")
		UNiagaraComponent* Niagara;

	UPROPERTY(Editanywhere, Category = "Niagara")
		USphereComponent* Sphere;

	UPROPERTY(Editanywhere, Category = "Niagara")
		USoundBase* NiagaraSound;

	UPROPERTY(Editanywhere, BlueprintReadWrite, category = "Niagara")
		float LifeTime = 10.f;

	UPROPERTY(Editanywhere, BlueprintReadWrite, category = "ProjectileMonement")
		UProjectileMovementComponent* ProjectileMonement;

	UPROPERTY(Editanywhere, BlueprintReadWrite, category = "ProjectileMonement")
		int32 ProjectileGravity=0.f;

	UPROPERTY(Editanywhere, BlueprintReadWrite, category = "ProjectileMonement")
		FVector ProjectileVelocity=FVector(1500.f,0.f,0.f);

	UPROPERTY(Editanywhere, BlueprintReadWrite, category = "DamageType")
		TSubclassOf<UDamageType> DamageType;

	UFUNCTION()
		void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void ExecuteGetHit(AActor* BoxHit);

	TArray<AActor*> IgnoreActor;
private:
	int32 Damage=5;
	AActor* NiagaraTargetActor = nullptr;
	AActor* NiagaraCreateActor = nullptr;
	
	
	

};
