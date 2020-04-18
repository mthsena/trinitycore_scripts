#include "BountyHunter.h"

class BountyHunter : public CreatureScript
{
private:
    void LoadBounties() 
    {
        uint32 oldMSTime = getMSTime();
        time_t currentTime = time(NULL);

        QueryResult result = CharacterDatabase.Query("SELECT * FROM bounties");
        if(!result)
        {
            sLog->outString(">> Loaded 0 bounties.");
            sLog->outString();
            return;
        }

        Field *fields;
        uint32 count = 0;
        do
        {
            fields = result->Fetch();
            BountyData bounty;
            bounty.guid = fields[0].GetUInt32();
            bounty.posterguid = fields[1].GetUInt32();
            bounty.money = fields[2].GetUInt32();
            bounty.expiretime = fields[3].GetUInt32();

            if(bounty.expiretime < currentTime) 
            {
                sLog->outError("Bounty on %u from %u has expired! Deleting from DB...", bounty.guid, bounty.posterguid);
                ExpireBounty(&bounty, true, false, false);
            }
            else 
            {
                bounty.index = count;
                bountyIndex[bounty.index] = bounty.guid;
                bountyMap[bounty.guid] = bounty;

                count++;
            }
        } while(result->NextRow());

        sLog->outString(">> Loaded %u bounties in %u ms!", count, GetMSTimeDiffToNow(oldMSTime));
        sLog->outString();
    }

    void SaveAllBounties() {
        if(bountyMap.size() == 0) {
            CharacterDatabase.Execute("TRUNCATE TABLE bounties");
            return;
        }
        time_t currentTime = time(NULL);
        SQLTransaction trans = CharacterDatabase.BeginTransaction();
        trans->Append("TRUNCATE TABLE bounties");

        std::map<uint32, BountyData>::iterator iter;
        std::map<uint32, BountyData>::iterator end;
        for(iter = bountyMap.begin(), end = bountyMap.end(); iter != end; ++iter) {
            BountyData *bounty = &iter->second;
            if(bounty->expiretime < currentTime) 
            {
                ExpireBounty(bounty);
                bountyMap.erase(iter);
            } 
            else 
            {
                trans->PAppend("INSERT INTO bounties VALUES('%u', '%u', '%u', '%u')", bounty->guid, bounty->posterguid, bounty->money, bounty->expiretime);
            }
        }
        CharacterDatabase.CommitTransaction(trans);
    }

    void SaveBounty(BountyData *bounty) 
    {
        time_t currentTime = time(NULL);
        if(bounty->expiretime < currentTime)
        {
            ExpireBounty(bounty, true, true);
        }
        else
        {
            CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '%u', '%u', '%u')", bounty->guid, bounty->posterguid, bounty->money, bounty->expiretime);
        }
    }

    void DeleteAllBounties(Player *player) 
    {
        uint32 bountyCount = bountyMap.size();
        for(std::map<uint32, BountyData>::iterator iter = bountyMap.begin(), end = bountyMap.end(); iter != end; ++iter) 
        {
            ExpireBounty(&iter->second, true);
            bountyMap.erase(iter);
        }
        player->GetSession()->SendNotification("%i bounties have been deleted!", bountyCount);
    }

    bool isPlayerOnline(uint32 guid) 
    {
        // a player is online when we can find them.
        return sObjectAccessor->FindPlayer(guid) != NULL;
    }

    void SendMoneyToCharacter(Player *player, uint32 amount) 
    {
        //SQLTransaction trans = CharacterDatabase.BeginTransaction();
        //
        //MailDraft(subject, text)
        //    .AddMoney(copper)
        //    .SendMailTo(trans, MailReceiver(guid), MailSender(MAIL_NORMAL, 0, MAIL_STATIONERY_AUCTION));
        //
        //CharacterDatabase.CommitTransaction(trans);

        ItemPosCountVec dest;
        if(player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, B_TOKEN_ID, amount) == EQUIP_ERR_OK)
        {
            if(player->AddItem(B_TOKEN_ID, amount))
            {
                player->GetSession()->SendAreaTriggerMessage("|cff00ff00Your Bounty Tokens was succesfully added to your inventory!|r");
            }
        }
    }

    void SendMessageToCharacter(uint32 guid, std::string subject, std::string text)
    {
        SQLTransaction trans = CharacterDatabase.BeginTransaction();
        MailDraft(subject, text)
            .SendMailTo(trans, MailReceiver(guid), MailSender(MAIL_NORMAL, 0, MAIL_STATIONERY_DEFAULT));
        CharacterDatabase.CommitTransaction(trans);
    }

    void AlertBountyExpire(BountyData *bounty) 
    {
        // Find the victim, and tell him that he no longer has a bounty posted on him.
        Player *player = sObjectAccessor->FindPlayer(bounty->guid);
        if(player) {
            player->GetSession()->SendAreaTriggerMessage("|cff00ff00The bounty on you has expired!|r");

            // get rid of the arrow on his head too.
            if(player->HasAura(BOUNTY_MARKER)) {
                player->RemoveAura(BOUNTY_MARKER);
            }
        }

        // find the bounty poster and alert him that his bounty has expired.
        Player *pPoster = sObjectAccessor->FindPlayer(bounty->posterguid);
        if(pPoster) {
            pPoster->GetSession()->SendAreaTriggerMessage("Your bounty on |cffff0000%s|r has expired!", GetCharacterNameByGuid(bounty->guid).c_str());
        }
    }

    bool MoreInfoForPlayer(Player *player, uint32 uiAction) {
        if(uiAction == 1) {
            return false;
        }

        if (uiAction < GOSSIP_AFTER_PRICES) {
            player->PlayerTalkClass->SendCloseGossip();
        }

        uint32 index = uiAction - GOSSIP_AFTER_PRICES;
        if(index >= BOUNTY_LIMIT) {
            player->GetSession()->SendNotification("An error has occurred.");
            player->PlayerTalkClass->SendCloseGossip();
            return false;
        }
        uint32 guid = bountyIndex[index];
        if(guid == 0) {
            player->GetSession()->SendNotification("That bounty no longer exists.");
            player->PlayerTalkClass->SendCloseGossip();
            return false;
        }
        BountyData *bounty = getBountyByGuid(guid);
        if(!bounty) {
            player->GetSession()->SendNotification("That bounty no longer exists.");
            player->PlayerTalkClass->SendCloseGossip();
            return false;
        }


        // populate field
        uint32 level;
        uint8 race;
        uint8 Class;
        uint32 mapId;
        uint32 areaId;
        std::string name;
        bool offline;

        Player * pBounty = sObjectAccessor->FindPlayer(bounty->guid);
        if(pBounty) {
            level = pBounty->getLevel();
            race = pBounty->getRace();
            Class = pBounty->getClass();
            mapId = pBounty->GetMapId();
            areaId = pBounty->GetAreaId();
            name = pBounty->GetName();
            offline = false;
        } else {
            //                                                     0       1     2     3     4    5
            offline = true;
            QueryResult result = CharacterDatabase.PQuery("SELECT level, race, class, map, zone, name FROM characters WHERE guid = '%u'",
                bounty->guid);
            if(!result) {
                player->GetSession()->SendNotification("I could not find any info for that player.");
                player->PlayerTalkClass->SendCloseGossip();
                return false;
            }

            Field *fields = result->Fetch();
            level = fields[0].GetUInt8();
            race = fields[1].GetUInt8();
            Class = fields[2].GetUInt8();
            mapId = fields[3].GetUInt16();
            areaId = fields[4].GetUInt16();
            name = fields[5].GetString();

        }
        std::string race_s, Class_s;
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
        case RACE_NAGA:             race_s = "Naga";  	     break;
        case RACE_GOBLIN:           race_s = "Goblin";      break;
        case RACE_VRYKUL:           race_s = "Vrykul";	     break;
        case RACE_BROKEN:           race_s = "Broken";      break;
        }
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

        std::string timeLeft = secsToTimeString(bounty->expiretime - time(NULL));

        int locale = player->GetSession()->GetSessionDbcLocale();
        std::string areaName = "<unknown>";
        std::string zoneName = "";

        MapEntry const* map = sMapStore.LookupEntry(mapId);
        std::string mapName = map->name[locale];

        AreaTableEntry const* area = GetAreaEntryByAreaID(areaId);
        if (area)
        {
            areaName = area->area_name[locale];

            AreaTableEntry const* zone = GetAreaEntryByAreaID(area->zone);
            if (zone)
                zoneName = zone->area_name[locale];
        }
        std::string status;
        if(offline) {
            status = "Offline";
        } else {
            status = "Online";
        }
        if(pBounty) {
            if(pBounty->isAFK()) {
                status += ", <AFK> "+ pBounty->afkMsg;
            } else if (pBounty->isDND()) {
                status += ", <Busy> "+ pBounty->dndMsg;
            }
        }

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "General Information:", GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, " Name: "+name, GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, " Status: "+status, GOSSIP_SENDER_MAIN, 1);
        std::stringstream level_t;
        level_t << "  Level: " << level;
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, level_t.str(), GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "  Race: " + race_s, GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "  Class: " + Class_s, GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "  Time Remaining: " + timeLeft, GOSSIP_SENDER_MAIN, 1);

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Location Information:", GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "  Map: " + mapName, GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "  Area: " + areaName, GOSSIP_SENDER_MAIN, 1);
        if(!offline) {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "  Zone: " + zoneName, GOSSIP_SENDER_MAIN, 1);
        }
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Back to Bounty Listings", GOSSIP_SENDER_MAIN, OPTION_SHOW_BOUNTIES);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Goodbye", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
        return true;
        //player->SEND_GOSSIP_MENU(BOUNTY_TEXT_BOUNTY_INFO, Creature->GetGUID());
    }

    inline bool closeGossipNotify(Player *pPlayer, std::string message) {
        pPlayer->PlayerTalkClass->SendCloseGossip();
        pPlayer->GetSession()->SendNotification(message.c_str());
        return true;
    }

