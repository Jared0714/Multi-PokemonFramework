#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

namespace Battle {
    namespace Universal {
        static vector<u32> pointer(2);
        static u8 slot;
        int valid;

        vector<string> Identifier(vector<string> party) {
            int location, data;
            valid = 0;

            for (int i = 0; i < party.size(); i++) {
                if (ProcessPlus::Read32(Helpers::Battle::offset[0] + (i * 0x4)) != 0) {
                    location = ProcessPlus::Read32(Helpers::Battle::offset[0] + (i * 0x4));
                    data = ProcessPlus::Read16(location + 0xC);

                    if (data != 0 && data <= Helpers::AutoRegion(721, Helpers::GetVersion(802, 807))) {
                        party[i] = allPkmn[data - 1];
                        valid++;
                    }

                    else goto none;
                }

                else none: party[i] = Color::Gray << "None";
            }

            return party;
        }

        void SlotKB(MenuEntry *entry) {
            vector<string> party(6);

            if (IsInBattle()) {
                party = Identifier(party);

                if (KB<u8>(entry->Name() << Color::White << "\n\n1: " << party[0] << Color::White << "\n2: " << party[1] << Color::White << "\n3: " << party[2] << Color::White << "\n4: " << party[3] << Color::White << "\n5: " << party[4] << Color::White << "\n6: " + party[5] + "\n", true, false, 1, slot, 0, 1, valid, Callback8)) {
                    for (int i = 0; i < pointer.size(); i++)
                        pointer[i] = Helpers::Battle::offset[i] + ((slot - 1) * 0x4);

                    Message::Completed();
                    entry->Name() = "Slot: " << Color::Gray << Utils::ToString(slot, 0);
                }
            }
        }

        static int isAffected, conditionOption;

        struct Conditions {
            const char *name;
            int value;
        };

