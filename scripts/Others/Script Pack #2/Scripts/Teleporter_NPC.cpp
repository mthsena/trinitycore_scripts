#include "ScriptPCH.h"

class Teleporter_NPC : public CreatureScript
{
public:
    Teleporter_NPC() : CreatureScript("Teleporter_NPC") { }
    
    bool OnGossipHello(Player * player, Creature * creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface/ICONS/INV_Misc_Coin_01:30|t Sanctuary Mall.", GOSSIP_SENDER_MAIN, 1);
        switch (player->GetTeam())
        {
        case HORDE:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface/ICONS/INV_BannerPVP_01:30|t Faction Malls.", GOSSIP_SENDER_MAIN, 2);
            break;
        case ALLIANCE:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface/ICONS/INV_BannerPVP_02:30|t Faction Malls.", GOSSIP_SENDER_MAIN, 2);
            break;
        }
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Arena_2v2_7:30|t PvP Arenas.", GOSSIP_SENDER_MAIN, 3);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Arena_3v3_5:30|t Duel Zone", GOSSIP_SENDER_MAIN, 4);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Arena_3v3_5:30|t World Boss", GOSSIP_SENDER_MAIN, 134);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/INV_MISC_FILM_01:30|t Event Zone.", GOSSIP_SENDER_MAIN, 9);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Quests_Completed_08:30|t Questing Zone.", GOSSIP_SENDER_MAIN, 5);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "|TInterface/ICONS/INV_Misc_Gear_01:30|t Profession Mall.", GOSSIP_SENDER_MAIN, 6);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "|TInterface/ICONS/INV_Chest_Plate13:30|t Transmorgrification Mall.", GOSSIP_SENDER_MAIN, 7);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "|TInterface/ICONS/Achievement_Dungeon_Icecrown_IcecrownEntrance:30|t Icecrown Citadel.", GOSSIP_SENDER_MAIN, 8);
        player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
        return true;
    }
    
    bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        
        switch(uiAction)
        {
        case 1: // Global Mall
            player->TeleportTo(530, -2981.270020f, 779.124023f, -8.054820f, 2.530470f);
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            player->PlayerTalkClass->SendCloseGossip();
            break;
        
        case 134: // World Boss
            player->TeleportTo(0, -7627.41f, -708.915f, 183.457f, 4.95638f);
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            player->PlayerTalkClass->SendCloseGossip();
            break;
        
        case 2: // Malls
            if (player->GetTeam() == HORDE)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface/ICONS/INV_Misc_Coin_05:30|t Orgrimmar", GOSSIP_SENDER_MAIN, 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface/ICONS/INV_Misc_Coin_05:30|t Undercity", GOSSIP_SENDER_MAIN, 12);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:30|t Back", GOSSIP_SENDER_MAIN, 20);
                player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
            }
            else
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface/ICONS/INV_Misc_Coin_05:30|t Stormwind", GOSSIP_SENDER_MAIN, 13);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface/ICONS/INV_Misc_Coin_05:30|t Ironforge", GOSSIP_SENDER_MAIN, 14);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:30|t Back", GOSSIP_SENDER_MAIN, 20);
                player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
            }
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 3: // PvP Arenas
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Arena_2v2_3:30|t Gurubashi Arena", GOSSIP_SENDER_MAIN, 15);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Arena_2v2_3:30|t Dire Maul Arena", GOSSIP_SENDER_MAIN, 16);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:30|t Back", GOSSIP_SENDER_MAIN, 20);
            player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 4: // duelzone
            player->TeleportTo(0, 4300.189941f, -2761.300049f, 16.813999f, 3.643650f);
            player->PlayerTalkClass->SendCloseGossip();
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 5: // Questing Zone.
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Arena_2v2_3:30|t Northwatch Hold", GOSSIP_SENDER_MAIN, 17);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Arena_2v2_3:30|t Supreme", GOSSIP_SENDER_MAIN, 18);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Arena_2v2_3:30|t Mulgore", GOSSIP_SENDER_MAIN, 19);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:30|t Back", GOSSIP_SENDER_MAIN, 20);
            player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 6: // prifessions mall
            player->TeleportTo(0, -219.182281f, 1638.179443f, 79.765350f, 1.288978f);
            player->PlayerTalkClass->SendCloseGossip();
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 7: // mog mall
            player->TeleportTo(1, -2650.709961f, -5021.879883f, 21.182899f, 2.431570f);
            player->PlayerTalkClass->SendCloseGossip();
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 8: // ICC
            player->TeleportTo(571, 5873.82f, 2110.98f, 636.011f, 3.5523f);
            player->PlayerTalkClass->SendCloseGossip();
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 9: // event zone
            player->TeleportTo(1, -11841.861328f, -4757.439941f, 6.225769f, 0.398504f);
            player->PlayerTalkClass->SendCloseGossip();
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 11: // org
            player->TeleportTo(1, 1462.180054f, -4419.850098f, 25.463112f, 0.109132f);
            player->PlayerTalkClass->SendCloseGossip();
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 12: // undercity
            player->TeleportTo(0, 1745.290039f, 239.115997f, 61.920300f, 6.248010f);
            player->PlayerTalkClass->SendCloseGossip();
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 13: // stormwind
            player->TeleportTo(0, -8847.259766f, 606.219971f, 92.426201f, 0.757473f);
            player->PlayerTalkClass->SendCloseGossip();
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 14: // ironforge
            player->TeleportTo(0, -4936.500000f, -937.025024f, 503.040985f, 5.440750f);
            player->PlayerTalkClass->SendCloseGossip();
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 15: // guru
            player->TeleportTo(0, -13245.921875f, 193.394821f, 31.008369f, 1.096788f);
            player->PlayerTalkClass->SendCloseGossip();
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 16: // dire maul
            player->TeleportTo(1, -3761.399658f, 1133.067749f, 132.084564f, 4.719074f);
            player->PlayerTalkClass->SendCloseGossip();
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 17: // northwatch hold
            player->TeleportTo(1, -1998.12f, -3680.54f, 21.1346f, 2.45298f);
            player->PlayerTalkClass->SendCloseGossip();
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 18: // supreme
            player->TeleportTo(0, -1852.07f, -4251.95f, 2.76502f, 1.08637f);
            player->PlayerTalkClass->SendCloseGossip();
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 19: // mulgore
            player->TeleportTo(1, -2203.916992f, -699.970459f, -10.450468f, 0.375297f);
            player->PlayerTalkClass->SendCloseGossip();
			player->Dismount();
			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
            break;
        
        case 20: // bk
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface/ICONS/INV_Misc_Coin_01:30|t Sanctuary Mall.", GOSSIP_SENDER_MAIN, 1);
            switch (player->GetTeam())
            {
            case HORDE:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface/ICONS/INV_BannerPVP_01:30|t Faction Malls.", GOSSIP_SENDER_MAIN, 2);
                break;
            case ALLIANCE:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface/ICONS/INV_BannerPVP_02:30|t Faction Malls.", GOSSIP_SENDER_MAIN, 2);
                break;
            }
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Arena_2v2_7:30|t PvP Arenas.", GOSSIP_SENDER_MAIN, 3);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Arena_3v3_5:30|t Duel Zone", GOSSIP_SENDER_MAIN, 4);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Arena_3v3_5:30|t World Boss", GOSSIP_SENDER_MAIN, 134);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/INV_MISC_FILM_01:30|t Event Zone.", GOSSIP_SENDER_MAIN, 9);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "|TInterface/ICONS/Achievement_Quests_Completed_08:30|t Questing Zone.", GOSSIP_SENDER_MAIN, 5);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "|TInterface/ICONS/INV_Misc_Gear_01:30|t Profession Mall.", GOSSIP_SENDER_MAIN, 6);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "|TInterface/ICONS/INV_Chest_Plate13:30|t Transmorgrification Mall.", GOSSIP_SENDER_MAIN, 7);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TABARD, "|TInterface/ICONS/Achievement_Dungeon_Icecrown_IcecrownEntrance:30|t Icecrown Citadel.", GOSSIP_SENDER_MAIN, 8);
            player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
            break;
        }
    return true;
    }
};
     
void AddSC_Teleporter_NPC()
{
    new Teleporter_NPC;
}