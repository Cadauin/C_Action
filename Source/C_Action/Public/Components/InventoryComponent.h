// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/Item.h"
#include "InventoryComponent.generated.h"


class UInsideWidget;
class UInventoryWidget;
struct FInsideItem
{
	FItemDetails ItemDetails;
	UInsideWidget* Widget = nullptr;
};
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class C_ACTION_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();
	void Init();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	TArray<FInsideItem>& GetInsideItemBox() { return InsideItemBox; };
	int32 FindIndexCouldSaveItem();



	void ToggleInventoryWidget();
	void PickUp(AItem* Item);
protected:
	virtual void BeginPlay() override;

	int32 InsideItemBoxCount = 20;

private:
	TArray<AItem*> ItemArray;
	TArray<FInsideItem> InsideItemBox;
	UInventoryWidget* InventoryWidget;
	TMap<int32, FItemDetails> ItemMap;

		
};
