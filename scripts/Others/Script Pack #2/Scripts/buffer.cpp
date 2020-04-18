/* Copyright (C) 2008-09 TrinityCore & John Diver <http://www.trinitycore.org/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *
 * This script has been created by John Diver.
 * HHScripts takes no ownership.
 * You can: share-alike.
 */

/* ScriptData
ScriptName: Npc_buffer
ScriptComment: Wotlk Buffer -Fixed at Trinity
*/

#include "precompiled.h"

/*** Define ***/
//Buff - Druid
#define	BUFF_MARK_OF_THE_WILD		48469
#define BUFF_THORNS					53307
//Buff - Mage
#define BUFF_ARCANE_INTELLECT		42955
//Buff - Paladin
#define BUFF_BLESSING_OF_WISDOM		48938
#define BUFF_BLESSING_OF_KINGS		25898
#define BUFF_BLESSING_OF_SANCTUARY 	25899
#define BUFF_BLESSING_OF_MIGHT		48932
//Buff - Priest
#define BUFF_DIVINE_SPIRIT			48073
#define BUFF_POWER_WORD_FORTITUDE	48161
#define BUFF_SHADOW_PROTECTION		48169

/*** Source ***/

bool GossipHello_npc_buffer(Player *player, Creature *_Creature)
{
	player->ADD_GOSSIP_ITEM(8, "Mark of the Wild",		GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
	player->ADD_GOSSIP_ITEM(8, "Thorns",				GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
	player->ADD_GOSSIP_ITEM(2, "Arcane intellect",		GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
	player->ADD_GOSSIP_ITEM(3, "Blessing of Wisdom",	GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
	player->ADD_GOSSIP_ITEM(3, "Blessing of Kings",		GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
	player->ADD_GOSSIP_ITEM(3, "Blessing of Sanctuary",	GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
	player->ADD_GOSSIP_ITEM(3, "Blessing of Might",		GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
	player->ADD_GOSSIP_ITEM(6, "Divine spirit",			GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
	player->ADD_GOSSIP_ITEM(6, "Power word: Fortitude",	GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
	player->ADD_GOSSIP_ITEM(6, "Shadow Protection",		GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
	player->ADD_GOSSIP_ITEM(6, "Close",					GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 0);
	player->SEND_GOSSIP_MENU(1, _Creature->GetGUID());
	return true;
}

bool GossipSelect_npc_buffer(Player *player, Creature *_Creature, uint32 sender, uint32 action )
{
	switch(action)
	{
		case GOSSIP_ACTION_INFO_DEF + 1: //Mark of the Wild (Rank 9)
			player->CLOSE_GOSSIP_MENU();
			_Creature->CastSpell(player, BUFF_MARK_OF_THE_WILD, false);
		break;
		case GOSSIP_ACTION_INFO_DEF + 2: //Thorns (Rank 8)
			player->CLOSE_GOSSIP_MENU();
			_Creature->CastSpell(player, BUFF_THORNS, false);
		break;
		case GOSSIP_ACTION_INFO_DEF + 3: //Arcane intellect (Rank 7)
			player->CLOSE_GOSSIP_MENU();
			_Creature->CastSpell(player, BUFF_ARCANE_INTELLECT, false);
		break;
		case GOSSIP_ACTION_INFO_DEF + 4: //Blessing of Wisdom (Rank 5)
			player->CLOSE_GOSSIP_MENU();
			_Creature->CastSpell(player, BUFF_BLESSING_OF_WISDOM, false);
		break;
		case GOSSIP_ACTION_INFO_DEF + 5: //Blessing of Kings
			player->CLOSE_GOSSIP_MENU();
			_Creature->CastSpell(player, BUFF_BLESSING_OF_KINGS, false);
		break;
		case GOSSIP_ACTION_INFO_DEF + 6: //Blessing of Sanctuary
			player->CLOSE_GOSSIP_MENU();
			_Creature->CastSpell(player, BUFF_BLESSING_OF_SANCTUARY, false);
		break;
		case GOSSIP_ACTION_INFO_DEF + 7: //Blessing of Might (Rank 10)
			player->CLOSE_GOSSIP_MENU();
			_Creature->CastSpell(player, BUFF_BLESSING_OF_MIGHT, false);
		break;
		case GOSSIP_ACTION_INFO_DEF + 8: //Divine spirit (Rank 6)
			player->CLOSE_GOSSIP_MENU();
			_Creature->CastSpell(player, BUFF_DIVINE_SPIRIT, false);
		break;
		case GOSSIP_ACTION_INFO_DEF + 9: //Power word: Fortitude (Rank 8)
			player->CLOSE_GOSSIP_MENU();
			_Creature->CastSpell(player, BUFF_POWER_WORD_FORTITUDE, false);
		break;
		case GOSSIP_ACTION_INFO_DEF + 10: //Shadow Protection (Rank 5)
			player->CLOSE_GOSSIP_MENU();
			_Creature->CastSpell(player, BUFF_SHADOW_PROTECTION, false);
		break;
		case GOSSIP_ACTION_INFO_DEF + 0: //Menu close
			player->CLOSE_GOSSIP_MENU();
		break;
	}
	return true;
}

void AddSC_npc_buffer()
{
	Script *newscript;
	
	newscript = new Script;
	newscript->Name="npc_buffer";
	newscript->pGossipHello = &GossipHello_npc_buffer;
	newscript->pGossipSelect = &GossipSelect_npc_buffer;
	newscript->RegisterSelf();
}