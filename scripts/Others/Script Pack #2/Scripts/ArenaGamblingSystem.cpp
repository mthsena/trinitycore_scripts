/*
 * Author: Xees
 * FileName: ArenaGamblingSystem.cpp
 * Description: This file is used to script the Arena Gambling System
 * Version: 1.7
 * Status: functional
*/
#include "ScriptPCH.h"
#include "ArenaGamblingSystem.h"

using namespace std;

const char *GamblerPlayerStatFields[GAMBLER_PLAYER_STAT_MAX] = 
{
	"playerGUID",
	"duelsLost",
	"duelsWon",
	"duelsRefused",
	"duelsTotal"
};

GamblingSystem::GamblingSystem() : WorldScript(GAMBLER_SYSTEM_SCRIPT_NAME)
{
	m_checkMatches.SetInterval(GAMBLER_SYSTEM_INTERVAL_TELE_CHECK);
}

GamblingSystem::~GamblingSystem()
{
	AcquireMatchLock();
	GamblerMatchMap::iterator Itr;
	for(Itr = m_matchStorage.begin(); Itr != m_matchStorage.end(); ++Itr)
		delete Itr->second;
	m_matchStorage.clear();
	ReleaseMatchLock();
}

// Creation
void GamblingSystem::Initalize()
{
	LoadConfigData();
	_loadPastMatches();
	new GamblerDuelScript();
}

// Events
// Called on every world tick (don't execute too heavy code here).
void GamblingSystem::OnUpdate(uint32 diff)
{
	if(m_checkMatches.GetCurrent() >= 0)
		m_checkMatches.Update(diff);
	else
		m_checkMatches.SetCurrent(0);
	if(m_checkMatches.Passed())
		m_checkMatches.Reset();

	AcquireMatchLock();
	GamblerMatchMap::iterator Itr;
	for(Itr = m_matchStorage.begin(); Itr != m_matchStorage.end(); ++Itr)
	{
		if(Itr->second->GetMatchStatus() != GAMBLER_MATCH_STATUS_TELEPORT)
			continue;

		Player *pChallenger = sObjectMgr->GetPlayer(Itr->second->GetChallengerGUID());
		Player *pDefender	= sObjectMgr->GetPlayer(Itr->second->GetDefenderGUID());
		
		if(pChallenger == NULL || pDefender == NULL)
			continue;
		if(pChallenger->IsBeingTeleported() || pChallenger->isBeingLoaded() || pDefender->IsBeingTeleported() || pDefender->isBeingLoaded())
			continue;

		Itr->second->SetMatchStatus(GAMBLER_MATCH_STATUS_RUNNING);
	}
	ReleaseMatchLock();
}

// Database Interaction
void GamblingSystem::LoadConfigData()
{
	m_minRequiredLevel      = 255;
	m_maxLevelDiff	   = 5;
	m_maxBet		   = 100;
	m_awardFled		   = false;
	m_enableGM		   = false;
	m_enableSameip	   = false;
    m_enableLimits	   = false;
    m_onlyCurrency	   = false;
    m_equalDuels	   	   = false;
	QueryResult queryResult = CharacterDatabase.Query("SELECT optionIndex, optionValue FROM custom_duel_config");
	if(!queryResult){
		sLog->outError("GamblingSystem: Unable to load duel_config, result was not returned");
		return;
	}else{
		do
		{
			Field *Fields = queryResult->Fetch();
			switch(Fields[0].GetUInt32())
			{
				case GAMBLER_CONFIG_OPTION_MAPID:				m_arenaCoords.m_mapId		= Fields[1].GetUInt32();	break;
				case GAMBLER_CONFIG_OPTION_COORDSX:				m_arenaCoords.m_positionX	= Fields[1].GetFloat();		break;
				case GAMBLER_CONFIG_OPTION_COORDSY:				m_arenaCoords.m_positionY	= Fields[1].GetFloat();		break;
				case GAMBLER_CONFIG_OPTION_COORDSZ:				m_arenaCoords.m_positionZ	= Fields[1].GetFloat();		break;
				case GAMBLER_CONFIG_OPTION_COORDSO:				m_arenaCoords.m_orientation	= Fields[1].GetFloat();		break;
				case GAMBLER_CONFIG_OPTION_MIN_REQUIREDLEVEL:	m_minRequiredLevel			= Fields[1].GetUInt32();	break;
				case GAMBLER_CONFIG_OPTION_MAX_LEVELDIFF:		m_maxLevelDiff				= Fields[1].GetUInt32();	break;
				case GAMBLER_CONFIG_OPTION_AWARD_FLED:			m_awardFled					= Fields[1].GetBool();		break;
				case GAMBLER_CONFIG_OPTION_MAX_BET:				m_maxBet					= Fields[1].GetUInt32();	break;
				case GAMBLER_CONFIG_OPTION_ENABLE_GM:			m_enableGM					= Fields[1].GetBool();		break;
				case GAMBLER_CONFIG_OPTION_ENABLE_SAMEIP:		m_enableSameip				= Fields[1].GetBool();		break;
                case GAMBLER_CONFIG_OPTION_ENABLE_LIMITS:		m_enableLimits				= Fields[1].GetBool();		break;
                case GAMBLER_CONFIG_OPTION_ONLY_CURRENCY:		m_onlyCurrency				= Fields[1].GetBool();		break;
               	case GAMBLER_CONFIG_OPTION_EQUAL_DUELS:			m_equalDuels				= Fields[1].GetBool();		break;
			}
		}while(queryResult->NextRow());
	}

	if(m_maxBet > GAMBLER_SYSTEM_TOTAL_MAX_BET){
		m_maxBet = GAMBLER_SYSTEM_TOTAL_MAX_BET;
	}

	if(QueryResult queryResult = CharacterDatabase.Query("SELECT MAX(`matchId`) FROM `custom_duel_storage`"))
		m_highMatchId = queryResult->Fetch()[0].GetUInt32();
	else
		m_highMatchId = 0;

	return;
}

