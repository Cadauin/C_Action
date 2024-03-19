
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C_ACTION_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAttributeComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ReceiveDamage(float Damage);
	void UseStamina(float StaminaCost);
	void RegenStamina(float DeltaTime);

	void Resetstate();

	float GetHealthPercent();
	float GetStaminaPercent();
	bool IsAlive();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, category = "Actor Attributes")
	float MaxHealth=100.f;

	UPROPERTY(EditAnywhere,category="Actor Attributes")
	float Health=MaxHealth;

	UPROPERTY(EditAnywhere, category = "Actor Attributes")
		float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, category = "Actor Attributes")
		float Stamina = MaxHealth;

	UPROPERTY(EditAnywhere, category = "Actor Attributes")
		int32 Gold;

	UPROPERTY(EditAnywhere, category = "Actor Attributes")
		int32 Souls;

	UPROPERTY(EditAnywhere, category = "Actor Attributes")
		float DodgeCost = 14.f;

	UPROPERTY(EditAnywhere, category = "Actor Attributes")
		float StaminaRegenRate = 2.f;


public:
	void AddSouls(int32 NumberOfsoul);
	void AddGold(int32 AmountOfGold);

	FORCEINLINE int32 GetGold() const { return Gold; }
	FORCEINLINE int32 GetSouls() const { return Souls; }
	FORCEINLINE float GetDodgeCost() const { return DodgeCost; }
	FORCEINLINE float GetStamina() const { return Stamina; }
	FORCEINLINE float GetHealth() const { return Health; }
};
