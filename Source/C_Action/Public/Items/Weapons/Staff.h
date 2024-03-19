// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/weapons/weapon.h"
#include "Staff.generated.h"



class USoundBase;
class UBoxComponent;
class UNiagaraComponent;
class ABaseNiagara;
/**
 * 
 */
UCLASS()
class C_ACTION_API AStaff : public AWeapon
{
	GENERATED_BODY()

public:
	 void Equip(USceneComponent* InParent, FName InsocketName, AActor* NewOwner, APawn* NewInstigator) ;
	
	 void DeactivateEmber() ;
	 void DisableSphereCollision() ;
	 void PlayEquipSound() ;
	 void AttachMeshToSocket(USceneComponent* InParent, const FName& InsocketName) ;
	 void SpellMagic(FRotator NewRotator, AActor* TargetActor, AActor* CreateActor);

	UPROPERTY(Editanywhere, category = "Magic")
		TSubclassOf<ABaseNiagara> Magic;
		
	UPROPERTY(Editanywhere,category="Magic")
	float TraceDistance = 1500.f;


protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Editanywhere, category = "Magic")
	float SpellDistance=50.f;
};
