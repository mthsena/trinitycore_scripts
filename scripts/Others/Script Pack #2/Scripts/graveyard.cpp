#include "ScriptPCH.h"
#include "Chat.h"
 
class graveyard : public PlayerScript
{
public:
   graveyard() : PlayerScript("graveyard") {}
 
   void OnPlayerKilledByCreature(Creature* killer, Player* killed)
   {
   if (!killed) 
	return;

          if (killed->GetMapId() == 13)
          {
    		   killed->CombatStop();
                 ChatHandler(killed).PSendSysMessage("You died, but your spirit lived on. You are as a punishment unable to act for 45 seconds.");
                 killed->TeleportTo(13, -333.884430f, -50.475521f, 626.97370f, 1.489797);
		   killer->MonsterYell("Another foolish mortal has been slain!", LANG_UNIVERSAL, NULL);
          }

          if (killer->GetEntry() == 986507)
          {
    		   killed->CombatStop();
	 	   killed->TeleportTo(34, 5541.770020f, -3783.469971f, 1594.910034f, 2.883010f);
	 	   killed->CastSpell(killed, 42354, true);
	 	   ChatHandler(killed).PSendSysMessage("You have died, and Dante has bound your soul for 45 seconds.");
    	   }

          if (killed->GetAreaId() == 255)
          {
                 ChatHandler(killed).PSendSysMessage("Emeth has destroyed your soul, you have been banished for 45 seconds.");
		   killer->MonsterYell("Another foolish mortal has been slain!", LANG_UNIVERSAL, NULL);
          }
   }
};
 
void AddSC_graveyard()
{
   new graveyard();
}