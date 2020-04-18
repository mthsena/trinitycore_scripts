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
 - Developer(s): Styler
 - Complete: 100%
 - ScriptName: 'player_tools' 
 - Comment: N/A
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"

enum defines
{
	GOLD_AMOUNT = 1000000,
};

static bool FreeFaction = false;

class player_tools : public CreatureScript
{
	public:
		player_tools() : CreatureScript("player_tools"){}

		bool OnGossipHello(Player * pPlayer, Creature * pCreature)
		{
			
			
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_Boss_Valanar:24|t|r 100g - Change my race ", GOSSIP_SENDER_MAIN, 0);
			if(FreeFaction == false)
				pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Spell_Arcane_Arcane04:24|t|r 100g - Change my faction", GOSSIP_SENDER_MAIN, 1);
			else
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\Achievement_General_HordeSlayer:24|t|r FREE - Change my faction", GOSSIP_SENDER_MAIN, 3);
			pPlayer->ADD_GOSSIP_ITEM(4, "|cff00ff00|TInterface\\icons\\INV_MISC_TICKET_TAROT_STACK_01:24|t|r 100g - Change my name", GOSSIP_SENDER_MAIN, 2);
			pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
		{
			if(!Player)
				return true;

			WorldSession * m_session = Player->GetSession();

			switch(uiAction)
			{
				case 0:
					if(Player->GetMoney() >= GOLD_AMOUNT)
					{
						Player->SetMoney(Player->GetMoney() - GOLD_AMOUNT);
						Player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
						CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '128' WHERE guid = %u", Player->GetGUID());
						m_session->SendNotification("Relog. You will be prompted on your next login.");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					else
					{
						m_session->SendNotification("You don't have enough Gold!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
				case 1:
					if(Player->GetMoney() >= GOLD_AMOUNT)
					{
						Player->SetMoney(Player->GetMoney() - GOLD_AMOUNT);
						Player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
						CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '64' WHERE guid = %u", Player->GetGUID());
						m_session->SendNotification("Relog. You will be prompted on your next login.");
						Player->PlayerTalkClass->SendCloseGossip();

					}
					else
					{
						m_session->SendNotification("You don't have enough Gold!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
				case 2:
					if(Player->GetMoney() >= GOLD_AMOUNT)
					{
						Player->SetMoney(Player->GetMoney() - GOLD_AMOUNT);
						Player->SetAtLoginFlag(AT_LOGIN_RENAME);
						CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '1' WHERE guid = %u", Player->GetGUID());
						m_session->SendNotification("Relog. You will be prompted on your next login.");
						Player->PlayerTalkClass->SendCloseGossip();

					}
					else
					{
						m_session->SendNotification("You don't have enough Gold!");
						Player->PlayerTalkClass->SendCloseGossip();
					}
					break;
				case 3:
						Player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
						CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '64' WHERE guid = %u", Player->GetGUID());
						m_session->SendNotification("Relog. You will be prompted on your next login.");
						Player->PlayerTalkClass->SendCloseGossip();
					break;

			}
			return true;
		}

};


class FactionChange_Command : public CommandScript
{
    public:
        FactionChange_Command() : CommandScript("FactionChange") { }

        static bool HandleFactionCommand(ChatHandler* handler, const char* args)
        {
			if(!args)
			{
				handler->GetSession()->SendNotification("Must use on or off.");
				return false;
			}

			std::string param = (char*)args;
			if(param == "on")
			{
				FreeFaction = true;
				char announce[512];
				snprintf(announce, 512, "%s has enabled free faction changes to help balance the server!", handler->GetSession()->GetPlayerName());
				sWorld->SendServerMessage(SERVER_MSG_STRING, announce);

			}
			else if(param == "off")
			{
				FreeFaction = false;
			}

            return true;
        }

        ChatCommand* GetCommands() const
        {
            static ChatCommand FactionCommandTable[] =
            {
                { "factionchange",          3,         true,   &HandleFactionCommand,        "", NULL },
                { NULL,             0,                  false,  NULL,                            "", NULL }
            };
            return FactionCommandTable;
        }
};




void AddSC_NPC_player_tools()
{
	new player_tools();
	new FactionChange_Command();
}