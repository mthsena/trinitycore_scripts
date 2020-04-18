/*
    House System v3

    Made by Nathan


*/
#include "ScriptPCH.h"
#include "ObjectMgr.h"

enum eEnums
{
    SAY_NOT_INTERESTED      = -1999922,
    SAY_WRONG               = -1999923,
    SAY_CORRECT             = -1999924,
    PRICE_FOR_LAND			= 15,
    LAND_ITEM_ID			= 35127,
    HOUSE_TOKEN			= 35129,

	PRICE_FOR_P1		= 15,
	PRICE_FOR_P2		= 15,
	PRICE_FOR_P3		= 15,
	PRICE_FOR_P4		= 15,
};

int count = 0;
int selection;

#define	PACKAGE_1  		"PACKAGE1"
#define 	PACKAGE_2  		"PACKAGE2"
#define	PACKAGE_3 		"PACKAGE3"
#define	PACKAGE_4		"PACKAGE4"

bool buyLand(Player* player, Creature* creep, uint32 selection);
bool isLandOwner(uint64 plrName);
int getGoBonus(uint64 plrName);
int getNPCBonus(uint64 plrName);
bool updatePlayerPackage(uint32 AccID, uint32 package);
bool hasPackage(uint32 AccID, uint32 package);
int getLandPrice(uint32 selection);

std::string UInt32ToString2(uint32 integer) {
    std::stringstream out;
    out << integer;
    return out.str();
}

class player_housing_npc : public CreatureScript
{
    public:

        player_housing_npc()
            : CreatureScript("player_housing_npc")
        {
        }
        bool OnGossipHello(Player* player, Creature* creature)
        {
			QueryResult result = CharacterDatabase.PQuery("SELECT id, zone_name, price FROM player_house_available");
			if(result)
			{
				std::string item;
				int idStr[150];
				count = 1;
				selection = 0;
				player->PlayerTalkClass->ClearMenus();
				do{
					Field *fields = result->Fetch();
					idStr[count] = fields[0].GetInt64();
					item = fields[1].GetString();
					uint32 price = fields[2].GetUInt32();
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, item+" Price: "+UInt32ToString2(price)+" Tokens", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+count);
					count++;
				} while (result->NextRow());
			} else {
				ChatHandler(player->GetSession()).PSendSysMessage("No land is available at this time!");
				player->PlayerTalkClass->SendCloseGossip();
			}

			if(!player->HasItemCount(LAND_ITEM_ID, 1, true))
			{
				if(isLandOwner(player->GetGUID())){
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Give me a replacement land item!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+777);
				}
			}
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Not interested.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+10000);
	     player->SaveRecallPosition();
            player->PlayerTalkClass->SendGossipMenu(11110, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
        {
			if (uiAction == GOSSIP_ACTION_INFO_DEF+901)
			{
				player->PlayerTalkClass->SendCloseGossip();
				OnGossipHello(player, creature);
			}

			if (uiAction == GOSSIP_ACTION_INFO_DEF+10000)
			{
				player->PlayerTalkClass->SendCloseGossip();
			}

			if (uiAction == GOSSIP_ACTION_INFO_DEF+777)
			{
				ItemPosCountVec dest;
				if(player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, LAND_ITEM_ID, 1) == EQUIP_ERR_OK)
				{	
					if(player->AddItem(LAND_ITEM_ID, 1)){
					ChatHandler(player->GetSession()).PSendSysMessage("Don't lose it this time!");
					}
				} else {
					ChatHandler(player->GetSession()).PSendSysMessage("Bag is full or other issue!");
				}
			}

			if (uiAction == GOSSIP_ACTION_INFO_DEF+902)
			{
				QueryResult spawnresult;
				spawnresult = CharacterDatabase.PQuery("SELECT map_id, spawn_x, spawn_y, spawn_z, spawn_o FROM player_house_available WHERE id=%u", selection);	
				if(spawnresult)
				{
					Field *fields = spawnresult->Fetch();
					player->TeleportTo(fields[0].GetUInt32(),fields[1].GetFloat(),fields[2].GetFloat(),fields[3].GetFloat(),fields[4].GetFloat());
					return true;
					} else {
					ChatHandler(player->GetSession()).PSendSysMessage("Could not locate your spawn! Please contact a GM!");
				}

			}

			for(int i = 1; i <= count; i++)
			{
				if (uiAction == GOSSIP_ACTION_INFO_DEF+i)
				{
					selection = i;					
					player->PlayerTalkClass->ClearMenus();
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Preview (Teleport to location)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+902);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Go back to other loactions.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+901);
					player->PlayerTalkClass->SendGossipMenu(3, creature->GetGUID());
				}
			}
            return true;
        }
};

