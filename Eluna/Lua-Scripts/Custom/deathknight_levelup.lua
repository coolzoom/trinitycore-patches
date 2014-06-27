function LevelUP6 (event, player)
		if player:GetClass() == 6 then -- Death Knight
		if (player:GetLevel() == 56) then
		player:LearnSpell(50842)
		player:LearnSpell(49998)
		player:LearnSpell(46584)
		elseif (player:GetLevel() == 57) then
		player:LearnSpell(48263)
		player:LearnSpell(47528)
		elseif (player:GetLevel() == 58) then
		player:LearnSpell(48721)
		player:LearnSpell(45524)
		elseif (player:GetLevel() == 59) then
		player:LearnSpell(49926)
		player:LearnSpell(47476)
		elseif (player:GetLevel() == 60) then
		player:LearnSpell(43265)
		player:LearnSpell(49917)
		elseif (player:GetLevel() == 61) then
		player:LearnSpell(49896)
		player:LearnSpell(49020)
		player:LearnSpell(3714)
		elseif (player:GetLevel() == 62) then
		player:LearnSpell(48792)
		player:LearnSpell(49892)
		elseif (player:GetLevel() == 63) then
		player:LearnSpell(49999)
		elseif (player:GetLevel() == 64) then
		player:LearnSpell(49927)
		player:LearnSpell(45529)
		elseif (player:GetLevel() == 65) then
		player:LearnSpell(56222)
		player:LearnSpell(57330)
		player:LearnSpell(49918)
		elseif (player:GetLevel() == 66) then
		player:LearnSpell(49939)
		player:LearnSpell(48743)
		elseif (player:GetLevel() == 67) then
		player:LearnSpell(49903)
		player:LearnSpell(51423)
		player:LearnSpell(56815)
		player:LearnSpell(49936)
		elseif (player:GetLevel() == 68) then
		player:LearnSpell(48707)
		player:LearnSpell(49893)
		elseif (player:GetLevel() == 69) then
		player:LearnSpell(49928)
		elseif (player:GetLevel() == 70) then
		player:LearnSpell(45463)
		player:LearnSpell(49919)
		player:LearnSpell(48265)
		elseif (player:GetLevel() == 72) then
		player:LearnSpell(49940)
		player:LearnSpell(61999)
		elseif (player:GetLevel() == 73) then
		player:LearnSpell(49904)
		player:LearnSpell(51424)
		player:LearnSpell(49937)
		elseif (player:GetLevel() == 74) then
		player:LearnSpell(49929)
		elseif (player:GetLevel() == 75) then
		player:LearnSpell(47568)
		player:LearnSpell(57623)
		player:LearnSpell(49923)
		player:LearnSpell(49920)
		elseif (player:GetLevel() == 76) then
		player:LearnSpell(49894)
		elseif (player:GetLevel() == 78) then
		player:LearnSpell(49941)
		player:LearnSpell(49909)
		elseif (player:GetLevel() == 79) then
		player:LearnSpell(51425)
		elseif (player:GetLevel() == 80) then
		player:LearnSpell(49930)
		player:LearnSpell(42650)
		player:LearnSpell(49938)
		player:LearnSpell(49895)
		player:LearnSpell(49924)
		player:LearnSpell(49921)

end
end
end

RegisterServerHook(13, LevelUP6)