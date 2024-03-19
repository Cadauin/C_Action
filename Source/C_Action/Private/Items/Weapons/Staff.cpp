// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Staff.h"
#include "C_Action/C_ActionCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"
#include "Interfaces/PickUpInterface.h"
#include "Interfaces/SpellMagicInterface.h"
#include "Niagaras/BaseNiagara.h"
#include "NiagaraComponent.h"

void AStaff::Equip(USceneComponent* InParent, FName InsocketName, AActor* NewOwner, APawn* NewInstigator)
{
}



void AStaff::SpellMagic(FRotator NewRotator, AActor* TargetActor, AActor* CreateActor)
{
	UWorld* World = GetWorld();
	FRotator MagicRotation;
	FVector SpellLocation = GetActorLocation()+GetActorForwardVector() * SpellDistance;
	TArray<AActor*> IgnoreActors;
	APlayerCameraManager* CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector CameraLocation = CameraManager->GetCameraLocation();
	FVector CameraForward = CameraManager->GetActorForwardVector();
	FVector CameraImpactPoint = CreateActor->GetActorLocation() + CameraForward * TraceDistance;
	
	IgnoreActors.Add(this);
	IgnoreActors.Add(CreateActor);
	if (TargetActor == nullptr)
	{

		FHitResult HitResult;
		bool Hit=UKismetSystemLibrary::LineTraceSingle(this, CreateActor->GetActorLocation(), CameraImpactPoint, ETraceTypeQuery::TraceTypeQuery1, false, IgnoreActors, EDrawDebugTrace::None, HitResult, true);
		if (Hit)
		{
			CameraImpactPoint = HitResult.ImpactPoint;
		}
	}
	else
	{
		CameraImpactPoint = TargetActor->GetActorLocation();
	}

	MagicRotation = FRotationMatrix::MakeFromX(CameraImpactPoint - SpellLocation).Rotator();
	
	if (World && Magic)
	{
		ABaseNiagara* SpawnedMagic = World->SpawnActor<ABaseNiagara>(Magic, SpellLocation, MagicRotation);
		if (SpawnedMagic)
		{
			TArray<FName> ActorTags = CreateActor->Tags;
			SpawnedMagic->Init(GetDamage(), CreateActor, TargetActor);
		}
	}
}



void AStaff::DeactivateEmber()
{
	
}



void AStaff::DisableSphereCollision()
{
}

void AStaff::PlayEquipSound()
{
}

void AStaff::AttachMeshToSocket(USceneComponent* InParent, const FName& InsocketName)
{
}

void AStaff::BeginPlay()
{
	Super::BeginPlay();
	
}
