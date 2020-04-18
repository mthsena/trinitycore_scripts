/*                                      //
//                Made by               //
//            _____                     //  
//    __ __  /  |  |   ____ _____       //
//   |  |  \/   |  |__/ __ \\__  \      //
//   |  |  /    ^   /\  ___/ / __ \_    // 
//   |____/\____   |  \___  >____  /    //
//              |__|      \/     \/     // 
//--------------------------------------//

* Made for UnforgivenWoW
* Please give credit where credit is due!
*/

#include "ScriptPCH.h"
#include "ScriptedGossip.h"
#include "Spell.h"

#define ITEM_POS(bag, slot) (bag << 8) | (slot & 255)


class EnchantApplicator : CreatureScript
{
public:
    EnchantApplicator() : CreatureScript("EnchantApplicator2") { }
    SpellInfo const* GetEnchantSpellInfo(uint32 spellId) {
        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
        if(!spellInfo)
            return NULL;
        
        return (spellInfo->Targets & TARGET_FLAG_ITEM) ? spellInfo : NULL;
    }
    
    SpellInfo const* GetEnchantInfo(Item* item) {
        ItemTemplate const* templ = item->GetTemplate();
        if(templ->Spells[0].SpellId == 0 || templ->Spells[0].SpellTrigger != 0) 
            return NULL;
        return GetEnchantSpellInfo(templ->Spells[0].SpellId);
    }
    
    void EnchantApplicatorListEnchants(Player* plr)
    {
        uint8 limit = 0;
        uint8 max = 64;
        
        // pair of slot to the template for name.
        typedef std::pair<uint16, std::string> EnchantInfo;
        
        // template, item guid
        std::map<uint32, EnchantInfo> foundEnchants; // we collect unique item_templates.
        
        // scan over backpack
        for(uint8 i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i) {
            if(Item* item = plr->GetItemByPos(INVENTORY_SLOT_BAG_0, i)) {
                SpellInfo const* spellInfo = GetEnchantInfo(item);
                if(spellInfo && plr->CanUseItem(item) == EQUIP_ERR_OK && foundEnchants.find(spellInfo->Id) == foundEnchants.end()) {
                    foundEnchants[spellInfo->Id] = EnchantInfo(ITEM_POS(INVENTORY_SLOT_BAG_0, i), (std::string)spellInfo->SpellName[0]);
                }
            }
        }
        // scan over bags.
        for (uint8 i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
            if (Bag* pBag = plr->GetBagByPos(i))
                for (uint32 j = 0; j < pBag->GetBagSize(); ++j)
                    if (Item* item = pBag->GetItemByPos(j)) {
                        SpellInfo const* spellInfo = GetEnchantInfo(item);
                        if(spellInfo && plr->CanUseItem(item) == EQUIP_ERR_OK && foundEnchants.find(spellInfo->Id) == foundEnchants.end()) {
                            foundEnchants[spellInfo->Id] = EnchantInfo(ITEM_POS(i, j), (std::string)spellInfo->SpellName[0]);
                        }
                    }
        
        for(std::map<uint32, EnchantInfo>::iterator itr = foundEnchants.begin(); itr != foundEnchants.end() && limit < max; ++itr, limit++) {
            plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, itr->second.second, itr->second.first, 0);
        }
        
        if(limit == 0) {
            plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'll come back when I have enchants in my inventory.", 0, 0);
        } else if(limit < max)
            plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "No thanks!", 0, 0);
    }
    
    bool EnchantApplicatorListTargets(Player* player, Creature* pCreature, uint32 enchant_item_pos) {
        Item* enchant_item = player->GetItemByPos(enchant_item_pos);
        if(!enchant_item)
            return false;
        
        SpellInfo const* spellInfo = GetEnchantInfo(enchant_item);
        if(!spellInfo)
            return false;

        std::string spellName = spellInfo->SpellName[0];
        
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, spellName + " can be applied to...", enchant_item_pos, 0);
        uint8 count = 0;
        for(uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i) {
            if(Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i)) {
                if(item->IsFitToSpellRequirements(spellInfo)) {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, item->GetTemplate()->Name1, enchant_item_pos, ITEM_POS(INVENTORY_SLOT_BAG_0, i));
                    count++;
                }
            }
        }
        if(!count) {
            player->GetSession()->SendNotification("That enchant cannot be applied to any items you have equipped.");
            player->PlayerTalkClass->SendCloseGossip();
        } else {
            player->PlayerTalkClass->SendGossipMenu(100002,pCreature->GetGUID());
        }
        return true;
    }
    
    bool DoEnchantItem(Player* player, uint16 enchant_item_pos, uint32 target_slot) {
        Item* enchant_item = player->GetItemByPos(enchant_item_pos);
        Item* target_item = player->GetItemByPos(target_slot);
        if(!enchant_item || !target_item || !player->IsEquipmentPos(target_slot) || player->CanUseItem(enchant_item) != EQUIP_ERR_OK) {
            sLog->outString("DoEnchantItem error, %u - %u", enchant_item_pos, target_slot);
            return false;
        }
        SpellInfo const* spellInfo = GetEnchantInfo(enchant_item);
        if(spellInfo && target_item->IsFitToSpellRequirements(spellInfo)) {
            SpellCastTargets targets;
            targets.SetItemTarget(target_item);
            player->CastItemUseSpell(enchant_item, targets, 1, 0);
            return true;
        }
        sLog->outString("DoEnchantItem error - spell could not be cast onto item.");
        return false;
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        EnchantApplicatorListEnchants(pPlayer);
        pPlayer->PlayerTalkClass->SendGossipMenu(100001, pCreature->GetGUID());
        return true;
    }
    bool OnGossipSelect(Player* player, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        if(uiSender == 0 && uiAction == 0) {
            // goodbye, heathens!
            player->PlayerTalkClass->SendCloseGossip();

        } else if(uiSender > 0 && uiAction == 0) {
            if(!EnchantApplicatorListTargets(player, pCreature, uiSender)) {
                player->GetSession()->SendNotification("An error has occurred within the Enchant Applicator, please try again.");
                player->PlayerTalkClass->SendCloseGossip();
            }
        } else if(player->IsEquipmentPos(uiAction))
        {
            if(!DoEnchantItem(player, uiSender, uiAction)) {
                player->GetSession()->SendNotification("An error has occurred! We could not enchant that item, please try again.");
            }
            player->PlayerTalkClass->SendCloseGossip();
        }
        return true;
    }
};

