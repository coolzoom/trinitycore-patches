#include "precompiled.h"
#include "Config/Config.h"

#define MSG_GOSSIP_TEXT_1  "I would like to rent a Ancient Frostsaber" 
#define MSG_GOSSIP_TEXT_2  "I would like to rent a Swift Brewfest Ram" 
#define MSG_GOSSIP_TEXT_3  "I would like to rent a Black War Kodo"
#define MSG_GOSSIP_TEXT_4  "I would like to rent a Swift Blue Raptor"
#define MSG_GOSSIP_TEXT_5  "I would like to rent a Black War Tiger"
#define MSG_GOSSIP_TEXT_6  "I would like to rent a Amani War Bear"
#define MSG_GOSSIP_TEXT_7  "I would like to rent a Mechanostrider"
#define MSG_GOSSIP_TEXT_8  "I would like to rent a Raven Lord"
#define MSG_NOT_MONEY      "You do not have enough money." 
#define MSG_MOUTED         "You already have a mount." 
#define MOUNT_SPELL_ID_1   16056 
#define MOUNT_SPELL_ID_2   43900 
#define MOUNT_SPELL_ID_3   22718 
#define MOUNT_SPELL_ID_4   23241 
#define MOUNT_SPELL_ID_5   22723 
#define MOUNT_SPELL_ID_6   43688 
#define MOUNT_SPELL_ID_7   17453 
#define MOUNT_SPELL_ID_8   41252 
#define NEW_GOSSIP_MESSAGE 40000
bool GossipHello_npc_rentalmount(Player *player, Creature *_creature) 
{ 
    player->ADD_GOSSIP_ITEM(4, MSG_GOSSIP_TEXT_1, GOSSIP_SENDER_MAIN, 1001); 
    player->ADD_GOSSIP_ITEM(4, MSG_GOSSIP_TEXT_2, GOSSIP_SENDER_MAIN, 1002); 
    player->ADD_GOSSIP_ITEM(4, MSG_GOSSIP_TEXT_3, GOSSIP_SENDER_MAIN, 1003); 
    player->ADD_GOSSIP_ITEM(4, MSG_GOSSIP_TEXT_4, GOSSIP_SENDER_MAIN, 1004); 
    player->ADD_GOSSIP_ITEM(4, MSG_GOSSIP_TEXT_5, GOSSIP_SENDER_MAIN, 1005); 
    player->ADD_GOSSIP_ITEM(4, MSG_GOSSIP_TEXT_6, GOSSIP_SENDER_MAIN, 1006); 
    player->ADD_GOSSIP_ITEM(4, MSG_GOSSIP_TEXT_7, GOSSIP_SENDER_MAIN, 1007); 
    player->ADD_GOSSIP_ITEM(4, MSG_GOSSIP_TEXT_8, GOSSIP_SENDER_MAIN, 1008); 
    player->SEND_GOSSIP_MENU(NEW_GOSSIP_MESSAGE, _creature->GetObjectGuid()); 
    return true; 
} 

bool GossipSelect_npc_rentalmount(Player *player, Creature *_creature, uint32 sender, uint32 action ) 
{ 
    if (sender != GOSSIP_SENDER_MAIN) 
        return false; 

    if (player->IsMounted()){ 
        _creature->MonsterSay(MSG_MOUTED, NULL); 
         return false; 
    } 

    uint32 fastprice = sConfig.GetIntDefault("RentalMountNPC.FastPrice",500);

    switch (action) 
    { 
    case 1001: 
        if (player->GetMoney() < fastprice) 
        { 
            _creature->MonsterSay(MSG_NOT_MONEY, NULL); 
        } else { 
            player->CastSpell(player,MOUNT_SPELL_ID_1,false);
            player->ModifyMoney(-fastprice); 
        } 
        break; 
    case 1002: 
        if (player->GetMoney() < fastprice) 
        { 
            _creature->MonsterSay(MSG_NOT_MONEY, NULL); 
        } else { 
            player->CastSpell(player,MOUNT_SPELL_ID_2,false); 
            player->ModifyMoney(-fastprice); 
        } 
        break; 
    case 1003: 
        if (player->GetMoney() < fastprice) 
        { 
            _creature->MonsterSay(MSG_NOT_MONEY, NULL); 
        } else { 
            player->CastSpell(player,MOUNT_SPELL_ID_3,false); 
            player->ModifyMoney(-fastprice); 
        } 
        break; 
    case 1004: 
        if (player->GetMoney() < fastprice) 
        { 
            _creature->MonsterSay(MSG_NOT_MONEY, NULL); 
        } else { 
            player->CastSpell(player,MOUNT_SPELL_ID_4,false); 
            player->ModifyMoney(-fastprice); 
        } 
        break; 
    case 1005: 
        if (player->GetMoney() < fastprice) 
        { 
            _creature->MonsterSay(MSG_NOT_MONEY, NULL); 
        } else { 
            player->CastSpell(player,MOUNT_SPELL_ID_5,false); 
            player->ModifyMoney(-fastprice); 
        } 
        break; 
    case 1006: 
        if (player->GetMoney() < fastprice) 
        { 
            _creature->MonsterSay(MSG_NOT_MONEY, NULL); 
        } else { 
            player->CastSpell(player,MOUNT_SPELL_ID_6,false); 
            player->ModifyMoney(-fastprice); 
        } 
        break; 
    case 1007: 
        if (player->GetMoney() < fastprice) 
        { 
            _creature->MonsterSay(MSG_NOT_MONEY, NULL); 
        } else { 
            player->CastSpell(player,MOUNT_SPELL_ID_7,false); 
            player->ModifyMoney(-fastprice); 
        } 
        break; 
    case 1008: 
        if (player->GetMoney() < fastprice) 
        { 
            _creature->MonsterSay(MSG_NOT_MONEY, NULL); 
        } else { 
            player->CastSpell(player,MOUNT_SPELL_ID_8,false); 
            player->ModifyMoney(-fastprice); 
        } 
        break; 

    } 
    player->CLOSE_GOSSIP_MENU();
    return true; 
} 

void AddSC_npc_rentalmount() 
{ 
     Script *newscript; 
     newscript = new Script; 
     newscript->Name = "npc_rentalmount"; 
     newscript->pGossipHello = &GossipHello_npc_rentalmount; 
     newscript->pGossipSelect = &GossipSelect_npc_rentalmount; 
     newscript->RegisterSelf(); 
}
