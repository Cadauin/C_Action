// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlashOverlay.generated.h"

/**
 * 
 */
class UProgressBar;
class UTextBlock;
UCLASS()

class C_ACTION_API USlashOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public :
	void SetHealthBarpercent(float Percent);
	void SetStaminaBarPercent(float Percent);
	void SetGold(int32 Gold);
	void SetSouls(int32 Soul);

private:
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* HealthProgressBar;
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* StaminaProgressBar;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* SoulsCount;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* GoldCount;
};
