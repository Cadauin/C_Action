// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterfaces.h"
#include "BreakableActor.generated.h"


class UGeometryCollectionComponent;
class UCapsuleComponent;
UCLASS()
class C_ACTION_API ABreakableActor : public AActor ,public IHitInterfaces
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Visibleanywhere,BlueprintReadWrite)
		UCapsuleComponent* Capsule;

private:
	bool bBroken = false;

	UPROPERTY(Visibleanywhere)
	UGeometryCollectionComponent* GeometryCollection;
	
	UPROPERTY(Editanywhere,category="Breakable Properties")
	TArray<TSubclassOf<class ATreasure>> TreasureClass;
};
