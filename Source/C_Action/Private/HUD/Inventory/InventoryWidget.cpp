// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Inventory/InventoryWidget.h"
#include "HUD/Inventory/InsideWidget.h"
#include "Components/InventoryComponent.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/WidgetComponent.h"

void UInventoryWidget::Init(TArray<FInsideItem>& InsideItemBox)
{
	
	GridPanel = Cast<UUniformGridPanel>(this->GetWidgetFromName("GridPanel"));
	GridPanel->ClearChildren();
	for (int i = 0; i < InsideItemBox.Num(); i++)
		{
				UInsideWidget* InsideWidget = Cast<UInsideWidget>(CreateWidget(GridPanel, UInsideItemWidgetClass));
				InsideWidget->Init();
				InsideWidget->SetWidget(InsideItemBox[i].ItemDetails);
				InsideItemBox[i].Widget = InsideWidget;
				UUniformGridSlot* GridSlot = GridPanel->AddChildToUniformGrid(InsideItemBox[i].Widget);
				int o = i % 4;
				GridSlot->SetRow(o);
				int j = i / 4;
				GridSlot->SetColumn(j);
		}

	
}




void UInventoryWidget::RefreshInsideItemBox(TArray<FInsideItem>& InsideItemBox)
{
	for (size_t i = 0; i < InsideItemBox.Num(); i++)
	{
		if (InsideItemBox[i].Widget != nullptr&&InsideItemBox[i].ItemDetails.ID!=0)
		{
			InsideItemBox[i].Widget->Init();			
			InsideItemBox[i].Widget->SetWidget(InsideItemBox[i].ItemDetails);
		}
	}
}

int UInventoryWidget::GetGridPanelIndex()
{
	return GridPanel->GetChildrenCount();
}





