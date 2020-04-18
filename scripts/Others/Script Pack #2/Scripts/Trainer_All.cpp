#include "ScriptPCH.h"

class Trainer_Alchemy : public CreatureScript
{
public:
	Trainer_Alchemy()
		: CreatureScript("Trainer_Alchemy")
	{
	}

	struct Trainer_AlchemyAI : public ScriptedAI
	{
		Trainer_AlchemyAI(Creature *c) : ScriptedAI(c)
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
		return new Trainer_AlchemyAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Alchemy", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		if(pPlayer->HasSpell(51304) == true)
		{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Flask of the North Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
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
			case GOSSIP_ACTION_INFO_DEF + 1: // Learn Alchemy
				pPlayer->CLOSE_GOSSIP_MENU();
				if(pPlayer->HasSpell(51304) == true)
				{
			    		pCreature->MonsterWhisper("You already know Alchemy!", pPlayer->GetGUID());
				}
			        if(pPlayer->HasSpell(51304) == false)
					{
				        if(pPlayer->GetFreePrimaryProfessionPoints() == 0)
						{
		                    			pCreature->MonsterWhisper("You already know 6 Professions!", pPlayer->GetGUID());
						}
						if(!pPlayer->GetFreePrimaryProfessionPoints() == 0)
				        	{
				        		pPlayer->learnSpellHighRank(51304); // Grand Master Skill
				        		pPlayer->learnSpellHighRank(53042); // Mixology
				        		pPlayer->learnSpellHighRank(67025); // Flask of the North
							pPlayer->MonsterWhisper("You have succesfully learned Alchemy!", pPlayer->GetGUID());
						}		
				    }
					break;
					
			case GOSSIP_ACTION_INFO_DEF + 2: // Flask of the North Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(36908, 4);
				pPlayer->AddItem(40411, 1);
		}
        return true;
	}
};

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

			return false;
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
		                    			pCreature->MonsterWhisper("You already know 6 Professions!", pPlayer->GetGUID());
						}
						if(!pPlayer->GetFreePrimaryProfessionPoints() == 0)
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

class Trainer_Leatherworking : public CreatureScript
{
public:
	Trainer_Leatherworking()
		: CreatureScript("Trainer_Leatherworking")
	{
	}

	struct Trainer_LeatherworkingAI : public ScriptedAI
	{
		Trainer_LeatherworkingAI(Creature *c) : ScriptedAI(c)
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
		return new Trainer_LeatherworkingAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Leatherworking", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				if(pPlayer->HasSpell(51302) == true)
						{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Fur Lining - Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
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
			case GOSSIP_ACTION_INFO_DEF + 1: // Learn Leatherworking
				pPlayer->CLOSE_GOSSIP_MENU();
				if(pPlayer->HasSpell(51302) == true)
				{
			    pCreature->MonsterWhisper("You already know Leatherworking!", pPlayer->GetGUID());
				}
			        if(pPlayer->HasSpell(51302) == false)
					{
				        if(pPlayer->GetFreePrimaryProfessionPoints() == 0)
						{
		                    pCreature->MonsterWhisper("You already know 6 Professions!", pPlayer->GetGUID());
						}
						if(!pPlayer->GetFreePrimaryProfessionPoints() == 0)
				        	{
				        		pPlayer->learnSpellHighRank(51302); // Grand Master Skill
				        		pPlayer->learnSpellHighRank(57683); // Fur Lining - Attack Power
				        		pPlayer->learnSpellHighRank(57690); // Fur Lining - Stamina
				        		pPlayer->learnSpellHighRank(57691); // Fur Lining - Spell Power
							pPlayer->MonsterWhisper("You have succesfully learned Leatherworking!", pPlayer->GetGUID());
						}		
				    }
					break;
					
					case GOSSIP_ACTION_INFO_DEF + 2: // Fur Lining - Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(44128, 1);
		}
        return true;
	}
};

class Trainer_Jewelcrafting: public CreatureScript
{
public:
	Trainer_Jewelcrafting()
		: CreatureScript("Trainer_Jewelcrafting")
	{
	}