public:
    BountyHunter() : CreatureScript("BountyHunter")
    {
        LoadBounties();
    }

    std::string GetCharacterNameByGuid(uint32 guid) 
    {   
        // try to find the player name by guid if they're online, else find in the DB, or return a default.
        Player *player = sObjectAccessor->FindPlayer(guid);
        if(player)
            return player->GetName();
        QueryResult result = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid = '%u'", guid);
        if(result)
            return result->Fetch()[0].GetString();
        return "<non-existant character>";

    }

    void ClaimBounty(BountyData *bounty, Player *killer, Player *victim) {
        if (bounty->expiretime < time(NULL) || victim->InArena()) {
            // bounty expired, take no action.
            return;
        }
        if (bounty->posterguid == killer->GetGUIDLow()) {
            killer->GetSession()->SendNotification("You cannot collect a bounty that you have posted.");
            return;
        }

        uint32 gold = bounty->money;

        // alert the bounty poster that his bounty has been claimed.
        std::stringstream temp;
        temp << "Your " << gold << " Token bounty on " << victim->GetName();
        temp << " has been collected by " << killer->GetName() << "!";

        Player *bountyposter = sObjectAccessor->FindPlayer(bounty->posterguid);
        if (bountyposter) {
            bountyposter->GetSession()->SendAreaTriggerMessage(temp.str().c_str());
        } else {
            SendMessageToCharacter(bounty->posterguid, temp.str(), "");
        }

        // alert the killer that he has collected the bounty
        killer->GetSession()->SendAreaTriggerMessage("You have collected a %u Bounty Tokens on %s!", gold, victim->GetName());

        // compose message
        std::string posterName = GetCharacterNameByGuid(bounty->posterguid);
        std::stringstream title;
        title << "Your reward for killing " << victim->GetName() << "!";
        std::stringstream body;
        body << "Congratulations on collecting the bounty for " << victim->GetName()  << "!\n";
        body << "Enclosed is a token reward for your efforts, minus expenses of course.\n\n";
        body << "Bounty Posted By: " << posterName;

        // send message & money - tax.
        SendMoneyToCharacter(killer, gold);

        // alert the victim that they were prey to a bounty killing.
        victim->GetSession()->SendAreaTriggerMessage("%s has collected a %u Bounty Tokens on you that was posted by %s!", killer->GetName(), gold, posterName.c_str());

        // announce it to the world!
        std::stringstream announce;
        announce << "|cffff00ff[BountyHunter]|r ";
        announce << "|cff00ff00|Hplayer:" << killer->GetName() << "|h[" << killer->GetName() << "]|h|r";
        announce << " has claimed ";
        announce << "|cffffa500|Hplayer:" << posterName << "|h[" << posterName << "]|h|r";
        announce << "'s bounty on ";
        announce << "|cffff0000|Hplayer:" << victim->GetName() << "|h[" <<  victim->GetName() << "]|h|r";
        announce << ", earning " << gold << " Bounty Tokens!";
        sWorld->SendServerMessage(SERVER_MSG_STRING, announce.str().c_str(), 0);

        // delete the bounty after it has been claimed.
        CharacterDatabase.PExecute("DELETE FROM bounties WHERE guid = '%u'", bounty->guid);
        bountyMap.erase(bounty->guid);
        bountyIndex[bounty->index] = 0;
    }

    void ClaimReverseBounty(BountyData *bounty, Player *pBounty, Player *pBountyPoster) {
        if (bounty->expiretime < time(NULL) || pBountyPoster->InArena()) {
            // bounty expired, take no action.
            return;
        }

        uint32 gold = bounty->money;

        // notify involved parties about what happened.
        pBountyPoster->GetSession()->SendAreaTriggerMessage("%s has on you, claiming your %u Bounty Tokens!", pBounty->GetName(), gold);
        pBounty->GetSession()->SendAreaTriggerMessage("You have taken revenge on %s, claming their %u Bounty Tokens on you!", pBountyPoster->GetName(), gold);

        // compose message.
        std::stringstream title;
        title << "Your reward for exacting your revenge on " << pBountyPoster->GetName() << "!";

        std::stringstream body;
        body << "You've killed the person who put a bounty on your head!\n";
        body << "Enclosed is a " << gold << " token reward for your efforts & revenge, minus expenses of course.\n\n";
        body << "Bounty Posted By: " << pBountyPoster->GetName();

        // send message & money - tax.
        SendMoneyToCharacter(pBounty, gold);

        // announce it to the world
        std::stringstream announce;
        announce << "|cffff00ff[BountyHunter]|r ";
        announce << "|cff00ff00|Hplayer:" << pBounty->GetName() << "|h[" << pBounty->GetName() << "]|h|r";
        announce << " has exacted revenge upon ";
        announce << "|cffff0000|Hplayer:" << pBountyPoster->GetName() << "|h[" << pBountyPoster->GetName() << "]|h|r";
        announce << " and claimed the "  << gold << " Bounty Tokens!";
        sWorld->SendServerMessage(SERVER_MSG_STRING, announce.str().c_str(), 0);

        // delete the bounty, it's been claimed.
        CharacterDatabase.PExecute("DELETE FROM bounties WHERE guid = '%u'", bounty->guid);
        bountyMap.erase(bounty->guid);
        bountyIndex[bounty->index] = 0;
    }

    void ExpireBounty(BountyData *bounty, bool deleteFromDb = false, bool deleteFromMap = false, bool deleteIndex = true) 
    {
        uint32 gold = bounty->money;

        // compose title
        std::stringstream title;
        title << "Your " << gold << " Bounty Tokens on " << GetCharacterNameByGuid(bounty->guid) << " has expired!";

        // send refund.
        //SendMoneyToCharacter(bounty->posterguid, title.str(), "Here is a refund of your bounty, minus expenses.", bounty->money * MONEY_TAX);

        // alert the parties that the bounty is done
        AlertBountyExpire(bounty);

        // free up the bounty id
        if(deleteIndex)
            bountyIndex[bounty->index] = 0;

        // delete if we are supposed to
        if(deleteFromDb)
            CharacterDatabase.PExecute("DELETE FROM bounties WHERE guid = '%u'", bounty->guid);
        if(deleteFromMap)
            bountyMap.erase(bounty->guid);
    }

    bool OnGossipHello(Player * player, Creature * Creature)
    {
        uint32 bountyCount = bountyMap.size();
        uint32 titleTextId = BOUNTY_TEXT_HELLO;

        if(bountyCount == BOUNTY_LIMIT) {
            // we are not excepting any more bounties.
            titleTextId = BOUNTY_TEXT_FULL;
        } else {
            // display the select bounty menu.
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, SELECT_BOUNTY, GOSSIP_SENDER_MAIN, OPTION_SELECT_BOUNTY);
        }

        if (bountyCount > 0) {
            // show the bounty count and ask if they want to see em.
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "There are "+UInt32ToString(bountyCount)+" open bounties, would you like to see them?",
                GOSSIP_SENDER_MAIN, OPTION_SHOW_BOUNTIES
                );
        } else {
            // set the menu text to no bounties.
            titleTextId = BOUNTY_TEXT_NO_BOUNTIES;
        }

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, NVM, GOSSIP_SENDER_MAIN, OPTION_GOODBYE);

        if (player->isGameMaster() && bountyCount > 0)
        {
            // if the player is a GM and there are bounties active, display this option
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TALK, WIPE_BOUNTY, GOSSIP_SENDER_MAIN, OPTION_TRUNCATE, "Are you sure you wish to delete all bounties?", 0, false);
        }

        player->PlayerTalkClass->SendGossipMenu(11100, Creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();

        if(player->GetSession()->GetSecurity() == 2 || player->GetSession()->GetSecurity() == 3 || player->GetSession()->GetSecurity() == 4 || player->GetSession()->GetSecurity() == 5 || player->GetSession()->GetSecurity() == 6 || player->GetSession()->GetSecurity() == 7 || player->GetSession()->GetSecurity() == 8) {
            // we cannot set bounties on game masters!
            return closeGossipNotify(player, "Gamemasters are not allowed to place bounties.");
        }

        switch(uiAction)
        {
        case OPTION_SELECT_BOUNTY:
            {
                if(bountyMap.size() == BOUNTY_LIMIT) {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "I'll check back later, goodbye!", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
                    player->PlayerTalkClass->SendGossipMenu(BOUNTY_TEXT_JUST_RAN_OUT, creature->GetGUID());
                    return true;
                }
                for(uint32 i = 0, len = bountyPriceOptions; i < len; i++) {
                    uint32 bountyPrice = bountyPrices[i];
                    std::string message = "Post a bounty of "+ UInt32ToString(bountyPrice) + " Tokens.";
                    player->ADD_GOSSIP_ITEM_EXTENDED(
                        GOSSIP_ICON_MONEY_BAG,
                        message,
                        GOSSIP_SENDER_MAIN,
                        GOSSIP_PRICE_START + i,
                        "", 0,
                        true // I'm not sure if coded will work with a money confirm, we'll see :O!
                        );
                }
                // I should probably choose a better textId.
                player->PlayerTalkClass->SendGossipMenu(11100, creature->GetGUID());
                break;
            }
        case OPTION_SHOW_BOUNTIES:
            {
                if(bountyMap.size() == 0) {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Goodbye!", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
                    player->PlayerTalkClass->SendGossipMenu(BOUNTY_TEXT_JUST_RAN_OUT, creature->GetGUID());
                    return true;
                }
                time_t now = time(NULL);

                for(std::map<uint32, BountyData>::iterator iter = bountyMap.begin(), end = bountyMap.end(); iter != end; ++iter) {
                    BountyData *bounty = &iter->second;
                    if(bounty->expiretime >= now) { // only list active bounties. they will auto expire after 30s.
                        uint32 gold = bounty->money;
                        std::stringstream temp;
                        temp << GetCharacterNameByGuid(bounty->guid);
                        temp << " " << gold << " Token, expires in ";
                        temp << secsToTimeString(bounty->expiretime - now, true);

                        player->ADD_GOSSIP_ITEM(
                            isPlayerOnline(bounty->guid) ? GOSSIP_ICON_BATTLE : GOSSIP_ICON_TAXI,
                            temp.str(),
                            GOSSIP_SENDER_MAIN,
                            GOSSIP_AFTER_PRICES + bounty->index
                            );
                    }
                }
                player->PlayerTalkClass->SendGossipMenu(BOUNTY_TEXT_BOUNTY_LIST, creature->GetGUID());
                break;
            }
        case OPTION_GOODBYE:
            {
                player->PlayerTalkClass->SendCloseGossip();
                break;
            }
        case OPTION_TRUNCATE:
            {
                DeleteAllBounties(player);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            }
        default:
            {
                player->PlayerTalkClass->ClearMenus();
                bool show = MoreInfoForPlayer(player, uiAction);
                if(show)
                    player->PlayerTalkClass->SendGossipMenu(BOUNTY_TEXT_BOUNTY_INFO, creature->GetGUID());
            }
        }
        return true;
    }

    bool OnGossipSelectCode(Player *pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction, const char * ccode)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if ( uiSender == GOSSIP_SENDER_MAIN )
        {
            if (uiAction < GOSSIP_PRICE_START || uiAction >= GOSSIP_PRICE_MAX) {
                sLog->outString("Invalid action passed to bounty code.");
                return true;
            }
            // find out the corresponding bounty price
            uint32 index = uiAction - GOSSIP_PRICE_START;
            uint32 bountyPrice = bountyPrices[index];


            // copy the string so we can edit it...

            std::string code = ccode;
            std::transform(code.begin(), code.end(), code.begin(), ::tolower);
            code[0] = toupper(code[0]);

            if(bountyMap.size() == BOUNTY_LIMIT) {
                // no more bounties can be posted.
                return closeGossipNotify(pPlayer, "Bounty list is currently full.");
            }

            Player *pBounty = sObjectAccessor->FindPlayerByName(code.c_str());
            if(!pBounty) {
                // we cannot add bounties to offline players.
                return closeGossipNotify(pPlayer, "That player is offline.");
            }
            if(pBounty->isGameMaster()) {
                // we cannot set bounties on game masters!
                return closeGossipNotify(pPlayer, "That player is a Game Master.");
            }
            uint32 guid = pBounty->GetGUIDLow();
            BountyData *oldBounty = getBountyByGuid(guid);
            if(oldBounty) {
                // bounty was found.
                std::string gold = UInt32ToString(oldBounty->money);
                return closeGossipNotify(pPlayer, "That player already has a bounty of "+gold+" Bounty Tokens on them!");
            }
            if(pPlayer->GetGUIDLow() == guid) {
                // player is trying to hunt himself?
                return closeGossipNotify(pPlayer, "You can't set a bounty on yourself.");
            }

            if(!pPlayer->HasItemCount(B_TOKEN_ID, bountyPrice))
            {
                pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, 0, 0, 0);
                pPlayer->PlayerTalkClass->SendCloseGossip();
                return false;
            }

            BountyData bounty;
            bounty.guid = guid;
            bounty.expiretime = time(NULL) + EXPIRE_TIME_SECS;
            bounty.money = bountyPrice;
            bounty.posterguid = pPlayer->GetGUIDLow();

            AddBounty(pPlayer, pBounty, bounty);
            pPlayer->PlayerTalkClass->SendCloseGossip();

        }
        return true;
    }
    void AddBounty(Player *player, Player *pBounty, BountyData bounty) {
        uint32 index = findUnusedIndex();
        // we could not find an open bounty, this is very weird.
        if (index == BOUNTY_LIMIT) {
            player->GetSession()->SendNotification("An error has occurred.");
            sLog->outError("Could not find available index, even when all checks passed.");
            return;
        }

        // withdraw cash.
        //player->ModifyMoney(-bounty.money);

        // alert world of new bounty. 
        uint32 gold = bounty.money;

        player->DestroyItemCount(B_TOKEN_ID, gold, true);

        std::stringstream announce;
        announce << "|cffff00ff[BountyHunter]|r A post of " << gold << " Bounty Tokens has been placed on ";
        announce << "|cffff0000|Hplayer:" << pBounty->GetName() << "|h[" << pBounty->GetName() << "]|h|r";
        announce << " by ";
        announce << "|cff00ff00|Hplayer:" << player->GetName() << "|h[" << player->GetName() << "]|h|r!";

        sWorld->SendServerMessage(SERVER_MSG_STRING, announce.str().c_str(), 0);

        // alert victim of bounty on his head.
        pBounty->GetSession()->SendAreaTriggerMessage("A %u Bounty Tokens has been placed on |cffff0000YOU|r by |cff00ff00%s|r! Kill the person who placed the bounty on you to clear your name.", gold, player->GetName());
        pBounty->GetSession()->SendAreaTriggerMessage("<--- |cffff0000INCOMING BOUNTY!|r --->");
        pBounty->AddAura(BOUNTY_MARKER, pBounty);
        pBounty->SetPvP(true);
        pBounty->SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);

        player->GetSession()->SendAreaTriggerMessage("Your bounty has been successfully placed! If the player you set a bounty on kills you, he will claim your Bounty Tokens!");

        // save bounty.
        bounty.index = index;
        bountyMap[bounty.guid] = bounty;
        bountyIndex[bounty.index] = bounty.guid;
        SaveBounty(&bounty);
    }
};

