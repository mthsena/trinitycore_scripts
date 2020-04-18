#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"


class teleguy : public CreatureScript
{
    public:
        teleguy() : CreatureScript("teleguy") { }

    long long int money;
    int costo;

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if ( pPlayer->GetTeam() == ALLIANCE ) 
        {
            pPlayer->ADD_GOSSIP_ITEM( 5, "Stormwind. "        , GOSSIP_SENDER_MAIN, 1206);
            pPlayer->ADD_GOSSIP_ITEM( 5, "Swamp of Sorrows. "        , GOSSIP_SENDER_MAIN, 5000);
        }  
        else 
        {
            pPlayer->ADD_GOSSIP_ITEM( 5, "Duskwood. "           , GOSSIP_SENDER_MAIN, 5001);
            pPlayer->ADD_GOSSIP_ITEM( 5, "Orgrimmar."        , GOSSIP_SENDER_MAIN, 1215);
        }
    
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
        return true;
    }


    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        if(!player->getAttackers().empty())
        {
            player->CLOSE_GOSSIP_MENU();
            creature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
            return true;
        }

        if( player->getLevel() < 8  ) 
        {
            player->CLOSE_GOSSIP_MENU();
            creature->MonsterSay("You must be lvl 8+", LANG_UNIVERSAL, NULL);
            return true;
        }

        money = player->GetMoney();
        costo = 500;

        if (money < costo ) 
        {
            player->CLOSE_GOSSIP_MENU();
            creature->MonsterSay("You haven't enough money", LANG_UNIVERSAL, NULL);
            return true;
        }

        switch(action)
        {
            case 5000:  // Swamp of sorrows
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(0, -10561.3f, -1158.44f, 27.8789f, 0.0f);
                break;
            case 5001:  // Duskwood
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(0, -10441.9f, -3266.2f, 20.1782f, 0.0f);
                break;
            // Teleport to Darnassus
            case 1203:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(1, 9947.52f, 2482.73f, 1316.21f, 0.0f);
                player->ModifyMoney(-1*costo);
                break;
            // Teleport to Stormwind
            case 1206:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(0, -8960.14f, 516.266f, 96.3568f, 0.0f);
                player->ModifyMoney(-1*costo);
                break;
            // Teleport to Dalaran
            case 1205:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(571, 5804.14f, 624.770f, 647.7670f, 1.64f);
                player->ModifyMoney(-1*costo);
                break;
            // Teleport to Undercity
            case 1213:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(0, 1819.71f, 238.79f, 60.5321f, 0.0f);
                player->ModifyMoney(-1*costo);
                break;
            // Teleport to Orgrimmar
            case 1215:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(1, 1552.5f, -4420.66f, 8.94802f, 0.0f);
                player->ModifyMoney(-1*costo);
                break;
            // Teleport to Exodar
            case 1216:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(530, -4073.03f, -12020.4f, -1.47f, 0.0f);
                player->ModifyMoney(-1*costo);
                break;
            // Teleport to Silvermoon
            case 1217:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(530, 9338.74f, -7277.27f, 13.7895f, 0.0f);
                player->ModifyMoney(-1*costo);
            break;
            // Teleport player to Gnomeregan
            case 1222:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(0, -5163.43f,660.40f,348.28f,4.65f);
                player->ModifyMoney(-1*costo);
                break;
            // Teleport to Ironforge
            case 1224:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(0, -4924.07f, -951.95f, 501.55f, 5.40f);
                player->ModifyMoney(-1*costo);
                break;
            // Teleport to Thunder Bluff
            case 1225:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(1, -1280.19f,127.21f,131.35f,5.16f); 
                player->ModifyMoney(-1*costo);
                break;
            // Teleport player to Ragefire Chasm   
            case 1248: 
                if( player->getLevel() >= 8)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(1, 1800.53f,-4394.68f,-17.93f,5.49f);
                    player->ModifyMoney(-2*costo);
                } 
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 8!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Teleport player to the Wailing Caverns     
            case 1249:
                if (player->getLevel() >= 10)   
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(1, -722.53f,-2226.30f,16.94f,2.71f);
                    player->ModifyMoney(-2*costo);
                }
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                   creature->MonsterSay("You must be at least level 10!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Teleport player to the Deadmines
            case 1250:     
                if (player->getLevel() >= 10)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(0, -11212.04f,1658.58f,25.67f,1.45f);
                    player->ModifyMoney(-2*costo);
                } 
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 10!", LANG_UNIVERSAL, NULL);
                } 
            break;
            // Teleport player to Shadowfang Keep    
            case 1251:
                if (player->getLevel() >= 15)   
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(0, -254.47f,1524.68f,76.89f,1.56f);
                    player->ModifyMoney(-2*costo);
                } 
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 15!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Teleport player to Blackfathom Deeps
            case 1252:
                if (player->getLevel() >= 15)  
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(1, 4254.58f,664.74f,-29.04f,1.97f);
                    player->ModifyMoney(-2*costo);
                }
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 15!", LANG_UNIVERSAL, NULL);
                }   
                break;
            // Teleport player to the Stockade
            case 1253:
                if (player->getLevel() >= 20) 
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(0, -8769.76f,813.08f,97.63f,2.26f);
                    player->ModifyMoney(-2*costo);
                }
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 20!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Teleport player to Razorfen Kraul
            case 1254: 
                if (player->getLevel() >= 24)  
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(1, -4484.04f,-1739.40f,86.47f,1.23f);
                    player->ModifyMoney(-4*costo);
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 24!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Teleport player to Gnomeregan
            case 1255: 
                if (player->getLevel() >= 20)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(0, -5162.62f,667.81f,248.05f,1.48f);
                    player->ModifyMoney(-4*costo);
                } 
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 20!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Teleport player to Razorfen Downs
            case 1256:
                if (player->getLevel() >= 25)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(1, -4645.08f,-2470.85f,85.53f,4.39f);
                    player->ModifyMoney(-4*costo);
                } 
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 25!", LANG_UNIVERSAL, NULL);
                }
                 break;
            // Teleport player to the Scarlet Monastery
            case 1257:
                if (player->getLevel() >= 25)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(0, 2843.89f,-693.74f,139.32f,5.11f);
                    player->ModifyMoney(-4*costo);
                } 
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 25!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Teleport player to Uldaman
            case 1258:    
                if (player->getLevel() >= 35)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(0, -6119.70f,-2957.30f,204.11f,0.03f);
                    player->ModifyMoney(-6*costo);
                } 
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 35!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Teleport player to Zul'Farrak
            case 1259:
                if (player->getLevel() >= 35)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(1, -6839.39f,-2911.03f,8.87f,0.41f);
                    player->ModifyMoney(-6*costo);
                }
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 35!", LANG_UNIVERSAL, NULL);
                }   
            break;
            // Teleport player to Maraudon
            case 1260:
                if (player->getLevel() >= 40)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(1, -1433.33f,2955.34f,96.21f,4.82f);
                    player->ModifyMoney(-8*costo);
                } 
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 40!", LANG_UNIVERSAL, NULL);
                }   
                break;
            // Teleport player to the Sunken Temple
            case 1261:
                if (player->getLevel() >= 45)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(0, -10346.92f,-3851.90f,-43.41f,6.09f);
                    player->ModifyMoney(-8*costo);
                } 
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 45!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Teleport player to Blackrock Depths  
            case 1262:
                if (player->getLevel() >= 45)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(0, -7301.03f,-913.19f,165.37f,0.08f);
                    player->ModifyMoney(-8*costo);
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 45!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Teleport player to Dire Maul  
            case 1263: 
                if (player->getLevel() >= 50)   
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(1, -3982.47f,1127.79f,161.02f,0.05f);
                    player->ModifyMoney(-10*costo);
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 50!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Teleport player to Blackrock Spire   
            case 1264:
                if (player->getLevel() >= 50)   
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(0, -7535.43f,-1212.04f,285.45f,5.29f);
                    player->ModifyMoney(-10*costo);
                } 
                 else
                 {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 50!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Teleport player to Stratholme  
            case 1265:
                if (player->getLevel() >= 50)    
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(0, 3263.54f,-3379.46f,143.59f,0.00f);
                    player->ModifyMoney(-10*costo);
                } 
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 50!", LANG_UNIVERSAL, NULL);
                } 
                break;
            // Teleport player to Scholomance
            case 1266:
                if (player->getLevel() >= 50)   
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(0, 1219.01f,-2604.66f,85.61f,0.50f);
                    player->ModifyMoney(-10*costo);
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 50!", LANG_UNIVERSAL, NULL);
                }   
                break;
            // Shattrath City
            case 1287:
                if( player->getLevel() >= 58)
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(530, -1850.209961f, 5435.821777f, -10.961435f, 3.403913f);
                    player->ModifyMoney(-1*costo);
                } 
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 58!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Teleport player to Isle Of Quel'Danas
            case 1288:
                if (player->getLevel() >= 65)   
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(530, 12947.4f,-6893.31f,5.68398f,3.09154f);
                    player->ModifyMoney(-1*costo);
                }             
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 65!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Karazhan
            case 4007:
                if (player->getLevel() >= 70) 
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(0, -11118.8f, -2010.84f, 47.0807f, 0.0f);
                    player->ModifyMoney(-20*costo);
                } 
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 70!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Gruul's Lair
            case 4008:
                if (player->getLevel() >= 65)  
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(530, 3539.007568f, 5082.357910f, 1.691071f, 0.0f);
                    player->ModifyMoney(-20*costo);
                }            
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 65!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Hellfire Citadel
            case 4009:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(530, -305.816223f, 3056.401611f, -2.473183f, 2.01f);
                player->ModifyMoney(-20*costo);
                break;
            // Coilfang Reservoir
            case 4010:
                player->CLOSE_GOSSIP_MENU();
                player->TeleportTo(530, 517.288025f, 6976.279785f, 32.007198f, 0.0f);
                player->ModifyMoney(-20*costo);
                break;
            // Tempest Keep
            case 4011:
                if (player->getLevel() >= 70) 
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(530, 3089.579346f, 1399.046509f, 187.653458f, 4.794070f);
                    player->ModifyMoney(-20*costo);
                }
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 70!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Caverns of Time
            case 4012:
                if (player->getLevel() >= 66)    
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(1, -8173.66f, -4746.36f, 33.8423f, 4.93989f);
                    player->ModifyMoney(-20*costo);
                }
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 66!", LANG_UNIVERSAL, NULL);
                } 
                break;
            // Zul'Aman
            case 4016:
                if (player->getLevel() >= 70) 
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(530, 6846.95f, -7954.5f, 170.028f, 4.61501f);
                    player->ModifyMoney(-20*costo);
                } 
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 70!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Black Temple
            case 4013:
                if (player->getLevel() >= 70) 
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(530, -3610.719482f, 324.987579f, 37.400028f, 3.282981f);
                    player->ModifyMoney(-20*costo);
                }
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 70!", LANG_UNIVERSAL, NULL);
                } 
                break;
            // magistrate
            case 4017:
                if (player->getLevel() >= 70)    
                {    
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(530, 12884.6f, -7317.69f, 65.5023f, 4.799f);
                    player->ModifyMoney(-40*costo);
                } 
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 70!", LANG_UNIVERSAL, NULL);
                }   
                break;
            // sunwell
            case 4018:
                if (player->getLevel() >= 70)   
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(530, 12574.1f, -6774.81f, 15.0904f, 3.13788f);
                    player->ModifyMoney(-40*costo);
                } 
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 70!", LANG_UNIVERSAL, NULL);
                } 
            break;
            // Utgarde Keep
            case 4019:
                if (player->getLevel() >= 80)     
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(571, 1219.720f, -4865.28f, 41.25f, 0.31f);
                    player->ModifyMoney(-400*costo);
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 80!", LANG_UNIVERSAL, NULL);
                }  
                break;
            // The Nexus
            case 4020:
                if (player->getLevel() >= 80)     
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(571, 3776.950f, 6953.80f, 105.05f, 0.345f);
                    player->ModifyMoney(-400*costo);
                } 
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 80!", LANG_UNIVERSAL, NULL);
                }  
                break;
            // Azjol-Nerub
            case 4021:
                if (player->getLevel() >= 80)   
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(571, 3675.430f, 2169.00f, 35.90f, 2.29f);
                    player->ModifyMoney(-400*costo);
                } 
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 80!", LANG_UNIVERSAL, NULL);
                } 
                break;
            // Ahn'kahet: The Old Kingdom
            case 4022:
                if (player->getLevel() >= 80)     
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(571, 3646.760f, 2045.17f, 1.79f, 4.37f);
                    player->ModifyMoney(-400*costo);
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 80!", LANG_UNIVERSAL, NULL);
                }
                break;
            // Drak'Tharon Keep
            case 4023:
                if (player->getLevel() >= 80)    
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(571, 4450.860f, -2045.25f, 162.83f, 0.00f);
                    player->ModifyMoney(-400*costo);
                }    
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 80!", LANG_UNIVERSAL, NULL);
                } 
                break;
            // The Violet Hold
            case 4024:
                if (player->getLevel() >= 80)    
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(571, 5679.820f, 486.80f, 652.40f, 4.08f);
                    player->ModifyMoney(-400*costo);
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 80!", LANG_UNIVERSAL, NULL);
                }  
                break;
            // Gun' Drak
            case 4025:
                if (player->getLevel() >= 80)      
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(571, 6937.540f, -4455.98f, 450.68f, 1.00f);
                    player->ModifyMoney(-400*costo);
                } 
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                     creature->MonsterSay("You must be at least level 80!", LANG_UNIVERSAL, NULL);
                }    
                break;
            // Utgarde Pinnacle
            case 4026:
                if (player->getLevel() >= 80)       
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(571, 1245.690f, -4856.59f, 216.86f, 3.45f);
                    player->ModifyMoney(-400*costo);
                } 
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 80!", LANG_UNIVERSAL, NULL);
                }    
                break;
            case 4027:// Ulduar
                if (player->getLevel() >= 80)       
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(571, 8976.240f, -1281.33f, 1059.01f, 0.58f);
                    player->ModifyMoney(-400*costo);
                } 
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 80!", LANG_UNIVERSAL, NULL);
                }   
                break;
            case 4028:// The Obsidian Sanctum
                if (player->getLevel() >= 80)       
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(571, 3625.780f, 280.40f, -120.14f, 3.25f);
                    player->ModifyMoney(-400*costo);
                }
                else 
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 80!", LANG_UNIVERSAL, NULL);
                }    
                break;
            case 4029:// Naxxramas
                if (player->getLevel() >= 80)   
                {
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(571, 3668.719f, -1262.460f, 243.63f, 5.03f);
                    player->ModifyMoney(-400*costo);
                }
                else
                {
                    player->CLOSE_GOSSIP_MENU();
                    creature->MonsterSay("You must be at least level 80!", LANG_UNIVERSAL, NULL);
                }  
            break;
        }
        return true;
    }

    bool GossipSelect_teleguy(Player *player, Creature *_Creature, uint32 sender, uint32 action )
    {
        // Main menu
        if (sender == GOSSIP_SENDER_MAIN)
            OnGossipSelect(player, _Creature, 0, action);
        return true;
    }
};

void AddSC_teleguy()
{
    new teleguy;
}
