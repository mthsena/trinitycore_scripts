/*###################################
#	
#           _____                 
#   __ __  /  |  |   ____ _____   
#  |  |  \/   |  |__/ __ \\__  \  
#  |  |  /    ^   /\  ___/ / __ \_
#  |____/\____   |  \___  >____  /
#             |__|      \/     \/ 
#
#
# ScriptData
# SDName: item_custom_summon
# SD%Complete: 100
# TC%Conversion Complete: 100 by u4ea
# SDComment: Summon multiple NPCs
# SDCategory: Items
# EndScriptData 
# 
# Temporaily summons specified NPC's 
###################################*/

#include "ScriptPCH.h"

// Must declare identifiers
class ItemUse_item_custom_summon : public ItemScript

// Must open main construct
{
    public:

        ItemUse_item_custom_summon()
        // Will be the actual scriptname placed on the item
            : ItemScript("item_custom_summon")
        {
        }
	// Be sure to use OnUse, not ItemUse otherwise you will declare it twice
	bool OnUse(Player* pPlayer, Item* pItem, const SpellCastTargets &pTargets)

	{
  // Do not allow player to use item while in combat, flight, or dead
	if ((pPlayer->isInCombat()) || (pPlayer->isInFlight()) || (pPlayer->isDead()))
	{
      pPlayer->SendEquipError(EQUIP_ERR_NOT_IN_COMBAT, pItem, NULL);
        return false;
	}
	if (pPlayer->IsMounted()) // Is player mounted
	{
      pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, pItem, NULL);
        return true;
	}
	{
	// Summons NPCs to the player at distances that can be set furthermore additional npcs could be spawned.
	// TeleNPC
      pPlayer->SummonCreature(10,pPlayer->GetPositionX()+1 ,pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,120000);
    // Summons Mr. T
	  pPlayer->SummonCreature(32478,pPlayer->GetPositionX()+3 ,pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,120000);
	}
        return false;
	}

	// Make sure wrap your main define
};

// Always use new standards such as GoHello_ ItemUse_ AT_ etc, function links to the scriptname hence ItemUse=function and item_custom_summon=scriptname

void AddSC_item_custom_summon()

{
    new ItemUse_item_custom_summon();
}