class BountyTimer : public WorldScript
{
private:
    IntervalTimer m_bountyTimer;
    BountyHunter *m_bountyHunter;
public:
    BountyTimer(BountyHunter *bountyHunter): WorldScript("BountyTimer"), m_bountyHunter(bountyHunter) {
        m_bountyTimer.SetCurrent(0);
        m_bountyTimer.SetInterval(15000);
    }

    void OnUpdate(uint32 diff) {
        m_bountyTimer.Update(diff);
        if(m_bountyTimer.Passed()) {
            m_bountyTimer.Reset();
            pruneBounty();
        }

    }
    void pruneBounty() {
        time_t currentTime = time(NULL);
        for(std::map<uint32, BountyData>::iterator iter = bountyMap.begin(), end = bountyMap.end(); iter != end; ++iter) 
        {
            BountyData *bounty = &iter->second;
            if(bounty->expiretime < currentTime) {
                m_bountyHunter->ExpireBounty(bounty, true);
                bountyMap.erase(iter);
            } else {
                Player *player = sObjectAccessor->FindPlayer(bounty->guid);
                if(player) {
                    if(player->isAlive() && !player->InArena()) { // keep refreshing the aura. 
                        player->AddAura(BOUNTY_MARKER, player);
                        player->SetPvP(true);
                        player->SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
                    }
                }
            }
        }
    }

};

