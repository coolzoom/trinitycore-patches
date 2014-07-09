/* Copyright (C) 2010 SAMCC Studios <http://www.samccstudios.com/>
 * Written by LordPsyan
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

 /*
Script Name: npc_bots v1.1
Complete: 100%
Comment: Database Driven Bots Master
*/

#include "ScriptPCH.h"
#include "Config.h"
#include "SystemConfig.h"

#define GOSSIP_SENDER_MAIN      1000
#define GOSSIP_BOTS             2000
#define GOSSIP_GMBOTS           4000
#define GOSSIP_PLAYERTOOLS      5000

#define SPELL_RESURRECTION_SICKNESS_15007  15007

#define NB_BOTS_PAGE            10
#define MSG_TYPE                100002
#define MSG_BOTS                100003

#define NEXT_PAGE               "-> [Next Page]"
#define PREV_PAGE               "<- [Previous Page]"
#define MAIN_MENU               "<= [Main Menu]"

npcClass npc_bots : public CreatureScript
{
public:
    npc_bots() : CreatureScript("npc_bots") {}

bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if(sConfigMgr->GetBoolDefault("Npc_Bots.OnlyGMs", false)) // If Npc_Bots.OnlyGMs is enabled in worldserver.conf
        if (pPlayer->GetSession()->GetSecurity() == SEC_PLAYER)
        {
            pCreature->MonsterWhisper("Sorry, I can only Provide Bots to Platinum Members.", pPlayer);
            return true;
        }

    bool EnableBots = sConfigMgr->GetBoolDefault("Npc_Bots.EnableBots", true);
    bool EnableGMBots = sConfigMgr->GetBoolDefault("Npc_Bots.EnableGMBots", true);

    // Main Menu

    // Check config if "  Bots " is enabled or not
    if(EnableBots)
        pPlayer->ADD_GOSSIP_ITEM( 7, "Bots ->"              , GOSSIP_SENDER_MAIN, 1000);
    // Check config if "GM Bots" is enabled or not
    if(EnableGMBots)
    {
    if (pPlayer->GetSession()->GetSecurity() > SEC_PLAYER)
        {
        pPlayer->ADD_GOSSIP_ITEM( 7, "Platinum Members Bots ->"                 , GOSSIP_SENDER_MAIN, 3000);
        }
    }

    pPlayer->SEND_GOSSIP_MENU(MSG_TYPE, pCreature->GetGUID());

return true;
}

bool showBots(Player *pPlayer, Creature *pCreature, uint32 showFromId = 0)
{


 QueryResult result;
 result = WorldDatabase.PQuery("SELECT `npcClass`, `level` FROM `npc_bots` WHERE `entry` BETWEEN 70001 AND 70248 ORDER BY `entry` ASC");

 if (result)
 {
 std::string name = "";
 uint32 catNumber = 0;
  do
 {
 Field *fields = result->Fetch();
 npcClass = fields[0].GetString();
 entry = fields[1].GetInt32();

    pPlayer->ADD_GOSSIP_ITEM(9, npcClass, GOSSIP_SENDER_MAIN, entry);
}
 while (result->NextRow());

    pPlayer->SEND_GOSSIP_MENU(MSG_BOTS, pCreature->GetGUID());
 return true;
 }
 else
 {
 if (showFromId = 0)
 {
 //you are too poor
 pCreature->MonsterWhisper("You don't have enough money.", pPlayer);
 pPlayer->CLOSE_GOSSIP_MENU();
 }
 else
 {

 //show Spells from beginning
 showBots(pPlayer, pCreature, 0);
 }
 }

 return false;
}

