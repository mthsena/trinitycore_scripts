#include "ArenaTeamMgr.h"
#include "ScriptPCH.h"
#include <cstring>
#include <string.h>
//TODO: Make all these mounts with these ID's
//ITEM ID FOR THE MOUNT		  1      2      3     4      5
uint32 PM_MOUNTS_ARR [12]	  = {0, 65128,65129,65130,65131,65132,93025,93026,93027,93054,93061,93065};
enum PLAYER_MOUNTS
{
	PM_MOUNT_ITEM_1 = 65128,
	PM_MOUNT_ITEM_2 = 65129,
	PM_MOUNT_ITEM_3 = 65130,
	PM_MOUNT_ITEM_4 = 65131,
	PM_MOUNT_ITEM_5 = 65132,
	PM_MOUNT_ITEM_6 = 93025,
	PM_MOUNT_ITEM_7 = 93026,
	PM_MOUNT_ITEM_8 = 93027,
	PM_MOUNT_ITEM_9 = 93054,
	PM_MOUNT_ITEM_10 = 93061,
	PM_MOUNT_ITEM_11 = 93065,

	PVP_TICKET_ID = 19182,
	PVP_TICKET_COST = 50,

	ARENA_TEAM_COST = 1500,
	BROKEN_SOUL_ID = 29438,
	BROKEN_SOUL_COST = 1500
};

enum PMGossipMenuOptions
{
	OPTION_BUY_1 = GOSSIP_ACTION_INFO_DEF + 22,

	OPTION_BUY_2_HK = GOSSIP_ACTION_INFO_DEF + 23,
    OPTION_BUY_2_DP = GOSSIP_ACTION_INFO_DEF + 24,
	OPTION_BUY_2_VP = GOSSIP_ACTION_INFO_DEF + 25,

	OPTION_BUY_3_PVP = GOSSIP_ACTION_INFO_DEF + 26,
    OPTION_BUY_3_DP = GOSSIP_ACTION_INFO_DEF + 27,
	OPTION_BUY_3_VP = GOSSIP_ACTION_INFO_DEF + 28,

	OPTION_BUY_4_HK = GOSSIP_ACTION_INFO_DEF + 29,
    OPTION_BUY_4_DP = GOSSIP_ACTION_INFO_DEF + 30,
	OPTION_BUY_4_VP = GOSSIP_ACTION_INFO_DEF + 31,

	OPTION_BUY_5_ARENA = GOSSIP_ACTION_INFO_DEF + 32,
    OPTION_BUY_5_DP = GOSSIP_ACTION_INFO_DEF + 33,
	OPTION_BUY_5_VP = GOSSIP_ACTION_INFO_DEF + 34,

	OPTION_BUY_6 = GOSSIP_ACTION_INFO_DEF + 35,
    OPTION_BUY_6_DP = GOSSIP_ACTION_INFO_DEF + 36,
	OPTION_BUY_6_VP = GOSSIP_ACTION_INFO_DEF + 37,

	OPTION_BUY_7 = GOSSIP_ACTION_INFO_DEF + 38,
    OPTION_BUY_7_DP = GOSSIP_ACTION_INFO_DEF + 39,
	OPTION_BUY_7_VP = GOSSIP_ACTION_INFO_DEF + 40,

	OPTION_BUY_8 = GOSSIP_ACTION_INFO_DEF + 41,
    OPTION_BUY_8_DP = GOSSIP_ACTION_INFO_DEF + 42,
	OPTION_BUY_8_VP = GOSSIP_ACTION_INFO_DEF + 43,

	OPTION_BUY_9 = GOSSIP_ACTION_INFO_DEF + 44,
    OPTION_BUY_9_DP = GOSSIP_ACTION_INFO_DEF + 45,
	OPTION_BUY_9_VP = GOSSIP_ACTION_INFO_DEF + 46,

	OPTION_BUY_10 = GOSSIP_ACTION_INFO_DEF + 47,
    OPTION_BUY_10_DP = GOSSIP_ACTION_INFO_DEF + 48,
	OPTION_BUY_10_VP = GOSSIP_ACTION_INFO_DEF + 49,

