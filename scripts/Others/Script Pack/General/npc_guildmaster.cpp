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
#include <cstring>
#include "GuildMgr.h"

const uint32 GUILD_TOKEN = 30;
bool requiresGUpdate = true;
std::vector<uint64> GuildHouses;
char string[200];

enum Objects
{
	OBJECT_TABLE        = 180698,
	OBJECT_TORCH        = 187988,
	OBJECT_MAILBOX      = 142094,
	OBJECT_CRATE        = 183992,
	OBJECT_A_FLAG       = 187342,
	OBJECT_H_FLAG       = 192688,
	OBJECT_CHAIR        = 10201,
	OBJECT_FIREPIT      = 1967,
	OBJECT_GUILDVAULT   = 187390,
	OBJECT_BARBER_CHAIR = 191817,
	OBJECT_CRANBERRY_BUSH = 195199,
};

void SpawnObject(Player * pPlayer, uint32 objectId)
{
	const GameObjectTemplate* objectInfo = sObjectMgr->GetGameObjectTemplate(objectId);
	
	float x = float(pPlayer->GetPositionX());
	float y = float(pPlayer->GetPositionY());
	float z = float(pPlayer->GetPositionZ());
	float o = float(pPlayer->GetOrientation());
	Map* map = pPlayer->GetMap();

	GameObject* object = new GameObject;
	uint32 guidLow = sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT);
	
	if (!object->Create(guidLow, objectInfo->entry, map, pPlayer->GetPhaseMaskForSpawn(), x, y, z, o, 0.0f, 0.0f, 0.0f, 0.0f, 0, GO_STATE_READY))
	{
		delete object;
		return;
	}
	
	object->SetRespawnTime(1);
	object->SaveToDB(map->GetId(), (1 << map->GetSpawnMode()), pPlayer->GetPhaseMaskForSpawn());
	
	if (!object->LoadGameObjectFromDB(guidLow, map))
	{
		delete object;
		return;
	}
	
	sObjectMgr->AddGameobjectToGrid(guidLow, sObjectMgr->GetGOData(guidLow));
	WorldDatabase.PExecute("INSERT INTO guildhouse_objects VALUES('%u', '%u')", pPlayer->GetGuildId(), guidLow);
}

uint32 getGuildAreaId(Player * pPlayer)
{
	QueryResult Result = WorldDatabase.PQuery("SELECT area FROM guildhouses WHERE guildId='%u'", pPlayer->GetGuildId());
	if(Result)
	{
		Field * pField = Result->Fetch();
		return pField[0].GetUInt32();
	}

	return -1;

}

bool isInGuildArea(Player * pPlayer)
{
	for(int i = 0; i < 21; i++)
	{
		if(pPlayer->GetAreaId() == getGuildAreaId(pPlayer))
			return true;
	}
	return false;
}

bool isGuildHouseOwner(Player * pPlayer)
{
	if(GuildHouses.empty() || requiresGUpdate == true)
	{
		if(requiresGUpdate == true)
		{
			GuildHouses.clear();
			requiresGUpdate = false;
		}
		QueryResult Result = WorldDatabase.PQuery("SELECT guildId FROM guildhouses WHERE guildId != '0'");
		if(Result)
		{
			Field * pFields = Result->Fetch();
			int i = 0;
			do
			{
				GuildHouses.push_back(pFields[0].GetUInt64());
				i++;
			}while(Result->NextRow());
			
			return isGuildHouseOwner(pPlayer);
		}
		else
		{
			return false;
		}
	}
	else
	{
		for(std::vector<uint64>::iterator itr = GuildHouses.begin(); itr != GuildHouses.end(); itr++)
		{
			if(*itr != pPlayer->GetGuildId())
				continue;
			else
				return true;
		}
		return false;
	}
}

bool isPlayerGuildLeader(Player *player)
{
	return (player->GetRank() == 0) && (player->GetGuildId() != 0);
}

bool GuildOwnsHouse(Player * pPlayer)
{
	QueryResult pResult = WorldDatabase.PQuery("SELECT * FROM guildhouses WHERE guildId='%u'", pPlayer->GetGuildId());
	if(!pResult)
		return false;
	else
		return true;
}

void CleanUpObjects(Player * pPlayer, uint32 guildId)
{
	QueryResult ObjectSpawns = WorldDatabase.PQuery("SELECT	`guid` FROM `guildhouse_objects` WHERE `guildId` = '%u'", guildId);
	if(ObjectSpawns)
	{
		do
		{
			Field * pField = ObjectSpawns->Fetch();
			uint32 Object_GUID = pField[0].GetUInt32();
			GameObject* object = NULL;
			ChatHandler handler(pPlayer->GetSession());

			if (GameObjectData const* gameObjectData = sObjectMgr->GetGOData(Object_GUID))
				object = handler.GetObjectGlobalyWithGuidOrNearWithDbGuid(Object_GUID, gameObjectData->id);

			if (!object)
				continue;

			object->SetRespawnTime(0);
			object->Delete();
			object->DeleteFromDB();
			WorldDatabase.PExecute("DELETE FROM `guildhouse_objects` WHERE guid='%u'", Object_GUID);
		}while(ObjectSpawns->NextRow());
	}
}

