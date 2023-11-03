// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;
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


	EItemState ItemState = EItemState::EIS_Hovering;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
