
uint32 auras[] = {
    32609, // 0 - Flag A
    32610, // 1 - Flag H
    71304, // 2 - Green Spirit
    71986, // 3 - Red Spirit
    42744, // 4 - Blue Smoke
    52670, // 5 - Red Smoke
    61894, // 6 - Green Smoke
    28126, // 7 - Purple Smoke
    21336, // 8 - Chilled
    60451, // 9 - Corruption
    69105, // 10 - Horror
    55086, // 11 - Darkness
    68862, // 12 - Banish
    72521, // 13 - Shadowmourne
    26388, // 14 - Dream
    49411, // 15 - Lightning
    33569, // 16 - Glory
    75041, // 17 - Burning
    43184, // 18 - Flames
    68302, // 19 - Ground
    46804, // 20 - Fire Shield
    36193, // 21 - Saw
    40159, // 22 - Crystal Man
};

class NPC_Funny : public CreatureScript
{
public:
    NPC_Funny() : CreatureScript("NPC_Funny") {}

    void RemoveMorphs(Player* player)
    {
        player->DeMorph();
        player->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
    }

    void SetMorph(Player* player, uint32 entryId, float scale)
    {
        player->DeMorph();
        player->SetFloatValue(OBJECT_FIELD_SCALE_X, scale);
        player->SetUInt32Value(UNIT_FIELD_DISPLAYID, entryId);
        ChatHandler(player->GetSession()).PSendSysMessage("Success! Morph added.");
    }

    void RemoveAuras(Player* player)
    {
        for (int i = 0; i < (sizeof(auras) / sizeof(*auras)); i++)
            player->RemoveAura(auras[i]);
    }

    void SetAura(Player* player, uint32 auraId)
    {
        RemoveAuras(player);
        player->AddAura(auraId, player);
        ChatHandler(player->GetSession()).PSendSysMessage("Success! Aura added.");
    }

