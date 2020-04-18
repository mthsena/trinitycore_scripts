#include "ScriptPCH.h"
#include <cstring>

#define SET_CURRENCY 0  //0 for gold, 1 for honor, 2 for tokens

#if SET_CURRENCY == 0
#define BOUNTY_1 "I would like to place a 20g bounty."
#define BOUNTY_2 "I would like to place a 40g bounty."
#define BOUNTY_3 "I would like to place a 100g bounty."
#define BOUNTY_4 "I would like to place a 200g bounty."
#endif

#if SET_CURRENCY == 1
#define BOUNTY_1 "I would like to place a 20 honor bounty."
#define BOUNTY_2 "I would like to place a 40 honor bounty."
#define BOUNTY_3 "I would like to place a 100 honor bounty."
#define BOUNTY_4 "I would like to place a 200 honor bounty."
#endif

#define PLACE_BOUNTY "I would like to place a bounty."
#define LIST_BOUNTY "List the current bounties."
#define NVM "Nevermind"
#define WIPE_BOUNTY "Wipe bounties"

enum BountyPrice
{
	BOUNTY_PRICE_1 = 1,
	BOUNTY_PRICE_2 = 3,
	BOUNTY_PRICE_3 = 5,
	BOUNTY_PRICE_4 = 10,
};

bool passChecks(Player * pPlayer, const char * name)
{ 

	Player * pBounty = sObjectAccessor->FindPlayerByName(name);
	WorldSession * m_session = pPlayer->GetSession();
	if(!pBounty)
	{
		m_session->SendNotification("The player is offline or doesn't exist!");
		return false;
	}
	QueryResult result = CharacterDatabase.PQuery("SELECT * FROM bounties WHERE guid ='%u'", pBounty->GetGUID());
	if(result)
	{
		m_session->SendNotification("This player already has a bounty on them!");
		return false;
	}
	if(pPlayer->GetGUID() == pBounty->GetGUID())
	{
		m_session->SendNotification("You cannot set a bounty on yourself!");
		return false;
	}
	return true;
}

void alertServer(const char * name, int msg)
{
	std::string message;
	if(msg == 1)
	{
		message = "A bounty has been placed on |cffffffff";
		message += name;
		message += "|. Kill the target immediately to collect the reward!";
	}
	else if(msg == 2)
	{
		message = "The bounty on |cffffffff";
		message += name;
		message += "| has been collected!";
	}
	sWorld->SendServerMessage(SERVER_MSG_STRING, message.c_str(), 0);
}


bool hasCurrency(Player * pPlayer, uint32 required, int currency)
{
	WorldSession *m_session = pPlayer->GetSession();
	switch(currency)
	{
		case 0: //gold
			{
			uint32 currentmoney = pPlayer->GetMoney();
			uint32 requiredmoney = (required * 10000);
			if(currentmoney < requiredmoney)
			{
				m_session->SendNotification("You don't have enough gold!");
				return false;
			}
			pPlayer->SetMoney(currentmoney - requiredmoney);
			break;
			}
		case 1: //honor
			{
			uint32 currenthonor = pPlayer->GetHonorPoints();
			if(currenthonor < required)
			{
				m_session->SendNotification("You don't have enough honor!");
				return false;
			}
			pPlayer->SetHonorPoints(currenthonor - required);
			break;
			}
	}
	return true;
}

void flagPlayer(const char * name)
{
	Player * pBounty = sObjectAccessor->FindPlayerByName(name);
	pBounty->SetPvP(true);
	pBounty->SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
}

class BountyHunter : public CreatureScript
{
	public:
		BountyHunter() : CreatureScript("BountyHunter"){}
		bool OnGossipHello(Player * Player, Creature * Creature)
		{
			Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, PLACE_BOUNTY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
			Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, LIST_BOUNTY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
			Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, NVM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
			if ( Player->isGameMaster() )
			{
				Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, WIPE_BOUNTY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
			}

			Player->PlayerTalkClass->SendGossipMenu(907, Creature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
		{
			pPlayer->PlayerTalkClass->ClearMenus();
			switch(uiAction)
			{
				case GOSSIP_ACTION_INFO_DEF+1:
				{
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, BOUNTY_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5, "", 0, true);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, BOUNTY_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6, "", 0, true);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, BOUNTY_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7, "", 0, true);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, BOUNTY_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8, "", 0, true);
					pPlayer->PlayerTalkClass->SendGossipMenu(365, pCreature->GetGUID());
					break;
				}
				case GOSSIP_ACTION_INFO_DEF+2:
				{
					QueryResult Bounties = CharacterDatabase.PQuery("SELECT * FROM bounties");
					
					if(!Bounties)
					{
						pPlayer->PlayerTalkClass->SendCloseGossip();
						return false;
					}
#if SET_CURRENCY == 0
					if(	Bounties->GetRowCount() > 1)
					{
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Bounties: ", GOSSIP_SENDER_MAIN, 1);
						do
						{
							Field * fields = Bounties->Fetch();
							std::string option;
							QueryResult name = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid='%u'", fields[0].GetUInt64());
							Field * names = name->Fetch();
							option = names[0].GetString();
							option +=" ";
							option += fields[1].GetString();
							option += " gold";
							pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, option, GOSSIP_SENDER_MAIN, 1);
						}while(Bounties->NextRow());
					}
					else
					{
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Bounties: ", GOSSIP_SENDER_MAIN, 1);
						Field * fields = Bounties->Fetch();
						std::string option;
						QueryResult name = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid='%u'", fields[0].GetUInt64());
						Field * names = name->Fetch();
						option = names[0].GetString();
						option +=" ";
						option += fields[1].GetString();
						option += " gold";
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, option, GOSSIP_SENDER_MAIN, 1);
						
					}