void SellGuildHouse(Player * pPlayer, Creature * pCreature)
{
	if(isInGuildArea(pPlayer))
	{
		WorldDatabase.PExecute("UPDATE `guildhouses` SET `guildId`='0' WHERE `guildId`='%u'", pPlayer->GetGuildId());
		CleanUpObjects(pPlayer, pPlayer->GetGuildId());
		pCreature->MonsterSay("You have successfully sold your guild house!", LANG_UNIVERSAL, pPlayer->GetGUID());
		pPlayer->PlayerTalkClass->SendCloseGossip();
		requiresGUpdate = true;
		pPlayer->TeleportTo(530, -1861.239990f, 5437.810059f, -10.463400f, 1.353830f); // generally the mall
	}
	else
	{
		pPlayer->GetSession()->SendNotification("You must be in your guild house to sell it!");
	}
}

void PurchaseGuildHouse(Player * pPlayer, Creature * pCreature, uint32 &Id)
{
	if(pPlayer->HasItemCount(GUILD_TOKEN, 1))
	{
		WorldDatabase.PExecute("UPDATE `guildhouses` SET `guildId`='%u' WHERE `id`='%u'", pPlayer->GetGuildId(), Id);
		pCreature->MonsterSay("Congratulations on the purchase of your new guild house!", LANG_UNIVERSAL, pPlayer->GetGUID());
		pPlayer->DestroyItemCount(GUILD_TOKEN, 1, true);
		requiresGUpdate = true;
	}
	else
	{
		pCreature->MonsterSay("You need a guild token to purchase a guild house!", LANG_UNIVERSAL, pPlayer->GetGUID());
	}
		pPlayer->PlayerTalkClass->SendCloseGossip();
}

void TeleportToHouse(Player * pPlayer)
{
	if(pPlayer->isInCombat())
		return;

	QueryResult result = WorldDatabase.PQuery("SELECT `x`, `y`, `z`, `map` FROM `guildhouses` WHERE `guildId` = '%u'", pPlayer->GetGuildId());
	if (result)
	{
		Field *fields = result->Fetch();
		float x = fields[0].GetFloat();
		float y = fields[1].GetFloat();
		float z = fields[2].GetFloat();
		uint32 map = fields[3].GetUInt32();
		pPlayer->TeleportTo(map, x, y, z, pPlayer->GetOrientation());
	}
}

class GuildHouse_NPC : public CreatureScript
{
	public:
		GuildHouse_NPC() : CreatureScript("GuildHouse"){}


		void ShowHouseListings(Player * pPlayer, Creature * pCreature, unsigned int start = 0)
		{
			pPlayer->PlayerTalkClass->ClearMenus();

			QueryResult pResult = WorldDatabase.PQuery("SELECT id, comment FROM guildhouses WHERE guildId='0'");
			uint32 houses = pResult->GetRowCount();
			int offset = 0;
			Field * pField = pResult->Fetch();
			bool ranOnce = false;
			for(unsigned int i = start; i < houses; i++)
			{
				if(start != 0 && ranOnce == false)
				{
					for(size_t x = 0; x < start; x++)
					{
						pResult->NextRow();
					}
					ranOnce = true;
				}

				if(offset != 10)
				{
					pPlayer->ADD_GOSSIP_ITEM(6, pField[1].GetString(), GOSSIP_SENDER_MAIN, pField[0].GetUInt32());
					offset++;
					pResult->NextRow();
				}
				else
				{
					if((startid + 12) > houses)
					{
						pPlayer->ADD_GOSSIP_ITEM(7, "-------------END--------------", GOSSIP_SENDER_MAIN, 41);
					}
					else
					{
						pPlayer->ADD_GOSSIP_ITEM(7, "Next Page", GOSSIP_SENDER_MAIN, 4353);
						startid = start + offset;
						i = houses +10;
					}
				}
			}
			pPlayer->PlayerTalkClass->SendGossipMenu(2, pCreature->GetGUID());
		}
		
		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			startid = 0;