uint32 ProfessionEnchantIds[] = {
    // engineering 
    54998, // hand mounted pyro rocket 
    54999, // hyperspeed accelerators
    55016, // nitro boots
    67839, // mind amplification dish
    63765, // springy arachnoweave
    55002, // flexweave underlay
    63770, // reticulated armor webbing
    54793, // frag belt
    // enchanting
    44645, // ring - assault
    44636, // ring - spellpower
    59636, // ring - stamina
    // inscription
    61117, // inscription of the axe
    61118, // inscription of the craig
    61119, // inscription of the pinnacle
    61120, // inscription of the storm
    // leatherworking
    57683, // fur lining - attack power
    57690, // fur lining - stamina
    57691, // fur lining - spell power
    // tailoring
    55777, // swordguard embroidery
    55642, // lightweave embroidery
    55769, // darkglow embroidery
};
class ProfessionEnchantApplicator : public CreatureScript {
public:
    ProfessionEnchantApplicator() : CreatureScript("ProfessionEnchantApplicator") { }
    
    SpellInfo const* GetEnchantSpellInfo(uint32 spellId) {
        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
        if(!spellInfo)
            return NULL;
        
        return (spellInfo->Targets & TARGET_FLAG_ITEM) ? spellInfo : NULL;
    }
    bool HasReagentsFor(Player *plr, SpellInfo const* spellInfo) {
        if(!plr || !spellInfo)
            return false;
        for (uint32 i = 0; i < MAX_SPELL_REAGENTS; ++i) {
            if (spellInfo->Reagent[i] > 0 && spellInfo->ReagentCount[i] > 0) {
                if(!plr->HasItemCount(spellInfo->Reagent[i], spellInfo->ReagentCount[i], false))
                    return false;
            }
        }
        return true;
    }
    
