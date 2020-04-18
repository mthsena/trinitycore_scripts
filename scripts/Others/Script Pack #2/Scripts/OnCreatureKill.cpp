#include "ScriptPCH.h"
 
class will_of_the_sartharion : public PlayerScript
{
public:
   will_of_the_sartharion() : PlayerScript("will_of_the_sartharion") {}
 
   void OnCreatureKill(Player * killer, Creature* killed)
   {
          if (killed->GetEntry() == 39234)
          {
		char msg[250];
		snprintf(msg, 250, "|CFF7BBEF7[Emeth the Ancient]|r: I have been slain by|cffff0000 %s|r and his group... I will return within 12 hours with even greater powers and devastate the entire planet!",killer->GetName());
		sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
		killer->AddItem(92556, 1);
		ChatHandler(killer).PSendSysMessage("You have been awarded with a Skull Box for placing the last hit on Emeth!");
          }
          if (killed->GetEntry() == 986507)
          {
		char msg[250];
		snprintf(msg, 250, "|CFF7BBEF7[Dante Bloodrayne]|r: I have been slain by|cffff0000 %s|r and his group... I will return within 24 hours with even greater powers and devastate the entire planet!",killer->GetName());
		sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
		killer->AddItem(92556, 1);
		ChatHandler(killer).PSendSysMessage("You have been awarded with a Skull Box for placing the last hit on Dante!");
          }
   }
};
 
void AddSC_will_of_the_sartharion()
{
   new will_of_the_sartharion();
}