	OPTION_BUY_11 = GOSSIP_ACTION_INFO_DEF + 50,
    OPTION_BUY_11_DP = GOSSIP_ACTION_INFO_DEF + 51,
	OPTION_BUY_11_VP = GOSSIP_ACTION_INFO_DEF + 52,

    OPTION_GOODBYE = GOSSIP_ACTION_INFO_DEF + 100,
};

//GOSSIP TEXT STRING							  1			  2			3		  4			5
std::string PM_MOUNT_TEXT [12] = {"Null(LeaveBlank)", "Ashes of Al'ar", "Argent Hippogryph", "Magnificent Flying Carpet", "Icebound Frostbrood Vanquisher", "Blazing Hippogryph", "Swift Orange Drake", "Swift Purple Drake", "Swift Red Drake", "Blue Cloud Serpent", "Celestial Serpent", "Purple Deepholm Dragon"};
//SPELL ID FOR THE MOUNT	          1      2      3     4      5
uint32 PM_MOUNT_SPELL [12]	  = {0, 40192,63844,61309,72807,74856,93025,93026,93027,93054,93061,93065};
//HK REQUIRED FOR MOUNT 	          1      2      3     4      5
uint32 PM_MOUNT_COST_HK [8]   = {0,   0,  5000,   0,   7500,   0, 10000, 15000};
//DP REQUIRED FOR MOUNT 	          1      2      3     4      5
uint32 PM_MOUNT_COST_DP [12]   = {0,   0,    5,    7,   10,    15,   20, 20, 20, 25, 30, 35};
//VP REQUIRED FOR MOUNT 	          1      2      3     4      5
uint32 PM_MOUNT_COST_VP [12]   = {0,   0,    75,    100,   150,    200, 200, 200, 300, 350, 400, 500};

class npc_player_mount : public CreatureScript
{
public:
    npc_player_mount() : CreatureScript("npc_player_mount") { }
	
	bool OnGossipHello(Player* player, Creature* creature)
	{
		if(!player || player->isInCombat())
			return false;

		if(!HasMount(player, PM_MOUNTS_ARR[1]))
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, PM_MOUNT_TEXT[1]+"[Unlocked]", GOSSIP_SENDER_MAIN, OPTION_BUY_1);