void GamblingSystem::_loadPastMatches()
{
	if(QueryResult queryResult = CharacterDatabase.Query("SELECT * FROM `custom_duel_storage`"))
	{
		do
		{
			GamblerMatchData *matchData = new GamblerMatchData(queryResult->Fetch());
			if(matchData->GetMatchWinner() == 0)
			{
				_createItemAndMailToPlayer(NULL, matchData->GetChallengerGUID(), matchData->GetChallengerItemId(), matchData->GetChallengerItemCount(), GAMBLER_SYSTEM_MSG_MAIL_BODY_MATCH_INCOMPLETE);
				_createItemAndMailToPlayer(NULL, matchData->GetDefenderGUID(), matchData->GetDefenderItemId(), matchData->GetDefenderItemCount(), GAMBLER_SYSTEM_MSG_MAIL_BODY_MATCH_INCOMPLETE);
				continue;
			}
			AcquireMatchLock();
			m_matchStorage.insert(make_pair(matchData->GetMatchId(), matchData));
			ReleaseMatchLock();
		}while(queryResult->NextRow());
	}
	CharacterDatabase.PExecute("DELETE FROM `custom_duel_storage` WHERE `matchWinner` = '0'");
}

void GamblingSystem::_saveCurrentMatchProgress(GamblerMatchData *matchData)
{
	if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT * FROM `custom_duel_storage` WHERE `matchId` = '%u'", matchData->GetMatchId()))
		CharacterDatabase.PExecute("UPDATE `custom_duel_storage` SET `matchWinner` = '%u'", matchData->GetMatchWinner());
	else
		CharacterDatabase.PExecute("INSERT INTO `custom_duel_storage` VALUES ('%u', '%u', '%u', '%u', '%u', '%u', '%u', NOW(), '%u')", matchData->GetMatchId(), matchData->GetChallengerGUID(), matchData->GetDefenderGUID(), matchData->GetChallengerItemId(),matchData->GetChallengerItemCount(), matchData->GetDefenderItemId(),matchData->GetDefenderItemCount(), matchData->GetMatchWinner());
}

void GamblingSystem::_updatePlayerStats(uint32 playerGUID, GamblerPlayerStatIndex statIndex, uint32 statIncreaseValue)
{
	if(statIndex > GAMBLER_PLAYER_STAT_MAX)
	{
		sLog->outError("GamblingSystem: _updatePlayerStats statIndex out of range");
		return;
	}
	if(QueryResult queryResult = CharacterDatabase.PQuery("SELECT `%s` FROM `custom_duel_statistics` WHERE `%s` = '%u'", GamblerPlayerStatFields[statIndex], GamblerPlayerStatFields[GAMBLER_PLAYER_STAT_GUID], playerGUID))
		CharacterDatabase.PExecute("UPDATE `custom_duel_statistics` SET `%s` = '%u' WHERE `%s` = '%u'", GamblerPlayerStatFields[statIndex], queryResult->Fetch()[0].GetUInt32()+statIncreaseValue, GamblerPlayerStatFields[GAMBLER_PLAYER_STAT_GUID], playerGUID);
	else
		CharacterDatabase.PExecute("INSERT INTO `custom_duel_statistics` (`%s`,`%s`) VALUES('%u', '%u')", GamblerPlayerStatFields[GAMBLER_PLAYER_STAT_GUID], GamblerPlayerStatFields[statIndex], playerGUID, statIncreaseValue);
}

