// Fill out your copyright notice in the Description page of Project Settings.


#include "Respawn/RespawnPoint.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/AttributeComponent.h"
#include "Components/ReSpawnPointComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "C_Action/C_ActionCharacter.h"
#include "HUD/ReSpawnPointWidget.h"
#include "HUD/PointBackgroundWidget.h"

// Sets default values
ARespawnPoint::ARespawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RespawnPointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RespawnPointMesh"));
	RespawnPointMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RespawnPointMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = RespawnPointMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
	Sphere->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(GetRootComponent());
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}



// Called when the game starts or when spawned
void ARespawnPoint::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this,&ARespawnPoint::OnBeginOverlap);
}

void ARespawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ARespawnPoint::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (!IsCheck)
	{
		AC_ActionCharacter* C_ActionCharacter = Cast<AC_ActionCharacter>(OtherActor);
		if (C_ActionCharacter) 
		{
			auto Background = Cast<UPointBackgroundWidget>(C_ActionCharacter->GetRespawnWidgetComponent()->GetWidget());
			if (Background)
			{
				Background->Init();
				Background->RefreshPoint(this);
				IsCheck = true;
			}
		}

		
	}

}
void ARespawnPoint::TransfromPlayer()
{	
	RespawnPlayer();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AC_ActionCharacter* MyC_ActionCharacter = Cast<AC_ActionCharacter>(PlayerController->GetPawn());
	FVector SpawnLocation = GetActorLocation()+GetActorForwardVector() * SpawnDistance;
	MyC_ActionCharacter->SetActorLocation(SpawnLocation);
}



void ARespawnPoint::RespawnPlayer()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AC_ActionCharacter* MyC_ActionCharacter = Cast<AC_ActionCharacter>(PlayerController->GetPawn());
	UAttributeComponent* AttributeComponent = MyC_ActionCharacter->FindComponentByClass<UAttributeComponent>();
	if (AttributeComponent)
	{
		AttributeComponent->Resetstate();
	}
}

