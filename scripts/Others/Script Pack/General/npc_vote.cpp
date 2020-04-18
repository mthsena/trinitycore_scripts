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
#include "ScriptPCH.h"
#define TOKEN_ID 850000 // Replace 49927 to YOUR_TOKEN_ID


class vote_NPC : public CreatureScript

	{
public:

vote_NPC() : CreatureScript("vote_NPC") {}

bool OnGossipHello(Player* pPlayer, Creature* _creature)
{
		pPlayer->ADD_GOSSIP_ITEM(5, "Required Vote Tokens in (x)", GOSSIP_SENDER_MAIN, 111212);
		pPlayer->ADD_GOSSIP_ITEM(9, "Spectral Tiger Cub->(5)", GOSSIP_SENDER_MAIN, 1);
		pPlayer->ADD_GOSSIP_ITEM(9, "Windrider Cub->(5)", GOSSIP_SENDER_MAIN, 2);
		pPlayer->ADD_GOSSIP_ITEM(9, "Mini Thor->(5)", GOSSIP_SENDER_MAIN, 3);
		pPlayer->ADD_GOSSIP_ITEM(9, ">> Mini Gryphon Hatchling ->(5)", GOSSIP_SENDER_MAIN, 4);
		pPlayer->ADD_GOSSIP_ITEM(9, ">> Mini Diablo ->(5)", GOSSIP_SENDER_MAIN, 5);
		pPlayer->ADD_GOSSIP_ITEM(9, ">> Onyxian Whelpling ->(5)", GOSSIP_SENDER_MAIN, 6);
		pPlayer->ADD_GOSSIP_ITEM(9, ">> Core Hound Pup ->(5)", GOSSIP_SENDER_MAIN, 7);
		pPlayer->ADD_GOSSIP_ITEM(9, ">> Mr.Chilly ->(5)", GOSSIP_SENDER_MAIN, 8);
		pPlayer->ADD_GOSSIP_ITEM(9, ">> Curious Oracel Hatchling ->(5)", GOSSIP_SENDER_MAIN, 9);
		pPlayer->ADD_GOSSIP_ITEM(9, ">> Phoenix Hatchling ->(5)", GOSSIP_SENDER_MAIN, 10);
		pPlayer->ADD_GOSSIP_ITEM(9, ">> Hippogryph Hatchling ->(5)", GOSSIP_SENDER_MAIN, 11);


        pPlayer->PlayerTalkClass->SendGossipMenu(907, _creature->GetGUID());
        return true;

}

bool OnGossipSelect(Player* pPlayer, Creature* _creature, uint32 uiSender, uint32 uiAction)
{ 
        pPlayer->PlayerTalkClass->ClearMenus();
        
        if (uiSender == GOSSIP_SENDER_MAIN)
        {
                
                switch(uiAction)
                {       

	       case 1: // Specral Tiger (25) vote tokens
                if (pPlayer->HasItemCount(TOKEN_ID, 25, true))
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->AddItem(49343, 1);
					pPlayer->DestroyItemCount(TOKEN_ID, 25, true);
                    _creature->MonsterWhisper("Your Companion has been added.", pPlayer->GetGUID());
					return true;
                }
                else 
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("You dont have enough Vote Tokens.", pPlayer->GetGUID());
                    return false;
                }
                break;



		   	case 2: // Windrider Cub (25) vote tokens
               if (pPlayer->HasItemCount(TOKEN_ID, 25, true))
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                     pPlayer->AddItem(49663, 1);
					pPlayer->DestroyItemCount(TOKEN_ID, 25, true);
                    _creature->MonsterWhisper("Your Companion has been added.", pPlayer->GetGUID());
					return true;
                }
                else 
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("You dont have enough Vote Tokens.", pPlayer->GetGUID());
                    return false;
                }
                break;


		     	case 3: // Mini Thor (25) vote tokens
                if (pPlayer->HasItemCount(TOKEN_ID, 25, true))
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->AddItem(56806, 1);
					pPlayer->DestroyItemCount(TOKEN_ID, 25, true);
                    _creature->MonsterWhisper("Your Companion has been added.", pPlayer->GetGUID());
					return true;
                }
                else 
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("You dont have enough Vote Tokens.", pPlayer->GetGUID());
                    return false;
                }
                break;


		      	case 4: // Mini Gryphon vote tokens
                if (pPlayer->HasItemCount(TOKEN_ID, 25, true))
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->AddItem(49662, 1);
					pPlayer->DestroyItemCount(TOKEN_ID, 25, true);
                    _creature->MonsterWhisper("Your Companion has been added.", pPlayer->GetGUID());
					return true;
                }
                else 
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("You dont have enough Vote Tokens.", pPlayer->GetGUID());
                    return false;
                }
                break;




			    case 5: // Mini Diablo vote tokens
                if (pPlayer->HasItemCount(TOKEN_ID, 25, true))
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->AddItem(13584, 1);
					pPlayer->DestroyItemCount(TOKEN_ID, 25, true);
                    _creature->MonsterWhisper("Your Companion has been added.", pPlayer->GetGUID());
					return true;
                }
                else 
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("You dont have enough Vote Tokens.", pPlayer->GetGUID());
                    return false;
                }
                break;





				
		     	case 6: // Onyx Whelp vote tokens
                if (pPlayer->HasItemCount(TOKEN_ID, 25, true))
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->AddItem(49362, 1);
					pPlayer->DestroyItemCount(TOKEN_ID, 25, true);
                    _creature->MonsterWhisper("Your Companion has been added.", pPlayer->GetGUID());
					return true;
                }
                else 
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("You dont have enough Vote Tokens.", pPlayer->GetGUID());
                    return false;
                }
                break;



		      	case 7: // Core Hound vote tokens
                if (pPlayer->HasItemCount(TOKEN_ID, 25, true))
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->AddItem(49646, 1);
					pPlayer->DestroyItemCount(TOKEN_ID, 25, true);
                    _creature->MonsterWhisper("Your Companion has been added.", pPlayer->GetGUID());
					return true;
                }
                else 
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("You dont have enough Vote Tokens.", pPlayer->GetGUID());
                    return false;
                }
                break;





			    case 8: // Mr.Chilly vote tokens
                if (pPlayer->HasItemCount(TOKEN_ID, 25, true))
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->AddItem(41133, 1);
					pPlayer->DestroyItemCount(TOKEN_ID, 25, true);
                    _creature->MonsterWhisper("Your Companion has been added.", pPlayer->GetGUID());
					return true;
                }
                else 
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("You dont have enough Vote Tokens.", pPlayer->GetGUID());
                    return false;
                }
                break;




				case 9: // Curious hatch vote tokens
                if (pPlayer->HasItemCount(TOKEN_ID, 25, true))
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->AddItem(46545, 1);
					pPlayer->DestroyItemCount(TOKEN_ID, 25, true);
                    _creature->MonsterWhisper("Your Companion has been added.", pPlayer->GetGUID());
					return true;
                }
                else 
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("You dont have enough Vote Tokens.", pPlayer->GetGUID());
                    return false;
                }
                break;




				case 10: // Phoenix vote tokens
                if (pPlayer->HasItemCount(TOKEN_ID, 25, true))
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->AddItem(35504, 1);
					pPlayer->DestroyItemCount(TOKEN_ID, 25, true);
                    _creature->MonsterWhisper("Your Companion has been added.", pPlayer->GetGUID());
					return true;
                }
                else 
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("You dont have enough Vote Tokens.", pPlayer->GetGUID());
                    return false;
                }
                break;




				case 11: // Hippo vote tokens
                if (pPlayer->HasItemCount(TOKEN_ID, 25, true))
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->AddItem(23713, 1);
					pPlayer->DestroyItemCount(TOKEN_ID, 25, true);
                    _creature->MonsterWhisper("Your Companion has been added.", pPlayer->GetGUID());
					return true;
                }
                else 
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    _creature->MonsterWhisper("You dont have enough Vote Tokens.", pPlayer->GetGUID());
                    return false;
                }
                break;
		}

	}


return true;
}
};

void AddSC_vote_NPC()
{
    new vote_NPC();
}