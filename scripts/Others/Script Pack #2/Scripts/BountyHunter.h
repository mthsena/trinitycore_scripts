#include "ScriptPCH.h"
#include <cstring>
#include <string.h>

#define SELECT_BOUNTY "I would like to place a bounty!"
#define NVM "Goodbye."
#define WIPE_BOUNTY "[GM] Truncate bounties table!!"
#define BOUNTY_SCRIPT_NAME "Bountyhunter_Item"

#define EXPIRE_TIME_SECS 86400 // 1 hour expire time
#define MONEY_TAX 0.90
#define BOUNTY_LIMIT 64
#define BOUNTY_MARKER 64328

#define B_TOKEN_ID 64328

// list of bounty prices.
uint32 bountyPrices[] = {5, 10, 25, 50, 75, 100, 250, 500};

uint32 bountyPriceOptions = sizeof(bountyPrices) / sizeof(uint32);

enum BountyGossipText
{
    BOUNTY_TEXT_HELLO = 11100,
    BOUNTY_TEXT_FULL = 11101,
    BOUNTY_TEXT_PRICES = 11102,
    BOUNTY_TEXT_NO_BOUNTIES = 11103, 
    BOUNTY_TEXT_JUST_RAN_OUT = 11104,
    BOUNTY_TEXT_BOUNTY_LIST = 11105, 
    BOUNTY_TEXT_BOUNTY_INFO = 11106,
    BOUNTY_TEXT_ERROR_HAPPENED = 11107,
};

enum BountyGossipMenuOptions
{
    OPTION_SELECT_BOUNTY = GOSSIP_ACTION_INFO_DEF + 1,
    OPTION_SHOW_BOUNTIES = GOSSIP_ACTION_INFO_DEF + 2,
    OPTION_GOODBYE = GOSSIP_ACTION_INFO_DEF + 3,
    OPTION_TRUNCATE = GOSSIP_ACTION_INFO_DEF + 4,
    GOSSIP_PRICE_START = GOSSIP_ACTION_INFO_DEF + 5,
};

uint32 GOSSIP_PRICE_MAX = GOSSIP_ACTION_INFO_DEF + 5 + bountyPriceOptions;
uint32 GOSSIP_AFTER_PRICES = GOSSIP_ACTION_INFO_DEF + 6 + bountyPriceOptions;

struct BountyData
{
    uint32 guid;
    uint32 posterguid;
    uint32 money;
    time_t expiretime;
    uint32 index;
};


static std::map<uint32, BountyData> bountyMap;

uint32 bountyIndex[BOUNTY_LIMIT] = {0};


uint32 findUnusedIndex() {
    for(uint32 i = 0; i < BOUNTY_LIMIT; i++) {
        if(bountyIndex[i] == 0) {
            return i;
        }
    }
    return BOUNTY_LIMIT;
}


BountyData* getBountyByGuid(uint32 guid)
{
    std::map<uint32, BountyData>::iterator itr = bountyMap.find(guid);
    return (itr != bountyMap.end()) ? &itr->second : NULL;
}

BountyData* FindBountyByIndex(uint32 index) {
    std::map<uint32, BountyData>::iterator itr = bountyMap.begin();
    uint32 pos = 0;
    for(; itr != bountyMap.end(); ++itr, pos++) {
        if (pos == index) {
            return &itr->second;
        }
    }
    return NULL;
}


std::string UInt32ToString(uint32 integer) {
    std::stringstream out;
    out << integer;
    return out.str();
}