        void Condition(MenuEntry *entry) {
            Conditions conditions[5] = {
                {"Paralyzed", Helpers::AutoRegion(0x20, 0x28)},
                {"Asleep", Helpers::AutoRegion(0x24, 0x30)},
                {"Frozen", Helpers::AutoRegion(0x28, 0x38)},
                {"Burned", Helpers::AutoRegion(0x2C, 0x40)},
                {"Poisoned", Helpers::AutoRegion(0x30, 0x48)}
            };

            static const vector<string> choices = {"None", "Affected"};
            vector<string> options;
            KeyboardPlus keyboard;

            for (const Conditions &nickname : conditions)
                options.push_back(nickname.name);

            if (IsInBattle()) {
                if (pointer[0] != 0 && pointer[1] != 0) {
                    start:
                    if (keyboard.SetKeyboard(entry->Name() + ":", true, choices, isAffected) != -1) {
                        if (isAffected == false)
                            goto apply;

                        else if (isAffected == true) {
                            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, conditionOption) != -1) {
                                apply:
                                for (int i = 0; i < pointer.size(); i++) {
                                    for (int k = 0; k < sizeof(conditions) / sizeof(conditions[0]); k++)
                                        ProcessPlus::Write8(pointer[i], conditions[k].value, 0);

                                    if (isAffected == true)
                                        ProcessPlus::Write8(pointer[i], conditions[conditionOption].value, 1);
                                }

                                Message::Completed();
                            }

                            else goto start;
                        }
                    }
                }
            }
        }

        static int statOption, baseOption, boostOption;
        static u16 baseVal[5];
        static u8 boostVal[7];

        void StatisticsKB(MenuEntry *entry) {
            static const vector<string> choice = {"Base", "Boosts"}, baseChoices = {"Attack", "Defense", "Sp. Atk", "Sp. Def", "Speed"}, boostsChoices = {"Attack", "Defense", "Sp. Atk", "Sp. Def", "Speed", "Accuracy", "Evasiveness"};
            u16 getBaseVal;
            u8 getBoostVal;

            if (IsInBattle()) {
                if (pointer[0] != 0 && pointer[1] != 0) {
                    start:
                    KeyboardPlus keyboard;
                    keyboard.SetKeyboard(entry->Name() + ":", true, choice, statOption);

                    if (statOption == 0) {
                        base:
                        keyboard.SetKeyboard(entry->Name() + ":", true, baseChoices, baseOption);

                        if (baseOption != -1) {
                            if (KB<u16>(baseChoices[baseOption] + ":", true, false, 3, getBaseVal, 0, 1, 999, Callback16)) {
                                baseVal[baseOption] = getBaseVal;
                                Message::Completed();
                            }

                            else goto base;
                        }

                        else goto start;
                    }

                    else if (statOption == 1) {
                        boosts:
                        keyboard.SetKeyboard(entry->Name() + ":", true, boostsChoices, boostOption);

                        if (boostOption != -1) {
                            if (KB<u8>(boostsChoices[boostOption] + ":", true, false, 1, getBoostVal, 0, 0, 6, Callback8)) {
                                boostVal[boostOption] = getBoostVal + 6;
                                Message::Completed();
                            }

                            else goto boosts;
                        }

                        else goto start;
                    }
                }
            }
        }

        void Statistics(MenuEntry *entry) {
            if (IsInBattle()) {
                if (pointer[0] != 0 && pointer[1] != 0) {
                    for (int i = 0; i < pointer.size(); i++) {
                        for (int k = 0; k < sizeof(baseVal) / sizeof(baseVal[0]); k++) {
                            if (baseVal[k] != 0)
                                ProcessPlus::Write16(pointer[i], Helpers::AutoRegion(0xF6, 0x1DA) + (k * 2), baseVal[k]);
                        }

                        for (int l = 0; l < sizeof(boostVal) / sizeof(boostVal[0]); l++) {
                            if (boostVal[l] != 0)
                                ProcessPlus::Write8(pointer[i], Helpers::AutoRegion(0x104, 0x1EA) + (l * 1), boostVal[l]);
                        }
                    }
                }
            }
        }

        static int invincibilityOption;
        static u16 healthVal;
        static u8 staminaVal;

        void InvincibilityKB(MenuEntry *entry) {
            static const vector<string> choices = {"Health", "Stamina"};
            u16 getHealthVal;
            u8 getStaminaVal;

            if (IsInBattle()) {
                if (pointer[0] != 0 && pointer[1] != 0) {
                    start:
                    KeyboardPlus keyboard;
                    keyboard.SetKeyboard(entry->Name() + ":", true, choices, invincibilityOption);

                    if (invincibilityOption == 0) {
                        if (KB<u16>("Health:", true, false, 3, getHealthVal, 0, 1, 999, Callback16)) {
                            healthVal = getHealthVal;
                            Message::Completed();
                        }

                        else goto start;
                    }

                    else if (invincibilityOption == 1) {
                        if (KB<u8>("Stamina:", true, false, 2, getStaminaVal, 0, 1, 99, Callback8)) {
                            staminaVal = getStaminaVal;
                            Message::Completed();
                        }

                        else goto start;
                    }
                }
            }
        }

        static const int healthCap = 2, staminaSlots = 4;

        void Invincibility(MenuEntry *entry) {
            if (IsInBattle()) {
                if (pointer[0] != 0 && pointer[1] != 0) {
                    for (int i = 0; i < pointer.size(); i++) {
                        for (int k = 0; k < healthCap; k++) {
                            if (healthVal != 0)
                                ProcessPlus::Write16(pointer[i], 0x10 - (k * 2), healthVal);
                        }

                        for (int l = 0; l < staminaSlots; l++) {
                            if (staminaVal != 0)
                                ProcessPlus::Write16(pointer[i], Helpers::AutoRegion(0x11E, 0x204) + (l * 0xE), (staminaVal << 8) | staminaVal);
                        }
                    }
                }
            }
        }

        static u16 item;

        void Item(MenuEntry *entry) {
            if (IsInBattle()) {
                if (pointer[0] != 0 && pointer[1] != 0) {
                    FindItemKB(entry);
                    item = heldItemID;

                    if (item > 0) {
                        for (int i = 0; i < pointer.size(); i++)
                            ProcessPlus::Write16(pointer[i], 0x12, item);

                        Message::Completed();
                    }
                }
            }
        }

        static u16 attack;
        static int attackSlot;

        void Attacks(MenuEntry *entry) {
            static const vector<string> options = {"Move 1", "Move 2", "Move 3", "Move 4"};
            KeyboardPlus keyboard;

            if (IsInBattle()) {
                if (pointer[0] != 0 && pointer[1] != 0) {
                    start:
                    if (keyboard.SetKeyboard(entry->Name() + ":", true, options, attackSlot) != -1) {
                        FindMoveKB(entry);
                        attack = moveID;

                        if (attack > 0) {
                            for (int i = 0; i < pointer.size(); i++)
                                ProcessPlus::Write16(pointer[i], Helpers::AutoRegion(0x11C, 0x202) + (attackSlot * 0xE), attack);

                            Message::Completed();
                        }

                        else goto start;
                    }
                }
            }
        }

        static u8 multiplier = 1;

        void ExpMultiplierKB(MenuEntry *entry) {
            if (IsInBattle()) {
                if (KB<u8>(entry->Name() + ":", true, false, 3, multiplier, 0, 1, 100, Callback8))
                    Message::Completed();
            }
        }

        void ExpMultiplier(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::AutoRegion(
                    Helpers::GetVersion<u32>(
                        {0x53EDA0, 0x175FB0},
                        {0x579860, 0x16B81C}),

                    Helpers::GetVersion<u32>(
                        {0x597700, 0x490E74},
                        {0x5BBD40, 0x4ACD38}
            ))};

            static vector<u32> original(5);
            static u32 revert;
            static bool saved[2] = {false, false};

            if (IsInBattle()) {
                if (ProcessPlus::Write32(address[0], {0xE1D002B2, 0xE92D4002, 0xE3A01000 + multiplier, 0xE0000190, 0xE8BD8002}, original, entry, saved[0])) {
                    if (!ProcessPlus::Write32(address[1], Helpers::AutoRegion(Helpers::GetVersion(0xEB0F237A, 0xEB10380F), Helpers::GetVersion(0xEB041A21, 0xEB043C00)), revert, entry, saved[1]))
                        return;
                }
            }
        }

        bool IsValid(u32 pointer, PK6 *pkmn) {
            if (!GetPokemon(pointer, pkmn))
                return false;

            return true;
        }

        static bool isPokeViewOn;
        static int pokeViewState;
        static int infoScreen = 0;

        bool PokeViewCallback(const Screen &screen) {
            static PK6 *pkmn = new PK6;
            static const u32 pointer = Helpers::AutoRegion(Helpers::GetVersion(0x81FF744, 0x81FEEC8), Helpers::GetVersion(0x3003035C, 0x30030544));
            static u32 location = pointer;
            static const vector<string> stats = {"HP", "Atk", "Def", "Spe", "SpA", "SpD"};

            if (!screen.IsTop)
                return false;

            if (IsInBattle()) {
                if (isPokeViewOn) {
                    if (Controller::IsKeyPressed(Key::R) && (location + 0x1E4) <= (pointer + (0x1E4 * 0x5)))
                        location += 0x1E4;

                    if (Controller::IsKeyPressed(Key::L) && (location - 0x1E4) >= (pointer))
                        location -= 0x1E4;

                    if (infoScreen == 0)
                        screen.Draw(Color::Gray << "Slot: " << Utils::ToString(((location + 0x1E4 - pointer) / 0x1E4), 0), 5, 5, Color::White, Color::Black);

                    if (IsValid(location, pkmn)) {
                        if (infoScreen == 0) {
                            screen.Draw("Species: " << Color(0xF2, 0xCE, 0x70) << allPkmn[pkmn->species - 1], 5, 15, Color::White, Color::Black);
                            screen.Draw("Nature: " << Color::White << allNatures[pkmn->nature], 5, 25, Color::White, Color::Black);
                            screen.Draw("Item: " << (pkmn->heldItem == 0 ? Color::Gray : Color::White) << (pkmn->heldItem == 0 ? "None" : allItems[pkmn->heldItem - 1]), 5, 35, Color::White, Color::Black);
                            screen.Draw("Ability: " << Color::White << allAbilities[pkmn->ability - 1], 5, 45, Color::White, Color::Black);
                        }

                        else if (infoScreen == 1) {
                            screen.Draw(Color::SkyBlue << "Moves", 5, 5, Color::White, Color::Black);

                            for (int i = 0; i < 4; i++) {
                                if (pkmn->moves[i] > 0)
                                    screen.Draw(to_string(i + 1) + ": " << Color::White << allMoves[pkmn->moves[i] - 1], 5, 15 + (i * 10), Color::White, Color::Black);

                                else screen.Draw(to_string(i + 1) + ": " << Color::Gray << "None", 5, 15 + (i * 10), Color::White, Color::Black);
                            }
                        }

                        else if (infoScreen == 2) {
                            screen.Draw(Color::Magenta << "IVs", 5, 5, Color::White, Color::Black);

                            for (int j = 0; j < stats.size(); j++)
                                screen.Draw(stats[j] + ": " + to_string((u8)(pkmn->iv32 >> (5 * j)) & 0x1F), 5, 15 + (j * 10), Color::White, Color::Black);
                        }

                        else if (infoScreen == 3) {
                            screen.Draw(Color::Olive << "EVs", 5, 5, Color::White, Color::Black);

                            for (int k = 0; k < stats.size(); k++)
                                screen.Draw(stats[k] + ": " + to_string(pkmn->evs[k]), 5, 15 + (k * 10), Color::White, Color::Black);
                        }

                        return true;
                    }
                }
            }

            return false;
        }

        void TogglePokeView(MenuEntry *entry) {
            if (IsInBattle()) {
                if (entry->Hotkeys[0].IsPressed())
                    infoScreen++;

                if (infoScreen > 3)
                    infoScreen = 0;

                OSD::Run(PokeViewCallback);
                return;
            }

            OSD::Stop(PokeViewCallback);
        }

        void PokeView(MenuEntry *entry) {
            static const vector<string> options = {"Enable", "Disable"};
            KeyboardPlus keyboard;

            if (IsInBattle()) {
                if (keyboard.SetKeyboard(entry->Name() + ":", false, options, pokeViewState) != -1) {
                    (pokeViewState == 0 ? isPokeViewOn = true : isPokeViewOn = false);
                    entry->SetGameFunc(TogglePokeView);
                    Message::Completed();
                }
            }
        }

        void AccessBag(MenuEntry *entry) {
            static const u32 pointer = Helpers::AutoRegion(0x8000158, 0x302E05B4);

            if (IsInBattle()) {
                if (entry->Hotkeys[0].IsDown())
                    ProcessPlus::Write8(pointer, Helpers::AutoRegion(Helpers::GetVersion(0x778, 0x77C), 0x760), Helpers::AutoRegion(4, 3));
            }
        }

        void Shiny100(MenuEntry *entry) {
            static const u32 address = Helpers::AutoRegion(Helpers::GetVersion(0x14F6A4, 0x14ECA4), Helpers::GetVersion(0x318AF0, 0x320CF0));
            static u32 original;
            static bool saved = false;

            if (!ProcessPlus::Write32(address, 0xEA00001C, original, entry, saved))
                return;
        }
    }

    namespace Gen6 {
        void Bypass1MegaRestrict(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x8C79D86, 0x8C79D86);
            static const u32 pointer = 0x8000178;

            if (Bit::Read8(address, data8, true) && data8 != 1) {
                Sleep(Seconds(1));

                if (MessageBox(CenterAlign("Unlock full Mega Evolution?"), DialogType::DialogYesNo, ClearScreen::Both)()) {
                    if (Bit::Read8(address, data8, true))
                        Bit::Write8(address, 1, true);
                }
            }

            if (IsInBattle())
                ProcessPlus::Write8(pointer, 0xEDD, 1);
        }

        void NoEncounters(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x436AC8, Helpers::PickGame(0x4640EC, 0x4640E4));
            static u32 original;
            static bool saved = false;

            if (!ProcessPlus::Write32(address, 0xE12FFF1E, original, entry, saved))
                return;
        }

        bool IsObtained(int value) {
            // Dex offset
            if ((Helpers::GetVersion(0x8CC8D4C, 0x8CE0CB8) >= 0x8000000) && (Helpers::GetVersion(0x8CC8D4C, 0x8CE0CB8) < 0x8DF0000)) {
                u32 obtainedOffset = ProcessPlus::Read32(Helpers::GetVersion(0x8CC8D4C, 0x8CE0CB8));

                if ((obtainedOffset >= 0x8000000) && (obtainedOffset < 0x8DF0000)) {
                    // Check if all is obtained
                    for (int i = 0; i < 721; i++) {
                        if ((ProcessPlus::Read8(obtainedOffset + 0xC + (i / 8)) & (1 << (i % 8))) == 0)
                            break;

                        if (i == 720)
                            return false;
                    }

                    // Check if value is set
                    if ((ProcessPlus::Read8(obtainedOffset + 0xC + ((value - 1) / 8)) & (1 << ((value - 1) % 8))) != 0)
                        return true;
                }
            }

            return false;
        }

        unsigned short last = 0xFFFF, poke[721];

        void InitPokemon(int pokeID, int form, int level, bool updateRadar) {
            static const u32 pointer = Helpers::GetVersion(0x8CEC564, 0x8D06468);
            static const int length = Helpers::GetVersion(0x178, 0xF4);
            u32 offset = ProcessPlus::Read32(pointer);

            // Check for valid pointer
            if ((offset >= 0x8000000) && (offset < 0x8DF0000)) {
                // Check if ZO file contains encounter data
                if (ProcessPlus::Read32(offset + 0x10) != ProcessPlus::Read32(offset + 0x14)) {
                    last = ProcessPlus::Read16(pointer + 4);
                    u32 encOffset = offset + ProcessPlus::Read32(offset + 0x10) + Helpers::GetVersion(0x10, 0xE);

                    // Make sure the table for the DexNav is exactly the same as the one used for normal encounters
                    if (group == Group::ORAS && updateRadar)
                        Process::CopyMemory((void*)(0x16B3DF40 + ProcessPlus::Read32(0x16B3DF40 + 4 + ProcessPlus::Read16(pointer + 4) * 4) + Helpers::GetVersion(0x10, 0xE)), (void*)encOffset, 0xF4);

                    int pokemon = 1;
                    u32 currentEncOffset = 0;

                    for (int i = 0; i < length; i += 4) {
                        if (ProcessPlus::Read8(encOffset + i + 2) != 1) {
                            currentEncOffset = encOffset + i;
                            pokemon = pokeID;
                            Process::Write8(currentEncOffset + 2, level);
                            Process::Write8(encOffset + i + 3, 1);

                            // Associate the Pokemon ID replaced with the one we use to overwrite it
                            poke[pokemon - 1] = pokemon;

                            if (ProcessPlus::Read16(currentEncOffset) != (pokemon + (0x800 * form)))
                                Process::Write16(currentEncOffset, (pokemon + (0x800 * form)));
                        }
                    }

                    /* Update DexNav because the it is not updated when we go to a location without any possible encounter,
                    so when we return to the previous route the DexNav does not show the good species, a battle is necessary to reload it. */
                    if (updateRadar && group == Group::ORAS) {
                        for (int j = 0; j < length; j += 4) {
                            // Replace the Pokemon ID according to the one associated with it in the array
                            u32 loc = 0x16B3DF40 + ProcessPlus::Read32(0x16B3DF40 + 4 + ProcessPlus::Read16(pointer + 4) * 4) + Helpers::GetVersion(0x10, 0xE) + j;

                            if (ProcessPlus::Read16(loc) != 0)
                                Process::Write16(loc, poke[ProcessPlus::Read16(loc) - 1]);
                        }
                    }
                }

                else last = 0xFFFF;
            }
        }

        static int pokemon, form;
        static u8 level;

        void Spawner(MenuEntry *entry) {
            FindPkmnKB(entry);
            pokemon = pkmnID;
            KeyboardPlus keyboard;

            if (pokemon > 0) {
                if (KB<u8>("Level:", true, false, 3, level, 0, 1, 100, Callback8)) {
                    if (keyboard.SetKeyboard("Form:", true, CTRPluginFramework::Gen6::Forms(pokemon), form) != -1) {
                        InitPokemon(pokemon, form, level, Helpers::GetVersion(false, true));
                        Message::Completed();
                    }
                }
            }
        }

        static int legendaryOption;

        void RematchLegendary(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x8C7A74C, 0x8C7A56C, 0x8C7A73C, 0x8C7A736},
                    {0x8C81DF2, 0x8C81E0C, Helpers::PickGame<u32>(0x8C81E29, 0x8C81E28), 0x8C81E41, 0x8C81E4E, 0x8C81F38, 0x8C81DF8, 0x8C81CC4, 0x8C81DF7, 0x8C81F38, 0x8C81F39, 0x8C81F3A, 0x8C81DEF}
            )};

            static const vector<string> options = {
                Helpers::GetVersion<string>(
                    {"Mewtwo", Helpers::PickGame("Xerneas", "Yveltal"), "Zygarde"},
                    {Helpers::PickGame("Ho-Oh", "Lugia"), Helpers::PickGame("Latias", "Latios"), Helpers::PickGame("Groudon", "Kyogre"), "Rayquaza", "Deoxys", Helpers::PickGame("Palkia", "Dialga"), "Heatran", "Regigigas", "Giritina", Helpers::PickGame("Tornadus", "Thunderus"), "Landorus", "Kyruem"}
            )};

            KeyboardPlus keyboard;

            static const vector<vector<bool>> rightSide = {
                {true, true, false},
                {true, true, Helpers::PickGame(true, false), false, true, true, true, false, false, true, true}
            };

            static const u8 additional = 0;
            static vector<u8> flag(Helpers::GetVersion(3, 12), 0);
            static const bool extra = false;

            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, legendaryOption) != -1) {
                (group == Group::XY ? flag[1] = 5 : flag[3] = 14, flag[7] = 1);

                for (int i = 0; i < address.size(); i++) {
                    if (i > address.size())
                        break;

                    if (legendaryOption == i) {
                        if (Bit::Read8(address[i], data8, rightSide[Helpers::GetVersion(0, 1)][i]) && data8 != 0) {
                            if (Bit::Read8(address[i], data8, rightSide[Helpers::GetVersion(0, 1)][i]))
                                Bit::Write8(address[i], flag[i], rightSide[Helpers::GetVersion(0, 1)][i]);
                        }
                    }

                    if (i == (group == Group::XY ? 1: 7)) {
                        if (Bit::Read8(address[i + 1], data8, extra) && data8 != 0) {
                            if (Bit::Read8(address[i + 1], data8, extra))
                                Bit::Write8(address[i + 1], additional, extra);
                        }
                    }
                }
            }
        }

        void GuaranteedCatch(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x8073334, 0x80737A4);

            if (IsInBattle()) {
                if (entry->IsActivated()) {
                    if (CRO::Read32(address) == 0xA000004) {
                        if (!CRO::Write32(address, 0xEA000004))
                            return;
                    }
                }

                if (!entry->IsActivated()) {
                    if (CRO::Read32(address) == 0xEA000004) {
                        if (!CRO::Write32(address, 0xA000004))
                            return;
                    }
                }
            }
        }

        void CatchTrainersPokemon(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x8075474, 0x8075858);
            vector<u32> check(3);

            if (IsInBattle()) {
                if (entry->IsActivated()) {
                    check = {0xE5D00000, 0xE3500000, 0xA00000E};

                    if (CRO::Read32(address, 3) == check) {
                        if (!CRO::Write32(address, {0xE3A0B000, 0xE5C0B000, 0xEA00000E}))
                            return;
                    }
                }

                if (!entry->IsActivated()) {
                    check = {0xE3A0B000, 0xE5C0B000, 0xEA00000E};

                    if (CRO::Read32(address, 3) == check) {
                        if (!CRO::Write32(address, {0xE5D00000, 0xE3500000, 0xA00000E}))
                            return;
                    }
                }
            }
        }
    }

    namespace Gen7 {
        void AlwaysCriticalHit(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x5979D0, 0x80860D8},
                    {0x5BBB90, 0x8087FF0}
            )};

            static vector<u32> original(12);
            static bool saved = false;

            if (IsInBattle()) {
                if (ProcessPlus::Write32(address[0], {0xE59D0000, 0xE92D401E, 0xE59A1008, 0xE2813004, 0xE281401C, 0xE4932004, 0xE1500002, 0x3A01001, 0x58D1018, 0xE1530004, 0x1AFFFFF9, 0xE8BD801E}, original, entry, saved)) {
                    if (entry->IsActivated()) {
                        if (CRO::Read32(address[1]) == 0xE59D0000) {
                            if (!CRO::Write32(address[1], Helpers::GetVersion(0xEBF9B23C, 0xEBF976E6)))
                                return;
                        }
                    }

                    if (!entry->IsActivated()) {
                        if (CRO::Read32(address[1]) == Helpers::GetVersion(0xEBF9B23C, 0xEBF976E6)) {
                            if (!CRO::Write32(address[1], 0xE59D0000))
                                return;
                        }
                    }
                }
            }
        }

        void Bypass1MegaRestrict(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x80A2CE4, 0x80A6150);

            if (IsInBattle()) {
                if (entry->IsActivated()) {
                    if (CRO::Read32(address) == 0xE12FFF32) {
                        if (!CRO::Write32(address, 0xE3A00000))
                            return;
                    }
                }

                if (!entry->IsActivated()) {
                    if (CRO::Read32(address) == 0xE3A00000) {
                        if (!CRO::Write32(address, 0xE12FFF32))
                            return;
                    }
                }
            }
        }

        void InfiniteZMoves(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x80311D4, 0x8031E74);
            vector<u32> check(3);

            if (IsInBattle()) {
                if (entry->IsActivated()) {
                    check = {Helpers::GetVersion(0xE1D000D5, 0xEB0195FE), 0xE3500000, 0xE320F000};

                    if (CRO::Read32(address, 3) == check) {
                        if (!CRO::Write32(address, {0xE3A00000, 0xE5C30005, 0xE1500000}))
                            return;
                    }
                }

                if (!entry->IsActivated()) {
                    check = {0xE3A00000, 0xE5C30005, 0xE1500000};

                    if (CRO::Read32(address, 3) == check) {
                        if (!CRO::Write32(address, {Helpers::GetVersion(0xE1D000D5, 0xEB0195FE), 0xE3500000, 0xE320F000}))
                            return;
                    }
                }
            }
        }

        void ZMovesWithoutCrystal(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x597800, 0x314300, 0x314370, 0x36DFF4},
                    {0x5BBDE0, 0x31C494, 0x31C504, 0x376EB0}
            )};

            static const vector<u32> instruction = {
                Helpers::GetVersion<u32>(
                    {0xE92D4005, 0xE1A00006, 0xEA000000, 0xE92D4005, 0xE59D2050, 0xE59F100C, 0xE1510002, 0x01D510B4, 0x11A01000, 0xE8BD8005, 0x0078BF60},
                    {0xE92D407D, 0xE1A00006, 0xEA000000, 0xE92D407D, 0xE1D510B4, 0xE59D201C, 0xE202530F, 0xE3550203, 0x18BD807D, 0xE59F300C, 0xEB000004, 0xE59F3008, 0xEB000002, 0xE8BD807D, 0x30000404, 0x300073EC, 0xE2834018, 0xE4935004, 0xE1550002, 0x01A01000, 0xE1530004, 0x1AFFFFFA, 0xE12FFF1E}
            )};

            static vector<u32> original(instruction.size());
            static vector<u32> revert(2);
            static bool saved[2] = {false, false};

            if (IsInBattle()) {
                if (ProcessPlus::Write32(address[0], instruction, original, entry, saved[0])) {
                    if (ProcessPlus::Write32({address[1], address[2]}, {Helpers::GetVersion(0xEB0A0D3E, 0xEB0A7E51), Helpers::GetVersion(0xEB0A0D25, 0xEB0A7E38)}, revert, entry, saved[1])) {
                        entry->Hotkeys[0].IsDown() ? Process::Write32(address[3], 0xE3A00001) : Process::Write32(address[3], 0xE3A00000);
                        return;
                    }
                }
            }
        }

        void NoEncounters(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x807A5E8, 0x807E5B8);

            if (entry->IsActivated()) {
                if (CRO::Read32(address) == 0xE3A00064) {
                    if (!CRO::Write32(address, 0xE3A09000))
                        return;
                }
            }

            if (!entry->IsActivated()) {
                if (CRO::Read32(address) == 0xE3A09000) {
                    if (!CRO::Write32(address, 0xE3A00064))
                        return;
                }
            }
        }

        static int pokemon, form;
        static u8 level;

        void InitPokemon(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x597BA0, 0x597BC0, 0x399CB4, 0x399CC4, 0x399CF0, 0x399C9C, 0x399D50},
                    {0x5BBFC0, 0x5BBFE0, Helpers::PickGame<u32>(0x3A86A0, 0x3A86A4), Helpers::PickGame<u32>(0x3A86B0, 0x3A86B4), Helpers::PickGame<u32>(0x3A86DC, 0x3A86E0), Helpers::PickGame<u32>(0x3A8688, 0x3A868C), Helpers::PickGame<u32>(0x3A873C, 0x3A8740)}
            )};

            static vector<u32> original(10);
            static vector<u32> revert(6);
            static bool saved[2] = {false, false};

            if (ProcessPlus::Write32(address[0], {0xE92D400E, 0xE59F0014, 0xE3500000, 0x18BD800E, 0xE59F000C, 0xEBF83F51, 0xE2800001, 0xE8BD800E, 0, 0x327}, original, entry, saved[0])) {
                if (!ProcessPlus::Write32({address[1], address[2], address[3], address[4], address[5], address[6]}, {(unsigned int)pokemon, Helpers::GetVersion(0xEB07F7B9, Helpers::PickGame(0xEB084E46, 0xEB084E45)), 0xE1D400B0, 0xE1D400B0, 0xE3A00000 + level, 0xC3A00000 + form}, revert, entry, saved[1]))
                    return;
            }
        }

        void Spawner(MenuEntry *entry) {
            FindPkmnKB(entry);
            pokemon = pkmnID;
            KeyboardPlus keyboard;

            if (pokemon > 0) {
                if (keyboard.SetKeyboard("Form:", true, CTRPluginFramework::Gen7::Forms(pokemon), form) != -1) {
                    if (KB<u8>("Level:", true, false, 3, level, 0, 1, 100, Callback8))
                        entry->SetGameFunc(InitPokemon);
                        Message::Completed();
                }
            }
        }

        static int legendaryIndex;

        void RematchLegendary(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x330D721C, 0x330D721E, 0x330D7220, 0x330D71E4, 0x330D76CA, 0x330D76EE, 0x330D783A},
                    {0x33013264, 0x33013266, 0x33013268, 0x3301322C, 0x33013712, 0x3301379F, 0x33013796}
            )};

            static const vector<string> options = {"Tapu Koko", "Tapu Lele", "Tapu Bulu", "Tapu Fini", "Cosmog", Helpers::PickGame("Solgaleo", "Lunala"), "Necrozma"};
            KeyboardPlus keyboard;

            static const vector<bool> rightSide = {true, true, true, true, false, false, false};
            static vector<u8> flag(7, 1);

            flag[0] = 3;
            flag[3] = 3;
            flag[4] = 0;
            flag[5] = 2;

            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, legendaryIndex) != -1) {
                for (int i = 0; i < address.size(); i++) {
                    if (legendaryIndex == i) {
                        if (Bit::Read8(address[i], data8, rightSide[i]) && data8 != 0) {
                            Bit::Write8(address[i], flag[i], rightSide[i]);
                            Message::Completed();
                            return;
                        }
                    }
                }

                Message::Warning();
                return;
            }
        }

        void RefightTrainer(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion<u32>(0x49EFC8, Helpers::PickGame<u32>(0x4BB03C, 0x4BB034));
            static vector<u32> original(2);
            static bool saved = false;

            if (ProcessPlus::Write32(address, {0xE3A00000, 0xE12FFF1E}, original, entry, saved))
                return;
        }

        void RejectTrainerBattle(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x802EBF0, 0x8032034);

            if (entry->IsActivated()) {
                if (CRO::Read32(address) == Helpers::GetVersion(0xEB00FA2F, 0xEB00F53B)) {
                    if (!CRO::Write32(address, 0xE3A00001))
                        return;
                }
            }

            if (!entry->IsActivated()) {
                if (CRO::Read32(address) == 0xE3A00001) {
                    if (!CRO::Write32(address, Helpers::GetVersion(0xEB00FA2F, 0xEB00F53B)))
                        return;
                }
            }
        }

        void GuaranteedCatch(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x59775C, 0x490E68},
                    {0x5BBEA0, 0x4ACD2C}
            )};

            static vector<u32> original(9);
            static u32 revert;
            static bool saved[2] = {false, false};

            if (IsInBattle()) {
                if (ProcessPlus::Write32(address[0], {0xE5D00008, 0xE92D4003, 0xE59D0010, 0xE59F100C, 0xE1510000, 0x024000F8, 0x058D0010, 0xE8BD8003, Helpers::GetVersion<u32>(0x6DA1CC, 0x70C62C)}, original, entry, saved[0])) {
                    if (!ProcessPlus::Write32(address[1], Helpers::GetVersion<u32>(0xEB041A3B, 0xEB043C5B), revert, entry, saved[1]))
                        return;
                }
            }
        }

        void CanCatchTrial(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x8076530, Helpers::PickGame<u32>(0x80B8914, 0x80B88FC)},
                    {0x8077CD8, 0x80BC874}
            )};

            if (IsInBattle()) {
                if (entry->IsActivated()) {
                    if (CRO::Read32(address[0]) == 0xE3A00000 && CRO::Read32(address[1] == 0xE1A01004)) {
                        if (!CRO::Write32(address[0], 0xE3A00001) || !CRO::Write32(address[1], 0xE3A01000))
                            return;
                    }
                }

                if (!entry->IsActivated()) {
                    if (CRO::Read32(address[0]) == 0xE3A00001 && CRO::Read32(address[1] == 0xE3A01000)) {
                        if (!CRO::Write32(address[0], 0xE3A00000) || !CRO::Write32(address[1], 0xE1A01004))
                            return;
                    }
                }
            }
        }

        void CatchTrainersPokemon(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x8035AA8, 0x8036F18);
            vector<u32> check(4);

            if (IsInBattle()) {
                if (entry->IsActivated()) {
                    check = {Helpers::GetVersion(0xEB019429, 0xEB01979E), 0xE3500000, 0xE320F000, 0xA00000B};

                    if (CRO::Read32(address, 4) == check) {
                        if (!CRO::Write32(address, {0xE3A0B000, 0xE590000C, 0xE5C0B000, 0xEA00000B}))
                            return;
                    }
                }

                if (!entry->IsActivated()) {
                    check = {0xE3A0B000, 0xE590000C, 0xE5C0B000, 0xEA00000B};

                    if (CRO::Read32(address, 4) == check) {
                        if (!CRO::Write32(address, {Helpers::GetVersion(0xEB019429, 0xEB01979E), 0xE3500000, 0xE320F000, 0xA00000B}))
                            return;
                    }
                }
            }
        }
    }

    static int music, musicType;
    static vector<string> getMusicFiles;
    static bool musicSelected = false;

    void MusicKB(MenuEntry *entry) {
        static const vector<string> options = {"Wild Encounter", "Trainer"};
        KeyboardPlus keyboard;

        if (keyboard.SetKeyboard(entry->Name() + ":", true, options, musicType) != -1) {
            static const vector<Music> fromGame = Helpers::AutoRegion(Helpers::GetVersion(XY::musicFiles, ORAS::musicFiles), Helpers::GetVersion(SM::musicFiles, USUM::musicFiles));

            if (getMusicFiles.empty()) {
                for (const Music &nickname : fromGame)
                    getMusicFiles.push_back(nickname.name);
            }

            if (keyboard.SetKeyboard(entry->Name() + ":\n\nSelect the music file you would like to use.", true, getMusicFiles, music) != -1) {
                musicSelected = true;
                Message::Completed();
                return;
            }

            else musicSelected = false;
        }

        else musicSelected = false;
    }

    void Music(MenuEntry *entry) {
        static const vector<u32> address = {
            Helpers::AutoRegion<u32>(Helpers::GetVersion<u32>(0x1615FDA4, 0x16127D6C), Helpers::GetVersion<u32>(0x32F99D88, 0x32EDD178)),
            Helpers::AutoRegion<u32>(Helpers::GetVersion<u32>(0x1615FDC8, 0x16127DA0), Helpers::GetVersion<u32>(0x32F99DEC, 0x32EDD8A0))
        };

        static const vector<string> original = {
            Helpers::GetVersion("bgm_xy_vs_norapoke.aac", "bgm_sg_vs_norapoke_sg.dspadpcm.bcstm"), Helpers::GetVersion("bgm_nj_vs_norapoke.dspadpcm.bcstm", "bgm_mj_vs_norapoke.dspadpcm.bcstm"),
            Helpers::GetVersion("bgm_xy_vs_trainer.aac", "bgm_sg_vs_trainer_sg.dspadpcm.bcstm"), Helpers::GetVersion("bgm_nj_vs_trainer.dspadpcm.bcstm", "bgm_mj_vs_norapoke.dspadpcm.bcstm")
        };

        static const string extension = Helpers::AutoRegion(Helpers::GetVersion(".aac", ".dspadpcm.bcstm"), ".dspadpcm.bcstm");

        if (Utils::FindExtension(getMusicFiles[music], extension.size()) != extension)
            getMusicFiles[music] += extension;

        if (entry->IsActivated()) {
            if (musicSelected) {
                string check;

                if (Process::ReadString(address[musicType], check, original.size(), StringFormat::Utf8) && check != getMusicFiles[music]) {
                    for (int i = 0; i < Helpers::AutoRegion(Helpers::GetVersion(0x24, 0x34), 0x30); i++)
                        Process::Write8(address[musicType] + i, 0);

                    if (Process::WriteString(address[musicType], getMusicFiles[music], (getMusicFiles[music].size() + 1> original[musicType].size() ? Helpers::AutoRegion(Helpers::GetVersion(0x24, 0x34), 0x30) : getMusicFiles[music].size() + 1), StringFormat::Utf8))
                        return;
                }
            }
        }

        else {
            string revert;

            for (int i = 0; i < address.size(); i++) {
                if (Process::ReadString(address[i], revert, original.size(), StringFormat::Utf8) && revert != original[i]) {
                    for (int j = 0; j < Helpers::AutoRegion(Helpers::GetVersion(0x24, 0x34), 0x30); j++)
                        Process::Write8(address[i] + j, 0);

                    Process::WriteString(address[i], original[i], original[i].size(), StringFormat::Utf8);
                }
            }

            return;
        }
    }
}