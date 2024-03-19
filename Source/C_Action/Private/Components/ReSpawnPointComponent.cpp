// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ReSpawnPointComponent.h"
#include "HUD/PointBackgroundWidget.h"
#include "HUD/ReSpawnPointWidget.h"
#include "Components/WidgetComponent.h"
#include "C_Action/C_ActionCharacter.h"

// Sets default values for this component's properties
UReSpawnPointComponent::UReSpawnPointComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UReSpawnPointComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
void UReSpawnPointComponent::Init()
{
	BackgroundWidget = Cast<UPointBackgroundWidget>(Cast<AC_ActionCharacter>(GetOwner())->GetWidgetComponent()->GetWidget());
	if (BackgroundWidget)
	{
		BackgroundWidget->Init();
	}
}



// Called every frame
void UReSpawnPointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UReSpawnPointComponent::ToggleRespawnPointWidget()
{
	auto WidgetComponent = Cast<AC_ActionCharacter>(GetOwner())->GetRespawnWidgetComponent();
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

void UReSpawnPointComponent::CheckPoint(ARespawnPoint* Point)
{
	if (Point) { TarrayRespawnPoint.Add(Point); }
	
}


