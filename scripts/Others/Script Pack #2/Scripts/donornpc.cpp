#include "ScriptPCH.h"
#include <cstring>
#include "ObjectMgr.h"


class donorrewarder : public CreatureScript
{
    public:

        donorrewarder()
            : CreatureScript("donorrewarder")
        {
        }

        void RewardItem(Player* player, Creature* pCreature, int item , int count, int cost)
        {
                char str[200];

                if (!player->HasItemCount(37711, cost, true))
                {
                     sprintf(str,"You don't have enough points for this item, you must donate on www.unforgivenwow.com!");
                     player->MonsterWhisper(str,player->GetGUID(),true);
                }
                else
                {
                    if (player->AddItem(item, count))
                    {
  			   std::string DateTime = "%Y-%m-%d %H:%M:%S";
			   ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(item);
                        player->DestroyItemCount(37711, cost, true);
                        LoginDatabase.PQuery("INSERT INTO realmd.donation_purchases (account_id, character_name, character_guid, donation_item_id, donation_item_name, donation_item_amount, date) VALUES ('%u', '%s', '%u', '%u', '%s', '%u', DATE_FORMAT(date, '%s'))", player->GetSession()->GetAccountId(), player->GetName(), player->GetGUIDLow(), item, itemTemplate->Name1.c_str(), count, DateTime.c_str());
                        sprintf(str,"Your points are taken and your item is given!!!");
                        player->MonsterWhisper(str,player->GetGUID(),true);
			   player->SaveToDB();
                    }
                    else
                    {
                        sprintf(str,"Item can't be given maybe your bag is full or you already got the item!");
                        player->MonsterWhisper(str,player->GetGUID(),true);
                    }

                }

            player->PlayerTalkClass->ClearMenus();
            OnGossipHello(player, pCreature);
        }

bool HasCheatCooldown(Player* player)
{
	QueryResult result = CharacterDatabase.PQuery("SELECT * FROM character_cooldown WHERE guid = '%u' AND cooldown=1", player->GetGUIDLow());
	if(result)
		return true;
	return false;
}
bool HasCheatCasttime(Player* player)
{
	QueryResult result = CharacterDatabase.PQuery("SELECT * FROM character_casttime WHERE guid = '%u' AND casttime=1", player->GetGUIDLow());
	if(result)
		return true;
	return false;
}
bool HasCheatPower(Player* player)
{
	QueryResult result = CharacterDatabase.PQuery("SELECT * FROM character_cheatpower WHERE guid = '%u' AND cheatpower=1", player->GetGUIDLow());
	if(result)
		return true;
	return false;
}

