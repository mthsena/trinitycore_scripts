/*
 * Author: Xees
 * FileName: ArenaGamblingSystem.h
 * Description: This file is used for definitions and requirements of the Arena Gambling System
 * Version: 1.7
 * Status: functional
*/
#ifndef ArenaGambler_H
#define ArenaGambler_H

// scriptName
#define GAMBLER_SYSTEM_SCRIPT_NAME "custom_gambling_system_script"
#define GAMBLER_SYSTEM_DUEL_SCRIPT_NAME "custom_gambler_duel_script"

#define ARENA_GAMBLER_SCRIPT_NAME "duel_system"
#define ARENA_RECORDS_SCRIPT_NAME "duel_records_system"

enum ARENA_GAMBLER_MENUS
{
	ARENA_GAMBLER_MENU_MAIN	= 1,
	ARENA_GAMBLER_MENU_CHALLENGE_PLAYER,
	ARENA_GAMBLER_MENU_BET_ITEM,
	ARENA_GAMBLER_MENU_BET_ITEM_AMOUNT,
	ARENA_GAMBLER_MENU_BET_ITEM_AMOUNT_1,
	ARENA_GAMBLER_MENU_BET_ITEM_AMOUNT_10,
	ARENA_GAMBLER_MENU_BET_ITEM_AMOUNT_20,
	ARENA_GAMBLER_MENU_BET_ITEM_AMOUNT_30,
	ARENA_GAMBLER_MENU_BET_ITEM_AMOUNT_40,
	ARENA_GAMBLER_MENU_BET_ITEM_AMOUNT_50,
	ARENA_GAMBLER_MENU_BET_ITEM_AMOUNT_100,
	ARENA_GAMBLER_MENU_BET_ITEM_AMOUNT_200,
	ARENA_GAMBLER_MENU_BET_ITEM_AMOUNT_300,
	ARENA_GAMBLER_MENU_BET_ITEM_AMOUNT_500,
	ARENA_GAMBLER_MENU_BET_ITEM_AMOUNT_1000,
	ARENA_GAMBLER_MENU_ACCEPT_CHALLENGE,
	ARENA_GAMBLER_MENU_CANCEL_CHALLENGE,
	ARENA_GAMBLER_MENU_DECLINE_CHALLENGE,
	ARENA_GAMBLER_MENU_EXIT
};

enum ARENA_GAMBLER_MENU_ICONS
{
	ARENA_GAMBLER_ICON_CHALLENGE	= GOSSIP_ICON_BATTLE,			// ARENA_GAMBLER_MENU_CHALLENGE_PLAYER
	ARENA_GAMBLER_ICON_BET_ITEM		= GOSSIP_ICON_MONEY_BAG,		// ARENA_GAMBLER_MENU_BET_ITEM
	ARENA_GAMBLER_ICON_ACCEPT		= GOSSIP_ICON_BATTLE,			// ARENA_GAMBLER_MENU_ACCEPT_CHALLENGE
	ARENA_GAMBLER_ICON_CANCEL		= GOSSIP_ICON_DOT,				// ARENA_GAMBLER_MENU_CANCEL_CHALLENGE
	ARENA_GAMBLER_ICON_DECLINE		= GOSSIP_ICON_TAXI,				// ARENA_GAMBLER_MENU_DECLINE_CHALLENGE
	ARENA_GAMBLER_ICON_EXIT			= GOSSIP_ICON_TABARD,			// ARENA_GAMBLER_MENU_EXIT
};

// Menu Texts
#define ARENA_GAMBLER_TEXT_CHALLENGE "I would like to Challenge a player to a duel!"
#define ARENA_GAMBLER_TEXT_CHALLENGE_CODE_TEXT "Enter the name of a player you wish to challenge. (Case Sensitive)"
#define ARENA_GAMBLER_TEXT_BET_ITEM "I would like to Bet an item"
#define ARENA_GAMBLER_TEXT_BET_ITEM_CODE_TEXT "Enter the name of the item you wish to bet"
#define ARENA_GAMBLER_TEXT_BET_ITEM_AMOUNT "I would like to enter the amount"
#define ARENA_GAMBLER_TEXT_BET_AMOUNT_TEXT "Select the amount of items you wish to bet"
#define ARENA_GAMBLER_TEXT_ACCEPT_CHALLENGE "I accept the challenge!"
#define ARENA_GAMBLER_TEXT_CANCEL_CHALLENGE "I do not want to do this challenge!"
#define ARENA_GAMBLER_TEXT_DECLINE_CHALLENGE "I do not accept this challenge!"
#define ARENA_GAMBLER_TEXT_EXIT "Nevermind"

