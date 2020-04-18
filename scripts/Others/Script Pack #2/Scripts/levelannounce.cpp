#include "ScriptPCH.h"

class custom_LevelAnnounce : public PlayerScript
{
public:
    custom_LevelAnnounce() : PlayerScript("custom_LevelAnnounce") {}

    void OnLevelChanged(Player* player, Item* item, uint8 newLevel)
    {
	 ItemPosCountVec dest;	

        switch (newLevel)
        {

           case 10:
           case 20:
           case 30:
           case 40:
           case 50:
	    player->CastSpell(player, 38186, true);
	    ChatHandler(player->GetSession()).PSendSysMessage("Your character has leveled so fast that you have earned 10 leveling souls!");
           break;

           case 60:
           case 70:
           case 80:
           case 90:
           case 100:
	    player->CastSpell(player, 38186, true);
	    ChatHandler(player->GetSession()).PSendSysMessage("Your character has leveled so fast that you have earned 25 leveling souls!");
           break;

           case 110:
           case 120:
           case 130:
           case 140:
           case 150:
	    player->CastSpell(player, 38186, true);
	    ChatHandler(player->GetSession()).PSendSysMessage("Your character has leveled so fast that you have earned 50 leveling souls!");
           break;

           case 160:
           case 170:
           case 180:
           case 190:
           case 200:
	    player->CastSpell(player, 38186, true);
	    ChatHandler(player->GetSession()).PSendSysMessage("Your character has leveled so fast that you have earned 75 leveling souls!");
           break;

           case 210:
           case 220:
           case 230:
           case 240:
	    player->CastSpell(player, 38186, true);
	    ChatHandler(player->GetSession()).PSendSysMessage("Your character has leveled so fast that you have earned 100 leveling souls!");
           break;

           default: break;
        }
        }
};

void AddSC_custom_LevelAnnounce()
{
    new custom_LevelAnnounce();
}