		for(uint32 count = 2; count < 12; count++)
		{
			if(!HasMount(player, PM_MOUNTS_ARR[count]))
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, PM_MOUNT_TEXT[count]+"[Locked]", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+count+10);
		}

		player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
		return true;
	}

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
		player->PlayerTalkClass->ClearMenus();
		player->PlayerTalkClass->SendCloseGossip();

		uint32 HK_Count = player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS);
		uint32 DP_Count = GetDonationPoints(player->GetSession()->GetAccountId());
		uint32 VP_Count = GetVotePoints(player->GetSession()->GetAccountId());
		bool PVP_TICKET = GetPvpTicketCount(player, PVP_TICKET_COST);
		bool ARENA_RATE = GetArenaTeamRating(player);

		switch(uiAction)
		{
			//PURCHASE 2ND MOUNT
			case OPTION_BUY_1: 
			GiveMountItem(player, PM_MOUNTS_ARR[1], 0, 0);
				return true;
			case OPTION_BUY_2_HK: 
					GiveMountItem(player, PM_MOUNTS_ARR[2], 0, 0);
				return true;
			case OPTION_BUY_2_DP: 
					GiveMountItem(player, PM_MOUNTS_ARR[2], PM_MOUNT_COST_DP[2], 0);
				return true;
			case OPTION_BUY_2_VP: 
					GiveMountItem(player, PM_MOUNTS_ARR[2], 0, PM_MOUNT_COST_VP[2]);
				return true;
			//PURCHASE 3ND MOUNT
			case OPTION_BUY_3_PVP: 
					GiveMountItem(player, PM_MOUNTS_ARR[3], 0, 0, true);
				return true;
			case OPTION_BUY_3_DP: 
					GiveMountItem(player, PM_MOUNTS_ARR[3], PM_MOUNT_COST_DP[3], 0);
				return true;
			case OPTION_BUY_3_VP: 
					GiveMountItem(player, PM_MOUNTS_ARR[3], 0, PM_MOUNT_COST_VP[3]);
				return true;
			//PURCHASE 4TH MOUNT
			case OPTION_BUY_4_HK: 
					GiveMountItem(player, PM_MOUNTS_ARR[4], 0, 0);
				return true;
			case OPTION_BUY_4_DP: 
					GiveMountItem(player, PM_MOUNTS_ARR[4], PM_MOUNT_COST_DP[4], 0);
				return true;
			case OPTION_BUY_4_VP: 
					GiveMountItem(player, PM_MOUNTS_ARR[4], 0, PM_MOUNT_COST_VP[4]);
				return true;
			//PURCHASE 5TH MOUNT
			case OPTION_BUY_5_ARENA: 
				if(player->HasItemCount(BROKEN_SOUL_ID, BROKEN_SOUL_COST))
				{
					player->DestroyItemCount(BROKEN_SOUL_ID, BROKEN_SOUL_COST, true);
					GiveMountItem(player, PM_MOUNTS_ARR[5], 0, 0);
				}
				return true;
			case OPTION_BUY_5_DP: 
					GiveMountItem(player, PM_MOUNTS_ARR[5], PM_MOUNT_COST_DP[5], 0);
				return true;
			case OPTION_BUY_5_VP: 
					GiveMountItem(player, PM_MOUNTS_ARR[5], 0, PM_MOUNT_COST_VP[5]);
				return true;
			//PURCHASE 6TH MOUNT
			case OPTION_BUY_6: 
				if(player->HasItemCount(19182, 125, false) && player->HasItemCount(29438, 1500))
				{
					player->DestroyItemCount(19182, 125, true);
					player->DestroyItemCount(29438, 1500, true);
					GiveMountItem(player, PM_MOUNTS_ARR[6], 0, 0);
				}
				return true;
			case OPTION_BUY_6_DP: 
					GiveMountItem(player, PM_MOUNTS_ARR[6], PM_MOUNT_COST_DP[6], 0);
				return true;
			case OPTION_BUY_6_VP: 
					GiveMountItem(player, PM_MOUNTS_ARR[6], 0, PM_MOUNT_COST_VP[6]);
				return true;
			//PURCHASE 7TH MOUNT
			case OPTION_BUY_7: 
				if(player->HasItemCount(20880, 150, false) && player->HasItemCount(29435, 1250))
				{
					player->DestroyItemCount(20880, 350, true);
					player->DestroyItemCount(29435, 1250, true);
					GiveMountItem(player, PM_MOUNTS_ARR[7], 0, 0);
				}
				return true;
			case OPTION_BUY_7_DP: 
					GiveMountItem(player, PM_MOUNTS_ARR[7], PM_MOUNT_COST_DP[7], 0);
				return true;
			case OPTION_BUY_7_VP: 
					GiveMountItem(player, PM_MOUNTS_ARR[7], 0, PM_MOUNT_COST_VP[7]);
				return true;
			//PURCHASE 8TH MOUNT
			case OPTION_BUY_8: 
				if(HK_Count >= PM_MOUNT_COST_HK[6] && player->HasItemCount(20880, 350))
				{
					player->DestroyItemCount(20880, 150, true);
					GiveMountItem(player, PM_MOUNTS_ARR[8], 0, 0);
				}
				return true;
			case OPTION_BUY_8_DP: 
					GiveMountItem(player, PM_MOUNTS_ARR[8], PM_MOUNT_COST_DP[8], 0);
				return true;
			case OPTION_BUY_8_VP: 
					GiveMountItem(player, PM_MOUNTS_ARR[8], 0, PM_MOUNT_COST_VP[8]);
				return true;
			//PURCHASE 9TH MOUNT
			case OPTION_BUY_9: 
				if(player->HasItemCount(23247, 750, false) && player->HasItemCount(40752, 500))
				{
					player->DestroyItemCount(23247, 750, true);
					player->DestroyItemCount(40752, 500, true);
					GiveMountItem(player, PM_MOUNTS_ARR[8], 0, 0);
				}
				return true;
			case OPTION_BUY_9_DP: 
					GiveMountItem(player, PM_MOUNTS_ARR[9], PM_MOUNT_COST_DP[9], 0);
				return true;
			case OPTION_BUY_9_VP: 
					GiveMountItem(player, PM_MOUNTS_ARR[9], 0, PM_MOUNT_COST_VP[9]);
				return true;
			//PURCHASE 9TH MOUNT
			case OPTION_BUY_10: 
				if(player->HasItemCount(23247, 2000) && player->HasItemCount(19182, 200))
				{
					player->DestroyItemCount(23247, 2000, true);
					player->DestroyItemCount(19182, 200, true);
					GiveMountItem(player, PM_MOUNTS_ARR[10], 0, 0);
				}
				return true;
			case OPTION_BUY_10_DP: 
					GiveMountItem(player, PM_MOUNTS_ARR[10], PM_MOUNT_COST_DP[10], 0);
				return true;
			case OPTION_BUY_10_VP: 
					GiveMountItem(player, PM_MOUNTS_ARR[10], 0, PM_MOUNT_COST_VP[10]);
				return true;
			//PURCHASE 9TH MOUNT
			case OPTION_BUY_11: 
				if(player->HasItemCount(29438, 1500) && player->HasItemCount(29435, 1500) && player->HasItemCount(29437, 500))
				{
					player->DestroyItemCount(29438, 1500, true);
					player->DestroyItemCount(29435, 1500, true);
					player->DestroyItemCount(29437, 500, true);
					GiveMountItem(player, PM_MOUNTS_ARR[11], 0, 0);
				}
				return true;
			case OPTION_BUY_11_DP: 
					GiveMountItem(player, PM_MOUNTS_ARR[11], PM_MOUNT_COST_DP[11], 0);
				return true;
			case OPTION_BUY_11_VP: 
					GiveMountItem(player, PM_MOUNTS_ARR[11], 0, PM_MOUNT_COST_VP[11]);
				return true;
			//END PURCHASE MOUNT

			//DISPLAY PURCHASE PRICES 2nd
			case GOSSIP_ACTION_INFO_DEF + 12: 
				if(HK_Count >= PM_MOUNT_COST_HK[2])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_HK[2])+" HK's ["+iToS(HK_Count)+" HK's]", GOSSIP_SENDER_MAIN, OPTION_BUY_2_HK);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_HK[2])+" HK's [You have "+iToS(HK_Count)+" HK's]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(DP_Count >= PM_MOUNT_COST_DP[2])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_DP[2])+" DP ["+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_BUY_2_DP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_DP[2])+" DP [You have "+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(VP_Count >= PM_MOUNT_COST_VP[2])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_VP[2])+" VP ["+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_BUY_2_VP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_VP[2])+" VP [You have "+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				break;

			//DISPLAY PURCHASE PRICES 3rd
			case GOSSIP_ACTION_INFO_DEF + 13: 
				if(PVP_TICKET)
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PVP_TICKET_COST)+" PVP Ticket's", GOSSIP_SENDER_MAIN, OPTION_BUY_3_PVP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PVP_TICKET_COST)+" PVP Ticket's", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(DP_Count >= PM_MOUNT_COST_DP[3])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_DP[3])+" DP ["+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_BUY_3_DP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_DP[3])+" DP [You have "+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(VP_Count >= PM_MOUNT_COST_VP[3])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_VP[3])+" VP ["+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_BUY_3_VP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_VP[3])+" VP [You have "+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
				break;

			//DISPLAY PURCHASE PRICES 4th
			case GOSSIP_ACTION_INFO_DEF + 14: 
				if(HK_Count >= PM_MOUNT_COST_HK[4])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_HK[4])+" HK's ["+iToS(HK_Count)+" HK's]", GOSSIP_SENDER_MAIN, OPTION_BUY_4_HK);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_HK[4])+" HK's [You have "+iToS(HK_Count)+" HK's]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(DP_Count >= PM_MOUNT_COST_DP[4])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_DP[4])+" DP ["+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_BUY_4_DP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_DP[4])+" DP [You have "+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(VP_Count >= PM_MOUNT_COST_VP[4])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_VP[4])+" VP ["+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_BUY_4_VP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_VP[4])+" VP [You have "+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
				break;
			//DISPLAY PURCHASE PRICES 5th
			case GOSSIP_ACTION_INFO_DEF + 15: 
				if(ARENA_RATE)
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(ARENA_TEAM_COST)+" Arena Rating & 1500 Broken Souls", GOSSIP_SENDER_MAIN, OPTION_BUY_5_ARENA);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(ARENA_TEAM_COST)+" Arena Rating & 1500 Broken Souls", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(DP_Count >= PM_MOUNT_COST_DP[5])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_DP[5])+" DP ["+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_BUY_5_DP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_DP[5])+" DP [You have "+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(VP_Count >= PM_MOUNT_COST_VP[5])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_VP[5])+" VP ["+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_BUY_5_VP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_VP[5])+" VP [You have "+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
				break;
			//DISPLAY PURCHASE PRICES 6th
			case GOSSIP_ACTION_INFO_DEF + 16:
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "This mount is a 400% Flying Mount.", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
				if(player->HasItemCount(19182, 125) && player->HasItemCount(29438, 1500))
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with 125 PVP Ticket's & 1500 Broken Souls", GOSSIP_SENDER_MAIN, OPTION_BUY_6);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need 125 PVP Ticket's & 1500 Broken Souls", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(DP_Count >= PM_MOUNT_COST_DP[6])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_DP[6])+" DP ["+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_BUY_6_DP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_DP[6])+" DP [You have "+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(VP_Count >= PM_MOUNT_COST_VP[6])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_VP[6])+" VP ["+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_BUY_6_VP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_VP[6])+" VP [You have "+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
				break;
			//DISPLAY PURCHASE PRICES 7th
			case GOSSIP_ACTION_INFO_DEF + 17:
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "This mount is a 400% Flying Mount.", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
				if(player->HasItemCount(20880, 150) && player->HasItemCount(29435, 1250))
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with 150 Battlemasters Tokens & 1250 Stolen Souls", GOSSIP_SENDER_MAIN, OPTION_BUY_7);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need 150 Battlemasters Tokens & 1250 Stolen Souls", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(DP_Count >= PM_MOUNT_COST_DP[7])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_DP[7])+" DP ["+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_BUY_7_DP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_DP[7])+" DP [You have "+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(VP_Count >= PM_MOUNT_COST_VP[7])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_VP[7])+" VP ["+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_BUY_7_VP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_VP[7])+" VP [You have "+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
				break;
			//DISPLAY PURCHASE PRICES 8th
			case GOSSIP_ACTION_INFO_DEF + 18: 
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "This mount is a 400% Flying Mount.", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
				if(player->HasItemCount(23247, 750) && player->HasItemCount(40752, 500))
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with 750 Event Coins & 500 TD Coins", GOSSIP_SENDER_MAIN, OPTION_BUY_8);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need 750 Event coins & 500 TD Coins", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(DP_Count >= PM_MOUNT_COST_DP[8])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_DP[8])+" DP ["+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_BUY_8_DP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_DP[8])+" DP [You have "+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(VP_Count >= PM_MOUNT_COST_VP[8])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_VP[8])+" VP ["+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_BUY_8_VP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_VP[8])+" VP [You have "+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
				break;
			case GOSSIP_ACTION_INFO_DEF + 19: 
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "This mount is a 500% Flying Mount.", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
			if(HK_Count >= PM_MOUNT_COST_HK[6] && player->HasItemCount(20880, 350))
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_HK[6])+" HK's ["+iToS(HK_Count)+" HK's] + 350 BM Tokens", GOSSIP_SENDER_MAIN, OPTION_BUY_9);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_HK[6])+" HK's [You have "+iToS(HK_Count)+" HK's] + 350 BM Tokens", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(DP_Count >= PM_MOUNT_COST_DP[9])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_DP[9])+" DP ["+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_BUY_9_DP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_DP[9])+" DP [You have "+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(VP_Count >= PM_MOUNT_COST_VP[9])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_VP[9])+" VP ["+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_BUY_9_VP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_VP[9])+" VP [You have "+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
				break;
			case GOSSIP_ACTION_INFO_DEF + 20: 
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "This mount is a 600% Flying Mount.", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
				if(player->HasItemCount(23247, 2000) && player->HasItemCount(19182, 200))
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with 2000 Event Coins & 200 PvP Tickets", GOSSIP_SENDER_MAIN, OPTION_BUY_10);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need 2000 Event coins & 200 PvP Tickets", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(DP_Count >= PM_MOUNT_COST_DP[10])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_DP[10])+" DP ["+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_BUY_10_DP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_DP[10])+" DP [You have "+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(VP_Count >= PM_MOUNT_COST_VP[10])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_VP[10])+" VP ["+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_BUY_10_VP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_VP[10])+" VP [You have "+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
				break;
			case GOSSIP_ACTION_INFO_DEF + 21: 
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "This mount is a 700% Flying Mount. RAUWR!", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
				if(HK_Count >= PM_MOUNT_COST_HK[7] && player->HasItemCount(29438, 1500) && player->HasItemCount(29435, 1500) && player->HasItemCount(29437, 500))
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_HK[7])+" HK's ["+iToS(HK_Count)+" HK's] + 2000 Broken Souls, 2000 Stolen Souls & 500 Pure Souls", GOSSIP_SENDER_MAIN, OPTION_BUY_11);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_HK[7])+" HK's [You have "+iToS(HK_Count)+" HK's] + 2000 Broken Souls, 2000 Stolen Souls & 500 Pure Souls", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(DP_Count >= PM_MOUNT_COST_DP[11])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_DP[11])+" DP ["+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_BUY_11_DP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_DP[11])+" DP [You have "+iToS(DP_Count)+" DP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

				if(VP_Count >= PM_MOUNT_COST_VP[11])
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Buy with "+iToS(PM_MOUNT_COST_VP[11])+" VP ["+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_BUY_11_VP);
				else
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "You need "+iToS(PM_MOUNT_COST_VP[11])+" VP [You have "+iToS(VP_Count)+" VP]", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
				break;
			//END DISPLAY PRICES

			case OPTION_GOODBYE: return true; break;
			default: break;
		}

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Goodbye.", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
		player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
		return true;
	}

	bool HasMount(Player* player, uint32 ItemId)
	{
		if(!player || !ItemId)
			return false;

		if(player->HasItemCount(ItemId, 1))
			return true;
		return false;
	}

	bool GiveMountItem(Player* player, uint32 MountItem, uint32 dp, uint32 vp, bool pvpticket = false)
	{
		if(dp != 0)
		{
			if(!RemoveDonationPoints(player->GetSession()->GetAccountId(), dp))
				return false;
		}

		if(vp != 0)
		{
			if(!RemoveVotePoints(player->GetSession()->GetAccountId(), vp))
				return false;
		}

		if(pvpticket)
		{
			if(!RemovePvpTicket(player, PVP_TICKET_COST))
				return false;
		}

		ItemPosCountVec dest;
		if(player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, MountItem, 1) == EQUIP_ERR_OK)
		{	
			if(player->AddItem(MountItem, 1))
			{
				player->GetSession()->SendAreaTriggerMessage("The mount has been placed in your bag!");
				ChatHandler(player->GetSession()).PSendSysMessage("The mount has been placed in your bag!");
				return true;
			}
		}
		return false;
	}

	uint32 GetVotePoints(uint32 PlayerId)
	{
		uint32 vp;
		QueryResult result = LoginDatabase.PQuery("SELECT vp FROM fusion.account_data WHERE id = '%u'", PlayerId);
		if(result)
		{
			vp = (*result)[0].GetUInt32();
			if (vp < 0)
				return 0;
		} else {
			return 0;
		}
		return vp;
	}

	bool RemoveVotePoints(uint32 PlayerId, uint32 Count)
	{
		if(Count > 0)
			LoginDatabase.PExecute("UPDATE fusion.account_data SET vp = vp - '%u' WHERE id = '%u'", Count, PlayerId);
		return true;
	}

	uint32 GetDonationPoints(uint32 PlayerId)
	{
		uint32 dp;
		QueryResult result = LoginDatabase.PQuery("SELECT dp FROM fusion.account_data WHERE id = '%u'", PlayerId);
		if(result)
		{
			dp = (*result)[0].GetUInt32();
			if (dp < 0)
				return 0;
		} else {
			return 0;
		}
		return dp;
	}

	bool RemoveDonationPoints(uint32 PlayerId, uint32 Count)
	{
		if(Count > 0)
			LoginDatabase.PExecute("UPDATE fusion.account_data SET dp = dp - '%u' WHERE id = '%u'", Count, PlayerId);
		return true;
	}

	bool GetPvpTicketCount(Player* player, uint32 count)
	{
		if(!player->HasItemCount(PVP_TICKET_ID, count))
            return false;
		return true;
	}

	bool RemovePvpTicket(Player* player, uint32 Count)
	{
		player->DestroyItemCount(PVP_TICKET_ID, Count, true);
		return true;
	}

	bool GetArenaTeamRating(Player* player)
	{
		for (uint8 i = 0; i < MAX_ARENA_SLOT; ++i)
		{
			if (ArenaTeam* at = sArenaTeamMgr->GetArenaTeamById(player->GetArenaTeamId(i)))
			{
				if(at->GetRating() >= ARENA_TEAM_COST)
					return true;
			}
		}
		return false;
	}

	std::string iToS(uint32 integer) 
	{
    std::stringstream out;
    out << integer;
    return out.str();
	}
};

