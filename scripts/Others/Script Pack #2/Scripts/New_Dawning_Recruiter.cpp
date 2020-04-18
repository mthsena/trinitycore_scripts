#include "ScriptPCH.h"

class New_Dawning_Recruiter : public CreatureScript
{
public:
	New_Dawning_Recruiter() : CreatureScript("New_Dawning_Recruiter") { }
	
	bool OnGossipHello(Player * player, Creature * creature)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Yes, I would like to help your company.", GOSSIP_SENDER_MAIN, 1);                                
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "No, I don't want to help your company.", GOSSIP_SENDER_MAIN, 2);
		player->PlayerTalkClass->SendGossipMenu(13333339, creature->GetGUID());
		return true;
	}
	
	bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
	{
		player->PlayerTalkClass->ClearMenus();
		
		switch(uiAction)
		{
		case 1: // Yes, I would like to help your company.
			player->TeleportTo(1, -2101.669434f, -3604.848633f, 60.047607f, 4.870027f);
			player->PlayerTalkClass->SendCloseGossip();
			break;

		
		case 2: // No, I don't want to help your company.
			creature->MonsterWhisper("Okay, feel free to come back if you change your mind.", player->GetGUID());
			player->PlayerTalkClass->SendCloseGossip();
			break;
		}
		return true;
	}
};
     
void AddSC_New_Dawning_Recruiter()
{
	new New_Dawning_Recruiter;
}