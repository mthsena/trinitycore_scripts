#include "ScriptPCH.h"
using namespace std;

/* Player */
uint64 m_PlayerGUID;
string playerName;
/* Is Active */
bool isBattleActive = false;
bool hasLogged = false;
bool inZone = true;
/* Is Bosses Dead */
int isWaveBossDead = 0;

#define MSG_FIGHT_COMPUTER "I would like to fight!"

enum Events
{
	EVENT_NONE,
	EVENT_CHECK_ACTIVITY, // Check Activity of the battle : if true or false ? can start?
	EVENT_CHECK_WAVES, // Checks the waves so it can move on to the next event, if it is allowed
	EVENT_CHECK_PLAYER,
	EVENT_FIRST_WAVE,
	EVENT_FIRST_WAVE_TREAT,
	EVENT_FIRST_WAVE_ELITE,
	EVENT_SECOND_WAVE,
	EVENT_SECOND_WAVE_TREAT,
	EVENT_SECOND_WAVE_ELITE,
	EVENT_FINAL_WAVE_BOSS,
       EVENT_COMPLETED_WAVES,
};

enum bPhases
{
	/* Final Boss Phases */
	PHASE_START_COMBAT,
	PHASE_END,
};

enum SpellIds
{
	/* First Wave Spells */
	/* Red Blood Guard */
	SPELL_BERSERKER_CHARGE = 38907,
	SPELL_MORTAL_STRIKE = 68783,
	SPELL_DEEP_WOUNDS = 23256,
	/* First Wave Treat Spells */
	SPELL_ROOT_AURA = 40885,
	/* First Wave Elite Spells */
	/* `- Spore Healer */
	SPELL_HEAL_REGROWTH = 48443, //heal+H.O.T.
	SPELL_HEAL_NORMAL = 48378, //heal normal
	SPELL_HEAL_REJUV = 48441, //H.O.T.
	SPELL_HEAL_AURA_HOTS = 38299, // Aura hots
	SPELL_FLASH_HEAL = 48071,
	SPELL_POWER_WORD_SHIELD = 20697, // Absorbs a ton of damage
	SPELL_HEAL_LIFEBLOOM = 67958,
	/* `- Hank the Tank */
	SPELL_BATTLE_STANCE = 2487, //warrior bstance
	SPELL_SHOUT_BUFF = 47436,	//attk pwr self buff
	SPELL_TANK_CHARGE = 11578,	//warrior charge
	SPELL_GROUND_STOMP = 47502, //thunderclap
	SPELL_EXECUTE = 47471,		//normal strike
	SPELL_TANK_STRIKE = 47450,	//normal strike
	SPELL_INCREASE_BLOCK_VALUE = 67515, // Increases block value
	SPELL_SHIELD_BLOCK = 69580, // Blocks attacks
	SPELL_INCREASE_DEFENSE_RATING = 60343, // Increases Defense by 180+
	SPELL_INCREASE_DODGE_RATING = 18062, // Increase dodge by 96
	SPELL_REND = 47465, // Rends the target ~Bleeds
	SPELL_SHIELD_BASH = 47488, // Bashes the target with a shield
	/* Second Wave Spells */
	SPELL_ROGUE_STEALTH = 1784,
	SPELL_ROGUE_CHEAP_SHOT = 1833, //in stealth only
	SPELL_ROGUE_STRIKE = 48660,
	SPELL_ROGUE_FINISHER = 48668,
	SPELL_ROGUE_VANISH = 26889, //idea here is to make the sidekicks(and main?) vanish in/out of the fight
	SPELL_ROGUE_KICK = 27814,
	SPELL_ROGUE_BACKSTAB = 52540,
	SPELL_ROGUE_RUPTURE = 48672,
	SPELL_ROGUE_KIDNEY_SHOT = 41389,
	/* Second Wave Treat Spells */
	SPELL_UNHOLY_BONE_SHIELD = 49222,
	SPELL_UNHOLY_AOE = 49938,
	SPELL_UNHOLY_PLAGUE_STRIKE = 49921,
	SPELL_UNHOLY_STANGULATE = 47476,
	SPELL_UNHOLY_DEATH_STRIKE = 49924,
	SPELL_UNHOLY_ARMY = 42650, // <- should happen with both NPC's simultaneously
	SPELL_ENRAGE = 59707,
	/* Second Wave Elite Spells */
	/*	`- Rider Brutes	*/
	SPELL_RIDERS_LIGHTNING = 59159, // aoe
	SPELL_RIDERS_CHAIN_LIGHTNING = 49269, // aoe
	SPELL_RIDERS_MOONFIRE = 48463,
	SPELL_RIDERS_STORM = 48467, // aoe
	/*	`- Rider Healer	*/
	SPELL_RIDERS_STAM_BUFF = 48161, // fortitude buff
	SPELL_RIDERS_SHIELD = 48066, // absorbs damage
	SPELL_RIDERS_HEALING_BOLT = 66097,
	SPELL_RIDERS_RENEW = 48068,
	SPELL_RIDERS_GREATER_HEAL = 48063,
	/* Final Wave Boss Spells */
	SPELL_DRAGON_FIRE_SHIELD = 57108, //Reduces damage by 95% for 5s
	SPELL_DRAGON_ENGULF = 74562,
	SPELL_DRAGON_BREATH = 74525,
	SPELL_DRAGON_TAIL_WHIP = 74531,
	SPELL_DRAGON_BERSERK = 26662,
	SPELL_DRAGON_CLAW = 74524,
	SPELL_DRAGON_MASSIVE_FLAMESTRIKE = 26558,
	//SPELL_DRAGON_FIREBALL_BARRAGE = 37541,
	/* Others */
	SPELL_TELEPORT_VISUAL = 64446,
	SPELL_VANISH_1 = 1856,
	SPELL_VANISH_2 = 1857,
	SPELL_VANISH_3 = 26889,
};