class player_housing_npc_guide : public CreatureScript
{
    public:

        player_housing_npc_guide()
            : CreatureScript("player_housing_npc_guide")
        {
        }

	 bool OnGossipHello(Player* player, Creature* creature)
        {
			player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Buy this land!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Take me back!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            		player->PlayerTalkClass->SendGossipMenu(4, creature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			player->PlayerTalkClass->SendCloseGossip();
            if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
            {
				if (player->IsBeingTeleported() || player->isInCombat())			
					return false;	

				player->TeleportTo(player->m_recallMap, player->m_recallX, player->m_recallY, player->m_recallZ, player->m_recallO);
				return true;
            }

	     if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
            {
				player->PlayerTalkClass->SendCloseGossip();
				uint32 selection;
				QueryResult result = CharacterDatabase.PQuery("SELECT id FROM player_house_available WHERE c_guid = '%u'", creature->GetGUIDLow());
				if(result)
				{
					Field *fields = result->Fetch();
					selection = fields[0].GetInt32();
					if(GetOwnerLandCount(player->GetGUID()) < 10){
						buyLand(player, creature, selection);
					} else {
						ChatHandler(player->GetSession()).PSendSysMessage("You can not purchase anymore land!");
						player->PlayerTalkClass->SendCloseGossip();
					}
				} else {
					ChatHandler(player->GetSession()).PSendSysMessage("Failed!");
					player->PlayerTalkClass->SendCloseGossip();
				}

			}

				return true;
		}

		uint32 GetOwnerLandCount(uint32 playerguid)
		{
			QueryResult result = CharacterDatabase.PQuery("SELECT * FROM player_house_taken WHERE player_guid=%u", playerguid);	
			uint32 house_count = 0;
			if(result) 
			{
				while (result->NextRow())
				{
					house_count++;
				} 
			}
			return house_count;
		}
};

class player_housing_packages : public CreatureScript
{
    public:

        player_housing_packages()
            : CreatureScript("player_housing_packages")
        {
        }
					int npcb, gob;
	    bool OnGossipHello(Player* player, Creature* creature)
        {
		
			if(!isLandOwner(player->GetGUID()))
			{
				ChatHandler(player->GetSession()).PSendSysMessage("You do not own any land!");
				player->PlayerTalkClass->SendCloseGossip();
				return false;
			}
			
			char gprice [50];
			char npcprice [50];

			npcb = getNPCBonus(player->GetGUID());
			if(npcb > 0){
				if(npcb >= 200)	
					npcb = 200;
				else
					npcb = npcb+10;
			} else {
				npcb = 10;
			}

			gob = getGoBonus(player->GetGUID());
			if(gob > 0){
				if(gob >= 200)
					gob = 200;
				else
					gob = gob+5;
			} else {
				gob = 10;
			}
			sprintf (npcprice, "+10 NPC Spawn Limit!(%i Tokens)", npcb);
			sprintf (gprice, "+10 GameObject Spawn Limit!(%i Tokens)", gob);

			player->PlayerTalkClass->ClearMenus();
			uint32 accID = player->GetGUIDLow();
			if(!hasPackage(accID, 1) || !hasPackage(accID, 2) || !hasPackage(accID, 3) || !hasPackage(accID, 4))
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Buy Spawn Packages!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Buy More Land!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, npcprice, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, gprice, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            		player->PlayerTalkClass->SendGossipMenu(11111, creature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			uint32 AccID = player->GetGUIDLow();
			switch(uiAction)
			{
			//BUY PACKAGE
			case GOSSIP_ACTION_INFO_DEF+1: 
					player->PlayerTalkClass->ClearMenus();
					if(!hasPackage(AccID, 1))
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, PACKAGE_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+10);
					if(!hasPackage(AccID, 2))
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, PACKAGE_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+11);
					if(!hasPackage(AccID, 3))
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, PACKAGE_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+12);
					if(!hasPackage(AccID, 4))
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, PACKAGE_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+130);
					player->SaveRecallPosition();
					player->PlayerTalkClass->SendGossipMenu(11111, creature->GetGUID());
				break;
			//BUY NPC PACKAGE
			case GOSSIP_ACTION_INFO_DEF+2: 
				ChatHandler(player->GetSession()).PSendSysMessage("This feature is not available yet!");
				player->PlayerTalkClass->SendCloseGossip();
				break;
			
