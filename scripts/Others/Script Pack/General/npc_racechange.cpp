/*
  _____                        ____               
 |  ___| __ ___ _______ _ __  / ___|___  _ __ ___ 
 | |_ | '__/ _ \_  / _ \ '_ \| |   / _ \| '__/ _ \
 |  _|| | | (_) / /  __/ | | | |__| (_) | | |  __/
 |_|  |_|  \___/___\___|_| |_|\____\___/|_|  \___|
	 Lightning speed and strength
		 conjured directly from the depths of logic!   
			Infusion-WoW 2011 - 2012 (C)
<--------------------------------------------------------------------------->
 - Developer(s): N/A
 - Complete: N/A
 - ScriptName: '' 
 - Comment: N/A
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"

extern CharacterDatabaseWorkerPool CharacterDatabase;

#define BROKEN_LEVEL			60
#define BROKEN_DRAENEIONLY      true
#define BROKEN_PRICE			5000
#define BROKEN_MOUNT			700
#define BROKEN_MOUNT_ID			75614
#define FELORC_LEVEL			60
#define FELORC_ORCONLY		    true
#define FELORC_PRICE			5000
#define FELORC_MOUNT			700
#define FELORC_MOUNT_ID			72286
#define GOBLIN_LEVEL			1
#define GOBLIN_PRICE			5000
#define GOBLIN_MOUNT			1000
#define GOBLIN_MOUNT_ID			71342

class racechange_global_teleporter : public CreatureScript
{
public:
    racechange_global_teleporter() : CreatureScript("racechange_global_teleporter") { }

    bool OnGossipHello(Player* player, Creature* pCreature)
    {
		player->ADD_GOSSIP_ITEM(9, "Change Race ->", GOSSIP_SENDER_MAIN, 196);
        player->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
        return true;

        if (player->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID) != 21105 && player->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID) && 21267
		&& player->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID) != 20582 && player->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID) != 20583)
	{
		char broken[255];
		sprintf(broken, "Switch race to Broken for %ug", BROKEN_PRICE);

		char felorc[255];
		sprintf(felorc, "Switch race to Fel Orc for %ug", FELORC_PRICE);

		char goblin[255];
		sprintf(goblin, "Switch race to Goblin for %ug", GOBLIN_PRICE);

		if (BROKEN_DRAENEIONLY)
		{
			if (player->getRace() == RACE_DRAENEI && player->getGender() == GENDER_MALE && player->getLevel() >= BROKEN_LEVEL)
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(8, GOSSIP_ICON_MONEY_BAG, broken, 
					GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1, "Type in 'SWITCH', without quotes. Race switch is PERMANENT.", 0, true);
			}
		}
		else
		{
			if (player->getGender() == GENDER_MALE && player->getLevel() >= BROKEN_LEVEL)
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(8, GOSSIP_ICON_MONEY_BAG, broken, 
					GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1, "Type in 'SWITCH', without quotes. Race switch is PERMANENT.", 0, true);
			}
		}

		if (FELORC_ORCONLY)
		{
			if (player->getRace() == RACE_ORC && player->getGender() == GENDER_MALE && player->getLevel() >= FELORC_LEVEL)
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(8, GOSSIP_ICON_MONEY_BAG, felorc, 
					GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2, "Type in 'SWITCH', without quotes. Race switch is PERMANENT.", 0, true);
			}
		}
		else
		{
			if (player->getGender() == GENDER_MALE && player->getLevel() >= FELORC_LEVEL)
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(8, GOSSIP_ICON_MONEY_BAG, felorc, 
					GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2, "Type in 'SWITCH', without quotes. Race switch is PERMANENT.", 0, true);
			}
		}

		if (player->getGender() == GENDER_MALE && player->getLevel() >= GOBLIN_LEVEL)
		{
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(8, GOSSIP_ICON_MONEY_BAG, goblin, 
				GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3, "Type in 'SWITCH', without quotes. Race switch is PERMANENT.", 0, true);
		}
		else if (player->getGender() == GENDER_FEMALE && player->getLevel() >= GOBLIN_LEVEL)
		{
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(8, GOSSIP_ICON_MONEY_BAG, goblin, 
				GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4, "Type in 'SWITCH', without quotes. Race switch is PERMANENT.", 0, true);
		}

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Good bye.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
		player->SEND_GOSSIP_MENU(14, pCreature->GetGUID());
	}
	else
	{
		char brokenm[255];
		sprintf(brokenm, "Buy Broken mount for %ug", BROKEN_MOUNT);

		char felorcm[255];
		sprintf(felorcm, "Buy Fel Orc mount for %ug", FELORC_MOUNT);

		char goblinm[255];
		sprintf(goblinm, "Buy Goblin multi-mount for %ug", GOBLIN_MOUNT);

		QueryResult result = CharacterDatabase.PQuery("SELECT mount FROM character_overrides WHERE guid = %u", player->GetGUIDLow());
		if (!result)
		{
			Field *fields = result->Fetch();
			if (fields[0].GetInt32() == 0)
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(8, GOSSIP_ICON_MONEY_BAG, "Switch back to my original race", 
					GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7, 
					"Type in 'SWITCH', to return to your original race. You will get back 1/4 money.", 0, true);
				switch(player->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID))
				{
					case 21105:
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, brokenm, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
						break;
					case 21267:
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, felorcm, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
						break;
					case 20582:
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, goblinm, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
						break;
					case 20583:
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, goblinm, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
						break;
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Good bye.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
				player->SEND_GOSSIP_MENU(15, pCreature->GetGUID());
			}
			else
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(8, GOSSIP_ICON_MONEY_BAG, "Switch back to my original race", 
					GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7, 
					"Type in 'SWITCH', to return to your original race. You will get back 1/4 money  and your race mount will be removed.", 0, true);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Sell mount for 1/4 money.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Good bye.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
				player->SEND_GOSSIP_MENU(16, pCreature->GetGUID());
			}
		}
	}
}
    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

	if (uiSender != GOSSIP_SENDER_MAIN) { return false; }
        switch (uiAction) {
        case GOSSIP_ACTION_INFO_DEF + 5:
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Lets talk a bit more...", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Good bye.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
	pPlayer->SEND_GOSSIP_MENU(18, pCreature->GetGUID());
	break;
		}
        
        pPlayer->CLOSE_GOSSIP_MENU();
        return true;
	}
};

void AddSC_racechange_global_teleporter()
{
    new racechange_global_teleporter();
}
