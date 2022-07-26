#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"
#include <time.h>

using namespace CTRPluginFramework;

namespace Computer {
    void PCBackup(MenuEntry *entry) {
        static const u32 address = Helpers::AutoRegion(Helpers::GetVersion(0x8C861C8, 0x8C9E134), Helpers::GetVersion(0x330D9838, 0x33015AB0));
        vector<string> listOfFiles, listOfFileNames;
        string extension = ".bin";

        Directory directory(bin);
        directory.ListFiles(listOfFiles, extension);
        listOfFileNames = listOfFiles;
        int index = listOfFileNames.size();

        if (index >= 20) {
            if (MessageBox(CenterAlign("Limit reached! Erase old backups?"), DialogType::DialogYesNo, ClearScreen::Both)()) {
                for (int i = 0; i < index; i++)
                    File::Remove(bin + listOfFileNames[i]);

                MessageBox(CenterAlign("All backups have been erased."), DialogType::DialogOk, ClearScreen::Both)();
            }

            return;
        }

        int choice;
        string fileName;
        static const vector<string> options = {"Export", "Import"};
        KeyboardPlus keyboard;

        if (keyboard.SetKeyboard(entry->Name() + ":", true, options, choice) != -1) {
            if (choice == 0) {
                if (!Directory::IsExists(bin))
                    Directory::Create(bin);

                if (index <= 20) {
                    if (KB<string>("Name:", true, false, 16, fileName, "")) {
                        File dumpFile(bin + fileName + extension, File::RWC);
                        dumpFile.Dump(address, Helpers::AutoRegion(215760, 222720));
                        Message::Completed();
                        return;
                    }
                }
            }

            if (choice == 1) {
                if (index == 0) {
                    MessageBox(CenterAlign("You have 0 backup(s) to recover from!"), DialogType::DialogOk, ClearScreen::Both)();
                    return;
                }

                if (index >= 1) {
                    keyboard.Populate(listOfFileNames);
                    int fileIndex = keyboard.Open();

                    if (fileIndex >= 0) {
                        File injectFile(bin + listOfFileNames[fileIndex]);
                        injectFile.Inject(address, Helpers::AutoRegion(215760, 222720));
                        Message::Completed();
                        return;
                    }
                }
            }
        }
    }

    namespace Editor {
        static u8 box, slot;
        static u32 pointer;

        bool Setup(void) {
            if (KB<u8>("Box:", true, false, 2, box, 0, 1, Helpers::AutoRegion(31, 32), Callback8)) {
                if (KB<u8>("Slot:", true, false, 2, slot, 0, 1, 30, Callback8)) {
                    pointer = (((slot - 1) * 0xE8) + ((box - 1) * 6960 + GetPokePointer()));
                    return true;
                }
            }

            return false;
        }

        void Initialize(MenuEntry *entry) {
            if (Setup())
                Message::Completed();
        }

        bool IsValid(u32 pointer, PK6 *pkmn) {
            if (!GetPokemon(pointer, pkmn)) {
                if (!IsInBattle())
                    MessageBox(CenterAlign("Failed to read or decrypt data!"), DialogType::DialogOk, ClearScreen::Both)();

                return false;
            }

            return true;
        }

        bool IsValid(u32 pointer, PK6 *pkmn, MenuEntry *entry) {
            if (!GetPokemon(pointer, pkmn)) {
                entry->Disable();
                return false;
            }

            return true;
        }

        static int shinifyOption;

        void Shinify(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> noYes = {"No", "Yes"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                if (keyboard.SetKeyboard(entry->Name() + ":", true, noYes, shinifyOption) != -1) {
                    if (IsShiny(pkmn) != shinifyOption) {
                        MakeShiny(pkmn, shinifyOption);

                        if (SetPokemon(pointer, pkmn)) {
                            Message::Completed();
                            return;
                        }
                    }

                    Message::Warning();
                }
            }
        }

        static u16 species;