// Match Data Retrieval
GamblerMatchData *GamblingSystem::GetMatchDataBy(Player *pPlayer)
{
	AcquireMatchLock();
	GamblerMatchMap::iterator Itr;
	for(Itr = m_matchStorage.begin(); Itr != m_matchStorage.end(); ++Itr)
	{
		if(Itr->second->GetChallengerGUID() == pPlayer->GetGUIDLow() || Itr->second->GetDefenderGUID() == pPlayer->GetGUIDLow())
		{
			// Match is over, old data
			if(Itr->second->GetMatchWinner())
				continue;
			ReleaseMatchLock();
			return Itr->second;
		}
	}
	ReleaseMatchLock();
	return NULL;
}

// Match Requirements Checking
bool GamblingSystem::CanHaveMatch(Player *pChallenger, Player *pDefender)
{

	// if same ip dueling is enabled in configuration
	/*if(m_enableSameip == 1){
		// no multibox or dueling with same ip
		if(pChallenger->GetSession()->GetRemoteAddress().compare(pDefender->GetSession()->GetRemoteAddress()) == 0)
			return false;
	}*/
	
	// no dueling on the same account
	if(pChallenger->GetSession()->GetAccountId() == pDefender->GetSession()->GetAccountId())
		return false;

	// no dueling if any of the players are logging out!
	if(pChallenger->GetSession()->isLogingOut() || pDefender->GetSession()->isLogingOut())
		return false;

	// No dueling if player already has a duel record in progress
	if(GetMatchDataBy(pChallenger) || GetMatchDataBy(pDefender))
		return false;

	// No dueling if you don't meet the level requirement in the database
	uint32 m_minRequiredLevel = 0;
	if(pChallenger->getLevel() <= m_minRequiredLevel || pDefender->getLevel() <= m_minRequiredLevel)
		return false;

	return true;
}

// Match Setup
void GamblingSystem::SetupMatch(Player *pChallenger, Player *pDefender)
{
	GamblerMatchData *matchData = new GamblerMatchData(_generateMatchId(), pChallenger->GetGUIDLow(), pDefender->GetGUIDLow());
	AcquireMatchLock();
	m_matchStorage.insert(make_pair(matchData->GetMatchId(), matchData));
	ReleaseMatchLock();
}

std::string GamblingSystem::GetQualityColor(int32 qualityType) const
{
	switch(qualityType)
	{
		case ITEM_QUALITY_POOR:
		{
			return QUALITY_POOR;
		}break;
		case ITEM_QUALITY_NORMAL:
		{
			return QUALITY_NORMAL;
		}break;
		case ITEM_QUALITY_UNCOMMON:
		{
			return QUALITY_UNCOMMON;
		}break;
		case ITEM_QUALITY_RARE:
		{
			return QUALITY_RARE;
		}break;
		case ITEM_QUALITY_EPIC:
		{
			return QUALITY_EPIC;
		}break;
		case ITEM_QUALITY_LEGENDARY:
		{
			return QUALITY_LEGENDARY;
		}break;
		case ITEM_QUALITY_ARTIFACT:
		{
			return QUALITY_ARTIFACT;
		}break;
		case ITEM_QUALITY_HEIRLOOM:
		{
			return QUALITY_HEIRLOOM;
		}break;
	}
	return false;
}

bool GamblingSystem::AddItemForMatch(Player *pPlayer, std::string itemName)
{
	GamblerMatchData *matchData = GetMatchDataBy(pPlayer);
	if(matchData == NULL)
		return false; 

	WorldDatabase.EscapeString(itemName);
	if(QueryResult queryResult = WorldDatabase.PQuery("SELECT `entry` FROM `item_template` WHERE `name` = '%s'", itemName.c_str()))
	{
		uint32 itemId = queryResult->Fetch()[0].GetUInt32();

		ItemTemplate const *itemProto = sObjectMgr->GetItemTemplate(itemId);
		if(Item *pItem = pPlayer->GetItemByEntry(itemId))
		{
            // if its currency
            if(itemProto->BagFamily & BAG_FAMILY_MASK_CURRENCY_TOKENS)
            {
                if(pItem == NULL)
                    return false;
            }else{ // if its a normal item, check if its valid.
                if(_checkItemValidity(pItem) == false)
				    return false;
            }

            if(m_enableLimits == 1){ // if item limits are enabled, check them.
                if(_checkWithinLimits(pItem) == false)
                    return false;
            }
			if(matchData->IsChallenger(pPlayer)){
				matchData->SetChallengerItemId(itemId);
			}
			else{
				matchData->SetDefenderItemId(itemId);
			}
			return true;
		}
	}
	return false;
}

