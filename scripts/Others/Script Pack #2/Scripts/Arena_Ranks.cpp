/*
 * Arena Team Ranking NPC.
 *  Made by u4ea
 *  Fixed by SymbolixDEV
 * I'd very much appreciate if this NPC was named "Dow Jones"
 */

#include "ScriptPCH.h"
#include <cstring>
#include <string.h>
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ArenaTeam.h"
#include "ArenaTeamMgr.h"
#include "World.h"

enum ArenaRankActionIds {
    ARENA_2V2_LADDER = GOSSIP_ACTION_INFO_DEF + 1,
    ARENA_3V3_LADDER = GOSSIP_ACTION_INFO_DEF + 2,
    ARENA_5V5_LADDER = GOSSIP_ACTION_INFO_DEF + 3,
    ARENA_GOODBYE = GOSSIP_ACTION_INFO_DEF + 4,
    ARENA_NOOP = 1,
    ARENA_START_TEAM_LOOKUP = GOSSIP_ACTION_INFO_DEF + 5,
    
};

enum ArenaRankOptions {
    ARENA_MAX_RESULTS = 30,
};

enum ArenaGossipText {
    ARENA_GOSSIP_HELLO = 11201,
    ARENA_GOSSIP_NOTEAMS = 11202,
    ARENA_GOSSIP_TEAMS = 11203,
    ARENA_GOSSIP_TEAM_LOOKUP = 11204,
    
};

class ArenaTeamRanks : public CreatureScript
{
    private:
        uint32 optionToTeamType(uint32 option) {
            uint32 teamType;
            switch(option) {
                case ARENA_2V2_LADDER: teamType = 2; break;
                case ARENA_3V3_LADDER: teamType = 3; break;
                case ARENA_5V5_LADDER: teamType = 5; break;
            }
            return teamType;
        }
        uint32 teamTypeToOption(uint32 teamType) {
            uint32 option;
            switch(teamType) {
                case 2: option = ARENA_2V2_LADDER; break;
                case 3: option = ARENA_3V3_LADDER; break;
                case 5: option = ARENA_5V5_LADDER; break;
            }
            return option;
        }
        
        std::string raceToString(uint8 race) {
            std::string race_s = "Unknown";
            switch (race)
            {
                case RACE_HUMAN:            race_s = "Human";       break;
                case RACE_ORC:              race_s = "Orc";         break;
                case RACE_DWARF:            race_s = "Dwarf";       break;
                case RACE_NIGHTELF:         race_s = "Night Elf";   break;
                case RACE_UNDEAD_PLAYER:    race_s = "Undead";      break;
                case RACE_TAUREN:           race_s = "Tauren";      break;
                case RACE_GNOME:            race_s = "Gnome";       break;
                case RACE_TROLL:            race_s = "Troll";       break;
                case RACE_BLOODELF:         race_s = "Blood Elf";   break;
                case RACE_DRAENEI:          race_s = "Draenei";     break;
            }
            return race_s;
        }
        
        std::string classToString(uint8 Class) {
            std::string Class_s = "Unknown";
            switch (Class)
            {
                case CLASS_WARRIOR:         Class_s = "Warrior";        break;
                case CLASS_PALADIN:         Class_s = "Paladin";        break;
                case CLASS_HUNTER:          Class_s = "Hunter";         break;
                case CLASS_ROGUE:           Class_s = "Rogue";          break;
                case CLASS_PRIEST:          Class_s = "Priest";         break;
                case CLASS_DEATH_KNIGHT:    Class_s = "Death Knight";   break;
                case CLASS_SHAMAN:          Class_s = "Shaman";         break;
                case CLASS_MAGE:            Class_s = "Mage";           break;
                case CLASS_WARLOCK:         Class_s = "Warlock";        break;
                case CLASS_DRUID:           Class_s = "Druid";          break;
            }
            return Class_s;
        }
        
        std::string getPlayerStatus(uint32 guid) {
            Player *player = sObjectAccessor->FindPlayer(guid);
            if(!player)
                return "Offline";
            if(player->isAFK()) 
                return "Online, <AFK> ";
            if(player->isDND()) 
                return "Online, <Busy> ";
            return "Online";
        }
        
