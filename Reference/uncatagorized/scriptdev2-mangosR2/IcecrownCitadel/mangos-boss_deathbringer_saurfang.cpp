/* Copyright (C) 2006 - 2012 ScriptDev2 <http://www.scriptdev2.com/>
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

/* ScriptData
SDName: boss_deathbringer_saurfang
SD%Complete: 99%
SDComment: Events - intro and outro missing for alliance version
SDCategory: Icecrown Citadel
EndScriptData */

#include "precompiled.h"
#include "icecrown_citadel.h"

// talks
enum
{
    SAY_AGGRO                   = -1631028,
    SAY_FALLENCHAMPION          = -1631029,
    SAY_BLOODBEASTS             = -1631030,
    SAY_SLAY_1                  = -1631031,
    SAY_SLAY_2                  = -1631032,
    SAY_BERSERK                 = -1631033,
    SAY_DEATH                   = -1631034,
    SAY_INTRO_ALLY_0            = -1631035,
    SAY_INTRO_ALLY_1            = -1631036,
    SAY_INTRO_ALLY_2            = -1631037,
    SAY_INTRO_ALLY_3            = -1631038,
    SAY_INTRO_ALLY_4            = -1631039,
    SAY_INTRO_ALLY_5            = -1631040,
    SAY_INTRO_HORDE_1           = -1631041,
    SAY_INTRO_HORDE_2           = -1631042,
    SAY_INTRO_HORDE_3           = -1631043,
    SAY_INTRO_HORDE_4           = -1631044,
    SAY_INTRO_HORDE_5           = -1631045,
    SAY_INTRO_HORDE_6           = -1631046,
    SAY_INTRO_HORDE_7           = -1631047,
    SAY_INTRO_HORDE_8           = -1631048,
    SAY_INTRO_HORDE_9           = -1631049,
    SAY_OUTRO_ALLY_1            = -1631050,
    SAY_OUTRO_ALLY_2            = -1631051,
    SAY_OUTRO_ALLY_3            = -1631052,
    SAY_OUTRO_ALLY_4            = -1631053,
    SAY_OUTRO_ALLY_5            = -1631054,
    SAY_OUTRO_ALLY_6            = -1631055,
    SAY_OUTRO_ALLY_7            = -1631056,
    SAY_OUTRO_ALLY_8            = -1631057,
    SAY_OUTRO_ALLY_9            = -1631058,
    SAY_OUTRO_ALLY_10           = -1631059,
    SAY_OUTRO_ALLY_11           = -1631060,
    SAY_OUTRO_ALLY_12           = -1631061,
    SAY_OUTRO_ALLY_13           = -1631062,
    SAY_OUTRO_ALLY_14           = -1631063,
    SAY_OUTRO_ALLY_15           = -1631064,
    SAY_OUTRO_ALLY_16           = -1631065,
    SAY_OUTRO_HORDE_1           = -1631066,
    SAY_OUTRO_HORDE_2           = -1631067,
    SAY_OUTRO_HORDE_3           = -1631068,
    SAY_OUTRO_HORDE_4           = -1631069,
};

enum
{
        // Blood Power
        SPELL_BLOOD_POWER                       = 72371,
        SPELL_BLOOD_LINK_BEAST                  = 72176, // proc aura for Blood Beasts
        SPELL_BLOOD_LINK                        = 72202, // cast on Saurfang to give 1 Blood Power

        // Mark of the Fallen Champion
        SPELL_MARK_OF_FALLEN_CHAMPION           = 72256, // proc on melee hit, dmg to marked targets
        SPELL_MARK_OF_FALLEN_CHAMPION_DEBUFF    = 72293, // proc on death - heal Saurfang
        SPELL_REMOVE_MARKS                      = 72257,

        // Rune of Blood
        SPELL_RUNE_OF_BLOOD                     = 72408, // cast on self on aggro
        SPELL_RUNE_OF_BLOOD_DEBUFF              = 72410,