enum SpawnIds
{
	/* First Wave */
	NPC_RED_BLOOD_GUARD =         88001,
	NPC_RED_BLOOD_GUARD_MINI =    88002,
	NPC_RED_BLOOD_GUARD_MINI2 =   88003,
	NPC_RED_BLOOD_GUARD_MINI3 =   88004,
	/* First Wave Treat */
	NPC_WAVE_SPAWN_TRIGGER =      88500,
	NPC_GARM_WATCHER       =      80050,
	NPC_FRIGID_PROTO_DRAKE =      80051,
	NPC_OSTERKILGR         =      80052,
	NPC_BLIGHT_FALCONER    =      80053,
	NPC_CONVERTED_HERO     =      80054,
	NPC_PORTAL =                  88501,
    /* First Wave Elite */ 					/* NPC : Display ID */
	NPC_HANK_THE_TANK  =		  88011,	// Tank: 27930 Paladin Tank BE
	NPC_FIELD_MEDIC  =			  88012,	// Healer: 17544 Spore thing
	/* Second Wave */
	NPC_ROGUE_INITIATE = 		  88013, // Main rogue: 24918
	NPC_ROGUE_INITIATE_1 =		  88014, // Sidekick(easier to kill): 24919
	NPC_ROGUE_INITIATE_2 = 		  88015, // Sidekick(easier to kill): 24919
	/* Second Wave Treat */
	NPC_THE_UNHOLY = 			  88016, // Main: 25446
	NPC_THE_UNHOLY_TWIN = 		  88017, // Twin: 25496
	NPC_THE_UNHOLY_PET = 		  88018, // Their Pet: 25467 (no spells, normal attacks just to occupy the player) Maybe just SPELL_PET_BITE ?
	/* Second Wave Elite */
	NPC_RIDERS_OFTHE_ICE =	 	  88019, // Main/Healer: 25083
	NPC_RIDERS_OFTHE_ICE_1 =	  88020, // Brute: 25082
	NPC_RIDERS_OFTHE_ICE_2 = 	  88021, // Brute: 25082
	/* Final Wave Boss */
	NPC_DRAGON_BOSS = 			  88022, // Dragon: 25015
	NPC_DRAGON_BOSS_TRIGGER =     88023,
	GOBJECT_DRAGON_BOSS_RUNE =    183036,
};