        std::string getWinPercent(uint32 wins, uint32 losses) {
            uint32 totalGames = wins + losses;
            if (totalGames == 0)
                return "0%";
            
            std::stringstream buf;
            uint32 percentage = (wins * 100) / totalGames;
            buf << percentage << "%";
            return buf.str();
        }
        
    public:
        ArenaTeamRanks() : CreatureScript("ArenaTeamRanks"){}
        
        bool OnGossipHello(Player *player, Creature *creature) {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "2v2 Rankings", GOSSIP_SENDER_MAIN, ARENA_2V2_LADDER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "3v3 Rankings", GOSSIP_SENDER_MAIN, ARENA_3V3_LADDER);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "5v5 Rankings", GOSSIP_SENDER_MAIN, ARENA_5V5_LADDER);
            
            player->SEND_GOSSIP_MENU(ARENA_GOSSIP_HELLO, creature->GetGUID());
            
            return true;
        }
        
        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction) {
            player->PlayerTalkClass->ClearMenus();
            
            switch(uiAction) {
                case ARENA_GOODBYE:
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
                case ARENA_2V2_LADDER:
                case ARENA_5V5_LADDER:
                case ARENA_3V3_LADDER:
                {
                    uint32 teamType = optionToTeamType(uiAction);
                    QueryResult result = CharacterDatabase.PQuery(
                            "SELECT arenaTeamId, name, rating, seasonWins, seasonGames - seasonWins "
                            "FROM arena_team WHERE type = '%u' ORDER BY rating DESC LIMIT %u;", teamType, ARENA_MAX_RESULTS
                            );
                    
                    if(!result) {
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Goodbye", GOSSIP_SENDER_MAIN, ARENA_GOODBYE);
                        player->SEND_GOSSIP_MENU(ARENA_GOSSIP_NOTEAMS, creature->GetGUID());
                    } else {
                        //uint64 rowCount = result->GetRowCount();
                        std::string name;
                        uint32 teamId, rating, seasonWins, seasonLosses, rank = 1;
                        do {
                            Field *fields = result->Fetch();
                            teamId = fields[0].GetUInt32();
                            name = fields[1].GetString();
                            rating = fields[2].GetUInt32();
                            seasonWins = fields[3].GetUInt32();
                            seasonLosses = fields[4].GetUInt32();
                            
                            std::stringstream buffer;
                            buffer << rank << ". [" << rating << "] " << name;
                            buffer << " (" << seasonWins << "-" << seasonLosses << ")";
                            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, buffer.str(), GOSSIP_SENDER_MAIN, ARENA_START_TEAM_LOOKUP + teamId);
                            
                            rank++;
                        } while(result->NextRow());
                        
                        player->SEND_GOSSIP_MENU(ARENA_GOSSIP_TEAMS, creature->GetGUID());
                    }
                    break;
                }
                default:
                {
                    if (uiAction > ARENA_START_TEAM_LOOKUP) 
                    {
                        uint32 teamId = uiAction - ARENA_START_TEAM_LOOKUP;
                        
                        // lookup team
                        QueryResult result = CharacterDatabase.PQuery(
                            //      0     1       2           3
                            "SELECT name, rating, seasonWins, seasonGames - seasonWins, "
                            //  4      5                     6     7             8
                            "weekWins, weekGames - weekWins, rank, captainGuid , type "
                            "FROM arena_team WHERE arenaTeamId = '%u'", teamId);
                        
                        // no team found
                        if(!result) {
                            player->GetSession()->SendNotification("Arena team not found...");
                            player->PlayerTalkClass->SendCloseGossip();
                            return true;
                        }
                        
                        // populate the results
                        Field *fields = result->Fetch();
                        std::string name = fields[0].GetString();
                        uint32 rating = fields[1].GetUInt32();
                        uint32 seasonWins = fields[2].GetUInt32();
                        uint32 seasonLosses = fields[3].GetUInt32();
                        uint32 weekWins = fields[4].GetUInt32();
                        uint32 weekLosses = fields[5].GetUInt32();
                        uint32 rank = fields[6].GetUInt32();
                        uint32 captainGuid = fields[7].GetUInt32();
                        uint32 type = fields[8].GetUInt32();
                        uint32 parentOption = teamTypeToOption(type);
                        
                        std::string seasonWinPercentage = getWinPercent(seasonWins, seasonLosses);
                        std::string weekWinPercentage = getWinPercent(weekWins, weekLosses);
                        
                        std::stringstream buf;
                        buf << "Team Name: " << name;
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, buf.str(), GOSSIP_SENDER_MAIN, parentOption);
                        buf.str("");
                        buf << "Rating: " << rating << " (rank " << rank << ", bracket " << type << "v" << type << ")";
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, buf.str(), GOSSIP_SENDER_MAIN, parentOption);
                        buf.str("");
                        buf << "Total Week: " << weekWins << "-" << weekLosses << " (" << weekWinPercentage << " win), " << (weekWins + weekLosses) << " played"; 
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, buf.str(), GOSSIP_SENDER_MAIN, parentOption);
                        buf.str("");
                        buf << "Total Season: " << seasonWins << "-" << seasonLosses << " (" << seasonWinPercentage << " win), " << (seasonWins + seasonLosses) << " played"; 
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, buf.str(), GOSSIP_SENDER_MAIN, parentOption);
                        
                        QueryResult members = CharacterDatabase.PQuery( "SELECT  a.guid, a.personalRating, a.weekWins, a.weekGames - a.weekWins, a.seasonWins, a.seasonGames - a.seasonWins, c.name, c.race, c.class, c.level FROM arena_team_member a LEFT JOIN characters c ON c.guid = a.guid WHERE arenaTeamId = '%u' ORDER BY a.guid = '%u' DESC, a.seasonGames DESC, c.name ASC", teamId, captainGuid);
                        if(!members) {
                            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "No team members found...?", GOSSIP_SENDER_MAIN, parentOption);
                        } else {
                            uint32 memberPos = 1;
                            uint32 memberCount = members->GetRowCount();
                            uint32 guid, personalRating, level;
                            std::string name, race, Class;
                            
                            buf.str("");
                            buf << memberCount << " team " << ((memberCount == 1) ? "member" : " members") << " found:";
                            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, buf.str(), GOSSIP_SENDER_MAIN, parentOption);
                            
                            do {
                                // populate fields
                                fields = members->Fetch();
                                guid = fields[0].GetUInt32();
                                personalRating = fields[1].GetUInt32();
                                weekWins= fields[2].GetUInt32();
                                weekLosses = fields[3].GetUInt32();
                                seasonWins = fields[4].GetUInt32();
                                seasonLosses = fields[5].GetUInt32();
                                name = fields[6].GetString();
                                race = raceToString(fields[7].GetUInt8());
                                Class = classToString(fields[8].GetUInt8());
                                level = fields[9].GetUInt32();
                                
                                seasonWinPercentage = getWinPercent(seasonWins, seasonLosses);
                                weekWinPercentage = getWinPercent(weekWins, weekLosses);
                                
                                // TODO: add output
                                buf.str(""); // clear it
                                buf << memberPos << ". "; 
                                if (guid == captainGuid) 
                                    buf <<  "Team Captain ";
                                buf << name << ", " << getPlayerStatus(guid);
                                
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, buf.str(), GOSSIP_SENDER_MAIN, parentOption);
                                buf.str("");
                                buf << "Level " << level << " " << race << " " << Class << ", " << personalRating << " personal rating.";
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, buf.str(), GOSSIP_SENDER_MAIN, parentOption);
                                buf.str("");
                                buf << "Week: " << weekWins << "-" << weekLosses << " (" << weekWinPercentage << " win), " << (weekWins + weekLosses) << " played"; 
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, buf.str(), GOSSIP_SENDER_MAIN, parentOption);
                                buf.str("");
                                buf << "Season: " << seasonWins << "-" << seasonLosses << " (" << seasonWinPercentage << " win), " << (seasonWins + seasonLosses) << " played"; 
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, buf.str(), GOSSIP_SENDER_MAIN, parentOption);
                                memberPos++;
                            } while(members->NextRow());
                            
                        }
                        
                        buf.str("");
                        buf << "Return to " << type << "v" << type << " rankings!";
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, buf.str(), GOSSIP_SENDER_MAIN, parentOption);
                        player->SEND_GOSSIP_MENU(ARENA_GOSSIP_TEAM_LOOKUP, creature->GetGUID());
                    }
                }
            }
            
            return true;
        }
};

