// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once



#include "Characters/BaseCharacter.h"
#include "InputActionValue.h"
#include "Characters/CharacterTypes.h"
#include "C_ActionCharacter.generated.h"


	class USpringArmComponent;
	class UCameraComponent;
	class UInputMappingContext;
	class UInputAction;
	class UGroomComponent;
	class AItem;
	class UAnimMontage;


UCLASS(config=Game)
class AC_ActionCharacter : public ABaseCharacter
{
	
	GENERATED_BODY()
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	 UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	 UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	 UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Equip;

	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = Input, meta = (AllowprivateAccess = "true"))
		UInputAction* Attack;

	UPROPERTY(VisibleAnyWhere, Category = "Groom")
		UGroomComponent* Hair;

	UPROPERTY(VisibleAnyWhere,Category="Groom")
		UGroomComponent* Eyebrows;
	UPROPERTY(VisibleInstanceOnly)
	AItem* OverLappingItem;

	/*
	*Montages
	*/


	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		UAnimMontage* EquipMontage;


public:
	AC_ActionCharacter();
	
	FORCEINLINE void SetOverLappingItem(AItem* Item) { OverLappingItem = Item; };
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; };
	

protected:
	virtual void BeginPlay();
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			
	void EKeyPressed(const FInputActionValue& Value);

	void Attacked(const FInputActionValue& value) ;

	void EquipWeapon(AWeapon* Weapon);
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	*Play Montage Funtions
	*/

	virtual void AttackEnd() override;

	virtual bool CanAttack() override;

	void PlayEquipMontage(const FName& SelectionName);

	bool CanDisarm();
	void Disarm();

	bool Canarm();
	void Arm();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();

	UFUNCTION(BlueprintCallable)
		void FinishEquipping();

	
	// To add mapping context
	
private:
	ECharacterState CharacterState = ECharacterState::ECS_UnEquip;

	UPROPERTY(BlueprintReadWrite,meta=(AllowPrivateAccess="True"))
	EActionState ActionState = EActionState::EAS_Unoccupied;
	

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

