


#include "Niagaras/BaseNiagara.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/HitInterfaces.h"



ABaseNiagara::ABaseNiagara()
{
	PrimaryActorTick.bCanEverTick = true;

	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	Niagara->SetupAttachment(GetRootComponent());

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(Niagara);
	Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);


	ProjectileMonement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMonement"));
	ProjectileMonement->ProjectileGravityScale = ProjectileGravity;
	ProjectileMonement->Velocity = ProjectileVelocity;
}

// Called when the game starts or when spawned
void ABaseNiagara::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&ABaseNiagara::OnBoxOverlap);
}

void ABaseNiagara::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this&&OtherActor!=NiagaraCreateActor)
	{
		ExecuteGetHit(OtherActor);
	}
}

void ABaseNiagara::ExecuteGetHit(AActor* BoxHit)
{
	
	if (!NiagaraCreateActor || !BoxHit || !UDamageType::StaticClass())
	{
		return;
	}
	IHitInterfaces* HitInterface = Cast<IHitInterfaces>(BoxHit);
	if (HitInterface)
	{
		AController* Player = NiagaraCreateActor->GetInstigator()->GetController();
		if (Player)
		{ 
			UGameplayStatics::ApplyDamage(BoxHit, Damage, Player, NiagaraCreateActor,UDamageType::StaticClass());
		}
		HitInterface->Execute_GetHit(BoxHit,BoxHit->GetActorLocation(), NiagaraCreateActor);
		Destroy();
	}
}



// Called every frame
void ABaseNiagara::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseNiagara::Init(float WeaponDamage,AActor* Create,AActor* Target)
{
	SetCreateActor(Create);
	SetTargetActor(Target);
	SetDamage(WeaponDamage);
	SetLifeSpan(LifeTime);
}




void ABaseNiagara::SetDamage(float NewDamage)
{
	Damage = NewDamage;
}

void ABaseNiagara::SetAActorTag(const FName& Tag)
{
	Tags.Add(Tag);
}

void ABaseNiagara::SetSpeed(FVector Speed)
{
	ProjectileMonement->Velocity = Speed;
}