        // Blood Nova
        SPELL_BLOOD_NOVA                        = 72378,

        // Boiling Blood
        SPELL_BOILING_BLOOD                     = 72385,

        // Blood Beasts
        SPELL_CALL_BLOOD_BEAST_1                = 72172,
        SPELL_CALL_BLOOD_BEAST_2                = 72173,
        SPELL_CALL_BLOOD_BEAST_3                = 72356,
        SPELL_CALL_BLOOD_BEAST_4                = 72357,
        SPELL_CALL_BLOOD_BEAST_5                = 72358,

        SPELL_SCENT_OF_BLOOD                    = 72769,
        SPELL_SCENT_OF_BLOOD_TRIGGERED          = 72771, // doesn't trigger, so cast in script...
        SPELL_RESISTANT_SKIN                    = 72723,

        // enrage
        SPELL_BERSERK                           = 26662,
        SPELL_FRENZY                            = 72737,

        //summons
        NPC_BLOOD_BEAST                         = 38508
};

enum Equipment
{
    EQUIP_MAIN           = 50798,
    EQUIP_OFFHAND        = EQUIP_NO_CHANGE,
    EQUIP_RANGED         = EQUIP_NO_CHANGE,
    EQUIP_DONE           = EQUIP_NO_CHANGE,
};

enum SaurfangEvent
{
    NPC_OVERLORD_SAURFANG       = 37187,
    NPC_KORKRON_REAVER          = 37920,

    NPC_MURADIN_BRONZEBEARD     = 37200,
    NPC_ALLIANCE_MASON          = 37902,

    SPELL_VEHICLE_HARDCODED     = 46598, // Deathbringer enters Overlord
};

// positions
float fPositions[12][4] =
{
    {-468.05f, 2211.69f, 541.11f, 3.16f}, // Deathbringer teleport point
    {-491.30f, 2211.35f, 541.11f, 3.16f}, // Deathbringer dest point
    {-559.82f, 2211.29f, 539.30f, 6.28f}, // main npc summon/despawn point
    {-561.87f, 2215.94f, 539.30f, 6.28f}, // guard npc1 summon/despawn point
    {-560.17f, 2214.17f, 539.30f, 6.28f}, // guard npc2 summon/despawn point
    {-560.17f, 2207.71f, 539.30f, 6.28f}, // guard npc3 summon/despawn point
    {-561.87f, 2205.68f, 539.30f, 6.28f}, // guard npc4 summon/despawn point
    {-534.82f, 2211.29f, 539.30f, 6.28f}, // main npc first move
    {-536.87f, 2215.94f, 539.30f, 6.28f}, // guard npc1 first move
    {-535.17f, 2214.17f, 539.30f, 6.28f}, // guard npc2 first move
    {-535.17f, 2207.71f, 539.30f, 6.28f}, // guard npc3 first move
    {-536.87f, 2205.68f, 539.30f, 6.28f} // guard npc4 first move
};

// Event handler
struct MANGOS_DLL_DECL boss_deathbringer_saurfang_eventAI : public base_icc_bossAI
{
    boss_deathbringer_saurfang_eventAI(Creature* pCreature) : base_icc_bossAI(pCreature)
    {
        m_uiEventStep = 0;
        m_uiNextEventTimer = 0;

        m_bIsAlliance = true;

        m_bTeleported = false;
        m_bIsIntroStarted = false;
        m_bIsIntroFinished = false; // if true - boss is now ready to fight untill death - outro event
        m_bIsOutroStarted = false;

        m_guidNpc.Clear();
        m_lGuards.clear();
    }

    uint32 m_uiNextEventTimer;
    uint32 m_uiEventStep;

    bool m_bIsAlliance;
    bool m_bTeleported;
    bool m_bIsIntroStarted;
    bool m_bIsIntroFinished;
    bool m_bIsOutroStarted;

    ObjectGuid m_guidNpc;
    ObjectGuid m_guidKiller;
    GUIDList m_lGuards;

