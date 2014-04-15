#include "ScriptPCH.h"
#include <stdio.h>
#include <stdlib.h>
#include "CityConquestMgr.h"

static int entry;

struct city_conquest_spawnerAI : public ScriptedAI
{
    city_conquest_spawnerAI(Creature *c) : ScriptedAI(c) 
	{
		CityConquest.RegisterCreature(me, 2);
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

	void SummonedCreatureDespawn(Creature *pSummoned)
    {
		QueryResult_AutoPtr result 
			= WorldDatabase.PQuery("SELECT city_id FROM city_capture_bosses WHERE  "
			//                             0               
			"spawner_entry = %u", entry);

		if (result)
		{
			Field *fields = result->Fetch();
			CityConquest.EndSiege(fields[0].GetInt32());
		}

    }


    void UpdateAI(const uint32 uiDiff)
    {
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_city_conquest_spawner(Creature* pCreature)
{
    return new city_conquest_spawnerAI (pCreature);
}

bool GossipHello_city_conquest_spawner(Player *player, Creature *_Creature)
{
	return true;
}

bool GossipSelect_city_conquest_spawner(Player *player, Creature *_creature, uint32 sender, uint32 action )
{
	return true;
}

void AddSC_city_conquest_spawner()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "city_conquest_spawner";
    newscript->GetAI = &GetAI_city_conquest_spawner;
	newscript->pGossipHello = &GossipHello_city_conquest_spawner;
    newscript->pGossipSelect = &GossipSelect_city_conquest_spawner;
    newscript->RegisterSelf();
}
