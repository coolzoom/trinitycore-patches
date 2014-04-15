#include "ScriptPCH.h"
#include "BookofKnowledge.h"

//extern SpellItemEnchantmentEntry const* GetEnchant(uint32 enchantid);
bool GossipHello_DXG_EnchantBook(Player* player, Creature* crea)
{
            if (player->isInCombat() || player->HasInvisibilityAura() || player->HasStealthAura())
            {
                            player->GetSession()->SendNotification("You can not use this book while in combat or in Invisible/Stealth!");
                            player->CLOSE_GOSSIP_MENU();
                            return true;
            }
            //player->GetSession()->SendNotification("You can not use this book at the moment!");
            //player->CLOSE_GOSSIP_MENU();
            //return true;

            player->ADD_GOSSIP_ITEM(3,  "Enchant 2H Weapons 15g", GOSSIP_SENDER_MAIN, 1);
            player->ADD_GOSSIP_ITEM(3,  "Enchant 1H Weapons 15g", GOSSIP_SENDER_MAIN, 2);
            if(player->getClass() == 1 || player->getClass() == 3 || player->getClass() == 4)
            {
            player->ADD_GOSSIP_ITEM(3,  "Enchant Ranged Weapons 15g", GOSSIP_SENDER_MAIN, 20);
            }
            player->ADD_GOSSIP_ITEM(3, "Enchant Chest 15g",       GOSSIP_SENDER_MAIN, 4);
            player->ADD_GOSSIP_ITEM(3, "Enchant Feet 15g",         GOSSIP_SENDER_MAIN, 5);
            player->ADD_GOSSIP_ITEM(3, "Enchant Hands 15g",       GOSSIP_SENDER_MAIN, 6);
            player->ADD_GOSSIP_ITEM(3, "Enchant Wrist 15g",       GOSSIP_SENDER_MAIN, 8);
            player->ADD_GOSSIP_ITEM(3, "Enchant Shield 15g",     GOSSIP_SENDER_MAIN, 10);
            player->ADD_GOSSIP_ITEM(3, "Enchant Rings 15g",       GOSSIP_SENDER_MAIN, 11);
            player->ADD_GOSSIP_ITEM(3, "Enchant Cloak 15g",       GOSSIP_SENDER_MAIN, 12); 
            player->ADD_GOSSIP_ITEM(3, "Enchant Head 15g",         GOSSIP_SENDER_MAIN, 14);
            player->ADD_GOSSIP_ITEM(3, "Enchant Legs 15g",         GOSSIP_SENDER_MAIN, 15);
            player->ADD_GOSSIP_ITEM(3, "Enchant Shoulder 15g",   GOSSIP_SENDER_MAIN, 16);
            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
            return true;
}
void AddEnchant(Player *pPlayer, Item *pItem, uint32 enchantid)
{
            if (!pPlayer || !pItem || !enchantid)
                            return;
            // remove old enchanting before applying new if equipped
            pPlayer->ApplyEnchantment(pItem, PERM_ENCHANTMENT_SLOT, false);
            pItem->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchantid, 0, 0);
            // add new enchanting if equipped
            pPlayer->ApplyEnchantment(pItem, PERM_ENCHANTMENT_SLOT, true);
            pPlayer->GetSession()->SendNotification("Your %s has now been enchanted for 15 gold", pItem->GetProto()->Name1);
}
bool GossipSelect_DXG_EnchantBook(Player* player, Creature* crea, uint32 sender, uint32 action)
{
            if (player->isInCombat() || player->HasInvisibilityAura() || player->HasStealthAura())
            {
                            player->GetSession()->SendNotification("You can not use this book while in combat or in Invis/Stealth!", player->GetGUID());
                            player->CLOSE_GOSSIP_MENU();
                            return true;
            }
            switch (action)
            {
            case 1000: // Home Page
                            {
                                            GossipHello_DXG_EnchantBook(player, crea);
                            }
                            break;
            case 1: // 2hand Weapon
                            {
                                            player->ADD_GOSSIP_ITEM(1,    "Savagery", GOSSIP_SENDER_MAIN, 30);
                                            //player->ADD_GOSSIP_ITEM(1,    "Adamantite Sharpening Stone", GOSSIP_SENDER_MAIN, 31);
                                            //player->ADD_GOSSIP_ITEM(1,    "Elemental Sharpening Stone", GOSSIP_SENDER_MAIN, 32);
                                            player->ADD_GOSSIP_ITEM(1,    "Major Agility", GOSSIP_SENDER_MAIN, 33);
                                            //player->ADD_GOSSIP_ITEM(1,    "Major Intellect", GOSSIP_SENDER_MAIN, 34);
                                            //player->ADD_GOSSIP_ITEM(1,    "Major Spirit", GOSSIP_SENDER_MAIN, 35);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
            case 2: // 1 Hand Weapon Page 1
                            {
                                            player->ADD_GOSSIP_ITEM(1,    "Deathfrost", GOSSIP_SENDER_MAIN, 36);
                                            player->ADD_GOSSIP_ITEM(1,    "Executioner", GOSSIP_SENDER_MAIN, 37);
                                            player->ADD_GOSSIP_ITEM(1,    "Greater Agility", GOSSIP_SENDER_MAIN, 38);
                                            player->ADD_GOSSIP_ITEM(1,    "Major Healing", GOSSIP_SENDER_MAIN, 39);
                                            player->ADD_GOSSIP_ITEM(1,    "Soulfrost", GOSSIP_SENDER_MAIN, 40);
                                            player->ADD_GOSSIP_ITEM(1,    "Sunfire", GOSSIP_SENDER_MAIN, 41);
                                            player->ADD_GOSSIP_ITEM(1,    "Mongoose", GOSSIP_SENDER_MAIN, 42);
                                            player->ADD_GOSSIP_ITEM(1,    "Spellsurge", GOSSIP_SENDER_MAIN, 43);
                                            player->ADD_GOSSIP_ITEM(1,    "Battlemaster", GOSSIP_SENDER_MAIN, 44);
                                            player->ADD_GOSSIP_ITEM(1,    "Major Spellpower", GOSSIP_SENDER_MAIN, 45);
                                            player->ADD_GOSSIP_ITEM(1,    "// Page 2 -->", GOSSIP_SENDER_MAIN, 3);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
            case 3: // 1 Hand Weapon Page 2
                            {
                                            player->ADD_GOSSIP_ITEM(1,    "Potency", GOSSIP_SENDER_MAIN, 46);
                                            player->ADD_GOSSIP_ITEM(1,    "Major Striking", GOSSIP_SENDER_MAIN, 47);
                                            player->ADD_GOSSIP_ITEM(1,    "Major Intellect", GOSSIP_SENDER_MAIN, 48);
                                            player->ADD_GOSSIP_ITEM(1,    "Mighty Spirit", GOSSIP_SENDER_MAIN, 49);
                                            player->ADD_GOSSIP_ITEM(1,    "Lifestealing", GOSSIP_SENDER_MAIN, 50);
                                            player->ADD_GOSSIP_ITEM(1,    "Crusader", GOSSIP_SENDER_MAIN, 51);
                                            player->ADD_GOSSIP_ITEM(1,    "Fiery Weapon", GOSSIP_SENDER_MAIN, 52);
                                            player->ADD_GOSSIP_ITEM(1,    "Adamantite Weapon Chain", GOSSIP_SENDER_MAIN, 53);
                                            player->ADD_GOSSIP_ITEM(1,    "Elemental Sharpening Stone", GOSSIP_SENDER_MAIN, 54);
                                            player->ADD_GOSSIP_ITEM(1,    "Adamantite Sharpening Stone", GOSSIP_SENDER_MAIN, 55);
                                            player->ADD_GOSSIP_ITEM(1,    "<-- Page 1 \\", GOSSIP_SENDER_MAIN, 2);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
            case 4:  // Chest.
                            {
                                            player->ADD_GOSSIP_ITEM(1, "Exceptional Stats", GOSSIP_SENDER_MAIN, 56);
                                            player->ADD_GOSSIP_ITEM(1, "Exceptional Health", GOSSIP_SENDER_MAIN, 57);
                                            player->ADD_GOSSIP_ITEM(1, "Greater Mana Restoration", GOSSIP_SENDER_MAIN, 58);
                                            player->ADD_GOSSIP_ITEM(1, "Major Resilience", GOSSIP_SENDER_MAIN, 59);
                                            player->ADD_GOSSIP_ITEM(1, "Defense", GOSSIP_SENDER_MAIN, 60);
                                            player->ADD_GOSSIP_ITEM(1, "Exceptional Mana", GOSSIP_SENDER_MAIN, 61);
                                            player->ADD_GOSSIP_ITEM(1, "Major Spirit", GOSSIP_SENDER_MAIN, 62);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
            case 5:  // Boots.
                            {
                                            player->ADD_GOSSIP_ITEM(1, "Surefooted", GOSSIP_SENDER_MAIN, 63);
                                            player->ADD_GOSSIP_ITEM(1, "Vitality", GOSSIP_SENDER_MAIN, 64);
                                            player->ADD_GOSSIP_ITEM(1, "Dexterity", GOSSIP_SENDER_MAIN, 65);
                                            //player->ADD_GOSSIP_ITEM(1, "Greater Spirit", GOSSIP_SENDER_MAIN, 66);
                                            //player->ADD_GOSSIP_ITEM(1, "Icewalker", GOSSIP_SENDER_MAIN, 67);
                                            player->ADD_GOSSIP_ITEM(1, "Fortitude", GOSSIP_SENDER_MAIN, 68);
                                            player->ADD_GOSSIP_ITEM(1, "Boar's Speed", GOSSIP_SENDER_MAIN, 69);
                                            player->ADD_GOSSIP_ITEM(1, "Cat's Swiftness", GOSSIP_SENDER_MAIN, 70);
                                            //player->ADD_GOSSIP_ITEM(1, "Nitro Boosts", GOSSIP_SENDER_MAIN, 71);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
            case 6: // Gloves Page 1
                            {
                                            player->ADD_GOSSIP_ITEM(1,    "Blasting", GOSSIP_SENDER_MAIN, 72);
                                            player->ADD_GOSSIP_ITEM(1,    "Assault", GOSSIP_SENDER_MAIN, 73);
                                            player->ADD_GOSSIP_ITEM(1,    "Major Healing", GOSSIP_SENDER_MAIN, 74);
                                            player->ADD_GOSSIP_ITEM(1,    "Major Spellpower", GOSSIP_SENDER_MAIN, 75);
                                            player->ADD_GOSSIP_ITEM(1,    "Major Strength", GOSSIP_SENDER_MAIN, 76);
                                            player->ADD_GOSSIP_ITEM(1,    "Superior Agility", GOSSIP_SENDER_MAIN, 77);
                                            //player->ADD_GOSSIP_ITEM(1,    "Exceptional Spellpower", GOSSIP_SENDER_MAIN, 78);
                                            player->ADD_GOSSIP_ITEM(1,    "Spellstrike", GOSSIP_SENDER_MAIN, 79);
                                            //player->ADD_GOSSIP_ITEM(1,    "Fire Power", GOSSIP_SENDER_MAIN, 80);
                                            //player->ADD_GOSSIP_ITEM(1,    "// Page 2 -->", GOSSIP_SENDER_MAIN, 7);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
            /*case 7: // Gloves Page 2
                            {
                                            player->ADD_GOSSIP_ITEM(1,    "Frost Power", GOSSIP_SENDER_MAIN, 81);
                                            player->ADD_GOSSIP_ITEM(1,    "Shadow Power", GOSSIP_SENDER_MAIN, 82);
                                            player->ADD_GOSSIP_ITEM(1,    "Threat", GOSSIP_SENDER_MAIN, 83);
                                            player->ADD_GOSSIP_ITEM(1,    "Minor Haste", GOSSIP_SENDER_MAIN, 84);
                                            player->ADD_GOSSIP_ITEM(1,    "Riding Skill", GOSSIP_SENDER_MAIN, 85);
                                            player->ADD_GOSSIP_ITEM(1,    "Reticulated Armor Webbing", GOSSIP_SENDER_MAIN, 86);
                                            player->ADD_GOSSIP_ITEM(1,    "Hyperspeed Accelerators", GOSSIP_SENDER_MAIN, 87);
                                            player->ADD_GOSSIP_ITEM(1,    "Hand-Mounted Pyro Rocket", GOSSIP_SENDER_MAIN, 88);
                                            player->ADD_GOSSIP_ITEM(1,    "<-- Page 1 \\", GOSSIP_SENDER_MAIN, 6);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;*/
            case 8: // Bracers Page 1
                            {
                                            player->ADD_GOSSIP_ITEM(1, "Assault", GOSSIP_SENDER_MAIN, 89);
                                            player->ADD_GOSSIP_ITEM(1, "Spirit", GOSSIP_SENDER_MAIN, 90);
                                            player->ADD_GOSSIP_ITEM(1, "Superior Healing", GOSSIP_SENDER_MAIN, 91);
                                            player->ADD_GOSSIP_ITEM(1, "Stats", GOSSIP_SENDER_MAIN, 92);
                                            player->ADD_GOSSIP_ITEM(1, "Major Intellect", GOSSIP_SENDER_MAIN, 93);
                                            player->ADD_GOSSIP_ITEM(1, "Restore Mana Prime", GOSSIP_SENDER_MAIN, 94);
                                            player->ADD_GOSSIP_ITEM(1, "Major Defense", GOSSIP_SENDER_MAIN, 95);
                                            player->ADD_GOSSIP_ITEM(1, "Brawn", GOSSIP_SENDER_MAIN, 96);
                                            player->ADD_GOSSIP_ITEM(1,    "// Page 2 -->", GOSSIP_SENDER_MAIN, 9);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
            case 9: // Bracers Page 2
                            {
                                            player->ADD_GOSSIP_ITEM(1, "Spellpower", GOSSIP_SENDER_MAIN, 97);
                                            player->ADD_GOSSIP_ITEM(1, "Fortitude", GOSSIP_SENDER_MAIN, 98);
                                            //player->ADD_GOSSIP_ITEM(1, "Fur Lining - Fire Resist", GOSSIP_SENDER_MAIN, 99);
                                            //player->ADD_GOSSIP_ITEM(1, "Fur Lining - Frost Resist", GOSSIP_SENDER_MAIN, 100);
                                            //player->ADD_GOSSIP_ITEM(1, "Fur Lining - Nature Resist", GOSSIP_SENDER_MAIN, 101);
                                            //player->ADD_GOSSIP_ITEM(1, "Fur Lining - Shadow Resist", GOSSIP_SENDER_MAIN, 102);
                                            //player->ADD_GOSSIP_ITEM(1, "Fur Lining - Stamina", GOSSIP_SENDER_MAIN, 103);
                                            //player->ADD_GOSSIP_ITEM(1, "Fur Lining - Spell Power", GOSSIP_SENDER_MAIN, 104);
                                            player->ADD_GOSSIP_ITEM(1,    "<-- Page 1 \\", GOSSIP_SENDER_MAIN, 8);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
            case 10: // Shield.
                            {
                                            player->ADD_GOSSIP_ITEM(1, "Defense", GOSSIP_SENDER_MAIN, 105);
                                            //player->ADD_GOSSIP_ITEM(1, "Titanium Plating", GOSSIP_SENDER_MAIN, 106);
                                            player->ADD_GOSSIP_ITEM(1, "Greater Intellect", GOSSIP_SENDER_MAIN, 107);
                                            player->ADD_GOSSIP_ITEM(1, "Resistance", GOSSIP_SENDER_MAIN, 108);
                                            player->ADD_GOSSIP_ITEM(1, "Shield Block", GOSSIP_SENDER_MAIN, 109);
                                            player->ADD_GOSSIP_ITEM(1, "Resilience", GOSSIP_SENDER_MAIN, 110);
                                            player->ADD_GOSSIP_ITEM(1, "Major Stamina", GOSSIP_SENDER_MAIN, 111);
                                            player->ADD_GOSSIP_ITEM(1, "Superior Spirit", GOSSIP_SENDER_MAIN, 112);
                                            player->ADD_GOSSIP_ITEM(1, "Frost Resistance", GOSSIP_SENDER_MAIN, 113);
                                            player->ADD_GOSSIP_ITEM(1, "Lesser Protection", GOSSIP_SENDER_MAIN, 114);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
            case 11: // Rings
                            {
                                            player->ADD_GOSSIP_ITEM(1, "Healing", GOSSIP_SENDER_MAIN, 115);
                                            player->ADD_GOSSIP_ITEM(1, "Spellpower", GOSSIP_SENDER_MAIN, 116);
                                            //player->ADD_GOSSIP_ITEM(1, "Stamina", GOSSIP_SENDER_MAIN, 117);
                                            player->ADD_GOSSIP_ITEM(1, "Stats", GOSSIP_SENDER_MAIN, 118);
                                            player->ADD_GOSSIP_ITEM(1, "Striking", GOSSIP_SENDER_MAIN, 119);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
            case 12: // Cloak Page 1
                            {
                                            player->ADD_GOSSIP_ITEM(1, "Stealth", GOSSIP_SENDER_MAIN, 120);
                                            player->ADD_GOSSIP_ITEM(1, "Dodge", GOSSIP_SENDER_MAIN, 121);
                                            player->ADD_GOSSIP_ITEM(1, "Steelweave", GOSSIP_SENDER_MAIN, 122);
                                            player->ADD_GOSSIP_ITEM(1, "Major Armor", GOSSIP_SENDER_MAIN, 123);
                                            player->ADD_GOSSIP_ITEM(1, "Greater Agility", GOSSIP_SENDER_MAIN, 124);
                                            player->ADD_GOSSIP_ITEM(1, "Greater Fire Resistance", GOSSIP_SENDER_MAIN, 125);
                                            player->ADD_GOSSIP_ITEM(1, "Greater Arcane Resistance", GOSSIP_SENDER_MAIN, 126);
                                            player->ADD_GOSSIP_ITEM(1, "Greater Shadow Resistance", GOSSIP_SENDER_MAIN, 127);
                                            player->ADD_GOSSIP_ITEM(1, "Greater Nature Resistance", GOSSIP_SENDER_MAIN, 128);
                                            player->ADD_GOSSIP_ITEM(1, "Major Resistance", GOSSIP_SENDER_MAIN, 129);
                                            player->ADD_GOSSIP_ITEM(1, "Spell Penetration", GOSSIP_SENDER_MAIN, 130);
                                            //player->ADD_GOSSIP_ITEM(1,    "// Page 2 -->", GOSSIP_SENDER_MAIN, 13);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
            /*case 13: // Cloak Page 2
                            {
                                            player->ADD_GOSSIP_ITEM(1, "Spell Piercing", GOSSIP_SENDER_MAIN, 131);
                                            player->ADD_GOSSIP_ITEM(1, "Major Resistance", GOSSIP_SENDER_MAIN, 132);
                                            player->ADD_GOSSIP_ITEM(1, "Dodge", GOSSIP_SENDER_MAIN, 133);
                                            player->ADD_GOSSIP_ITEM(1, "Subtlety", GOSSIP_SENDER_MAIN, 134);
                                            player->ADD_GOSSIP_ITEM(1, "Darkglow Embroidery", GOSSIP_SENDER_MAIN, 135);
                                            player->ADD_GOSSIP_ITEM(1, "Lightweave Embroidery", GOSSIP_SENDER_MAIN, 136);
                                            player->ADD_GOSSIP_ITEM(1, "Darkglow Embroidery", GOSSIP_SENDER_MAIN, 137);
                                            player->ADD_GOSSIP_ITEM(1,    "<-- Page 1 \\", GOSSIP_SENDER_MAIN, 12);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;*/
            case 14: // Head
                            {
                                            player->ADD_GOSSIP_ITEM(1, "Glyph of the Outcast", GOSSIP_SENDER_MAIN, 138);
                                            player->ADD_GOSSIP_ITEM(1, "Glyph of Ferocity", GOSSIP_SENDER_MAIN, 139);
                                            player->ADD_GOSSIP_ITEM(1, "Glyph of Power", GOSSIP_SENDER_MAIN, 140);
                                            player->ADD_GOSSIP_ITEM(1, "Glyph of Renewal", GOSSIP_SENDER_MAIN, 141);
                                            player->ADD_GOSSIP_ITEM(1, "Glyph of the Defender", GOSSIP_SENDER_MAIN, 142);
                                            player->ADD_GOSSIP_ITEM(1, "Glyph of the Gladiator", GOSSIP_SENDER_MAIN, 143);
                                            if (player->getClass()==CLASS_WARLOCK)
                                            {
                                            player->ADD_GOSSIP_ITEM(1, "Hoodoo Hex", GOSSIP_SENDER_MAIN, 144);
                                            }
                                            //player->ADD_GOSSIP_ITEM(1, "Arcanum of the Savage Gladiator", GOSSIP_SENDER_MAIN, 145);
                                            //player->ADD_GOSSIP_ITEM(1, "Arcanum of the Stalwart Protector", GOSSIP_SENDER_MAIN, 146);
                                            //player->ADD_GOSSIP_ITEM(1, "Arcanum of Torment", GOSSIP_SENDER_MAIN, 147);
                                            //player->ADD_GOSSIP_ITEM(1, "Arcanum of Toxic Warding", GOSSIP_SENDER_MAIN, 148);
                                            //player->ADD_GOSSIP_ITEM(1, "Arcanum of Triumph", GOSSIP_SENDER_MAIN, 149);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
            case 15: // Legs.
                            {
                                            player->ADD_GOSSIP_ITEM(1, "Runic Spellthread", GOSSIP_SENDER_MAIN, 150);
                                            player->ADD_GOSSIP_ITEM(1, "Nethercobra Leg Armor", GOSSIP_SENDER_MAIN, 151);
                                            player->ADD_GOSSIP_ITEM(1, "Golden Spellthread", GOSSIP_SENDER_MAIN, 152);
                                            player->ADD_GOSSIP_ITEM(1, "Heavy Knothide Armor Kit", GOSSIP_SENDER_MAIN, 153);
                                            player->ADD_GOSSIP_ITEM(1, "Nethercleft Leg Armor", GOSSIP_SENDER_MAIN, 154);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
            case 16: // Shoulder.
                            {
                                            player->ADD_GOSSIP_ITEM(1, "Greater Inscription of the Orb", GOSSIP_SENDER_MAIN, 155);
                                            player->ADD_GOSSIP_ITEM(1, "Greater Inscription of the Oracle", GOSSIP_SENDER_MAIN, 156);
                                            player->ADD_GOSSIP_ITEM(1, "Greater Inscription of the Blade", GOSSIP_SENDER_MAIN, 157);
                                            player->ADD_GOSSIP_ITEM(1, "Greater Inscription of the Knight", GOSSIP_SENDER_MAIN, 158);
                                            player->ADD_GOSSIP_ITEM(1, "Might of the Scourge", GOSSIP_SENDER_MAIN, 159);
                                            player->ADD_GOSSIP_ITEM(1, "Power of the Scourge", GOSSIP_SENDER_MAIN, 160);
                                            player->ADD_GOSSIP_ITEM(1, "Resilience of the Scourge", GOSSIP_SENDER_MAIN, 161);
                                            player->ADD_GOSSIP_ITEM(1, "Fortitude of the Scourge", GOSSIP_SENDER_MAIN, 162);
                                            player->ADD_GOSSIP_ITEM(1, "Greater Inscription of Warding", GOSSIP_SENDER_MAIN, 163);
                                            player->ADD_GOSSIP_ITEM(1, "Greater Inscription of Faith", GOSSIP_SENDER_MAIN, 164);
                                            player->ADD_GOSSIP_ITEM(1, "Greater Inscription of Discipline", GOSSIP_SENDER_MAIN, 165);
                                            player->ADD_GOSSIP_ITEM(1, "Greater Inscription of Vengeance", GOSSIP_SENDER_MAIN, 166);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
                                            case 20: // Ranged
                            {
                                            player->ADD_GOSSIP_ITEM(1, "Biznicks 247x128 Accurascope", GOSSIP_SENDER_MAIN, 167);
                                            player->ADD_GOSSIP_ITEM(1, "Khorium Scope", GOSSIP_SENDER_MAIN, 168);
                                            player->ADD_GOSSIP_ITEM(1, "Stabilized Eternium Scope", GOSSIP_SENDER_MAIN, 169);
                                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
            default:
                            if(player->GetMoney()>=150000)
                            {
                            {
                                            player->ModifyMoney(-150000);
                                            uint32 enchantid = enchants[(action - 30)];
                                            //SpellItemEnchantmentEntry const *pEnchant = GetEnchant(enchantid);
                                            //if (!pEnchant)
                                            //{
                                            //    player->CLOSE_GOSSIP_MENU();
                                            //    break;
                                            //}
                                            Item *itemTarget = NULL;
                                            if (action >= 30 && action <= 55)
                                            { // Weapon Enchants.
                                                            itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                                                            if (itemTarget && action < 36 && itemTarget->GetProto()->InventoryType != INVTYPE_2HWEAPON)
                                                            {
                                                                            player->CLOSE_GOSSIP_MENU();
                                                                            break;
                                                            }
                                                            if (action >= 36)
                                                            {
                                                                            AddEnchant(player, itemTarget, enchantid);
                                                                            itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
                                                                            if (itemTarget && itemTarget->GetProto()->InventoryType != INVTYPE_WEAPONOFFHAND && itemTarget->GetProto()->InventoryType != INVTYPE_WEAPONMAINHAND)
                                                                                            itemTarget = NULL;
                                                            }
                                            }
                                            else if (action >= 56 && action <= 62) // Chest Enchants.
                                            {
                                                            itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST);
                                            }
                                            else if (action >= 63 && action <= 71) // Boot Enchants.
                                            {
                                                            itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET);
                                            }
                                            else if (action >= 72 && action <= 88) // Glove Enchants
                                            {
                                                            itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS);
                                            }
                                            else if (action >= 89 && action <= 104) // Bracer Enchants
                                            {
                                                            itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS);
                                            }
                                            else if (action >= 105 && action <= 114) // Shield Enchants.
                                            {
                                                            itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
                                                            if (itemTarget && itemTarget->GetProto()->InventoryType != INVTYPE_SHIELD)
                                                                            itemTarget = NULL;
                                            }
                                            else if (action >= 115 && action <= 119) // Ring Enchants.
                                            {
                                                            itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1);
                                                            AddEnchant(player, itemTarget, enchantid);
                                                            itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2);
                                            }
                                            else if (action >= 120 && action <= 137) // Cloak Enchants.
                                            {
                                                            itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK);
                                            }
                                            else if (action >= 138 && action <= 149) // Head Enchants.
                                            {
                                                            itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD);
                                            }
                                            else if (action >= 150 && action <= 154) // Leg Enchants.
                                            {
                                                            itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS);
                                            }
                                            else if (action >= 155 && action <= 166)
                                            { // Shoulder Enchants.
                                                            itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS);
                                            }
                                            else if (action >= 167 && action <= 169)
                                            { // Ranged Enchants.
                                           
                                                            itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);
                                                            if (itemTarget && action <= 169 && itemTarget->GetProto()->InventoryType != INVTYPE_RANGED)
                                                            {
                                                                            player->CLOSE_GOSSIP_MENU();
                                                                            break;
                                                            }
                                                            /*if (action >= 167)
                                                            {
                                                                            AddEnchant(player, itemTarget, enchantid);
                                                                            itemTarget = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);
                                                                            if (itemTarget && itemTarget->GetProto()->InventoryType != INVTYPE_RANGED)
                                                                                            itemTarget = NULL;
                                                            }*/
                                            }
                                            AddEnchant(player, itemTarget, enchantid);
                                            player->CLOSE_GOSSIP_MENU();
                            }
                            }
                            else
                            {
                            player->ADD_GOSSIP_ITEM(2,    "Not enough money", GOSSIP_SENDER_MAIN, 3240);
                            player->ADD_GOSSIP_ITEM(2,    "[Main Menu]", GOSSIP_SENDER_MAIN, 1000);
                            player->PlayerTalkClass->SendGossipMenu(907, crea->GetGUID());
                            }
                            break;
            }
            return true;
}
void AddSC_DXG_EnchantBook()
{
            Script *newscript;
            newscript = new Script;
            newscript->Name="DXG_EnchantBook";
            newscript->pGossipHello =  &GossipHello_DXG_EnchantBook;
            newscript->pGossipSelect = &GossipSelect_DXG_EnchantBook;
            newscript->RegisterSelf();
};
