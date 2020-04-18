/*
  _____                        ____               
 |  ___| __ ___ _______ _ __  / ___|___  _ __ ___ 
 | |_ | '__/ _ \_  / _ \ '_ \| |   / _ \| '__/ _ \
 |  _|| | | (_) / /  __/ | | | |__| (_) | | |  __/
 |_|  |_|  \___/___\___|_| |_|\____\___/|_|  \___|
	 Lightning speed and strength
		 conjured directly from the depths of logic!   
			Infusion-WoW 2011 - 2012 (C)
<--------------------------------------------------------------------------->
 - Developer(s): Styler
 - Complete: 100%
 - ScriptName: 'npc_support' 
 - Comment: N/A
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"
#include <cstring>

class npc_support : public CreatureScript
{
    public:
        npc_support() : CreatureScript("npc_support") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "1. Ich kann eine Klassenquest nicht abschliessen.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "2. Ich kann eine Nordend Rufquest nicht abschliessen.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "3. Ich kann eine Normale Quest nicht abschliessen.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "4. Ich habe Probleme nach dem Fraktionswechsel.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "5. Ich sehe den SucheNachGruppe Channel nicht.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "6. Ich habe eine Frage wegen dem Spenden.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "7. Ich habe das falsche Item gespendet.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "8. Wann werden ArenaPunkte verteilt ?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "9. Wann sind Wartungsarbeiten?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "10. Wann sind die Supportzeiten?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+10);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "11. Nach einem Serverdown fehlen mir Items.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+11);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "12. Nach einem Sertverdown funktioniert eine Quest nichtmehr.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+12);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "13. Ein Spieler hat mich beleidigt.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+13);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "14. Eine Instanz geht nicht und wir oder ich komme nicht weiter.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+14);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "15. Ich habe eine Frage die hier nirgends steht.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+15);
				player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            return true;
		};

		bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
		{
            player->PlayerTalkClass->ClearMenus();
            player->CLOSE_GOSSIP_MENU();
        switch (action)
            {
		    
			case GOSSIP_ACTION_INFO_DEF+1:
					creature->MonsterWhisper("Wenn es sich um eine Klassenquest handelt bitte folgendes machen", player->GetGUID());
					creature->MonsterWhisper("Den Fehler unter bugtracker.privat-wow-server.de eintragen und ein Ticket eröffnen.", player->GetGUID());
	                player->CLOSE_GOSSIP_MENU();
	           break;
			case GOSSIP_ACTION_INFO_DEF+2:
					creature->MonsterWhisper("Wenn es sich um eine Nordend Rufquest handelt bitte folgendes machen", player->GetGUID());
					creature->MonsterWhisper("Den Fehler unter bugtracker.privat-wow-server.de eintragen und ein Ticket eröffnen. Bitte genau schreiben z.B Söhne Hodir etc. ", player->GetGUID());
	                player->CLOSE_GOSSIP_MENU();
	           break;
			case GOSSIP_ACTION_INFO_DEF+3:
					creature->MonsterWhisper("Wenn es sich um eine Normale Quest handelt bitte folgendes machen", player->GetGUID());
					creature->MonsterWhisper("Den Fehler unter bugtracker.privat-wow-server.de eintragen und auf den fixx der Quest warten. Bitte eine diese Quest auslassen und eine neue beginnen. Bitte kein Ticket eröffnen.", player->GetGUID());
	                player->CLOSE_GOSSIP_MENU();
	           break;
			case GOSSIP_ACTION_INFO_DEF+4:
					creature->MonsterWhisper("Wenn du nach einem Fraktionswechsel Probleme hast bitte folgendes machen", player->GetGUID());
					creature->MonsterWhisper("Den Fehler unter bugtracker.privat-wow-server.de eintragen und ein Ticket eröffnen.", player->GetGUID());
	                player->CLOSE_GOSSIP_MENU();
	           break;
			case GOSSIP_ACTION_INFO_DEF+5:
					creature->MonsterWhisper("Wenn du den SucheNachGruppe Channel nicht mehr siehst bitte folgendes machen", player->GetGUID());
					creature->MonsterWhisper("Im Sagen Chat folgendes eingeben /join suchenachgruppe  und den Cache Ordner deines Wow löschen ( WoW muss geschlossen sein ) sollte dies nicht funktionieren bitte ein Ticket eröffnen", player->GetGUID());
	                player->CLOSE_GOSSIP_MENU();
	           break;
			case GOSSIP_ACTION_INFO_DEF+6:
					creature->MonsterWhisper("Bitte besuche diese Homepage spenden.privat-wow-server.de erst wenn du alles dort gelesen hast und dir nicht geholfen werden konnte besuche uns im Teamspeak im SpendenSupport von 16:00 -20:00 Kein TICKET erstellen GameMaster können dir bei Spenden Support nicht helfen.", player->GetGUID());
	                player->CLOSE_GOSSIP_MENU();
	           break;
			case GOSSIP_ACTION_INFO_DEF+7:
					creature->MonsterWhisper("Bitte besuche diese Homepage spenden.privat-wow-server.de erst wenn du alles dort gelesen hast und dir nicht geholfen werden konnte besuche uns im Teamspeak im SpendenSupport von 16:00 -20:00 Kein TICKET erstellen GameMaster können dir bei Spenden Support nicht helfen.", player->GetGUID());
	                player->CLOSE_GOSSIP_MENU();
	           break;
			case GOSSIP_ACTION_INFO_DEF+8:
					creature->MonsterWhisper("Arena Punkte werden Sonntag und Mittwoch um 21:00 verteilt solltest du keine ArenaPunkte bekommen haben bitte bis zum nächsten Zeitpunkt abwarten. Bitte Kein Ticket eröffnen GameMaster können dir da nicht weiterhelfen", player->GetGUID());
	                player->CLOSE_GOSSIP_MENU();
	           break;
			case GOSSIP_ACTION_INFO_DEF+9:
					creature->MonsterWhisper("Wartungsarbeiten sind jeden Mittwoch um 09:00 Es kann aber auch vorkommen das es an anderen Tagen passiert.", player->GetGUID());
	                player->CLOSE_GOSSIP_MENU();
	           break;
			case GOSSIP_ACTION_INFO_DEF+10:
					creature->MonsterWhisper("Unsere Supportzeiten sind von 10:00 - 22:00 am Wochenende bei Bedarf", player->GetGUID());
	                player->CLOSE_GOSSIP_MENU();
	           break;
			case GOSSIP_ACTION_INFO_DEF+11:
					creature->MonsterWhisper("Bitte lese dir unsere Serverregeln durch dort steht alles was du wissen must. Bitte kein Ticket eröffnen ein GameMaster kann dir da nicht weiterhelfen.", player->GetGUID());
	                player->CLOSE_GOSSIP_MENU();
	           break;
			case GOSSIP_ACTION_INFO_DEF+12:
					creature->MonsterWhisper("Bitte eröffne ein Ticket mit deinem genauen Fehler. Welche Quest wieso weshalb warum", player->GetGUID());
	                player->CLOSE_GOSSIP_MENU();
	           break;
			case GOSSIP_ACTION_INFO_DEF+13:
					creature->MonsterWhisper("Wenn dich ein Spieler beleidigt hat setze Ihn auf die Ignorier Liste. Sollte der Spieler nicht aufhören dich zu beleidigen mache einen Screenshot davon und eröffne ein Ticket", player->GetGUID());
	                player->CLOSE_GOSSIP_MENU();
	           break;
			case GOSSIP_ACTION_INFO_DEF+14:
					creature->MonsterWhisper("GameMaster haben in Instanzen nicht zu suchen somit bitte kein Ticket eröffnen. Bitte schreibe dein Problem detailiert in den Bugtracker. bugtracker.privat-wow-server.de", player->GetGUID());
	                player->CLOSE_GOSSIP_MENU();
	           break;
			case GOSSIP_ACTION_INFO_DEF+15:
					creature->MonsterWhisper("Wenn du eine Frage hast die dir sonst nicht beantwortet werden kann, dann eröffne doch bitte ein Ticket.", player->GetGUID());
	                player->CLOSE_GOSSIP_MENU();
	           break;
			}

			player->CLOSE_GOSSIP_MENU();
			return true;
	    }		
};

void AddSC_npc_support()
{
	new npc_support();
}
