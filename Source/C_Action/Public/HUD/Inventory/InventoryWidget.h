// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
class UUniformGridPanel;
class UInsideWidget;
class UWidget;
struct FItemDetails;
struct FInsideItem;
UCLASS()
class C_ACTION_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init(TArray<FInsideItem>& InsideItemBox);

	void RefreshInsideItemBox(TArray<FInsideItem>& InsideItemBox);
	int GetGridPanelIndex();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UInsideWidget> UInsideItemWidgetClass;


private:
	UPROPERTY(meta = (BindWidget))
		UUniformGridPanel* GridPanel;

	TArray<UWidget*> Widgets;
};
