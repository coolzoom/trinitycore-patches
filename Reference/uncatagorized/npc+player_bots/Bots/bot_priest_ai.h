#include "bot_ai.h"


#define FEAR_WARD   6346

#define SPELL_PW_SHIELD           SPELL_PW_SHIELD_A[SPELL_LEVEL]
//#define SPELL_DIVINE_SPIRIT     14818

#define SPELL_FORTITUDE           SPELL_FORTITUDE_A[SPELL_LEVEL]
#define SPELL_HEAL                SPELL_HEAL_A[SPELL_LEVEL]
#define SPELL_RENEW               SPELL_RENEW_A[SPELL_LEVEL]
#define SPELL_FADE                SPELL_FADE_A[SPELL_LEVEL]
#define SPELL_RESURRECTION        SPELL_RESURRECTION_A[SPELL_LEVEL]
//define SPELL_VAMPIRIC_EMBRACE
//#define SPELL_INNER_FOCUS       14751

//BUFFS
#define SPELL_INNER_FIRE          SPELL_INNER_FIRE_A[SPELL_LEVEL]
#define SPELL_PRAYER_OF_SHADOW    SPELL_PRAYER_OF_SHADOW_A[SPELL_LEVEL]
#define DIVINE_SPIRIT               DIVINE_SPIRIT_A[SPELL_LEVEL]
//#define SPELL_TOUCH_OF_WEAKNESS 19265 //rank 5

uint32 SPELL_FORTITUDE_A[] = { 1243, 1244, 1245, 2791, 10937, 10938, 25389, 25389, 25389 };
uint32 SPELL_RENEW_A[] = { 8362, 11640, 6075, 6077, 10927, 10928, 25315, 37260, 37260 };
uint32 SPELL_HEAL_A[] = { 29170, 29170, 2055, 6064, 10963, 10964, 10965, 25213, 25213 };
uint32 SPELL_PW_SHIELD_A[] = { 17, 592, 3747, 6066, 10899, 10900, 10901, 25218, 25218 };
uint32 SPELL_FADE_A[] = { 586, 586, 586, 586, 586, 586, 586, 586, 586 };
uint32 SPELL_PRAYER_OF_SHADOW_A[] = { 0, 0, 0, 0, 0, 27683, 27683, 39374, 39374, 39374 };

uint32 SPELL_INNER_FIRE_A[] = { 588, 7128, 602, 1006, 10951, 10952, 25431, 25431, 48040, 48040 };
uint32 DIVINE_SPIRIT_A[] = {0, 0, 0, 14752, 14818, 14819, 27841, 25312, 48073, 48073};

uint32 SPELL_RESURRECTION_A[] = { 2006, 2006, 2006, 2010, 10880, 10881, 20770, 25435, 25435 };
