#include "ScriptedPch.h"
#include <stdio.h>
#include <stdlib.h>

extern DatabaseType CharacterDatabase;

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

bool PayOrBuy(int money, Player *player, Creature *_creature)
{
	if (money < 0)
	{
		if (player->GetMoney() >= -money * 10000)
		{
			player->ModifyMoney(money * 10000);
			_creature->MonsterWhisper("Trade sucessfull.", player->GetGUID(), false);
			return true;
		}
		_creature->MonsterWhisper("I am sorry, but you dont have enough money for that.", player->GetGUID(), false);
	}
	else
	{
		player->ModifyMoney(money * 10000);
		_creature->MonsterWhisper("There are the money of yours!", player->GetGUID(), false);
		return true;
	}

	return false;
}

void ChooseRace(Player *player, Creature *_creature)
{
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
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(GOSSIP_ICON_MONEY_BAG, broken, 
					GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1, "Type in 'SWITCH', without quotes. Race switch is PERMANENT.", 0, true);
			}
		}
		else
		{
			if (player->getGender() == GENDER_MALE && player->getLevel() >= BROKEN_LEVEL)
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(GOSSIP_ICON_MONEY_BAG, broken, 
					GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1, "Type in 'SWITCH', without quotes. Race switch is PERMANENT.", 0, true);
			}
		}

		if (FELORC_ORCONLY)
		{
			if (player->getRace() == RACE_ORC && player->getGender() == GENDER_MALE && player->getLevel() >= FELORC_LEVEL)
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(GOSSIP_ICON_MONEY_BAG, felorc, 
					GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2, "Type in 'SWITCH', without quotes. Race switch is PERMANENT.", 0, true);
			}
		}
		else
		{
			if (player->getGender() == GENDER_MALE && player->getLevel() >= FELORC_LEVEL)
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(GOSSIP_ICON_MONEY_BAG, felorc, 
					GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2, "Type in 'SWITCH', without quotes. Race switch is PERMANENT.", 0, true);
			}
		}

		if (player->getGender() == GENDER_MALE && player->getLevel() >= GOBLIN_LEVEL)
		{
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(GOSSIP_ICON_MONEY_BAG, goblin, 
				GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3, "Type in 'SWITCH', without quotes. Race switch is PERMANENT.", 0, true);
		}
		else if (player->getGender() == GENDER_FEMALE && player->getLevel() >= GOBLIN_LEVEL)
		{
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(GOSSIP_ICON_MONEY_BAG, goblin, 
				GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4, "Type in 'SWITCH', without quotes. Race switch is PERMANENT.", 0, true);
		}

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Good bye.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
		player->SEND_GOSSIP_MENU(14, _creature->GetGUID());
	}
	else
	{
		char brokenm[255];
		sprintf(brokenm, "Buy Broken mount for %ug", BROKEN_MOUNT);

		char felorcm[255];
		sprintf(felorcm, "Buy Fel Orc mount for %ug", FELORC_MOUNT);

		char goblinm[255];
		sprintf(goblinm, "Buy Goblin multi-mount for %ug", GOBLIN_MOUNT);

		QueryResult_AutoPtr result = CharacterDatabase.PQuery("SELECT mount FROM character_overrides WHERE guid = %u", player->GetGUIDLow());
		if(result)
		{
			Field *fields = result->Fetch();
			if (fields[0].GetInt32() == 0)
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(GOSSIP_ICON_MONEY_BAG, "Switch back to my original race", 
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
				player->SEND_GOSSIP_MENU(15, _creature->GetGUID());
			}
			else
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(GOSSIP_ICON_MONEY_BAG, "Switch back to my original race", 
					GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7, 
					"Type in 'SWITCH', to return to your original race. You will get back 1/4 money  and your race mount will be removed.", 0, true);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Sell mount for 1/4 money.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Good bye.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
				player->SEND_GOSSIP_MENU(16, _creature->GetGUID());
			}
		}
	}
}

void WhatNext(Player *player, Creature *_creature)
{
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Lets talk a bit more...", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Good bye.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
	player->SEND_GOSSIP_MENU(18, _creature->GetGUID());
}

bool GossipHello_npc_race_switch(Player *player, Creature *_creature)
{
	ChooseRace(player, _creature);
	return true;
}

