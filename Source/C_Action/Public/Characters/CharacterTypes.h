#pragma once
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_UnEquip UMETA(DisPlayName = "UnEquip"),
	ECS_EquippedOneHandWeapon UMETA(DisPlayName = "Equipped One-Hand WeaponUMETA"),
	ECS_EquippedTwoHandWeapon UMETA(DisPlayName = "Equipped Two-Hand WeaponUMETA")
};

UENUM(BlueprintType)
enum class EActionState:uint8
{
	EAS_Unoccupied UMETA(Displayname="Unoccupied"),
	EAS_Attacking UMETA(Displayname="Attacking"),
	EAS_EquippingWeapon UMETA(Displayname="Equipping Weapon")
};