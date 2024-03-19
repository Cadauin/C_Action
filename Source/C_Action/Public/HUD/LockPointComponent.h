// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "LockPointComponent.generated.h"

/**
 * 
 */
UCLASS()
class C_ACTION_API ULockPointComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	class ULockPoint* LockPoint;
	
};
