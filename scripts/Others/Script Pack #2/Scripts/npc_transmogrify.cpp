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

#include "ScriptPCH.h"

enum TransmogrifyActions {
    ACTION_TIER_1,
    ACTION_TIER_2,
    ACTION_TIER_25,
    ACTION_TIER_3,
    ACTION_TIER_4,
    ACTION_TIER_5,
    ACTION_TIER_6,
    ACTION_ARENA_1,
    ACTION_ARENA_2,
    ACTION_ARENA_3,
    ACTION_ARENA_4,
    ACTION_REMOVE
};

class npc_transmogrify : public CreatureScript
{
    public:
        npc_transmogrify() : CreatureScript("npc_transmogrify") { }
		
		bool OnGossipHello(Player* player, Creature* creature){
		if (sWorld->getBoolConfig(CONFIG_FREE_TRANSMOGRIFICATION)){
            switch (player->getClass())
            {
                case CLASS_WARRIOR:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Tier 1", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Tier 2", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Ahn'Qiraj tier", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Tier 3", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Tier 4", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Tier 5", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Tier 6", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Season 1", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Season 2", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Season 3", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Season 4", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_PALADIN:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Tier 1", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Tier 2", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Ahn'Qiraj tier", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Tier 3", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Tier 4", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Tier 5", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Tier 6", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Season 1", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Season 2", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Season 3", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Season 4", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_HUNTER:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Tier 1", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Tier 2", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Ahn'Qiraj tier", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Tier 3", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Tier 4", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Tier 5", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Tier 6", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Season 1", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Season 2", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Season 3", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Season 4", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_ROGUE:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Tier 1", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Tier 2", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Ahn'Qiraj tier", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Tier 3", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Tier 4", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Tier 5", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Tier 6", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Season 1", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Season 2", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Season 3", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Season 4", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_PRIEST:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Tier 1", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Tier 2", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Ahn'Qiraj tier", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Tier 3", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Tier 4", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Tier 5", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Tier 6", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Season 1", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Season 2", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Season 3", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Season 4", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_DEATH_KNIGHT:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Tier 1", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Tier 2", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Ahn'Qiraj tier", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Tier 3", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Tier 4", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Tier 5", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Tier 6", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Season 1", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Season 2", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Season 3", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Season 4", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_SHAMAN:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Tier 1", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Tier 2", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Tier Ahn'Qiraj tier", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Tier 3", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Tier 4", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Tier 5", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Tier 6", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Season 1", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Season 2", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Season 3", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Season 4", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_MAGE:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Tier 1", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Tier 2", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Tier Ahn'Qiraj tier", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Tier 3", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Tier 4", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Tier 5", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Tier 6", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Season 1", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Season 2", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Season 3", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Season 4", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_WARLOCK:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Tier 1", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Tier 2", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Tier Ahn'Qiraj tier", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Tier 3", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Tier 4", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Tier 5", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Tier 6", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Season 1", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Season 2", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Season 3", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Season 4", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_DRUID:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Tier 1", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Tier 2", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Tier Ahn'Qiraj tier", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Tier 3", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Tier 4", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Tier 5", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Tier 6", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Season 1", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Season 2", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Season 3", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Season 4", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
            }
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Remove transmogrification", GOSSIP_SENDER_MAIN, ACTION_REMOVE);
            player->SEND_GOSSIP_MENU(51000, creature->GetGUID());
            return true;
        }
		else{
		{
            switch (player->getClass())
            {
                case CLASS_WARRIOR:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Tier 1 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Tier 2 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Ahn'Qiraj tier (2000 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Tier 3 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Tier 4 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Tier 5 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Tier 6 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Season 1 (1550 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Season 2 (1750 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Season 3 (2000 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warrior Season 4 (2200 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_PALADIN:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Tier 1 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Tier 2 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Ahn'Qiraj tier (2000 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Tier 3 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Tier 4 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Tier 5 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Tier 6 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Season 1 (1550 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Season 2 (1750 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Season 3 (2000 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Paladin Season 4 (2200 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_HUNTER:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Tier 1 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Tier 2 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Ahn'Qiraj tier (2000 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Tier 3 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Tier 4 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Tier 5 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Tier 6 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Season 1 (1550 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Season 2 (1750 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Season 3 (2000 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Hunter Season 4 (2200 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_ROGUE:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Tier 1 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Tier 2 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Ahn'Qiraj tier (2000 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Tier 3 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Tier 4 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Tier 5 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Tier 6 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Season 1 (1550 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Season 2 (1750 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Season 3 (2000 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Rogue Season 4 (2200 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_PRIEST:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Tier 1 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Tier 2 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Ahn'Qiraj tier (2000 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Tier 3 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Tier 4 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Tier 5 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Tier 6 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Season 1 (1550 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Season 2 (1750 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Season 3 (2000 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Priest Season 4 (2200 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_DEATH_KNIGHT:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Tier 1 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Tier 2 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Ahn'Qiraj tier (2000 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Tier 3 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Tier 4 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Tier 5 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Tier 6 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Season 1 (1550 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Season 2 (1750 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Season 3 (2000 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Death Knight Season 4 (2200 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_SHAMAN:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Tier 1 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Tier 2 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Tier Ahn'Qiraj tier (2000 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Tier 3 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Tier 4 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Tier 5 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Tier 6 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Season 1 (1550 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Season 2 (1750 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Season 3 (2000 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Shaman Season 4 (2200 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_MAGE:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Tier 1 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Tier 2 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Tier Ahn'Qiraj tier (2000 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Tier 3 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Tier 4 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Tier 5 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Tier 6 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Season 1 (1550 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Season 2 (1750 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Season 3 (2000 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Mage Season 4 (2200 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_WARLOCK:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Tier 1 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Tier 2 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Tier Ahn'Qiraj tier (2000 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Tier 3 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Tier 4 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Tier 5 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Tier 6 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Season 1 (1550 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Season 2 (1750 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Season 3 (2000 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Warlock Season 4 (2200 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
                case CLASS_DRUID:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Tier 1 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Tier 2 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Tier Ahn'Qiraj tier (2000 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_25);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Tier 3 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Tier 4 (1550 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_4);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Tier 5 (1750 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_5);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Tier 6 (2200 3v3 Rating)", GOSSIP_SENDER_MAIN, ACTION_TIER_6);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Season 1 (1550 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_1);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Season 2 (1750 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_2);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Season 3 (2000 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_3);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Druid Season 4 (2200 2v2 Rating)", GOSSIP_SENDER_MAIN, ACTION_ARENA_4);
                    break;
            }
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Remove transmogrification", GOSSIP_SENDER_MAIN, ACTION_REMOVE);
            player->SEND_GOSSIP_MENU(51000, creature->GetGUID());
            return true;
        }}}

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
        {
            player->PlayerTalkClass->CloseGossip();
			
		if (sWorld->getBoolConfig(CONFIG_FREE_TRANSMOGRIFICATION)){
            switch (action)
            {
                case ACTION_TIER_1:
                        TransmogrifyItems(player, creature, ACTION_TIER_1);                 
                    break;
                case ACTION_TIER_2:
                        TransmogrifyItems(player, creature, ACTION_TIER_2);
                    break;
                case ACTION_TIER_25:
                        TransmogrifyItems(player, creature, ACTION_TIER_25);
                    break;
                case ACTION_TIER_3:
                        TransmogrifyItems(player, creature, ACTION_TIER_3);
                    break;
                case ACTION_TIER_4:
                        TransmogrifyItems(player, creature, ACTION_TIER_4);
                    break;
                case ACTION_TIER_5:
                        TransmogrifyItems(player, creature, ACTION_TIER_5);
                    break;
                case ACTION_TIER_6:
                        TransmogrifyItems(player, creature, ACTION_TIER_6);
                    break;
                case ACTION_ARENA_1:
                        TransmogrifyItems(player, creature, ACTION_ARENA_1);
                    break;
                case ACTION_ARENA_2:
                        TransmogrifyItems(player, creature, ACTION_ARENA_2);
                    break;
                case ACTION_ARENA_3:
                        TransmogrifyItems(player, creature, ACTION_ARENA_3);
                    break;
                case ACTION_ARENA_4:
                        TransmogrifyItems(player, creature, ACTION_ARENA_4);
                    break;
                case ACTION_REMOVE:
                    for (uint8 i=0; i<10; i++)
                    {
                        Item *trItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
                        if (!trItem)
                            continue;

                        trItem->RemoveFakeDisplay();
                        player->SetVisibleItemSlot(i,trItem);

                        player->CastSpell(player, 27123, false);
                    }
                    break;
        }}
		else{
			switch (action)
            {
                case ACTION_TIER_1:
                    if (player->isGameMaster() || player->GetAchievementMgr().HasAchieved(GetAchievementStore()->LookupEntry(402)))
                        TransmogrifyItems(player, creature, ACTION_TIER_1);
                    else
                        creature->MonsterWhisper("You don't have required rating.", player->GetGUID());
                    break;
                case ACTION_TIER_2:
                    if (player->isGameMaster() || player->GetAchievementMgr().HasAchieved(GetAchievementStore()->LookupEntry(403)))
                        TransmogrifyItems(player, creature, ACTION_TIER_2);
                    else
                        creature->MonsterWhisper("You don't have required rating.", player->GetGUID());
                    break;
                case ACTION_TIER_25:
                    if (player->isGameMaster() || player->GetAchievementMgr().HasAchieved(GetAchievementStore()->LookupEntry(405)))
                        TransmogrifyItems(player, creature, ACTION_TIER_25);
                    else
                        creature->MonsterWhisper("You don't have required rating.", player->GetGUID());
                    break;
                case ACTION_TIER_3:
                    if (player->isGameMaster() || player->GetAchievementMgr().HasAchieved(GetAchievementStore()->LookupEntry(1160)))
                        TransmogrifyItems(player, creature, ACTION_TIER_3);
                    else
                        creature->MonsterWhisper("You don't have required rating.", player->GetGUID());
                    break;
                case ACTION_TIER_4:
                    if (player->isGameMaster() || player->GetAchievementMgr().HasAchieved(GetAchievementStore()->LookupEntry(402)))
                        TransmogrifyItems(player, creature, ACTION_TIER_4);
                    else
                        creature->MonsterWhisper("You don't have required rating.", player->GetGUID());
                    break;
                case ACTION_TIER_5:
                    if (player->isGameMaster() || player->GetAchievementMgr().HasAchieved(GetAchievementStore()->LookupEntry(403)))
                        TransmogrifyItems(player, creature, ACTION_TIER_5);
                    else
                        creature->MonsterWhisper("You don't have required rating.", player->GetGUID());
                    break;
                case ACTION_TIER_6:
                    if (player->isGameMaster() || player->GetAchievementMgr().HasAchieved(GetAchievementStore()->LookupEntry(1160)))
                        TransmogrifyItems(player, creature, ACTION_TIER_6);
                    else
                        creature->MonsterWhisper("You don't have required rating.", player->GetGUID());
                    break;
                case ACTION_ARENA_1:
                    if (player->isGameMaster() || player->GetAchievementMgr().HasAchieved(GetAchievementStore()->LookupEntry(399)))
                        TransmogrifyItems(player, creature, ACTION_ARENA_1);
                    else
                        creature->MonsterWhisper("You don't have required rating.", player->GetGUID());
                    break;
                case ACTION_ARENA_2:
                    if (player->isGameMaster() || player->GetAchievementMgr().HasAchieved(GetAchievementStore()->LookupEntry(400)))
                        TransmogrifyItems(player, creature, ACTION_ARENA_2);
                    else
                        creature->MonsterWhisper("You don't have required rating.", player->GetGUID());
                    break;
                case ACTION_ARENA_3:
                    if (player->isGameMaster() || player->GetAchievementMgr().HasAchieved(GetAchievementStore()->LookupEntry(401)))
                        TransmogrifyItems(player, creature, ACTION_ARENA_3);
                    else
                        creature->MonsterWhisper("You don't have required rating.", player->GetGUID());
                    break;
                case ACTION_ARENA_4:
                    if (player->isGameMaster() || player->GetAchievementMgr().HasAchieved(GetAchievementStore()->LookupEntry(1159)))
                        TransmogrifyItems(player, creature, ACTION_ARENA_4);
                    else
                        creature->MonsterWhisper("You don't have required rating.", player->GetGUID());
                    break;
                case ACTION_REMOVE:
                    for (uint8 i=0; i<10; i++)
                    {
                        Item *trItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
                        if (!trItem)
                            continue;

                        trItem->RemoveFakeDisplay();
                        player->SetVisibleItemSlot(i,trItem);

                        player->CastSpell(player, 27123, false);
                    }
                    break;
		
		}}
		return true;
		}
		
        // Функция пробегает по слотам и задает фейковые значения для отображения.
        // В функцию передаются массив идов вещей, размер массива, а также "вариант" для исключения некоторых слотов.
        // variant = 0 - 8 вещей (в порядке - голова, наплечи, грудь, пояс, штаны, боты, наручи, перчи).
        // variant = 1 - 5 вещей (в порядке - голова, наплечи, грудь, штаны, боты).
        // variant = 2 - 5 вещей (в порядке - голова, наплечи, грудь, штаны, перчи).
        void ItemCycle(Player* player, int32 mas[], int8 size = 8, int8 variant = 0)
        {
            for (uint8 i=0; i<10;i++)
            {
                if (!variant)
                {
                    if (i==1 || i==3)
                        continue;
                }

                if (variant==1)
                {
                    if (i==1 || i==3 || i==5 || i==8 || i==9)
                        continue;
                }

                if (variant==2)
                {
                    if (i==1 || i==3 || i==5 || i==7 || i==8)
                        continue;
                }

                Item *trItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0,i);
                if (!trItem)
                    continue;

                for(uint8 n=0;n<size;n++)
                {
                    trItem->SetFakeDisplay(mas[n]);
                    player->SetVisibleItemSlot(i,trItem);
                }
            }
        }

        void TransmogrifyItems(Player* player, Creature* creature, int8 tier)
        {
            ChatHandler handler(player);

            int32 t1_war[8] = {16866,16868,16865,16864,16867,16862,16861,16863};
            int32 t1_pal[8] = {16854,16856,16853,16858,16855,16859,16857,16860};
            int32 t1_hun[8] = {16846,16848,16845,16851,16847,16849,16850,16852};
            int32 t1_rog[8] = {16821,16823,16820,16827,16822,16824,16825,16826};
            int32 t1_pri[8] = {16813,16816,16815,16817,16814,16811,16819,16812};
            int32 t1_sha[8] = {16842,16844,16841,16838,16843,16847,16840,16839};
            int32 t1_mag[8] = {16795,16797,16798,16802,16796,16800,16799,16801};
            int32 t1_wrl[8] = {16808,16807,16809,16806,16810,16803,16804,16805};
            int32 t1_dru[8] = {16834,16831,16833,16828,16835,16829,16830,16831};

            int32 t2_war[8] = {16963,16961,16966,16960,16962,16965,16959,16964};
            int32 t2_pal[8] = {16955,16953,16958,16952,16954,16957,16951,16956};
            int32 t2_hun[8] = {16939,16937,16942,16936,16938,16941,16935,16940};
            int32 t2_rog[8] = {16908,16832,16905,16910,16909,16906,16911,16907};
            int32 t2_pri[8] = {16921,16924,16923,16925,16922,16919,16926,16920};
            int32 t2_sha[8] = {16947,16945,16950,16944,16946,16949,16943,16948};
            int32 t2_mag[8] = {16914,16917,16916,16918,16915,16912,16918,16913};
            int32 t2_wrl[8] = {16929,16932,16931,16933,16930,16927,16934,16928};
            int32 t2_dru[8] = {16900,16902,16897,16903,16901,16898,16904,16899};

            int32 t25_war[5] = {21329,21330,21331,21332,21333};
            int32 t25_pal[5] = {21387,21391,21389,21390,21388};
            int32 t25_hun[5] = {21366,21367,21370,21368,21365};
            int32 t25_rog[5] = {21360,21361,21364,21362,21359};
            int32 t25_pri[5] = {21348,21350,21351,21352,21349};
            int32 t25_sha[5] = {21372,21376,21374,21375,21373};
            int32 t25_mag[5] = {21347,21345,21343,21346,21344};
            int32 t25_wrl[5] = {21337,21335,21334,21336,21338};
            int32 t25_dru[5] = {21353,21354,21357,21356,21355};

            int32 t3_war[8] = {22418,22419,22416,22422,22417,22420,22423,22421};
            int32 t3_pal[8] = {22428,22429,22425,22431,22427,22430,22424,22426};
            int32 t3_hun[8] = {22438,22439,22436,22442,22437,22440,22443,22441};
            int32 t3_rog[8] = {22478,22479,22476,22482,22477,22480,22483,22481};
            int32 t3_pri[8] = {22514,22515,22512,22518,22513,22516,22519,22517};
            int32 t3_sha[8] = {22466,22467,22464,22470,22465,22468,22471,22469};
            int32 t3_mag[8] = {22498,22499,22496,22502,22497,22500,22503,22501};
            int32 t3_wrl[8] = {22506,22507,22504,22510,22505,22508,22511,22509};
            int32 t3_dru[8] = {22490,22491,22488,22494,22489,22492,22495,22493};

            int32 t4_war[5] = {29021,29023,29019,29022,29020};
            int32 t4_pal[5] = {29068,29070,29066,29069,29067};
            int32 t4_hun[5] = {29081,29084,29082,29083,29085};
            int32 t4_rog[5] = {29044,29047,29045,29046,29048};
            int32 t4_pri[5] = {29049,29054,29050,29053,29055};
            int32 t4_sha[5] = {29040,29043,29038,29042,29039};
            int32 t4_mag[5] = {29076,29079,29077,29078,29080};
            int32 t4_wrl[5] = {28963,28967,28964,28966,28968};
            int32 t4_dru[5] = {29098,29100,29096,29099,29097};

            int32 t5_war[5] = {30115,30117,30113,30116,30114};
            int32 t5_pal[5] = {30125,30127,30123,30126,30124};
            int32 t5_hun[5] = {30141,30143,30139,30142,30140};
            int32 t5_rog[5] = {30146,30149,30144,30148,30145};
            int32 t5_pri[5] = {30152,30154,30150,30153,30151};
            int32 t5_sha[5] = {30190,30194,30185,30192,30189};
            int32 t5_mag[5] = {30206,30210,30196,30207,30205};
            int32 t5_wrl[5] = {30212,30215,30214,30213,30211};
            int32 t5_dru[5] = {30228,30230,30222,30229,30223};

            int32 t6_war[8] = {30972,30979,30975,34546,30977,34569,34441,30969};
            int32 t6_pal[8] = {30987,30998,30991,34488,30995,34560,34433,30985};
            int32 t6_hun[8] = {31003,31006,31004,34549,31005,34570,34443,31001};
            int32 t6_rog[8] = {31027,31030,31028,34558,31029,34575,34448,31026};
            int32 t6_pri[8] = {31064,31070,31065,34528,31067,34563,34434,31061};
            int32 t6_sha[8] = {31015,31024,31018,34545,31021,34567,34439,31011};
            int32 t6_mag[8] = {31056,31059,31057,34557,31058,34574,34447,31055};
            int32 t6_wrl[8] = {31051,31054,31052,34541,31053,34564,34436,31050};
            int32 t6_dru[8] = {31039,31048,31042,34556,31044,34573,34444,31034};

            int32 a1_war[5] = {24545,24546,24544,24547,24549};
            int32 a1_pal[5] = {27881,27883,27879,27882,27880};
            int32 a1_hun[5] = {28331,28333,28334,28332,28335};
            int32 a1_rog[5] = {25830,25832,25831,25833,25834};
            int32 a1_pri[5] = {27708,27710,27711,27709,27707};
            int32 a1_sha[5] = {27471,27473,27469,27472,27470};
            int32 a1_mag[5] = {25855,25854,25856,25858,25857};
            int32 a1_wrl[5] = {24553,24554,24552,24555,24556};
            int32 a1_dru[5] = {31376,31378,31379,31377,31375};

            int32 a2_war[5] = {30488,30490,30486,30489,30487};
            int32 a2_pal[5] = {32022,32024,32020,32023,32021};
            int32 a2_hun[5] = {31962,31964,31960,31963,31961};
            int32 a2_rog[5] = {31999,32001,32002,32000,31998};
            int32 a2_pri[5] = {32035,32037,32038,32036,32034};
            int32 a2_sha[5] = {32011,32013,32009,32012,32010};
            int32 a2_mag[5] = {32048,32047,32050,32051,32049};
            int32 a2_wrl[5] = {31974,31976,31977,31975,31973};
            int32 a2_dru[5] = {31988,31990,31991,31989,31987};

            int32 a3_war[5] = {33730,33732,33728,33731,33729};
            int32 a3_pal[5] = {33751,33753,33749,33752,33750};
            int32 a3_hun[5] = {33666,33668,33664,33667,33665};
            int32 a3_rog[5] = {33701,33703,33704,33702,33700};
            int32 a3_pri[5] = {33745,33747,33748,33746,33744};
            int32 a3_sha[5] = {33713,33715,33711,33714,33712};
            int32 a3_mag[5] = {33758,33757,33760,33761,33759};
            int32 a3_wrl[5] = {33677,33679,33680,33678,33676};
            int32 a3_dru[5] = {33672,33674,33675,33673,33671};

            int32 a4_war[5] = {35068,35070,35066,35069,35067};
            int32 a4_pal[5] = {35061,35063,35059,35062,35060};
            int32 a4_hun[5] = {34992,34994,34990,34993,34991};
            int32 a4_rog[5] = {35033,35035,35036,35034,35032};
            int32 a4_pri[5] = {35084,35086,35087,35085,35083};
            int32 a4_dkn[5] = {40442,40444,40440,40443,40441};
            int32 a4_sha[5] = {35050,35052,35048,35051,35049};
            int32 a4_mag[5] = {35097,35096,35099,35100,35098};
            int32 a4_wrl[5] = {35004,35006,35007,35005,35003};
            int32 a4_dru[5] = {35023,35025,35026,35024,35022};

            switch (tier)
            {
                case ACTION_TIER_1:
                    switch (player->getClass())
                    {
                        case CLASS_WARRIOR:
                        case CLASS_DEATH_KNIGHT:
                            ItemCycle(player,t1_war);
                            break;
                        case CLASS_PALADIN:
                            ItemCycle(player,t1_pal);
                            break;
                        case CLASS_HUNTER:
                            ItemCycle(player,t1_hun);
                            break;
                        case CLASS_ROGUE:
                            ItemCycle(player,t1_rog);
                            break;
                        case CLASS_PRIEST:
                            ItemCycle(player,t1_pri);
                            break;
                        case CLASS_SHAMAN:
                            ItemCycle(player,t1_sha);
                            break;
                        case CLASS_MAGE:
                            ItemCycle(player,t1_mag);
                            break;
                        case CLASS_WARLOCK:
                            ItemCycle(player,t1_wrl);
                            break;
                        case CLASS_DRUID:
                            ItemCycle(player,t1_dru);
                            break;
                        default:
                            break;
                    }
                    break;
                case ACTION_TIER_2:
                    switch (player->getClass())
                    {
                        case CLASS_WARRIOR:
                        case CLASS_DEATH_KNIGHT:
                            ItemCycle(player,t2_war);
                            break;
                        case CLASS_PALADIN:
                            ItemCycle(player,t2_pal);
                            break;
                        case CLASS_HUNTER:
                            ItemCycle(player,t2_hun);
                            break;
                        case CLASS_ROGUE:
                            ItemCycle(player,t2_rog);
                            break;
                        case CLASS_PRIEST:
                            ItemCycle(player,t2_pri);
                            break;
                        case CLASS_SHAMAN:
                            ItemCycle(player,t2_sha);
                            break;
                        case CLASS_MAGE:
                            ItemCycle(player,t2_mag);
                            break;
                        case CLASS_WARLOCK:
                            ItemCycle(player,t2_wrl);
                            break;
                        case CLASS_DRUID:
                            ItemCycle(player,t2_dru);
                            break;
                        default:
                            break;
                    }
                    break;
                case ACTION_TIER_25:
                    switch (player->getClass())
                    {
                        case CLASS_WARRIOR:
                        case CLASS_DEATH_KNIGHT:
                            ItemCycle(player,t25_war,5,1);
                            break;
                        case CLASS_PALADIN:
                            ItemCycle(player,t25_pal,5,1);
                            break;
                        case CLASS_HUNTER:
                            ItemCycle(player,t25_hun,5,1);
                            break;
                        case CLASS_ROGUE:
                            ItemCycle(player,t25_rog,5,1);
                            break;
                        case CLASS_PRIEST:
                            ItemCycle(player,t25_pri,5,1);
                            break;
                        case CLASS_SHAMAN:
                            ItemCycle(player,t25_sha,5,1);
                            break;
                        case CLASS_MAGE:
                            ItemCycle(player,t25_mag,5,1);
                            break;
                        case CLASS_WARLOCK:
                            ItemCycle(player,t25_wrl,5,1);
                            break;
                        case CLASS_DRUID:
                            ItemCycle(player,t25_dru,5,1);
                            break;
                        default:
                            break;
                    }
                    break;
                case ACTION_TIER_3:
                    switch (player->getClass())
                    {
                        case CLASS_WARRIOR:
                        case CLASS_DEATH_KNIGHT:
                            ItemCycle(player,t3_war);
                            break;
                        case CLASS_PALADIN:
                            ItemCycle(player,t3_pal);
                            break;
                        case CLASS_HUNTER:
                            ItemCycle(player,t3_hun);
                            break;
                        case CLASS_ROGUE:
                            ItemCycle(player,t3_rog);
                            break;
                        case CLASS_PRIEST:
                            ItemCycle(player,t3_pri);
                            break;
                        case CLASS_SHAMAN:
                            ItemCycle(player,t3_sha);
                            break;
                        case CLASS_MAGE:
                            ItemCycle(player,t3_mag);
                            break;
                        case CLASS_WARLOCK:
                            ItemCycle(player,t3_wrl);
                            break;
                        case CLASS_DRUID:
                            ItemCycle(player,t3_dru);
                            break;
                        default:
                            break;
                    }
                    break;
                case ACTION_TIER_4:
                    switch (player->getClass())
                    {
                        case CLASS_WARRIOR:
                        case CLASS_DEATH_KNIGHT:
                            ItemCycle(player,t4_war,5,2);
                            break;
                        case CLASS_PALADIN:
                            ItemCycle(player,t4_pal,5,2);
                            break;
                        case CLASS_HUNTER:
                            ItemCycle(player,t4_hun,5,2);
                            break;
                        case CLASS_ROGUE:
                            ItemCycle(player,t4_rog,5,2);
                            break;
                        case CLASS_PRIEST:
                            ItemCycle(player,t4_pri,5,2);
                            break;
                        case CLASS_SHAMAN:
                            ItemCycle(player,t4_sha,5,2);
                            break;
                        case CLASS_MAGE:
                            ItemCycle(player,t4_mag,5,2);
                            break;
                        case CLASS_WARLOCK:
                            ItemCycle(player,t4_wrl,5,2);
                            break;
                        case CLASS_DRUID:
                            ItemCycle(player,t4_dru,5,2);
                            break;
                        default:
                            break;
                    }
                    break;
                case ACTION_TIER_5:
                    switch (player->getClass())
                    {
                        case CLASS_WARRIOR:
                        case CLASS_DEATH_KNIGHT:
                            ItemCycle(player,t5_war,5,2);
                            break;
                        case CLASS_PALADIN:
                            ItemCycle(player,t5_pal,5,2);
                            break;
                        case CLASS_HUNTER:
                            ItemCycle(player,t5_hun,5,2);
                            break;
                        case CLASS_ROGUE:
                            ItemCycle(player,t5_rog,5,2);
                            break;
                        case CLASS_PRIEST:
                            ItemCycle(player,t5_pri,5,2);
                            break;
                        case CLASS_SHAMAN:
                            ItemCycle(player,t5_sha,5,2);
                            break;
                        case CLASS_MAGE:
                            ItemCycle(player,t5_mag,5,2);
                            break;
                        case CLASS_WARLOCK:
                            ItemCycle(player,t5_wrl,5,2);
                            break;
                        case CLASS_DRUID:
                            ItemCycle(player,t5_dru,5,2);
                            break;
                        default:
                            break;
                    }
                    break;
                case ACTION_TIER_6:
                    switch (player->getClass())
                    {
                        case CLASS_WARRIOR:
                        case CLASS_DEATH_KNIGHT:
                            ItemCycle(player,t6_war);
                            break;
                        case CLASS_PALADIN:
                            ItemCycle(player,t6_pal);
                            break;
                        case CLASS_HUNTER:
                            ItemCycle(player,t6_hun);
                            break;
                        case CLASS_ROGUE:
                            ItemCycle(player,t6_rog);
                            break;
                        case CLASS_PRIEST:
                            ItemCycle(player,t6_pri);
                            break;
                        case CLASS_SHAMAN:
                            ItemCycle(player,t6_sha);
                            break;
                        case CLASS_MAGE:
                            ItemCycle(player,t6_mag);
                            break;
                        case CLASS_WARLOCK:
                            ItemCycle(player,t6_wrl);
                            break;
                        case CLASS_DRUID:
                            ItemCycle(player,t6_dru);
                            break;
                        default:
                            break;
                    }
                    break;
                case ACTION_ARENA_1:
                    switch (player->getClass())
                    {
                        case CLASS_WARRIOR:
                        case CLASS_DEATH_KNIGHT:
                            ItemCycle(player,a1_war,5,2);
                            break;
                        case CLASS_PALADIN:
                            ItemCycle(player,a1_pal,5,2);
                            break;
                        case CLASS_HUNTER:
                            ItemCycle(player,a1_hun,5,2);
                            break;
                        case CLASS_ROGUE:
                            ItemCycle(player,a1_rog,5,2);
                            break;
                        case CLASS_PRIEST:
                            ItemCycle(player,a1_pri,5,2);
                            break;
                        case CLASS_SHAMAN:
                            ItemCycle(player,a1_sha,5,2);
                            break;
                        case CLASS_MAGE:
                            ItemCycle(player,a1_mag,5,2);
                            break;
                        case CLASS_WARLOCK:
                            ItemCycle(player,a1_wrl,5,2);
                            break;
                        case CLASS_DRUID:
                            ItemCycle(player,a1_dru,5,2);
                            break;
                        default:
                            break;
                    }
                    break;
                case ACTION_ARENA_2:
                    switch (player->getClass())
                    {
                        case CLASS_WARRIOR:
                        case CLASS_DEATH_KNIGHT:
                            ItemCycle(player,a2_war,5,2);
                            break;
                        case CLASS_PALADIN:
                            ItemCycle(player,a2_pal,5,2);
                            break;
                        case CLASS_HUNTER:
                            ItemCycle(player,a2_hun,5,2);
                            break;
                        case CLASS_ROGUE:
                            ItemCycle(player,a2_rog,5,2);
                            break;
                        case CLASS_PRIEST:
                            ItemCycle(player,a2_pri,5,2);
                            break;
                        case CLASS_SHAMAN:
                            ItemCycle(player,a2_sha,5,2);
                            break;
                        case CLASS_MAGE:
                            ItemCycle(player,a2_mag,5,2);
                            break;
                        case CLASS_WARLOCK:
                            ItemCycle(player,a2_wrl,5,2);
                            break;
                        case CLASS_DRUID:
                            ItemCycle(player,a2_dru,5,2);
                            break;
                        default:
                            break;
                    }
                    break;
                case ACTION_ARENA_3:
                    switch (player->getClass())
                    {
                        case CLASS_WARRIOR:
                        case CLASS_DEATH_KNIGHT:
                            ItemCycle(player,a3_war,5,2);
                            break;
                        case CLASS_PALADIN:
                            ItemCycle(player,a3_pal,5,2);
                            break;
                        case CLASS_HUNTER:
                            ItemCycle(player,a3_hun,5,2);
                            break;
                        case CLASS_ROGUE:
                            ItemCycle(player,a3_rog,5,2);
                            break;
                        case CLASS_PRIEST:
                            ItemCycle(player,a3_pri,5,2);
                            break;
                        case CLASS_SHAMAN:
                            ItemCycle(player,a3_sha,5,2);
                            break;
                        case CLASS_MAGE:
                            ItemCycle(player,a3_mag,5,2);
                            break;
                        case CLASS_WARLOCK:
                            ItemCycle(player,a3_wrl,5,2);
                            break;
                        case CLASS_DRUID:
                            ItemCycle(player,a3_dru,5,2);
                            break;
                        default:
                            break;
                    }
                    break;
                case ACTION_ARENA_4:
                    switch (player->getClass())
                    {
                        case CLASS_WARRIOR:
                            ItemCycle(player,a4_war,5,2);
                            break;
                        case CLASS_PALADIN:
                            ItemCycle(player,a4_pal,5,2);
                            break;
                        case CLASS_HUNTER:
                            ItemCycle(player,a4_hun,5,2);
                            break;
                        case CLASS_ROGUE:
                            ItemCycle(player,a4_rog,5,2);
                            break;
                        case CLASS_PRIEST:
                            ItemCycle(player,a4_pri,5,2);
                            break;
                        case CLASS_DEATH_KNIGHT:
                            ItemCycle(player,a4_dkn,5,2);
                            break;
                        case CLASS_SHAMAN:
                            ItemCycle(player,a4_sha,5,2);
                            break;
                        case CLASS_MAGE:
                            ItemCycle(player,a4_mag,5,2);
                            break;
                        case CLASS_WARLOCK:
                            ItemCycle(player,a4_wrl,5,2);
                            break;
                        case CLASS_DRUID:
                            ItemCycle(player,a4_dru,5,2);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }

            player->CastSpell(player, 27123, false);
        }
};

void AddSC_transmogrify_script()
{
    new npc_transmogrify();
}
