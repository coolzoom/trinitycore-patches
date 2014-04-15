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
 *
 * Created by Surion for www.realmsofwarcraft.com
 *
 */

#include "precompiled.h"
#include "Config/Config.h"
#include "Object.h"

#define GOSSIP_SENDER_MAIN      1000
#define SPELL_RESURRECTION_SICKNESS_15007  15007


bool GossipHello_levelnpc(Player* pPlayer, Creature* pCreature)
{
	if(sConfig.GetBoolDefault("LevelNPC.OnlyGMs", false)) // If LevelNPC.OnlyGMs is enabled in trinitycore.conf
		if (pPlayer->GetSession()->GetSecurity() == SEC_PLAYER)
		{
			pCreature->MonsterSay("Sorry, I can only add levels to Platinum Members.", LANG_UNIVERSAL, NULL);
			return true;
		}

	bool EnableLevel10 = sConfig.GetBoolDefault("LevelNPC.EnableLevel10", true);
	bool EnableLevel20 = sConfig.GetBoolDefault("LevelNPC.EnableLevel20", true);
	bool EnableLevel30 = sConfig.GetBoolDefault("LevelNPC.EnableLevel30", true);
	bool EnableLevel40 = sConfig.GetBoolDefault("LevelNPC.EnableLevel40", true);
	bool EnableLevel50 = sConfig.GetBoolDefault("LevelNPC.EnableLevel50", true);
	bool EnableLevel60 = sConfig.GetBoolDefault("LevelNPC.EnableLevel60", true);
	bool EnableLevel70 = sConfig.GetBoolDefault("LevelNPC.EnableLevel70", true);
	bool EnableLevel80 = sConfig.GetBoolDefault("LevelNPC.EnableLevel80", true);
	bool EnableLevel90 = sConfig.GetBoolDefault("LevelNPC.EnableLevel90", true);
	bool EnableLevel100 = sConfig.GetBoolDefault("LevelNPC.EnableLevel100", true);
    if (pPlayer->GetTeam() == ALLIANCE)
	{
		pPlayer->ADD_GOSSIP_ITEM( 7, "Instant Levels ->"        , GOSSIP_SENDER_MAIN, 1000);
		pPlayer->ADD_GOSSIP_ITEM( 10, "(1 gold) Remove Resurrect Sickness" , GOSSIP_SENDER_MAIN, 5000);
	}
	else
	{
		pPlayer->ADD_GOSSIP_ITEM( 7, "Instant Levels ->"        , GOSSIP_SENDER_MAIN, 1000);
		pPlayer->ADD_GOSSIP_ITEM( 10, "(1 gold) Remove Resurrect Sickness" , GOSSIP_SENDER_MAIN, 5000);
	}
    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());

return true;
}