class BountyKills : public PlayerScript
{
private:
    BountyHunter *m_bountyHunter;
public:
    BountyKills(BountyHunter *bountyHunter) : PlayerScript("BountyKills"), m_bountyHunter(bountyHunter) {}

    void OnPVPKill(Player * killer, Player * victim)
    {
        BountyData *bounty = getBountyByGuid(victim->GetGUIDLow());
        if (bounty) {
            if(victim->GetGUIDLow() != killer->GetGUIDLow())
                m_bountyHunter->ClaimBounty(bounty, killer, victim);
        }

        bounty = getBountyByGuid(killer->GetGUIDLow());
        if (bounty && victim->GetGUIDLow() == bounty->posterguid) {
            m_bountyHunter->ClaimReverseBounty(bounty, killer, victim);
        }
    }

    void OnLogin(Player* player) 
    {
        BountyData *bounty = getBountyByGuid(player->GetGUIDLow());
        if(!bounty) {
            if(player->HasAura(BOUNTY_MARKER)) 
                player->RemoveAura(BOUNTY_MARKER);
        } 
        else if(bounty->expiretime >= time(NULL))
        {
            if(player->isAlive() && !player->InArena())
                player->AddAura(BOUNTY_MARKER, player);
            uint32 gold = bounty->money;

            player->GetSession()->SendAreaTriggerMessage(
                "A reward of %u Bounty Tokens has been placed on |cffff0000YOU|r by |cff00ff00%s|r! Kill the person who placed the bounty on you to clear your name.", 
                gold, m_bountyHunter->GetCharacterNameByGuid(bounty->posterguid).c_str());
        } else {
            m_bountyHunter->ExpireBounty(bounty, true, true);
        }

    }
};

