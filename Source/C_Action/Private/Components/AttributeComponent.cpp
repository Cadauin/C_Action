


#include "Components/AttributeComponent.h"


UAttributeComponent::UAttributeComponent()
{

	PrimaryComponentTick.bCanEverTick = false;


}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UAttributeComponent::AddSouls(int32 NumberOfsoul)
{
	Souls += NumberOfsoul;
}

void UAttributeComponent::AddGold(int32 AmountGold)
{
	Gold += AmountGold;
}


// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UAttributeComponent::ReceiveDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0, MaxHealth);
}

void UAttributeComponent::UseStamina(float StaminaCost)
{
	Stamina = FMath::Clamp(Stamina - StaminaCost, 0,MaxStamina);
}

void UAttributeComponent::RegenStamina(float DeltaTime)
{
	Stamina = FMath::Clamp(Stamina + StaminaRegenRate * DeltaTime, 0, MaxStamina);
}

void UAttributeComponent::Resetstate()
{
	Health = MaxHealth;
	Stamina = MaxStamina;
}

float UAttributeComponent::GetHealthPercent()
{
	return Health / MaxHealth;
}

float UAttributeComponent::GetStaminaPercent()
{
	return Stamina/MaxStamina;
}

bool UAttributeComponent::IsAlive()
{
	return Health>0.f;
}

