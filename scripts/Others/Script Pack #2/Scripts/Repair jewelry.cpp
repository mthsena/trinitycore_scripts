/*
-- Repair jewelry
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `StatsCount`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `ScalingStatDistribution`, `ScalingStatValue`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `delay`, `ammo_type`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `block`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `RequiredDisenchantSkill`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `ScriptName`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `flagsCustom`, `WDBVerified`) VALUES (100000, 0, 0, 0, 'Repair jewelry', 60324, 4, 1, 0, 1, 0, 0, 0, -1, -1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 18282, 0, 0, 0, 8000, 0, -1, 0, 0, NULL, 0, -1, 0, -1, 0, 0, NULL, 0, -1, 0, -1, 0, 0, NULL, 0, -1, 0, -1, 0, 0, NULL, 0, -1, 0, -1, 1, '|cff00FF00Use: You can repair your equipment!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 'item_repair', 0, 0, 0, 0, 0, 1);
-- By vstar0v0
*/

#include "ScriptMgr.h"
#define item_id 100000

class item_repair : public ItemScript
{
public:
	item_repair() : ItemScript("item_repair") {}

	bool OnUse(Player* pPlayer, Item* item, const SpellCastTargets &)
	{
		if (pPlayer->IsInCombat())
		{      
			pPlayer->GetSession()->SendNotification("You can't use this item in combat!");
			return true;
		}
		if (pPlayer->GetBattleground())
		{
			pPlayer->GetSession()->SendNotification("You cannot use this in Battleground!");
			return true;
		}

		if (pPlayer->IsInFlight())
		{
			pPlayer->GetSession()->SendNotification("You cannot use this in Flight!");
			return true;
		}

		if (pPlayer->InArena())
		{
			pPlayer->GetSession()->SendNotification("You cannot use this in an arena match!");
			return true;
		}
		if (pPlayer->isDead())
		{
			pPlayer->GetSession()->SendNotification("You can't use in Dead!");
			return true;
		}
		else
		{
			pPlayer->DurabilityRepairAll(true,0,0);
			pPlayer->GetSession()->SendNotification("Your equipment has been repaired!");
			pPlayer->DestroyItemCount(item_id, 1, true, false);
			return true;
		}
	}
};

void AddSC_item_repair()
{
	new item_repair();
}