#include "ScriptPCH.h"
class Talent_Chooser : public CreatureScript
{
public:
  Talent_Chooser()
   : CreatureScript("Talent_Chooser")
  {
  }

  bool OnGossipHello(Player * pPlayer, Creature * pCreature)
  {
   switch(pPlayer->getClass())
   {
   case CLASS_PALADIN:
        //Paladin
        pPlayer->ADD_GOSSIP_ITEM(4, "Retribution", GOSSIP_SENDER_MAIN, 0);
        pPlayer->ADD_GOSSIP_ITEM(4, "Holy", GOSSIP_SENDER_MAIN, 1);
        pPlayer->ADD_GOSSIP_ITEM(4, "Protection", GOSSIP_SENDER_MAIN, 2);
	 pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
   break;
  
   case CLASS_HUNTER:
        //Hunter
        pPlayer->ADD_GOSSIP_ITEM(4, "Marksmanpship", GOSSIP_SENDER_MAIN, 3);
        pPlayer->ADD_GOSSIP_ITEM(4, "Survival", GOSSIP_SENDER_MAIN, 4);
        pPlayer->ADD_GOSSIP_ITEM(4, "Beast Mastery", GOSSIP_SENDER_MAIN, 5);
	 pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
   break;

   case CLASS_ROGUE:
        //Rogue
        pPlayer->ADD_GOSSIP_ITEM(4, "Assassination", GOSSIP_SENDER_MAIN, 6);
        pPlayer->ADD_GOSSIP_ITEM(4, "Combat", GOSSIP_SENDER_MAIN, 7);
        pPlayer->ADD_GOSSIP_ITEM(4, "Subtlety", GOSSIP_SENDER_MAIN, 8);
	 pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
   break;

   case CLASS_PRIEST:
        //Priest
        pPlayer->ADD_GOSSIP_ITEM(4, "Shadow", GOSSIP_SENDER_MAIN, 9);
        pPlayer->ADD_GOSSIP_ITEM(4, "Holy", GOSSIP_SENDER_MAIN, 10);
        pPlayer->ADD_GOSSIP_ITEM(4, "Disciplin", GOSSIP_SENDER_MAIN, 11);
	 pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
   break;

   case CLASS_WARLOCK:
        //Warlock
        pPlayer->ADD_GOSSIP_ITEM(4, "Affliction", GOSSIP_SENDER_MAIN, 12);
        pPlayer->ADD_GOSSIP_ITEM(4, "Demonology", GOSSIP_SENDER_MAIN, 13);
        pPlayer->ADD_GOSSIP_ITEM(4, "Destruction", GOSSIP_SENDER_MAIN, 14);
	 pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
   break;

   case CLASS_SHAMAN:
        //Shaman
        pPlayer->ADD_GOSSIP_ITEM(4, "Enhancement", GOSSIP_SENDER_MAIN, 15);
        pPlayer->ADD_GOSSIP_ITEM(4, "Elemental", GOSSIP_SENDER_MAIN, 16);
        pPlayer->ADD_GOSSIP_ITEM(4, "Restoration", GOSSIP_SENDER_MAIN, 17);
	 pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
   break;

   case CLASS_WARRIOR:
        //Warrior
        pPlayer->ADD_GOSSIP_ITEM(4, "Arms", GOSSIP_SENDER_MAIN, 18);
        pPlayer->ADD_GOSSIP_ITEM(4, "Protection", GOSSIP_SENDER_MAIN, 19);
        pPlayer->ADD_GOSSIP_ITEM(4, "Fury", GOSSIP_SENDER_MAIN, 20);
	 pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
   break;

   case CLASS_DRUID:
        //Druid
        pPlayer->ADD_GOSSIP_ITEM(4, "Feral", GOSSIP_SENDER_MAIN, 21);
        pPlayer->ADD_GOSSIP_ITEM(4, "Balance", GOSSIP_SENDER_MAIN, 22);
        pPlayer->ADD_GOSSIP_ITEM(4, "Restoration", GOSSIP_SENDER_MAIN, 23);
	 pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
   break;

   case CLASS_MAGE:
        //Mage
        pPlayer->ADD_GOSSIP_ITEM(4, "Frost", GOSSIP_SENDER_MAIN, 24);
        pPlayer->ADD_GOSSIP_ITEM(4, "Fire", GOSSIP_SENDER_MAIN, 25);
        pPlayer->ADD_GOSSIP_ITEM(4, "Arcane", GOSSIP_SENDER_MAIN, 26);
	 pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
   break;

  default: break;
  }
  	return true;
  }