			//+10 NPC SPAWN
			case GOSSIP_ACTION_INFO_DEF+3:
				if(player->HasItemCount(HOUSE_TOKEN, npcb, true)){
					player->DestroyItemCount(HOUSE_TOKEN, npcb, true);
					CharacterDatabase.PExecute("UPDATE player_house SET npcs_bonus = npcs_bonus + 10 WHERE player_guid=%u", player->GetGUID());
					ChatHandler(player->GetSession()).PSendSysMessage("You can now add 10 more NPC's!");
				} else {
					ChatHandler(player->GetSession()).PSendSysMessage("You do not have enough House Tokens to purchase this package!");
				}
				player->PlayerTalkClass->SendCloseGossip();
				break;
			//+10 GO SPAWN
			case GOSSIP_ACTION_INFO_DEF+4:
				if(player->HasItemCount(HOUSE_TOKEN, gob, true)){
					player->DestroyItemCount(HOUSE_TOKEN, gob, true);
					CharacterDatabase.PExecute("UPDATE player_house SET items_bonus = items_bonus + 10 WHERE player_guid=%u", player->GetGUID());
					ChatHandler(player->GetSession()).PSendSysMessage("You can now add 10 more GameObjects!!");
				} else {
					ChatHandler(player->GetSession()).PSendSysMessage("You do not have enough House Tokens to purchase this package!");
				}
				player->PlayerTalkClass->SendCloseGossip();
				break;

			case GOSSIP_ACTION_INFO_DEF+10: 
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Buy Package #1 (15 Tokens)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+13);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Preview Package #1", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+16);
					player->PlayerTalkClass->SendGossipMenu(11111, creature->GetGUID());
				break;
			case GOSSIP_ACTION_INFO_DEF+11: 
				player->PlayerTalkClass->ClearMenus();
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Buy Package #2 (15 Tokens)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+14);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Preview Package #2", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+17);
					player->PlayerTalkClass->SendGossipMenu(11111, creature->GetGUID());
				break;
			case GOSSIP_ACTION_INFO_DEF+12:
				player->PlayerTalkClass->ClearMenus();
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Buy Package #3 (15 Tokens)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+15);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Preview Package #3", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+18);
					player->PlayerTalkClass->SendGossipMenu(11111, creature->GetGUID());
				break;
			case GOSSIP_ACTION_INFO_DEF+130:
				player->PlayerTalkClass->ClearMenus();
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Buy Package #4 (15 Tokens)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+150);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Preview Package #4", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+180);
					player->PlayerTalkClass->SendGossipMenu(11111, creature->GetGUID());
				break;
			
				//buy packages
			case GOSSIP_ACTION_INFO_DEF+13: 
				if(player->HasItemCount(HOUSE_TOKEN, 15, true))
				{
					player->PlayerTalkClass->SendCloseGossip();
					player->DestroyItemCount(HOUSE_TOKEN, PRICE_FOR_P1, true);
					updatePlayerPackage(player->GetGUIDLow(), 1);
					ChatHandler(player->GetSession()).PSendSysMessage("Package #1 bought! A new option will show up on your Land Manager.");
				}else {
					ChatHandler(player->GetSession()).PSendSysMessage("You do not have enough House Tokens to purchase this package!");
				}
				break;
			case GOSSIP_ACTION_INFO_DEF+14: 
				if(player->HasItemCount(HOUSE_TOKEN, 15, true))
				{
					player->PlayerTalkClass->SendCloseGossip();
					player->DestroyItemCount(HOUSE_TOKEN, PRICE_FOR_P2, true);
					updatePlayerPackage(player->GetGUIDLow(), 2);
					ChatHandler(player->GetSession()).PSendSysMessage("Package #2 bought! A new option will show up on your Land Manager.");
				}else {
					ChatHandler(player->GetSession()).PSendSysMessage("You do not have enough House Tokens to purchase this package!");
				}
				break;
			case GOSSIP_ACTION_INFO_DEF+15:
				if(player->HasItemCount(HOUSE_TOKEN, 15, true))
				{
					player->PlayerTalkClass->SendCloseGossip();
					player->DestroyItemCount(HOUSE_TOKEN, PRICE_FOR_P3, true);
					updatePlayerPackage(player->GetGUIDLow(), 3);
					ChatHandler(player->GetSession()).PSendSysMessage("Package #3 bought! A new option will show up on your Land Manager.");
				} else {
					ChatHandler(player->GetSession()).PSendSysMessage("You do not have enough House Tokens to purchase this package!");
				}
				break;
			case GOSSIP_ACTION_INFO_DEF+150:
				if(player->HasItemCount(HOUSE_TOKEN, 15, true))
				{
					player->PlayerTalkClass->SendCloseGossip();
					player->DestroyItemCount(HOUSE_TOKEN, PRICE_FOR_P4, true);
					updatePlayerPackage(player->GetGUIDLow(), 4);
					ChatHandler(player->GetSession()).PSendSysMessage("Package #4 bought! A new option will show up on your Land Manager.");
				} else {
					ChatHandler(player->GetSession()).PSendSysMessage("You do not have enough House Tokens to purchase this package!");
				}
				break;