void SellMount(Player *player, Creature *_creature, int mount)
{
	switch (mount)
	{
		case GOBLIN_MOUNT_ID:
			if (PayOrBuy(GOBLIN_MOUNT * 0.25, player, _creature))
			{
				player->Unmount();
				player->removeSpell(GOBLIN_MOUNT_ID, false, false);
				CharacterDatabase.PExecute("REPLACE INTO character_overrides (guid, modelOverride, mount) VALUES ('%u', '%u', 0)", 
					player->GetGUIDLow(), player->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID));
			}
			break;
		case FELORC_MOUNT_ID:
			if (PayOrBuy(FELORC_MOUNT * 0.25, player, _creature))
			{
				player->Unmount();
				player->removeSpell(FELORC_MOUNT_ID, false, false);
				CharacterDatabase.PExecute("REPLACE INTO character_overrides (guid, modelOverride, mount) VALUES ('%u', '%u', 0)", 
					player->GetGUIDLow(), player->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID));
			}
			break;
		case BROKEN_MOUNT_ID:
			if (PayOrBuy(BROKEN_MOUNT * 0.25, player, _creature))
			{
				player->Unmount();
				player->removeSpell(BROKEN_MOUNT_ID, false, false);
				CharacterDatabase.PExecute("REPLACE INTO character_overrides (guid, modelOverride, mount) VALUES ('%u', '%u', 0)", 
					player->GetGUIDLow(), player->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID));
			}
			break;
		default:
			break;
	}
	player->SaveToDB();
}

void SellRace(Player *player, Creature *_creature)
{
	switch (player->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID))
	{
		case 21105:
			if (PayOrBuy(BROKEN_PRICE * 0.25, player, _creature))
			{}
			break;
		case 21267:
			if (PayOrBuy(FELORC_PRICE * 0.25, player, _creature))
			{}
			break;
		case 20582:
			if (PayOrBuy(GOBLIN_PRICE * 0.25, player, _creature))
			{}
			break;
		case 20583:
			if (PayOrBuy(GOBLIN_PRICE * 0.25, player, _creature))
			{}
			break;
		default:
			break;
	}
}

bool GossipSelect_npc_race_switch(Player *player, Creature *_creature, uint32 sender, uint32 action )
{
	if (sender != GOSSIP_SENDER_MAIN)
		return false;

	if (action ==  GOSSIP_ACTION_INFO_DEF + 5)
		player->PlayerTalkClass->CloseGossip();
	else if (action == GOSSIP_ACTION_INFO_DEF + 12)
		ChooseRace(player, _creature);

	QueryResult_AutoPtr result = CharacterDatabase.PQuery("SELECT mount FROM character_overrides WHERE guid = %u", player->GetGUIDLow());
	if(result)
	{
		Field *fields = result->Fetch();
		int mount = fields[0].GetInt32();

		switch (action)
		{
			case GOSSIP_ACTION_INFO_DEF + 6:
				SellMount(player, _creature, mount);
				WhatNext(player, _creature);
				break;
			case GOSSIP_ACTION_INFO_DEF + 8:
				if (PayOrBuy(-BROKEN_MOUNT, player, _creature))
				{
					player->Unmount();
					player->learnSpell(BROKEN_MOUNT_ID, false);
					player->CastSpell(player, BROKEN_MOUNT_ID, true);
					CharacterDatabase.PExecute("REPLACE INTO character_overrides (guid, modelOverride, mount) VALUES ('%u', '%u', '%u')", 
						player->GetGUIDLow(), player->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID), BROKEN_MOUNT_ID);
				}

				WhatNext(player, _creature);
				break;
			case GOSSIP_ACTION_INFO_DEF + 9:
				if (PayOrBuy(-FELORC_MOUNT, player, _creature))
				{
					player->Unmount();
					player->learnSpell(FELORC_MOUNT_ID, false);
					player->CastSpell(player, FELORC_MOUNT_ID, true);
					CharacterDatabase.PExecute("REPLACE INTO character_overrides (guid, modelOverride, mount) VALUES ('%u', '%u', '%u')", 
						player->GetGUIDLow(), player->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID), FELORC_MOUNT_ID);
				}

				WhatNext(player, _creature);
				break;
			case GOSSIP_ACTION_INFO_DEF + 10:
				if (PayOrBuy(-GOBLIN_MOUNT, player, _creature))
				{
					player->Unmount();
					player->learnSpell(GOBLIN_MOUNT_ID, false);
					player->CastSpell(player, GOBLIN_MOUNT_ID, true);
					CharacterDatabase.PExecute("REPLACE INTO character_overrides (guid, modelOverride, mount) VALUES ('%u', '%u', '%u')", 
						player->GetGUIDLow(), player->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID), GOBLIN_MOUNT_ID);
				}

				WhatNext(player, _creature);
				break;
			default:
				break;
		}
	}
	
	return true;
}

