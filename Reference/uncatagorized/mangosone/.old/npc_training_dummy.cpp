/* Copyright (C) 2012 - 2012 LilleCarl <http://www.lillecarl.com/>
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

#include "precompiled.h"

typedef UNORDERED_MAP<ObjectGuid, uint32> AttackerMap;

struct MANGOS_DLL_DECL npc_training_dummyAI : public Scripted_NoMovementAI
{
    npc_training_dummyAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature){}

    AttackerMap m_AttackerMap;

    void Reset()
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
    }

    void DamageTaken(Unit* pDealer, uint32& uiDamage)
    {
        if (pDealer->GetTypeId() == TYPEID_PLAYER)
            m_AttackerMap[pDealer->GetObjectGuid()] = 6000;

        if (m_creature->GetHealthPercent() < 10.0f || m_creature->GetHealthPercent() > 20.0f) // allow players using finishers
            m_creature->SetHealth(m_creature->GetMaxHealth()/5);

        m_creature->SetTargetGuid(ObjectGuid()); // prevent from rotating
    }

    void UpdateAI(const uint32 diff)
    {
        for (AttackerMap::iterator itr = m_AttackerMap.begin(); itr != m_AttackerMap.end();)
        {
            if (itr->second < diff)
            {
                if (Player* pAttacker = m_creature->GetMap()->GetPlayer(itr->first))
                {
                    pAttacker->CombatStop(true);
                    pAttacker->AttackStop(false);
                    pAttacker->CombatStopWithPets(true);
                    pAttacker->ClearInCombat();
                }

                itr = m_AttackerMap.erase(itr);

                if (m_AttackerMap.empty())
                {
                    EnterEvadeMode();
                    m_creature->SetHealth(m_creature->GetMaxHealth());
                }
            }
            else
            {
                itr->second -= diff;
                ++itr;
            }
        }
    }
};
 
CreatureAI* GetAI_npc_training_dummy(Creature* pCreature)
{
    return new npc_training_dummyAI(pCreature);
}

void AddSC_npc_scripts()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "training_dummy";
    pNewScript->GetAI = &GetAI_npc_training_dummy;
    pNewScript->RegisterSelf();
}