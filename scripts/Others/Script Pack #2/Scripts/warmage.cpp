#include "ScriptPCH.h"

class npc_warmage: public CreatureScript
{
public:
    npc_warmage() : CreatureScript("npc_warmage") { }

    bool OnGossipHello(Player* player, Creature *pCreature)
    {
	 if (player->GetTeam() == ALLIANCE)
	 {
	 	player->ADD_GOSSIP_ITEM( 10, "Slay Down the Warchief [RAID]"     , GOSSIP_SENDER_MAIN, 3);
	 }
	 else // Main Menu for Horde
	 {
	 	player->ADD_GOSSIP_ITEM( 10, "Slay Down the King [RAID]"        , GOSSIP_SENDER_MAIN, 4);
	 }
	 player->ADD_GOSSIP_ITEM( 10, "Teleport me to the Battlefield" , GOSSIP_SENDER_MAIN, 1);
	 player->ADD_GOSSIP_ITEM( 10, "Teleport me to the Silver Blade" , GOSSIP_SENDER_MAIN, 2);
	 if (player->HasItemCount(1821, 1, true))
	 {
	 player->ADD_GOSSIP_ITEM( 10, "Valhalas Battle Arena" , GOSSIP_SENDER_MAIN, 5);
	 }
	 player->ADD_GOSSIP_ITEM( 10, "The Throne of the Elements" , GOSSIP_SENDER_MAIN, 6);
	 player->PlayerTalkClass->SendGossipMenu(55005,pCreature->GetGUID());
        return true;
    }

    void SendDefaultMenu(Player* player, Creature* pCreature, uint32 uiAction)
    {
	if (player->isInCombat())
	{
		player->PlayerTalkClass->SendCloseGossip();
		pCreature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
		return;
	}
       if (player->GetMap()->IsBattlegroundOrArena())
       {
              player->PlayerTalkClass->SendCloseGossip();
              pCreature->MonsterSay("You cannot teleport while in battleground or Arena!", LANG_UNIVERSAL, NULL);
              return;
	}

	    switch(uiAction)
	    {

	    case 1: //Alliance Town
            	    player->TeleportTo(571, 3582.155273f, 6627.647949f, 195.171249f, 1.372450f);
		    pCreature->MonsterWhisper("You have been teleported, now go speak with Raelorasz.", player->GetGUID());
		    break;
	    case 2: //Alliance Town
	 	    if (player->HasItemCount(19999, 1, true))
	 	    {
		    pCreature->MonsterWhisper("You have been teleported, now go speak with Talon.", player->GetGUID());
            	    player->TeleportTo(571, 9088.542969f, 1245.036133f, 4.407508f, 5.394810f);
		    } else {
		    pCreature->MonsterWhisper("You require Glasses of the Mist to be in that area.", player->GetGUID());
		    player->PlayerTalkClass->SendCloseGossip();
		    }
		    break;
	    case 3: //Alliance Town
		    pCreature->MonsterWhisper("You have been teleported to Orgrimmar.", player->GetGUID());
            	    player->TeleportTo(1, 1918.543091f, -4433.199707f, 24.809250f, 3.594606f);
		    break;
	    case 4: //Alliance Town
		    pCreature->MonsterWhisper("You have been teleported to Stormwind.", player->GetGUID());
            	    player->TeleportTo(0, -8553.379883f, 597.395020f, 104.599960f, 5.414090f);
		    break;
	    case 5: //Valhalas
		    pCreature->MonsterWhisper("You have been teleported to Valhalas.", player->GetGUID());
            	    player->TeleportTo(571, 8128.030273f, 3440.376953f, 672.371155f, 0.0759106f);
		    break;
	    case 6: //Valhalas
		    pCreature->MonsterWhisper("You have been teleported to the ancient Palace of the Elements.", player->GetGUID());
            	    player->TeleportTo(13, -333.902008f, 18.739201f, 626.979004f, 3.911380f);
		    break;
	    }
	}

    bool OnGossipSelect(Player* player, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
	    player->PlayerTalkClass->ClearMenus();
	    if (uiSender == GOSSIP_SENDER_MAIN)
	    SendDefaultMenu(player, pCreature, uiAction);
	    return true;
    }
};

class npc_tdtele: public CreatureScript
{
public:
    npc_tdtele() : CreatureScript("npc_tdtele") { }

    bool OnGossipHello(Player* player, Creature *pCreature)
    {
	 player->ADD_GOSSIP_ITEM( 10, "Teleport to the Tower Defense!"  , GOSSIP_SENDER_MAIN, 1);
	 player->ADD_GOSSIP_ITEM( 10, "Not right now." , GOSSIP_SENDER_MAIN, 2);
	 player->PlayerTalkClass->SendGossipMenu(55005,pCreature->GetGUID());
        return true;
    }

    void SendDefaultMenu(Player* player, Creature* pCreature, uint32 uiAction)
    {
	if (player->isInCombat())
	{
		player->PlayerTalkClass->SendCloseGossip();
		pCreature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
		return;
	}
       if (player->GetMap()->IsBattlegroundOrArena())
       {
              player->PlayerTalkClass->SendCloseGossip();
              pCreature->MonsterSay("You cannot teleport while in battleground or Arena!", LANG_UNIVERSAL, NULL);
              return;
	}

	    switch(uiAction)
	    {

	    case 1: //Alliance Town
            	    player->TeleportTo(429, -18.296444f, 472.577820f, -23.303589f, 0.056212f);
		    break;
	    case 2: //Alliance Town
            	    player->PlayerTalkClass->SendCloseGossip();
		    pCreature->MonsterWhisper("Come back anytime when you wish to play!", player->GetGUID());
		    break;
	    }
	}

    bool OnGossipSelect(Player* player, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
	    player->PlayerTalkClass->ClearMenus();
	    if (uiSender == GOSSIP_SENDER_MAIN)
	    SendDefaultMenu(player, pCreature, uiAction);
	    return true;
    }

};

void AddSC_npc_warmage()
{
    new npc_tdtele();
    new npc_warmage();
}