struct BountyHunterItem : public ItemScript
{
    BountyHunterItem() : ItemScript(BOUNTY_SCRIPT_NAME) { LoadBounties(); }

    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
    {
        player->PlayerTalkClass->ClearMenus();

        uint32 bountyCount = bountyMap.size();
        uint32 titleTextId = BOUNTY_TEXT_HELLO;

        if(bountyCount == BOUNTY_LIMIT) {
            // we are not excepting any more bounties.
            titleTextId = BOUNTY_TEXT_FULL;
        } else {
            AddSimpleMenuItemToPlayer(player,GOSSIP_ICON_MONEY_BAG,GOSSIP_SENDER_MAIN, OPTION_SELECT_BOUNTY, SELECT_BOUNTY);
        }

        if (bountyCount > 0) {
            // show the bounty count and ask if they want to see em.
            AddSimpleMenuItemToPlayer(player,GOSSIP_ICON_INTERACT_1,GOSSIP_SENDER_MAIN, OPTION_SHOW_BOUNTIES, "There are %u open bounties, would you like to see them?",bountyCount);
        } else {
            // set the menu text to no bounties.
            titleTextId = BOUNTY_TEXT_NO_BOUNTIES;
        }
        AddSimpleMenuItemToPlayer(player,GOSSIP_ICON_TALK,GOSSIP_SENDER_MAIN, OPTION_GOODBYE, NVM);

        if (player->isGameMaster() && bountyCount > 0)
        {
            // if the player is a GM and there are bounties active, display this option
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TALK, WIPE_BOUNTY, GOSSIP_SENDER_MAIN, OPTION_TRUNCATE, "Are you sure you wish to delete all bounties?", 0, false);
        }

        player->PlayerTalkClass->SendGossipMenu(11100, item->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Item* item, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();

        if(player->GetSession()->GetSecurity() == 2 || player->GetSession()->GetSecurity() == 3 || player->GetSession()->GetSecurity() == 4 || player->GetSession()->GetSecurity() == 5 || player->GetSession()->GetSecurity() == 6 || player->GetSession()->GetSecurity() == 7 || player->GetSession()->GetSecurity() == 8) {
            // we cannot set bounties on game masters!
            return closeGossipNotify(player, "Gamemasters are not allowed to place bounties.");
        }

        switch(uiAction)
        {
        case OPTION_SELECT_BOUNTY:
            {
                if(bountyMap.size() == BOUNTY_LIMIT) {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "I'll check back later, goodbye!", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
                    player->PlayerTalkClass->SendGossipMenu(BOUNTY_TEXT_JUST_RAN_OUT, item->GetGUID());
                    return true;
                }
                for(uint32 i = 0, len = bountyPriceOptions; i < len; i++) {
                    uint32 bountyPrice = bountyPrices[i];
                    std::string message = "Post a bounty of "+ UInt32ToString(bountyPrice) + " Tokens.";
                    player->ADD_GOSSIP_ITEM_EXTENDED(
                        GOSSIP_ICON_MONEY_BAG,
                        message,
                        GOSSIP_SENDER_MAIN,
                        GOSSIP_PRICE_START + i,
                        "", 0,
                        true // I'm not sure if coded will work with a money confirm, we'll see :O!
                        );
                }
                // I should probably choose a better textId.
                player->PlayerTalkClass->SendGossipMenu(11100, item->GetGUID());
                break;
            }
        case OPTION_SHOW_BOUNTIES:
            {
                if(bountyMap.size() == 0) {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Goodbye!", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
                    player->PlayerTalkClass->SendGossipMenu(BOUNTY_TEXT_JUST_RAN_OUT, item->GetGUID());
                    return true;
                }
                time_t now = time(NULL);

                for(std::map<uint32, BountyData>::iterator iter = bountyMap.begin(), end = bountyMap.end(); iter != end; ++iter) {
                    BountyData *bounty = &iter->second;
                    if(bounty->expiretime >= now) { // only list active bounties. they will auto expire after 30s.
                        uint32 gold = bounty->money;
                        std::stringstream temp;
                        temp << GetCharacterNameByGuid(bounty->guid);
                        temp << " " << gold << " Token, expires in ";
                        temp << secsToTimeString(bounty->expiretime - now, true);

                        player->ADD_GOSSIP_ITEM(
                            isPlayerOnline(bounty->guid) ? GOSSIP_ICON_BATTLE : GOSSIP_ICON_TAXI,
                            temp.str(),
                            GOSSIP_SENDER_MAIN,
                            GOSSIP_AFTER_PRICES + bounty->index
                            );
                    }
                }
                player->PlayerTalkClass->SendGossipMenu(BOUNTY_TEXT_BOUNTY_LIST, item->GetGUID());
                break;
            }
        case OPTION_GOODBYE:
            {
                player->PlayerTalkClass->SendCloseGossip();
                break;
            }
        case OPTION_TRUNCATE:
            {
                DeleteAllBounties(player);
                player->PlayerTalkClass->SendCloseGossip();
                break;
            }
        default:
            {
                player->PlayerTalkClass->ClearMenus();
                bool show = MoreInfoForPlayer(player, uiAction);
                if(show)
                    player->PlayerTalkClass->SendGossipMenu(BOUNTY_TEXT_BOUNTY_INFO, item->GetGUID());
            }
        }
        return true;
    }

    bool OnGossipSelectCode(Player *pPlayer, Item* item, uint32 uiSender, uint32 uiAction, const char * ccode)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if ( uiSender == GOSSIP_SENDER_MAIN )
        {
            if (uiAction < GOSSIP_PRICE_START || uiAction >= GOSSIP_PRICE_MAX) {
                sLog->outString("Invalid action passed to bounty code.");
                return true;
            }
            // find out the corresponding bounty price
            uint32 index = uiAction - GOSSIP_PRICE_START;
            uint32 bountyPrice = bountyPrices[index];


            // copy the string so we can edit it...

            std::string code = ccode;
            std::transform(code.begin(), code.end(), code.begin(), ::tolower);
            code[0] = toupper(code[0]);

            if(bountyMap.size() == BOUNTY_LIMIT) {
                // no more bounties can be posted.
                return closeGossipNotify(pPlayer, "Bounty list is currently full.");
            }

            Player *pBounty = sObjectAccessor->FindPlayerByName(code.c_str());
            if(!pBounty) {
                // we cannot add bounties to offline players.
                return closeGossipNotify(pPlayer, "That player is offline.");
            }
            if(pBounty->isGameMaster()) {
                // we cannot set bounties on game masters!
                return closeGossipNotify(pPlayer, "That player is a Game Master.");
            }
            uint32 guid = pBounty->GetGUIDLow();
            BountyData *oldBounty = getBountyByGuid(guid);
            if(oldBounty) {
                // bounty was found.
                std::string gold = UInt32ToString(oldBounty->money);
                return closeGossipNotify(pPlayer, "That player already has a bounty of "+gold+" Bounty Tokens on them!");
            }
            if(pPlayer->GetGUIDLow() == guid) {
                // player is trying to hunt himself?
                return closeGossipNotify(pPlayer, "You can't set a bounty on yourself.");
            }

            if(!pPlayer->HasItemCount(B_TOKEN_ID, bountyPrice))
            {
                pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, 0, 0, 0);
                pPlayer->PlayerTalkClass->SendCloseGossip();
                return false;
            }

            BountyData bounty;
            bounty.guid = guid;
            bounty.expiretime = time(NULL) + EXPIRE_TIME_SECS;
            bounty.money = bountyPrice;
            bounty.posterguid = pPlayer->GetGUIDLow();