// Amount of bets Menu text -- TODO: write a more efficient way to override Opcode OnGossipSelectWithCode string restrictions
#define ARENA_GAMBLER_TEXT_BET_AMOUNT_1 "1 item."
#define ARENA_GAMBLER_TEXT_BET_AMOUNT_10 "10 items."
#define ARENA_GAMBLER_TEXT_BET_AMOUNT_20 "20 items."
#define ARENA_GAMBLER_TEXT_BET_AMOUNT_30 "30 items."
#define ARENA_GAMBLER_TEXT_BET_AMOUNT_40 "40 items."
#define ARENA_GAMBLER_TEXT_BET_AMOUNT_50 "50 items."
#define ARENA_GAMBLER_TEXT_BET_AMOUNT_100 "100 items."
#define ARENA_GAMBLER_TEXT_BET_AMOUNT_200 "200 items."
#define ARENA_GAMBLER_TEXT_BET_AMOUNT_300 "300 items."
#define ARENA_GAMBLER_TEXT_BET_AMOUNT_500 "500 items."
#define ARENA_GAMBLER_TEXT_BET_AMOUNT_1000 "1000 items."

// Mail System Defines
#define GAMBLER_SYSTEM_MSG_MAIL_SUBJECT "The Judgment Arena : Rewards !"
#define GAMBLER_SYSTEM_MSG_MAIL_BODY_MATCH_INCOMPLETE "Your item is being returned as the result of an incomplete match"
#define GAMBLER_SYSTEM_MSG_MAIL_BODY_MATCH_WON "You've won the match!"
#define GAMBLER_SYSTEM_MAIL_TYPE MAIL_STATIONERY_GM

