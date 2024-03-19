// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "HUD/Inventory/InsideWidget.h"
#include "HUD/Inventory/InventoryWidget.h"
#include "C_Action/C_ActionCharacter.h"
#include "Components/WidgetComponent.h"
#include "Items/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInventoryComponent::Init()
{
	InventoryWidget = Cast<UInventoryWidget>(Cast<AC_ActionCharacter>(GetOwner())->GetWidgetComponent()->GetWidget());
	InsideItemBox.SetNum(InsideItemBoxCount, false);
	InventoryWidget->Init(InsideItemBox);
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInventoryComponent::Use(AItem* Item)
{
}





void UInventoryComponent::ToggleInventoryWidget()
{
	auto WidgetComponent = Cast<AC_ActionCharacter>(GetOwner())->GetWidgetComponent();
	if (WidgetComponent->IsVisible())
	{
		WidgetComponent->SetVisibility(false);
		Cast<APlayerController>(Cast<AC_ActionCharacter>(GetOwner())->GetController())->SetInputMode(FInputModeGameOnly());
		Cast<APlayerController>(Cast<AC_ActionCharacter>(GetOwner())->GetController())->SetShowMouseCursor(false);
	}
	else
	{
		WidgetComponent->SetVisibility(true);
		Cast<APlayerController>(Cast<AC_ActionCharacter>(GetOwner())->GetController())->SetInputMode(FInputModeGameAndUI());
		Cast<APlayerController>(Cast<AC_ActionCharacter>(GetOwner())->GetController())->SetShowMouseCursor(true);
		GetWorld()->GetGameViewport()->SetMouseCaptureMode(EMouseCaptureMode::NoCapture);
		
	}
}

void UInventoryComponent::PickUp(AItem* Item)
{

	FItemDetails ItemDetail;
	ItemDetail = Item->GetItemDetails();
	

	for (int i = 0; i < ItemArray.Num(); i++)
	{
		if (InsideItemBox[i].ItemDetails.ID == ItemDetail.ID)
		{
			FItemDetails Temp;
			Temp = InsideItemBox[i].ItemDetails;
			Temp.Num+=ItemDetail.Num ;
			InsideItemBox[i].ItemDetails=Temp;
			InventoryWidget->RefreshInsideItemBox(InsideItemBox);
			return;
		}
	}
	int32 Index =FindIndexCouldSaveItem();
	if (Index == -1)
	{
		ItemArray.Add(Item);
		for (int i = 0; i < ItemArray.Num(); i++)
		{
			if (InsideItemBox[i].ItemDetails.Num == 0) {InsideItemBox[i].ItemDetails = ItemArray[i]->GetItemDetails();}
		}
		InventoryWidget->RefreshInsideItemBox(InsideItemBox);
	}
}



int32 UInventoryComponent::FindIndexCouldSaveItem()
{
	for (size_t i = 0; i < ItemArray.Num(); i++)
	{
		if (ItemArray[i]->GetItemDetails().ID == -1)
		{
			return i;
		}
	}
	return -1;
}

