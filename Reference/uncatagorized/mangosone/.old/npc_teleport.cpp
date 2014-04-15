/**
 *
 * @File : npc_teleport.cpp
 *
 * @Authors : Wilibald09
 *
 * @Date : 19/08/2008
 *
 * @Version : 1.2
 *
 **/


#include "precompiled.h"
#include "../../../game/Teleport/sc_npc_teleport.h"
#include <sstream>



#define GOSSIP_SHOW_DEST        1000
#define GOSSIP_TELEPORT         1001
#define GOSSIP_NEXT_PAGEC       1002
#define GOSSIP_PREV_PAGEC       1003
#define GOSSIP_NEXT_PAGED       1004
#define GOSSIP_PREV_PAGED       1005
#define GOSSIP_MAIN_MENU        1006

#define SPELL_VISUAL_TELEPORT   35517

#define NB_ITEM_PAGE            10
#define MSG_CAT                 100000
#define MSG_DEST                100001

#define NEXT_PAGE               "-> [Next Page]"
#define PREV_PAGE               "<- [Previous Page]"
#define MAIN_MENU               "<= [Main Menu]"


using namespace nsNpcTel;


namespace
{
    Page PageC, PageD;
    Page Cat;

    // Conversion function int->string
    std::string ConvertStr(const int64 &val)
    {
        std::ostringstream ostr;
        ostr << val;
        return ostr.str();
    }

    // Conversion function intMoney->stringMoney
    std::string ConvertMoney(const uint32 &Money)
    {
        std::string Str(ConvertStr(Money));
        uint32 SizeStr = Str.length();

        if (SizeStr > 4)
            Str = Str.insert(Str.length()-4, "po");
        if (SizeStr > 2)
            Str = Str.insert(Str.length()-2, "pa");
        Str += "pc";

        return Str;
    }

    // Teleport Player
    void Teleport(Player * const player, const uint16 &map,
                  const float &X, const float &Y, const float &Z, const float &orient)
    {
        player->CastSpell(player, SPELL_VISUAL_TELEPORT, true);
        player->TeleportTo(map, X, Y, Z, orient);
    }

    // Display categories
    void AffichCat(Player * const player, Creature * const creature)
    {
        if (PageC[player] > 0)
            player->ADD_GOSSIP_ITEM(7, PREV_PAGE, GOSSIP_PREV_PAGEC, 0);

        VCatDest_t i (PageC[player] * NB_ITEM_PAGE);
        for (; i < TabCatDest.size() && i < (NB_ITEM_PAGE * (PageC[player] + 1)); ++i)
        {
            if (TabCatDest[i].IsAllowedToTeleport(player))
                player->ADD_GOSSIP_ITEM(7, TabCatDest[i].GetName(player->isGameMaster()).c_str(), GOSSIP_SHOW_DEST, i);
        }

        if (i < TabCatDest.size())
            player->ADD_GOSSIP_ITEM(7, NEXT_PAGE, GOSSIP_NEXT_PAGEC, 0);

        player->SEND_GOSSIP_MENU(MSG_CAT, creature->GetObjectGuid());
    }

    // Display destination categories
    void AffichDest(Player * const player, Creature * const creature)
    {
        if (PageD[player] > 0)
            player->ADD_GOSSIP_ITEM(7, PREV_PAGE, GOSSIP_PREV_PAGED, 0);

        CatDest::VDest_t i (PageD[player] * NB_ITEM_PAGE);
        for (; i < TabCatDest[Cat[player]].size() && i < (NB_ITEM_PAGE * (PageD[player] + 1)); ++i)
        {
            player->ADD_GOSSIP_ITEM(5, TabCatDest[Cat[player]].GetDest(i).m_name.c_str(), GOSSIP_TELEPORT, i);
        }

        if (i < TabCatDest[Cat[player]].size())
            player->ADD_GOSSIP_ITEM(7, NEXT_PAGE, GOSSIP_NEXT_PAGED, 0);

        if (CatDest::CountOfCategoryAllowedBy(player) > 1)
            player->ADD_GOSSIP_ITEM(7, MAIN_MENU, GOSSIP_MAIN_MENU, 0);

        player->SEND_GOSSIP_MENU(MSG_DEST, creature->GetObjectGuid());
    }

    // Verification before teleportation
    void ActionTeleport(Player * const player, Creature * const creature, const uint32 &id)
    {
        Dest dest (TabCatDest[Cat[player]].GetDest(id));

        if (player->getLevel() < dest.m_level && !player->isGameMaster()) 
        {
            std::string msg ("You do not have the required level. This destination requires level " + ConvertStr(dest.m_level) + ".");
            creature->MonsterSay(msg.c_str(), LANG_UNIVERSAL);
            return;
        }

        if (player->GetMoney() < dest.m_cost && !player->isGameMaster())
        {
            std::string msg ("You do not have enough money. The price for teleportation is " + ConvertMoney(dest.m_cost) + ".");
            creature->MonsterSay(msg.c_str(), LANG_UNIVERSAL);
            return;
        }

        if (!player->isGameMaster() && dest.m_cost)
            player->ModifyMoney(-1 * dest.m_cost);

        Teleport(player, dest.m_map, dest.m_X, dest.m_Y, dest.m_Z, dest.m_orient);
    }
}

bool GossipHello_npc_teleport(Player *player, Creature *creature)
{
    PageC(player) = PageD(player) = Cat(player) = 0;

    if (player->isInCombat())
    {
        player->CLOSE_GOSSIP_MENU();
        creature->MonsterSay("You are in combat. Come back later", LANG_UNIVERSAL);
        return true;
    }
    AffichCat(player, creature);
    return true;
}

bool GossipSelect_npc_teleport(Player *player, Creature *creature, uint32 sender, uint32 param)
{
    switch(sender) 
    {
      // Display destinations
      case GOSSIP_SHOW_DEST:
        Cat(player) = param;
		player->PlayerTalkClass->ClearMenus();
        AffichDest(player, creature);
        break;

      // Previous categories page
      case GOSSIP_PREV_PAGEC:
        --PageC(player);
		player->PlayerTalkClass->ClearMenus();
        AffichCat(player, creature);
        break;

      // Next page categories
      case GOSSIP_NEXT_PAGEC:
        ++PageC(player);
		player->PlayerTalkClass->ClearMenus();
        AffichCat(player, creature);
        break;

      // Previous destinations page
      case GOSSIP_PREV_PAGED:
        --PageD(player);
		player->PlayerTalkClass->ClearMenus();
        AffichDest(player, creature);
        break;

      // Next destination page
      case GOSSIP_NEXT_PAGED:
        ++PageD(player);
		player->PlayerTalkClass->ClearMenus();
        AffichDest(player, creature);
        break;

      // Display main menu
      case GOSSIP_MAIN_MENU:
	    player->PlayerTalkClass->ClearMenus();
        GossipHello_npc_teleport(player, creature);
        break;

      // Teleportation
      case GOSSIP_TELEPORT:
        player->CLOSE_GOSSIP_MENU();
        if (player->HasAura(15007,EFFECT_INDEX_0)) {
            creature->CastSpell(player,38588,false); // Healing effect
            player->RemoveAurasDueToSpell(15007);
        }

        ActionTeleport(player, creature, param);
        break;
    }
    return true;
}


void AddSC_npc_teleport()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="npc_teleport";
    newscript->pGossipHello =  &GossipHello_npc_teleport;
    newscript->pGossipSelect = &GossipSelect_npc_teleport;
    newscript->RegisterSelf();
}
