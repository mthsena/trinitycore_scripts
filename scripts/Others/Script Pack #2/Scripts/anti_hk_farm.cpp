// Might've holes, someone look at it.
#include "ScriptPCH.h"

class anti_hk_farm : public PlayerScript
{
public: anti_hk_farm() : PlayerScript("anti_hk_farm") {}

void OnPVPKill(Player * killer, Player * killed)
{
  if (killer->GetGUID() == killed->GetGUID())
  {
		return;
	}
	if (killer->GetSession()->GetRemoteAddress() == killed->GetSession()->GetRemoteAddress() || killed->GetMaxHealth() < 10000)
	{
		uint32 Warning = 1;
		std::string Acc;
		std::string Char = killer->GetName();
		std::string str = "";
		str = "" + std::string(killer->GetName()) + ", might be a honorable kill farmer.";
		WorldPacket data(SMSG_NOTIFICATION, (str.size()+1));
		data << str;
		sWorld->SendGlobalGMMessage(&data); 
	}
	else
	{
		return;
		}
	}

	
	


    };
     
    void AddSC_anti_hk_farm()
    {
        new anti_hk_farm;
    }
