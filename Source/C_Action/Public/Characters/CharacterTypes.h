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

UENUM(BlueprintType)
enum EDeathPose 
{
	EDP_Death1 UMETA(Displayname = "Death1"),
	EDP_Death2 UMETA(Displayname = "Death2"),
	EDP_Death3 UMETA(Displayname = "Death3"),
	EDP_Death4 UMETA(Displayname = "Death4"),
	EDP_Death5 UMETA(Displayname = "Death5"),


	EDP_MAX UMETA(Displayname="DeathMax")
};

UENUM(BlueprintType)
enum class EEenemyState :uint8
{
	EES_Dead UMETA(Displayname = "Dead"),
	EES_Patrolling UMETA(Displayname = "Patrolling"),
	EES_Chasing UMETA(Displayname="Chasing"),
	EES_Attacking UMETA(Displayname="Attacking"),
	EES_Engaged UMETA(Displayname = "Engaged"),

	EES_NoState UMETA(Displayname="NoState")
};