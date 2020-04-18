#include "ScriptPCH.h"
#include <cstring>
#include "CharacterDatabaseCleaner.h"
#include "DatabaseEnv.h"
#include "ObjectMgr.h"

class pvpconverter : public CreatureScript
{
public:
    pvpconverter() : CreatureScript("pvpconverter") 
	{ 
	}
	
        void RewardItem(Player* pPlayer, Creature* pCreature)
        {
	     char str[200];

            if (pPlayer->HasItemCount(29436, 1))
            {
		  pPlayer->DestroyItemCount(29436, 1, true);
                pPlayer->ModifyArenaPoints(500);
                sprintf(str,"Your Arena Token was successfully converted to arena points!");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
            }
            else
            {
                sprintf(str,"You don't have any Arena Tokens!");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
            }
            pPlayer->PlayerTalkClass->ClearMenus();
            OnGossipHello(pPlayer, pCreature);
        }

        void RewardItemArena(Player* pPlayer, Creature* pCreature)
        {
	     char str[200];

            if (pPlayer->HasItemCount(29436, 1))
            {
		  pPlayer->DestroyItemCount(29436, 1, true);
                pPlayer->ModifyArenaPoints(1000);
                sprintf(str,"Your Arena Token was successfully converted to arena points!");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
            }
            else
            {
                sprintf(str,"You don't have any Arena Tokens!");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
            }
            pPlayer->PlayerTalkClass->ClearMenus();
            OnGossipHello(pPlayer, pCreature);
        }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Information about this system:", GOSSIP_SENDER_MAIN, 2000);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Continue", GOSSIP_SENDER_MAIN, 1000);

            pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();

	     char str[200];

            switch (uiAction)
            {
            case 1000:
                pPlayer->PlayerTalkClass->ClearMenus();
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Convert 1 Arena Token", GOSSIP_SENDER_MAIN, 1001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Return.", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
                return true;
                break;
            case 1001:
                RewardItem(pPlayer, pCreature); 
                break;
	     case 2000:
                sprintf(str,"For 1 Arena Token you will receive 500 Arena Points!");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
                pPlayer->PlayerTalkClass->ClearMenus();
                OnGossipHello(pPlayer, pCreature);
                break;
            case 9999:
                pPlayer->PlayerTalkClass->ClearMenus();
                OnGossipHello(pPlayer, pCreature);
                break;
            }

            return true;
        }

};

void AddSC_pvpconverter()
{
    new pvpconverter();
}