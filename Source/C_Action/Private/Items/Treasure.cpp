// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Treasure.h"
#include "C_Action/C_ActionCharacter.h"
#include "Kismet/Gameplaystatics.h"

void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AC_ActionCharacter* SlashCharacter = Cast<AC_ActionCharacter>(OtherActor);

	if (SlashCharacter)
	{
		if (PickSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, PickSound, GetActorLocation());
		}
		
		Destroy();
	}

}