class item_player_mount_class : public ItemScript
{
public:
    item_player_mount_class() : ItemScript("item_player_mount") { }

bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
{
	if(player->isInCombat()){
		ChatHandler(player->GetSession()).PSendSysMessage("You can not use this item while in combat!"); return false;
	}

	if(player->isDead()){
		ChatHandler(player->GetSession()).PSendSysMessage("You can not use this item when you're dead!"); return false;
	}

	if(player->isInFlight() || player->IsFlying() || player->IsFalling()){
		ChatHandler(player->GetSession()).PSendSysMessage("You can not use this item while in flight!"); return false;
	}

	if(player->IsMounted()){
		ChatHandler(player->GetSession()).PSendSysMessage("You can not use this item while mounted!"); return false;
	}

	Map *plrMap = player->GetMap();
	if(plrMap->IsBattlegroundOrArena() || plrMap->IsDungeon()){
		ChatHandler(player->GetSession()).PSendSysMessage("You can not use this item here!"); return false;
	}

	switch(item->GetEntry())
	{
	case PM_MOUNT_ITEM_1: SummonFlyingMount(player, PM_MOUNT_SPELL[1]);break;
	case PM_MOUNT_ITEM_2: SummonFlyingMount(player, PM_MOUNT_SPELL[2]);break;
	case PM_MOUNT_ITEM_3: SummonFlyingMount(player, PM_MOUNT_SPELL[3]);break;
	case PM_MOUNT_ITEM_4: SummonFlyingMount(player, PM_MOUNT_SPELL[4]);break;
	case PM_MOUNT_ITEM_5: SummonFlyingMount(player, PM_MOUNT_SPELL[5]);break;
	case PM_MOUNT_ITEM_6: SummonFlyingMount(player, PM_MOUNT_SPELL[6]);break;
	case PM_MOUNT_ITEM_7: SummonFlyingMount(player, PM_MOUNT_SPELL[7]);break;
	case PM_MOUNT_ITEM_8: SummonFlyingMount(player, PM_MOUNT_SPELL[8]);break;
	case PM_MOUNT_ITEM_9: SummonFlyingMount(player, PM_MOUNT_SPELL[9]);break;
	case PM_MOUNT_ITEM_10: SummonFlyingMount(player, PM_MOUNT_SPELL[10]);break;
	case PM_MOUNT_ITEM_11: SummonFlyingMount(player, PM_MOUNT_SPELL[11]);break;
	case 65133: SummonFlyingMount(player, 59567);break;
	default: break;
	}

	return true;
}

void SummonFlyingMount(Player* player, uint32 spellID)
{	
	Pet* plrPet = player->GetPet();
	if(plrPet)
		plrPet->UnSummon();

	player->UnsummonPetTemporaryIfAny();
	
	player->CastSpell(player, spellID, false);
}
};

void AddSC_player_mount()
{
   new npc_player_mount();
   new item_player_mount_class();
}