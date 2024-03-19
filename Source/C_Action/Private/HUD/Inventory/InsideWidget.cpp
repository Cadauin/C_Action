
// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Inventory/InsideWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Items/Item.h"
#include "HUD/Inventory/InventoryWidget.h"

void UInsideWidget::Init()
{
	ItemNum = Cast<UTextBlock>(this->GetWidgetFromName("ItemNum"));
	ItemIcon = Cast<UImage>(this->GetWidgetFromName("ItemIcon"));
	ItemButton = Cast<UButton>(this->GetWidgetFromName("ItemButton"));
}

void UInsideWidget::SetWidget(FItemDetails& Details)
{
	if (Details.ID == -1)
	{
		return;
	}
	this->ItemIcon->SetBrushResourceObject(Details.ItemIcon);
	this->ItemNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), Details.Num)));
	this->ItemButton->SetToolTipText(Details.ItemName);
}

void UInsideWidget::Use(UTextBlock* Num)
{
    if (Num)
    {
        FText NumAsText = Num->GetText();

       
        FString NumAsString = NumAsText.ToString();

        int32 NumAsInt;
        NumAsInt = FCString::Atoi(*NumAsString);
		if (NumAsInt > 0)
		{

		}
        
    }

}

