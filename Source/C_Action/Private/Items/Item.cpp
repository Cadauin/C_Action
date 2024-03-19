// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Components/SphereComponent.h"
#include "C_Action/C_ActionCharacter.h"
#include "Interfaces/PickUpInterface.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
// Sets default values
AItem::AItem()
{

	PrimaryActorTick.bCanEverTick = true;
	
	ItemMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = ItemMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);
	
	ItemEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("EmberEffect"));
	ItemEffect->SetupAttachment(GetRootComponent());

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetRootComponent());


}





void AItem::SetItemDetails(FItemDetails NewDetails)
{
	this->ID = NewDetails.ID;
	this->Num = NewDetails.Num;
	this->ItemName = NewDetails.ItemName;
	this->ItemDescribe = NewDetails.ItemDescribe;
	this->ItemIcon = NewDetails.ItemIcon;
	ItemMesh->SetStaticMesh(NewDetails.Mesh);
}

FItemDetails AItem::GetItemDetails()
{
	FItemDetails SelfDetails;

	SelfDetails.ID = this->ID;
	SelfDetails.Num = this->Num;
	SelfDetails.ItemName = this->ItemName;
	SelfDetails.ItemDescribe = this->ItemDescribe;
	SelfDetails.ItemIcon = this->ItemIcon;
	SelfDetails.Mesh = ItemMesh->GetStaticMesh();

	return SelfDetails;
}






void AItem::SetWidgetVisibility(bool NewValue)
{
	WidgetComponent->SetVisibility(NewValue);
}

UWidgetComponent* AItem::GetWidgetComponet()
{
	return WidgetComponent;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
}
void AItem::SpawnPickUpsystem()
{
	if (PickUpEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, PickUpEffect, GetActorLocation());
	}
}
void AItem::SpawnPickSound()
{
	if (PickUpSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, PickUpSound, GetActorLocation());
	}
}
void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickUpInterface* HitInterface = Cast<IPickUpInterface>(OtherActor);

	if (HitInterface)
	{
		HitInterface->SetOverLappingItem(this);
	}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IPickUpInterface* HitInterface = Cast<IPickUpInterface>(OtherActor);
	if (HitInterface)
	{
		HitInterface->SetOverLappingItem(nullptr);
	}
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	if (ItemState == EItemState::EIS_Hovering)
	{
		AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));
	}
}
float AItem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformedCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}