#endif
#if SET_CURRENCY == 1
					if(	Bounties->GetRowCount() > 1)
					{
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Bounties: ", GOSSIP_SENDER_MAIN, 1);
						do
						{
							Field * fields = Bounties->Fetch();
							std::string option;
							QueryResult name = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid='%u'", fields[0].GetUInt64());
							Field * names = name->Fetch();
							option = names[0].GetString();
							option +=" ";
							option += fields[1].GetString();
							option += " honor";
							pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, option, GOSSIP_SENDER_MAIN, 1);
						}while(Bounties->NextRow());
					}
					else
					{
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Bounties: ", GOSSIP_SENDER_MAIN, 1);
						Field * fields = Bounties->Fetch();
						std::string option;
						QueryResult name = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid='%u'", fields[0].GetUInt64());
						Field * names = name->Fetch();
						option = names[0].GetString();
						option +=" ";
						option += fields[1].GetString();
						option += " honor";
						pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, option, GOSSIP_SENDER_MAIN, 1);
						
					}
#endif
					pPlayer->PlayerTalkClass->SendGossipMenu(878, pCreature->GetGUID());
					break;
				}
				case GOSSIP_ACTION_INFO_DEF+3:
				{
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				}
				case GOSSIP_ACTION_INFO_DEF+4:
				{
					CharacterDatabase.PExecute("TRUNCATE TABLE bounties");
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				}
			}
			return true;
		}

		bool OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction, const char * code)
		{
			pPlayer->PlayerTalkClass->ClearMenus();
			if ( uiSender == GOSSIP_SENDER_MAIN )
			{
				if(islower(code[0]))
					toupper(code[0]);

				if(passChecks(pPlayer, code))
				{
					Player * pBounty = sObjectAccessor->FindPlayerByName(code);
					switch (uiAction)
					{
						case GOSSIP_ACTION_INFO_DEF+5:
						{
							if(hasCurrency(pPlayer, BOUNTY_PRICE_1, SET_CURRENCY))
							{
								CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u','1', '1')", pBounty->GetGUID());
								alertServer(code, 1);
								flagPlayer(code);
								pPlayer->PlayerTalkClass->SendCloseGossip();
							}
							break;
						}
							
						case GOSSIP_ACTION_INFO_DEF+6:
						{
							if(hasCurrency(pPlayer, BOUNTY_PRICE_2, SET_CURRENCY))
							{
								CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '3', '2')", pBounty->GetGUID());
								alertServer(code, 1);
								flagPlayer(code);
								pPlayer->PlayerTalkClass->SendCloseGossip();
							}
							break;
						}
						case GOSSIP_ACTION_INFO_DEF+7:
						{
							if(hasCurrency(pPlayer, BOUNTY_PRICE_3, SET_CURRENCY))
							{
								CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '5', '3')", pBounty->GetGUID());
								alertServer(code, 1);
								flagPlayer(code);
								pPlayer->PlayerTalkClass->SendCloseGossip();
							}
							break;
						}
						case GOSSIP_ACTION_INFO_DEF+8:
						{
							if(hasCurrency(pPlayer, BOUNTY_PRICE_4, SET_CURRENCY))
							{
								CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '10', '3')", pBounty->GetGUID());
								alertServer(code, 1);
								flagPlayer(code);
								pPlayer->PlayerTalkClass->SendCloseGossip();
							}
							break;
						}

					}
				}
				else
				{
					pPlayer->PlayerTalkClass->SendCloseGossip();
				}
			}
			return true;
		}
};


class BountyKills : public PlayerScript
{
	public:
		BountyKills() : PlayerScript("BountyKills"){}

		void OnPVPKill(Player * Killer, Player * Bounty)
		{
			if(Killer->GetGUID() == Bounty->GetGUID())
				return;

			QueryResult result = CharacterDatabase.PQuery("SELECT * FROM bounties WHERE guid='%u'", Bounty->GetGUID());
			if(!result)
				return;

			Field * fields = result->Fetch();
#if SET_CURRENCY == 0
			switch(fields[2].GetUInt64())
			{
			case 1:
				Killer->SetMoney(Killer->GetMoney() + (BOUNTY_PRICE_1 * 10000));
				break;
			case 2:
				Killer->SetMoney(Killer->GetMoney() + (BOUNTY_PRICE_2 * 10000));
				break;
			case 3:
				Killer->SetMoney(Killer->GetMoney() + (BOUNTY_PRICE_3 * 10000));
				break;
			case 4:
				Killer->SetMoney(Killer->GetMoney() + (BOUNTY_PRICE_4 * 10000));
				break;
			}
#endif
#if SET_CURRENCY == 1
			switch(fields[2].GetUInt64())
			{
			case 1:
				Killer->SetHonorPoints(Killer->GetHonorPoints() + (BOUNTY_PRICE_1));
				break;
			case 2:
				Killer->SetHonorPoints(Killer->GetHonorPoints() + (BOUNTY_PRICE_2));
				break;
			case 3:
				Killer->SetHonorPoints(Killer->GetHonorPoints() + (BOUNTY_PRICE_3));
				break;
			case 4:
				Killer->SetHonorPoints(Killer->GetHonorPoints()) + (BOUNTY_PRICE_4));
				break;
			}
#endif

			CharacterDatabase.PExecute("DELETE FROM bounties WHERE guid='%u'", Bounty->GetGUID());
			alertServer(Bounty->GetName().c_str(), 2);

		}
};

void AddSC_BountyHunter()
{
	new BountyHunter();
	new BountyKills();
}