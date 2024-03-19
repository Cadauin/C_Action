// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ReSpawnPointWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Respawn/RespawnPoint.h"
#include "C_Action/C_ActionCharacter.h"

void UReSpawnPointWidget::Init()
{
	ReSpawnPointName = Cast<UTextBlock>(this->GetWidgetFromName("ReSpawnPointName"));
	Button = Cast<UButton>(this->GetWidgetFromName("Button"));
}

void UReSpawnPointWidget::SetWidget(ARespawnPoint* Point)
{
	if (Point) 
	{
		this->ReSpawnPointName->SetText(FText::FromName(Point->GetName()));
		Button->OnClicked.AddDynamic(Point, &ARespawnPoint::TransfromPlayer);
	}

}


