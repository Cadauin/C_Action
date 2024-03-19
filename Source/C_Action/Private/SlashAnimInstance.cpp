// Fill out your copyright notice in the Description page of Project Settings.


#include "SlashAnimInstance.h"
#include "C_Action/C_ActionCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"



void USlashAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	SlashCharacter = Cast<AC_ActionCharacter>(TryGetPawnOwner());
	if (SlashCharacter)
	{
		SlashCharacterMovement = SlashCharacter->GetCharacterMovement();
	}
}

void USlashAnimInstance::NativeUpdateAnimation(float Deltatime)
{
Super:: NativeUpdateAnimation(Deltatime);


	if (SlashCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(SlashCharacterMovement->Velocity);
		IsLockTarget = SlashCharacter->GetLockbool();
		if (IsLockTarget)
		{Direction = SlashCharacter->GetDirection();}
		IsFalling = SlashCharacterMovement->IsFalling();
		CharacterState = SlashCharacter->GetCharacterState();
		ActionState = SlashCharacter->GetActionState();
		DeathPose = SlashCharacter->GetDeadPose();
	}

}