// Messages
#define GAMBLER_SYSTEM_MSG_ACCEPTED_CHALLENGE "%s has accepted the challenge!" // %s = accepters name
#define GAMBLER_SYSTEM_MSG_ITEM_BET_PLACED "%s has placed item %s up for bet!" // %s1 = players name %s2 = items name
#define GAMBLER_SYSTEM_MSG_CANCELED "%s has %s the match!" // the first %s will utilize one of the below defines considering the player is either, the challenger canceling the match, or the defender canceling the match
#define GAMBLER_SYSTEM_MSG_CANCELED_1 "Canceled"
#define GAMBLER_SYSTEM_MSG_CANCELED_2 "Forfeit"
#define GAMBLER_SYSTEM_MSG_CANT_LOCATE_PLAYER "Could not locate the second player, match aborted!"
#define GAMBLER_SYSTEM_MSG_CANT_START_DUEL "Cannot start match while currently in a duel, or in combat."
#define GAMBLER_SYSTEM_MSG_CANT_START_LOGGING "Cannot start the match while one fo the players is logging out!"
#define GAMBLER_SYSTEM_MSG_MATCH_STARTING "The match is now underway!"
#define GAMBLER_SYSTEM_MSG_DUEL_INTERRUPTED "The duel has been interrupted, items have been mailed back to their original owners"
#define GAMBLER_SYSTEM_MSG_DUEL_FLED_NON_AWARD "items have been mailed to their original owners"
#define GAMBLER_SYSTEM_MSG_DUEL_WON "%s has been mailed his match winnings!" // %s = winnerName
#define GAMBLER_SYSTEM_MSG_ITEM_VALIDATE_FAIL "An invalid item has caused the match to be stopped!"
#define GAMBLER_SYSTEM_MSG_ITEM_NO_INV "The amount of items you can bet is invalid!"
#define ARENA_GAMBLER_MSG_NOT_SAME_PLAYER "That is not the same person i requested the duel with!"
#define ARENA_GAMBLER_MSG_PLAYER_NOT_FOUND "The player might be offline or away at the moment , i was not able to locate the player."
#define ARENA_GAMBLER_MSG_MATCH_NOT_POSSIBLE "Duel is not accepted because of the following: "
#define ARENA_GAMBLER_MSG_NO_GMS_ALLOWED "Game Masters are not allowed to duel!"
#define ARENA_GAMBLER_MSG_SAME_ACC_ID "You cannot duel your self!"
#define ARENA_GAMBLER_MSG_NOT_READY "You or your opponent has not set ready for the duel!"
#define ARENA_GAMBLER_MSG_NO_ITEM "You or your opponent did not specify an item id!"
#define ARENA_GAMBLER_MSG_NO_AMOUNT "You or your opponent did not specify an item amount!"
#define ARENA_GAMBLER_MSG_MULTI_BOX "You cannot duel anyone with the same ip address!"
#define ARENA_GAMBLER_MSG_LOW_LEVEL "Your level is too low to duel"
#define ARENA_GAMBLER_MSG_MATCH_DATA "You have requested a duel from someone who already is in a duel."
#define ARENA_GAMBLER_MSG_DIFF_NOT_MET "Your level is too high or too low to duel this player."
#define ARENA_GAMBLER_MSG_CHALLENGE_ISSUED "You have challenged %s to a duel!"	// %s = defenders name
#define ARENA_GAMBLER_MSG_CHALLENGED "%s wants to challenge you to a duel!"		// %s = challengers name
#define ARENA_GAMBLER_MSG_ITEM_ADD_FAILED "You may not have the item, or the item could be soulbound, or you are not allowed to bet that item."
#define ARENA_GAMBLER_MSG_BET_ADD_FAILED "The maximum amount of items you can bet is %u" // %u = maximum bet
#define ARENA_GAMBLER_MSG_BET_AMOUNT_FAILED "You may not have the item, or your bet is not the same as your opponent, or you have chosen a higher bet that allowed, your not allowed to duel this item."
#define ARENA_GAMBLER_MSG_BET_AMOUNT_TOO_HIGH "The maximum number of items the player can recieve is lower than the amount betted."
#define ARENA_GAMBLER_MSG_ITEM_AMOUNT_SUCCESS "Your bet amount was entered successfully, please accept or reject the duel!"
#define ARENA_GAMBLER_MSG_ITEM_ADD_SUCCESS "Your item was selected successfully, now select the amount you would like to bet!"

// Intervals
#define GAMBLER_SYSTEM_INTERVAL_TELE_CHECK 10000 

// Vars
#define GAMBLER_SYSTEM_TOTAL_MAX_BET 1000

#define MSG_COLOR_LIGHTRED      "|cffff6060"
#define MSG_COLOR_LIGHTBLUE     "|cff00ccff"
#define MSG_COLOR_BLUE          "|cff0000ff"
#define MSG_COLOR_GREEN         "|cff00ff00"
#define MSG_COLOR_RED           "|cffff0000"
#define MSG_COLOR_GOLD          "|cffffcc00"
#define MSG_COLOR_GREY          "|cff888888"
#define MSG_COLOR_WHITE         "|cffffffff"
#define MSG_COLOR_SUBWHITE      "|cffbbbbbb"
#define MSG_COLOR_MAGENTA       "|cffff00ff"
#define MSG_COLOR_YELLOW        "|cffffff00"
#define MSG_COLOR_CYAN          "|cff00ffff"
#define MSG_COLOR_ORANGE		"|cffff9900"

#define QUALITY_POOR                 "cff9d9d9d"			  //GREY
#define QUALITY_NORMAL               "cffffffff"             //WHITE
#define QUALITY_UNCOMMON             "cff1eff00"             //GREEN
#define QUALITY_RARE                 "cff0070dd"             //BLUE
#define QUALITY_EPIC                 "cffa335ee"             //PURPLE
#define QUALITY_LEGENDARY            "cffff8000"             //ORANGE
#define QUALITY_ARTIFACT             "cffe6cc80"             //LIGHT YELLOW
#define QUALITY_HEIRLOOM             "cffe6cc80"			  //LIGHT YELLOW

