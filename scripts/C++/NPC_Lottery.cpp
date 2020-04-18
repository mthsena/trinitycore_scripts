#include "ScriptMgr.h"
#include "Player.h"
#include "WorldSession.h"
#include "Chat.h"
#include "ScriptedGossip.h"
#include "Creature.h"
#include "ScriptedCreature.h"
#include "ObjectAccessor.h"

#define DEFAULT_MESSAGE 907

using namespace std;

struct LotteryData
{
    uint32 itemId;
    string itemName;
    bool IsPending;

    LotteryData() : itemId(0), itemName(""), IsPending(false) { }
};
static LotteryData LotteryInfo;

struct PlayerData
{
    uint64 guid;
    uint8 number;
};
vector<PlayerData> pList;

class NPC_Lottery : public CreatureScript
{
public:
    NPC_Lottery() : CreatureScript("NPC_Lottery") {}

    void StartRaffle()
    {
        bool HasWinner = false;
        uint8 number = urand(1, 100);
        string numberStr = to_string(number);
        string msg = "|cffe1e1af";

        for (vector<PlayerData>::iterator itr = pList.begin(); itr != pList.end(); ++itr)
        {
            if (itr->number == number)
            {
                HasWinner = true;

                if (Player* plr = ObjectAccessor::FindPlayer(ObjectGuid(itr->guid)))
                {
                    msg += "<Lottery> raffled ";
                    msg += numberStr;
                    msg += " and the prize was added to the winner [";
                    msg += plr->GetName();
                    msg += "].";
                    sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);
                    plr->AddItem(LotteryInfo.itemId, 1);
                }
                else
                {
                    msg += "<Lottery> raffled ";
                    msg += numberStr;
                    msg += " and the winner is offline then the prize was lost.";
                    sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);
                }
            }
        }

        if (!HasWinner)
        {
            msg += "<Lottery> raffled ";
            msg += numberStr;
            msg += " and was closed without a winner.";
            sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);
        }

        pList.clear();
        LotteryInfo.itemId = 0;
        LotteryInfo.itemName = "";
        LotteryInfo.IsPending = false;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (LotteryInfo.itemId != 0)
        {
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "|TInterface/Buttons/UI-GroupLoot-Dice-Up:32:32:-32:0|tDo a bet", GOSSIP_SENDER_MAIN, 1, "", 0, true);
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "|TInterface/Icons/INV_Box_01:32:32:-32:0|tShow prize", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "|TInterface/Icons/INV_Misc_Coin_01:32:32:-32:0|tList bets", GOSSIP_SENDER_MAIN, 3);

            if (LotteryInfo.IsPending && player->GetSession()->GetSecurity() > SEC_PLAYER)
                AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "|TInterface/Icons/Trade_Engineering:32:32:-32:0|tStart raffle", GOSSIP_SENDER_MAIN, 20, "Are you sure?", 0, false);
        }
        else
        {
            if (!LotteryInfo.IsPending && player->GetSession()->GetSecurity() > SEC_PLAYER)
                AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "|TInterface/Icons/Trade_Engineering:32:32:-32:0|tOpen lottery", GOSSIP_SENDER_MAIN, 10, "", 0, true);
            else
                AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "|TInterface/PaperDollInfoFrame/UI-GearManager-LeaveItem-Opaque:32:32:-32:0|tLottery is closed.", GOSSIP_SENDER_MAIN, 100);
        }

        AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:32:32:-32:0|tExit.", GOSSIP_SENDER_MAIN, 100);

        SendGossipMenuFor(player, DEFAULT_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
        case 2:
            if (LotteryInfo.itemId == 0)
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Prize not found.");
                CloseGossipMenuFor(player);
                return false;
            }

            ChatHandler(player->GetSession()).PSendSysMessage("Prize: [%s]", LotteryInfo.itemName.c_str());
            CloseGossipMenuFor(player);
            break;

        case 3:
            if (pList.empty())
                ChatHandler(player->GetSession()).PSendSysMessage("No bets found.");

            for (vector<PlayerData>::iterator itr = pList.begin(); itr != pList.end(); ++itr)
            {
                if (Player* plr = ObjectAccessor::FindPlayer(ObjectGuid(itr->guid)))
                    ChatHandler(player->GetSession()).PSendSysMessage("%s bet %u\n", plr->GetName().c_str(), itr->number);
                else
                    ChatHandler(player->GetSession()).PSendSysMessage("(Offline) bet %u\n", itr->number);
            }

            CloseGossipMenuFor(player);
            break;

        case 20:
            StartRaffle();
            CloseGossipMenuFor(player);
            break;
        case 100:
            CloseGossipMenuFor(player);
            break;
        }

        return true;
    }

    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code)
    {
        player->PlayerTalkClass->ClearMenus();

        string msg = "|cffe1e1af";
        Item* item = NULL;

        switch (action)
        {
        case 1:
            if (atoi(code) < 1 || atoi(code) > 100)
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Type a number of 1-100.");
                CloseGossipMenuFor(player);
                return false;
            }

            for (vector<PlayerData>::iterator itr = pList.begin(); itr != pList.end(); ++itr)
            {
                if (itr->guid == player->GetGUID())
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("You already bet.");
                    CloseGossipMenuFor(player);
                    return false;
                }

                if (itr->number == atoi(code))
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("This bet already exists.");
                    CloseGossipMenuFor(player);
                    return false;
                }
            }

            PlayerData pData;
            pData.guid = player->GetGUID();
            pData.number = atoi(code);
            pList.push_back(pData);

            ChatHandler(player->GetSession()).PSendSysMessage("Your bet was registered!");
            CloseGossipMenuFor(player);
            break;

        case 10:
            item = player->GetItemByEntry(atoi(code));

            if (!item)
            {
                ChatHandler(player->GetSession()).PSendSysMessage("You not have this item or it not exists.");
                CloseGossipMenuFor(player);
                return false;
            }

            LotteryInfo.itemId = item->GetTemplate()->ItemId;
            LotteryInfo.itemName = item->GetTemplate()->Name1;
            LotteryInfo.IsPending = true;

            msg += "<Lottery> opened with prize [";
            msg += LotteryInfo.itemName;
            msg += "] |cffe1e1afplace your bets.";
            sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);
            CloseGossipMenuFor(player);
            break;
        }

        return true;
    }

    struct NPC_LotteryAI : public BossAI
    {
        NPC_LotteryAI(Creature* creature) : BossAI(creature, NULL) {}

        uint32 timer;

        void Reset()
        {
            // Run the every 30 seconds
            timer = 30 * IN_MILLISECONDS;
        }

        void UpdateAI(uint32 diff)
        {
            if (timer <= diff)
            {
                if (LotteryInfo.IsPending)
                {
                    std::stringstream ss;
                    ss << "Lottery is opened, worth [" << LotteryInfo.itemName << "]";
                    me->Say(ss.str(), LANG_UNIVERSAL, NULL);
                }

                timer = 30 * IN_MILLISECONDS;
            }
            else
                timer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new NPC_LotteryAI(creature);
    }

};

void AddSC_NPC_Lottery()
{
    new NPC_Lottery();
}