bool showGmBots(Player *pPlayer, Creature *pCreature, uint32 showFromId = 0)
{


 QueryResult result;
 result = WorldDatabase.PQuery("SELECT `npcClass`, `level` FROM `npc_bots` WHERE `entry` BETWEEN 70001 AND 70248 ORDER BY `entry` ASC");

 if (result)
 {
 std::string name = "";
 uint32 catNumber = 0;
  do
 {
 Field *fields = result->Fetch();
 npcClass = fields[0].GetString();
 entry = fields[1].GetInt32();

    pPlayer->ADD_GOSSIP_ITEM(9, npcClass, GOSSIP_SENDER_MAIN, entry);
}
 while (result->NextRow());

    pPlayer->SEND_GOSSIP_MENU(MSG_BOTS, pCreature->GetGUID());
 return true;
 }
 else
 {
 if (showFromId = 0)
 {
 //you are too poor
 pCreature->MonsterWhisper("You don't have enough money.", pPlayer);
 pPlayer->CLOSE_GOSSIP_MENU();
 }
 else
 {

 //show Spells from beginning
 showGmBots(pPlayer, pCreature, 0);
 }
 }

 return false;
}

void SendDefaultMenu(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{

// Not allow in combat
if (pPlayer->IsInCombat())
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
    return;
}

    bool EnableBots = sConfigMgr->GetBoolDefault("Npc_Bots.EnableBots", true);
    bool EnableGMBots = sConfigMgr->GetBoolDefault("Npc_Bots.EnableGMBots", true);

//Money Check
if (pPlayer->GetMoney() < (sConfigMgr->GetFloatDefault("BotsGoldCost",0)))
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterWhisper("You don't have enough money.", pPlayer);
    return;
}


  // send name as gossip item

       QueryResult result;
        uint32 spellId = 0;
        uint32 catNumber = 0;
        uint32 goldCost = 0;
        std::string spellName = "";

        result = WorldDatabase.PQuery("SELECT `npcClass`, `entry`FROM `npc_bots` WHERE `level` = %u LIMIT 1", uiAction);

        if (result)
        {

            do {

            Field *fields = result->Fetch();
            npcClass = fields[0].GetInt32();
            entry = fields[1].GetInt32();
            goldCost = fields[2].GetInt32();

            if (pPlayer->GetMoney() < goldCost)
            {
                pCreature->MonsterWhisper("You dont have enough money!", pPlayer);
                pPlayer->CLOSE_GOSSIP_MENU();
                return;
            }
            else if (uiAction < 5000 && uiAction != 1000 && uiAction != 2000 && uiAction != 3000 && uiAction != 4000 && uiAction != 5005)
            {
    pPlayer->CLOSE_GOSSIP_MENU();
    pPlayer->CastSpell(pPlayer,spellId,false);
    pPlayer->ModifyMoney(-goldCost);

            }

            } while (result->NextRow());
        } else {
            //pPlayer->ADD_GOSSIP_ITEM( 7, MAIN_MENU, GOSSIP_SENDER_MAIN, 5005);
        }

 switch(uiAction)
{

case 1000: //  Bots
         showBots(pPlayer, pCreature, 0);
        //pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"                            , GOSSIP_SENDER_MAIN, 5005);

    pPlayer->SEND_GOSSIP_MENU(MSG_BOTS, pCreature->GetGUID());
break;

case 3000: //GM  Bots

        showGmBots(pPlayer, pCreature, 0);
        //pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"                            , GOSSIP_SENDER_MAIN, 5005);

    pPlayer->SEND_GOSSIP_MENU(MSG_BOTS,pCreature->GetGUID());
break;

case 5005: //Back To Main Menu
    // Main Menu
    // Check config if "  Bots " is enabled or not
    if(EnableBots)
        pPlayer->ADD_GOSSIP_ITEM( 7, " Bots ->"              , GOSSIP_BOTS, 1000);
    // Check config if "GM Bots" is enabled or not
    if(EnableGMBots)
    {
    if (pPlayer->GetSession()->GetSecurity() > SEC_PLAYER)
        {
        pPlayer->ADD_GOSSIP_ITEM( 7, "Platinum Members Bots ->"                 , GOSSIP_SENDER_MAIN, 3000);
        }
    }
    pPlayer->SEND_GOSSIP_MENU(MSG_TYPE, pCreature->GetGUID());
break;

 pPlayer->CLOSE_GOSSIP_MENU();
 }

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
void AddSC_Npc_Bots()
{
    new npc_bots();
}