			if(pPlayer->GetGuildId() == 0)
			{
				pPlayer->GetSession()->SendNotification("You must be in a guild!");
				return false;
			}
			else if (!GuildOwnsHouse(pPlayer) && !isPlayerGuildLeader(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("Your guild does not own a house!");
				return false;
			}
			pPlayer->ADD_GOSSIP_ITEM(4, "Guild Housing System:", GOSSIP_SENDER_MAIN, 41);
			pPlayer->ADD_GOSSIP_ITEM(4, "----------------------------------------------", GOSSIP_SENDER_MAIN, 41);
			if(isPlayerGuildLeader(pPlayer))
			{
				if(!GuildOwnsHouse(pPlayer))
					pPlayer->ADD_GOSSIP_ITEM(6, "Buy a Guild House", GOSSIP_SENDER_MAIN, 38);
				else
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED(6, "Sell Guild House", GOSSIP_SENDER_MAIN, 39, "Are you sure you want to sell your guild house?", 0, false);
			}
			if(GuildOwnsHouse(pPlayer))
				pPlayer->ADD_GOSSIP_ITEM(7, "Teleport to Guild House", GOSSIP_SENDER_MAIN, 40);
			pPlayer->PlayerTalkClass->SendGossipMenu(2, pCreature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player * pPlayer, Creature * pCreature, uint32 /*uiSender*/, uint32 uiAction)
		{
			pPlayer->PlayerTalkClass->ClearMenus();

			switch(uiAction)
			{
				case 38:
					ShowHouseListings(pPlayer, pCreature);
					break;
				case 39:
					SellGuildHouse(pPlayer, pCreature);
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				case 40:
					TeleportToHouse(pPlayer);
					break;
				case 41:
					OnGossipHello(pPlayer, pCreature);
					break;
				case 4353:
					ShowHouseListings(pPlayer, pCreature, startid);
					break;
				default:
					if(uiAction < 38 && uiAction > 0)
						PurchaseGuildHouse(pPlayer, pCreature, uiAction);
					break;
			}
			return true;
		}

		private:
			uint32 startid;
};


class Table_Token : public ItemScript
{
	public:
		Table_Token() : ItemScript("Table Token"){}

		bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
		{
			if(!pPlayer)
				return false;

			if(!pItem)
				return false;

			if(!isPlayerGuildLeader(pPlayer) || !isGuildHouseOwner(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You must own a guild house to use this item!");
				return false;
			}

			if(!isInGuildArea(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You are not in your guild area!");
				return false;
			}

			SpawnObject(pPlayer, OBJECT_TABLE);
			pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true);
			return true;
		}
};

class Torch_Token : public ItemScript
{
	public:
		Torch_Token() : ItemScript("Torch Token"){}

		bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
		{
			if(!pPlayer)
				return false;
			
			if(!pItem)
				return false;

			if(!isPlayerGuildLeader(pPlayer) || !isGuildHouseOwner(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You must own a guild house to use this item!");
				return false;
			}

			if(!isInGuildArea(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You are not in your guild area!");
				return false;
			}

			SpawnObject(pPlayer, OBJECT_TORCH);
			pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true);
			
			return true;
		}
};

class Mailbox_Token : public ItemScript
{
	public:
		Mailbox_Token() : ItemScript("Mailbox Token"){}

		bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
		{
			if(!pPlayer)
				return false;

			if(!pItem)
				return false;

			if(!isPlayerGuildLeader(pPlayer) || !isGuildHouseOwner(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You must own a guild house to use this item!");
				return false;
			}

			if(!isInGuildArea(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You are not in your guild area!");
				return false;
			}

			SpawnObject(pPlayer, OBJECT_MAILBOX);
			pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true);

			return true;
		}
};

class Crate_Token : public ItemScript
{
	public:
		Crate_Token() : ItemScript("Crate Token"){}

		bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
		{
			if(!pPlayer)
				return false;

			if(!pItem)
				return false;

			if(!isPlayerGuildLeader(pPlayer) || !isGuildHouseOwner(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You must own a guild house to use this item!");
				return false;
			}

			if(!isInGuildArea(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You are not in your guild area!");
				return false;
			}

			SpawnObject(pPlayer, OBJECT_CRATE);
			pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true);

			return true;
		}
};

class A_Flag_Token : public ItemScript
{
	public:
		A_Flag_Token() : ItemScript("A_Flag Token"){}

		bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
		{
			if(!pPlayer)
				return false;

			if(!pItem)
				return false;

			if(!isPlayerGuildLeader(pPlayer) || !isGuildHouseOwner(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You must own a guild house to use this item!");
				return false;
			}

			if(!isInGuildArea(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You are not in your guild area!");
				return false;
			}

			SpawnObject(pPlayer, OBJECT_A_FLAG);
			pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true);

			return true;
		}
};

class H_Flag_Token : public ItemScript
{
	public:
		H_Flag_Token() : ItemScript("H_Flag Token"){}

		bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
		{
			if(!pPlayer)
				return false;

			if(!pItem)
				return false;

			if(!isPlayerGuildLeader(pPlayer) || !isGuildHouseOwner(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You must own a guild house to use this item!");
				return false;
			}

			if(!isInGuildArea(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You are not in your guild area!");
				return false;
			}


			SpawnObject(pPlayer, OBJECT_H_FLAG);
			pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true);

			return true;
		}
};

class Chair_Token : public ItemScript
{
	public:
		Chair_Token() : ItemScript("Chair Token"){}

		bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
		{
			if(!pPlayer)
				return false;

			if(!pItem)
				return false;

			if(!isPlayerGuildLeader(pPlayer) || !isGuildHouseOwner(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You must own a guild house to use this item!");
				return false;
			}

			if(!isInGuildArea(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You are not in your guild area!");
				return false;
			}

			SpawnObject(pPlayer, OBJECT_CHAIR);
			pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true);

			return true;
		}
};

class Firepit_Token : public ItemScript
{
	public:
		Firepit_Token() : ItemScript("Firepit Token"){}

		bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
		{
			if(!pPlayer)
				return false;

			if(!pItem)
				return false;

			if(!isPlayerGuildLeader(pPlayer) || !isGuildHouseOwner(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You must own a guild house to use this item!");
				return false;
			}

			if(!isInGuildArea(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You are not in your guild area!");
				return false;
			}

			SpawnObject(pPlayer, OBJECT_FIREPIT);
			pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true);

			return true;
		}
};

class Vault_Token : public ItemScript
{
	public:
		Vault_Token() : ItemScript("Vault Token"){}

		bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
		{
			if(!pPlayer)
				return false;

			if(!pItem)
				return false;

			if(!isPlayerGuildLeader(pPlayer) || !isGuildHouseOwner(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You must own a guild house to use this item!");
				return false;
			}

			if(!isInGuildArea(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You are not in your guild area!");
				return false;
			}

			SpawnObject(pPlayer, OBJECT_GUILDVAULT);
			pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true);

			return true;
		}
};

class Barber_Token : public ItemScript
{
	public:
		Barber_Token() : ItemScript("Barber Token"){}

		bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
		{
			if(!pPlayer)
				return false;

			if(!pItem)
				return false;

			if(!isPlayerGuildLeader(pPlayer) || !isGuildHouseOwner(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You must own a guild house to use this item!");
				return false;
			}

			if(!isInGuildArea(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You are not in your guild area!");
				return false;
			}

			SpawnObject(pPlayer, OBJECT_BARBER_CHAIR);
			pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true);
			
			return true;
		}
};

class Cranberry_Token : public ItemScript
{
	public:
		Cranberry_Token() : ItemScript("Cranberry Token"){}

		bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
		{
			if(!pPlayer)
				return false;

			if(!pItem)
				return false;

			if(!isPlayerGuildLeader(pPlayer) || !isGuildHouseOwner(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You must own a guild house to use this item!");
				return false;
			};

			if(!isInGuildArea(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You are not in your guild area!");
				return false;
			}

			SpawnObject(pPlayer, OBJECT_CRANBERRY_BUSH);
			pPlayer->DestroyItemCount(pItem->GetEntry(), 1, true);

			return true;
		}
};

//token vendor

class Guild_Token_Vendor : public CreatureScript
{
	public:
		Guild_Token_Vendor() : CreatureScript("Token Vendor"){}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			if(!isPlayerGuildLeader(pPlayer))
			{
				pPlayer->GetSession()->SendNotification("You must be a guildmaster!");
				pPlayer->PlayerTalkClass->SendCloseGossip();
				return false;
			}
			if(isGuildHouseOwner(pPlayer))
			{
				pPlayer->PlayerTalkClass->ClearMenus();
				pPlayer->ADD_GOSSIP_ITEM(4, "I would like to purchase Object Tokens!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
				pPlayer->ADD_GOSSIP_ITEM(3, "Nevermind.", GOSSIP_SENDER_MAIN, 2);
				pPlayer->PlayerTalkClass->SendGossipMenu(2, pCreature->GetGUID());
				//return true;
			}
			else
			{
				pPlayer->GetSession()->SendNotification("You must own a guild house!");
				return false;
			}
			return true;
		}

		bool OnGossipSelect(Player * pPlayer, Creature * pCreature, uint32 /*uiSender*/, uint32 uiAction)
		{
			switch(uiAction)
			{
				case GOSSIP_ACTION_TRADE:
					pPlayer->GetSession()->SendListInventory(pCreature->GetGUID());
					break;
				case 2:
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
			}
			return true;
		}
};


void AddSC_GuildHouse()
{
	new GuildHouse_NPC();
 	new Table_Token();
	new Torch_Token();
	new Mailbox_Token();
	new Crate_Token();
	new A_Flag_Token();
	new H_Flag_Token();
	new Chair_Token();
	new Firepit_Token();
	new Vault_Token();
	new Barber_Token();
	new Guild_Token_Vendor();
	new Cranberry_Token();
}
