// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/CharacterTypes.h"
#include "SlashAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class C_ACTION_API USlashAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float Deltatime) override;
	
	UPROPERTY(BlueprintReadOnly)
		class AC_ActionCharacter* SlashCharacter;

	UPROPERTY(BlueprintReadOnly,category = "Movement")
		class UCharacterMovementComponent* SlashCharacterMovement;

	UPROPERTY(BlueprintReadOnly,category="Movement")
		float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, category = "Movement")
		bool IsFalling;

	UPROPERTY(BlueprintReadOnly,category="Movement")
	ECharacterState CharacterState;

	UPROPERTY(BlueprintReadOnly, category = "Action State")
		EActionState ActionState;

	UPROPERTY(BlueprintReadOnly, category = "Action State")
	TEnumAsByte<EDeathPose> DeathPose;
};