    virtual void ResetFight() {}

    void Reset()
    {
        if (m_bIsIntroFinished)
        {
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
        }

        ResetFight();
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (!m_bTeleported && pWho->GetTypeId() == TYPEID_PLAYER && !((Player*)pWho)->isGameMaster())
        {
            // teleport behind door
            m_creature->NearTeleportTo(fPositions[0][0], fPositions[0][1], fPositions[0][2], fPositions[0][3]);
            m_bTeleported = true;
        }

        if (m_bTeleported && !m_bIsIntroStarted && pWho->GetTypeId() == TYPEID_PLAYER && !((Player*)pWho)->isGameMaster() && m_creature->GetDistance2d(pWho) < 50.0f)
        {
            m_bIsAlliance = false; //((Player*)pWho)->GetTeam() == ALLIANCE;
            DoSummonEventNpcs();
            m_bIsIntroStarted = true;
            NextStep(0);
        }
    }

    void DamageTaken(Unit *pDealer, uint32 &uiDamage)
    {
        if (m_bIsOutroStarted)
        {
            uiDamage = 0;
            return;
        }

        if (uiDamage >= m_creature->GetHealth())
        {
            m_bIsOutroStarted = true;
            uiDamage = 0;
            m_creature->RemoveAllAuras();
            m_guidKiller = pDealer->GetObjectGuid();
            DoFakeDeath();
            m_uiEventStep = 0;
        }
    }

    void DoSummonEventNpcs()
    {
        // main npc
        if (Creature *pTmp = m_creature->SummonCreature(m_bIsAlliance ? NPC_MURADIN_BRONZEBEARD : NPC_OVERLORD_SAURFANG, fPositions[2][0], fPositions[2][1], fPositions[2][2], fPositions[2][3], TEMPSUMMON_MANUAL_DESPAWN, 0))
            m_guidNpc = pTmp->GetObjectGuid();
        // 4 adds
        if (Creature *pTmp = m_creature->SummonCreature(m_bIsAlliance ? NPC_ALLIANCE_MASON : NPC_KORKRON_REAVER, fPositions[3][0], fPositions[3][1], fPositions[3][2], fPositions[3][3], TEMPSUMMON_MANUAL_DESPAWN, 0))
            m_lGuards.push_back(pTmp->GetObjectGuid());
        if (Creature *pTmp = m_creature->SummonCreature(m_bIsAlliance ? NPC_ALLIANCE_MASON : NPC_KORKRON_REAVER, fPositions[4][0], fPositions[4][1], fPositions[4][2], fPositions[4][3], TEMPSUMMON_MANUAL_DESPAWN, 0))
            m_lGuards.push_back(pTmp->GetObjectGuid());
        if (Creature *pTmp = m_creature->SummonCreature(m_bIsAlliance ? NPC_ALLIANCE_MASON : NPC_KORKRON_REAVER, fPositions[5][0], fPositions[5][1], fPositions[5][2], fPositions[5][3], TEMPSUMMON_MANUAL_DESPAWN, 0))
            m_lGuards.push_back(pTmp->GetObjectGuid());
        if (Creature *pTmp = m_creature->SummonCreature(m_bIsAlliance ? NPC_ALLIANCE_MASON : NPC_KORKRON_REAVER, fPositions[6][0], fPositions[6][1], fPositions[6][2], fPositions[6][3], TEMPSUMMON_MANUAL_DESPAWN, 0))
            m_lGuards.push_back(pTmp->GetObjectGuid());
    }

    Creature* GetMainNpc()
    {
        return m_creature->GetMap()->GetCreature(m_guidNpc);
    }

