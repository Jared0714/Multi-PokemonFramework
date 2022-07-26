#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

#include <cmath>
#include <algorithm>
#include <iterator>

using namespace CTRPluginFramework;

namespace Trainer {
    namespace Info {
        static int selectID;
        static u32 newIDVals[2];

        void IDs(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::AutoRegion<u32>(
                    Helpers::GetVersion<u32>(
                        {0x8C79C3C, 0x8C81340},
                        {0x8C79C3E, 0x8C81342}),

                    Helpers::GetVersion<u32>(
                        {0x330D67D0, 0x33012818},
                        {0x330D67D2, 0x3301281A}
            ))};

            static const vector<string> options = {"Trainer", "Secret"};
            KeyboardPlus keyboard;

            start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, selectID) != -1) {
                if (KB<u32>(options[selectID] + ":", true, false, 5, newIDVals[selectID], 0, 1, 65535, Callback32)) {
                    Process::Write16(address[selectID], newIDVals[selectID]);
                    Message::Completed();
                }

                else goto start;
            }
        }

        string nameVal;

        void Name(MenuEntry *entry) {
            static const u32 address = Helpers::AutoRegion(Helpers::GetVersion(0x8C79C84, 0x8C81388), Helpers::GetVersion(0x330D6808, 0x33012850));

            if (KB<string>(entry->Name() + ":", true, false, 16, nameVal, "")) {
                if (Process::WriteString(address, nameVal, StringFormat::Utf16))
                    Message::Completed();
            }
        }

        void CopyToName(MenuEntry *entry) {
            static const u32 address[2] = {
                Helpers::GetVersion<u32>(0x8C79D62, 0x8C81466),
                Helpers::GetVersion<u32>(0x8C79C84, 0x8C81388)
            };

            if (entry->Hotkeys[0].IsPressed())
                Process::CopyMemory((void*)address[1], (u8*)address[0], 0x26);
        }

        int timeLimit(int index) {
            return (index == 0 ? 999 : 59);
        }

        static u16 time[3];
        static int timeChoice, canSetTime[3];

        void PlayTimeKB(MenuEntry *entry) {
            static const vector<string> options = {"Hours", "Minutes", "Seconds"};
            KeyboardPlus keyboard;

            start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, timeChoice) != -1) {
                if (KB<u16>(options[timeChoice] + ":", true, false, trunc(log10(timeLimit(timeChoice))) + 1, time[timeChoice], 0, 1, timeLimit(timeChoice), Callback16)) {
                    canSetTime[timeChoice] = 1;
                    Message::Completed();
                }

                else goto start;
            }
        }

        void PlayTime(MenuEntry *entry) {
            static const u32 address = Helpers::AutoRegion(Helpers::GetVersion(0x8CE2814, 0x8CFBD88), Helpers::GetVersion(0x34197648, 0x33F8127C));

            for (int i = 0; i < 3; i++) {
                if (canSetTime[i] == true)
                    (i == 0) ? Process::Write16(address, time[0]) : Process::Write8(address + 1 + i, time[i]);
            }
        }

        static int lang;

        void LanguageKB(MenuEntry *entry) {
            static const vector<string> options = {"Japanese", "English", "French", "Italian", "German", "Spanish", "Korean"};
            KeyboardPlus keyboard;

            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, lang) != -1)
                Message::Completed();
        }

        void Language(MenuEntry *entry) {
            static const u32 address = Helpers::AutoRegion(Helpers::GetVersion(0x8C79C69, 0x8C8136D), Helpers::GetVersion(0x330D6805, 0x3301284D));

            if (Process::Read8(address, data8) && data8 != (lang == 5 ? 7 : lang + 1))
                Process::Write8(address, (lang == 5 ? 7 : lang + 1));
        }
    }

    static u32 moneyAmount;

    void MoneyKB(MenuEntry *entry) {
        if (KB<u32>(entry->Name() + ":", true, false, 7, moneyAmount, 0, 0, 9999999, Callback32))
            Message::Completed();
    }

    void Money(MenuEntry *entry) {
        static const u32 address = Helpers::AutoRegion<u32>(Helpers::GetVersion<u32>(0x8C6A6AC, 0x8C71DC0), Helpers::GetVersion<u32>(0x330D8FC0, 0x33015210));

        if (Process::Read32(address, data32) && data32 != moneyAmount)
            Process::Write32(address, moneyAmount);
    }

    static u16 battlePoints;

    void BattlePointsKB(MenuEntry *entry) {
        if (KB<u16>(entry->Name() + ":", true, false, 4, battlePoints, 0, 0, 9999, Callback16))
            Message::Completed();
    }

    void BattlePoints(MenuEntry *entry) {
        static const u32 address = Helpers::AutoRegion<u32>(Helpers::GetVersion<u32>(0x8C6A6E0, 0x8C71DE8), Helpers::GetVersion<u32>(0x330D90D8, 0x33015328));

        if (Process::Read16(address, data16) && data16 != moneyAmount)
            Process::Write16(address, battlePoints);
    }

    namespace Pouch {
        static u16 itemAmount;

        void ItemsKB(MenuEntry *entry) {
            if (KB<u16>(entry->Name() + ":", true, false, 3, itemAmount, 0, 0, 999, Callback16))
                Message::Completed();
        }

        static const vector<int> items = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 112, 116, 117, 118, 119, 135, 136, 213, 214, 215, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 492, 493, 494, 495, 496, 497, 498, 499, 537, 538, 539, 540, 541, 542, 543, 544, 545, 546, 547, 548, 549, 550, 551, 552, 553, 554, 555, 556, 557, 558, 559, 560, 561, 562, 563, 564, 571, 572, 573, 576, 577, 580, 581, 582, 583, 584, 585, 586, 587, 588, 589, 590, 639, 640, 644, 646, 647, 648, 649, 650, 656, 657, 658, 659, 660, 661, 662, 663, 664, 665, 666, 667, 668, 669, 670, 671, 672, 673, 674, 675, 676, 677, 678, 679, 680, 681, 682, 683, 684, 685, 699, 704, 710, 711, 715};

        void Items(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::AutoRegion<u32>(
                    Helpers::GetVersion<u32>(
                        {0x8C67564, 0x8C67566},
                        {0x8C6EC70, 0x8C6EC72}),

                    Helpers::GetVersion<u32>(
                        {0x330D5934, 0x330D5936},
                        {0x33011934, 0x33011936}
            ))};

            vector<int> getItems;
            copy(items.begin(), items.end(), back_inserter(getItems));
            (group != Group::XY ? getItems.insert(getItems.end(), {534, 535, 752, 753, 754, 755, 756, 757, 758, 759, 760, 761, 762, 763, 764, 767, 768, 769, 770}) : getItems.insert(getItems.end(), {65, 66, 67}));

            if (group == Group::XY || group == Group::ORAS)
                getItems.insert(getItems.end(), {500, 652, 653, 654, 655});

            if (group == Group::SM || group == Group::USUM)
                getItems.insert(getItems.end(), {111, 137, 795, 796, 844, 846, 849, 851, 853, 854, 855, 856, 879, 880, 881, 882, 883, 884, 904, 905, 906, 907, 908, 909, 910, 911, 912, 913, 914, 915, 916, 917, 918, 919, 920});

            sort(getItems.begin(), getItems.end());

            for (int counter = 0; counter < getItems.size(); counter++)
                (group == Group::XY || group == Group::ORAS ? Process::Write32(address[0] + (0x4 * counter), getItems[counter] | (itemAmount << 16)) : Process::Write32(address[0] + (0x4 * counter), getItems[counter] + (itemAmount << 10)));
        }

        static u16 medAmount;

        void MedicinesKB(MenuEntry *entry) {
            if (KB<u16>(entry->Name() + ":", true, false, 3, medAmount, 0, 0, 999, Callback16))
                Message::Completed();
        }

        static const vector<int> medicines = {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 134, 504, 565, 566, 567, 568, 569, 570, 591, 645, 708, 709};

        void Medicines(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::AutoRegion<u32>(
                    Helpers::GetVersion<u32>(
                        {0x8C67ECC, 0x8C67ECE},
                        {0x8C6F5E0, 0x8C6F5E2}),

                    Helpers::GetVersion<u32>(
                        {0x330D647C, 0x330D647E},
                        {0x330124A8, 0x330124AA}
            ))};

            vector<int> getMedicines;
            copy(medicines.begin(), medicines.end(), back_inserter(getMedicines));
            (group == Group::XY || group == Group::ORAS ? getMedicines.push_back(571) : getMedicines.push_back(852));

            if (group != Group::XY)
                getMedicines.insert(getMedicines.end(), {65, 66, 67});

            sort(getMedicines.begin(), getMedicines.end());

            for (int counter = 0; counter < getMedicines.size(); counter++)
                (group == Group::XY || group == Group::ORAS ? Process::Write32(address[0] + (0x4 * counter), getMedicines[counter] | (medAmount << 16)) : Process::Write32(address[0] + (0x4 * counter), getMedicines[counter] + (medAmount << 10)));
        }

        vector<int> berries = {149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 686, 687, 688};
        static u16 berryAmount;

        void BerriesKB(MenuEntry *entry) {
            if (KB<u16>(entry->Name() + ":", true, false, 3, berryAmount, 0, 0, 999, Callback16))
                Message::Completed();
        }

        void Berries(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::AutoRegion<u32>(
                    Helpers::GetVersion<u32>(
                        {0x8C67FCC, 0x8C67FCE},
                        {0x8C6F6E0, 0x8C6F6E2}),

                    Helpers::GetVersion<u32>(
                        {0x330D657C, 0x330D657E},
                        {0x33012598, 0x3301259A}
            ))};

            sort(berries.begin(), berries.end());

            for (int counter = 0; counter < berries.size(); counter++)
                (group == Group::XY || group == Group::ORAS ? Process::Write32(address[0] + (0x4 * counter), berries[counter] | (berryAmount << 16)) : Process::Write32(address[0] + (0x4 * counter), berries[counter] + (berryAmount << 10)));
        }

        static const vector<int> teachables = {328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 618, 619, 620, 690, 691, 692, 693, 694};

        void TMsHMs(void) {
            static const vector<u32> address = {
                Helpers::AutoRegion<u32>(
                    Helpers::GetVersion<u32>(
                        {0x8C67D24, 0x8C67D26},
                        {0x8C6F430, 0x8C6F432}),

                    Helpers::GetVersion<u32>(
                        {0x330D62CC, 0x330D62CE},
                        {0x330122F8, 0x330122FA}
            ))};

            vector<int> getTeachables;
            copy(teachables.begin(), teachables.end(), back_inserter(getTeachables));

            if (group == Group::XY || group == Group::ORAS) {
                getTeachables.insert(getTeachables.end(), {420, 421, 422, 423, 424});

                if (group == Group::ORAS)
                    getTeachables.insert(getTeachables.end(), {425, 737});
            }

            sort(getTeachables.begin(), getTeachables.end());

            for (int counter = 0; counter < getTeachables.size(); counter++)
                (group == Group::XY || group == Group::ORAS ? Process::Write32(address[0] + (0x4 * counter), getTeachables[counter] | (1 << 16)) : Process::Write32(address[0] + (0x4 * counter), getTeachables[counter] + (1 << 10)));

            Message::Completed();
        }

        void KeyItems(void) {
            static const vector<u32> address = {
                Helpers::AutoRegion<u32>(
                    Helpers::GetVersion<u32>(
                        {0x8C67BA4, 0x8C67BA6},
                        {0x8C6F2B0, 0x8C6F2B2}),

                    Helpers::GetVersion<u32>(
                        {0x330D5FEC, 0x330D5FEE},
                        {0x33011FE0, 0x33011FE2}
            ))};

            vector<int> getKeyItems = {216, 465, 466, 628, 629, 631, 632, 638};
            (group != Group::XY ? getKeyItems.insert(getKeyItems.end(), {765}) : getKeyItems.insert(getKeyItems.end(), {431, 442, 450, 641, 642, 643, 689, 695, 696, 698, 700, 701, 702, 703, 705, 712, 713, 714}));

            if (group == Group::ORAS)
                getKeyItems.insert(getKeyItems.end(), {457, 474, 503, 718, 719, 720, 721, 722, 724, 725, 726, 727, 728, 729, 730, 731, 732, 733, 734, 735, 736, 738, 739, 740, 741, 742, 743, 744, 751, 771, 772, 774, 775});

            if (group == Group::XY || group == Group::ORAS)
                getKeyItems.insert(getKeyItems.end(), {447, 471, 697});

            if (group == Group::SM || group == Group::USUM)
                getKeyItems.insert(getKeyItems.end(), {705, 706, 765, 773, 797, 841, 842, 843, 845, 847, 850, 857, 858, 860});

            sort(getKeyItems.begin(), getKeyItems.end());

            for (int counter = 0; counter < getKeyItems.size(); counter++)
                (group == Group::XY || group == Group::ORAS ? Process::Write32(address[0] + (0x4 * counter), getKeyItems[counter] | (1 << 16)) : Process::Write32(address[0] + (0x4 * counter), getKeyItems[counter] + (1 << 10)));

            Message::Completed();
        }

        static int unlockCase;

        void Unlockable(MenuEntry *entry) {
            static const vector<string> options = {"TMs & HMs", "Key Items"};
            KeyboardPlus keyboard;

            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, unlockCase) != -1)
                (unlockCase == 0 ? TMsHMs() : KeyItems());
        }
    }

    namespace Gen6 {
        static u32 pokeMiles;

        void PokeMilesKB(MenuEntry *entry) {
            if (KB<u32>(entry->Name() + ":", true, false, 7, pokeMiles, 0, 0, 9999999, Callback32))
                Message::Completed();
        }

        void PokeMiles(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion<u32>(0x8C82BA0, 0x8C8B36C);

            if (Process::Read32(address, data32) && data32 != pokeMiles)
                Process::Write32(address, pokeMiles);
        }

        static u8 badgesUnlocked;

        void Badges(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion<u32>(0x8C6A6B0, 0x8C71DC4l);
            static const u8 check[9] = {0x0, 0x1, 0x3, 0x7, 0xF, 0x1F, 0x3F, 0x7F, 0xFF};

            if (KB<u8>(entry->Name() + ":", true, false, 1, badgesUnlocked, 0, 0, 8, Callback8)) {
                if (Process::Write8(address, check[badgesUnlocked]))
                    Message::Completed();
            }
        }
    }

    namespace Gen7 {
        static const vector<int> crystals = {807, 808, 809, 810, 811, 812, 813, 814, 815, 816, 817, 818, 819, 820, 821, 822, 823, 824, 825, 826, 827, 828, 829, 830, 831, 832, 833, 834, 835};

        void ZCrystals(MenuEntry *entry) {
            static const u32 address = {Helpers::GetVersion<u32>(0x330D669C, 0x330126A4)};
            static vector<int> getCrystals;
            copy(crystals.begin(), crystals.end(), back_inserter(getCrystals));

            if (group == Group::USUM)
                getCrystals.insert(getCrystals.end(), {927, 928, 929, 930, 931, 932});

            sort(getCrystals.begin(), getCrystals.end());

            for (int counter = 0; counter < crystals.size(); counter++)
                Process::Write32(address + (0x4 * counter), getCrystals[counter] + (1 << 10));

            Message::Completed();
        }
    }

    static int dexStatus;

    void Pokedex(MenuEntry *entry) {
        static const vector<u32> address = {
            Helpers::AutoRegion(
                Helpers::GetVersion<u32>(
                    {0x8C7A948, 0x8C7A8E8, 0x8C7A812, 0x8C7A8E4},
                    {0x8C8204C, 0x8C81FEC, 0x8C81F20, 0x8C81FE8}),

                Helpers::GetVersion<u32>(
                    {0x330D7DAC, 0x330D7D48, 0x330D780F, 0x330D7818},
                    {0x33013DF4, 0x33013D90, 0x330138CF, 0x330138D8}
        ))};

        static const vector<string> options = {"Unlock"};
        KeyboardPlus keyboard;

        if (keyboard.SetKeyboard(entry->Name() + ":", true, options, dexStatus) != -1) {
            if ((Bit::Read8(address[2], data8, Helpers::AutoRegion(true, false)) && data8 != Helpers::AutoRegion(5, 3)) || (Bit::Read8(address[3], data8, true) && data8 != 7)) {
                if (Bit::Write8(address[2], Helpers::AutoRegion(5, 3), Helpers::AutoRegion(true, false))) {
                    if (Bit::Write8(address[3], 7, true))
                        Message::Completed();
                }
            }

            else Message::Warning();
        }
    }
}