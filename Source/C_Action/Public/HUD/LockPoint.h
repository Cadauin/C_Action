// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LockPoint.generated.h"

/**
 * 
 */
UCLASS()
class C_ACTION_API ULockPoint : public UUserWidget
{
	GENERATED_BODY()
public:
	class UImage* LockPoint;
};
