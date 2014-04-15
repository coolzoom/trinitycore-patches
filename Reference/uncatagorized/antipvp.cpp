 #include "ScriptedPch.h"

#define SPELL_GripOfTheLegion 31972
#define SPELL_FingerOfDeath 31984

struct CustomAntiPvPGuardAI : public ScriptedAI
{
    CustomAntiPvPGuardAI(Creature *c) : ScriptedAI(c)
    {
        Reset();
    }

    uint32 GripOfTheLegion_timer;
    uint32 FingerOfDeath_timer;


    void Reset()
    {
        GripOfTheLegion_timer = 1; // This spell will be casted 1 milisecond after Guard enter combat
        FingerOfDeath_timer = 100; // This spell will be casted 100 milisecond  after Guard enter combat
    }
    
    
    void EnterCombat(Unit* Who)
    {
        // EMPTY, add something if you want
    }

    void MoveInLineOfSight(Unit* Who) // This function is important for your guard.
    {
        float atkDist = me->GetDistance(Who);
        if (!me->getVictim() && me->canAttack(Who) && (Who->IsHostileToPlayers() || me->IsHostileTo(Who) ) && Who->isInAccessiblePlaceFor(me) && atkDist <= 35.0f)
        {
                me->AI()->AttackStart(Who);
        }
    }


    void KilledUnit(Unit* Who)
    {
        Reset(); // Reset spell timers after target is killed, but perhaps there are more enemies
		me->CombatStop();// Stop combat mode
	    me->DeleteThreatList();// clear thread list 
	}


    void JustDied(Unit* Who)
    {
        // EMPTY, add something if you want
    }


    void UpdateAI(const uint32 uiDiff)
    {
        if (!me->getVictim())
        {
                // EMPTY, add something if you want
        }


        if (!UpdateVictim())
            return;

            {
                DoCast(me->getVictim(), SPELL_GripOfTheLegion);
                GripOfTheLegion_timer = 6010;
            }
                GripOfTheLegion_timer -= uiDiff;
            {
                DoCast(me->getVictim(), SPELL_FingerOfDeath);
                FingerOfDeath_timer = 1100;
            }

            FingerOfDeath_timer -= uiDiff;
            DoMeleeAttackIfReady();
    }

};

CreatureAI* GetAI_CustomAntiPvPGuard(Creature* pCreature)
{
    return new CustomAntiPvPGuardAI (pCreature);
}

void AddSC_CustomAntiPvPGuard()
{
    Script* newscript;

    newscript = new Script;
	newscript->Name = "custom_anti_pvp_guard";
    newscript->GetAI = &GetAI_CustomAntiPvPGuard;
    newscript->RegisterSelf();
}
