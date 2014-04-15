/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ScriptPCH.h"
#include "Config.h"

class levelnpc : public CreatureScript
{
public:
    levelnpc() : CreatureScript("levelnpc") {}


bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
	if(sConfig->GetBoolDefault("LevelNPC.OnlyGMs", false)) // If LevelNPC.OnlyGMs is enabled in trinitycore.conf
		if (pPlayer->GetSession()->GetSecurity() == SEC_PLAYER)
		{
			pCreature->MonsterWhisper("Sorry, I can only add levels to Platinum Members.", pPlayer->GetGUID());
			return true;
		}

	bool EnableLevels = sConfig->GetBoolDefault("LevelNPC.EnableLevels", true);

	// Main Menu for Alliance
    if (pPlayer->GetTeam() == ALLIANCE)
	{
	// Check config if "Levels" is enabled or not
	if(EnableLevels)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Instant Level 80 ->"        , GOSSIP_SENDER_MAIN, 1000);
	else // Main Menu for Horde
	{
	// Check config if "Levels" is enabled or not
	if(EnableLevels)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Instant Level 80 ->"        , GOSSIP_SENDER_MAIN, 1000);
	}

    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());

return true;
}

void SendDefaultMenu(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{

// Not allow in combat
if (pPlayer->isInCombat())
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
	return;
}

	bool EnableLevels = sConfig->GetBoolDefault("LevelNPC.EnableLevels", true);
	
//Mony Check
if(sConfig->GetBoolDefault("LevelNPC.UseTokens", true))
{
if (!pPlayer->HasItemCount((sConfig->GetIntDefault("LevelNPC.ItemEntryNum",0)), 1))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterWhisper("You ain't gots no darn chips.", pPlayer->GetGUID());
	return;
}
else if(pPlayer->GetMoney() < (sConfig->GetIntDefault("LevelNPC.SkillGoldCost",0)))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterWhisper("You don't have enough money.", pPlayer->GetGUID());
	return;
}
}
switch(uiAction)
{

case 1000: //Profession
            pPlayer->ADD_GOSSIP_ITEM( 5, "Add Levels to 80"              , GOSSIP_SENDER_MAIN, 1001);
            pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"          , GOSSIP_SENDER_MAIN, 3000);

	pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
break;

case 3000: //Back To Main Menu
	// Main Menu for Alliance
    if (pPlayer->GetTeam() == ALLIANCE)
	{
	// Check config if "Leveling" is enabled or not
	if(EnableLevels)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Instant Level 80 ->"        , GOSSIP_SENDER_MAIN, 1000);
	}
	else // Main Menu for Horde
	{
	// Check config if "Leveling" is enabled or not
	if(EnableProfessions)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Instant Level 80 ->"        , GOSSIP_SENDER_MAIN, 1000);
	}

	pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
break;

//////////////////////////////////////////////////Professions///////////////////////////////////////////////////////////////

case 1001: // Leveling
	if(pPlayer->getLevel() >= 80)
      {
		pCreature->MonsterWhisper("You Are Level 80 or higher", pPlayer->GetGUID());
		OnGossipHello(pPlayer, pCreature);
		return;
	}

	pPlayer->getLevel()(171,(sConfig->GetIntDefault("MaxLeveling",0)));
	if(sConfig->GetBoolDefault("LevelNPC.UseTokens", true))
	pPlayer->DestroyItemCount(99998, 1, true);
	else
	pPlayer->ModifyMoney(-(sConfig->GetIntDefault("LevelNPC.SkillGoldCost",0)));
	pPlayer->CLOSE_GOSSIP_MENU();
break;
case 3000: //Back To Main Menu
	// Main Menu for Alliance
    if (pPlayer->GetTeam() == ALLIANCE)
	{
	// Check config if "Leveling" is enabled or not
	if(EnableProfessions)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Instant Level 80 ->"        , GOSSIP_SENDER_MAIN, 1000);
	}
	else // Main Menu for Horde
	{
	// Check config if "Leveling" is enabled or not
	if(EnableProfessions)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Instant Level 80 ->"        , GOSSIP_SENDER_MAIN, 1000);
	}

	pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
break;

 pPlayer->CLOSE_GOSSIP_MENU();

} // end of switch
} //end of function

bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	// Main menu
	pPlayer->PlayerTalkClass->ClearMenus();
	if (uiSender == GOSSIP_SENDER_MAIN)
	SendDefaultMenu(pPlayer, pCreature, uiAction);

return true;
}
};

void AddSC_levelnpc()
{

new levelnpc();

}
