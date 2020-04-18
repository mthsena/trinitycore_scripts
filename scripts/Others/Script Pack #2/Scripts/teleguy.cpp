#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"


class teleguy : public CreatureScript
{
    public:
        teleguy() : CreatureScript("teleguy") { }


    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        pPlayer->ADD_GOSSIP_ITEM(5, "К продовцам в шатрат."                   , GOSSIP_SENDER_MAIN, 1201);
        pPlayer->ADD_GOSSIP_ITEM(5, "|cffff0000[ПВП зона]|r"                   , GOSSIP_SENDER_MAIN, 1291);

		pPlayer->ADD_GOSSIP_ITEM(5, "Озеро ледяных оков"                   , GOSSIP_SENDER_MAIN, 1290);
        if ( pPlayer->GetTeam() == ALLIANCE ) 
        {
            pPlayer->ADD_GOSSIP_ITEM(5, "|cff0000FF[Дуель Зона]|r"               , GOSSIP_SENDER_MAIN, 1300);
            pPlayer->ADD_GOSSIP_ITEM(5, "Дарнасс."                         , GOSSIP_SENDER_MAIN, 1203);
            pPlayer->ADD_GOSSIP_ITEM(5, "Экзодар."                         , GOSSIP_SENDER_MAIN, 1216);
            pPlayer->ADD_GOSSIP_ITEM(5, "Штормград."                       , GOSSIP_SENDER_MAIN, 1206);
            pPlayer->ADD_GOSSIP_ITEM(5, "Стальгорн."                       , GOSSIP_SENDER_MAIN, 1224);
            pPlayer->ADD_GOSSIP_ITEM(5, "Шаттрат."                         , GOSSIP_SENDER_MAIN, 1287);
            pPlayer->ADD_GOSSIP_ITEM(5, "Даларан."                         , GOSSIP_SENDER_MAIN, 1205);
        }  
        else 
        {
            pPlayer->ADD_GOSSIP_ITEM(5, "|cff0000FF[Дуель Зона]|r"               , GOSSIP_SENDER_MAIN, 1301);
            pPlayer->ADD_GOSSIP_ITEM(5, "Оргриммар."                       , GOSSIP_SENDER_MAIN, 1215);
            pPlayer->ADD_GOSSIP_ITEM(5, "Луносвет."                        , GOSSIP_SENDER_MAIN, 1217);
            pPlayer->ADD_GOSSIP_ITEM(5, "Подгород."                        , GOSSIP_SENDER_MAIN, 1213);
            pPlayer->ADD_GOSSIP_ITEM(5, "Громовой утёс."                   , GOSSIP_SENDER_MAIN, 1225);
            pPlayer->ADD_GOSSIP_ITEM(5, "Шаттрат."                         , GOSSIP_SENDER_MAIN, 1287);
            pPlayer->ADD_GOSSIP_ITEM(5, "Даларан."                         , GOSSIP_SENDER_MAIN, 1205);
        }
    
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
        return true;
    }


    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        if(!player->getAttackers().empty())
        {
            player->CLOSE_GOSSIP_MENU();
            creature->MonsterWhisper("Вы в бою!", player->GetGUID(), true);
            return true;
        }
        

        
        switch(action)
        {
            case 1200:
               case 0: //1
               player->TeleportTo(1, -2619.429443f, -1341.416382f, 1.138281f, 0.859594f); //map, x, y , z, o
               break;
               case 1://2
               player->TeleportTo(1, -2619.429443f, -1341.416382f, 1.138281f, 0.859594f); //map, x, y , z, o
               break;
               case 2://3
               player->TeleportTo(1, -2619.429443f, -1341.416382f, 1.138281f, 0.859594f); //map, x, y , z, o
               break;
               case 3://4
               player->TeleportTo(1, -2619.429443f, -1341.416382f, 1.138281f, 0.859594f); //map, x, y , z, o
               break;
               case 4://5
               player->TeleportTo(1, -2619.429443f, -1341.416382f, 1.138281f, 0.859594f); //map, x, y , z, o
               break;
               case 5: //6
               player->TeleportTo(1, -2619.429443f, -1341.416382f, 1.138281f, 0.859594f); //map, x, y , z, o
               break;
               case 6://7
               player->TeleportTo(1, -2619.429443f, -1341.416382f, 1.138281f, 0.859594f); //map, x, y , z, o
               break;
               case 7://8
               player->TeleportTo(1, -2619.429443f, -1341.416382f, 1.138281f, 0.859594f); //map, x, y , z, o
               break;
               case 8://9
               player->TeleportTo(1, -2619.429443f, -1341.416382f, 1.138281f, 0.859594f); //map, x, y , z, o
               break;
               case 9://10
               player->TeleportTo(1, -2619.429443f, -1341.416382f, 1.138281f, 0.859594f); //map, x, y , z, o
               break;
               
                          
            case 1201: //Start location
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(530, -1810.92f, 5412.58f, -12.4277f, 0.0f);
                break;
            case 1203: // Teleport to Darnassus
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(1, 9947.52f, 2482.73f, 1316.21f, 0.0f);
                break;
            case 1206: // Teleport to Stormwind
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(0, -8960.14f, 516.266f, 96.3568f, 0.0f);
                break;

            case 1205: // Teleport to Dalaran
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(571, 5804.14f, 624.770f, 647.7670f, 1.64f);
                break;

            case 1213: // Teleport to Undercity
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(0, 1819.71f, 238.79f, 60.5321f, 0.0f);
                break;

            case 1215: // Teleport to Orgrimmar
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(1, 1552.5f, -4420.66f, 8.94802f, 0.0f);
                break;

            case 1216: // Teleport to Exodar
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(530, -4073.03f, -12020.4f, -1.47f, 0.0f);
                break;

            case 1217: // Teleport to Silvermoon
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(530, 9338.74f, -7277.27f, 13.7895f, 0.0f);
                break;

            case 1225: // Teleport to Thunder Bluff
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(1, -1280.19f,127.21f,131.35f,5.16f); 
                break;

            case 1224: // Teleport to Ironforge
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(0, -4924.07f, -951.95f, 501.55f, 5.40f);
                break;
            case 1287:// Shattrath City
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(530, -1850.209961f, 5435.821777f, -10.961435f, 3.403913f);
                break;
			case 1290:// OLO
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(571, 4605.400879f, 2848.147461f, 396.896851f, 0.244662f);
                break;
          case 1291:// мясо
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(0, -13180.426758f, 339.243744f, 42.979755f, 4.277194f);
                break;
        case 1300:// дульзона альянс
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(0, -9101.162109f, 409.645386f, 92.572105f, 3.792909f);
                break;
case 1301:// дульзона орда
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(1, 1366.901733f, -4371.698242f, 26.070211f, 3.394853f);
                break;

         }
                        
        return true;
    }
};

class npc_teleporter_country : public CreatureScript
{
public:
    npc_teleporter_country() : CreatureScript("npc_teleporter_country") { }
        
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());
                        
        if(pPlayer->GetTeam() == ALLIANCE)              
           pPlayer->ADD_GOSSIP_ITEM(9, "Телепортироваться к подножию города Штормграда"  , GOSSIP_SENDER_MAIN, 100);
        else
           pPlayer->ADD_GOSSIP_ITEM(9, "Телепортироваться к подножию города Оргриммара"  , GOSSIP_SENDER_MAIN, 101);
        
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }
        
    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        switch(uiAction)
        {
            case 100:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(0, -9111.47f, 397.90f, 92.52f, 3.79f);
            break;
                
            case 101:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(1, 1345.58f, -4376.42f, 26.17f, 3.35f);
            break;
         }
                        
        return true;
    }
};

void AddSC_teleguy()
{
    new teleguy;
    new npc_teleporter_country;
}