  bool OnGossipSelect(Player * player, Pet * pet, Creature * creature, uint32, uint32 uiAction)
  {
   switch(uiAction)
   {
        //Paladin
        case 0:
          player->removeSpell(19939, false);
          player->removeSpell(20166, false);
          player->removeSpell(26573, false);
          player->learnSpell(20066, false);
          player->learnSpell(35395, false);
          break;
        case 1:
          player->removeSpell(26573, false);
          player->removeSpell(35395, false);
          player->removeSpell(20066, false);
          player->learnSpell(19939, false);
          player->learnSpell(20166, false);
          break;
        case 2:
          player->removeSpell(19939, false);
          player->removeSpell(20166, false);
          player->removeSpell(35395, false);
          player->removeSpell(20066, false);
          player->learnSpell(26573, false);
          break;
  
        //Hunter
        case 3:
          player->removeSpell(34026, false);
          player->removeSpell(19503, false);
          player->removeSpell(19577, false);
          player->learnSpell(19424, false);
          break;
        case 4:
          player->removeSpell(34026, false);
          player->removeSpell(19424, false);
          player->removeSpell(19577, false);
          player->learnSpell(19503, false);
          break;
        case 5:
          player->removeSpell(19503, false);
          player->removeSpell(19424, false);
          player->learnSpell(34026, false);
          player->learnSpell(19577, false);
          break;
        //Rogue
        case 6:
          player->removeSpell(36554, false);
          player->removeSpell(13877, false);
          player->removeSpell(13750, false);
          player->learnSpell(1329, false);
          break;
        case 7:
          player->removeSpell(36554, false);
          player->removeSpell(1329, false);
          player->learnSpell(13877, false);
          player->learnSpell(13750, false);
          break;
        case 8:
          player->removeSpell(13877, false);
          player->removeSpell(1329, false);
          player->removeSpell(13750, false);
          player->learnSpell(36554, false);
          break;
        //Priest
        case 9:
          player->removeSpell(19236, false);
          player->removeSpell(47788, false);
          player->removeSpell(10060, false);
          player->removeSpell(33206, false);
          player->learnSpell(2944, false);
          player->learnSpell(15473, false);
          break;
        case 10:
          player->removeSpell(2944, false);
          player->removeSpell(15473, false);
          player->removeSpell(10060, false);
          player->removeSpell(33206, false);
          player->learnSpell(19236, false);
          player->learnSpell(47788, false);
          break;
        case 11:
          player->removeSpell(19236, false);
          player->removeSpell(47788, false);
          player->removeSpell(2944, false);
          player->removeSpell(15473, false);
          player->learnSpell(10060, false);
          player->learnSpell(33206, false);
          break;
        //Warlock
        case 12:
          player->removeSpell(17919, false);
          player->removeSpell(47260, false);
          player->removeSpell(17962, false);
          player->removeSpell(19028, false);
          player->removeSpell(30146, false);
          pet->removeSpell(30151, false);
          pet->removeSpell(30213, false);
          player->learnSpell(18223, false);
          player->learnSpell(32385, false);
          player->learnSpell(709, false);
          break;
        case 13:
          player->removeSpell(18223, false);
          player->removeSpell(32385, false);
          player->removeSpell(709, false);
          player->removeSpell(17919, false);
          player->removeSpell(47260, false);
          player->removeSpell(17962, false);
          player->learnSpell(19028, false);
          player->learnSpell(30146, false);
          pet->learnSpell(30151);
          pet->learnSpell(30213);
          break;
        case 14:
          player->removeSpell(19028, false);
          player->removeSpell(30146, false);
          pet->removeSpell(30151, false);
          pet->removeSpell(30213, false);
          player->removeSpell(17919, false);
          player->removeSpell(47260, false);
          player->removeSpell(17962, false);
          player->learnSpell(17919, false);
          player->learnSpell(47260, false);
          player->learnSpell(17962, false);
          break;
        //Shaman
        case 15:
          player->removeSpell(3738, false);
          player->removeSpell(421, false);
          player->removeSpell(974, false);
          player->removeSpell(8004, false);
          player->learnSpell(8232, false);
          player->learnSpell(674, false);
          player->learnSpell(51532, false);
          break;
        case 16:
          player->removeSpell(8232, false);
          player->removeSpell(674, false);
          player->removeSpell(51532, false);
          player->removeSpell(974, false);
          player->removeSpell(8004, false);
          player->learnSpell(3738, false);
          player->learnSpell(421, false);
          break;
        case 17:
          player->removeSpell(8232, false);
          player->removeSpell(674, false);
          player->removeSpell(51532, false);
          player->removeSpell(3738, false);
          player->removeSpell(421, false);
          player->learnSpell(974, false);
          player->learnSpell(8004, false);
          break;
        //Warrior
        case 18:
          player->removeSpell(871, false);
          player->removeSpell(12809, false);
          player->removeSpell(674, false);
          player->removeSpell(23881, false);
          player->removeSpell(20252, false);
          player->learnSpell(12294, false);
          break;
        case 19:
          player->removeSpell(12294, false);
          player->removeSpell(674, false);
          player->removeSpell(23881, false);
          player->removeSpell(20252, false);
          player->learnSpell(871, false);
          player->learnSpell(12809, false);
          break;
        case 20:
          player->removeSpell(12294, false);
          player->removeSpell(23881, false);
          player->removeSpell(20252, false);
          player->learnSpell(674, false);
          player->learnSpell(23881, false);
          player->learnSpell(20252, false);
          break;
        //Druid
        case 21:
          player->removeSpell(5570, false);
          player->removeSpell(33891, false);
          player->removeSpell(29166, false);
          player->learnSpell(16979, false);
          player->learnSpell(1082, false);
          player->learnSpell(768, false);
          player->learnSpell(1850, false);
          player->learnSpell(5215, false);
          break;
        case 22:
          player->removeSpell(33891, false);
          player->removeSpell(29166, false);
          player->removeSpell(16979, false);
          player->removeSpell(1082, false);
          player->removeSpell(768, false);
          player->removeSpell(1850, false);
          player->removeSpell(5215, false);
          player->learnSpell(5570, false);
          break;
        case 23:
          player->removeSpell(5570, false);
          player->removeSpell(16979, false);
          player->removeSpell(1082, false);
          player->removeSpell(768, false);
          player->removeSpell(1850, false);
          player->removeSpell(5215, false);
          player->learnSpell(33891, false);
          player->learnSpell(29166, false);
          break;
        //Mage
        case 24:
          player->removeSpell(12042, false);
          player->removeSpell(31589, false);
          player->removeSpell(54490, false);
          player->removeSpell(8444, false);
          player->removeSpell(44448, false);
          player->removeSpell(12505, false);
          player->learnSpell(120, false);
          player->learnSpell(12472, false);
          player->learnSpell(28593, false);
          break;
        case 25:
          player->removeSpell(12042, false);
          player->removeSpell(31589, false);
          player->removeSpell(54490, false);
          player->removeSpell(120, false);
          player->removeSpell(12472, false);
          player->removeSpell(28593, false);
          player->learnSpell(8444, false);
          player->learnSpell(44448, false);
          player->learnSpell(12505, false);
          break;
        case 26:
          player->removeSpell(8444, false);
          player->removeSpell(44448, false);
          player->removeSpell(12505, false);
          player->removeSpell(120, false);
          player->removeSpell(12472, false);
          player->removeSpell(28593, false);
          player->learnSpell(12042, false);
          player->learnSpell(31589, false);
          player->learnSpell(54490, false);
	   break;
   }
   return true;
  }
};
void InitializeTalent_Chooser()
{
new Talent_Chooser();
};