// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once



#include "Characters/BaseCharacter.h"
#include "InputActionValue.h"
#include "Characters/CharacterTypes.h"
#include "Interfaces/PickUpInterface.h"
#include "C_ActionCharacter.generated.h"


	class USpringArmComponent;
	class UCameraComponent;
	class UInputMappingContext;
	class UInputAction;
	class UGroomComponent;
	class AItem;
	class ATreasure;
	class AEnmey;
	class ASoul;
	class UAnimMontage;
	class USlashOverlay;
	class UWidgetComponent;
	class UInventoryComponent;
	class UReSpawnPointComponent;
	class UPointBackgroundWidget;
	class UNiagaraComponent;
UCLASS(config=Game)
class AC_ActionCharacter : public ABaseCharacter, public IPickUpInterface
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

	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = Input, meta = (AllowprivateAccess = "true"))
		UInputAction* Dodge;

	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = Input, meta = (AllowprivateAccess = "true"))
		UInputAction* AssassinKey;

	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = Input, meta = (AllowprivateAccess = "true"))
		UInputAction* InventoryKey;

	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = Input, meta = (AllowprivateAccess = "true"))
		UInputAction* CameraLockKey;

	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = Input, meta = (AllowprivateAccess = "true"))
		UInputAction* RespawnPointKey;

	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = Input, meta = (AllowprivateAccess = "true"))
		UInputAction* DashKey;

	UPROPERTY(VisibleAnyWhere, Category = "Groom")
		UGroomComponent* Hair;

	UPROPERTY(VisibleAnyWhere,Category="Groom")
		UGroomComponent* Eyebrows;

	UPROPERTY(VisibleAnyWhere, Category = "Groom")
		UNiagaraComponent* DashNiagara;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverLappingItem;

	/*
	*Montages
	*/


	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		UAnimMontage* DodgeMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		UAnimMontage* DashMontage;

	/*
	Assassin
	*/
	UPROPERTY(Editanywhere, Category = "Assassin")
		float AssassinDistance =150.f;



public:
	AC_ActionCharacter();
	
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; };
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

	virtual void Jump() override;
	virtual void Die_Implementation() override;
	virtual void SetOverLappingItem(AItem* Item)override;
	virtual void AddSouls(ASoul* Soul)override;
	virtual void AddGold(ATreasure* Treasure)override;

	/*Assassin*/

	UPROPERTY(BlueprintReadOnly)
	class AEnemy* AssassinTarget;

	UPROPERTY(BlueprintReadOnly)
	FVector AssassinLocation;
	UPROPERTY(BlueprintReadOnly)
	FRotator AssassinRotation;
	
	FHitResult AssassinHitResult;
protected:

	virtual void BeginPlay();
	
	virtual void Tick(float DeltaTime)override;
	void CameraFollow();
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			
	void EquipKey(const FInputActionValue& Value);

	void Attacked(const FInputActionValue& value) ;
	
	void Dodged(const FInputActionValue& value);

	void Assassin(const FInputActionValue& value);

	void CameraLock(const FInputActionValue& value);

	void Dash(const FInputActionValue& value);

	void SwapWeapon();

	UFUNCTION(BlueprintCallable)
	void SetCollisionIgnore();

	bool HasEnoughStamina(float Cost);

	bool IsOccupied();

	void EquipWeapon(AWeapon* Weapon);



	ECharacterState SetEquipWeaponState(AWeapon* Weapon);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
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

	

	bool AssassinBack(AActor& Actor);

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();

	UFUNCTION(BlueprintCallable)
		void FinishEquipping();

	UFUNCTION(BlueprintCallable)
		void HitReactEnd();

	UFUNCTION(BlueprintCallable)
		void DodgeEnd();

	UFUNCTION(BlueprintCallable)
	void ResetMeshCollision();

	UFUNCTION(BlueprintCallable)
		void AssassinEnd();

	UFUNCTION(BlueprintCallable)
		void CallStaff();

	UFUNCTION(BlueprintCallable)
		void EnableCollision();

	UFUNCTION(BlueprintCallable)
		void DisableCollision(); 
	/*
	Camera
	*/
	FHitResult CameraHitResult;

	bool IsCameraLock=false;

	bool IsCameraForwardHaveSomething = false;

	bool IsCameraLockBox = false;
	
	UPROPERTY(Editanywhere,category="Camera")
	float CameraHeight = 50.0f;

	UPROPERTY(Editanywhere, category = "Camera")
	float CameraDistance = 100.f;

	UPROPERTY(Editanywhere, category = "Camera")
	float CameraRotationSpeed = 5.0f;

	UPROPERTY(Editanywhere, category = "Camera")
	float CameraSmoothness = 0.5f;

	UPROPERTY(EditAnyWhere,Category="Camera")
	FVector CameraLockBox = FVector(1000.f,50.f ,50.f );

	UPROPERTY(EditAnyWhere, category = "Camera")
		float CameraLockDistance = 2000.f;

	UPROPERTY(Editanywhere, category = "Camera")
		AActor* ActorTarget = nullptr;

	UPROPERTY(Editanywhere, category = "Camera")
		AEnemy* CameraTarget = nullptr;

	UPROPERTY(Editanywhere, category = "Camera")
	class ABossCharacter* CameraBossTarget = nullptr;

	UPROPERTY(EditAnywhere, Category = "Camera")
		TEnumAsByte<ETraceTypeQuery> CameraTracetype01;

	UPROPERTY(EditAnywhere, Category = "Dash")
		float DashDistance=3000.f;
private:
	ECharacterState CharacterState = ECharacterState::ECS_UnEquip;

	UPROPERTY(BlueprintReadWrite,meta=(AllowPrivateAccess="True"))
	EActionState ActionState = EActionState::EAS_Unoccupied;
	

	void InitializeSlashOverlay();
	UPROPERTY()
		USlashOverlay* SlashOverlay;
	void SetHealthHUD();

	TArray<AWeapon*> WeaponClass;
	int32 NowWeaponNum=0;

	

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE EActionState GetActionState() const { return ActionState; }

	FORCEINLINE bool GetLockbool() const { return IsCameraLock; }

	float GetDirection();
/*
Inventory
*/
	UPROPERTY(EditAnywhere, Category = "Inventory")
		UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, Category = "Inventory")
		UWidgetComponent* WidgetComponent;

	FORCEINLINE UWidgetComponent* GetWidgetComponent() { return WidgetComponent; };

	void PickUpItem(AItem* Item);


	UPROPERTY(Editanywhere, Category = "Respawn")
		UReSpawnPointComponent* RespawnPointComponent;

	UPROPERTY(Editanywhere)
		UWidgetComponent* PointBackgroundWidget;

	FORCEINLINE UWidgetComponent* GetRespawnWidgetComponent() { return PointBackgroundWidget; };
};

