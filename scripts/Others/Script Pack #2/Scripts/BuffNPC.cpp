#include "ScriptPCH.h"
     
enum spells
{
        POWER_WORD_FORTITUDE = 48162,
        PRAYER_OF_SPRITE = 48074,
        SHADOW_BUFF = 48170,
        KINGS_BUFF = 43223,
        ARCANE_BUFF = 36880,
        MARK_OF_THE_WILD = 48469
};
     
class buff_npc : public CreatureScript
{
        public:
                buff_npc() : CreatureScript("buff_npc"){}
     
                bool OnGossipHello(Player * pPlayer, Creature * pCreature)
                {
                        pPlayer->ADD_GOSSIP_ITEM(4, "Buff me!", GOSSIP_SENDER_MAIN, 1);
                                                pPlayer->ADD_GOSSIP_ITEM(4, "Never mind", GOSSIP_SENDER_MAIN, 100);
                        pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
                                                                       
                        return true;
                }
     
                bool OnGossipSelect(Player * pPlayer, Creature * pCreature, uint32 /*uiSender*/, uint32 uiAction)
                {
                                        pPlayer->PlayerTalkClass->ClearMenus();
                                       
                                            switch(pPlayer->getClass())
                        {
                                case CLASS_WARRIOR:
                                                                        {
                                        pPlayer->CastSpell(pPlayer, POWER_WORD_FORTITUDE, true);
                                                                                pPlayer->CastSpell(pPlayer, KINGS_BUFF, true);
                                                                                pPlayer->CastSpell(pPlayer, MARK_OF_THE_WILD, true);
                                                                                pPlayer->CastSpell(pPlayer, PRAYER_OF_SPRITE, true);
                                                                                pPlayer->CastSpell(pPlayer, SHADOW_BUFF, true);
                                        pCreature->MonsterWhisper("You are now buffed!", pPlayer->GetGUID(), true);
                                                                        }break;
 
                                                                case CLASS_PALADIN:
                                                                        {
                                                                                 pPlayer->CastSpell(pPlayer, POWER_WORD_FORTITUDE, true);
                                                                                 pPlayer->CastSpell(pPlayer, KINGS_BUFF, true);
                                                                                 pPlayer->CastSpell(pPlayer, MARK_OF_THE_WILD, true);
                                                                                 pPlayer->CastSpell(pPlayer, PRAYER_OF_SPRITE, true);
                                                                                 pPlayer->CastSpell(pPlayer, ARCANE_BUFF, true);
                                                                                 pPlayer->CastSpell(pPlayer, SHADOW_BUFF, true);
                                                                                 pCreature->MonsterWhisper("You are now buffed!", pPlayer->GetGUID(), true);
                                                                        }break;
 
                                                                case CLASS_HUNTER:
                                                                                {
                                                                                         pPlayer->CastSpell(pPlayer, POWER_WORD_FORTITUDE, true);
                                                                                         pPlayer->CastSpell(pPlayer, KINGS_BUFF, true);
                                                                                         pPlayer->CastSpell(pPlayer, MARK_OF_THE_WILD, true);
                                                                                         pPlayer->CastSpell(pPlayer, PRAYER_OF_SPRITE, true);
                                                                                         pPlayer->CastSpell(pPlayer, ARCANE_BUFF, true);
                                                                                         pPlayer->CastSpell(pPlayer, SHADOW_BUFF, true);
                                                                                         pCreature->MonsterWhisper("You are now buffed!", pPlayer->GetGUID(), true);
                                                                                }break;
 
                                                                case CLASS_ROGUE:
                                                                        {
                                                                                 pPlayer->CastSpell(pPlayer, POWER_WORD_FORTITUDE, true);
                                                                                 pPlayer->CastSpell(pPlayer, KINGS_BUFF, true);
                                                                                 pPlayer->CastSpell(pPlayer, MARK_OF_THE_WILD, true);
                                                                                 pPlayer->CastSpell(pPlayer, PRAYER_OF_SPRITE, true);
                                                                                 pPlayer->CastSpell(pPlayer, SHADOW_BUFF, true);
                                                                                 pCreature->MonsterWhisper("You are now buffed!", pPlayer->GetGUID(), true);
                                                                        }break;
 
                                                                case CLASS_PRIEST:
                                                                        {
                                                                                 pPlayer->CastSpell(pPlayer, POWER_WORD_FORTITUDE, true);
                                                                                 pPlayer->CastSpell(pPlayer, KINGS_BUFF, true);
                                                                                 pPlayer->CastSpell(pPlayer, MARK_OF_THE_WILD, true);
                                                                                 pPlayer->CastSpell(pPlayer, PRAYER_OF_SPRITE, true);
                                                                                 pPlayer->CastSpell(pPlayer, ARCANE_BUFF, true);
                                                                                 pPlayer->CastSpell(pPlayer, SHADOW_BUFF, true);
                                                                                 pCreature->MonsterWhisper("You are now buffed!", pPlayer->GetGUID(), true);
                                                                        }break;
 
                                                                case CLASS_DEATH_KNIGHT:
                                                                        {
                                                                                 pPlayer->CastSpell(pPlayer, POWER_WORD_FORTITUDE, true);
                                                                                 pPlayer->CastSpell(pPlayer, KINGS_BUFF, true);
                                                                                 pPlayer->CastSpell(pPlayer, MARK_OF_THE_WILD, true);
                                                                                 pPlayer->CastSpell(pPlayer, PRAYER_OF_SPRITE, true);
                                                                                 pPlayer->CastSpell(pPlayer, SHADOW_BUFF, true);
                                                                                 pCreature->MonsterWhisper("You are now buffed!", pPlayer->GetGUID(), true);
                                                                        }break;
 
                                                                case CLASS_SHAMAN:
                                                                        {
                                                                                 pPlayer->CastSpell(pPlayer, POWER_WORD_FORTITUDE, true);
                                                                                 pPlayer->CastSpell(pPlayer, KINGS_BUFF, true);
                                                                                 pPlayer->CastSpell(pPlayer, MARK_OF_THE_WILD, true);
                                                                                 pPlayer->CastSpell(pPlayer, PRAYER_OF_SPRITE, true);
                                                                                 pPlayer->CastSpell(pPlayer, ARCANE_BUFF, true);
                                                                                 pPlayer->CastSpell(pPlayer, SHADOW_BUFF, true);
                                                                                 pCreature->MonsterWhisper("You are now buffed!", pPlayer->GetGUID(), true);
                                                                        }break;
 
                                                                case CLASS_MAGE:
                                                                        {
                                                                                 pPlayer->CastSpell(pPlayer, POWER_WORD_FORTITUDE, true);
                                                                                 pPlayer->CastSpell(pPlayer, KINGS_BUFF, true);
                                                                                 pPlayer->CastSpell(pPlayer, MARK_OF_THE_WILD, true);
                                                                                 pPlayer->CastSpell(pPlayer, PRAYER_OF_SPRITE, true);
                                                                                 pPlayer->CastSpell(pPlayer, ARCANE_BUFF, true);
                                                                                 pPlayer->CastSpell(pPlayer, SHADOW_BUFF, true);
                                                                                 pCreature->MonsterWhisper("You are now buffed!", pPlayer->GetGUID(), true);
                                                                        }break;
 
                                                                case CLASS_WARLOCK:
                                                                        {
                                                                                 pPlayer->CastSpell(pPlayer, POWER_WORD_FORTITUDE, true);
                                                                                 pPlayer->CastSpell(pPlayer, KINGS_BUFF, true);
                                                                                 pPlayer->CastSpell(pPlayer, MARK_OF_THE_WILD, true);
                                                                                 pPlayer->CastSpell(pPlayer, PRAYER_OF_SPRITE, true);
                                                                                 pPlayer->CastSpell(pPlayer, ARCANE_BUFF, true);
                                                                                 pPlayer->CastSpell(pPlayer, SHADOW_BUFF, true);
                                                                                 pCreature->MonsterWhisper("You are now buffed!", pPlayer->GetGUID(), true);
                                                                        }break;
 
                                                                case CLASS_DRUID:
                                                                        {
                                                                                 pPlayer->CastSpell(pPlayer, POWER_WORD_FORTITUDE, true);
                                                                                 pPlayer->CastSpell(pPlayer, KINGS_BUFF, true);
                                                                                 pPlayer->CastSpell(pPlayer, MARK_OF_THE_WILD, true);
                                                                                 pPlayer->CastSpell(pPlayer, PRAYER_OF_SPRITE, true);
                                                                                 pPlayer->CastSpell(pPlayer, ARCANE_BUFF, true);
                                                                                 pPlayer->CastSpell(pPlayer, SHADOW_BUFF, true);
                                                                                 pCreature->MonsterWhisper("You are now buffed!", pPlayer->GetGUID(), true);
                                                                        }break;
 
                                                                case 100:
                                                                {
                                                                                pPlayer->CLOSE_GOSSIP_MENU();
                                                                }break;
                                     
                                                }
                        return true;
                }
};
     
void AddSC_buff_npc()
{
        new buff_npc();
}
