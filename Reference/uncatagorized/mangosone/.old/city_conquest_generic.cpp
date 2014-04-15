#include "ScriptPCH.h"
#include "CityConquestMgr.h"

struct city_conquest_genericAI : public ScriptedAI
{
    city_conquest_genericAI(Creature *c) : ScriptedAI(c) 
	{
		CityConquest.RegisterCreature(me, 0);
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
};

CreatureAI* GetAI_city_conquest_generic(Creature* pCreature)
{
    return new city_conquest_genericAI (pCreature);
}

void AddSC_city_conquest_generic()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "city_conquest_generic";
    newscript->GetAI = &GetAI_city_conquest_generic;
    newscript->RegisterSelf();
}
