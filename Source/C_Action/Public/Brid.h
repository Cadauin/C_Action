// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Brid.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
UCLASS()
class C_ACTION_API ABrid : public APawn
{
	GENERATED_BODY()

public:
	ABrid();
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void MoveForWard(const FInputActionValue& Value);

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, category = "Input")
	UInputMappingContext* BridIMappingContext;

	UPROPERTY(editanywhere, BlueprintReadOnly, category = "Input")
	UInputAction* MoveAction;
private:
	UPROPERTY(visibleanywhere,category="Capsule")
	UCapsuleComponent* capsule;

	UPROPERTY(visibleanywhere)
	USkeletalMeshComponent* Bridmesh;

	UPROPERTY(visibleanywhere)
		USpringArmComponent* SpringArm;

	UPROPERTY(visibleanywhere)
		UCameraComponent* ViewCamera;
};
