// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HealthBarComponent.h"
#include "HUD/HealthBar.h"
#include "Components/ProgressBar.h"


void UHealthBarComponent::SetHealthPercent(float Percent)
{
	if (HealthBarwWidget == NULL)
	{
		HealthBarwWidget = Cast<UHealthBar>(GetUserWidgetObject());
	}
	if (HealthBarwWidget&&HealthBarwWidget->HealthBar)
	{
		HealthBarwWidget->HealthBar->SetPercent(Percent);
		


	}

}