            AddBounty(pPlayer, pBounty, bounty);
            pPlayer->PlayerTalkClass->SendCloseGossip();

        }
        return true;
    }

    void AddSimpleMenuItemToPlayer(Player* player, uint32 icon, uint32 sender,uint32 action, const char *Message, ...)
    {
        if(!player)
            return;

        char Result[1024];
        va_list List;
        va_start(List, Message);
        vsnprintf(Result, 1024, Message, List);
        va_end(List);

        player->PlayerTalkClass->GetGossipMenu().AddMenuItem(-1, icon,	Result,	sender,	action, "", false);
    }

    std::string GetCharacterNameByGuid(uint32 guid) 
    {   
        // try to find the player name by guid if they're online, else find in the DB, or return a default.
        Player *player = sObjectAccessor->FindPlayer(guid);
        if(player)
            return player->GetName();
        QueryResult result = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid = '%u'", guid);
        if(result)
            return result->Fetch()[0].GetString();
        return "<non-existant character>";

    }

    void ClaimBounty(BountyData *bounty, Player *killer, Player *victim) {
        if (bounty->expiretime < time(NULL) || victim->InArena()) {
            // bounty expired, take no action.
            return;
        }
        if (bounty->posterguid == killer->GetGUIDLow()) {
            killer->GetSession()->SendNotification("You cannot collect a bounty that you have posted.");
            return;
        }

        uint32 gold = bounty->money;

        // alert the bounty poster that his bounty has been claimed.
        std::stringstream temp;
        temp << "Your " << gold << " Token bounty on " << victim->GetName();
        temp << " has been collected by " << killer->GetName() << "!";

        Player *bountyposter = sObjectAccessor->FindPlayer(bounty->posterguid);
        if (bountyposter) {
            bountyposter->GetSession()->SendAreaTriggerMessage(temp.str().c_str());
        } else {
            SendMessageToCharacter(bounty->posterguid, temp.str(), "");
        }

        // alert the killer that he has collected the bounty
        killer->GetSession()->SendAreaTriggerMessage("You have collected a %u Bounty Tokens on %s!", gold, victim->GetName());

        // compose message
        std::string posterName = GetCharacterNameByGuid(bounty->posterguid);
        std::stringstream title;
        title << "Your reward for killing " << victim->GetName() << "!";
        std::stringstream body;
        body << "Congratulations on collecting the bounty for " << victim->GetName()  << "!\n";
        body << "Enclosed is a token reward for your efforts, minus expenses of course.\n\n";
        body << "Bounty Posted By: " << posterName;

        // send message & money - tax.
        SendMoneyToCharacter(killer, gold);

        // alert the victim that they were prey to a bounty killing.
        victim->GetSession()->SendAreaTriggerMessage("%s has collected a %u Bounty Tokens on you that was posted by %s!", killer->GetName(), gold, posterName.c_str());

        // announce it to the world!
        std::stringstream announce;
        announce << "|cffff00ff[BountyHunter]|r ";
        announce << "|cff00ff00|Hplayer:" << killer->GetName() << "|h[" << killer->GetName() << "]|h|r";
        announce << " has claimed ";
        announce << "|cffffa500|Hplayer:" << posterName << "|h[" << posterName << "]|h|r";
        announce << "'s bounty on ";
        announce << "|cffff0000|Hplayer:" << victim->GetName() << "|h[" <<  victim->GetName() << "]|h|r";
        announce << ", earning " << gold << " Bounty Tokens!";
        sWorld->SendServerMessage(SERVER_MSG_STRING, announce.str().c_str(), 0);

        // delete the bounty after it has been claimed.
        CharacterDatabase.PExecute("DELETE FROM bounties WHERE guid = '%u'", bounty->guid);
        bountyMap.erase(bounty->guid);
        bountyIndex[bounty->index] = 0;
    }

    void ClaimReverseBounty(BountyData *bounty, Player *pBounty, Player *pBountyPoster) {
        if (bounty->expiretime < time(NULL) || pBountyPoster->InArena()) {
            // bounty expired, take no action.
            return;
        }

        uint32 gold = bounty->money;

        // notify involved parties about what happened.
        pBountyPoster->GetSession()->SendAreaTriggerMessage("%s has on you, claiming your %u Bounty Tokens!", pBounty->GetName(), gold);
        pBounty->GetSession()->SendAreaTriggerMessage("You have taken revenge on %s, claming their %u Bounty Tokens on you!", pBountyPoster->GetName(), gold);

        // compose message.
        std::stringstream title;
        title << "Your reward for exacting your revenge on " << pBountyPoster->GetName() << "!";

        std::stringstream body;
        body << "You've killed the person who put a bounty on your head!\n";
        body << "Enclosed is a " << gold << " token reward for your efforts & revenge, minus expenses of course.\n\n";
        body << "Bounty Posted By: " << pBountyPoster->GetName();

        // send message & money - tax.
        SendMoneyToCharacter(pBounty, gold);

        // announce it to the world
        std::stringstream announce;
        announce << "|cffff00ff[BountyHunter]|r ";
        announce << "|cff00ff00|Hplayer:" << pBounty->GetName() << "|h[" << pBounty->GetName() << "]|h|r";
        announce << " has exacted revenge upon ";
        announce << "|cffff0000|Hplayer:" << pBountyPoster->GetName() << "|h[" << pBountyPoster->GetName() << "]|h|r";
        announce << " and claimed the "  << gold << " Bounty Tokens!";
        sWorld->SendServerMessage(SERVER_MSG_STRING, announce.str().c_str(), 0);

        // delete the bounty, it's been claimed.
        CharacterDatabase.PExecute("DELETE FROM bounties WHERE guid = '%u'", bounty->guid);
        bountyMap.erase(bounty->guid);
        bountyIndex[bounty->index] = 0;
    }

    void ExpireBounty(BountyData *bounty, bool deleteFromDb = false, bool deleteFromMap = false, bool deleteIndex = true) 
    {
        uint32 gold = bounty->money;

        // compose title
        std::stringstream title;
        title << "Your " << gold << " Bounty Tokens on " << GetCharacterNameByGuid(bounty->guid) << " has expired!";

        //SendMoneyToCharacter(bounty->posterguid, title.str(), "Here is a refund of your bounty, minus expenses.", bounty->money * MONEY_TAX);

        // alert the parties that the bounty is done
        AlertBountyExpire(bounty);

        // free up the bounty id
        if(deleteIndex)
            bountyIndex[bounty->index] = 0;

        // delete if we are supposed to
        if(deleteFromDb)
            CharacterDatabase.PExecute("DELETE FROM bounties WHERE guid = '%u'", bounty->guid);
        if(deleteFromMap)
            bountyMap.erase(bounty->guid);
    }

    void AddBounty(Player *player, Player *pBounty, BountyData bounty) {
        uint32 index = findUnusedIndex();
        // we could not find an open bounty, this is very weird.
        if (index == BOUNTY_LIMIT) {
            player->GetSession()->SendNotification("An error has occurred.");
            sLog->outError("Could not find available index, even when all checks passed.");
            return;
        }

        // withdraw cash.
        //player->ModifyMoney(-bounty.money);

        // alert world of new bounty. 
        uint32 gold = bounty.money;

        player->DestroyItemCount(B_TOKEN_ID, gold, true);

        std::stringstream announce;
        announce << "|cffff00ff[BountyHunter]|r A post of " << gold << " Bounty Tokens has been placed on ";
        announce << "|cffff0000|Hplayer:" << pBounty->GetName() << "|h[" << pBounty->GetName() << "]|h|r";
        announce << " by ";
        announce << "|cff00ff00|Hplayer:" << player->GetName() << "|h[" << player->GetName() << "]|h|r!";

        sWorld->SendServerMessage(SERVER_MSG_STRING, announce.str().c_str(), 0);

        // alert victim of bounty on his head.
        pBounty->GetSession()->SendAreaTriggerMessage("A %u Bounty Tokens has been placed on |cffff0000YOU|r by |cff00ff00%s|r! Kill the person who placed the bounty on you to clear your name.", gold, player->GetName());
        pBounty->GetSession()->SendAreaTriggerMessage("<--- |cffff0000INCOMING BOUNTY!|r --->");
        pBounty->AddAura(BOUNTY_MARKER, pBounty);
        pBounty->SetPvP(true);
        pBounty->SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);

        player->GetSession()->SendAreaTriggerMessage("Your bounty has been successfully placed! If the player you set a bounty on kills you, he will claim your Bounty Tokens!");

        // save bounty.
        bounty.index = index;
        bountyMap[bounty.guid] = bounty;
        bountyIndex[bounty.index] = bounty.guid;
        SaveBounty(&bounty);
    }