enum MatchParticipants
{
	GAMBLER_CHALLENGER,
	GAMBLER_DEFENDER,
	GAMBLER_WINNER,
	GAMBLER_MAX_MEMBERS,
};

enum GamberSystemConfigIndex
{
	GAMBLER_CONFIG_OPTION_MAPID,
	GAMBLER_CONFIG_OPTION_COORDSX,
	GAMBLER_CONFIG_OPTION_COORDSY,
	GAMBLER_CONFIG_OPTION_COORDSZ,
	GAMBLER_CONFIG_OPTION_COORDSO,
	GAMBLER_CONFIG_OPTION_MIN_REQUIREDLEVEL,
	GAMBLER_CONFIG_OPTION_MAX_LEVELDIFF,
	GAMBLER_CONFIG_OPTION_AWARD_FLED,
	GAMBLER_CONFIG_OPTION_MAX_BET,
	GAMBLER_CONFIG_OPTION_ENABLE_GM,
	GAMBLER_CONFIG_OPTION_ENABLE_SAMEIP,
    GAMBLER_CONFIG_OPTION_ENABLE_LIMITS,
    GAMBLER_CONFIG_OPTION_ONLY_CURRENCY,
    GAMBLER_CONFIG_OPTION_EQUAL_DUELS
};

enum GamblerPlayerStatIndex
{
	GAMBLER_PLAYER_STAT_GUID,
	GAMBLER_PLAYER_STAT_DUELS_LOST,
	GAMBLER_PLAYER_STAT_DUELS_WON,
	GAMBLER_PLAYER_STAT_DUELS_REFUSED,
	GAMBLER_PLAYER_STAT_DUELS_TOTAL,
	GAMBLER_PLAYER_STAT_MAX
};

enum GamblerMatchStatus
{
	GAMBLER_MATCH_STATUS_SETUP,
	GAMBLER_MATCH_STATUS_TELEPORT,
	GAMBLER_MATCH_STATUS_RUNNING,
};

struct GamblerMatchData
{
	public:
		GamblerMatchData(uint32 Id, uint32 challengerGUID, uint32 defenderGUID) 
		{
			SetMatchStatus(GAMBLER_MATCH_STATUS_SETUP);
			SetChallengerGUID(challengerGUID);
			SetDefenderGUID(defenderGUID);
			SetChallengerReady(false);
			SetDefenderReady(false);
			SetMatchWinner(0);
			matchId = Id;

			for(uint8 i = 0; i < GAMBLER_MAX_MEMBERS-1; i++)
				itemStorage[i] = 0;

			for(uint8 i = 0; i < GAMBLER_MAX_MEMBERS-1; i++)
				CountStorage[i] = 0;
		}

		GamblerMatchData(Field *pFields)
		{
			SetMatchStatus(GAMBLER_MATCH_STATUS_SETUP);
			matchId	= pFields[0].GetUInt32();
			SetChallengerGUID(pFields[1].GetUInt32());
			SetDefenderGUID(pFields[2].GetUInt32());
			SetChallengerItemId(pFields[3].GetUInt32());
			SetChallengerItemCount(pFields[4].GetUInt32());
			SetDefenderItemId(pFields[5].GetUInt32());
			SetDefenderItemCount(pFields[6].GetUInt32());
			SetMatchDate(pFields[7].GetString());
			SetMatchWinner(pFields[8].GetUInt32());
			SetChallengerReady(false);
			SetDefenderReady(false);
		}

		// External Assignment Functions
		void SetChallengerGUID(uint32 challengerGUID)	{ _setMemberGUID(GAMBLER_CHALLENGER,	challengerGUID);	}
		void SetDefenderGUID(uint32 defenderGUID)		{ _setMemberGUID(GAMBLER_DEFENDER,		defenderGUID);		}
		void SetChallengerItemId(uint32 itemId)			{ _setMemberItemId(GAMBLER_CHALLENGER,	itemId);			}
		void SetDefenderItemId(uint32 itemId)			{ _setMemberItemId(GAMBLER_DEFENDER,	itemId);			}
		void SetChallengerItemCount(uint32 amount)		{ _setMemberItemCount(GAMBLER_CHALLENGER,	amount);		}
		void SetDefenderItemCount(uint32 amount)		{ _setMemberItemCount(GAMBLER_DEFENDER,	amount);			}
		void SetChallengerReady(bool isReady)			{ _setMemberReady(GAMBLER_CHALLENGER,	isReady);			}
		void SetDefenderReady(bool isReady)				{ _setMemberReady(GAMBLER_DEFENDER,		isReady);			}
		void SetMatchWinner(uint32 winnerGUID)			{ _setMemberGUID(GAMBLER_WINNER,		winnerGUID);		}
		void SetMatchDate(std::string matchTime)		{ matchDate = matchTime;									}
		void SetMatchStatus(GamblerMatchStatus status)	{ matchStatus = status;										}

