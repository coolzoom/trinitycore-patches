#include "precompiled.h"

bool ItemUse_item_icerune(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
                {
   uint32 sSpell = 18282; //Icerune Visual Spell when used
   if (pPlayer->isInCombat())
   {
        pPlayer->GetSession()->SendNotification("You are in combat.");
   }
  
   else if (pPlayer->isMoving())
   {
        pPlayer->GetSession()->SendNotification("You can not do that while moving.");
   }
  /*
   else if (pPlayer->GetClosestCreatureWithEntry(pPlayer, 100000, 40) || pPlayer->GetClosestCreatureWithEntry(pPlayer, 100000, 8))
   {
        pPlayer->GetSession()->SendNotification("Flaming Legion Vortex can not be summoned right now. Another Vortex is nearby.");
   }*/
  
   else
   {
        float x, y, z, o = pPlayer->GetOrientation();
  
        if (o >= 3.141592)
         o = o - 3.141592;
        else
         o = o + 3.141592;
        Creature* pCreature = pPlayer->SummonCreature(100000,pPlayer->GetPositionX() ,pPlayer->GetPositionY(), pPlayer->GetPositionZ()+2, 0,TEMPSUMMON_TIMED_DESPAWN,120000);
        pCreature->CastSpell(pCreature, 40162, true);
        return false;
   }
  return false;
                }

void AddSC_summon()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "summon";
    pNewScript->pItemUse = &ItemUse_item_icerune;
    pNewScript->RegisterSelf();
}
