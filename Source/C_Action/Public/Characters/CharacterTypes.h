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
	EAS_HitReaction UMETA(Displayname="HitReaction"),
	EAS_Attacking UMETA(Displayname="Attacking"),
	EAS_EquippingWeapon UMETA(Displayname = "Equipping Weapon"),
	EAS_Assassination UMETA(Displayname = "Assassination"),
	EAS_Dodge UMETA(Displayname = "Dodge"),
	EAS_Dash UMETA(Displayname = "Dash"),
	EAS_Dead UMETA(Displayname = "Dead")
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
{EES_NoState UMETA(Displayname="NoState"),
	EES_Dead UMETA(Displayname = "Dead"),
	EES_Patrolling UMETA(Displayname = "Patrolling"),
	EES_Chasing UMETA(Displayname="Chasing"),
	EES_Assassinated UMETA(Displayname = "Assassinated"),
	EES_Attacking UMETA(Displayname="Attacking"),
	EES_Engaged UMETA(Displayname = "Engaged")

	
};

UENUM(BlueprintType)
enum class EEnemyType :uint8 
{
	EET_Human UMETA(Displayname="Human"),
	EET_Monster UMETA(Displayname="Monster")

};

UENUM(BlueprintType)
enum class EBossState :uint8
{
	EBS_NoState UMETA(Displayname="Nostate"),
	EBS_Dead UMETA(Displayname="Dead"),
	EBS_Engaged UMETA(Displayname = "Engaged"),
	EBS_Stun UMETA(Displayname="Stun")
};

