#include "ScriptPCH.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../game/CityConquestMgr.h"

static int entry;

struct city_conquest_bossAI : public ScriptedAI
{
    city_conquest_bossAI(Creature *c) : ScriptedAI(c) 
	{
		CityConquest.RegisterCreature(me, 1);
		entry = me->GetEntry();
	}

    void Reset()
    {

    }

    void EnterCombat(Unit* pWho)
    {

    }

    void EnterEvadeMode()
    {
    }

    void UpdateAI(const uint32 uiDiff)
    {
        DoMeleeAttackIfReady();
    }

	void JustDied(Unit* Killer)
    {
		QueryResult_AutoPtr result 
			= WorldDatabase.PQuery("SELECT city_id, boss_entry_A, boss_entry_H FROM city_capture_bosses WHERE boss_entry_A = %u OR boss_entry_H = %u OR "
			//                             0        1             2        
			"spawner_entry = %u", entry, entry, entry);

		if (result)
		{
			Field *fields = result->Fetch();
			Cities::iterator l;
			for (l = CityConquest.cities.begin(); l != CityConquest.cities.end(); ++l)
			{
				City *ct = *l;
				if (ct->id == fields[0].GetInt32())
				{
					if (entry == fields[2].GetInt32() || entry == fields[1].GetInt32())
					{
						CityConquest.SwitchFaction(ct->id);
						return;
					}
				}
			}
		}
    }
};

CreatureAI* GetAI_city_conquest_boss(Creature* pCreature)
{
    return new city_conquest_bossAI (pCreature);
}

void AddSC_city_conquest_boss()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "city_conquest_boss";
    newscript->GetAI = &GetAI_city_conquest_boss;
    newscript->RegisterSelf();
}