void SendDefaultMenu_levelnpc(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{

// Not allow in combat
if (pPlayer->isInCombat())
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
	return;
}

	bool EnableLevel10 = sConfig.GetBoolDefault("LevelNPC.EnableLevel10", true);
	bool EnableLevel20 = sConfig.GetBoolDefault("LevelNPC.EnableLevel20", true);
	bool EnableLevel30 = sConfig.GetBoolDefault("LevelNPC.EnableLevel30", true);
	bool EnableLevel40 = sConfig.GetBoolDefault("LevelNPC.EnableLevel40", true);
	bool EnableLevel50 = sConfig.GetBoolDefault("LevelNPC.EnableLevel50", true);
	bool EnableLevel60 = sConfig.GetBoolDefault("LevelNPC.EnableLevel60", true);
	bool EnableLevel70 = sConfig.GetBoolDefault("LevelNPC.EnableLevel70", true);
	bool EnableLevel80 = sConfig.GetBoolDefault("LevelNPC.EnableLevel80", true);
	bool EnableLevel90 = sConfig.GetBoolDefault("LevelNPC.EnableLevel90", true);
	bool EnableLevel100 = sConfig.GetBoolDefault("LevelNPC.EnableLevel100", true);
	
//Mony Check
/*if(sConfig.GetBoolDefault("LevelNPC.UseTokens", true))
{
if (!pPlayer->HasItemCount((sConfig.GetIntDefault("LevelNPC.ItemEntryNum",0)), 0))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You ain't gots no darn Donation Gems.", LANG_UNIVERSAL, NULL);
	return;
}
}
else if(pPlayer->GetMoney() < (sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You don't have enough money.", LANG_UNIVERSAL, NULL);
	return;
}*/

switch(uiAction)
{

//////////////////////////////////////////////////Leveling///////////////////////////////////////////////////////////////
case 1000: //Leveling
	if(EnableLevel10 && pPlayer->getLevel() < 10)
		pPlayer->ADD_GOSSIP_ITEM( 7, "(1 Donation Gem) Instant 10 ->"         , GOSSIP_SENDER_MAIN, 1001);
	if(EnableLevel20 && pPlayer->getLevel() < 20 && pPlayer->getLevel() >= 10)
		pPlayer->ADD_GOSSIP_ITEM( 7, "(2 Donation Gems) Instant 20 ->"        , GOSSIP_SENDER_MAIN, 1002);
	if(EnableLevel30 && pPlayer->getLevel() < 30 && pPlayer->getLevel() >= 20)
		pPlayer->ADD_GOSSIP_ITEM( 7, "(5 Donation Gems) Instant 30 ->"        , GOSSIP_SENDER_MAIN, 1003);
	if(EnableLevel40 && pPlayer->getLevel() < 40 && pPlayer->getLevel() >= 30)
		pPlayer->ADD_GOSSIP_ITEM( 7, "(5 Donation Gems) Instant 40 ->"       , GOSSIP_SENDER_MAIN, 1004);
	if(EnableLevel50 && pPlayer->getLevel() < 50 && pPlayer->getLevel() >= 40)
		pPlayer->ADD_GOSSIP_ITEM( 7, "(5 Donation Gems) Instant 50 ->"       , GOSSIP_SENDER_MAIN, 1005);
	if(EnableLevel60 && pPlayer->getLevel() < 60 && pPlayer->getLevel() >= 50)
		pPlayer->ADD_GOSSIP_ITEM( 7, "(5 Donation Gems) Instant 60 ->"       , GOSSIP_SENDER_MAIN, 1006);
	if(EnableLevel70 && pPlayer->getLevel() < 70 && pPlayer->getLevel() >= 60)
		pPlayer->ADD_GOSSIP_ITEM( 7, "(5 Donation Gems) Instant 70 ->"       , GOSSIP_SENDER_MAIN, 1007);
	if(EnableLevel80 && pPlayer->getLevel() < 80 && pPlayer->getLevel() >= 70)
		pPlayer->ADD_GOSSIP_ITEM( 7, "(5 Donation Gems) Instant 80 ->"       , GOSSIP_SENDER_MAIN, 1008);
	if(EnableLevel90 && pPlayer->getLevel() < 90 && pPlayer->getLevel() >= 80)
		pPlayer->ADD_GOSSIP_ITEM( 7, "(5 Donation Gems) Instant 90 ->"       , GOSSIP_SENDER_MAIN, 1009);
	if(EnableLevel100 && pPlayer->getLevel() < 100 && pPlayer->getLevel() >= 90)
		pPlayer->ADD_GOSSIP_ITEM( 7, "(5 Donation Gems) Instant 100 ->"       , GOSSIP_SENDER_MAIN, 1010);

		pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"                       , GOSSIP_SENDER_MAIN, 3000);
	pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
break;
case 3000: //Leveling
	if(EnableLevel10)
		pPlayer->ADD_GOSSIP_ITEM( 7, "Instant Levels ->"        , GOSSIP_SENDER_MAIN, 1000);
    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
break;
case 1001: // Leveling
if (!pPlayer->HasItemCount((sConfig.GetIntDefault("LevelNPC.ItemEntryNum",0)), 1))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("Sorry, you do not have enough Donation Gems.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->GiveLevel(10);
	if(sConfig.GetBoolDefault("LevelNPC.UseTokens", true))
	pPlayer->DestroyItemCount(99999, 1, true);
	else if(pPlayer->GetMoney() < (sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You don't have enough money.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->ModifyMoney(-(sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)));
	pPlayer->CLOSE_GOSSIP_MENU();
break;
case 1002: // Leveling
if (!pPlayer->HasItemCount((sConfig.GetIntDefault("LevelNPC.ItemEntryNum",0)), 2))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("Sorry, you do not have enough Donation Gems.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->GiveLevel(20);
	if(sConfig.GetBoolDefault("LevelNPC.UseTokens", true))
	pPlayer->DestroyItemCount(99999, 2, true);
	else if(pPlayer->GetMoney() < (sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You don't have enough money.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->ModifyMoney(-(sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)));
	pPlayer->CLOSE_GOSSIP_MENU();
break;
case 1003: // Leveling
if (!pPlayer->HasItemCount((sConfig.GetIntDefault("LevelNPC.ItemEntryNum",0)), 3))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("Sorry, you do not have enough Donation Gems.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->GiveLevel(30);
	if(sConfig.GetBoolDefault("LevelNPC.UseTokens", true))
	pPlayer->DestroyItemCount(99999, 5, true);
	else if(pPlayer->GetMoney() < (sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You don't have enough money.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->ModifyMoney(-(sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)));
	pPlayer->CLOSE_GOSSIP_MENU();
break;
case 1004: // Leveling
if (!pPlayer->HasItemCount((sConfig.GetIntDefault("LevelNPC.ItemEntryNum",0)), 5))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("Sorry, you do not have enough Donation Gems.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->GiveLevel(40);
	if(sConfig.GetBoolDefault("LevelNPC.UseTokens", true))
	pPlayer->DestroyItemCount(99999, 5, true);
	else if(pPlayer->GetMoney() < (sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You don't have enough money.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->ModifyMoney(-(sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)));
	pPlayer->CLOSE_GOSSIP_MENU();
break;
case 1005: // Leveling
if (!pPlayer->HasItemCount((sConfig.GetIntDefault("LevelNPC.ItemEntryNum",0)), 5))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("Sorry, you do not have enough Donation Gems.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->GiveLevel(50);
	if(sConfig.GetBoolDefault("LevelNPC.UseTokens", true))
	pPlayer->DestroyItemCount(99999, 5, true);
	else if(pPlayer->GetMoney() < (sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You don't have enough money.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->ModifyMoney(-(sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)));
	pPlayer->CLOSE_GOSSIP_MENU();
break;
case 1006: // Leveling
if (!pPlayer->HasItemCount((sConfig.GetIntDefault("LevelNPC.ItemEntryNum",0)), 5))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("Sorry, you do not have enough Donation Gems.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->GiveLevel(60);
	if(sConfig.GetBoolDefault("LevelNPC.UseTokens", true))
	pPlayer->DestroyItemCount(99999, 5, true);
	else if(pPlayer->GetMoney() < (sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You don't have enough money.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->ModifyMoney(-(sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)));
	pPlayer->CLOSE_GOSSIP_MENU();
break;
case 1007: // Leveling
if (!pPlayer->HasItemCount((sConfig.GetIntDefault("LevelNPC.ItemEntryNum",0)), 5))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("Sorry, you do not have enough Donation Gems.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->GiveLevel(70);
	if(sConfig.GetBoolDefault("LevelNPC.UseTokens", true))
	pPlayer->DestroyItemCount(99999, 5, true);
	else if(pPlayer->GetMoney() < (sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You don't have enough money.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->ModifyMoney(-(sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)));
	pPlayer->CLOSE_GOSSIP_MENU();
break;
case 1008: // Leveling
if (!pPlayer->HasItemCount((sConfig.GetIntDefault("LevelNPC.ItemEntryNum",0)), 5))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("Sorry, you do not have enough Donation Gems.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->GiveLevel(80);
	if(sConfig.GetBoolDefault("LevelNPC.UseTokens", true))
	pPlayer->DestroyItemCount(99999, 5, true);
	else if(pPlayer->GetMoney() < (sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You don't have enough money.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->ModifyMoney(-(sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)));
	pPlayer->CLOSE_GOSSIP_MENU();
break;
case 1009: // Leveling
if (!pPlayer->HasItemCount((sConfig.GetIntDefault("LevelNPC.ItemEntryNum",0)), 5))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("Sorry, you do not have enough Donation Gems.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->GiveLevel(90);
	if(sConfig.GetBoolDefault("LevelNPC.UseTokens", true))
	pPlayer->DestroyItemCount(99999, 5, true);
	else if(pPlayer->GetMoney() < (sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You don't have enough money.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->ModifyMoney(-(sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)));
	pPlayer->CLOSE_GOSSIP_MENU();
break;
case 1010: // Leveling
if (!pPlayer->HasItemCount((sConfig.GetIntDefault("LevelNPC.ItemEntryNum",0)), 5))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("Sorry, you do not have enough Donation Gems.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->GiveLevel(100);
	if(sConfig.GetBoolDefault("LevelNPC.UseTokens", true))
	pPlayer->DestroyItemCount(99999, 5, true);
	else if(pPlayer->GetMoney() < (sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You don't have enough money.", LANG_UNIVERSAL, NULL);
	return;
}
	pPlayer->ModifyMoney(-(sConfig.GetIntDefault("LevelNPC.SkillGoldCost",0)));
	pPlayer->CLOSE_GOSSIP_MENU();
break;
case 5000://Remove Res Sickness
	if(!pPlayer->HasAura(SPELL_RESURRECTION_SICKNESS_15007))
	{
		pCreature->MonsterSay("You don't have resurrection sickness.", LANG_UNIVERSAL, NULL);
		GossipHello_levelnpc(pPlayer, pCreature);
		return;
	}
	else if(pPlayer->GetMoney() < (sConfig.GetIntDefault("LevelNPC.SkillGoldCostRes",0)))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You don't have enough money.", LANG_UNIVERSAL, NULL);
	return;
}
	pCreature->CastSpell(pPlayer,38588,false); // Healing effect
	pPlayer->RemoveAurasDueToSpell(SPELL_RESURRECTION_SICKNESS_15007,0);
	pPlayer->CLOSE_GOSSIP_MENU();
break;

 pPlayer->CLOSE_GOSSIP_MENU();

} // end of switch
} //end of function

bool GossipSelect_levelnpc(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	// Main menu
	pPlayer->PlayerTalkClass->ClearMenus();
	if (uiSender == GOSSIP_SENDER_MAIN)
	SendDefaultMenu_levelnpc(pPlayer, pCreature, uiAction);

return true;
}

void AddSC_levelnpc()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="levelnpc";
    newscript->pGossipHello =  &GossipHello_levelnpc;
    newscript->pGossipSelect = &GossipSelect_levelnpc;
    newscript->RegisterSelf();
}