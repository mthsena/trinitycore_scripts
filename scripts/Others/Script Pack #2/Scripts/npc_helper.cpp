class npc_helper : public CreatureScript
{
public:
    npc_helper() : CreatureScript("npc_helper") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Магазин", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

        if (player->getPowerType() == POWER_MANA)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Восстановить здоровье и ману", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+36);
        else
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Восстановить здоровье", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+36);

        player->SEND_GOSSIP_MENU(68, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                OnGossipHello(player, creature);
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- Назад", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Стартовые сеты", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+103);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Стартовые оффсеты(ПВЕ)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+104);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Стартовые оффсеты(ПВП)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+31);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Оружие", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Самоцветы", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+22);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Символы", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+30);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Полезное", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+42);
                player->SEND_GOSSIP_MENU(68, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+103:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- Назад", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Арена Сезон 7", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Тир 9", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
                player->SEND_GOSSIP_MENU(68, creature->GetGUID());
                break;
			case GOSSIP_ACTION_INFO_DEF+104:
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- Назад", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Пояс/Ботинки/Брасеры", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+32);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Триньки", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+41);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Кольца/Шея", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+33);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Плащи", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+34);
				player->SEND_GOSSIP_MENU(68, creature->GetGUID());
				break;
            case GOSSIP_ACTION_INFO_DEF+5:
                player->GetSession()->sSendListInventory(50001, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+6:
                player->GetSession()->sSendListInventory(50003, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+8:
                player->GetSession()->sSendListInventory(50000, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+9:
                player->GetSession()->sSendListInventory(50002, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+10:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- Назад", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Арбалеты", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Древковое", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+12);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Дробящее", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+13);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Кинжалы", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+14);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Кулачное", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+15);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Луки", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+16);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Мечи", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+17);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Посохи", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+18);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Огнестрельное", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+19);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Топоры", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+20);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Жезлы", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+21);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Щиты", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+35);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "В правую руку", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+37);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Libram/Idol/Totem/Sigils", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+38);
                player->SEND_GOSSIP_MENU(68, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+11:
                player->GetSession()->sSendListInventory(50013, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+12:
                player->GetSession()->sSendListInventory(50008, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+13:
                player->GetSession()->sSendListInventory(50007, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+14:
                player->GetSession()->sSendListInventory(50012, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+15:
                player->GetSession()->sSendListInventory(50011, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+16:
                player->GetSession()->sSendListInventory(50005, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+17:
                player->GetSession()->sSendListInventory(50009, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+18:
                player->GetSession()->sSendListInventory(50010, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+19:
                player->GetSession()->sSendListInventory(50006, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+20:
                player->GetSession()->sSendListInventory(50004, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+21:
                player->GetSession()->sSendListInventory(50014, creature->GetGUID());
                break;
             case GOSSIP_ACTION_INFO_DEF+22:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "<- Назад", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Жёлтые", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+23);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Зелёные", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+24);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Красные", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+25);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Синие", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+26);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Оранжевые", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+27);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Пурпурные", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+29);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Особые", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+28);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Simple/Prismatic", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+39);
                player->SEND_GOSSIP_MENU(68, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+23:
                player->GetSession()->sSendListInventory(50017, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+24:
                player->GetSession()->sSendListInventory(50019, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+25:
                player->GetSession()->sSendListInventory(50015, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+26:
                player->GetSession()->sSendListInventory(50016, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+27:
                player->GetSession()->sSendListInventory(50020, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+28:
                player->GetSession()->sSendListInventory(50021, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+29:
                player->GetSession()->sSendListInventory(50018, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+30:
                switch(player->getClass())
                {
                    case 1:
                        player->GetSession()->sSendListInventory(50022, creature->GetGUID());
                    break;
                    case 2:
                        player->GetSession()->sSendListInventory(50023, creature->GetGUID());
                    break;
                    case 3:
                        player->GetSession()->sSendListInventory(50024, creature->GetGUID());
                    break;
                    case 4:
                        player->GetSession()->sSendListInventory(50025, creature->GetGUID());
                    break;
                    case 5:
                        player->GetSession()->sSendListInventory(50026, creature->GetGUID());
                    break;
                    case 6:
                        player->GetSession()->sSendListInventory(50027, creature->GetGUID());
                    break;
                    case 7:
                        player->GetSession()->sSendListInventory(50028, creature->GetGUID());
                    break;
                    case 8:
                        player->GetSession()->sSendListInventory(50029, creature->GetGUID());
                    break;
                    case 9:
                        player->GetSession()->sSendListInventory(50030, creature->GetGUID());
                    break;
                    case 11:
                        player->GetSession()->sSendListInventory(50031, creature->GetGUID());
                    break;
                }
                break;
            case GOSSIP_ACTION_INFO_DEF+31:
                player->GetSession()->sSendListInventory(50035, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+32:
                player->GetSession()->sSendListInventory(50034, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+33:
                player->GetSession()->sSendListInventory(50033, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+34:
                player->GetSession()->sSendListInventory(50036, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+35:
                player->GetSession()->sSendListInventory(50032, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+36:
                player->CLOSE_GOSSIP_MENU();
                if (player->isInCombat())
                {
                    ChatHandler(player).PSendSysMessage("|cfff4b25eПомошник шепчет:|r |cfffcedbbВы в бою и не можете использовать этот сервис.|r");
                    return true;
                }
                if (player->getPowerType() == POWER_MANA && player->GetHealth() == player->GetMaxHealth() && player->GetPower(POWER_MANA) == player->GetMaxPower(POWER_MANA))
                {
                    ChatHandler(player).PSendSysMessage("|cfff4b25eПомошник шепчет:|r |cfffcedbbВаше здоровье и мана - полные.|r");
                    return true;
                }
                if (player->GetHealth() == player->GetMaxHealth())
                {
                    ChatHandler(player).PSendSysMessage("|cfff4b25eПомошник шепчет:|r |cfffcedbbВаше здоровье - полное.|r");
                    return true;
                }

                creature->CastSpell(player, 24208, true);

                if (player->getPowerType() == POWER_MANA)
                    player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));

                break;
            case GOSSIP_ACTION_INFO_DEF+37:
                player->GetSession()->sSendListInventory(50037, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+38:
                player->GetSession()->sSendListInventory(50038, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+39:
                player->GetSession()->sSendListInventory(50039, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+41:
                player->GetSession()->sSendListInventory(50041, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+42:
                player->GetSession()->sSendListInventory(50042, creature->GetGUID());
                break;
        }

        return true;
    }
};

void AddSC_npc_helper()
{
    new npc_helper;
}