    void EnchantApplicatorListEnchants(Player *plr) {
        uint8 limit = 0;
        uint8 max = 64;
        for(uint32 *spellIdPtr = ProfessionEnchantIds; limit < max && spellIdPtr < ProfessionEnchantIds + sizeof(ProfessionEnchantIds) / sizeof(uint32); spellIdPtr++) {
            if(plr->HasSpell(*spellIdPtr)) {
                if(SpellInfo const* spellInfo = GetEnchantSpellInfo(*spellIdPtr)) {
                    if(HasReagentsFor(plr, spellInfo)) {
                        plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1,(std::string)spellInfo->SpellName[0], spellInfo->Id, 0);
                        limit++;
                    }
                }
            }
        }
        if(limit == 0) {
            plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I'll come back when I know some profession enchants and have the reagents for them in my inventory.", 0, 0);
        } else if(limit < max)
            plr->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "No thanks!", 0, 0);
    }
    
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        EnchantApplicatorListEnchants(pPlayer);
        pPlayer->PlayerTalkClass->SendGossipMenu(100001, pCreature->GetGUID());
        return true;
    }
    
    bool OnGossipSelect(Player* player, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        if(uiSender == 0 && uiAction == 0) {
            // goodbye, heathens!
            player->PlayerTalkClass->SendCloseGossip();

        } else if(uiSender > 0 && uiAction == 0) {
            if(!EnchantApplicatorListTargets(player, pCreature, uiSender)) {
                player->GetSession()->SendNotification("An error has occurred within the Enchant Applicator, please try again.");
                player->PlayerTalkClass->SendCloseGossip();
            }
        } else {
            if(!DoEnchantSpell(player, uiSender, uiAction)) {
                player->GetSession()->SendNotification("An error has occurred! We could not enchant that item, please try again.");
            }
            player->PlayerTalkClass->SendCloseGossip();
        }
        return true;
    }
    
    bool EnchantApplicatorListTargets(Player* player, Creature* pCreature, uint32 spellId) {
        if(!player->HasSpell(spellId))
            return false;
        
        SpellInfo const* spellInfo = GetEnchantSpellInfo(spellId);
        if(!spellInfo)
            return false;

        std::string spellName = spellInfo->SpellName[0];
        
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, spellName + " can be applied to...", spellId, 0);
        uint8 count = 0;
        for(uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i) {
            if(Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i)) {
                if(item->IsFitToSpellRequirements(spellInfo)) {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, item->GetTemplate()->Name1, spellId, ITEM_POS(INVENTORY_SLOT_BAG_0, i));
                    count++;
                }
            }
        }
        if(!count) {
            player->GetSession()->SendNotification("That enchant cannot be applied to any items you have equipped.");
            player->PlayerTalkClass->SendCloseGossip();
        } else {
            player->PlayerTalkClass->SendGossipMenu(100002,pCreature->GetGUID());
        }
        return true;
    }
    
    bool DoEnchantSpell(Player *player, uint32 spellId, uint32 target_slot) {
        Item* target_item = player->GetItemByPos(target_slot);
        if(!target_item || !player->IsEquipmentPos(target_slot) || !player->HasSpell(spellId)) {
            sLog->outString("DoEnchantItem error, %u", target_slot);
            return false;
        }
        SpellInfo const* spellInfo = GetEnchantSpellInfo(spellId);
        if(spellInfo && target_item->IsFitToSpellRequirements(spellInfo) && HasReagentsFor(player, spellInfo)) {
            SpellCastTargets targets;
            targets.SetItemTarget(target_item);
            player->CastSpell(targets, spellInfo, NULL, TRIGGERED_NONE, NULL, NULL, 0);
            return true;
        }
        sLog->outString("DoEnchantItem error - spell could not be cast onto item.");
        return false;
    }
};

/* 
 uint32 h[] = {1, 3, 5};
    for(uint32 *spellIdPtr = h; spellIdPtr < h + sizeof(h) / sizeof(uint32); spellIdPtr++) {
        std::cout << *spellIdPtr << std::endl;
    }
 
 */

void AddSC_EnchantApplicator()
{
    new ProfessionEnchantApplicator();
    new EnchantApplicator();
}

#undef ITEM_POS
