// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;
class UNiagaraComponent;
class UNiagaraSystem;
enum class EItemState :uint8 {
	EIS_Hovering,
	EIS_Equiped
};

UCLASS()
class C_ACTION_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(EditanyWhere, category = "My actor")
		UStaticMeshComponent* ItemMesh;

	UPROPERTY(Editanywhere, category = "My actor")
		ACharacter* Character;

	UPROPERTY(Editanywhere, category = "Spherecomponent")
		USphereComponent* Sphere;


	virtual void Tick(float DeltaTime) override;


	EItemState ItemState = EItemState::EIS_Hovering;

	UPROPERTY(Editanywhere, category = "Niagara")
		UNiagaraComponent* ItemEffect;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SpawnPickUpsystem();
	virtual void SpawnPickSound();

	UFUNCTION()
		virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintPure)
		float TransformedSin();

	UFUNCTION(BlueprintPure)
		float TransformedCos();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exposed | Sine Parameters")
		float Amplitude = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exposed | Sine Parameters")
		float TimeConstant = 5.f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Exposed | Info")
		float RunningTime = 0.f;

	UPROPERTY(Editanywhere, Category = "Effect")
		UNiagaraSystem* PickUpEffect;

	UPROPERTY(Editanywhere, Category = "Effect")
		USoundBase* PickUpSound;
};