bool Pay(int money, Player *player, Creature *_creature)
{
	if (player->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID) == player->GetUInt32Value(UNIT_FIELD_DISPLAYID))
	{
		if (player->GetMoney() >= money * 10000)
		{
			player->ModifyMoney(-(money * 10000));
			_creature->MonsterWhisper("Congratulation! Your race have been sucessfully changed!", player->GetGUID(), false);
			return true;
		}
		else
		{
			_creature->MonsterWhisper("You dont have enough money.", player->GetGUID(), false);
			return false;
		}
	}
	else
	{
		_creature->MonsterWhisper("You have to demorph first!", player->GetGUID(), false);
		return false;
	}

}

bool GossipSelectWithCode_npc_race_switch( Player *player, Creature *_creature,
									  uint32 sender, uint32 action, const char* sCode )
{
    if(sender == GOSSIP_SENDER_MAIN)
    {
		int i = -1;
		try
		{
			if (strlen(sCode) + 1 == sizeof "SWITCH")
				i = strcmp("SWITCH", sCode);

		} catch(char *str) {error_db_log(str);}

		if (i == 0)
		{

			if(action == GOSSIP_ACTION_INFO_DEF + 1)   //Draenei male
			{
				if (Pay(BROKEN_PRICE, player, _creature))
				{
					CharacterDatabase.PExecute("REPLACE INTO character_overrides (guid, modelOverride, mount) VALUES ('%u', '%u', 0)", player->GetGUIDLow(), 21105); 
					player->SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID, 21105);
					player->DeMorph();
				}

				ChooseRace(player, _creature);
				return true;
			}
			else if(action == GOSSIP_ACTION_INFO_DEF + 2)   //Fel orc male
			{
				if (Pay(FELORC_PRICE, player, _creature))
				{
					CharacterDatabase.PExecute("REPLACE INTO character_overrides (guid, modelOverride, mount) VALUES ('%u', '%u', 0)", player->GetGUIDLow(), 21267); 
					player->SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID, 21267);
					player->DeMorph();
				}

				WhatNext(player, _creature);
				return true;
			}
			else if(action == GOSSIP_ACTION_INFO_DEF + 3)   //Goblin male
			{
				if (Pay(GOBLIN_PRICE, player, _creature))
				{
					CharacterDatabase.PExecute("REPLACE INTO character_overrides (guid, modelOverride, mount) VALUES ('%u', '%u', 0)", player->GetGUIDLow(), 20582);  
					player->SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID, 20582);
					player->DeMorph();
				}

				WhatNext(player, _creature);
				return true;
			}
			else if(action == GOSSIP_ACTION_INFO_DEF + 4)   //Goblin female
			{
				if (Pay(GOBLIN_PRICE, player, _creature))
				{
					CharacterDatabase.PExecute("REPLACE INTO character_overrides (guid, modelOverride, mount) VALUES ('%u', '%u', 0)", player->GetGUIDLow(), 20583);
					player->SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID, 20583);
					player->DeMorph();
				}

				WhatNext(player, _creature);
				return true;
			}
			else if (action == GOSSIP_ACTION_INFO_DEF + 7)
			{
				QueryResult_AutoPtr result = CharacterDatabase.PQuery("SELECT mount FROM character_overrides WHERE guid = %u", player->GetGUIDLow());
				if(result)
				{
					Field *fields = result->Fetch();
					int mount = fields[0].GetInt32();
					SellMount(player, _creature, mount);
					SellRace(player, _creature);
					CharacterDatabase.PExecute("DELETE FROM character_overrides WHERE guid = '%u'", 
						player->GetGUIDLow());
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Good bye.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
					player->SEND_GOSSIP_MENU(17, _creature->GetGUID());
					return true;
				}
			}
		}
		else
		{
			_creature->MonsterWhisper("Wrong code entered!", player->GetGUID(), false);
		}
    }

	ChooseRace(player, _creature);
	return true;
}

void AddSC_npc_race_switch()
{
	Script *newscript;
	newscript = new Script;
	newscript->Name = "npc_race_switch";
	newscript->pGossipHello = &GossipHello_npc_race_switch;
	newscript->pGossipSelect = &GossipSelect_npc_race_switch;
	newscript->pGossipSelectWithCode =  &GossipSelectWithCode_npc_race_switch;
	newscript->RegisterSelf();
}