function LevelUP1 (event, player) --If the player levelup
                if player:GetClass() == 1 then --If the player class is Warrior
                if (player:GetLevel() == 1) then --If the player level 1
                player:LearnSpell(6673) --Battle Shout
                elseif (player:GetLevel() == 4) then --If the player level 4
		player:LearnSpell(100) --Charge
                player:LearnSpell(772) --Rend
                elseif (player:GetLevel() == 6) then --If the player level 6
                player:LearnSpell(6343) --Thunder Clap
                player:LearnSpell(34428) --Victory Rush
		player:LearnSpell(3127) --Parry
                elseif (player:GetLevel() == 8) then --If the player level 8
                player:LearnSpell(1715) --Hamstring
                player:LearnSpell(284) --Heroic Strike level 2
                elseif (player:GetLevel() == 10) then --If the player level 10
                player:LearnSpell(6546) --Rend level 2
                player:LearnSpell(2687) --Bloodrage
                player:LearnSpell(71) --Defensive Stance
                player:LearnSpell(7386) --Sunder Armor
                player:LearnSpell(355) --Taunt
                elseif (player:GetLevel() == 12) then --If the player level 12
                player:LearnSpell(7384) --Overpower
                player:LearnSpell(5242) --Battle Shout level 2
                player:LearnSpell(72) --Shield Bash
                elseif (player:GetLevel() == 14) then --If the player level 14
                player:LearnSpell(1160) --Demoralizing Shout
                player:LearnSpell(6572) --Revenge
                elseif (player:GetLevel() == 16) then --If the player level 16
                player:LearnSpell(285) --Heroic Strike level 3
                player:LearnSpell(694) --Mocking Blow
                player:LearnSpell(2565) --Shield Bash
                elseif (player:GetLevel() == 18) then --If the player level 18
                player:LearnSpell(8198) --Thunder Clap level 2
                player:LearnSpell(676) --Disarm
                elseif (player:GetLevel() == 20) then --If the player level 20
                player:LearnSpell(674) --Dual Wield
                player:LearnSpell(6547) --Rend level 3
                player:LearnSpell(20230) --Retaliation
                player:LearnSpell(845) --Cleave
                player:LearnSpell(12678) --Stance Mastery
                elseif (player:GetLevel() == 22) then --If the player level 22
                player:LearnSpell(6192) --Battle Shout level 3
                player:LearnSpell(5246) --Intimidating Shout
                elseif (player:GetLevel() == 24) then --If the player level 24
                player:LearnSpell(1608) --Heroic Strike level 4
                player:LearnSpell(6190) --Demoralizing Shout level 2
                player:LearnSpell(5308) --Execute
                player:LearnSpell(6574) --Revenge level 2
                elseif (player:GetLevel() == 26) then --If the player level 26
                player:LearnSpell(6178) --Charge level 2
                player:LearnSpell(1161) --Challenging Shout
                elseif (player:GetLevel() == 28) then --If the player level 28
                player:LearnSpell(8204) --Thunder Clap level 3
                player:LearnSpell(871) --Shield Wall
                elseif (player:GetLevel() == 30) then --If the player level 30
		player:LearnSpell(2458) --Berserker Stance
                player:LearnSpell(6548) --Rend level 4
                player:LearnSpell(7369) --Cleave level 2
                player:LearnSpell(20252) --Intercept
                player:LearnSpell(1464) --Slam
                elseif (player:GetLevel() == 32) then --If the player level 32
                player:LearnSpell(11564) --Heroic Strike level 5
                player:LearnSpell(11549) --Battle Shout level 4
                player:LearnSpell(18499) --Berserker Rage
                player:LearnSpell(20658) --Execute level 2
                elseif (player:GetLevel() == 34) then --If the player level 34
                player:LearnSpell(11554) --Demoralizing Shout level 3
                player:LearnSpell(7379) --Revenge level 3
                elseif (player:GetLevel() == 36) then --If the player level 36
                player:LearnSpell(1680) --Whirlwind
                elseif (player:GetLevel() == 38) then --If the player level 38
                player:LearnSpell(8205) --Thunder Clap level 4
                player:LearnSpell(6552) --Pummel
                player:LearnSpell(8820) --Slam level 2
                elseif (player:GetLevel() == 40) then --If the player level 40
		player:LearnSpell(750) --Plate Mail
                player:LearnSpell(11565) --Heroic Strike level 6
                player:LearnSpell(11572) --Rend level 5
                player:LearnSpell(11608) --Cleave level 3
                player:LearnSpell(20660) --Execute level 3
                player:LearnSpell(23922) --Shield Slam
                elseif (player:GetLevel() == 42) then --If the player level 42
                player:LearnSpell(11550) --Battle Shout level 5
                elseif (player:GetLevel() == 44) then --If the player level 44
                player:LearnSpell(11555) --Demoralizing Shout level 4
                player:LearnSpell(11600) --Revenge level 4
                elseif (player:GetLevel() == 46) then --If the player level 46
                player:LearnSpell(11578) --Charge level 3
                player:LearnSpell(11604) --Slam level 3
                elseif (player:GetLevel() == 48) then --If the player level 48
                player:LearnSpell(11566) --Heroic Strike level 7
                player:LearnSpell(11580) --Thunder Clap level 5
                player:LearnSpell(20661) --Execute level 4
                player:LearnSpell(23923) --Shield Slam level 2
                elseif (player:GetLevel() == 50) then --If the player level 50
                player:LearnSpell(11573) --Rend level 6
                player:LearnSpell(11609) --Cleave level 4
                player:LearnSpell(1719) --Recklessness
                elseif (player:GetLevel() == 52) then --If the player level 52
                player:LearnSpell(11551) --Battle Shout level 6
                elseif (player:GetLevel() == 54) then --If the player level 54
                player:LearnSpell(11556) --Demoralizing Shout level 5
                player:LearnSpell(11605) --Slam level 4
                player:LearnSpell(11601) --Revenge level 5
                player:LearnSpell(23924) --Shield Slam level 3
                elseif (player:GetLevel() == 56) then --If the player level 56
                player:LearnSpell(11567) --Heroic Strike level 8
                player:LearnSpell(20662) --Execute level 5
                elseif (player:GetLevel() == 58) then --If the player level 58
                player:LearnSpell(11581) --Thunder Clap level 6
                elseif (player:GetLevel() == 60) then --If the player level 60
                player:LearnSpell(25286) --Heroic Strike level 9
                player:LearnSpell(11574) --Rend level 7
                player:LearnSpell(25289) --Battle Shout level 7
                player:LearnSpell(20569) --Cleave level 5
                player:LearnSpell(25288) --Revenge level 6
                player:LearnSpell(23925) --Shield Slam level 4
                elseif (player:GetLevel() == 61) then --If the player level 61
                player:LearnSpell(25241) --Slam level 5
                elseif (player:GetLevel() == 62) then --If the player level 62
                player:LearnSpell(25202) --Demoralizing Shout level 6
                elseif (player:GetLevel() == 63) then --If the player level 63
                player:LearnSpell(25269) --Revenge level 7
                elseif (player:GetLevel() == 64) then --If the player level 64
                player:LearnSpell(23920) --Spell Reflection
                elseif (player:GetLevel() == 65) then --If the player level 65
                player:LearnSpell(25234) --Execute level 6
                elseif (player:GetLevel() == 66) then --If the player level 66
                player:LearnSpell(29707) --Heroic Strike level 10
                player:LearnSpell(25258) --Shield Slam level 5
                elseif (player:GetLevel() == 67) then --If the player level 67
                player:LearnSpell(25264) --Thunder Clap level 7
                elseif (player:GetLevel() == 68) then --If the player level 68
                player:LearnSpell(25208) --Rend level 8
                player:LearnSpell(25231) --Cleave level 6
                player:LearnSpell(469) --Commanding Shout
                elseif (player:GetLevel() == 69) then --If the player level 69
                player:LearnSpell(2048) --Battle Shout level 8
                player:LearnSpell(25242) --Slam level 6
                elseif (player:GetLevel() == 70) then --If the player level 70
                player:LearnSpell(30324) --Heroic Strike level 11
                player:LearnSpell(25203) --Demoralizing Shout level 7
                player:LearnSpell(25236) --Execute level 7
                player:LearnSpell(3411) --Intervene 
                player:LearnSpell(30357) --Revenge level 8
		player:LearnSpell(30356) --Shield Slam level 6
                elseif (player:GetLevel() == 71) then --If the player level 71
                player:LearnSpell(46845) --Rend level 9
                player:LearnSpell(64382) --Shattering Throw
                elseif (player:GetLevel() == 72) then --If the player level 72
                player:LearnSpell(47449) --Heroic Strike level 12
                player:LearnSpell(47519) --Cleave level 7
                elseif (player:GetLevel() == 73) then --If the player level 73
                player:LearnSpell(47501) --Thunder Clap level 8
                player:LearnSpell(47470) --Execute level 8
                elseif (player:GetLevel() == 74) then --If the player level 74
                player:LearnSpell(47439) --Commanding Shout level 2
                player:LearnSpell(47474) --Slam level 7
                elseif (player:GetLevel() == 75) then --If the player level 75
                player:LearnSpell(55694) --Enraged Regeneration
                player:LearnSpell(47487) --Shield Slam level 7
                elseif (player:GetLevel() == 76) then --If the player level 76
                player:LearnSpell(47450) --Heroic Strike level 13
                player:LearnSpell(47465) --Rend level 10
                elseif (player:GetLevel() == 77) then --If the player level 77
                player:LearnSpell(47520) --Cleave level 8
                elseif (player:GetLevel() == 78) then --If the player level 78
                player:LearnSpell(47502) --Thunder Clap level 9
                player:LearnSpell(47436) --Battle Shout level 9
                elseif (player:GetLevel() == 79) then --If the player level 79
                player:LearnSpell(47437) --Demoralizing Shout level 8
                player:LearnSpell(47475) --Slam level 8
                elseif (player:GetLevel() == 80) then --If the player level 80
                player:LearnSpell(57755) --Heroic Throw
                player:LearnSpell(47440) --Commanding Shout level 3
                player:LearnSpell(47471) --Execute level 9
                player:LearnSpell(57823) --Revenge level 9
                player:LearnSpell(47488) --Shield Slam level 8
end
end
end
 
RegisterServerHook(13, LevelUP1) --Last call LUA directly the internal parameters