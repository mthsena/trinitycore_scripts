#include "ScriptPCH.h"

class Trainer_Blacksmithing : public CreatureScript
{
public:
	Trainer_Blacksmithing()
		: CreatureScript("Trainer_Blacksmithing")
	{
	}

	struct Trainer_BlacksmithingAI : public ScriptedAI
	{
		Trainer_BlacksmithingAI(Creature *c) : ScriptedAI(c)
		{
		}

		void Reset()
		{
			me->RestoreFaction();
		}

		void EnterEvadeMode()
        {
            me->GetMotionMaster()->Clear();
            ScriptedAI::EnterEvadeMode();
        }

	};

	CreatureAI* GetAI(Creature* pCreature) const
    {
		return new Trainer_BlacksmithingAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Blacksmithing", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				if(pPlayer->HasSpell(51300) == true)
				{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Socket Bracer Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Socket Gloves Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Skill up to 450!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
		}
		pPlayer->SEND_GOSSIP_MENU(907, pCreature->GetGUID());
	}

	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
		MainMenu(pPlayer, pCreature);

        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
		if (pPlayer->isInCombat())
		{
			pCreature->MonsterWhisper("You are in combat!", pPlayer->GetGUID());
			pPlayer->CLOSE_GOSSIP_MENU();

			return true;
		}

		pPlayer->PlayerTalkClass->ClearMenus();

		switch (uiAction)
		{
			case GOSSIP_ACTION_INFO_DEF + 1: // Learn Blacksmithing
				pPlayer->CLOSE_GOSSIP_MENU();
				if(pPlayer->HasSpell(51300) == true)
				{
			    pCreature->MonsterWhisper("You already know Blacksmithing!", pPlayer->GetGUID());
				}
			        if(pPlayer->HasSpell(51300) == false)
					{
				        if(pPlayer->GetFreePrimaryProfessionPoints() == 0)
						{
		                    pCreature->MonsterWhisper("You already know two Professions!", pPlayer->GetGUID());
						}
						if(pPlayer->GetFreePrimaryProfessionPoints() == 1)
				        {
				        pPlayer->learnSpellHighRank(51300); // Grand Master Skill
				        pPlayer->learnSpellHighRank(55628); // Socket Bracers
				        pPlayer->learnSpellHighRank(55641); // Socket Gloves 
						pPlayer->MonsterWhisper("You have succesfully learned Blacksmithing!", pPlayer->GetGUID());
						}
						if(pPlayer->GetFreePrimaryProfessionPoints() == 2)
				        {
				        pPlayer->learnSpellHighRank(51300); // Grand Master Skill
				        pPlayer->learnSpellHighRank(55628); // Socket Bracers
				        pPlayer->learnSpellHighRank(55641); // Socket Gloves 
						pPlayer->MonsterWhisper("You have succesfully learned Blacksmithing!", pPlayer->GetGUID());
						}		
				    }
					break;
					
			case GOSSIP_ACTION_INFO_DEF + 2: // Socket Bracer Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(36913, 4);
				pPlayer->AddItem(35624, 1);
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 3: // Socket Gloves Materials
			    pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(36913, 4);
				pPlayer->AddItem(35627, 1);	
                break;	
				
			case GOSSIP_ACTION_INFO_DEF + 4: // Skill Up!
			    pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(2835, 1);
				
		}
        return true;
	}
};

void AddSC_Script_Blacksmithing()
{
	new Trainer_Blacksmithing();
}