bool GamblingSystem::AddItemAmountForMatch(Player *pPlayer, uint32 amount)
{
	GamblerMatchData *matchData = GetMatchDataBy(pPlayer);
	if(matchData == NULL)
		return false; 

	uint32 itemId = matchData->GetItemIdBy(pPlayer);
	ItemTemplate const *itemProto = sObjectMgr->GetItemTemplate(itemId);

	if(Item *pItem = pPlayer->GetItemByEntry(itemId))
	{
        // if duels must be equal, then challenger item count must equal defender item count.
        if(m_equalDuels == 1){
            // if the player is challenger and his amount is not equal to the defender's item count, return false.
            if(matchData->IsChallenger(pPlayer) && matchData->GetDefenderItemCount() != 0 && amount != matchData->GetDefenderItemCount())
                return false;
		    // if the player is defender and his amount is not equal to challenger's item count, return false.
            else if(matchData->IsDefender(pPlayer)  && matchData->GetChallengerItemCount() != 0 && amount != matchData->GetChallengerItemCount())
			    return false;
        }

		if(amount > m_maxBet)
			return false;

              if(!pPlayer->HasItemCount(itemId,amount))
			return false;

		if(matchData->IsChallenger(pPlayer)){
			matchData->SetChallengerItemCount(amount);
		}
		else{
			matchData->SetDefenderItemCount(amount);
		}
			
		Player *secondPlayer = NULL;
		if(matchData->IsChallenger(pPlayer))
			secondPlayer = sObjectMgr->GetPlayer(matchData->GetDefenderGUID());
		else
			secondPlayer = sObjectMgr->GetPlayer(matchData->GetChallengerGUID());
		if(secondPlayer)
			ChatHandler(secondPlayer).PSendSysMessage("|cffffffffThe player |cff00ccff%s |cffffffffhas bet |cff00ccff%u|cffffffffx of the item |%s|Hitem:%u:0:0:0:0:0:0:0:%u|h[%s]|h|r", pPlayer->GetName(), amount, GetQualityColor(itemProto->Quality).c_str(),  pItem->GetEntry(), pPlayer->getLevel(),  itemProto->Name1.c_str());
		return true;
	}
	return false;
}

