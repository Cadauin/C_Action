// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickUpInterface.generated.h"

UINTERFACE(MinimalAPI)


class UPickUpInterface : public UInterface
{
	GENERATED_BODY()
};
/**
 * 
 */
class C_ACTION_API IPickUpInterface

{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetOverLappingItem(class AItem* Item) ;
	virtual void AddSouls(class ASoul* Soul);
	virtual void AddGold(class ATreasure* Treasure);
	virtual void PickUpItem(AItem* Item);
};
