// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

class USoundBase;
class UBoxComponent;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class C_ACTION_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	AWeapon();
	void Equip(USceneComponent* InParent, FName InsocketName, AActor* NewOwner ,APawn* NewInstigator);
	void AttachMeshToSocket(USceneComponent* InParent, const FName& InsocketName);

	TArray<AActor*> IgnoreActor;

	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }
protected:
		virtual void BeginPlay() override;

		virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

		virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

		UFUNCTION()
			void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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



};