private:
    void LoadBounties() 
    {
        uint32 oldMSTime = getMSTime();
        time_t currentTime = time(NULL);

        QueryResult result = CharacterDatabase.Query("SELECT * FROM bounties");
        if(!result)
        {
            sLog->outString(">> Loaded 0 bounties.");
            sLog->outString();
            return;
        }

        Field *fields;
        uint32 count = 0;
        do
        {
            fields = result->Fetch();
            BountyData bounty;
            bounty.guid = fields[0].GetUInt32();
            bounty.posterguid = fields[1].GetUInt32();
            bounty.money = fields[2].GetUInt32();
            bounty.expiretime = fields[3].GetUInt32();

            if(bounty.expiretime < currentTime) 
            {
                sLog->outError("Bounty on %u from %u has expired! Deleting from DB...", bounty.guid, bounty.posterguid);
                ExpireBounty(&bounty, true, false, false);
            }
            else 
            {
                bounty.index = count;
                bountyIndex[bounty.index] = bounty.guid;
                bountyMap[bounty.guid] = bounty;

                count++;
            }
        } while(result->NextRow());

        sLog->outString(">> Loaded %u bounties in %u ms!", count, GetMSTimeDiffToNow(oldMSTime));
        sLog->outString();
    }

    void SaveAllBounties() {
        if(bountyMap.size() == 0) {
            CharacterDatabase.Execute("TRUNCATE TABLE bounties");
            return;
        }
        time_t currentTime = time(NULL);
        SQLTransaction trans = CharacterDatabase.BeginTransaction();
        trans->Append("TRUNCATE TABLE bounties");

        std::map<uint32, BountyData>::iterator iter;
        std::map<uint32, BountyData>::iterator end;
        for(iter = bountyMap.begin(), end = bountyMap.end(); iter != end; ++iter) {
            BountyData *bounty = &iter->second;
            if(bounty->expiretime < currentTime) 
            {
                ExpireBounty(bounty);
                bountyMap.erase(iter);
            } 
            else 
            {
                trans->PAppend("INSERT INTO bounties VALUES('%u', '%u', '%u', '%u')", bounty->guid, bounty->posterguid, bounty->money, bounty->expiretime);
            }
        }
        CharacterDatabase.CommitTransaction(trans);
    }

    void SaveBounty(BountyData *bounty) 
    {
        time_t currentTime = time(NULL);
        if(bounty->expiretime < currentTime)
        {
            ExpireBounty(bounty, true, true);
        }
        else
        {
            CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '%u', '%u', '%u')", bounty->guid, bounty->posterguid, bounty->money, bounty->expiretime);
        }
    }

    void DeleteAllBounties(Player *player) 
    {
        uint32 bountyCount = bountyMap.size();
        for(std::map<uint32, BountyData>::iterator iter = bountyMap.begin(), end = bountyMap.end(); iter != end; ++iter) 
        {
            ExpireBounty(&iter->second, true);
            bountyMap.erase(iter);
        }
        player->GetSession()->SendNotification("%i bounties have been deleted!", bountyCount);
    }

    bool isPlayerOnline(uint32 guid)  { return sObjectAccessor->FindPlayer(guid) != NULL; }

    void SendMoneyToCharacter(Player *player, uint32 amount) 
    {
        //SQLTransaction trans = CharacterDatabase.BeginTransaction();
        //
        //MailDraft(subject, text)
        //    .AddMoney(copper)
        //    .SendMailTo(trans, MailReceiver(guid), MailSender(MAIL_NORMAL, 0, MAIL_STATIONERY_AUCTION));
        //
        //CharacterDatabase.CommitTransaction(trans);

        ItemPosCountVec dest;
        if(player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, B_TOKEN_ID, amount) == EQUIP_ERR_OK)
        {
            if(player->AddItem(B_TOKEN_ID, amount))
            {
                player->GetSession()->SendAreaTriggerMessage("|cff00ff00Your Bounty Tokens was succesfully added to your inventory!|r");
            }
        }
    }

    void SendMessageToCharacter(uint32 guid, std::string subject, std::string text)
    {
        SQLTransaction trans = CharacterDatabase.BeginTransaction();
        MailDraft(subject, text)
            .SendMailTo(trans, MailReceiver(guid), MailSender(MAIL_NORMAL, 0, MAIL_STATIONERY_DEFAULT));
        CharacterDatabase.CommitTransaction(trans);
    }

    void AlertBountyExpire(BountyData *bounty) 
    {
        // Find the victim, and tell him that he no longer has a bounty posted on him.
        Player *player = sObjectAccessor->FindPlayer(bounty->guid);
        if(player) {
            player->GetSession()->SendAreaTriggerMessage("|cff00ff00The bounty on you has expired!|r");

            // get rid of the arrow on his head too.
            if(player->HasAura(BOUNTY_MARKER)) {
                player->RemoveAura(BOUNTY_MARKER);
            }
        }

        // find the bounty poster and alert him that his bounty has expired.
        Player *pPoster = sObjectAccessor->FindPlayer(bounty->posterguid);
        if(pPoster) {
            pPoster->GetSession()->SendAreaTriggerMessage("Your bounty on |cffff0000%s|r has expired!", GetCharacterNameByGuid(bounty->guid).c_str());
        }
    }

    bool MoreInfoForPlayer(Player *player, uint32 uiAction) {
        if(uiAction == 1) {
            return false;
        }

        if (uiAction < GOSSIP_AFTER_PRICES) {
            player->PlayerTalkClass->SendCloseGossip();
        }

        uint32 index = uiAction - GOSSIP_AFTER_PRICES;
        if(index >= BOUNTY_LIMIT) {
            player->GetSession()->SendNotification("An error has occurred.");
            player->PlayerTalkClass->SendCloseGossip();
            return false;
        }
        uint32 guid = bountyIndex[index];
        if(guid == 0) {
            player->GetSession()->SendNotification("That bounty no longer exists.");
            player->PlayerTalkClass->SendCloseGossip();
            return false;
        }
        BountyData *bounty = getBountyByGuid(guid);
        if(!bounty) {
            player->GetSession()->SendNotification("That bounty no longer exists.");
            player->PlayerTalkClass->SendCloseGossip();
            return false;
        }


        // populate field
        uint32 level;
        uint8 race;
        uint8 Class;
        uint32 mapId;
        uint32 areaId;
        std::string name;
        bool offline;

        Player * pBounty = sObjectAccessor->FindPlayer(bounty->guid);
        if(pBounty) {
            level = pBounty->getLevel();
            race = pBounty->getRace();
            Class = pBounty->getClass();
            mapId = pBounty->GetMapId();
            areaId = pBounty->GetAreaId();
            name = pBounty->GetName();
            offline = false;
        } else {
            //                                                     0       1     2     3     4    5
            offline = true;
            QueryResult result = CharacterDatabase.PQuery("SELECT level, race, class, map, zone, name FROM characters WHERE guid = '%u'",
                bounty->guid);
            if(!result) {
                player->GetSession()->SendNotification("I could not find any info for that player.");
                player->PlayerTalkClass->SendCloseGossip();
                return false;
            }

            Field *fields = result->Fetch();
            level = fields[0].GetUInt8();
            race = fields[1].GetUInt8();
            Class = fields[2].GetUInt8();
            mapId = fields[3].GetUInt16();
            areaId = fields[4].GetUInt16();
            name = fields[5].GetString();

        }
        std::string race_s, Class_s;
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
        case RACE_NAGA:             race_s = "Naga";  	     break;
        case RACE_GOBLIN:           race_s = "Goblin";      break;
        case RACE_VRYKUL:           race_s = "Vrykul";	     break;
        case RACE_BROKEN:           race_s = "Broken";      break;
        }
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

        std::string timeLeft = secsToTimeString(bounty->expiretime - time(NULL));

        int locale = player->GetSession()->GetSessionDbcLocale();
        std::string areaName = "<unknown>";
        std::string zoneName = "";

        MapEntry const* map = sMapStore.LookupEntry(mapId);
        std::string mapName = map->name[locale];

        AreaTableEntry const* area = GetAreaEntryByAreaID(areaId);
        if (area)
        {
            areaName = area->area_name[locale];

            AreaTableEntry const* zone = GetAreaEntryByAreaID(area->zone);
            if (zone)
                zoneName = zone->area_name[locale];
        }
        std::string status;
        if(offline) {
            status = "Offline";
        } else {
            status = "Online";
        }
        if(pBounty) {
            if(pBounty->isAFK()) {
                status += ", <AFK> "+ pBounty->afkMsg;
            } else if (pBounty->isDND()) {
                status += ", <Busy> "+ pBounty->dndMsg;
            }
        }

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "General Information:", GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, " Name: "+name, GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, " Status: "+status, GOSSIP_SENDER_MAIN, 1);
        std::stringstream level_t;
        level_t << "  Level: " << level;
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, level_t.str(), GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "  Race: " + race_s, GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "  Class: " + Class_s, GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "  Time Remaining: " + timeLeft, GOSSIP_SENDER_MAIN, 1);

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Location Information:", GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "  Map: " + mapName, GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "  Area: " + areaName, GOSSIP_SENDER_MAIN, 1);
        if(!offline) {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "  Zone: " + zoneName, GOSSIP_SENDER_MAIN, 1);
        }
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, "Back to Bounty Listings", GOSSIP_SENDER_MAIN, OPTION_SHOW_BOUNTIES);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Goodbye", GOSSIP_SENDER_MAIN, OPTION_GOODBYE);
        return true;
        //player->SEND_GOSSIP_MENU(BOUNTY_TEXT_BOUNTY_INFO, Creature->GetGUID());
    }

    inline bool closeGossipNotify(Player *pPlayer, std::string message) {
        pPlayer->PlayerTalkClass->SendCloseGossip();
        pPlayer->GetSession()->SendNotification(message.c_str());
        return true;
    }

};

