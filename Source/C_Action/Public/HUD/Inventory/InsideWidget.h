// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InsideWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UImage;
class UButton;
struct FItemDetails;
class UInventoryWidget;
UCLASS()
class C_ACTION_API UInsideWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init();
	void SetWidget(FItemDetails& Details);

	UFUNCTION(BlueprintCallable)
		void Use(UTextBlock* Num);

private:
	 UTextBlock* ItemNum;
	 UImage* ItemIcon;
	 UButton* ItemButton;
};