	struct Trainer_JewelcraftingAI : public ScriptedAI
	{
		Trainer_JewelcraftingAI(Creature *c) : ScriptedAI(c)
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
		return new Trainer_JewelcraftingAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Jewelcrafting", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				if(pPlayer->HasSpell(51311) == true)
				{
		         pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Dragon's Eye - Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);	
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
			case GOSSIP_ACTION_INFO_DEF + 1: // Learn Jewelcrafting
				pPlayer->CLOSE_GOSSIP_MENU();
				if(pPlayer->HasSpell(51311) == true)
				{
			    		pCreature->MonsterWhisper("You already know Jewelcrafting!", pPlayer->GetGUID());
				}
			    if(pPlayer->HasSpell(51311) == false)
					{
				    if(pPlayer->GetFreePrimaryProfessionPoints() == 0)
						{
		                    			pCreature->MonsterWhisper("You already know 6 Professions!", pPlayer->GetGUID());
						}
					if(!pPlayer->GetFreePrimaryProfessionPoints() == 0)
				        {
				        		pPlayer->learnSpellHighRank(51311); // Grand Master Skill
				        		pPlayer->learnSpellHighRank(56049); // Bold Dragon's Eye 
				        		pPlayer->learnSpellHighRank(56052); // Delicate Dragon's Eye
				        		pPlayer->learnSpellHighRank(56053); // Runed Dragon's Eye
				        		pPlayer->learnSpellHighRank(56054); // Bright Dragon's Eye
				        		pPlayer->learnSpellHighRank(56055); // Subtle Dragon's Eye
				        		pPlayer->learnSpellHighRank(56056); // Flashing Dragon's Eye
				        		pPlayer->learnSpellHighRank(56074); // Brilliant Dragon's Eye
				        		pPlayer->learnSpellHighRank(56076); // Fractured Dragon's Eye
				        		pPlayer->learnSpellHighRank(56077); // Lustrous Dragon's Eye
				        		pPlayer->learnSpellHighRank(56079); // Mystic Dragon's Eye
				        		pPlayer->learnSpellHighRank(56081); // Precise Dragon's Eye
				        		pPlayer->learnSpellHighRank(56083); // Quick Dragon's Eye
				        		pPlayer->learnSpellHighRank(56084); // Rigid Dragon's Eye
				        		pPlayer->learnSpellHighRank(56085); // Smooth Dragon's Eye
				        		pPlayer->learnSpellHighRank(56086); // Solid Dragon's Eye
				        		pPlayer->learnSpellHighRank(56087); // Sparkling Dragon's Eye
				        		pPlayer->learnSpellHighRank(56088); // Stormy Dragon's Eye
				        		pPlayer->learnSpellHighRank(56089); // Thick Dragon's Eye
							pPlayer->MonsterWhisper("You have succesfully learned Jewelcrafting!", pPlayer->GetGUID());
						}		
				    }
					break;
					
					case GOSSIP_ACTION_INFO_DEF + 2: // Dragon's Eye - Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(42225, 3);
		}
        return true;
	}
};

class Trainer_Inscription : public CreatureScript
{
public:
	Trainer_Inscription()
		: CreatureScript("Trainer_Inscription")
	{
	}

	struct Trainer_InscriptionAI : public ScriptedAI
	{
		Trainer_InscriptionAI(Creature *c) : ScriptedAI(c)
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
		return new Trainer_InscriptionAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Inscription", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				if(pPlayer->HasSpell(45363) == true)
				{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Master's Inscription - Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
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
			case GOSSIP_ACTION_INFO_DEF + 1: // Learn Inscription
				pPlayer->CLOSE_GOSSIP_MENU();
				if(pPlayer->HasSpell(45363) == true)
				{
			    		pCreature->MonsterWhisper("You already know Inscription!", pPlayer->GetGUID());
				}
			        if(pPlayer->HasSpell(45363) == false)
					{
				        if(pPlayer->GetFreePrimaryProfessionPoints() == 0)
						{
		                    			pCreature->MonsterWhisper("You already know 6 Professions!", pPlayer->GetGUID());
						}
						if(!pPlayer->GetFreePrimaryProfessionPoints() == 0)
				        	{
				        		pPlayer->learnSpellHighRank(45363); // Grand Master Skill
				        		pPlayer->learnSpellHighRank(61117); // Inscription of the Axe
				        		pPlayer->learnSpellHighRank(61118); // Inscription of the Crag
				        		pPlayer->learnSpellHighRank(61119); // Inscription of the Pinnacle
				        		pPlayer->learnSpellHighRank(61120); // Inscription of the Storm
							pPlayer->MonsterWhisper("You have succesfully learned Inscription!", pPlayer->GetGUID());
						}	
				    }
					break;
					
			case GOSSIP_ACTION_INFO_DEF + 2: // Master's Inscription - Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(43127, 1);
		}
        return true;
	}
};

class Trainer_Engineering : public CreatureScript
{
public:
	Trainer_Engineering()
		: CreatureScript("Trainer_Engineering")
	{
	}

