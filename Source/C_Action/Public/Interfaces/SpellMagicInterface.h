// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpellMagicInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USpellMagicInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class C_ACTION_API ISpellMagicInterface
{
	GENERATED_BODY()

public:

	//UFUNCTION(BlueprintNativeEvent)
	//void SpawnMagic(FRotator NewRotator, AActor* TargetActor, AActor* CreateActor);
};
