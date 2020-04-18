/*script made by: SymbolixDEV
Complete : 50%
*/
class donate_npc : public CreatureScript
{
        public:
                donate_npc() : CreatureScript("donate_npc"){ }
     
                bool OnGossipHello(Player * pPlayer, Creature * pCreature)
                {
                        pPlayer->ADD_GOSSIP_ITEM(4, "What is donate ?!", GOSSIP_SENDER_MAIN, 1);
                                                pPlayer->ADD_GOSSIP_ITEM(4, "Close me! ", GOSSIP_SENDER_MAIN, 100);
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
				pCreature->MonsterWhisper("Text Here for information!", pPlayer->GetGUID(), true);
				        if (pPlayer->HasItemCount(23131, 25, true)) // donate reward
                     	{
                        		pPlayer->DestroyItemCount(23131, 25, true); // change 23131 with you custom Donate Reward Item !
                         		pPlayer->AddItem(12302,1); // Change This for Donate Reward (12302 is item id ,1 Is item count)
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
			}break;
 
                        case CLASS_PALADIN:
			{
				pCreature->MonsterWhisper("Text Here for information!", pPlayer->GetGUID(), true);
				        if (pPlayer->HasItemCount(23131, 25, true)) // donate reward
                     	{
                        		pPlayer->DestroyItemCount(23131, 25, true); // change 23131 with you custom Donate Reward Item !
                         		pPlayer->AddItem(12302,1); // Change This for Donate Reward (12302 is item id ,1 Is item count)
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
			}break;
 
                        case CLASS_HUNTER:
			{
				pCreature->MonsterWhisper("Text Here for information!", pPlayer->GetGUID(), true);
				        if (pPlayer->HasItemCount(23131, 25, true)) // donate reward
                     	{
                        		pPlayer->DestroyItemCount(23131, 25, true); // change 23131 with you custom Donate Reward Item !
                         		pPlayer->AddItem(12302,1); // Change This for Donate Reward (12302 is item id ,1 Is item count)
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
			}break;
			
                        case CLASS_ROGUE:
			{
				pCreature->MonsterWhisper("Text Here for information!", pPlayer->GetGUID(), true);
				        if (pPlayer->HasItemCount(23131, 25, true)) // donate reward
                     	{
                        		pPlayer->DestroyItemCount(23131, 25, true); // change 23131 with you custom Donate Reward Item !
                         		pPlayer->AddItem(12302,1); // Change This for Donate Reward (12302 is item id ,1 Is item count)
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
			}break;
 
                        case CLASS_PRIEST:
			{
				pCreature->MonsterWhisper("Text Here for information!", pPlayer->GetGUID(), true);
				        if (pPlayer->HasItemCount(23131, 25, true)) // donate reward
                     	{
                        		pPlayer->DestroyItemCount(23131, 25, true); // change 23131 with you custom Donate Reward Item !
                         		pPlayer->AddItem(12302,1); // Change This for Donate Reward (12302 is item id ,1 Is item count)
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
			}break;
 
                        case CLASS_DEATH_KNIGHT:
			{
				pCreature->MonsterWhisper("Text Here for information!", pPlayer->GetGUID(), true);
				        if (pPlayer->HasItemCount(23131, 25, true)) // donate reward
                     	{
                        		pPlayer->DestroyItemCount(23131, 25, true); // change 23131 with you custom Donate Reward Item !
                         		pPlayer->AddItem(12302,1); // Change This for Donate Reward (12302 is item id ,1 Is item count)
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
			}break;
 
			case CLASS_SHAMAN:
			{
				pCreature->MonsterWhisper("Text Here for information!", pPlayer->GetGUID(), true);
				        if (pPlayer->HasItemCount(23131, 25, true)) // donate reward
                     	{
                        		pPlayer->DestroyItemCount(23131, 25, true); // change 23131 with you custom Donate Reward Item !
                         		pPlayer->AddItem(12302,1); // Change This for Donate Reward (12302 is item id ,1 Is item count)
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
			}break;
 
                        case CLASS_MAGE:
			{
				pCreature->MonsterWhisper("Text Here for information!", pPlayer->GetGUID(), true);
				        if (pPlayer->HasItemCount(23131, 25, true)) // donate reward
                     	{
                        		pPlayer->DestroyItemCount(23131, 25, true); // change 23131 with you custom Donate Reward Item !
                         		pPlayer->AddItem(12302,1); // Change This for Donate Reward (12302 is item id ,1 Is item count)
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
			}break;
			
                        case CLASS_WARLOCK:
			{
				pCreature->MonsterWhisper("Text Here for information!", pPlayer->GetGUID(), true);
				        if (pPlayer->HasItemCount(23131, 25, true)) // donate reward
                     	{
                        		pPlayer->DestroyItemCount(23131, 25, true); // change 23131 with you custom Donate Reward Item !
                         		pPlayer->AddItem(12302,1); // Change This for Donate Reward (12302 is item id ,1 Is item count)
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
			}break;
 
                        case CLASS_DRUID:
			{
				pCreature->MonsterWhisper("Text Here for information!", pPlayer->GetGUID(), true);
				        if (pPlayer->HasItemCount(23131, 25, true)) // donate reward
                     	{
                        		pPlayer->DestroyItemCount(23131, 25, true); // change 23131 with you custom Donate Reward Item !
                         		pPlayer->AddItem(12302,1); // Change This for Donate Reward (12302 is item id ,1 Is item count)
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
                         		pPlayer->AddItem(12302,1);
			}break;
			
                        case 100:
                        {
                                pPlayer->CLOSE_GOSSIP_MENU();
                        }break;
                                     
                    }
       return true;
};
     
void AddSC_donate_npc()
{
        new donate_npc();
}