				//preview packages
			case GOSSIP_ACTION_INFO_DEF+16: 
				if (player->isInCombat())			
					return false;	
				player->TeleportTo(530, -1881.034668f, 5631.024902f, 127.382050f, 4.603881f);
				break;
			case GOSSIP_ACTION_INFO_DEF+17: 
				if (player->isInCombat())			
					return false;	
				player->TeleportTo(530, -1729.365845f, 5612.726562f, 127.946556f, 4.764105f);
				break;
			case GOSSIP_ACTION_INFO_DEF+18: 
				if (player->isInCombat())			
					return false;	
				player->TeleportTo(530, -2003.780518f, 5566.025391f, 53.307026f, 6.0363144f);
				break;
			case GOSSIP_ACTION_INFO_DEF+180: 
				if (player->isInCombat())			
					return false;	
				player->TeleportTo(530, -2213.622070f, 5547.188477f, 112.163513f, 2.822561f);
				break;

			}

				return true;
		}
};

class player_housing_npc_package_guide : public CreatureScript
{
    public:

        player_housing_npc_package_guide()
            : CreatureScript("player_housing_npc_package_guide")
        {
        }

	    bool OnGossipHello(Player* player, Creature* creature)
        {
			player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Take me back!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->PlayerTalkClass->SendGossipMenu(4, creature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			player->PlayerTalkClass->SendCloseGossip();
            if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
            {
				if (player->IsBeingTeleported() || player->isInCombat())			
					return false;	

				player->TeleportTo(player->m_recallMap, player->m_recallX, player->m_recallY, player->m_recallZ, player->m_recallO);
				return true;
            }

			if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
            {
				player->PlayerTalkClass->SendCloseGossip();
				uint32 selection;
				QueryResult result = CharacterDatabase.PQuery("SELECT id FROM player_house_available WHERE c_guid = '%u'", creature->GetGUIDLow());
				if(result)
				{
					Field *fields = result->Fetch();
					uint32 _selection = fields[0].GetInt32();
					if(GetOwnerLandCount(player->GetGUID()) < 10){
						buyLand(player, creature, _selection);
					} else {
						ChatHandler(player->GetSession()).PSendSysMessage("You can not own anymore land!");
					}
				} else {
					ChatHandler(player->GetSession()).PSendSysMessage("Failed!");
				}
				}
				return true;
		}

		uint32 GetOwnerLandCount(uint32 playerguid)
		{
			QueryResult result = CharacterDatabase.PQuery("SELECT * FROM player_house_taken WHERE player_guid=%u", playerguid);	
			uint32 house_count = 0;
			do{
				house_count++;
			} while (result->NextRow());
			return house_count;
		}
};

int getNPCBonus(uint64 plrName)
{
	uint32 npc = 0;
	QueryResult result = CharacterDatabase.PQuery("SELECT npcs_bonus FROM player_house WHERE player_guid = %u", plrName);
	if(result)
	{
		npc = (*result)[0].GetUInt32();
		if (npc < 0)
			return 0;
	} else {
		return 0;
	}
	return npc;
}

bool hasPackage(uint32 AccID, uint32 package)
{
	QueryResult result = CharacterDatabase.PQuery("SELECT * FROM player_house WHERE package%u = 1 AND player_guid = %u", package, AccID);
	if(result)
		return true;
	return false;
}

int getGoBonus(uint64 plrName)
{
	uint32 npc = 0;
	QueryResult result = CharacterDatabase.PQuery("SELECT items_bonus FROM player_house WHERE player_guid = %u", plrName);
	if(result)
	{
		npc = (*result)[0].GetUInt32();
		if (npc < 0)
			return 0;
	} else {
		return 0;
	}
	return npc;
}

bool updatePlayerPackage(uint32 AccID, uint32 package)
{
	CharacterDatabase.PExecute("UPDATE player_house SET package%u=1 WHERE player_guid=%u", package, AccID);
	return true;
}

bool isLandOwner(uint64 name)
{
	QueryResult result = CharacterDatabase.PQuery("SELECT * FROM player_house_taken WHERE player_guid=%u", name);
	if(result)
		return true;
	return false;
}

int getLandPrice(uint32 selection)
{
	uint32 PFL = -1;
	QueryResult result = CharacterDatabase.PQuery("SELECT price FROM player_house_available WHERE id=%u", selection);
	if(result)
		PFL = (*result)[0].GetUInt32();
	return PFL;
}

bool buyLand(Player* player, Creature* creep, uint32 selection)
{
	if(!selection)
		return false;

	uint32 _PFL = getLandPrice(selection);
	if(_PFL < 0)
		return false;

	if(player->HasItemCount(HOUSE_TOKEN, _PFL, true))
	{
		player->DestroyItemCount(HOUSE_TOKEN, _PFL, true);
		QueryResult a_result = CharacterDatabase.PQuery("SELECT zone_name, map_id, bottom_x, top_x, left_y, right_y,"
			//6			7		 8		   9	    10
			"spawn_x, spawn_y, spawn_z, spawn_o, c_guid FROM player_house_available WHERE id=%u", selection);
		if(a_result)
		{
			Field *fields = a_result->Fetch();
																							//   0         1        2        3       4       5        6
			CharacterDatabase.PExecute("INSERT INTO player_house_taken (player_name, player_guid, zone_name, map_id, bottom_x, top_x, left_y, right_y, spawn_x,"
				//  7        8        9
				"spawn_y, spawn_z, spawn_o) VALUES"
					"(\"%s\", %u, \"%s\", %u, %f, %f, %f, %f, %f, %f, %f, %f)",
				player->GetName(), player->GetGUID(), fields[0].GetString().c_str(), fields[1].GetUInt32(), fields[2].GetFloat(), fields[3].GetFloat(),
				fields[4].GetFloat(), fields[5].GetFloat(), fields[6].GetFloat(), fields[7].GetFloat(), fields[8].GetFloat(), fields[9].GetFloat());

			if(!isLandOwner(player->GetGUID()))
			    CharacterDatabase.PExecute("INSERT INTO player_house SET player_guid = %u, player_name = \"%s\"" , player->GetGUIDLow(), player->GetName());

			CharacterDatabase.PExecute("DELETE FROM player_house_available WHERE id = %u", selection);
			if(creep)
			{
				creep->CombatStop();
				creep->DeleteFromDB();
				creep->AddObjectToRemoveList();
			}
			player->CastSpell(player, 55420, false);
			player->AddItem(35127, 1);
			ChatHandler(player->GetSession()).PSendSysMessage("You now have your own land! You have been given a item to access all the custom features!");

			return true;

		} else {
			ChatHandler(player->GetSession()).PSendSysMessage("Your information could not be inserted into the database! Your House Tokens have been refunded!");
			player->AddItem(HOUSE_TOKEN, _PFL);
		}

		ItemPosCountVec dest;
		if(player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, LAND_ITEM_ID, 1) == EQUIP_ERR_OK){

				if(player->AddItem(LAND_ITEM_ID, 1))
				{

				} else {
					ChatHandler(player->GetSession()).PSendSysMessage("Your item to manage your land could not be given to you! Go to the Land Manager to get the House Controller.");
					//CharacterDatabase.PExecute("UPDATE account SET dp = dp + '%u' WHERE id = '%u'", _PFL, player->GetSession()->GetAccountId());
					//return false;
				}
		} else {
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_CANNOT_CREATE, LAND_ITEM_ID, 0);
			ChatHandler(player->GetSession()).PSendSysMessage("You do not have enough room in your inventory! Go to the Land Manager to get the House Controller.");
			return false;
		}
	} else {
		ChatHandler(player->GetSession()).PSendSysMessage("You do not have enough House Tokens to buy any land, this land costs %u House Tokens.", _PFL);
		return false;
	}
	return true;
}

void AddSC_PlayerHousing()
{
    new player_housing_npc();
    new player_housing_npc_guide();
    new player_housing_packages();
    new player_housing_npc_package_guide();
}