void GamblingSystem::AcceptChallenge(Player *pPlayer)
{
	GamblerMatchData *matchData = GetMatchDataBy(pPlayer);
	if(matchData == NULL)
		return;
	if(matchData->IsChallenger(pPlayer))
		matchData->SetChallengerReady(true);
	else
		matchData->SetDefenderReady(true);
	if(matchData->GetChallengerReady() && matchData->GetDefenderReady())
	{
		Player *secondPlayer = NULL;

		if(matchData->IsChallenger(pPlayer)){
			secondPlayer = sObjectMgr->GetPlayer(matchData->GetDefenderGUID());}
		else{
			secondPlayer = sObjectMgr->GetPlayer(matchData->GetChallengerGUID());}

		// Don't start the duel if there is no second player
		if(secondPlayer == NULL)
		{
			ChatHandler(pPlayer).PSendSysMessage(GAMBLER_SYSTEM_MSG_CANT_LOCATE_PLAYER);
			_deleteMatchData(matchData->GetMatchId());
			return;
		}
		// Don't start the duel if they are already in a duel
		if(secondPlayer->duel || pPlayer->duel)
		{
			SendMessageToPlayers(matchData, GAMBLER_SYSTEM_MSG_CANT_START_DUEL);
			_deleteMatchData(matchData->GetMatchId());
			return;
		}
		// Don't start the duel if they are already InCombat
		if(secondPlayer->isInCombat() || pPlayer->isInCombat())
		{
			SendMessageToPlayers(matchData, GAMBLER_SYSTEM_MSG_CANT_START_DUEL);
			_deleteMatchData(matchData->GetMatchId());
			return;
		}
		// Don't start the duel if the players are logging out
		if(secondPlayer->GetSession()->isLogingOut() || pPlayer->GetSession()->isLogingOut())
		{
			SendMessageToPlayers(matchData, GAMBLER_SYSTEM_MSG_CANT_START_LOGGING);
			_deleteMatchData(matchData->GetMatchId());
			return;
		}

		uint32 itemId1 = matchData->IsChallenger(pPlayer) ? matchData->GetChallengerItemId() : matchData->GetDefenderItemId();
		uint32 itemId2 = matchData->IsChallenger(secondPlayer) ? matchData->GetChallengerItemId() : matchData->GetDefenderItemId();

		uint32 amount1 = matchData->IsChallenger(pPlayer) ? matchData->GetChallengerItemCount() : matchData->GetDefenderItemCount();
		uint32 amount2 = matchData->IsChallenger(secondPlayer) ? matchData->GetChallengerItemCount() : matchData->GetDefenderItemCount();

        ItemTemplate const *Proto1 = sObjectMgr->GetItemTemplate(itemId1);
        ItemTemplate const *Proto2 = sObjectMgr->GetItemTemplate(itemId2);

        if(Proto1->BagFamily & BAG_FAMILY_MASK_CURRENCY_TOKENS || Proto2->BagFamily & BAG_FAMILY_MASK_CURRENCY_TOKENS){
            // Missing data here, not important.
        }else if(_checkItemValidity(pPlayer->GetItemByEntry(itemId1)) == false || _checkItemValidity(secondPlayer->GetItemByEntry(itemId2)) == false){
			SendMessageToPlayers(matchData, GAMBLER_SYSTEM_MSG_ITEM_VALIDATE_FAIL);
			_deleteMatchData(matchData->GetMatchId());
			return;
        }

		// Don't start the duel if the players don't have the item in inventory
		if(pPlayer->GetItemCount(itemId1) == 0 || secondPlayer->GetItemCount(itemId2) == 0)
		{
			SendMessageToPlayers(matchData, GAMBLER_SYSTEM_MSG_ITEM_NO_INV);
			_deleteMatchData(matchData->GetMatchId());
			return;
		}

		// Don't start the duel if the players don't have the amount of items betted
		if(!pPlayer->GetItemCount(itemId1, amount1)  || !secondPlayer->GetItemCount(itemId2, amount2))
		{
			SendMessageToPlayers(matchData, ARENA_GAMBLER_MSG_BET_AMOUNT_FAILED);
			_deleteMatchData(matchData->GetMatchId());
			return;
		}

		// Don't start the duel if the players have betted more than the maximum specified in configuration
		if(pPlayer->GetItemCount(amount1) > m_maxBet || secondPlayer->GetItemCount(amount2) > m_maxBet)
		{
			SendMessageToPlayers(matchData, ARENA_GAMBLER_MSG_BET_ADD_FAILED, m_maxBet);
			_deleteMatchData(matchData->GetMatchId());
			return;
		}

		_saveCurrentMatchProgress(matchData);
		_updatePlayerStats(pPlayer->GetGUIDLow(), GAMBLER_PLAYER_STAT_DUELS_TOTAL, 1);
		_updatePlayerStats(secondPlayer->GetGUIDLow(), GAMBLER_PLAYER_STAT_DUELS_TOTAL, 1);

		pPlayer->DestroyItemCount(itemId1, amount1, true, true);
		secondPlayer->DestroyItemCount(itemId2, amount2, true, true);

		pPlayer->SaveToDB();
		secondPlayer->SaveToDB();

		SendMessageToPlayers(matchData, GAMBLER_SYSTEM_MSG_MATCH_STARTING);
		
		pPlayer->SetBattlegroundEntryPoint();
		secondPlayer->SetBattlegroundEntryPoint();
		switch (urand(0,3))
              {
				case 0: pPlayer->TeleportTo(0, -1138.605225f, 1467.949585f, 54.166855f, 4.980240f);
					 secondPlayer->TeleportTo(0, -1138.605225f, 1467.949585f, 54.166855f, 4.980240f);
					 break;
				case 1: pPlayer->TeleportTo(0, -1121.683960f, 1433.243652f, 54.166855f, 3.064653f);
					 secondPlayer->TeleportTo(0, -1121.683960f, 1433.243652f, 54.166855f, 3.064653f);
					 break;
				case 2: pPlayer->TeleportTo(0, -1171.607178f, 1410.523926f, 54.166855f, 1.240173f);
					 secondPlayer->TeleportTo(0, -1171.607178f, 1410.523926f, 54.166855f, 1.240173f);
					 break;
				case 3: pPlayer->TeleportTo(0, -1180.112183f, 1451.894287f, 54.166855f, 5.848103f);
					 secondPlayer->TeleportTo(0, -1180.112183f, 1451.894287f, 54.166855f, 5.848103f);
					 break;
              }
		pPlayer->CastSpell(secondPlayer, 7266, true);
		matchData->SetMatchStatus(GAMBLER_MATCH_STATUS_TELEPORT);
	}
	else
		SendMessageToPlayers(matchData, GAMBLER_SYSTEM_MSG_ACCEPTED_CHALLENGE, pPlayer->GetName());
}

