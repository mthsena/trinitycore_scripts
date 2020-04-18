/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
Name: Transmogrify Npc
%Complete: 100
Category: Custom Script
EndScriptData */

#include "ScriptPCH.h"

enum TransmogrifyActions
{
    ACTION_TRANSMOGRIFY_ADD_DISPLAY,
    ACTION_TRANSMOGRIFY_REMOVE_DISPLAY
};

const int32 PriceInGold = 1000 * 100 * 100; // 1k golds

class npc_trans : public CreatureScript
{
    public:
        npc_trans() : CreatureScript("npc_trans") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Я хочу изменить внешний вид моей вещи!", GOSSIP_SENDER_MAIN, ACTION_TRANSMOGRIFY_ADD_DISPLAY);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Я хочу сбросить изменения моей вещи!", GOSSIP_SENDER_MAIN, ACTION_TRANSMOGRIFY_REMOVE_DISPLAY);
            player->SEND_GOSSIP_MENU(51000, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
        {
            player->PlayerTalkClass->CloseGossip();
            switch (action)
            {
                case ACTION_TRANSMOGRIFY_ADD_DISPLAY:
                    TransmogrifyItem(player, creature);
                    break;
                case ACTION_TRANSMOGRIFY_REMOVE_DISPLAY:
                    ClearItem(player, creature);
                    break;
            }
            return true;
        }

        void TransmogrifyItem(Player* player, Creature* creature)
        {
            ChatHandler handler(player);
            Item *trItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, INVENTORY_SLOT_ITEM_START);
            Item *displayItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, INVENTORY_SLOT_ITEM_START + 1);
            if (!trItem || !displayItem)
            {
                handler.PSendSysMessage("Положите нужные предметы в первый и второй слот основной сумки!");
                return;
            }

            if (!player->HasEnoughMoney(PriceInGold))
            {
                handler.PSendSysMessage("Цена трансмогрификации 1000 золота!");
                return;
            }

            uint8 result = trItem->SetFakeDisplay(displayItem->GetProto()->ItemId);
            switch (result)
            {
                case FAKE_ERR_CANT_FIND_ITEM:
                    handler.PSendSysMessage("Не могу найти предмет!");
                    break;
                /*case FAKE_ERR_WRONG_QUALITY:
                    handler.PSendSysMessage("Нельзя трансмогрифицировать предметы с низким качеством!");
                    break;*/
                case FAKE_ERR_DIFF_SLOTS:
                    handler.PSendSysMessage("Предметы в первом и втором слоте сумки имеют разные типы!");
                    break;
                case FAKE_ERR_SUBCLASS:
                    handler.PSendSysMessage("Предметы в первом и втором слоте сумки имеют разные подклассы!");
                    break;
                case FAKE_ERR_DIFF_CLASS:
                    handler.PSendSysMessage("Товары требуют различные классовые критерии для надевания!");
                    break;
                case FAKE_ERR_DIFF_RACE:
                    handler.PSendSysMessage("Товары требуют различные расовые критерии для надевания!");
                    break;
                case FAKE_ERR_OK:
                {
                    WorldPacket data;
                    data << uint8(INVENTORY_SLOT_BAG_0);
                    data << uint8(trItem->GetSlot());
                    player->GetSession()->HandleAutoEquipItemOpcode(data);

                    player->ModifyMoney(-1 * PriceInGold);
                    
                    handler.PSendSysMessage("Трансмогрификация прошла успешно!");
                    creature->GetAI()->DoCast(63491);
                    break;
                }
            }
        }

        void ClearItem(Player* player, Creature* creature)
        {
            ChatHandler handler(player);
            Item *trItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, INVENTORY_SLOT_ITEM_START);
            if (!trItem)
            {
                handler.PSendSysMessage("Положите предмет в первый слот!");
                return;
            }

            trItem->RemoveFakeDisplay();

            WorldPacket data;
            data << uint8(INVENTORY_SLOT_BAG_0);
            data << uint8(trItem->GetSlot());
            player->GetSession()->HandleAutoEquipItemOpcode(data);

            creature->GetAI()->DoCast(63491);
        }
};

void AddSC_trans()
{
    new npc_trans;
}			
