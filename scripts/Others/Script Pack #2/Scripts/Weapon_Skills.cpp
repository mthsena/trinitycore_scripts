enum SkillSpells
{
	SPELL_BLOCK = 107,
	SPELL_BOWS = 264,
	SPELL_CROSSBOWS = 5011,
	SPELL_DAGGERS = 1180,
	SPELL_DUAL_WIELD = 674,
	SPELL_FIST_WEAPONS = 15590,
	SPELL_GUNS = 266,
	SPELL_MAIL = 8737,
	SPELL_PLATE = 750,
	SPELL_ONE_HANDED_AXES = 196,
	SPELL_ONE_HANDED_MACES = 198,
	SPELL_ONE_HANDED_SWORDS = 201,
	SPELL_TWO_HANDED_AXES = 197,
	SPELL_TWO_HANDED_MACES = 199,
	SPELL_TWO_HANDED_SWORDS = 202,
	SPELL_STAVES = 227,
	SPELL_THROW = 2764,
	SPELL_THROWN = 2567,
	SPELL_POLEARMS = 200,
	SPELL_RELIC = 52665,
	SPELL_RELIC_2 = 27764,
	SPELL_RELIC_3 = 27762,
	SPELL_RELIC_4 = 27763,
	SPELL_SHIELD = 9116,
	SPELL_SHOOT = 3018,
	SPELL_SHOOT_WANDS = 5019,
	SPELL_WANDS = 5009
};

class Weapon_Skills : public PlayerScript
{
    public:
		Weapon_Skills() : PlayerScript("Weapon_Skills") { }