void GamblingSystem::CancelChallenge(Player *pPlayer)
{
	GamblerMatchData *matchData = GetMatchDataBy(pPlayer);
	if(matchData == NULL)
		return;
	SendMessageToPlayers(matchData, GAMBLER_SYSTEM_MSG_CANCELED, pPlayer->GetName(), matchData->GetChallengerGUID() == pPlayer->GetGUIDLow() ? GAMBLER_SYSTEM_MSG_CANCELED_1 : GAMBLER_SYSTEM_MSG_CANCELED_2);
	if(matchData->IsDefender(pPlayer))
		_updatePlayerStats(pPlayer->GetGUIDLow(), GAMBLER_PLAYER_STAT_DUELS_REFUSED, 1);
	_deleteMatchData(matchData->GetMatchId());
}

// Match Completion
void GamblingSystem::HandleMatchComplete(Player *pWinner, Player *pLoser, GamblerMatchData *matchData, DuelCompleteType completeType)
{
	uint32 itemId1 = matchData->IsChallenger(pWinner) ? matchData->GetChallengerItemId() : matchData->GetDefenderItemId();
	uint32 itemId2 = matchData->IsChallenger(pLoser) ? matchData->GetChallengerItemId() : matchData->GetDefenderItemId();
	uint32 amount1 = matchData->IsChallenger(pWinner) ? matchData->GetChallengerItemCount() : matchData->GetDefenderItemCount();
	uint32 amount2 = matchData->IsChallenger(pLoser) ? matchData->GetChallengerItemCount() : matchData->GetDefenderItemCount();
	switch(completeType)
	{
		case DUEL_INTERRUPTED:
		{
			_createItemAndMailToPlayer(pWinner, pWinner->GetGUIDLow(), itemId1, amount1, GAMBLER_SYSTEM_MSG_MAIL_BODY_MATCH_INCOMPLETE);
			_createItemAndMailToPlayer(pLoser, pLoser->GetGUIDLow(), itemId2, amount2, GAMBLER_SYSTEM_MSG_MAIL_BODY_MATCH_INCOMPLETE);
			SendMessageToPlayers(matchData, GAMBLER_SYSTEM_MSG_DUEL_INTERRUPTED);
		}break;
		case DUEL_WON:
		{
			_createItemAndMailToPlayer(pWinner, pWinner->GetGUIDLow(), itemId1, amount1, GAMBLER_SYSTEM_MSG_MAIL_BODY_MATCH_WON);
			_createItemAndMailToPlayer(pWinner, pWinner->GetGUIDLow(), itemId2, amount2, GAMBLER_SYSTEM_MSG_MAIL_BODY_MATCH_WON);
			SendMessageToPlayers(matchData, GAMBLER_SYSTEM_MSG_DUEL_WON, pWinner->GetName());
		}break;
		case DUEL_FLED:
		{
			if(m_awardFled)
			{
				_createItemAndMailToPlayer(pWinner, pWinner->GetGUIDLow(), itemId1, amount1, GAMBLER_SYSTEM_MSG_MAIL_BODY_MATCH_WON);
				_createItemAndMailToPlayer(pWinner, pWinner->GetGUIDLow(), itemId2, amount2, GAMBLER_SYSTEM_MSG_MAIL_BODY_MATCH_WON);
				SendMessageToPlayers(matchData, GAMBLER_SYSTEM_MSG_DUEL_WON, pWinner->GetName());
				
			}else{
				_createItemAndMailToPlayer(pWinner, pWinner->GetGUIDLow(), itemId1, amount1, GAMBLER_SYSTEM_MSG_MAIL_BODY_MATCH_INCOMPLETE);
				_createItemAndMailToPlayer(pLoser, pLoser->GetGUIDLow(), itemId2, amount2, GAMBLER_SYSTEM_MSG_MAIL_BODY_MATCH_INCOMPLETE);
				SendMessageToPlayers(matchData, GAMBLER_SYSTEM_MSG_DUEL_FLED_NON_AWARD);
			}
		}break;
	}
	_updatePlayerStats(pWinner->GetGUIDLow(), GAMBLER_PLAYER_STAT_DUELS_WON, 1);
	_updatePlayerStats(pLoser->GetGUIDLow(), GAMBLER_PLAYER_STAT_DUELS_LOST, 1);
	matchData->SetMatchWinner(pWinner->GetGUIDLow());
	_saveCurrentMatchProgress(matchData);
	_deleteMatchData(matchData->GetMatchId());
	pWinner->TeleportToBGEntryPoint();
	pLoser->TeleportToBGEntryPoint();
}