    void DoFakeDeath()
    {
        m_creature->InterruptNonMeleeSpells(false);
        m_creature->SetHealth(1);
        m_creature->StopMoving();
        m_creature->ClearComboPointHolders();
        m_creature->RemoveAllAurasOnDeath();
        m_creature->ModifyAuraState(AURA_STATE_HEALTHLESS_20_PERCENT, false);
        m_creature->ModifyAuraState(AURA_STATE_HEALTHLESS_35_PERCENT, false);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->ClearAllReactives();
        m_creature->GetMotionMaster()->Clear();
        m_creature->GetMotionMaster()->MoveIdle();
        m_creature->SetStandState(UNIT_STAND_STATE_DEAD);

        // like in JustDied()
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SAURFANG, DONE);

        DoScriptText(SAY_DEATH, m_creature);
        DoCastSpellIfCan(m_creature, SPELL_REMOVE_MARKS, CAST_TRIGGERED);
    }

    void NextStep(uint32 uiTime = 1000)
    {
        ++m_uiEventStep;
        m_uiNextEventTimer = uiTime;
    }

    virtual void UpdateFightAI(const uint32 uiDiff) {}

    void UpdateAI(const uint32 uiDiff)
    {
        // INTRO
        if (m_bIsIntroStarted && !m_bIsIntroFinished)
        {
            if (m_bIsAlliance)
            {
                // **************
                // ALLIANCE INTRO
                // **************
                if (m_uiNextEventTimer <= uiDiff)
                {
                    switch (m_uiEventStep)
                    {
                        case 0:
                        {
                            break;
                        }
                        default:
                            break;
                    }
                }
                else
                    m_uiNextEventTimer -= uiDiff;
            }
            else
            {
                // ***********
                // HORDE INTRO
                // ***********
                if (m_uiNextEventTimer <= uiDiff)
                {
                    switch (m_uiEventStep)
                    {
                        case 0:
                        {
                            break;
                        }
                        case 1:
                        {
                            m_pInstance->DoUseDoorOrButton(GO_SAURFANG_DOOR, 0, false);
                            m_creature->GetMotionMaster()->MovePoint(0, fPositions[1][0], fPositions[1][1], fPositions[1][2]);
                            NextStep(1000);
                            break;
                        }
                        case 2:
                        {
                            m_pInstance->DoUseDoorOrButton(GO_SAURFANG_DOOR, 0, true);
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_INTRO_HORDE_1, pTmp);
                                pTmp->GetMotionMaster()->MovePoint(0, fPositions[7][0], fPositions[7][1], fPositions[7][2]);
                            }
                            // move guards
                            int8 n = 8;
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                    pTmp->GetMotionMaster()->MovePoint(0, fPositions[n][0], fPositions[n][1], fPositions[n][2]);
                                ++n;
                            }
                            NextStep(6000);
                            break;
                        }
                        case 3:
                        {
                            DoScriptText(SAY_INTRO_HORDE_2, m_creature);
                            NextStep(13000);
                            break;
                        }
                        case 4:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_INTRO_HORDE_3, pTmp);
                            }
                            NextStep(7000);
                            break;
                        }
                        case 5:
                        {
                            DoScriptText(SAY_INTRO_HORDE_4, m_creature);
                            NextStep(11000);
                            break;
                        }
                        case 6:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_INTRO_HORDE_5, pTmp);
                            }
                            NextStep(16000);
                            break;
                        }
                        case 7:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_INTRO_HORDE_6, pTmp);
                            }
                            NextStep(15000);
                            break;
                        }
                        case 8:
                        {
                            if (Creature *pTmp = GetMainNpc())
                                DoScriptText(SAY_INTRO_HORDE_7, pTmp);

                            NextStep(3000);
                            break;
                        }
                        case 9:
                        {
                            float x, y, z;
                            m_creature->GetPosition(x, y, z);

                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_INTRO_HORDE_8, pTmp);
                                pTmp->SetWalk(false);
                                pTmp->GetMotionMaster()->MovePoint(0, x, y, z);
                            }
                            // move guards
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                {
                                    pTmp->SetWalk(false);
                                    pTmp->GetMotionMaster()->MovePoint(0, x, y, z);
                                }
                            }
                            NextStep(2000);
                            break;
                        }
                        case 10:
                        {
                            float x, y, z;
                            // npcs float in air
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->SetWalk(true);
                                pTmp->SetSpeedRate(MOVE_WALK, 3.0f);
                                pTmp->SetLevitate(true);
                                pTmp->GetPosition(x, y, z);
                                pTmp->GetMotionMaster()->MovePoint(0, x, y, z + frand(5.0f, 7.0f));
                                pTmp->HandleEmoteState(EMOTE_STATE_STRANGULATE);
                            }
                            // move guards
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                {
                                    pTmp->SetWalk(true);
                                    pTmp->SetSpeedRate(MOVE_WALK, 3.0f);
                                    pTmp->SetLevitate(true);
                                    pTmp->GetPosition(x, y, z);
                                    pTmp->GetMotionMaster()->MovePoint(0, x, y, z + frand(5.0f, 7.0f));
                                    pTmp->HandleEmoteState(EMOTE_STATE_STRANGULATE);
                                }
                            }
                            DoScriptText(SAY_INTRO_HORDE_9, m_creature);
                            NextStep(10000);
                            break;
                        }
                        case 11:
                        {
                            m_bIsIntroFinished = true;

                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                            m_creature->SetInCombatWithZone();

                            NextStep();
                            break;
                        }
                        case 12:
                        {
                            // fight is in progress
                            break;
                        }
                        default:
                            break;
                    }
                }
                else
                    m_uiNextEventTimer -= uiDiff;
            }

            return;
        }
        // END OF INTRO

        // OUTRO
        if (m_bIsOutroStarted)
        {
            if (m_bIsAlliance)
            {
                // **************
                // ALLIANCE OUTRO
                // **************
                if (m_uiNextEventTimer <= uiDiff)
                {
                    switch (m_uiEventStep)
                    {
                        case 0:
                        {
                            break;
                        }
                        default:
                            break;
                    }
                }
                else
                    m_uiNextEventTimer -= uiDiff;
            }
            else
            {
                // ***********
                // HORDE OUTRO
                // ***********
                if (m_uiNextEventTimer <= uiDiff)
                {
                    switch (m_uiEventStep)
                    {
                        case 0:
                        {
                            float x, y, z;

                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->HandleEmote(EMOTE_ONESHOT_NONE);
                                pTmp->GetPosition(x, y, z);
                                m_creature->UpdateAllowedPositionZ(x, y, z);
                                pTmp->GetMotionMaster()->MovePoint(0, x, y, z);
                            }
                            // move guards
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                {
                                    pTmp->GetPosition(x, y, z);
                                    m_creature->UpdateAllowedPositionZ(x, y, z);
                                    pTmp->GetMotionMaster()->MovePoint(0, x, y, z);
                                    pTmp->HandleEmote(EMOTE_ONESHOT_NONE);
                                }
                            }
                            NextStep(1000);
                            break;
                        }
                        case 1:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->SetLevitate(false);
                                pTmp->SetSpeedRate(MOVE_WALK, 1.0f);

                                for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                                {
                                    if (Creature *pGuard = m_creature->GetMap()->GetCreature(*i))
                                    {
                                        pGuard->SetLevitate(false);
                                        pGuard->SetSpeedRate(MOVE_WALK, 1.0f);
                                        pGuard->GetMotionMaster()->MoveFollow(pTmp, frand(2.0f, 5.0f), frand(M_PI_F / 2, 1.5f * M_PI_F));
                                    }
                                }
                            }
                            NextStep(1000);
                            break;
                        }
                        case 2:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_OUTRO_HORDE_1, pTmp);
                                pTmp->HandleEmote(EMOTE_ONESHOT_KNEEL);
                            }
                            NextStep(3000);
                            break;
                        }
                        case 3:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                float x, y, z;
                                m_creature->GetContactPoint(pTmp, x, y, z, 1.0f);
                                pTmp->GetMotionMaster()->MovePoint(0, x, y, z);
                            }
                            NextStep(0);
                            break;
                        }
                        case 4:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                // wait until Overlord comes to Deathbringer
                                if (!pTmp->IsWithinDist(m_creature, 2.0f))
                                    return;

                                pTmp->StopMoving();
                                pTmp->SetFacingToObject(m_creature);
                            }
                            NextStep(1000);
                            break;
                        }
                        case 5:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_OUTRO_HORDE_2, pTmp);
                                pTmp->HandleEmote(EMOTE_ONESHOT_KNEEL);
                                // Overlord should take Deathbringer on hands (vehicle ride?)
                            }
                            NextStep(3000);
                            break;
                        }
                        case 6:
                        {
                            // take deathbringer
                            if (Creature *pTmp = GetMainNpc())
                                DoScriptText(SAY_OUTRO_HORDE_3, pTmp);

                            NextStep(11000);
                            break;
                        }
                        case 7:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_OUTRO_HORDE_4, pTmp);
                                pTmp->GetMotionMaster()->MovePoint(0, fPositions[2][0], fPositions[2][1], fPositions[2][2]);
                            }
                            NextStep();
                            break;
                        }
                        case 8:
                        {
                            // wait until coming to gunship boarding place
                            if (Creature *pTmp = GetMainNpc())
                            {
                                if (!pTmp->IsWithinDist2d(fPositions[2][0], fPositions[2][1], 3.0f))
                                    return;

                                pTmp->ForcedDespawn();
                                for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                                {
                                    if (Creature *pGuard = m_creature->GetMap()->GetCreature(*i))
                                        pGuard->ForcedDespawn();
                                }
                            }

                            Unit *pKiller = m_creature;

                            if (m_pInstance)
                            {
                                if (Unit *pTmp = m_creature->GetMap()->GetUnit(m_guidKiller))
                                    pKiller = pTmp;
                            }

                            if (pKiller)
                                pKiller->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);

                            return;
                        }
                    }
                }
                else
                    m_uiNextEventTimer -= uiDiff;
            }
            return;
        }

        // fight
        UpdateFightAI(uiDiff);
    }
};

