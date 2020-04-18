/*
//
 - by: SymbolixDEV
 - Complete: 100%
*/
#include "ScriptPCH.h"

enum  defines
{
 faction_token = 0, // Faction Change Token set you cost
 race_token = 0 // Race Change Token set you cost
};

class npc_changer : public CreatureScript
{
  public:
		npc_changer() : CreatureScript("npc_changer"){}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			
			
			pPlayer->ADD_GOSSIP_ITEM(4, "Change My Race ", GOSSIP_SENDER_MAIN, 0);
		    pPlayer->ADD_GOSSIP_ITEM(4, "Change My Faction", GOSSIP_SENDER_MAIN, 1);
			pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			if(!Player)
				return true;

			switch(uiAction)
			{
				case 0:
					if(Player->HasItemCount(race_token, 0))
					{
						Player->DestroyItemCount(race_token, 0, true, false);
						Player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
						CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '128' WHERE guid = %u", Player->GetGUID());
						Player->GetSession()->SendNotification("You need to relog, to change your race!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					else
					{
						Player->GetSession()->SendNotification("You need atleast one race change token!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
				case 1:
					if(Player->HasItemCount(faction_token, 0))
					{
						Player->DestroyItemCount(faction_token, 0, true, false);
						Player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
						CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '64' WHERE guid = %u", Player->GetGUID());
						Player->GetSession()->SendNotification("You need to relog, to change your faction!");
						Player->PlayerTalkClass->SendCloseGossip();

					}

					else
					{
						Player->GetSession()->SendNotification("You need atleast one faction change token!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
			}
			return true;
		}

};

void AddSC_npc_changer()
{
	new npc_changer();
}