class npc_matchmakerrating : public CreatureScript
{
    public:
        npc_matchmakerrating() : CreatureScript("npc_matchmakerrating") { }

		uint16* GetMmr(Player *player)
		{
			uint16 *mmr = new uint16[3];
			for(int x = 0; x < 3; x++)
			{
				if(ArenaTeam *twos = sArenaTeamMgr->GetArenaTeamById(player->GetArenaTeamId(x)))
					mmr[x] = twos->GetMember(player->GetGUID())->MatchMakerRating;
				else
					mmr[x] = 0;
			}
			return mmr;
		}

		bool ChangeMmr(Player *player, int slot, int value)
		{
			if(ArenaTeam *team = sArenaTeamMgr->GetArenaTeamById(player->GetArenaTeamId(slot)))
			{
				ArenaTeamMember *member = team->GetMember(player->GetGUID());
				member->MatchMakerRating = value;
				member->ModifyMatchmakerRating(value - (int)member->MatchMakerRating, slot);
				team->SaveToDB();
				return true;
			}
			return false;
		}

        bool OnGossipHello(Player *player, Creature *_creature)
		{
			uint16 *mmr = GetMmr(player);

			if(mmr[0] > 0)
			{
				player->ADD_GOSSIP_ITEM(0, "Reset 2v2 MMR (5 PvP Tickets)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				if(mmr[0] > 1600)
					player->ADD_GOSSIP_ITEM(0, "Lower 2v2 MMR to 1600", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
			}

			if(mmr[1] > 0)
			{
				player->ADD_GOSSIP_ITEM(0, "Reset 3v3 MMR (10 PvP Tickets)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
				if(mmr[1] > 1500)
					player->ADD_GOSSIP_ITEM(0, "Lower 3v3 MMR to 1500", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
			}

			if(mmr[2] > 0)
			{
				player->ADD_GOSSIP_ITEM(0, "Reset 5v5 MMR (15 PvP Tickets)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
				if(mmr[1] > 1400)
					player->ADD_GOSSIP_ITEM(0, "Lower 5v5 MMR to 1400", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
			}

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bye", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
            
			player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetGUID());
			return true;
		}

        bool OnGossipSelect(Player *player, Creature *_creature, uint32 sender, uint32 action)
        {
            if (action < GOSSIP_ACTION_INFO_DEF + 7)
            {
				uint16 *mmr = GetMmr(player);
				switch(action - GOSSIP_ACTION_INFO_DEF)
				{
					case 1:
						if(mmr[0] > 0 && player->HasItemCount(19182, 5))
						{
							if(ChangeMmr(player, 0, 1500))
							{
								player->DestroyItemCount(19182, 5, true);
								player->SaveToDB();
							}
						}
						break;
					case 2:
						if(mmr[0] > 1600)
						{
							if(ChangeMmr(player, 0, 2100))
								player->SaveToDB();
						}
						break;
					case 3:
						if(mmr[1] > 0 && player->HasItemCount(19182, 10))
						{
							if(ChangeMmr(player, 1, 1500))
							{
								player->DestroyItemCount(19182, 10, true);
								player->SaveToDB();
							}
						}
						break;
					case 4:
						if(mmr[1] > 1500)
						{
							if(ChangeMmr(player, 1, 2000))
								player->SaveToDB();
						}
						break;
					case 5:
						if(mmr[2] > 0 && player->HasItemCount(19182, 15))
						{
							if(ChangeMmr(player, 2, 1500))
							{
								player->DestroyItemCount(19182, 15, true);
								player->SaveToDB();
							}
						}
						break;
					case 6:
						if(mmr[2] > 1400)
						{
							if(ChangeMmr(player, 2, 1900))
								player->SaveToDB();
						}
						break;
					default:
						break;
				}
			}

			player->CLOSE_GOSSIP_MENU();
			return true;
		}
};

void AddSC_arenateamranks()
{
    new ArenaTeamRanks();
    new npc_matchmakerrating();
}