struct MANGOS_DLL_DECL boss_deathbringer_saurfangAI : public boss_deathbringer_saurfang_eventAI
{
    boss_deathbringer_saurfangAI(Creature* pCreature) : boss_deathbringer_saurfang_eventAI(pCreature)
    {
        m_powerBloodPower = m_creature->getPowerType(); // don't call this function multiple times in script
        ResetFight();
    }

    uint32 m_uiRuneOfBloodTimer;
    uint32 m_uiBoilingBloodTimer;
    uint32 m_uiBloodNovaTimer;
    uint32 m_uiBloodBeastsTimer;
    uint32 m_uiScentOfBloodTimer;
    uint32 m_uiBerserkTimer;

    bool m_bIsFrenzied;

    Powers m_powerBloodPower;

    void ResetFight()
    {
        m_uiRuneOfBloodTimer    = 20000;
        m_uiBoilingBloodTimer   = urand(10000, 35000);
        m_uiBloodNovaTimer      = urand(16000, 35000);
        m_uiBloodBeastsTimer    = 40000;
        m_uiScentOfBloodTimer   = 47000; // 5 seconds after beasts engage in combat
        m_uiBerserkTimer        = (m_bIsHeroic ? 6 : 8) * MINUTE * IN_MILLISECONDS;

        m_bIsFrenzied = false;

        m_creature->SetPower(m_powerBloodPower, 0);
    }