        bool OnGossipHello(Player* player, Creature* pCreature)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Get a preview of the donor items", GOSSIP_SENDER_MAIN, 9998);
	     player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "NEW: Cheats", GOSSIP_SENDER_MAIN, 5400);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donor Weapons", GOSSIP_SENDER_MAIN, 2000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Rings/Trinkets/Amulets", GOSSIP_SENDER_MAIN, 3000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Armors", GOSSIP_SENDER_MAIN, 300);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "FROSTMOURNE - 50 DP", GOSSIP_SENDER_MAIN, 9997);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Special Items", GOSSIP_SENDER_MAIN, 5000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Special Tokens", GOSSIP_SENDER_MAIN, 4000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donor Shirts - 15 DP", GOSSIP_SENDER_MAIN, 10000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donor Talisman - 30 DP", GOSSIP_SENDER_MAIN, 11000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donor Set - 100 DP", GOSSIP_SENDER_MAIN, 12000);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Invincible Offset - 35 DP", GOSSIP_SENDER_MAIN, 305);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Emblem of Voting x2 - 1 DP", GOSSIP_SENDER_MAIN, 4005);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Unforgiven Gems 5 DP - 3 Gems", GOSSIP_SENDER_MAIN, 5100);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Portable Mailbox - 10 DP", GOSSIP_SENDER_MAIN, 5200);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Multi Vendor - 10 DP", GOSSIP_SENDER_MAIN, 5300);

            player->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* player, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (uiAction)
            {
            case 5400:
                player->PlayerTalkClass->ClearMenus();
		  if(!HasCheatCooldown(player))
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Cooldown Cheat - 15 DP", GOSSIP_SENDER_MAIN, 5401);
		  if(!HasCheatCasttime(player))
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Casttime Cheat - 15 DP", GOSSIP_SENDER_MAIN, 5402);
		  if(!HasCheatPower(player))
                	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Power Cheat - 10 DP", GOSSIP_SENDER_MAIN, 5403);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 5401:
		RewardItem(player, pCreature,24,1,15);
		break;
            case 5402:
		RewardItem(player, pCreature,25,1,15);
		break;
            case 5403:
		RewardItem(player, pCreature,26,1,10);
		break;
            case 5200:
		RewardItem(player, pCreature,40768,1,10);
		break;
	     case 5300:
		RewardItem(player, pCreature,37298,1,10);
		break;
            case 5100:
		RewardItem(player, pCreature,29765,3,5);
		break;
            case 300:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Cloak - 15 DP", GOSSIP_SENDER_MAIN, 301);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Tabard - 20 DP", GOSSIP_SENDER_MAIN, 302);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Bag - 5 DP", GOSSIP_SENDER_MAIN, 303);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Quiver - 5 DP", GOSSIP_SENDER_MAIN, 1303);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Shield - 15 DP", GOSSIP_SENDER_MAIN, 304);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 1303:
                if(player->getClass() != CLASS_HUNTER) {
		  char str[200];
		  sprintf(str,"Your not a Hunter, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature,7278,1,10);
                player->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 12:
		RewardItem(player, pCreature,24368,1,20);
		break;
            case 301:
                RewardItem(player, pCreature,21394,1,15);
                break;
            case 302:
                RewardItem(player, pCreature,20131,1,20);
                break;
            case 303:
                RewardItem(player, pCreature,20400,1,5);
                break;
            case 304:
                RewardItem(player, pCreature,34185,1,15);
                break;
	     case 305: // invincible off set
		  switch(player->getClass())
		  {
		  case CLASS_WARRIOR:
                RewardItem(player, pCreature, 66073,1,35);
   		  break;
		  case CLASS_PALADIN:
                RewardItem(player, pCreature, 66077,1,35);
     		  break;
		  case CLASS_HUNTER:
                RewardItem(player, pCreature, 66071,1,35);
	         break;
		  case CLASS_ROGUE:
                RewardItem(player, pCreature, 66072,1,35);
 	         break;
	 	  case CLASS_PRIEST:
                RewardItem(player, pCreature, 66074,1,35);
       	  break;
		  case CLASS_DEATH_KNIGHT:
                RewardItem(player, pCreature, 66070,1,35);
      	         break;
		  case CLASS_SHAMAN:
                RewardItem(player, pCreature, 66078,1,35);
      	 	  break;
		  case CLASS_MAGE:
                RewardItem(player, pCreature, 66079,1,35);
       	  break;
		  case CLASS_WARLOCK:
                RewardItem(player, pCreature, 66076,1,35);
        	  break;
		  case CLASS_DRUID:
                RewardItem(player, pCreature, 66075,1,35);
                break;

		  default: break;
		  }
		  break;
            case 1000:
                RewardItem(player, pCreature, 0, 0, 0);
                break;
            case 2000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "One-Handed Weapons", GOSSIP_SENDER_MAIN, 2001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Two-Handed Weapons", GOSSIP_SENDER_MAIN, 2002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Staves", GOSSIP_SENDER_MAIN, 2003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ranged", GOSSIP_SENDER_MAIN, 2004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Off-Hand Weapons", GOSSIP_SENDER_MAIN, 2005);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Main-Hand Weapons", GOSSIP_SENDER_MAIN, 2006);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 2001:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Sword - 15 DP", GOSSIP_SENDER_MAIN, 2101);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Dagger - 15 DP", GOSSIP_SENDER_MAIN, 2102);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Axe - 15 DP", GOSSIP_SENDER_MAIN, 2103);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Mace - 15 DP", GOSSIP_SENDER_MAIN, 2103);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 2101:
                RewardItem(player, pCreature,50672,1,15);
                break;
            case 2102:
                if(player->getClass() != CLASS_ROGUE) {
		  char str[200];
		  sprintf(str,"Your not a Rogue, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature,32044,1,15);
		  }
                break;
            case 2103:
                RewardItem(player, pCreature,50759,1,15);
                break;
            case 2104:
                RewardItem(player, pCreature,46017,1,15);
                break;
            case 2002:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Two-Hand Sword - 30 DP", GOSSIP_SENDER_MAIN, 2201);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Two-Hand Axe - 30 DP", GOSSIP_SENDER_MAIN, 2202);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Two-Hand Mace - 30 DP", GOSSIP_SENDER_MAIN, 2203);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Hunters Two-Hand Polearm - 30 DP", GOSSIP_SENDER_MAIN, 2204);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 2201:
                RewardItem(player, pCreature,50761,1,30);
                break;
            case 2202:
                RewardItem(player, pCreature,49623,1,30);
                break;
            case 2203:
                RewardItem(player, pCreature,33663,1,30);
		  break;
            case 2204:
                if(player->getClass() != CLASS_HUNTER) {
		  char str[200];
		  sprintf(str,"Your not a Hunter, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature,50425,1,30);
                player->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2003:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Staff - 20 DP", GOSSIP_SENDER_MAIN, 2301);
		  player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Feral Staff - 20 DP", GOSSIP_SENDER_MAIN, 2302);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 2301:
                if(player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_HUNTER) {
		  char str[200];
		  sprintf(str,"Your not a Caster, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature,54806,1,20);
                player->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2302:
                if(player->getClass() != CLASS_DRUID) {
		  char str[200];
		  sprintf(str,"Your not a Druid, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature,40348,1,20);
                player->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2004:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Bow - 15 DP", GOSSIP_SENDER_MAIN, 2401);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Gun - 15 DP", GOSSIP_SENDER_MAIN, 2402);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Wand - 15 DP", GOSSIP_SENDER_MAIN, 2403);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 2401:
                RewardItem(player, pCreature,34334,1,15);
                break;
            case 2402:
                RewardItem(player, pCreature,51450,1,15);
                break;
            case 2403:
                if(player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_HUNTER) {
		  char str[200];
		  sprintf(str,"Your not a Caster, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature,37177,1,15);
                player->PlayerTalkClass->SendCloseGossip();
		  }
                break;
            case 2005:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Warglaive (Off Hand) - 20 DP", GOSSIP_SENDER_MAIN, 2501);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Fist (Off Hand) - 15 DP", GOSSIP_SENDER_MAIN, 2502);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 2501:
                RewardItem(player, pCreature, 1951,1,20);
                break;
            case 2502:
                RewardItem(player, pCreature, 34203,1,15);
                break;
            case 2006:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Warglaive (Main Hand) - 20 DP", GOSSIP_SENDER_MAIN, 2601);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Fist (Main Hand) - 15 DP", GOSSIP_SENDER_MAIN, 2602);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 2601:
                RewardItem(player, pCreature, 1469,1,20);
                break;
            case 2602:
                RewardItem(player, pCreature, 34331,1,15);
                break;
            case 3000:
                player->PlayerTalkClass->ClearMenus();                
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Ancient Box - 30 DP", GOSSIP_SENDER_MAIN, 3001);
		  if (player->GetTeam() == HORDE)
		  {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Medallion of the Horde - 20 DP", GOSSIP_SENDER_MAIN, 3002);
		  } else {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Medallion of the Alliance - 20 DP", GOSSIP_SENDER_MAIN, 3012);
		  }
		  if(player->getClass() == CLASS_ROGUE)
		  {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Necklace of the Assassin - 20 DP", GOSSIP_SENDER_MAIN, 3004);
		  }
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Card Destruction (melee) - 20 DP", GOSSIP_SENDER_MAIN, 3003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Card Judgement (spell) - 20 DP", GOSSIP_SENDER_MAIN, 3015);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Trinket of the Comet - 15 DP", GOSSIP_SENDER_MAIN, 3005);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 3001:
                RewardItem(player, pCreature, 4632,1,30);
                break;
            case 3002:
                RewardItem(player, pCreature, 42126,1,20);
                break;
            case 3003:
                RewardItem(player, pCreature, 42989,1,20);
                break;
            case 3004:
                RewardItem(player, pCreature, 39246,1,20);
                break;
            case 3005:
                RewardItem(player, pCreature, 19336,1,20);
                break;
            case 3012:
                RewardItem(player, pCreature, 38589,1,20);
                break;
  	     case 3013:
		  RewardItem(player, pCreature, 45609,1,15);
		  break;
  	     case 3015:
		  RewardItem(player, pCreature, 19288,1,20);
		  break;
            case 4000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Faction Change Token - 5 DP", GOSSIP_SENDER_MAIN, 4001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Race Change Token - 5 DP", GOSSIP_SENDER_MAIN, 14002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Name Change Token - 5 DP", GOSSIP_SENDER_MAIN, 4002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Re-Customize Token - 5 DP", GOSSIP_SENDER_MAIN, 4003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Max Level - 5 DP", GOSSIP_SENDER_MAIN, 4009);
		  player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Levelup Token x255 - 5 DP", GOSSIP_SENDER_MAIN, 5040);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "200 Event Coins - 5 DP", GOSSIP_SENDER_MAIN, 4004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Berserk Token x25 - 5 DP", GOSSIP_SENDER_MAIN, 4006);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Honor Booster x5 - 5 DP", GOSSIP_SENDER_MAIN, 4007);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Shadowmourne Visual - 10 DP", GOSSIP_SENDER_MAIN, 14010);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "V.I.P Rank - 80 DP", GOSSIP_SENDER_MAIN, 4008);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Arena Token - 10 DP", GOSSIP_SENDER_MAIN, 4028);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Group Summoning Token - 10 DP", GOSSIP_SENDER_MAIN, 4029);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Temporary Item Token x2 - 1 DP", GOSSIP_SENDER_MAIN, 4030);
		  player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "Custom Enchant Token - 7 DP", GOSSIP_SENDER_MAIN, 4031);
		  player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT,  "Friendlystep - 8 DP", GOSSIP_SENDER_MAIN, 4032);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
	     case 4032:
		  RewardItem(player, pCreature, 985410,1,8);
		  break;
	     case 4031:
		  RewardItem(player, pCreature, 41596,1,7);
		  break;
            case 5040:
                RewardItem(player, pCreature, 44728,255,5);
                break;
            case 4030:
                RewardItem(player, pCreature, 9850100,2,1);
                break;
            case 4038:
                RewardItem(player, pCreature, 29435,1,12);
                break;
            case 4029:
                RewardItem(player, pCreature, 190,1,10);
                break;
            case 4028:
                RewardItem(player, pCreature, 29436,1,10);
                break;
  	     case 14002:
		  RewardItem(player, pCreature, 81,1,5);
		  break;
	     case 14010:
		  RewardItem(player, pCreature, 133337,1,10);
		  break;
            case 4001:
                RewardItem(player, pCreature, 5,1,5);
                break;
            case 4002:
                RewardItem(player, pCreature, 6,1,5);
                break;
            case 4003:
                RewardItem(player, pCreature, 1,1,5);
                break;
            case 4004:
                RewardItem(player, pCreature, 16,1,5);
                break;
            case 4005:
                RewardItem(player, pCreature, 40753,2,1);
                break;
            case 4006:
                RewardItem(player, pCreature, 31,25,5);
                break;
            case 4007:
                RewardItem(player, pCreature, 44115,5,10);
                break;
            case 4008:
                RewardItem(player, pCreature, 22,1,80);
                break;
            case 4009:
                RewardItem(player, pCreature, 7,1,5);
                break;
            case 4010:
                RewardItem(player, pCreature, 11,1,10);
                break;
            case 5000:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Idol - 15 DP", GOSSIP_SENDER_MAIN, 5001);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Thrown - 15 DP", GOSSIP_SENDER_MAIN, 5002);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Totem - 15 DP", GOSSIP_SENDER_MAIN, 5003);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Sigil - 15 DP", GOSSIP_SENDER_MAIN, 5004);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Donors Libram - 15 DP", GOSSIP_SENDER_MAIN, 5005);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "[Main Menu]", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
            case 5001:
                if(player->getClass() != CLASS_DRUID) {
		  char str[200];
		  sprintf(str,"Your not a Druid, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature, 50456,1,15);
		  } 
                break;
            case 5002:
                if(player->getClass() != CLASS_ROGUE) {
		  char str[200];
		  sprintf(str,"Your not a Rogue, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature, 30025,1,15);
		  } 
                break;
            case 5003:
                if(player->getClass() != CLASS_SHAMAN) {
		  char str[200];
		  sprintf(str,"Your not a Shaman, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature, 45169,1,15);
		  } 
                break;
            case 5004:
                if(player->getClass() != 6) {
		  char str[200];
		  sprintf(str,"Your not a Death Knight, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature, 45144,1,15);
		  } 
                break;
            case 5005:
                if(player->getClass() != CLASS_PALADIN) {
		  char str[200];
		  sprintf(str,"Your not a Paladin, so you cant buy this item!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature, 50461,1,15);
		  } 
                break;
            case 5006:
                RewardItem(player, pCreature, 4633,1,2);
                break;
	     case 10000:
		  switch(player->getClass())
		  {
		  case CLASS_WARRIOR:
                RewardItem(player, pCreature, 61009,1,15);
   		  break;
		  case CLASS_PALADIN:
                RewardItem(player, pCreature, 61007,1,15);
     		  break;
		  case CLASS_HUNTER:
                RewardItem(player, pCreature, 63005,1,15);
	         break;
		  case CLASS_ROGUE:
                RewardItem(player, pCreature, 61004,1,15);
 	         break;
	 	  case CLASS_PRIEST:
                RewardItem(player, pCreature, 61010,1,15);
       	  break;
		  case CLASS_DEATH_KNIGHT:
                RewardItem(player, pCreature, 61006,1,15);
      	         break;
		  case CLASS_SHAMAN:
                RewardItem(player, pCreature, 61001,1,15);
      	 	  break;
		  case CLASS_MAGE:
                RewardItem(player, pCreature, 61008,1,15);
       	  break;
		  case CLASS_WARLOCK:
                RewardItem(player, pCreature, 61003,1,15);
        	  break;
		  case CLASS_DRUID:
                RewardItem(player, pCreature, 61000,1,15);
                break;

		  default: break;
		  }
		  break;
	     case 11000: // donors talisman
		  switch(player->getClass())
		  {
		  case CLASS_WARRIOR:
                RewardItem(player, pCreature, 32485,1,30);
   		  break;
		  case CLASS_PALADIN:
                RewardItem(player, pCreature, 32489,1,30);
     		  break;
		  case CLASS_HUNTER:
                RewardItem(player, pCreature, 32487,1,30);
	         break;
		  case CLASS_ROGUE:
                RewardItem(player, pCreature, 32492,1,30);
 	         break;
	 	  case CLASS_PRIEST:
                RewardItem(player, pCreature, 32490,1,30);
       	  break;
		  case CLASS_DEATH_KNIGHT:
                RewardItem(player, pCreature, 21670,1,30);
      	         break;
		  case CLASS_SHAMAN:
                RewardItem(player, pCreature, 32491,1,30);
      	 	  break;
		  case CLASS_MAGE:
                RewardItem(player, pCreature, 32488,1,30);
       	  break;
		  case CLASS_WARLOCK:
                RewardItem(player, pCreature, 32493,1,30);
        	  break;
		  case CLASS_DRUID:
                RewardItem(player, pCreature, 32486,1,30);
                break;

		  default: break;
		  }
		  break;
	     case 12000: // donors set
		  switch(player->getClass())
		  {
		  case CLASS_WARRIOR:
                RewardItem(player, pCreature, 65073,1,100);
   		  break;
		  case CLASS_PALADIN:
                RewardItem(player, pCreature, 65077,1,100);
     		  break;
		  case CLASS_HUNTER:
                RewardItem(player, pCreature, 65071,1,100);
	         break;
		  case CLASS_ROGUE:
                RewardItem(player, pCreature, 65072,1,100);
 	         break;
	 	  case CLASS_PRIEST:
                RewardItem(player, pCreature, 65074,1,100);
       	  break;
		  case CLASS_DEATH_KNIGHT:
                RewardItem(player, pCreature, 65070,1,100);
      	         break;
		  case CLASS_SHAMAN:
                RewardItem(player, pCreature, 65078,1,100);
      	 	  break;
		  case CLASS_MAGE:
                RewardItem(player, pCreature, 65079,1,100);
       	  break;
		  case CLASS_WARLOCK:
                RewardItem(player, pCreature, 65076,1,100);
        	  break;
		  case CLASS_DRUID:
                RewardItem(player, pCreature, 65075,1,100);
                break;

		  default: break;
		  }
		  break;
	     case 9997:
                player->PlayerTalkClass->ClearMenus();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Are you sure you wish to buy frostmourne?", GOSSIP_SENDER_MAIN, 9997);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Yes.", GOSSIP_SENDER_MAIN, 9996);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "No.", GOSSIP_SENDER_MAIN, 9999);
                player->PlayerTalkClass->SendGossipMenu(85002, pCreature->GetGUID());
                return true;
                break;
	     case 9996:
                if(player->HasItemCount(27769, 1))
                {
                char str[200];
                sprintf(str,"You already have a Frostmourne, so you cant buy it!");
                player->MonsterWhisper(str,player->GetGUID(),true);
                player->PlayerTalkClass->SendCloseGossip();
                } else {
                RewardItem(player, pCreature, 27769,1,50);
                player->PlayerTalkClass->SendCloseGossip();
                }
                break;
            case 9998:
                player->GetSession()->SendListInventory(pCreature->GetGUID());
                break;
            case 9999:
                player->PlayerTalkClass->ClearMenus();
                OnGossipHello(player, pCreature);
                break;
            }


            return true;
        }

};

void AddSC_donorrewarder()
{
    new donorrewarder();
}