		void OnLogin(Player * player)
		{
			if(player->HasAtLoginFlag(AT_LOGIN_FIRST))
			{
				switch(player->getClass())
				{
				   case CLASS_PALADIN:
					   {
						   player->learnSpell(SPELL_BLOCK, true);
						   player->learnSpell(SPELL_ONE_HANDED_AXES, true);
						   player->learnSpell(SPELL_ONE_HANDED_MACES, true);
						   player->learnSpell(SPELL_ONE_HANDED_SWORDS, true);
						   player->learnSpell(SPELL_PLATE, true);
						   player->learnSpell(SPELL_POLEARMS, true);
						   player->learnSpell(SPELL_RELIC_3, true);
						   player->learnSpell(SPELL_SHIELD, true);
						   player->learnSpell(SPELL_TWO_HANDED_AXES, true);
						   player->learnSpell(SPELL_TWO_HANDED_MACES, true);
						   player->learnSpell(SPELL_TWO_HANDED_SWORDS, true);
					   }break;

				   case CLASS_SHAMAN:
					   {
						   player->learnSpell(SPELL_BLOCK, true);
						   player->learnSpell(SPELL_FIST_WEAPONS, true);
						   player->learnSpell(SPELL_MAIL, true);
						   player->learnSpell(SPELL_ONE_HANDED_AXES, true);
						   player->learnSpell(SPELL_ONE_HANDED_MACES, true);
						   player->learnSpell(SPELL_RELIC_4, true);
						   player->learnSpell(SPELL_SHIELD, true);
						   player->learnSpell(SPELL_STAVES, true);
						   player->learnSpell(SPELL_TWO_HANDED_AXES, true);
						   player->learnSpell(SPELL_TWO_HANDED_MACES, true);
					   }break;

				   case CLASS_WARRIOR:
					   {
						   player->learnSpell(SPELL_BLOCK, true);
						   player->learnSpell(SPELL_BOWS, true);
						   player->learnSpell(SPELL_CROSSBOWS, true);
						   player->learnSpell(SPELL_DUAL_WIELD, true);
						   player->learnSpell(SPELL_FIST_WEAPONS, true);
						   player->learnSpell(SPELL_GUNS, true);
						   player->learnSpell(SPELL_ONE_HANDED_AXES, true);
						   player->learnSpell(SPELL_ONE_HANDED_MACES, true);
						   player->learnSpell(SPELL_ONE_HANDED_SWORDS, true);
						   player->learnSpell(SPELL_PLATE, true);
						   player->learnSpell(SPELL_POLEARMS, true);
						   player->learnSpell(SPELL_SHIELD, true);
						   player->learnSpell(SPELL_SHOOT, true);
						   player->learnSpell(SPELL_STAVES, true);
						   player->learnSpell(SPELL_THROW, true);
						   player->learnSpell(SPELL_THROWN, true);
						   player->learnSpell(SPELL_TWO_HANDED_AXES, true);
						   player->learnSpell(SPELL_TWO_HANDED_MACES, true);
						   player->learnSpell(SPELL_TWO_HANDED_SWORDS, true);
					   }break;

				   case CLASS_HUNTER:
					   {
						   player->learnSpell(SPELL_BOWS, true);
						   player->learnSpell(SPELL_CROSSBOWS, true);
						   player->learnSpell(SPELL_DUAL_WIELD, true);
						   player->learnSpell(SPELL_FIST_WEAPONS, true);
						   player->learnSpell(SPELL_GUNS, true);
						   player->learnSpell(SPELL_MAIL, true);
						   player->learnSpell(SPELL_ONE_HANDED_AXES, true);
						   player->learnSpell(SPELL_ONE_HANDED_SWORDS, true);
						   player->learnSpell(SPELL_POLEARMS, true);
						   player->learnSpell(SPELL_STAVES, true);
						   player->learnSpell(SPELL_TWO_HANDED_AXES, true);
						   player->learnSpell(SPELL_TWO_HANDED_SWORDS, true);
					   }break;

				   case CLASS_ROGUE:
					   {
						   player->learnSpell(SPELL_BOWS, true);
						   player->learnSpell(SPELL_CROSSBOWS, true);
						   player->learnSpell(SPELL_DUAL_WIELD, true);
						   player->learnSpell(SPELL_FIST_WEAPONS, true);
						   player->learnSpell(SPELL_GUNS, true);
						   player->learnSpell(SPELL_ONE_HANDED_AXES, true);
						   player->learnSpell(SPELL_ONE_HANDED_MACES, true);
						   player->learnSpell(SPELL_ONE_HANDED_SWORDS, true);
						   player->learnSpell(SPELL_SHOOT, true);
						   player->learnSpell(SPELL_THROW, true);
						   player->learnSpell(SPELL_THROWN, true);
					   }break;

				   case CLASS_DRUID:
					   {
						   player->learnSpell(SPELL_DAGGERS, true);
						   player->learnSpell(SPELL_FIST_WEAPONS, true);
						   player->learnSpell(SPELL_ONE_HANDED_MACES, true);
						   player->learnSpell(SPELL_POLEARMS, true);
						   player->learnSpell(SPELL_RELIC_2, true);
						   player->learnSpell(SPELL_STAVES, true);
						   player->learnSpell(SPELL_TWO_HANDED_MACES, true);
					   }break;

				   case CLASS_MAGE:
					   {
						   player->learnSpell(SPELL_DAGGERS, true);
						   player->learnSpell(SPELL_ONE_HANDED_SWORDS, true);
						   player->learnSpell(SPELL_SHOOT_WANDS, true);
						   player->learnSpell(SPELL_STAVES, true);
						   player->learnSpell(SPELL_WANDS, true);
					   }break;

				   case CLASS_WARLOCK:
					   {
						   player->learnSpell(SPELL_DAGGERS, true);
						   player->learnSpell(SPELL_ONE_HANDED_SWORDS, true);
						   player->learnSpell(SPELL_SHOOT_WANDS, true);
						   player->learnSpell(SPELL_STAVES, true);
						   player->learnSpell(SPELL_WANDS, true);
					   }break;

				   case CLASS_PRIEST:
					   {
						   player->learnSpell(SPELL_DAGGERS, true);
						   player->learnSpell(SPELL_ONE_HANDED_MACES, true);
						   player->learnSpell(SPELL_SHOOT_WANDS, true);
						   player->learnSpell(SPELL_STAVES, true);
						   player->learnSpell(SPELL_WANDS, true);
					   }break;

				   case CLASS_DEATH_KNIGHT:
					   {
						   player->learnSpell(SPELL_DUAL_WIELD, true);
						   player->learnSpell(SPELL_ONE_HANDED_AXES, true);
						   player->learnSpell(SPELL_ONE_HANDED_MACES, true);
						   player->learnSpell(SPELL_ONE_HANDED_SWORDS, true);
						   player->learnSpell(SPELL_PLATE, true);
						   player->learnSpell(SPELL_POLEARMS, true);
						   player->learnSpell(SPELL_RELIC, true);
						   player->learnSpell(SPELL_TWO_HANDED_AXES, true);
						   player->learnSpell(SPELL_TWO_HANDED_MACES, true);
						   player->learnSpell(SPELL_TWO_HANDED_SWORDS, true);
					   }break;
				}
				player->UpdateSkillsToMaxSkillsForLevel();
			    player->MonsterWhisper("You now have all of your skills and they are also maxed out!", player->GetGUID());
			}
		}
};        


void AddSC_Weapon_Skills()
{
	new Weapon_Skills();
}