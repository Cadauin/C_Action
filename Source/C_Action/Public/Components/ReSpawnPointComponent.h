// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ReSpawnPointComponent.generated.h"

class ARespawnPoint;
class UPointBackgroundWidget;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C_ACTION_API UReSpawnPointComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UReSpawnPointComponent();

	void Init();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ToggleRespawnPointWidget();

	void CheckPoint(ARespawnPoint* Point);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



private:
	TArray<ARespawnPoint*> TarrayRespawnPoint;
	UPointBackgroundWidget* BackgroundWidget;
};
