// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PointBackgroundWidget.h"
#include "Components/VerticalBox.h"
#include "HUD/ReSpawnPointWidget.h"
#include "Respawn/RespawnPoint.h"
#include "Components/WidgetComponent.h"

void UPointBackgroundWidget::Init()
{
	VerticalBox=Cast<UVerticalBox>(this->GetWidgetFromName("VerticalBox"));
}

void UPointBackgroundWidget::RefreshPoint(ARespawnPoint* Point)
{
	UReSpawnPointWidget* PointWidget = Cast<UReSpawnPointWidget>(CreateWidget(VerticalBox, RespawnPointWidget));
	if (PointWidget)
	{
		VerticalBox->AddChild(PointWidget);
		PointWidget->Init();
		PointWidget->SetWidget(Point);
	}
}