        void Species(MenuEntry *entry) {
            PK6 *pkmn = new PK6;

            if (IsValid(pointer, pkmn)) {
                FindPkmnKB(entry);
                species = pkmnID;

                if (species > 0) {
                    SetSpecies(pkmn, species);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static int isNick;

        void IsNicknamed(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> options = {"No", "Yes"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, isNick) != -1) {
                    SetIsNicknamed(pkmn, isNick);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        string nick;

        void Nickname(MenuEntry *entry) {
            PK6 *pkmn = new PK6;

            if (IsValid(pointer, pkmn)) {
                if (KB<string>(entry->Name() + ":", true, false, 26, nick, "")) {
                    SetNickname(pkmn, nick);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static int genderChoice;

        void Gender(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> options = {"Male", "Female"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                for (int i = 0; i < fixedGender.size(); i++) {
                    if (pkmn->species == fixedGender[i]) {
                        MessageBox(CenterAlign("Cannot override fixed gender."), DialogType::DialogOk, ClearScreen::Both)();
                        return;
                    }
                }

                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, genderChoice) != -1) {
                    SetGender(pkmn, genderChoice);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static u8 level;

        void Level(MenuEntry *entry) {
            PK6 *pkmn = new PK6;

            if (IsValid(pointer, pkmn)) {
                if (KB<u8>(entry->Name() + ":", true, false, 3, level, 0, 1, 100, Callback8)) {
                    for (int i = 0; i < growthRates.size(); i++) {
                        for (int j = 0; j < growthRates[i].size(); j++) {
                            if (pkmn->species == growthRates[i][j]) {
                                SetLevel(pkmn, level, i);

                                if (SetPokemon(pointer, pkmn)) {
                                    Message::Completed();
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }

        static int natureID;

        void Nature(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                if (keyboard.SetKeyboard(entry->Name() + ":", true, allNatures, natureID) != -1) {
                    SetNature(pkmn, natureID);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        void Form(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            int form;
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                if (pkmn->species > 0) {
                    if (keyboard.SetKeyboard(entry->Name() + ":", true, Helpers::AutoRegion(Gen6::Forms(pkmn->species), Gen7::Forms(pkmn->species)), form) != -1) {
                        SetForm(pkmn, form);

                        if (SetPokemon(pointer, pkmn))
                            Message::Completed();
                    }
                }
            }
        }

        static u16 item;

        void HeldItem(MenuEntry *entry) {
            PK6 *pkmn = new PK6;

            if (IsValid(pointer, pkmn)) {
                FindItemKB(entry);
                item = heldItemID;

                if (item > 0) {
                    SetHeldItem(pkmn, item);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static u8 abil;

        void Ability(MenuEntry *entry) {
            PK6 *pkmn = new PK6;

            if (IsValid(pointer, pkmn)) {
                FindAbilityKB(entry);
                abil = abilityID;

                if (abil > 0) {
                    SetAbility(pkmn, abil);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static u16 friendshipAmount;

        void Friendship(MenuEntry *entry) {
            PK6 *pkmn = new PK6;

            if (IsValid(pointer, pkmn)) {
                if (KB<u16>(entry->Name() + ":", true, false, 3, friendshipAmount, 0, 0, 255, Callback16)) {
                    SetFriendship(pkmn, friendshipAmount);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static int languageChoice;

        void Language(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> options = {"JPN", "ENG", "FRE", "ITA", "GER", "ESP", "KOR", "CHS", "CHT"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, languageChoice) != -1) {
                    SetLanguage(pkmn, languageChoice + 1);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static int eggChoice;

        void IsEgg(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> options = {"No", "Yes"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, eggChoice) != -1) {
                    SetIsEgg(pkmn, eggChoice);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static u8 pkrsVal[2];
        static int pkrsCureChoice;

        void Pokerus(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> options = {"Cured", "Non-Cured"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                start:
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, pkrsCureChoice) != -1) {
                    if (pkrsCureChoice == 0) {
                        if (KB<u8>("Strain:", true, false, 1, pkrsVal[1], 0, 0, 3, Callback8))
                            SetPokerus(pkmn, 0, pkrsVal[1]);
                    }

                    else if (pkrsCureChoice == 1) {
                        if (KB<u8>("Days:", true, false, 2, pkrsVal[0], 0, 1, 15, Callback8)) {
                            if (KB<u8>("Strain:", true, false, 1, pkrsVal[1], 0, 0, 3, Callback8))
                                SetPokerus(pkmn, pkrsVal[0], pkrsVal[1]);

                            else goto start;
                        }

                        else goto start;
                    }

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static int getPlayerCountry, playerCountry;

        void Country(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            vector<string> options;
            KeyboardPlus keyboard;

            for (const Geograph &nickname : allCountries)
                options.push_back(nickname.name);

            if (IsValid(pointer, pkmn)) {
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, getPlayerCountry) != -1) {
                    playerCountry = allCountries[getPlayerCountry].id;
                    SetCountry(pkmn, playerCountry);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        void Region(MenuEntry *entry);

        static int consRegion;

        void ConsoleRegion(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> options = {"Japan", "Americas", "Europe", "China", "Korea", "Taiwan"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, consRegion) != -1) {
                    SetConsRegion(pkmn, consRegion + 1);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static int getOrigin, originID;
        int originsAvailable = 0;

        void OriginGame(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static vector<string> options;
            KeyboardPlus keyboard;

            for (const Origins &nickname : allOrigins) {
                if (originsAvailable != 8) {
                    if (originsAvailable > 3 && (group == Group::XY || group == Group::ORAS))
                        options.push_back(nickname.name);

                    if (group == Group::SM || group == Group::USUM)
                        options.push_back(nickname.name);

                    originsAvailable++;
                }

                else break;
            }

            if (IsValid(pointer, pkmn)) {
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, getOrigin) != -1) {
                    originID = allOrigins[getOrigin + Helpers::AutoRegion(4, 0)].choiceNo;
                    SetOrigin(pkmn, originID);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static int getMetLoc, metLocID, deterVer;

        void MetLocation(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            vector<string> options;
            KeyboardPlus keyboard;

            if (allOrigins[getOrigin + Helpers::AutoRegion(4, 0)].choiceNo == 24 || allOrigins[getOrigin + Helpers::AutoRegion(4, 0)].choiceNo == 25) {
                deterVer = allLocs6[getMetLoc].choiceNo;

                for (const Locations &nickname : allLocs6)
                    options.push_back(nickname.name);
            }

            else if (allOrigins[getOrigin + Helpers::AutoRegion(4, 0)].choiceNo == 26 || allOrigins[getOrigin + Helpers::AutoRegion(4, 0)].choiceNo == 27) {
                deterVer = allLocs6b[getMetLoc].choiceNo;

                for (const Locations &nickname : allLocs6b)
                    options.push_back(nickname.name);
            }

            else {
                MessageBox(CenterAlign("Failed to read or decrypt data!"), DialogType::DialogOk, ClearScreen::Both)();
                return;
            }

            if (IsValid(pointer, pkmn)) {
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, getMetLoc) != -1) {
                    metLocID = deterVer;
                    SetMetLocation(pkmn, metLocID, false);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static int getBall, ballID;

        void Ball(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            int counter = 0;
            vector<string> options;
            KeyboardPlus keyboard;

            for (const Balls &nickname : allBalls) {
                if (group == Group::XY || group == Group::ORAS) {
                    if (counter != 3)
                        options.push_back(nickname.name);
                }

                else options.push_back(nickname.name);
                counter++;
            }

            if (IsValid(pointer, pkmn)) {
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, getBall) != -1) {
                    if (group == Group::XY || group == Group::ORAS) {
                        if (getBall > 2)
                            ballID = allBalls[getBall + 1].choiceNo;
                    }

                    else ballID = allBalls[getBall].choiceNo;

                    SetBall(pkmn, ballID);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static u8 levelMetAt;

        void MetLevel(MenuEntry *entry) {
            PK6 *pkmn = new PK6;

            if (IsValid(pointer, pkmn)) {
                if (KB<u8>(entry->Name() + ":", true, false, 3, levelMetAt, 0, 1, 100, Callback8)) {
                    SetMetLevel(pkmn, levelMetAt);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        int dateLimit(int index) {
            if (index == 0)
                return 99;

            if (index == 1)
                return 12;

            if (index == 2)
                return 31;

            return 0;
        }

        static u8 date[3];
        static int dateChoice;

        void MetDate(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> options = {"Year", "Month", "Day"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                start:
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, dateChoice) != -1) {
                    int settings[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

                    for (int i = 0; i < 3; i ++) {
                        if (i == dateChoice) {
                            if (KB<u8>(options[dateChoice] + ":", true, false, 2, date[i], 0, 1, dateLimit(i), Callback8))
                                SetMetDate(pkmn, settings[i][0], settings[i][1], settings[i][2], false, date);

                            else goto start;
                        }
                    }

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static int encChoice;

        void IsFatefulEncounter(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> options = {"No", "Yes"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, encChoice) != -1) {
                    SetIsFatefulEnc(pkmn, encChoice);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static int getEggMetLoc, eggMetLocID, deterEggVer;

        void EggMetLoc(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            vector<string> options;
            KeyboardPlus keyboard;

            if (allOrigins[getOrigin].choiceNo == 24 || allOrigins[getOrigin].choiceNo == 25) {
                deterEggVer = allLocs6[getEggMetLoc].choiceNo;

                for (const Locations &nickname : allLocs6)
                    options.push_back(nickname.name);
            }

            else if (allOrigins[getOrigin].choiceNo == 26 || allOrigins[getOrigin].choiceNo == 27) {
                deterEggVer = allLocs6b[getEggMetLoc].choiceNo;

                for (const Locations &nickname : allLocs6b)
                    options.push_back(nickname.name);
            }

            else {
                MessageBox(CenterAlign("Failed to read or decrypt data!"), DialogType::DialogOk, ClearScreen::Both)();
                return;
            }

            if (IsValid(pointer, pkmn)) {
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, getEggMetLoc) != -1) {
                    eggMetLocID = deterEggVer;
                    SetMetLocation(pkmn, eggMetLocID, true);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static u8 eggDate[3];
        static int eggDateChoice;

        void EggMetDate(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> options = {"Year", "Month", "Day"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                start:
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, eggDateChoice) != -1) {
                    int settings[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

                    for (int i = 0; i < 3; i ++) {
                        if (i == eggDateChoice) {
                            if (KB<u8>(options[eggDateChoice] + ":", true, false, 2, eggDate[i], 0, 1, dateLimit(i), Callback8))
                                SetMetDate(pkmn, settings[i][0], settings[i][1], settings[i][2], true, eggDate);

                            else goto start;
                        }
                    }

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static u8 ivs[6];
        static int ivChoice;

        void IVs(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> options = {"HP", "Atk", "Def", "Spe", "SpA", "SpD"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                start:
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, ivChoice) != -1) {
                    if (KB<u8>(options[ivChoice] + ": " + to_string((u8)(pkmn->iv32 >> (5 * ivChoice)) & 0x1F), true, false, 2, ivs[ivChoice], 0, 0, 31, Callback8))
                        SetIV(pkmn, ivChoice, ivs[ivChoice]);

                    else goto start;

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static vector<u16> evAmount(6, 0);
        static int evChoice;

        void EVs(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> options = {"HP", "Atk", "Def", "Spe", "SpA", "SpD"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                start:
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, evChoice) != -1) {
                    if (KB<u16>(options[evChoice] + ": " + to_string(pkmn->evs[evChoice]), true, false, 3, evAmount[evChoice], 0, 0, 252, Callback16))
                        SetEV(pkmn, evChoice, evAmount[evChoice]);

                    else goto start;

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static u16 contestStats[6];
        static int contestChoice;

        void Contest(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> options = {"Cool", "Beauty", "Cute", "Smart", "Though", "Sheen"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                start:
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, contestChoice) != -1) {
                    if (KB<u16>(options[contestChoice] + ":", true, false, 3, contestStats[contestChoice], 0, 0, 255, Callback16))
                        SetContestStats(pkmn, contestChoice, contestStats[contestChoice]);

                    else goto start;

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static u16 moves;
        static int moveSlot;

        void CurrentMoves(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> options = {"Move 1", "Move 2", "Move 3", "Move 4"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                start:
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, moveSlot) != -1) {
                    FindMoveKB(entry);
                    moves = moveID;

                    if (moves > 0)
                        SetMoves(pkmn, moveSlot, moves, false);

                    else goto start;

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static u8 ppUps[6];
        static int ppUpSlot;

        void PPUps(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> options = {"Move 1", "Move 2", "Move 3", "Move 4"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                start:
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, ppUpSlot) != -1) {
                    if (KB<u8>(options[ppUpSlot] + ":", true, false, 1, ppUps[ppUpSlot], 0, 0, 3, Callback8))
                        SetPPUps(pkmn, ppUpSlot, ppUps[ppUpSlot]);

                    else goto start;

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static u16 relearnMoves;
        static int relearnMoveSlot;

        void RelearnMoves(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            static const vector<string> options = {"Move 1", "Move 2", "Move 3", "Move 4"};
            KeyboardPlus keyboard;

            if (IsValid(pointer, pkmn)) {
                start:
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, relearnMoveSlot) != -1) {
                    FindMoveKB(entry);
                    relearnMoves = moveID;

                    if (relearnMoves > 0)
                        SetMoves(pkmn, relearnMoveSlot, relearnMoves, true);

                    else goto start;

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static u32 sidNums;

        void SID(MenuEntry *entry) {
            PK6 *pkmn = new PK6;

            if (IsValid(pointer, pkmn)) {
                if (KB<u32>(entry->Name() + ":", true, false, 5, sidNums, 0, 1, 65535, Callback32)) {
                    SetSID(pkmn, sidNums);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static u32 tidNums;

        void TID(MenuEntry *entry) {
            PK6 *pkmn = new PK6;

            if (IsValid(pointer, pkmn)) {
                if (KB<u32>(entry->Name() + ":", true, false, 5, tidNums, 0, 1, 65535, Callback32)) {
                    SetTID(pkmn, tidNums);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        string name;

        void OTName(MenuEntry *entry) {
            PK6 *pkmn = new PK6;

            if (IsValid(pointer, pkmn)) {
                if (KB<string>(entry->Name() + ":", true, false, 26, name, "")) {
                    SetOTName(pkmn, name);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        string htName;

        void LatestHandler(MenuEntry *entry) {
            PK6 *pkmn = new PK6;

            if (IsValid(pointer, pkmn)) {
                if (KB<string>(entry->Name() + ":", true, false, 26, htName, "")) {
                    SetLatestHandler(pkmn, htName);

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }

        static int ribbonChoice, obtainRibbon;

        void Ribbons(MenuEntry *entry) {
            PK6 *pkmn = new PK6;
            vector<string> options;
            static const vector<string> noYes = {"No", "Yes"};
            KeyboardPlus keyboard;

            for (int i = 0; i < Helpers::AutoRegion(Helpers::PickGame(37, 44), 46); i++)
                options.push_back(allRibbons[i].name);

            if (IsValid(pointer, pkmn)) {
                start:
                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, ribbonChoice) != -1) {
                    if (keyboard.SetKeyboard(options[ribbonChoice] + ":", true, noYes, obtainRibbon) != -1)
                        SetRibbons(pkmn, allRibbons[ribbonChoice].category, allRibbons[ribbonChoice].index, obtainRibbon);

                    else goto start;

                    if (SetPokemon(pointer, pkmn))
                        Message::Completed();
                }
            }
        }
    }

    static u8 cloningSettings[2];
    static u8 amount;

    void Cloning(MenuEntry *entry) {
        PK6 *pkmn = new PK6;

        if (KB<u8>("Box:", true, false, 2, cloningSettings[0], 0, 1, Helpers::AutoRegion(31, 32), Callback8)) {
            if (KB<u8>("Slot:", true, false, 2, cloningSettings[1], 0, 1, 30, Callback8)) {
                u32 location = (((cloningSettings[1] - 1) * 0xE8) + ((cloningSettings[0] - 1) * 6960 + GetPokePointer()));

                if (Editor::IsValid(location, pkmn)) {
                    if (KB<u8>(entry->Name() + ":", true, false, 2, amount, 0, 0, 30 - cloningSettings[1], Callback8)) {
                        for (int i = 0; i < amount; i++) {
                            if (Editor::IsValid(location + (i * 0xE8), pkmn)) {
                                if (!SetPokemon(location + (i * 0xE8) + 0xE8, pkmn))
                                    return;
                            }

                            else return;
                        }

                        Message::Completed();
                    }
                }
            }
        }
    }

    // Ty H4x0rSpooky for the help
    void CopyPokemonInTrade(MenuEntry *entry) {
        static const vector<u32> address = {
            Helpers::AutoRegion(
                Helpers::GetVersion<u32>(
                    {0x850CC94, 0x850CCC4, 0x8C861C8},
                    {0x8523D14, 0x8523D68, 0x8C9E134}),

                Helpers::GetVersion<u32>(
                    {0x32A87098, 0x32A870C8, 0x330D9838},
                    {0x30000630, 0x30000660, 0x33015AB0}
        ))};

        // Check if the user is in trade or not
        if (Process::Read32(address[0], data32) && data32 == 0x5544) {
            // Must have the user hold down the hotkey
            if (entry->Hotkeys[0].IsDown()) {
                // Reads if the Pokemon data is empty or not, otherwise copy the offered Pokemon
                if (Process::Read32(address[1], data32) && data32 != 0)
                    Process::CopyMemory((u8*)address[2], (u8*)address[1], 0xE8);
            }
        }
    }

    static u8 originalLoc[2], previousLoc[2];

    void KeepOriginalPokemonKB(MenuEntry *entry) {
        if (KB<u8>("Box:", true, false, 2, originalLoc[0], 0, 1, Helpers::AutoRegion(31, 32), Callback8)) {
            if (KB<u8>("Slot:", true, false, 2, originalLoc[1], 0, 1, 30, Callback8)) {
                Message::Completed();
                return;
            }
        }
    }

    void KeepOriginalPokemon(MenuEntry *entry) {
        PK6 *pkmn = new PK6;
        u32 location = (((originalLoc[1] - 1) * 0xE8) + ((originalLoc[0] - 1) * 6960 + GetPokePointer()));
        static vector<u32> original(0xE8);

        if (previousLoc[0] != originalLoc[0] || previousLoc[1] != originalLoc[1]) {
            if (Editor::IsValid(location, pkmn, entry))
                original = ProcessPlus::Read32(location, 0xE8);

            previousLoc[0] = originalLoc[0];
            previousLoc[1] = originalLoc[1];
        }

        if (ProcessPlus::Read32(location, 0xE8) != original)
            ProcessPlus::Write32(location, original, 0xE8);
    }

    void UnlockEveryBox(MenuEntry *entry) {
        static const u32 address = Helpers::AutoRegion(Helpers::GetVersion(0x8C6AC26, 0x8C7232A), Helpers::GetVersion(0x330D982D, 0x33015AA5));

        if (Process::Read8(address, data8) && data8 < Helpers::AutoRegion(31, 32)) {
            if (Process::Write8(address, Helpers::AutoRegion(31, 32))) {
                Message::Completed();
                return;
            }
        }

        Message::Warning();
    }

    namespace Gen6 {
        void PCAnywhere(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x3BBFA8, Helpers::PickGame(0x3D8748, 0x3D8744));
            static u32 original;
            static bool saved = false;

            if (!ProcessPlus::Write32(address, 0xE3A00004, original, entry, saved))
                return;
        }
    }

    namespace Gen7 {
        void PCAnywhere(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x597878, 0x37E5E4, 0x374C3C, 0x5978A8},
                    {0x5BBEE0, 0x37DB28, 0x38B030, 0x5BBF10}
            )};

            static const vector<u32> instruction = {
                0xE92D400E, 0xE59F1074, 0xE5912000, 0xE3A03000, 0xE5813000, 0xE3A03C13, 0xE2833093, 0xE1520003, 0x03A04000, 0x11A04000, 0xE8BD800E, 0xE350000E, Helpers::GetVersion<u32>(0xEAF77958, 0xEAF70DE3), 0xE92D400F, 0xE24DD010, 0xE3A00000, 0xE58D0000,
                0xE58D0004, 0xE58D0008, 0xE58D000C, 0xE1A03000, 0xE1A02000, 0xE3A01C13, 0xE2811093, 0xE59F0018, 0xE5801000, 0xE59F0014, 0xE5900000, Helpers::GetVersion<u32>(0xEBF7D6DC, 0xEBF77D15), 0xE3A00002, 0xE28DD010, 0xE8BD800F, Helpers::GetVersion<u32>(0x638000, 0x669000), Helpers::GetVersion<u32>(0x6740BC, 0x6A59C4)
            };

            static vector<u32> original(instruction.size());
            static vector<u32> revert(3);
            static bool saved[2] = {false, false};

            if (ProcessPlus::Write32(address[0], instruction, original, entry, saved[0])) {
                if (!ProcessPlus::Write32({address[1], address[2], address[3]}, {Helpers::GetVersion<u32>(0xEB0864A3, 0xEB08F8F7), Helpers::GetVersion<u32>(0xEB088B18, 0xEB08C3AA), Helpers::GetVersion<u32>(0x1AF77958, 0x1AF70DE3)}, revert, entry, saved[1]))
                    return;
            }
        }
    }
}