// Match Data
void GamblingSystem::_deleteMatchData(Player *pPlayer)
{
	AcquireMatchLock();
	GamblerMatchMap::iterator Itr;
	for(Itr = m_matchStorage.begin(); Itr != m_matchStorage.end(); ++Itr)
	{
		if(Itr->second->GetChallengerGUID() == pPlayer->GetGUIDLow() || Itr->second->GetDefenderGUID() == pPlayer->GetGUIDLow())
		{
			delete Itr->second;
			m_matchStorage.erase(Itr);
			break;
		}
	}
	ReleaseMatchLock();
}

bool GamblingSystem::_checkItemValidity(Item *pItem)
{
	if(pItem == NULL || pItem->IsSoulBound() || pItem->IsBoundAccountWide() || pItem->IsBoundByEnchant())
		return false;
	return true;
}

bool GamblingSystem::_checkWithinLimits(Item *pItem)
{
	/*
	* Here you can add your items that you want players to be able to use in the system. this is temporary.
	* uint32 GAMBLER_SYSTEM_ITEM_LIMITS [] = {ITEMID1,ITEMID2,ITEMID3};
	*/
    uint32 GAMBLER_SYSTEM_ITEM_LIMITS [] = {20559};
    for (uint32 i = 0; i < sizeof(GAMBLER_SYSTEM_ITEM_LIMITS)/sizeof(uint32); ++i){
        if (pItem->GetEntry() == GAMBLER_SYSTEM_ITEM_LIMITS[i])
            return true;
    }
    return false;
}

void GamblingSystem::_deleteMatchData(uint32 matchId)
{
	AcquireMatchLock();
	GamblerMatchMap::iterator Itr = m_matchStorage.find(matchId);
	if(Itr != m_matchStorage.end())
		m_matchStorage.erase(Itr);
	ReleaseMatchLock();
}

uint32 GamblingSystem::_generateMatchId()
{
	m_highMatchId++;
	return m_highMatchId;
}

// Messaging
void GamblingSystem::SendMessageToPlayers(GamblerMatchData *matchData, const char *msgToSend, ...)
{
	Player *pChallenger = sObjectMgr->GetPlayer(matchData->GetChallengerGUID());
	Player *pDefender	= sObjectMgr->GetPlayer(matchData->GetDefenderGUID());
	
	char Result[1024];
	va_list List;
	va_start(List, msgToSend);
	vsnprintf(Result, 1024, msgToSend, List);
	va_end(List);

	if(pChallenger)
		ChatHandler(pChallenger).PSendSysMessage(Result);
	if(pDefender)
		ChatHandler(pDefender).PSendSysMessage(Result);
}

// Mail System
void GamblingSystem::_createItemAndMailToPlayer(Player *pPlayer, uint32 playerGUID, uint32 itemId, uint32 amount, std::string mailMessage)
{
	MailSender toSend(MAIL_NORMAL, playerGUID, GAMBLER_SYSTEM_MAIL_TYPE);
	SQLTransaction trans = CharacterDatabase.BeginTransaction();
	MailDraft mailDraft(GAMBLER_SYSTEM_MSG_MAIL_SUBJECT, mailMessage.c_str());

	// extract items
    typedef std::pair<uint32, uint32> ItemPair;
    typedef std::list< ItemPair > ItemPairs;
    ItemPairs items;
    ItemTemplate const* item_proto = sObjectMgr->GetItemTemplate(itemId);
    while (amount > item_proto->GetMaxStackSize())
    {
        items.push_back(ItemPair(itemId, item_proto->GetMaxStackSize()));
        amount -= item_proto->GetMaxStackSize();
    }
    items.push_back(ItemPair(itemId, amount));

	// TODO: items to be send is higher than the maximum items that a mail can hold!, security measure.
	if (items.size() > MAX_MAIL_ITEMS){}

	for(ItemPairs::const_iterator itr = items.begin(); itr != items.end(); ++itr)
    {
		if (Item* pItem = Item::CreateItem(itr->first, itr->second,pPlayer))
        {
           pItem->SaveToDB(trans);   // save for prevent lost at next mail load, if send fail then item will deleted
		   mailDraft.AddItem(pItem);
        }
    }

	if(pPlayer){
		mailDraft.SendMailTo(trans, MailReceiver(pPlayer), toSend);
	}
	else{
		mailDraft.SendMailTo(trans, MailReceiver(playerGUID), toSend);
	}
	CharacterDatabase.CommitTransaction(trans);
}

