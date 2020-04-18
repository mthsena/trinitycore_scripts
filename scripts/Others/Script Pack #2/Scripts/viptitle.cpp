//uw
#include "ScriptPCH.h"
#include <cstring>
#include "CharacterDatabaseCleaner.h"
#include "DatabaseEnv.h"
#include "ObjectMgr.h"

class npc_gmvendor : public CreatureScript
{
public:
    npc_gmvendor() : CreatureScript("npc_gmvendor") 
	{ 
	}

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {

        if (pPlayer->GetSession()->GetSecurity() > SEC_PLAYER)
	 {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Buy the Token.", GOSSIP_SENDER_MAIN, 3000);
            pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
	 } else {
	     char str[200];
	     sprintf(str,"Your not a VIP, I cant sell to you!");
            pPlayer->PlayerTalkClass->SendCloseGossip();
            pCreature->MonsterWhisper("Your not a VIP, i cant sell to you $N!", pPlayer->GetGUID());
	 }

            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();

	     char str[200];

            switch (uiAction)
            {
            case 3000:
		  pPlayer->GetSession()->SendListInventory(pCreature->GetGUID()); 
                break;
            case 9999:
                pPlayer->PlayerTalkClass->ClearMenus();
                OnGossipHello(pPlayer, pCreature);
                break;
            }

            return true;
        }

};

class viptitle : public CreatureScript
{
public:
    viptitle() : CreatureScript("viptitle") 
	{ 
	}
	
        void GiveTitle(Player* pPlayer, Creature* pCreature)
        {
	     char str[200];

            if (pPlayer->HasItemCount(82, 1))
            {
                CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(1000);
		  
		  pPlayer->DestroyItemCount(82, 1, true);
                pPlayer->SetTitle(titleInfo);
                sprintf(str,"You have been given the title <VIP>!");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
            }
            else
            {
                sprintf(str,"You need the VIP Title Token!");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
            }
            pPlayer->PlayerTalkClass->ClearMenus();
            OnGossipHello(pPlayer, pCreature);
        }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {

        if (pPlayer->GetSession()->GetSecurity() > SEC_PLAYER)
	 {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Information about this system:", GOSSIP_SENDER_MAIN, 2000);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Give me the title", GOSSIP_SENDER_MAIN, 1000);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Buy the Token.", GOSSIP_SENDER_MAIN, 3000);
            pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
	 } else {
	     char str[200];
	     sprintf(str,"Your not a VIP, I cant sell to you!");
            pPlayer->PlayerTalkClass->SendCloseGossip();
            pCreature->MonsterWhisper("Your not a VIP, i cant sell to you $N!", pPlayer->GetGUID());
	 }

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
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Convert 1 Title Token", GOSSIP_SENDER_MAIN, 1001);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Return.", GOSSIP_SENDER_MAIN, 9999);
                pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
                return true;
                break;
            case 1001:
                GiveTitle(pPlayer, pCreature); 
                break;
	     case 2000:
                sprintf(str,"Buy the: <VIP> Token - And I will grant you a new title only for VIPs!");
                pPlayer->MonsterWhisper(str,pPlayer->GetGUID(),true);
                pPlayer->PlayerTalkClass->ClearMenus();
                OnGossipHello(pPlayer, pCreature);
                break;
            case 3000:
		  pPlayer->GetSession()->SendListInventory(pCreature->GetGUID()); 
                break;
            case 9999:
                pPlayer->PlayerTalkClass->ClearMenus();
                OnGossipHello(pPlayer, pCreature);
                break;
            }

            return true;
        }

};

void AddSC_viptitle()
{
    new viptitle();
    new npc_gmvendor();
}