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
 - Developer(s): Styler, AwkwardDev
 - Complete: 100%
 - ScriptName: 'TitleNpc' 
 - Comment: Applied some magic to the script. (AwkwardDev)
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"

enum Actions
{
	// alliance
    ACTION_TITLE_PRIVATE,
    ACTION_TITLE_CORPORAL,
    ACTION_TITLE_SERGEANT,
    ACTION_TITLE_MASTER_SERGEANT,
    ACTION_TITLE_SERGEANT_MAJOR,
    ACTION_TITLE_KNIGHT,
    ACTION_TITLE_KNIGHT_LIEUTENANT,
    ACTION_TITLE_KNIGHT_CAPTAIN,
    ACTION_TITLE_KNIGHT_CHAMPION,
    ACTION_TITLE_LIEUTENANT_COMMANDER,
    ACTION_TITLE_COMMANDER,
    ACTION_TITLE_MARSHAL,
    ACTION_TITLE_FIELD_MARSHAL,
    ACTION_TITLE_GRAND_MARSHAL,
    // horde
    ACTION_TITLE_SCOUT,
    ACTION_TITLE_GRUNT,
    ACTION_TITLE_SERGEANT_H,
    ACTION_TITLE_SENIOR_SERGEANT,
    ACTION_TITLE_FIRST_SERGEANT,
    ACTION_TITLE_STONE_GUARD,
    ACTION_TITLE_BLOOD_GUARD,
    ACTION_TITLE_LEGIONNAIRE,
    ACTION_TITLE_CENTURION,
    ACTION_TITLE_CHAMPION,
    ACTION_TITLE_LIEUTENANT_GENERAL,
    ACTION_TITLE_GENERAL,
    ACTION_TITLE_WARLORD,
    ACTION_TITLE_HIGH_WARLORD
};

class TitleNpc : public CreatureScript
{
	public:
		TitleNpc() : CreatureScript("TitleNpc"){}

		uint32 GetTotalKill(Player* player)
		{
			QueryResult result = CharacterDatabase.PQuery("SELECT totalKills FROM characters WHERE guid = %u", player->GetGUID());
			if (result)
			{
			    Field* field = result->Fetch();
			    if (field)
			        return field[0].GetUInt32();
			}
			    return NULL;
		}

		bool OnGossipHello(Player* player, Creature* creature)
		{
			if (player->GetTeam() == ALLIANCE)
			{
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_A_01:24|t|r Private.(1 Kill)", GOSSIP_SENDER_MAIN, ACTION_TITLE_PRIVATE);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_A_02:24|t|r Corporal.(50 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_CORPORAL);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_A_03:24|t|r Sergeant.(100 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_SERGEANT);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_A_04:24|t|r Master Sergeant.(250 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_MASTER_SERGEANT);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_A_05:24|t|r Sergeant Major.(500 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_SERGEANT_MAJOR);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_A_06:24|t|r Knight.(750 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_KNIGHT);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_A_07:24|t|r Knight Lieutenant.(1000 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_KNIGHT_LIEUTENANT);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_A_08:24|t|r Knight Captain.(1500 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_KNIGHT_CAPTAIN);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_A_09:24|t|r Knight Champion.(3000 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_KNIGHT_CHAMPION);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_A_10:24|t|r Lieutenant Commander.(5000 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_LIEUTENANT_COMMANDER);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_A_11:24|t|r Commander.(7500 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_COMMANDER);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_A_12:24|t|r Marshal.(10000 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_MARSHAL);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_A_13:24|t|r Field Marshal.(15000 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_FIELD_MARSHAL);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_A_14:24|t|r Grand Marshal.(30000 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_GRAND_MARSHAL);
			}
			else
			{
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_H_01:24|t|r Scout.(1 Kill)", GOSSIP_SENDER_MAIN, ACTION_TITLE_SCOUT);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_H_02:24|t|r Grunt.(50 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_GRUNT);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_H_03:24|t|r Sergeant.(100 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_SERGEANT_H);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_H_04:24|t|r Senior Sergeant.(250 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_SENIOR_SERGEANT);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_H_05:24|t|r First Sergeant.(500 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_FIRST_SERGEANT);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_H_06:24|t|r Stone Guard.(750 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_STONE_GUARD);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_H_07:24|t|r Blood Guard.(1000 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_BLOOD_GUARD);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_H_08:24|t|r Legionnaire.(1500 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_LEGIONNAIRE);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_H_09:24|t|r Centurion.(3000 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_CENTURION);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_H_10:24|t|r Champion.(5000 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_CHAMPION);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_H_11:24|t|r Lieutenant General.(7500 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_LIEUTENANT_GENERAL);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_H_12:24|t|r General.(10000 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_GENERAL);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_H_13:24|t|r Warlord.(15000 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_WARLORD);
				player->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_PVP_H_14:24|t|r High Warlord.(30000 Kills)", GOSSIP_SENDER_MAIN, ACTION_TITLE_HIGH_WARLORD);
			}
			player->PlayerTalkClass->SendGossipMenu(9425, creature->GetGUID());
			    return true;
		}

