// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RespawnPoint.generated.h"


class UStaticMeshComponent;
class USphereComponent;
class UBoxComponent;
class UReSpawnPointWidget;
class UPointBackgroundWidget;

struct ReSpawnPointDetail
{
	int32 ID;
	FName PointName;
};
UCLASS()
class C_ACTION_API ARespawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARespawnPoint();
	virtual void Tick(float DeltaTime) override;

	bool GetCheck() const { return IsCheck; }

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void RespawnPlayer();

	UFUNCTION()
		void TransfromPlayer();

	int GetID() const { return ID; }
	FName GetName() const { return PointName; }
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Editanywhere, Category = "Mesh")
		UStaticMeshComponent* RespawnPointMesh;
	
	UPROPERTY(Editanywhere, category = "Spherecomponent")
		USphereComponent* Sphere;

	UPROPERTY(Editanywhere, category = "Spherecomponent")
		UBoxComponent* Box;

	UPROPERTY(Editanywhere,category="test")
	TSubclassOf<UReSpawnPointWidget> TestWidget;

	UPROPERTY(Editanywhere, category = "Spawn")
		float SpawnDistance=100.f;

	UPROPERTY(Editanywhere, category = "Widget")
		FName PointName;

	UPROPERTY(Editanywhere, category = "Widget")
		int32 ID;

	UPROPERTY(Editanywhere, category = "Widget")
	bool IsCheck = false;
	
};
