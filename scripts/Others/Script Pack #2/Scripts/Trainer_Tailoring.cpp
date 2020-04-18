#include "ScriptPCH.h"

class Trainer_Tailoring : public CreatureScript
{
public:
	Trainer_Tailoring()
		: CreatureScript("Trainer_Tailoring")
	{
	}

	struct Trainer_TailoringAI : public ScriptedAI
	{
		Trainer_TailoringAI(Creature *c) : ScriptedAI(c)
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
		return new Trainer_TailoringAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Tailoring", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				if(pPlayer->HasSpell(51309) == true)
				{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Darkglow Embroidery - Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Lightweave Embroidery - Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Swordguard Embroidery - Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
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
			case GOSSIP_ACTION_INFO_DEF + 1: // Learn Tailoring
				pPlayer->CLOSE_GOSSIP_MENU();
				if(pPlayer->HasSpell(51309) == true)
				{
			    pCreature->MonsterWhisper("You already know Tailoring!", pPlayer->GetGUID());
				}
			        if(pPlayer->HasSpell(51309) == false)
					{
				        if(pPlayer->GetFreePrimaryProfessionPoints() == 0)
						{
		                    pCreature->MonsterWhisper("You already know two Professions!", pPlayer->GetGUID());
						}
						if(pPlayer->GetFreePrimaryProfessionPoints() == 1)
				        {
				        pPlayer->learnSpellHighRank(51309); // Grand Master Skill
				        pPlayer->learnSpellHighRank(55777); // Swordguard Embroidery
				        pPlayer->learnSpellHighRank(55642); // Lightweave Embroidery
				        pPlayer->learnSpellHighRank(55769); // Darkglow Embroidery
						pPlayer->MonsterWhisper("You have succesfully learned Tailoring!", pPlayer->GetGUID());
						}
						if(pPlayer->GetFreePrimaryProfessionPoints() == 2)
				        {
				        pPlayer->learnSpellHighRank(51309); // Grand Master Skill
				        pPlayer->learnSpellHighRank(55777); // Swordguard Embroidery
				        pPlayer->learnSpellHighRank(55642); // Lightweave Embroidery
				        pPlayer->learnSpellHighRank(55769); // Darkglow Embroidery
						pPlayer->MonsterWhisper("You have succesfully learned Tailoring!", pPlayer->GetGUID());
						}		
				    }
					break;
					
					case GOSSIP_ACTION_INFO_DEF + 2: // Darkglow Embroidery - Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(41593, 1);
				pPlayer->AddItem(38426, 1);
					break;
					
					case GOSSIP_ACTION_INFO_DEF + 3: // Lightweave Embroidery - Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(41594, 1);
				pPlayer->AddItem(38426, 1);
					break;
					
					case GOSSIP_ACTION_INFO_DEF + 4: // Swordguard Embroidery - Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(41595, 1);
				pPlayer->AddItem(38426, 1);
		}
        return true;
	}
};

void AddSC_Script_Tailoring()
{
	new Trainer_Tailoring();
}