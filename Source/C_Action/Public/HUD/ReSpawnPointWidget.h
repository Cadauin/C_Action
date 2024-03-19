// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReSpawnPointWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UButton;
class ARespawnPoint;
UCLASS()
class C_ACTION_API UReSpawnPointWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init();
	void SetWidget(ARespawnPoint* Point);
private:
	UTextBlock* ReSpawnPointName;
	UButton* Button;
};