enum eEnums
{
	ITEM_INTRAVENOUS_HEALING_POTION = 44698, // You can change the items they can heal with here
	DIRE_MAUL_ZONE = 2557,
	DIRE_MAUL_AREA = 357, //3217,
	PVP_END_TOKEN = 19182, // You can easily change this
	SOUND_HORN_WAVE_START = 7054,
	SOUND_WAVE_COMPLETE = 8571,
};

struct DragonMove
{
	uint32 gobject;
	uint32 spellId;
	float x, y, z, o;
};

uint32 spellDisables[] = { SPELL_VANISH_1, SPELL_VANISH_2, SPELL_VANISH_3 };

static Position sTeleOut[] = 
{
	{ -4286.56f, 1330.970f, 161.21f, 0.019994f }
};

static DragonMove sMoveData[] =
{
	{GOBJECT_DRAGON_BOSS_RUNE, SPELL_DRAGON_MASSIVE_FLAMESTRIKE, -3786.241943f, 1096.538452f, 153.903366f, 6.257603f }
};

#define MAX_WAVE_SPAWN_LOCATIONS 20
const uint32 waveList[MAX_WAVE_SPAWN_LOCATIONS] =
{
	   /* First Wave Ids */
	   NPC_RED_BLOOD_GUARD,
	   /* First Wave Treat Ids */
	   NPC_WAVE_SPAWN_TRIGGER, NPC_GARM_WATCHER, NPC_FRIGID_PROTO_DRAKE, NPC_OSTERKILGR, NPC_BLIGHT_FALCONER, NPC_CONVERTED_HERO, NPC_PORTAL,
	   /* First Wave Elite Ids */
	   NPC_HANK_THE_TANK, NPC_FIELD_MEDIC,
	   /* Second Wave Ids */
	   NPC_ROGUE_INITIATE, NPC_ROGUE_INITIATE_1, NPC_ROGUE_INITIATE_2,
	   /* Second Wave Treat Ids */
	   NPC_THE_UNHOLY, NPC_THE_UNHOLY_TWIN, NPC_THE_UNHOLY_PET,
	   /* Second Wave Elite Ids */
	   NPC_RIDERS_OFTHE_ICE, NPC_RIDERS_OFTHE_ICE_1, NPC_RIDERS_OFTHE_ICE_2,
	   /* Final Wave Boss */
	   NPC_DRAGON_BOSS,
};

static Position m_WaveSpawns[] =
{
	/*    X               Y            Z           O      */
	             /* All Waves Spawns */
	{ -3756.859863f, 1097.575317f, 131.969559f, 6.159780f },
	             /* First Wave Treat */
	{ -3754.864258f, 1088.561890f, 131.969437f, 0.468786f }, // Portal 1 Location
	{ -3755.432373f, 1103.325684f, 131.969437f, 5.846407f }  // Portal 2 Location
};

void DoGivePlayerSpells(Player * player)
{
	switch(player->getClass())
	{
		case CLASS_ROGUE:
			for(int i = 0; i < 3; i++)
				if(player->getLevel() >= 24 && !player->HasSpell(spellDisables[i]))
					player->learnSpell(spellDisables[i], true);
			break;
	}
}

