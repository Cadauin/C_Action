// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AssassinInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAssassinInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class C_ACTION_API IAssassinInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	void Assassinated(const FVector& ImpactPoint, AActor* Hitter);


};
