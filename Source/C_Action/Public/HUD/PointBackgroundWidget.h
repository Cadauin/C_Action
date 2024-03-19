// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PointBackgroundWidget.generated.h"

/**
 * 
 */
class UReSpawnPointWidget;
class UVerticalBox;
	class ARespawnPoint;
UCLASS()
class C_ACTION_API UPointBackgroundWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init();
	void RefreshPoint(ARespawnPoint* Point);

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<UReSpawnPointWidget> RespawnPointWidget;
private:
	UVerticalBox* VerticalBox;
};
