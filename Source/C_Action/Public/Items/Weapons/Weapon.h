// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

class USoundBase;
class UBoxComponent;
class UNiagaraComponent;

UENUM(BlueprintType)
enum class WeaponState : uint8{
		One_Hand,
		Two_Hand
};

/**
 * 
 */
UCLASS()
class C_ACTION_API AWeapon : public AItem
{
	GENERATED_BODY()

public:

	AWeapon();
	void Equip(USceneComponent* InParent, FName InsocketName, AActor* NewOwner ,APawn* NewInstigator) ;
	void DeactivateEmber();
	void DisableSphereCollision();
	void PlayEquipSound();
	void AttachMeshToSocket(USceneComponent* InParent, const FName& InsocketName);

	TArray<AActor*> IgnoreActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Weapon")
	WeaponState WhatEquipWeapon = WeaponState::One_Hand;

	FORCEINLINE	WeaponState GetWeaponState() const { return WhatEquipWeapon; }

	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }

	FORCEINLINE float GetDamage() const { return Damage; }

	FORCEINLINE int32 GetWeaponAnimNum()const { return WeaponAnim; }

	FName GetWeaponEquipName();

	FName GetWeaponStorageName();
protected:
		virtual void BeginPlay() override;


		UFUNCTION()
		void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		bool ActorIsSameType(AActor* OtherActor);

		void ExecuteGetHit(FHitResult& BoxHit);

		UFUNCTION(BlueprintImplementableEvent)
		void CreatFields(const FVector& FieldLocation);
private:
	UPROPERTY(EditAnyWhere,Category="Weapon Properties")
		USoundBase* EquipSound;
	UPROPERTY(EditAnyWhere, Category = "Weapon Properties")
		UBoxComponent* WeaponBox;



	UPROPERTY(EditAnyWhere, Category = "Weapon Properties")
		float Damage=20.f;

	UPROPERTY(EditAnyWhere)
		USceneComponent* BoxTraceStart;

	UPROPERTY(EditAnyWhere)
		USceneComponent* BoxTraceEnd;

	virtual void BoxTrace(FHitResult& BoxHit);

	UPROPERTY(Editanywhere,category="Weapon Properties")
	FVector BoxTraceExtent = FVector(5.f);

	UPROPERTY(Editanywhere, category = "Weapon Properties")
		bool ShowBoxDebug = false;

	UPROPERTY(Editanywhere, category = "Weapon Properties")
		FString WeaponEquipName;
	UPROPERTY(Editanywhere, category = "Weapon Properties")
		FString WeaponStorageName;
	UPROPERTY(Editanywhere, category = "Weapon Properties")
	int32 WeaponAnim=0;

};
