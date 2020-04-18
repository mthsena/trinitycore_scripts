/* Custom Shadowhack PetGuy */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"

class petguy : public CreatureScript
{
    public: 
        petguy() : CreatureScript("petguy") { }
                
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if(pPlayer->getClass()!=CLASS_HUNTER)
        {
            pPlayer->PlayerTalkClass->SendGossipMenu(200002, pCreature->GetGUID()); //what kind pet do you need?
            return false;
        }

        if(!pPlayer->GetPet())
        {
            pPlayer->ADD_GOSSIP_ITEM( 7, "I wanna take a new pet", GOSSIP_SENDER_MAIN, 1216);
                if(pPlayer->HasAura(53270))
                    pPlayer->ADD_GOSSIP_ITEM( 7, "I wanna take an exotic pet", GOSSIP_SENDER_MAIN, 1215);
        }
        
        pPlayer->ADD_GOSSIP_ITEM( 4, "Nevermind", GOSSIP_SENDER_MAIN, 1224);
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
        return true;
    }
                
    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        uint32 pet_id=0;
        player->PlayerTalkClass->GetGossipMenu().ClearMenu();
        switch (action)
        {
            case 1215:
            {
                player->ADD_GOSSIP_ITEM( 11, "Chimera", GOSSIP_SENDER_MAIN, 1241);
                player->ADD_GOSSIP_ITEM( 11, "Core Hound", GOSSIP_SENDER_MAIN, 1243);
                player->ADD_GOSSIP_ITEM( 11, "Devasaur", GOSSIP_SENDER_MAIN, 1246);
                player->ADD_GOSSIP_ITEM( 11, "Spirit Beast", GOSSIP_SENDER_MAIN, 1247);
                player->ADD_GOSSIP_ITEM( 11, "Rhino", GOSSIP_SENDER_MAIN, 1248);
                player->ADD_GOSSIP_ITEM( 11, "Worm", GOSSIP_SENDER_MAIN, 1249);
                player->ADD_GOSSIP_ITEM( 11, "Silitid", GOSSIP_SENDER_MAIN, 1250);
                player->ADD_GOSSIP_ITEM( 4, "Nevermind", GOSSIP_SENDER_MAIN, 1224);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 1216:
            {
                player->PlayerTalkClass->SendGossipMenu(200001, creature->GetGUID()); //what kind pet do you need?
                player->ADD_GOSSIP_ITEM( 11, "Bat", GOSSIP_SENDER_MAIN, 1217);
                player->ADD_GOSSIP_ITEM( 11, "Bird of prey", GOSSIP_SENDER_MAIN, 1218);
// exotic       player->ADD_GOSSIP_ITEM( 9, "Chimera", GOSSIP_SENDER_MAIN, 1216);
                player->ADD_GOSSIP_ITEM( 11, "Dragonhawk", GOSSIP_SENDER_MAIN, 1219);
                player->ADD_GOSSIP_ITEM( 11, "Nether ray", GOSSIP_SENDER_MAIN, 1220);
                player->ADD_GOSSIP_ITEM( 11, "Ravanger", GOSSIP_SENDER_MAIN, 1221);
// exotic       player->ADD_GOSSIP_ITEM( 9, "Silitid", GOSSIP_SENDER_MAIN, 1216);
                player->ADD_GOSSIP_ITEM( 11, "Spider", GOSSIP_SENDER_MAIN, 1223);
                player->ADD_GOSSIP_ITEM( 11, "Sporebat", GOSSIP_SENDER_MAIN, 1242);
                player->ADD_GOSSIP_ITEM( 11, "Wild serpent", GOSSIP_SENDER_MAIN, 1225);
                player->ADD_GOSSIP_ITEM( 11, "Carrion bird", GOSSIP_SENDER_MAIN, 1226);
                player->ADD_GOSSIP_ITEM( 11, "Cat", GOSSIP_SENDER_MAIN, 1227);
// exotic       player->ADD_GOSSIP_ITEM( 9, "Core Hound", GOSSIP_SENDER_MAIN, 1216);
                player->ADD_GOSSIP_ITEM( 11, "Hyena", GOSSIP_SENDER_MAIN, 1228);
// exotic       player->ADD_GOSSIP_ITEM( 11, "Moth", GOSSIP_SENDER_MAIN, 1229);
                player->ADD_GOSSIP_ITEM( 11, "Raptor", GOSSIP_SENDER_MAIN, 1229);
                player->ADD_GOSSIP_ITEM( 7, "More pets?", GOSSIP_SENDER_MAIN, 1300);
                player->ADD_GOSSIP_ITEM( 4, "Nevermind", GOSSIP_SENDER_MAIN, 1224);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 1300:
            {
                player->ADD_GOSSIP_ITEM( 11, "Tallstrider", GOSSIP_SENDER_MAIN, 1230);
                // player->ADD_GOSSIP_ITEM( 11, "Wasp", GOSSIP_SENDER_MAIN, 1231);
                player->ADD_GOSSIP_ITEM( 11, "Wolf", GOSSIP_SENDER_MAIN, 1232);
                player->ADD_GOSSIP_ITEM( 11, "Bear", GOSSIP_SENDER_MAIN, 1233);
                player->ADD_GOSSIP_ITEM( 11, "Boar", GOSSIP_SENDER_MAIN, 1234);
                player->ADD_GOSSIP_ITEM( 11, "Crab", GOSSIP_SENDER_MAIN, 1235);
                player->ADD_GOSSIP_ITEM( 11, "Crocolisk", GOSSIP_SENDER_MAIN, 1236);
                player->ADD_GOSSIP_ITEM( 11, "Gorila", GOSSIP_SENDER_MAIN, 1237);
                player->ADD_GOSSIP_ITEM( 11, "Scorpid", GOSSIP_SENDER_MAIN, 1238);
                player->ADD_GOSSIP_ITEM( 11, "Turtle", GOSSIP_SENDER_MAIN, 1239);
                player->ADD_GOSSIP_ITEM( 11, "Warp stalker", GOSSIP_SENDER_MAIN, 1240);
                player->ADD_GOSSIP_ITEM( 11, "Moth", GOSSIP_SENDER_MAIN, 1244);
                player->ADD_GOSSIP_ITEM( 11, "Wasp", GOSSIP_SENDER_MAIN, 1251);
                player->ADD_GOSSIP_ITEM( 11, "Serpent", GOSSIP_SENDER_MAIN, 1252);
                player->ADD_GOSSIP_ITEM( 11, "Snowdrift Jormungar", GOSSIP_SENDER_MAIN, 1253);
                player->ADD_GOSSIP_ITEM( 7, "Back", GOSSIP_SENDER_MAIN, 1216);
                player->ADD_GOSSIP_ITEM( 4, "Nevermind", GOSSIP_SENDER_MAIN, 1224);
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                break;
            }
            case 1224:
            {
                player->CLOSE_GOSSIP_MENU();
                break;
            }
            case 1217:
            {
                pet_id=8601; 
                break; //bat
            }
            case 1218:
            {
                pet_id=1995; 
                break; //bird of pray
            }
            case 1219:
            {
                pet_id=20502; 
                break; //dragonhawk
            }
            case 1220:
            {
                pet_id=21901;
                break; //nether ray
            }
            case 1221:
            {
                pet_id=23326;
                break; //ravager
            }
            case 1223:
            {
                pet_id=11921;
                break; //spider
            }
            case 1242: 
            {
                pet_id=18129; 
                break; //sporebat
            }
            case 1225: 
            {
                pet_id=26806;
                break; //Wild serpent
            }
            case 1226: 
            {
                pet_id=5982;
                break; //Carrion bird
            }
            case 1227:
            {
                pet_id=24530; 
                break; //cat
            }
            case 1228: 
            {
                pet_id=5426; 
                break;    //hyena
            }
            case 1229: 
            {
                pet_id=20728; 
                break; //raptor
            }
            case 1230: 
            {
                pet_id=3244; 
                break; //tallstrider
            }
            case 1232:
            {
                pet_id=2753; 
                break; //wolf
            }
            case 1233: 
            {
                pet_id=8956; 
                break; //bear
            }
            case 1234:
            {
                pet_id=4511; 
                break; //boar
            }
            case 1235:
            {
                pet_id=17217; 
                break; //crab
            }
            case 1236:
            {
                pet_id=24047; 
                break; //crocolisk
            }
            case 1237: 
            {
                pet_id=1557; 
                break; //gorila
            }
            case 1238:
            {
                pet_id=3126; 
                break; //scorpid
            }
            case 1239: 
            {
                pet_id=4824; 
                break; //turtle
            }
            case 1240:
            {
                pet_id=23219; 
                break; //warp stalker
            }
            case 1243:
            {
                const uint32 pets[3]={21102, 11672, 17447};
                pet_id=pets[urand(0, 2)];
                break; // core hound
            }
            case 1246:
            {
                const uint32 pets[4]={20931, 32485, 6584, 6498};
                pet_id=pets[urand(0,3)];
                break; // Devasaur
            }
            case 1247:
            {
                const uint32 pets[4]={38453,35189,33776,32517};
                pet_id=pets[urand(0,3)];
                break; // Spirit beast
            }
            case 1244:
            {
                const uint32 pets[2]={17350, 18468};
                pet_id=pets[urand(0,1)];
                break; // Moth
            }
            case 1248:
            {
                const uint32 pets[3]={25489, 30447, 28009};
                pet_id=pets[urand(0,2)];
                break; // Rhino
            }
            case 1249:
            {
                const uint32 pets[3]={30422, 11320, 11740};
                pet_id=pets[urand(0,2)];
                break; //Worm
            }
            case 1250:
            {
                const uint32 pets[3]={8205, 6582, 4132};
                pet_id=pets[urand(0,2)];
                break; //Silitid
            }
            case 1241:
            {
                const uint32 pets[4]={12800, 11497, 21879, 20932};
                pet_id=pets[urand(0,3)];
                break; //Chimera
            }
            case 1251:
            {
                const uint32 pets[3]={28086, 28085, 18283};
                pet_id=pets[urand(0,2)];
                break; //Wasp
            }
            case 1252:
            {
                const uint32 pets[2]={11372, 28358};
                pet_id=pets[urand(0,1)];
                break; //Serpent
            }
            case 1253:
            {
                // Snowdrift Jormungar 
                pet_id = 29390;
                break;
            }
            default:break;
        }
        if(pet_id)
        {
            Creature *Pet=creature->SummonCreature(pet_id,creature->GetPositionX(),creature->GetPositionY(),creature->GetPositionZ(), 0.0f, (TempSummonType)TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 10000);
            uint8 level = player->getLevel();
            Pet->SetLevel(level);
            player->CastSpell(Pet, 13481, true);
            player->CLOSE_GOSSIP_MENU();
        }
        return true;
    }

    bool GossipSelect_petguy(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        // Main menu
        if (sender == GOSSIP_SENDER_MAIN)
        OnGossipSelect(player, _Creature, 0, action);

        return true;
    }
};

void AddSC_petguy()
{
    new petguy;
}