		bool OnGossipSelect(Player* Player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			WorldSession* ws = Player->GetSession();

			switch (uiAction)
			{
				case ACTION_TITLE_PRIVATE:
					{
					    if (GetTotalKill(Player) >= 1)
					        Player->SetTitle(sCharTitlesStore.LookupEntry(1));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_CORPORAL:
					{
						if (GetTotalKill(Player) >= 50)
							Player->SetTitle(sCharTitlesStore.LookupEntry(2));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_SERGEANT:
					{
						if (GetTotalKill(Player) >= 100)
							Player->SetTitle(sCharTitlesStore.LookupEntry(3));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_MASTER_SERGEANT:
					{
						if (GetTotalKill(Player) >= 250)
							Player->SetTitle(sCharTitlesStore.LookupEntry(4));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_SERGEANT_MAJOR:
					{
						if (GetTotalKill(Player) >= 500)
							Player->SetTitle(sCharTitlesStore.LookupEntry(5));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_KNIGHT:
					{
						if (GetTotalKill(Player) >= 750)
							Player->SetTitle(sCharTitlesStore.LookupEntry(6));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_KNIGHT_LIEUTENANT:
					{
						if (GetTotalKill(Player) >= 1000)
							Player->SetTitle(sCharTitlesStore.LookupEntry(7));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_KNIGHT_CAPTAIN:
					{
						if (GetTotalKill(Player) >= 1500)
							Player->SetTitle(sCharTitlesStore.LookupEntry(8));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_KNIGHT_CHAMPION:
					{
						if (GetTotalKill(Player) >= 3000)
							Player->SetTitle(sCharTitlesStore.LookupEntry(9));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_LIEUTENANT_COMMANDER:
					{
						if (GetTotalKill(Player) >= 5000)
							Player->SetTitle(sCharTitlesStore.LookupEntry(10));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_COMMANDER:
					{
						if (GetTotalKill(Player) >= 7500)
							Player->SetTitle(sCharTitlesStore.LookupEntry(11));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_MARSHAL:
					{
						if (GetTotalKill(Player) >= 10000)
							Player->SetTitle(sCharTitlesStore.LookupEntry(12));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_FIELD_MARSHAL:
					{
						if (GetTotalKill(Player) >= 15000)
							Player->SetTitle(sCharTitlesStore.LookupEntry(13));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_GRAND_MARSHAL:
					{
						if (GetTotalKill(Player) >= 30000)
							Player->SetTitle(sCharTitlesStore.LookupEntry(14));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_SCOUT:
					{
						if (GetTotalKill(Player) >= 1)
							Player->SetTitle(sCharTitlesStore.LookupEntry(15));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_GRUNT:
					{
						if (GetTotalKill(Player) >= 50)
							Player->SetTitle(sCharTitlesStore.LookupEntry(16));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_SERGEANT_H:
					{
						if (GetTotalKill(Player) >= 100)
							Player->SetTitle(sCharTitlesStore.LookupEntry(17));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_SENIOR_SERGEANT:
					{
						if (GetTotalKill(Player) >= 250)
							Player->SetTitle(sCharTitlesStore.LookupEntry(18));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_FIRST_SERGEANT:
					{
						if (GetTotalKill(Player) >= 500)
							Player->SetTitle(sCharTitlesStore.LookupEntry(19));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_STONE_GUARD:
					{
						if (GetTotalKill(Player) >= 750)
							Player->SetTitle(sCharTitlesStore.LookupEntry(20));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_BLOOD_GUARD:
					{
						if (GetTotalKill(Player) >= 1000)
							Player->SetTitle(sCharTitlesStore.LookupEntry(21));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_LEGIONNAIRE:
					{
						if (GetTotalKill(Player) >= 1500)
							Player->SetTitle(sCharTitlesStore.LookupEntry(22));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_CENTURION:
					{
						if (GetTotalKill(Player) >= 3000)
							Player->SetTitle(sCharTitlesStore.LookupEntry(23));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_CHAMPION:
					{
						if (GetTotalKill(Player) >= 5000)
							Player->SetTitle(sCharTitlesStore.LookupEntry(24));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_LIEUTENANT_GENERAL:
					{
						if (GetTotalKill(Player) >= 7500)
							Player->SetTitle(sCharTitlesStore.LookupEntry(25));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_GENERAL:
					{
						if (GetTotalKill(Player) >= 10000)
							Player->SetTitle(sCharTitlesStore.LookupEntry(26));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_WARLORD:
					{
						if (GetTotalKill(Player) >= 15000)
							Player->SetTitle(sCharTitlesStore.LookupEntry(27));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				case ACTION_TITLE_HIGH_WARLORD:
					{
						if (GetTotalKill(Player) >= 30000)
							Player->SetTitle(sCharTitlesStore.LookupEntry(28));
						else
							ws->SendNotification("You dont have enough kills");
					}
				break;
				Player->PlayerTalkClass->SendCloseGossip();
			}
			    return true;
		}
};

void AddSC_TitleNpc()
{
	new TitleNpc();
}
