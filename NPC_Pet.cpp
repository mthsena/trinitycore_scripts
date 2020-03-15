#include "ScriptMgr.h"
#include "Player.h"
#include "Pet.h"
#include "ObjectMgr.h"
#include "ScriptedGossip.h"
#include "Chat.h"

#define DEFAULT_MESSAGE 907

class NPC_Pet : public CreatureScript
{
public:
    NPC_Pet() : CreatureScript("NPC_Pet") { }

    void CreatePet(Player* player, Creature* creature, uint32 entry)
    {
        if (player->GetPet())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Failure! Drop your current pet.");
            CloseGossipMenuFor(player);
            return;
        }

        Creature* creatureTarget = creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY() + 2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);
        if (!creatureTarget)
            return;

        Pet* pet = player->CreateTamedPetFrom(creatureTarget, 0);
        if (!pet)
            return;

        creatureTarget->setDeathState(JUST_DIED);
        creatureTarget->RemoveCorpse();
        creatureTarget->SetHealth(0);                       // just for nice GM-mode view

        pet->SetPower(POWER_HAPPINESS, 1048000);

        pet->SetUInt64Value(UNIT_FIELD_CREATEDBY, player->GetGUID());
        pet->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, player->getFaction());
        pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());

        pet->GetMap()->AddToMap(pet->ToCreature());

        pet->GetCharmInfo()->SetPetNumber(sObjectMgr->GeneratePetNumber(), true);
        if (!pet->InitStatsForLevel(player->getLevel()))
            sLog->outMessage("script.beastmaster", LOG_LEVEL_ERROR, "Fail: no init stats for entry %u", entry);

        pet->UpdateAllStats();

        player->SetMinion(pet, true);

        pet->SavePetToDB(PET_SAVE_AS_CURRENT);
        pet->InitTalentForLevel();
        player->PetSpellInitialize();

        ChatHandler(player->GetSession()).PSendSysMessage("Success! Pet added.");
        CloseGossipMenuFor(player);
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->getClass() != CLASS_HUNTER)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Failure! Your class do not allow pets.");
            CloseGossipMenuFor(player);
            return false;
        }

        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Get a New Pet", GOSSIP_SENDER_MAIN, 30);

        if (player->CanTameExoticPets())
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Get a New Exotic Pet", GOSSIP_SENDER_MAIN, 50);

        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Open Stable", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Food Shop", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_VENDOR);
        SendGossipMenuFor(player, DEFAULT_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        ClearGossipMenuFor(player);

        switch (action)
        {
        case 100:
            OnGossipHello(player, creature);
            break;

        case 150:
            CloseGossipMenuFor(player);
            break;

        case 30:
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Bat.", GOSSIP_SENDER_MAIN, 18);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Bear.", GOSSIP_SENDER_MAIN, 1);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Boar.", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Cat.", GOSSIP_SENDER_MAIN, 4);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Carrion Bird.", GOSSIP_SENDER_MAIN, 5);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Crab.", GOSSIP_SENDER_MAIN, 6);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Crocolisk.", GOSSIP_SENDER_MAIN, 7);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Dragonhawk.", GOSSIP_SENDER_MAIN, 17);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Gorilla.", GOSSIP_SENDER_MAIN, 8);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Hound.", GOSSIP_SENDER_MAIN, 9);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Hyena.", GOSSIP_SENDER_MAIN, 10);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Moth.", GOSSIP_SENDER_MAIN, 11);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Owl.", GOSSIP_SENDER_MAIN, 12);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "Next..", GOSSIP_SENDER_MAIN, 31);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "..Back", GOSSIP_SENDER_MAIN, 100);

            SendGossipMenuFor(player, DEFAULT_MESSAGE, creature->GetGUID());
            break;

        case 31:
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Raptor.", GOSSIP_SENDER_MAIN, 20);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Ravager.", GOSSIP_SENDER_MAIN, 19);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Strider.", GOSSIP_SENDER_MAIN, 13);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Scorpid.", GOSSIP_SENDER_MAIN, 414);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Spider.", GOSSIP_SENDER_MAIN, 16);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Serpent.", GOSSIP_SENDER_MAIN, 21);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Turtle.", GOSSIP_SENDER_MAIN, 15);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Wasp.", GOSSIP_SENDER_MAIN, 93);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "..Back", GOSSIP_SENDER_MAIN, 30);
            SendGossipMenuFor(player, DEFAULT_MESSAGE, creature->GetGUID());
            break;

        case 50:
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Chimaera.", GOSSIP_SENDER_MAIN, 51);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Core Hound.", GOSSIP_SENDER_MAIN, 52);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Devilsaur.", GOSSIP_SENDER_MAIN, 53);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Rhino.", GOSSIP_SENDER_MAIN, 54);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Silithid.", GOSSIP_SENDER_MAIN, 55);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Worm.", GOSSIP_SENDER_MAIN, 56);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Loque'nahak.", GOSSIP_SENDER_MAIN, 57);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Skoll.", GOSSIP_SENDER_MAIN, 58);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Gondria.", GOSSIP_SENDER_MAIN, 59);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "..Back", GOSSIP_SENDER_MAIN, 100);
            SendGossipMenuFor(player, DEFAULT_MESSAGE, creature->GetGUID());
            break;

        case GOSSIP_OPTION_STABLEPET:
            player->GetSession()->SendStablePet(creature->GetGUID());
            break;
        case GOSSIP_OPTION_VENDOR:
            player->GetSession()->SendListInventory(creature->GetGUID());
            break;
        case 51: //chimera
            CreatePet(player, creature, 21879);
            break;
        case 52: //core hound
            CreatePet(player, creature, 21108);
            break;
        case 53: //devilsaur
            CreatePet(player, creature, 20931);
            break;
        case 54: //rhino
            CreatePet(player, creature, 30445);
            break;
        case 55: //silithid
            CreatePet(player, creature, 5460);
            break;
        case 56: //worm
            CreatePet(player, creature, 30148);
            break;
        case 57: //loque'nahak
            CreatePet(player, creature, 32517);
            break;
        case 58: //skoll
            CreatePet(player, creature, 35189);
            break;
        case 59: //gondria
            CreatePet(player, creature, 33776);
            break;
        case 16: //spider
            CreatePet(player, creature, 2349);
            break;
        case 17: //dragonhawk
            CreatePet(player, creature, 27946);
            break;
        case 18: //bat
            CreatePet(player, creature, 28233);
            break;
        case 19: //ravager
            CreatePet(player, creature, 17199);
            break;
        case 20: //raptor
            CreatePet(player, creature, 14821);
            break;
        case 21: //serpent
            CreatePet(player, creature, 28358);
            break;
        case 1: //bear
            CreatePet(player, creature, 29319);
            break;
        case 2: //boar
            CreatePet(player, creature, 29996);
            break;
        case 93: //bug
            CreatePet(player, creature, 28085);
            break;
        case 4: //cat
            CreatePet(player, creature, 28097);
            break;
        case 5: //carrion
            CreatePet(player, creature, 26838);
            break;
        case 6: //crab
            CreatePet(player, creature, 24478);
            break;
        case 7: //crocolisk
            CreatePet(player, creature, 1417);
            break;
        case 8: //gorila
            CreatePet(player, creature, 28213);
            break;
        case 9: //hound
            CreatePet(player, creature, 29452);
            break;
        case 10: //hyena
            CreatePet(player, creature, 13036);
            break;
        case 11: //moth
            CreatePet(player, creature, 27421);
            break;
        case 12: //owl
            CreatePet(player, creature, 23136);
            break;
        case 13: //strider
            CreatePet(player, creature, 22807);
            break;
        case 414: //scorpid
            CreatePet(player, creature, 9698);
            break;
        case 15: //turtle
            CreatePet(player, creature, 25482);
            break;
        }

        return true;
    }
};

void AddSC_NPC_Pet()
{
    new NPC_Pet();
}