    void Aggro(Unit *pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SAURFANG, IN_PROGRESS);

        DoScriptText(SAY_AGGRO, m_creature);

        SetEquipmentSlots(false, EQUIP_MAIN, EQUIP_OFFHAND, EQUIP_RANGED);

        DoCastSpellIfCan(m_creature, SPELL_BLOOD_POWER, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_RUNE_OF_BLOOD, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_MARK_OF_FALLEN_CHAMPION, CAST_TRIGGERED);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SAURFANG, FAIL);
    }

    // used for unlocking bugged encounter
    void JustDied(Unit *pKiller)
    {
        if (m_pInstance && m_pInstance->GetData(TYPE_SAURFANG) != DONE)
            m_pInstance->SetData(TYPE_SAURFANG, DONE);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim->GetTypeId() == TYPEID_PLAYER)
            DoScriptText(SAY_SLAY_1 - urand(0,1), m_creature, pVictim);
    }

    void JustSummoned(Creature *pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_BLOOD_BEAST)
        {
            pSummoned->CastSpell(pSummoned, SPELL_BLOOD_LINK_BEAST, true);
            pSummoned->CastSpell(pSummoned, SPELL_RESISTANT_SKIN, true);
            pSummoned->setFaction(m_creature->getFaction());
        }
    }

    Player* SelectRandomPlayerForMark()
    {
        Player *pResult = NULL;
        GUIDList lPlayers;
        ThreatList const &threatlist = m_creature->getThreatManager().getThreatList();

        if (!threatlist.empty())
        {
            for (ThreatList::const_iterator itr = threatlist.begin();itr != threatlist.end(); ++itr)
            {
                ObjectGuid const &guid = (*itr)->getUnitGuid();
                if (guid.IsPlayer() && guid != m_creature->getVictim()->GetObjectGuid()) // exclude current target
                {
                    // check if player already has the mark
                    if (Player *pPlayer = m_creature->GetMap()->GetPlayer(guid))
                    {
                        if (!pPlayer->HasAura(SPELL_MARK_OF_FALLEN_CHAMPION_DEBUFF))
                            lPlayers.push_back(guid);
                    }
                }
            }
        }

        if (!lPlayers.empty())
        {
            GUIDList::iterator i = lPlayers.begin();
            uint32 max = uint32(lPlayers.size() - 1);

            if (max > 0)
                std::advance(i, urand(0, max));

            pResult = m_creature->GetMap()->GetPlayer(*i);
        }

        // last option - current target
        if (!pResult)
        {
            Unit *pVictim = m_creature->getVictim();
            if (pVictim && pVictim->GetTypeId() == TYPEID_PLAYER && !pVictim->HasAura(SPELL_MARK_OF_FALLEN_CHAMPION_DEBUFF))
                pResult = (Player*)pVictim;
        }

        return pResult;
    }

    void UpdateFightAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Mark of the Fallen Champion
        if (m_creature->GetPower(m_powerBloodPower) >= 100)
        {
            if (Player *pTarget = SelectRandomPlayerForMark())
            {
                if (DoCastSpellIfCan(pTarget, SPELL_MARK_OF_FALLEN_CHAMPION_DEBUFF) == CAST_OK)
                {
                    m_creature->SetPower(m_powerBloodPower, 0); // reset Blood Power
                    // decrease the buff
                    m_creature->RemoveAurasDueToSpell(72371);
                    int32 power = m_creature->GetPower(m_powerBloodPower);
                    m_creature->CastCustomSpell(m_creature, 72371, &power, &power, NULL, true);
                    DoScriptText(SAY_FALLENCHAMPION, m_creature);
                }
            }
        }

        // Frenzy (soft enrage)
        if (!m_bIsFrenzied)
        {
            if (m_creature->GetHealthPercent() <= 30.0f)
            {
                DoCastSpellIfCan(m_creature, SPELL_FRENZY, CAST_TRIGGERED);
                DoScriptText(SAY_BERSERK, m_creature);
                m_bIsFrenzied = true;
            }
        }

        // Berserk (hard enrage)
        if (m_uiBerserkTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_BERSERK) == CAST_OK)
            {
                DoScriptText(SAY_BERSERK, m_creature);
                m_uiBerserkTimer = (m_bIsHeroic ? 6 : 8) * MINUTE * IN_MILLISECONDS;
            }
        }
        else
            m_uiBerserkTimer -= uiDiff;

        // Rune of Blood
        if (m_uiRuneOfBloodTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_RUNE_OF_BLOOD_DEBUFF) == CAST_OK)
                m_uiRuneOfBloodTimer = 20000;
        }
        else
            m_uiRuneOfBloodTimer -= uiDiff;

        // Boiling Blood
        if (m_uiBoilingBloodTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_BOILING_BLOOD) == CAST_OK)
                m_uiBoilingBloodTimer = urand(10000, 35000);
        }
        else
            m_uiBoilingBloodTimer -= uiDiff;

        // Boiling Blood
        if (m_uiBloodNovaTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_BLOOD_NOVA) == CAST_OK)
                m_uiBloodNovaTimer = urand(16000, 35000);
        }
        else
            m_uiBloodNovaTimer -= uiDiff;

        // Call Blood Beasts
        if (m_uiBloodBeastsTimer <= uiDiff)
        {
            m_creature->CastSpell(m_creature, SPELL_CALL_BLOOD_BEAST_1, true);
            m_creature->CastSpell(m_creature, SPELL_CALL_BLOOD_BEAST_2, true);

            if (m_bIs25Man)
            {
                m_creature->CastSpell(m_creature, SPELL_CALL_BLOOD_BEAST_3, true);
                m_creature->CastSpell(m_creature, SPELL_CALL_BLOOD_BEAST_4, true);
                m_creature->CastSpell(m_creature, SPELL_CALL_BLOOD_BEAST_5, true);
            }

            m_uiBloodBeastsTimer  = 40000;

            if (m_bIsHeroic)
                m_uiScentOfBloodTimer = 7000; // 5 seconds after beasts engage in combat

            DoScriptText(SAY_BLOODBEASTS, m_creature);
        }
        else
            m_uiBloodBeastsTimer -= uiDiff;

        // Scent of Blood
        if (m_bIsHeroic)
        {
            if (m_uiScentOfBloodTimer <= uiDiff)
            {
                DoCastSpellIfCan(m_creature, SPELL_SCENT_OF_BLOOD, CAST_TRIGGERED);
                DoCastSpellIfCan(m_creature, SPELL_SCENT_OF_BLOOD_TRIGGERED, CAST_TRIGGERED);
                m_uiScentOfBloodTimer = 40000;
                // via DB
                m_creature->MonsterTextEmote("Deathbringer Saurfang's Blood Beasts gain the scent of blood!", m_creature->getVictim(), true);
            }
            else
                m_uiScentOfBloodTimer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_deathbringer_saurfang(Creature* pCreature)
{
    return new boss_deathbringer_saurfangAI(pCreature);
}

struct MANGOS_DLL_DECL  mob_blood_beastAI : public ScriptedAI
{
    mob_blood_beastAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiScentOfBloodTimer;
    uint32 m_uiReadyTimer;

    bool m_bIsReady;

    void Reset()
    {
        m_uiScentOfBloodTimer = 5000;

        m_uiReadyTimer = 2000;
        m_bIsReady = false;

        SetCombatMovement(false);
        m_creature->SetWalk(true);
    }

    void JustReachedHome()
    {
        m_creature->ForcedDespawn();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!m_bIsReady)
        {
            if (m_uiReadyTimer <= uiDiff)
            {
                m_bIsReady = true;
                SetCombatMovement(true);
                m_creature->SetInCombatWithZone();
                if (m_creature->getVictim())
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
            }
            else
                m_uiReadyTimer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_blood_beast(Creature* pCreature)
{
    return new mob_blood_beastAI(pCreature);
}

void AddSC_boss_deathbringer_saurfang()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_deathbringer_saurfang";
    newscript->GetAI = &GetAI_boss_deathbringer_saurfang;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_blood_beast";
    newscript->GetAI = &GetAI_mob_blood_beast;
    newscript->RegisterSelf();
}