class BountyTimerItem : public WorldScript
{
private:
    IntervalTimer m_bountyTimer;
    BountyHunterItem *m_bountyHunter;
public:
    BountyTimerItem(BountyHunterItem *bountyHunter): WorldScript("BountyTimer"), m_bountyHunter(bountyHunter) {
        m_bountyTimer.SetCurrent(0);
        m_bountyTimer.SetInterval(15000);
    }

    void OnUpdate(uint32 diff) {
        m_bountyTimer.Update(diff);
        if(m_bountyTimer.Passed()) {
            m_bountyTimer.Reset();
            pruneBounty();
        }

    }
    void pruneBounty() {
        time_t currentTime = time(NULL);
        for(std::map<uint32, BountyData>::iterator iter = bountyMap.begin(), end = bountyMap.end(); iter != end; ++iter) 
        {
            BountyData *bounty = &iter->second;
            if(bounty->expiretime < currentTime) {
                m_bountyHunter->ExpireBounty(bounty, true);
                bountyMap.erase(iter);
            } else {
                Player *player = sObjectAccessor->FindPlayer(bounty->guid);
                if(player) {
                    if(player->isAlive() && !player->InArena()) { // keep refreshing the aura. 
                        player->AddAura(BOUNTY_MARKER, player);
                        player->SetPvP(true);
                        player->SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
                    }
                }
            }
        }
    }

};

class BountyKillsItem : public PlayerScript
{
private:
    BountyHunterItem *m_bountyHunter;
public:
    BountyKillsItem(BountyHunterItem *bountyHunter) : PlayerScript("BountyKills"), m_bountyHunter(bountyHunter) {}

    void OnPVPKill(Player * killer, Player * victim)
    {
        BountyData *bounty = getBountyByGuid(victim->GetGUIDLow());
        if (bounty) {
            if(victim->GetGUIDLow() != killer->GetGUIDLow())
                m_bountyHunter->ClaimBounty(bounty, killer, victim);
        }

        bounty = getBountyByGuid(killer->GetGUIDLow());
        if (bounty && victim->GetGUIDLow() == bounty->posterguid) {
            m_bountyHunter->ClaimReverseBounty(bounty, killer, victim);
        }
    }

    void OnLogin(Player* player) 
    {
        BountyData *bounty = getBountyByGuid(player->GetGUIDLow());
        if(!bounty) {
            if(player->HasAura(BOUNTY_MARKER)) 
                player->RemoveAura(BOUNTY_MARKER);
        } 
        else if(bounty->expiretime >= time(NULL))
        {
            if(player->isAlive() && !player->InArena())
                player->AddAura(BOUNTY_MARKER, player);
            uint32 gold = bounty->money;

            player->GetSession()->SendAreaTriggerMessage(
                "A reward of %u Bounty Tokens has been placed on |cffff0000YOU|r by |cff00ff00%s|r! Kill the person who placed the bounty on you to clear your name.", 
                gold, m_bountyHunter->GetCharacterNameByGuid(bounty->posterguid).c_str());
        } else {
            m_bountyHunter->ExpireBounty(bounty, true, true);
        }

    }
};

void AddSC_BountyHunter()
{
    BountyHunter *bountyHunter = new BountyHunter();
    new BountyKills(bountyHunter);
    new BountyTimer(bountyHunter);

    BountyHunterItem *bountyHunterItem = new BountyHunterItem();
    new BountyKillsItem(bountyHunterItem);
    new BountyTimerItem(bountyHunterItem);
}
