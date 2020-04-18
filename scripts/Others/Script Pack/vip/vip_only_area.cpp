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
 - Complete: 90
 - ScriptName: 'VIP_AREA' 
 - Comment: N/A
<--------------------------------------------------------------------------->
*/

#include "ScriptPCH.h"

    class VIP_AREA : public PlayerScript 
    {
            public:
            VIP_AREA() : PlayerScript("VIP_AREA") { }
     
			void VIPZONE(Player * me, ChatHandler * handler)       
			{
				if(me->GetAreaId() == 10)
                
					switch(me->GetSession()->GetSecurity())
						{
							case SEC_PLAYER:
								{
									handler->PSendSysMessage("Welcome to the VIP Zone");
									me->TeleportTo(571, 6182.615234f, 5738.993652f, 1.402846f, 5.567000f); // Where you get teleported.
									return;
								}	
							case 1:
								{
									handler->PSendSysMessage("Welcome to the VIP Zone %s!"), me->GetName();
									return;
								}
							default:
								{
									return;
								}
						}
			}
	
	};
 
void AddSC_VIP_AREA()
{
    new VIP_AREA();
}