	struct Trainer_EngineeringAI : public ScriptedAI
	{
		Trainer_EngineeringAI(Creature *c) : ScriptedAI(c)
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
		return new Trainer_EngineeringAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Engineering", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				if(pPlayer->HasSpell(51306) == true)
				{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Mind Amplification Dish Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nitro Boosts Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Hand-Mounted Pyro Rocket Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Hyperspeed Accelerators Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Reticulated Armor Webbing Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Flexweave Underlay Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Springy Arachnoweave Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Frag Belt", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
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
			case GOSSIP_ACTION_INFO_DEF + 1: // Learn Engineering
				pPlayer->CLOSE_GOSSIP_MENU();
				if(pPlayer->HasSpell(51306) == true)
				{
			    		pCreature->MonsterWhisper("You already know Engineering!", pPlayer->GetGUID());
				}
			        if(pPlayer->HasSpell(51306) == false)
					{
				        if(pPlayer->GetFreePrimaryProfessionPoints() == 0)
						{
		                    			pCreature->MonsterWhisper("You already know 6 Professions!", pPlayer->GetGUID());
						}
						if(!pPlayer->GetFreePrimaryProfessionPoints() == 0)
				        	{
				        		pPlayer->learnSpellHighRank(51306); // Grand Master Skill
				        		pPlayer->learnSpellHighRank(54998); // Hand-Mounted Pyro Rocket
				        		pPlayer->learnSpellHighRank(54999); // Hyperspeed Accelerators
				        		pPlayer->learnSpellHighRank(55016); // Nitro Boosts
				        		pPlayer->learnSpellHighRank(67839); // Mind Amplification Dish  
				        		pPlayer->learnSpellHighRank(63765); // Springy Arachnoweave
				        		pPlayer->learnSpellHighRank(55002); // Flexweave Underlay 
			    	    			pPlayer->learnSpellHighRank(63770); // Reticulated Armor Webbing
			    	    			pPlayer->learnSpellHighRank(54793); // Frag Belt
							pPlayer->MonsterWhisper("You have succesfully learned Engineering!", pPlayer->GetGUID());
						}		
				    }
					break;
			
			case GOSSIP_ACTION_INFO_DEF + 2: // Mind Amplification Dish Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(36913, 8);
				pPlayer->AddItem(39683, 1);
				break;
			
			case GOSSIP_ACTION_INFO_DEF + 3: // Nitro Boosts Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(39690, 6);
				pPlayer->AddItem(39681, 6);
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 4: // Hand-Mounted Pyro Rocket Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(36913, 6);
				pPlayer->AddItem(37702, 4);
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 5: // Hyperspeed Accelerators Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(36913, 6);
				pPlayer->AddItem(37700, 4);
				break;				
				
			case GOSSIP_ACTION_INFO_DEF + 6: // Reticulated Armor Webbing Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(36913, 4);
				pPlayer->AddItem(35624, 2);
				break;				
				
			case GOSSIP_ACTION_INFO_DEF + 7: // Flexweave Underlay Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(33470, 12);
				pPlayer->AddItem(39682, 1);
				break;				
				
			case GOSSIP_ACTION_INFO_DEF + 8: // Springy Arachnoweave Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(33470, 12);
				pPlayer->AddItem(39682, 1);
				break;
				
			case GOSSIP_ACTION_INFO_DEF + 9: // Frag Belt
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(36916, 8);
				pPlayer->AddItem(39690, 8);
		}
        return true;
	}
};

class Trainer_Enchanting : public CreatureScript
{
public:
	Trainer_Enchanting()
		: CreatureScript("Trainer_Enchanting")
	{
	}

	struct Trainer_EnchantingAI : public ScriptedAI
	{
		Trainer_EnchantingAI(Creature *c) : ScriptedAI(c)
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
		return new Trainer_EnchantingAI(pCreature);
    }

	void CreatureWhisperBasedOnBool(const char *text, Creature *pCreature, Player *pPlayer, bool value)
	{
		if (value)
			pCreature->MonsterWhisper(text, pPlayer->GetGUID());
	}

	void MainMenu(Player *pPlayer, Creature *pCreature)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Enchanting", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				if(pPlayer->HasSpell(51313) == true)
				{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Enchant Ring - Materials", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
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
			case GOSSIP_ACTION_INFO_DEF + 1: // Learn Enchanting
				pPlayer->CLOSE_GOSSIP_MENU();
				if(pPlayer->HasSpell(51313) == true)
				{
			    		pCreature->MonsterWhisper("You already know Enchanting!", pPlayer->GetGUID());
				}
			        if(pPlayer->HasSpell(51313) == false)
					{
				        if(pPlayer->GetFreePrimaryProfessionPoints() == 0)
						{
		                    pCreature->MonsterWhisper("You already know 6 Professions!", pPlayer->GetGUID());
						}
						if(!pPlayer->GetFreePrimaryProfessionPoints() == 0)
				        	{
				        		pPlayer->learnSpellHighRank(51313); // Grand Master Skill
				        		pPlayer->learnSpellHighRank(44635); // Ring - Assault
				        		pPlayer->learnSpellHighRank(44636); // Ring - Spellpower 
				        		pPlayer->learnSpellHighRank(59636); // Ring - Stamina
							pPlayer->MonsterWhisper("You have succesfully learned Enchanting!", pPlayer->GetGUID());
						}		
				    }
					break;
					
			case GOSSIP_ACTION_INFO_DEF + 2: // Ring Materials
				pPlayer->CLOSE_GOSSIP_MENU();
				pPlayer->AddItem(34054, 8);
				pPlayer->AddItem(34055, 1);
		}
        return true;
	}
};

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
		//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Skill up to 450!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
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
		                    			pCreature->MonsterWhisper("You already know 6 Professions!", pPlayer->GetGUID());
						}
						if(!pPlayer->GetFreePrimaryProfessionPoints() == 0)
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
				pPlayer->AddItem(2835, 1);
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

void AddSC_All_Trainers()
{
	new Trainer_Alchemy();
	new Trainer_Tailoring();
	new Trainer_Leatherworking();
	new Trainer_Jewelcrafting();
	new Trainer_Inscription();
	new Trainer_Engineering();
	new Trainer_Enchanting();
	new Trainer_Blacksmithing();
}