void MessageOnWave(Creature * me, uint32 eventId)
{
	stringstream ss;
	switch(eventId)
	{
	   case EVENT_CHECK_ACTIVITY: // Before Wave 1 starts
		   ss << playerName.c_str()
			  << " get ready! Next wave begins in 10 seconds!";
		   break;

	   case EVENT_CHECK_WAVES:
		   {
			   if( isWaveBossDead == 1)
			   {
				   ss << "I can't believe it! "
					  << playerName.c_str()
					  << " has killed the Red Blood Guard! We will see next wave, which is in 25 seconds, gear up!";
			   }
			   else if (isWaveBossDead == 2)
			   {
				   ss << "This is unreal! "
					  << playerName.c_str()
					  << " has dominated the treat wave! Next wave is in 35 seconds! Get ready for a good experience.";
			   }
			   else if (isWaveBossDead == 3)
			   {	
				   ss << "Holy shit! "
					  << playerName.c_str()
					  << " has demolished the elite! Good luck getting through the others... Second wave begins in 25 seconds! You may want to heal...";
			   }
			   else if (isWaveBossDead == 4)
			   {
				   ss << "Excellent! "
					  << playerName.c_str()
					  << " has stricken down the rogues! Well done! Next wave is in 35 seconds, be prepared!";
			   }
			   else if (isWaveBossDead == 5)
			   {
				   ss << "Zing! I can't believe what I'm seeing! "
				      << playerName.c_str()
					  << " has defeated the Unholy Twins, EPIC WIN! Next wave in 40 seconds, get ready!";
			   }
			   else if (isWaveBossDead == 6)
			   {
				   ss << "WOW! No Way! "
				      << playerName.c_str()
					  << " has stopped the riders dead in their tracks. Great job! Final wave beings in 35 seconds, get buffed up!";
			   }
			   else if (isWaveBossDead == 7)
			   {
				   ss << "Just...a moment of silence. "
				      << playerName.c_str()
					  << " has just won this entire challenge! Congratulations!";
			   }
		   }break;

	   case EVENT_FIRST_WAVE:
		   ss << "First wave has begun!"
			  << " From the blood gates of hell, here is," 
			  << " Arena Master, Red Blood Guard!";
		   break;

	   case EVENT_FIRST_WAVE_TREAT:
		   ss << "First treat wave has begun!"
			  << " Bounding across the continent, you will face many challenges!";
		   break;

	   case EVENT_FIRST_WAVE_ELITE:
		   ss << "First elite wave has begun!"
			  << " Say your last words, this elite team wont give you another chance to."
			  << " Entering the arena, Hank the Tank and his heal happy spore companion. Prepare for the worst!";
		   break;
		  
	   case EVENT_SECOND_WAVE:
		   ss << "Second wave has begun!"
			  << " Trust your eyes and dont blink, this team of initiates only provide pain!"
			  << " The quick, the stealthy.. The Rogue Initiates, maybe run?";
		   break;
	   
	   case EVENT_SECOND_WAVE_TREAT:
		  ss << "Second treat wave has begun!"
		     << " From the depths of the underworld, they were sent back here to take care of business!"
			 << " The deadliest duo, the Unholy Twins - Seal your fate, destroy them!";
		   break;
	   
	   case EVENT_SECOND_WAVE_ELITE:
		  ss << "Second elite wave has begun!"
		     << " The Riders of the Ice have entered the arena!"
			 << " Don't be fooled by their size, they will walk all over you. Attack!";
		   break;
		   
	   case EVENT_FINAL_WAVE_BOSS:
		  ss << "From deep into the Earth's core "
		     << " there lies a entirely different aspect of a challenge. "
			 << " Get Ready! Arena Dragon is here!";
		   break;
	}
	me->MonsterYell(ss.str().c_str(), LANG_UNIVERSAL, me->GetGUID());
}

void DoSendCompleteMessage(string who)
{
	stringstream ss;
	ss << who.c_str()
		<< "has completed the Dire Maul Arena Event!"
		<< "The event is now opened and ready for another victim!";
	sWorld->SendGlobalText(ss.str().c_str(), NULL);
}

void AddEndRewards(Player * player, uint32 honoramount, uint32 tokenId, uint32 tokenAmount)
{
	uint32 curHonor = player->GetHonorPoints();
	player->SetHonorPoints(curHonor + honoramount);
	ChatHandler(player).PSendSysMessage("Added %u honor!", honoramount);
	player->AddItem(tokenId, tokenAmount);
}