		// External Retrieval Functions
		uint32 GetChallengerGUID()						{ return _getMemberGUID(GAMBLER_CHALLENGER);				}
		uint32 GetDefenderGUID()						{ return _getMemberGUID(GAMBLER_DEFENDER);					}
		uint32 GetChallengerItemId()					{ return _getMemberItemId(GAMBLER_CHALLENGER);				}
		uint32 GetDefenderItemId()						{ return _getMemberItemId(GAMBLER_DEFENDER);				}
		uint32 GetChallengerItemCount()					{ return _getMemberItemCount(GAMBLER_CHALLENGER);			}
		uint32 GetDefenderItemCount()					{ return _getMemberItemCount(GAMBLER_DEFENDER);				}
		uint32 GetMatchWinner()							{ return _getMemberGUID(GAMBLER_WINNER);					}
		uint32 GetMatchId()								{ return matchId;											}
		uint8 GetMatchStatus()							{ return matchStatus;										}
		bool GetChallengerReady()						{ return _getMemberReadyStatus(GAMBLER_CHALLENGER);			}
		bool GetDefenderReady()							{ return _getMemberReadyStatus(GAMBLER_DEFENDER);			}
		std::string GetMatchDate()						{ return matchDate;											}

		bool MatchStarted()							
		{ 
			if(GetMatchStatus() >= GAMBLER_MATCH_STATUS_TELEPORT)
				return true;
			return false;
		}

		bool HasSetReady(Player *pPlayer)
		{
			if(IsChallenger(pPlayer))
				return GetChallengerReady();
			else
				return GetDefenderReady();
		}

		uint32 GetItemIdBy(Player *pPlayer)
		{
			if(pPlayer->GetGUIDLow() == GetChallengerGUID())
				return GetChallengerItemId();
			else
				return GetDefenderItemId();
		}

		uint32 GetItemCountBy(Player *pPlayer)
		{
			if(pPlayer->GetGUIDLow() == GetChallengerGUID())
				return GetChallengerItemCount();
			else
				return GetDefenderItemCount();
		}

		// Misc Functions
		bool IsChallenger(Player *pPlayer) 
		{ 
			if(pPlayer->GetGUIDLow() == GetChallengerGUID()) 
				return true; 
			return false; 
		}

		bool IsDefender(Player *pPlayer) { return !IsChallenger(pPlayer); }

	private:
		// Internal Assignment Functions
		void _setMemberGUID(MatchParticipants matchMember, uint32 memberGUID) { guidStorage[matchMember] = memberGUID; }
		void _setMemberItemId(MatchParticipants matchMember, uint32 itemId) 
		{ 
			if(matchMember > GAMBLER_DEFENDER)
				return;
			itemStorage[matchMember] = itemId; 
		}
		void _setMemberItemCount(MatchParticipants matchMember, uint32 amount) 
		{ 
			if(matchMember > GAMBLER_DEFENDER)
				return;
			CountStorage[matchMember] = amount; 
		}

		void _setMemberReady(MatchParticipants matchMember, bool isReady)
		{
			if(matchMember > GAMBLER_DEFENDER)
				return;
			readyStatus[matchMember] = isReady;
		}

		// Internal Retrieval Functions
		uint32 _getMemberGUID(MatchParticipants matchMember) { return guidStorage[matchMember]; }
		uint32 _getMemberItemId(MatchParticipants matchMember) 
		{ 
			if(matchMember > GAMBLER_DEFENDER)
				return 0;
			return itemStorage[matchMember]; 
		}
		uint32 _getMemberItemCount(MatchParticipants matchMember) 
		{ 
			if(matchMember > GAMBLER_DEFENDER)
				return 0;
			return CountStorage[matchMember]; 
		}

