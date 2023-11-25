// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Soul.generated.h"

/**
 * 
 */
UCLASS()
class C_ACTION_API ASoul : public AItem
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay();
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;

private:
	UPROPERTY(EditAnywhere, category = "Souls Properties")
		int32 Souls;

	double DesiredZ = 0.f;

	UPROPERTY(EditAnyWhere)
	float DriftRate = -15.f;
public:
	virtual void Tick(float Deltatime)override;

	FORCEINLINE int32 GetSouls() { return Souls; }
	FORCEINLINE void SetSouls(int32 NumberOfSouls) { Souls = NumberOfSouls; }
};
