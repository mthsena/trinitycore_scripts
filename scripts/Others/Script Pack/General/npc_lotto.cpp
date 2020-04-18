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
//test
#include "ScriptPCH.h"
#include <cstring>

enum eEnums
{
	ITEM_LOTTO   = 200800,
	
};

class npc_lotto : public CreatureScript
{
    public:
        npc_lotto() : CreatureScript("npc_lotto") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
			if (player->HasItemCount(ITEM_LOTTO, 1, false))
			{
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "The stars say i'll be looking, i fancy my chances in the lottery this week.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
			}
			else
				creature->MonsterWhisper("You dont have enough Lottery Tickets", player->GetGUID());

			player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            return true;
		};

		bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
		{
			
            player->PlayerTalkClass->ClearMenus();
            player->CLOSE_GOSSIP_MENU();
        switch (action)
            {
		    case GOSSIP_ACTION_INFO_DEF+1:
			    creature->MonsterWhisper("Greetings competitor! Thank you for purchasing your Lottery ticket, please be sure to check your numbers against our database, for your chance to win a stunning 200 gold coins!", player->GetGUID());
				WorldDatabase.PExecute("INSERT INTO game_lotto (entry, comment) values (%u,0)", player->GetGUIDLow());
				player->DestroyItemCount(ITEM_LOTTO, 1, true, false);
				break;
		    }

			player->CLOSE_GOSSIP_MENU();
			return true;
	    }


};

void AddSC_npc_lotto()
{
	new npc_lotto();
}