    void RemoveAll(Player* player)
    {
        RemoveMorphs(player);
        RemoveAuras(player);
        ChatHandler(player->GetSession()).PSendSysMessage("Success! Morphs and Auras removed.");
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Morphs", GOSSIP_SENDER_MAIN, 1);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Auras", GOSSIP_SENDER_MAIN, 2);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Remove All", GOSSIP_SENDER_MAIN, 3);
        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
        case 1:
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Alliance", GOSSIP_SENDER_MAIN, 4);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Horde", GOSSIP_SENDER_MAIN, 5);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            break;
        case 2:
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Flag", GOSSIP_SENDER_MAIN, 6);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Green Spirit", GOSSIP_SENDER_MAIN, 7);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Red Spirit", GOSSIP_SENDER_MAIN, 8);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Blue Smoke", GOSSIP_SENDER_MAIN, 9);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Red Smoke", GOSSIP_SENDER_MAIN, 10);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Green Smoke", GOSSIP_SENDER_MAIN, 11);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Purple Smoke", GOSSIP_SENDER_MAIN, 12);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Chilled", GOSSIP_SENDER_MAIN, 13);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Corruption", GOSSIP_SENDER_MAIN, 14);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Horror", GOSSIP_SENDER_MAIN, 15);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Darkness", GOSSIP_SENDER_MAIN, 16);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Banish", GOSSIP_SENDER_MAIN, 17);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Shadowmourne", GOSSIP_SENDER_MAIN, 18);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Dream", GOSSIP_SENDER_MAIN, 19);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Lightning", GOSSIP_SENDER_MAIN, 20);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Glory", GOSSIP_SENDER_MAIN, 21);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Burning", GOSSIP_SENDER_MAIN, 22);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Flames", GOSSIP_SENDER_MAIN, 23);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Ground", GOSSIP_SENDER_MAIN, 24);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Fire Shield", GOSSIP_SENDER_MAIN, 25);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Saw", GOSSIP_SENDER_MAIN, 26);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Crystal Man", GOSSIP_SENDER_MAIN, 27);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            break;
        case 3:
            RemoveAll(player);
            CloseGossipMenuFor(player);
            break;
        case 4:
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Human Male", GOSSIP_SENDER_MAIN, 28);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Human Female", GOSSIP_SENDER_MAIN, 29);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Gnome Male", GOSSIP_SENDER_MAIN, 30);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Gnome Female", GOSSIP_SENDER_MAIN, 31);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Dwarf Male", GOSSIP_SENDER_MAIN, 32);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Dwarf Female", GOSSIP_SENDER_MAIN, 33);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Night Elf Male", GOSSIP_SENDER_MAIN, 34);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Night Elf Female", GOSSIP_SENDER_MAIN, 35);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Draenei Male", GOSSIP_SENDER_MAIN, 36);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Draenei Female", GOSSIP_SENDER_MAIN, 37);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Worgen Black", GOSSIP_SENDER_MAIN, 38);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Worgen White", GOSSIP_SENDER_MAIN, 39);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Pandaren", GOSSIP_SENDER_MAIN, 40);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            break;
        case 5:
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Orc Male", GOSSIP_SENDER_MAIN, 41);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Orc Female", GOSSIP_SENDER_MAIN, 42);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Tauren Male", GOSSIP_SENDER_MAIN, 43);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Tauren Female", GOSSIP_SENDER_MAIN, 44);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Undead Male", GOSSIP_SENDER_MAIN, 45);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Undead Female", GOSSIP_SENDER_MAIN, 46);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Troll Male", GOSSIP_SENDER_MAIN, 47);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Troll Female", GOSSIP_SENDER_MAIN, 48);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Blood Elf Male", GOSSIP_SENDER_MAIN, 49);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Blood Elf Female", GOSSIP_SENDER_MAIN, 50);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Goblin Male", GOSSIP_SENDER_MAIN, 51);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Goblin Female", GOSSIP_SENDER_MAIN, 52);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Pandaren", GOSSIP_SENDER_MAIN, 53);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            break;
        case 6:
            if (player->GetTeam() == ALLIANCE)
                SetAura(player, auras[0]);
            else
                SetAura(player, auras[1]);
            CloseGossipMenuFor(player);
            break;
        case 7:
            SetAura(player, auras[2]);
            CloseGossipMenuFor(player);
            break;
        case 8:
            SetAura(player, auras[3]);
            CloseGossipMenuFor(player);
            break;
        case 9:
            SetAura(player, auras[4]);
            CloseGossipMenuFor(player);
            break;
        case 10:
            SetAura(player, auras[5]);
            CloseGossipMenuFor(player);
            break;
        case 11:
            SetAura(player, auras[6]);
            CloseGossipMenuFor(player);
            break;
        case 12:
            SetAura(player, auras[7]);
            CloseGossipMenuFor(player);
            break;
        case 13:
            SetAura(player, auras[8]);
            CloseGossipMenuFor(player);
            break;
        case 14:
            SetAura(player, auras[9]);
            CloseGossipMenuFor(player);
            break;
        case 15:
            SetAura(player, auras[10]);
            CloseGossipMenuFor(player);
            break;
        case 16:
            SetAura(player, auras[11]);
            CloseGossipMenuFor(player);
            break;
        case 17:
            SetAura(player, auras[12]);
            CloseGossipMenuFor(player);
            break;
        case 18:
            SetAura(player, auras[13]);
            CloseGossipMenuFor(player);
            break;
        case 19:
            SetAura(player, auras[14]);
            CloseGossipMenuFor(player);
            break;
        case 20:
            SetAura(player, auras[15]);
            CloseGossipMenuFor(player);
            break;
        case 21:
            SetAura(player, auras[16]);
            CloseGossipMenuFor(player);
            break;
        case 22:
            SetAura(player, auras[17]);
            CloseGossipMenuFor(player);
            break;
        case 23:
            SetAura(player, auras[18]);
            CloseGossipMenuFor(player);
            break;
        case 24:
            SetAura(player, auras[19]);
            CloseGossipMenuFor(player);
            break;
        case 25:
            SetAura(player, auras[20]);
            CloseGossipMenuFor(player);
            break;
        case 26:
            SetAura(player, auras[21]);
            CloseGossipMenuFor(player);
            break;
        case 27:
            SetAura(player, auras[22]);
            CloseGossipMenuFor(player);
            break;
        case 28:
            SetMorph(player, 18801, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 29:
            SetMorph(player, 18800, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 30:
            SetMorph(player, 18799, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 31:
            SetMorph(player, 18798, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 32:
            SetMorph(player, 18797, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 33:
            SetMorph(player, 18796, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 34:
            SetMorph(player, 18803, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 35:
            SetMorph(player, 18802, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 36:
            SetMorph(player, 18795, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 37:
            SetMorph(player, 18794, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 38:
            SetMorph(player, 522, 0.8f);
            CloseGossipMenuFor(player);
            break;
        case 39:
            SetMorph(player, 574, 0.8f);
            CloseGossipMenuFor(player);
            break;
        case 40:
            SetMorph(player, 30414, 2.3f);
            CloseGossipMenuFor(player);
            break;
        case 41:
            SetMorph(player, 18805, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 42:
            SetMorph(player, 18804, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 43:
            SetMorph(player, 18807, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 44:
            SetMorph(player, 18806, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 45:
            SetMorph(player, 18811, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 46:
            SetMorph(player, 18810, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 47:
            SetMorph(player, 18809, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 48:
            SetMorph(player, 18808, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 49:
            SetMorph(player, 18793, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 50:
            SetMorph(player, 18785, 1.0f);
            CloseGossipMenuFor(player);
            break;
        case 51:
            SetMorph(player, 20582, 1.2f);
            CloseGossipMenuFor(player);
            break;
        case 52:
            SetMorph(player, 20583, 1.2f);
            CloseGossipMenuFor(player);
            break;
        case 53:
            SetMorph(player, 30414, 2.3f);
            CloseGossipMenuFor(player);
            break;
        }
        return true;
    }
};

void AddSC_NPC_Funny()
{
    new NPC_Funny();
}