// Called when a duel begins, check if both players have match data with each other
void GamblerDuelScript::OnDuelRequest(Player *pDefender, Player *pChallenger)
{
	// To make sure we have the players and bug reporting
	if(pDefender == NULL || pChallenger == NULL){
		sLog->outError("GamblerDuelScript: OnDuelEnd pDefender or pChallenger is NULL!");
		return;}

	GamblerMatchData *ChallengerMatchData = sGamblingSystem.GetMatchDataBy(pChallenger);
	GamblerMatchData *DefenderMatchData = sGamblingSystem.GetMatchDataBy(pDefender);

    // if challenger or defender has no existing match data, return.
	if(ChallengerMatchData == NULL || DefenderMatchData == NULL){
		return;
    }// if challenger or defender has match data existing
    else{
        // if challenger's match id is not the same as the defender, and they both have match data.
        // then challenger has requested duel from someone else with match data.
        if(ChallengerMatchData->GetMatchId() != DefenderMatchData->GetMatchId()){
            ChatHandler(pChallenger).SendSysMessage(ARENA_GAMBLER_MSG_NOT_SAME_PLAYER);
            sGamblingSystem.CancelChallenge(pChallenger);
        }
        // if the challenger has not set ready, or the defender has not set ready!
        if(ChallengerMatchData->HasSetReady(pChallenger) == false || ChallengerMatchData->HasSetReady(pDefender) == false){
            ChatHandler(pChallenger).SendSysMessage(ARENA_GAMBLER_MSG_NOT_READY);
            sGamblingSystem.CancelChallenge(pChallenger);
        }
        // if challenger has no item id set, or defender has no item id set!
        if(ChallengerMatchData->GetChallengerItemId() == NULL || ChallengerMatchData->GetDefenderItemId() == NULL){
            ChatHandler(pChallenger).SendSysMessage(ARENA_GAMBLER_MSG_NO_ITEM);
            sGamblingSystem.CancelChallenge(pChallenger);
        }
        // if challenger has not set item count yet, or defender has not set item count yet!
        if(ChallengerMatchData->GetChallengerItemCount() == NULL || ChallengerMatchData->GetDefenderItemCount() == NULL){
            ChatHandler(pChallenger).SendSysMessage(ARENA_GAMBLER_MSG_NO_AMOUNT);
            sGamblingSystem.CancelChallenge(pChallenger);
        }
            
    }
}

// Called when a duel ends, check if there is a match running or not.
void GamblerDuelScript::OnDuelEnd(Player *pWinner, Player *pLoser, DuelCompleteType type)
{
	// To make sure we have the players and bug reporting
	if(pWinner == NULL || pLoser == NULL){
		sLog->outError("GamblerDuelScript: OnDuelEnd pWinner or pLoser is NULL!");
		return;}

	GamblerMatchData *WinnerData = sGamblingSystem.GetMatchDataBy(pWinner);
	GamblerMatchData *LoserData = sGamblingSystem.GetMatchDataBy(pLoser);

	if(WinnerData == NULL || LoserData == NULL){
		return;}
	else if(WinnerData->GetMatchId() == LoserData->GetMatchId()){
	sGamblingSystem.HandleMatchComplete(pWinner, pLoser, WinnerData, type);
	}
}

// Called when a player logsout, if a player exists, check match data, if it started, if yes then complete the duel
void GamblerDuelScript::OnLogout(Player *pPlayer)
{
	// To make sure we have the player and bug reporting
	if(pPlayer == NULL){
		sLog->outError("GamblerDuelScript: OnLogout pPlayer is NULL!");
		return;}

	GamblerMatchData *matchData = sGamblingSystem.GetMatchDataBy(pPlayer);
	if(matchData == NULL){
		return;}
	else if(matchData->MatchStarted() && (matchData->GetChallengerGUID() == pPlayer->GetGUIDLow() || matchData->GetDefenderGUID() == pPlayer->GetGUIDLow()))
			pPlayer->DuelComplete(DUEL_FLED);
}