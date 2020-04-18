#include "ScriptPCH.h"
#include "Player.h"

const Position allyPositions[1] =
{
    { -13286.6f, 292.655f, 47.9457f, 6.06654f }
};

const Position hordePositions[1] =
{
    { -13286.6f, 292.655f, 47.9457f, 6.06654f }
};

class mob_gurubashi_ressurect : public PlayerScript
{
public:
    mob_gurubashi_ressurect() : PlayerScript("mob_gurubashi_ressurect") {}

    void OnPVPKill(Player*/*Creature* */ killer, Player* killed)
    {
        if (killer->GetAreaId() == 2177) /*&& killed->GetMapId() == 33*/
        {
            if (killed->HasAuraType(SPELL_AURA_SPIRIT_OF_REDEMPTION))
                killed->RemoveAurasByType(SPELL_AURA_MOD_SHAPESHIFT);
            killer->AddItem(43307, 1);//Вещь и ее кол-во.

            killed->KillPlayer();
            killed->ResurrectPlayer(40.0f, true);

            if (Aura * aur = killed->GetAura(15007))
                aur->SetDuration(0.3*MINUTE*IN_MILLISECONDS); // 1 Минута Слабость после воскрешения

            killed->CastSpell(killed, 13874, true);
            if (Aura * aur = killed->GetAura(13874))
                aur->SetDuration(0.3*MINUTE*IN_MILLISECONDS); // 1 Минута Божественный щит

            uint32 rnd = urand(0,1);
            if (killed->GetTeam() == ALLIANCE)
                killed->TeleportTo(0, allyPositions[rnd].GetPositionX(), allyPositions[rnd].GetPositionY(), allyPositions[rnd].GetPositionZ(), allyPositions[rnd].GetOrientation());
            else
                killed->TeleportTo(0, hordePositions[rnd].GetPositionX(), hordePositions[rnd].GetPositionY(), hordePositions[rnd].GetPositionZ(), hordePositions[rnd].GetOrientation());
        }
    }
};

void AddSC_mob_gurubashi_ressurect()
{
    new mob_gurubashi_ressurect();
}