		bool _getMemberReadyStatus(MatchParticipants matchMember)
		{
			if(matchMember > GAMBLER_DEFENDER)
				return false;
			return readyStatus[matchMember];
		}

	protected:
		uint32 guidStorage[GAMBLER_MAX_MEMBERS];
		uint32 itemStorage[GAMBLER_MAX_MEMBERS-1];
		uint32 CountStorage[GAMBLER_MAX_MEMBERS-1];
		uint32 matchId;
		GamblerMatchStatus matchStatus;
		bool readyStatus[GAMBLER_MAX_MEMBERS-1];
		std::string matchDate;
};

typedef std::map<uint32, GamblerMatchData*> GamblerMatchMap;
class GamblingSystem : public WorldScript
{
	public:
		GamblingSystem();
		~GamblingSystem();

		// Creation
		void Initalize();

		// Events
		// Called on every world tick (don't execute too heavy code here).
        	void OnUpdate(uint32 diff);

		// Database Interaction
		void LoadConfigData();

		// Match Data Retrieval
		GamblerMatchData *GetMatchDataBy(Player *pPlayer);

		// Match Requirements Checking
		bool CanHaveMatch(Player *pChallenger, Player *pDefender);

		// Match Setup
		void SetupMatch(Player *pChallenger, Player *pDefender);
		bool AddItemForMatch(Player *pPlayer, std::string itemName);
		bool AddItemAmountForMatch(Player *pPlayer, uint32 amount);
		void AcceptChallenge(Player *pPlayer);
		void CancelChallenge(Player *pPlayer);

		std::string GetQualityColor(int32 qualityType) const; 

		// Match Completion
		void HandleMatchComplete(Player *pWinner, Player *pLoser, GamblerMatchData *matchData, DuelCompleteType completeType);

		// Messaging
		void SendMessageToPlayers(GamblerMatchData *matchData, const char *msgToSend, ...);


	private:
		// Database Interaction
		void _loadPastMatches();
		void _saveCurrentMatchProgress(GamblerMatchData *matchData);
		void _updatePlayerStats(uint32 playerGUID, GamblerPlayerStatIndex statIndex, uint32 statIncreaseValue);

		// Mail System
		void _createItemAndMailToPlayer(Player *pPlayer, uint32 playerGUID, uint32 itemId, uint32 amount, std::string mailMessage);

		// Mutex Wrappers
		void AcquireMatchLock() { m_matchLock.acquire(); }
		void ReleaseMatchLock() { m_matchLock.release(); }

		// Match Data
		bool _checkItemValidity(Item *pItem);
		bool _checkItemValidity(uint32 itemId);
        	bool _checkWithinLimits(Item *pItem);
		void _deleteMatchData(Player *pPlayer);
		void _deleteMatchData(uint32 matchId);
		uint32 _generateMatchId();
	protected:

		// Matches
		ACE_Thread_Mutex m_matchLock;
		GamblerMatchMap m_matchStorage;
		IntervalTimer m_checkMatches;

		// Config Data
		WorldLocation m_arenaCoords;
		uint32 m_minRequiredLevel;
		uint8 m_maxLevelDiff;
		uint32 m_highMatchId;
		bool m_awardFled;
		uint32 m_maxBet;
		bool m_enableGM;
		bool m_enableSameip;
        bool m_enableLimits;
        bool m_onlyCurrency;
        bool m_equalDuels;
};

class GamblerDuelScript : PlayerScript
{
	public:
	GamblerDuelScript() : PlayerScript(GAMBLER_SYSTEM_DUEL_SCRIPT_NAME) {}

	 // Called when a duel is requested
	void OnDuelRequest(Player *pDefender, Player *pChallenger);
       // Called when a duel ends
	void OnDuelEnd(Player *pWinner, Player *pLoser, DuelCompleteType type);
	// Called when a player logsout
	void OnLogout(Player *pPlayer);
};

#define sGamblingSystem (*ACE_Singleton<GamblingSystem, ACE_Null_Mutex>::instance())
#endif // ArenaGambler_H