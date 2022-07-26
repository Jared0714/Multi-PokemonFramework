#ifndef DECRYPTION_HPP
#define DECRYPTION_HPP

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "stdafx.hpp"

namespace CTRPluginFramework {
    struct PK6 {
        u32 encryptionConstant;
        u16 sanity;
        u16 checksum;

        // Block A
        u16 species;
        u16 heldItem;
        u16 trainerID;
        u16 secretID;
        u32 exp;
        u8 ability;
        u8 abilityNumber;
        u8 trainingBagHits;
        u8 trainingBag;
        u32 pid;
        u8 nature;
        u8 miscData;
        u8 evs[6];
        u8 contest[6];
        u8 markValue;
        u8 pkrus;
        u8 st1;
        u8 st2;
        u8 st3;
        u8 st4;
        u8 ribbons[6];
        u8 unused1[2];
        u8 ribbonCountMemoryContest;
        u8 ribbonCountMemoryBattle;
        u8 superTrainingFlags;
        u8 unused2[5];

        // Block B
        u8 nickname[26];
        u16 moves[4];
        u8 movePP[4];
        u8 movePPUps[4];
        u16 relearn[4];
        u8 secretSuperTrainingUnlockled;
        u8 unused3;
        u32 iv32;

        // Block C
        u8 hiddnTrnerName[26];
        u8 hiddnTrnerGender;
        u8 currentHandler;
        u8 geo1Region;
        u8 geo1Country;
        u8 geo2Region;
        u8 geo2Country;
        u8 geo3Region;
        u8 geo3Country;
        u8 geo4Region;
        u8 geo4Country;
        u8 geo5Region;
        u8 geo5Country;
        u8 unused4[4];
        u8 hiddnTrnerFriendship;
        u8 hiddnTrnerAffection;
        u8 hiddnTrnerIntensity;
        u8 hiddnTrnerMemory;
        u8 hiddnTrnerFeeling;
        u8 unused5;
        u16 hiddnTrnerTextVar;
        u8 unused6[4];
        u8 fullness;
        u8 enjoyment;

        // Block D
        u8 ogTrnerName[26];
        u8 ogTrnerFriendship;
        u8 ogTrnerAffection;
        u8 ogTrnerIntensity;
        u8 ogTrnerMemory;
        u16 ogTrnerTextVar;
        u8 ogTrnerFeeling;
        u8 eggDate[3];
        u8 metDate[3];
        u8 unused7;
        u16 eggLocation;
        u16 metLocation;
        u8 ball;
        u8 metLevel;
        u8 fatefulEnc;
        u8 version;
        u8 country;
        u8 region;
        u8 consoleRegion;
        u8 language;
        u8 unused8[4];
    };

    struct PK7 {
        u32 encryptionConstant;
        u16 sanity;
        u16 checksum;

        // Block A
        u16 species;
        u16 heldItem;
        u16 trainerID;
        u16 secretID;
        u32 exp;
        u8 ability;
        u8 abilityNumber;
        u8 markValue;
        u32 pid;
        u8 nature;
        u8 fatefulEncounterGenderForm;
        u8 evs[6];
        u8 contest[6];
        u8 resortEventStatus;
        u8 pkrus;
        u8 st1;
        u8 st2;
        u8 st3;
        u8 st4;
        u8 ribbons[6];
        u8 unused1[2];
        u8 ribbonCountMemoryContest;
        u8 ribbonCountMemoryBattle;
        u8 superTrainingFlags;
        u8 unused2[5];

        // Block B
        u8 nickname[26];
        u16 moves[4];
        u8 movePP[4];
        u8 movePPUps[4];
        u16 relearn[4];
        u8 secretSuperTrainingUnlockled;
        u8 unused3;
        u32 iv32;

        // Block C
        u8 hiddnTrnerName[26];
        u8 hiddnTrnerGender;
        u8 currentHandler;
        u8 geo1Region;
        u8 geo1Country;
        u8 geo2Region;
        u8 geo2Country;
        u8 geo3Region;
        u8 geo3Country;
        u8 geo4Region;
        u8 geo4Country;
        u8 geo5Region;
        u8 geo5Country;
        u8 unused4[4];
        u8 hiddnTrnerFriendship;
        u8 hiddnTrnerAffection;
        u8 hiddnTrnerIntensity;
        u8 hiddnTrnerMemory;
        u8 hiddnTrnerFeeling;
        u8 unused5;
        u16 hiddnTrnerTextVar;
        u8 unused6[4];
        u8 fullness;
        u8 enjoyment;

        // Block D
        u8 ogTrnerName[26];
        u8 ogTrnerFriendship;
        u8 ogTrnerAffection;
        u8 ogTrnerIntensity;
        u8 ogTrnerMemory;
        u16 ogTrnerTextVar;
        u8 ogTrnerFeeling;
        u8 eggDate[3];
        u8 metDate[3];
        u8 unused7;
        u16 eggLocation;
        u16 metLocation;
        u8 ball;
        u8 metLevel;
        u8 hyperTrainFlags;
        u8 version;
        u8 country;
        u8 region;
        u8 consoleRegion;
        u8 language;
        u8 unused8[4];
    };

    u32 GetPokePointer(void);

    const u8 blockPosition[4][24] = {
        {0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3},
        {1, 1, 2, 3, 2, 3, 0, 0, 0, 0, 0, 0, 2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2},
        {2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2, 0, 0, 0, 0, 0, 0, 3, 2, 3, 2, 1, 1},
        {3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0}
    };

    void Unshuffle(u8 *shuffled, u8 *poke, u32 sv);

    template <class PKX>
    void DecryptPokemon(u8 *ekm, PKX *poke) {
        // Encryption key from first 4 bytes of ekm
        u32 pokeVal = *(u32*)ekm;

        // Shuffle Value used to unshuffle the data
        u32 shuffleVal = (((pokeVal >> 0xD) & 0x1F) % 24);

        // Get initial seed from first 4 bytes, same as enc key
        u32 seed = pokeVal;

        // Decrypt data using seed
        for (int i = 8; i < 232; i += 2)  {
            seed = (0x41C64E6D * seed) + 0x00006073;
            ekm[i] ^= (u8)(seed >> 16);
            ekm[i + 1] ^= (u8)(seed >> 24);
        }

        // Unshuffle block data
        Unshuffle(ekm, (u8*)poke, shuffleVal);
    }

    template <class PKX>
    void EncryptPokemon(PKX *poke, u8 *ekm) {
        // Encryption key from first 4 bytes of ekm
        u32 pokeVal = *(u32*)ekm;

        // Shuffle Value used to reshuffle the data
        u32 shuffleVal = (((pokeVal >> 0xD) & 0x1F) % 24);

        // Get initial seed from first 4 bytes, same as enc key
        u32 seed = pokeVal;

        // Reshuffle block data
        for (int i = 0; i < 11; i++) {
            Unshuffle(ekm, (u8*)poke, shuffleVal);

            if (!Process::CopyMemory(ekm, poke, 232))
                return;
        }

        // Encrypt data using seed
        for (int i = 8; i < 232; i += 2)  {
            seed = (0x41C64E6D * seed) + 0x00006073;
            ekm[i] ^= (u8)(seed >> 16);
            ekm[i + 1] ^= (u8)(seed >> 24);
        }
    }

    template <class PKX>
    u16 Chcksum(PKX *poke) {
        u16 chksum = 0;

        for (u8 i = 4; i < 232 / 2; i++)
            chksum += *((u16*)(poke) + i);

        return chksum;
    }

    template <class PKX>
    bool IsValid(PKX *poke) {
        // Ensure sanity check
        if (!poke || poke->sanity)
            return false;

        // Calculate checksum
        if (Chcksum(poke) != poke->checksum)
            return false;

        // Ensure species is in a valid range
        return (poke->species >= 1 && poke->species <= (group == Group::XY || group == Group::ORAS ? 721 : 802));
    }

    template <class PKX>
    bool GetPokemon(u32 pokePointer, PKX *poke) {
        if (poke == 0 || pokePointer == 0)
            return false;

        // Load encrypted game data to ekm
        u8 ekm[232];

        if (!Process::CopyMemory(&ekm, (u8*)pokePointer, 232))
            return false;

        // Decrypt data and store in struct
        DecryptPokemon(ekm, poke);

        // Check validity and return check
        return (IsValid(poke));
    }

    template <class PKX>
    bool SetPokemon(u32 pokePointer, PKX *poke) {
        if (poke == 0 || pokePointer == 0)
            return false;

        // Fix checksum
        poke->checksum = Chcksum(poke);

        // Load decrypted struct data to ekm
        u8 ekm[232];

        if (!Process::CopyMemory(&ekm, poke, 232))
            return false;

        // Encrypt data and store in array
        EncryptPokemon(poke, ekm);

        // Write array data to game
        if (Process::Patch(pokePointer, ekm, 232))
            return true;

        MessageBox(CenterAlign("Failed to encrypt or write data!"), DialogType::DialogOk)();
        return false;
    }

    template <class PKX>
    u8 IsShiny(PKX *poke) {
        return (poke->trainerID ^ poke->secretID ^ (u16)(poke->pid & 0x0000FFFF) ^ (u16)((poke->pid & 0xFFFF0000) >> 16)) < 16;
    }

    template <class PKX>
    void MakeShiny(PKX *poke, bool shinify) {
        u16 sxor = (poke->trainerID ^ poke->secretID ^ (u16)(poke->pid & 0x0000FFFF)) & 0xFFF0;

        if (shinify)
            poke->pid = (poke->pid & 0x000FFFFF) | (sxor << 16);

        else poke->pid = Utils::Random(1, 0xFFFFFFFF);
    }

    template <class PKX>
    void SetSpecies(PKX *poke, u16 pokeNo) {
        if (poke->species != pokeNo) {
            if (pokeNo > 0 && pokeNo <= Helpers::AutoRegion(721, Helpers::GetVersion(802, 807)))
                poke->species = pokeNo;
        }

        else Message::Warning;
    }

    template<class PKX>
    void SetIsNicknamed(PKX *poke, int option) {
        poke->iv32 = ((poke->iv32 & 0x7FFFFFFFu) | (option ? 0x80000000u : 0u));
    }

    template<class PKX>
    void SetNickname(PKX *poke, String name) {
        Process::WriteString((u32)poke->nickname, name, StringFormat::Utf16);
    }

    static const int expTable[100][6] = {{0, 0, 0, 0, 0, 0}, {8, 15, 4, 9, 6, 10}, {27, 52, 13, 57, 21, 33}, {64, 122, 32, 96, 51, 80}, {125, 237, 65, 135, 100, 156}, {216, 406, 112, 179, 172, 270}, {343, 637, 178, 236, 274, 428}, {512, 942, 276, 314, 409, 640}, {729, 1326, 393, 419, 583, 911}, {1000, 1800, 540, 560, 800, 1250}, {1331, 2369, 745, 742, 1064, 1663}, {1728, 3041, 967, 973, 1382, 2160}, {2197, 3822, 1230, 1261, 1757, 2746}, {2744, 4719, 1591, 1612, 2195, 3430}, {3375, 5737, 1957, 2035, 2700, 4218}, {4096, 6881, 2457, 2535, 3276, 5120}, {4913, 8155, 3046, 3120, 3930, 6141}, {5832, 9564, 3732, 3798, 4665, 7290}, {6859, 11111, 4526, 4575, 5487, 8573}, {8000, 12800, 5440, 5460, 6400, 10000}, {9261, 14632, 6482, 6458, 7408, 11576}, {10648, 16610, 7666, 7577, 8518, 13310}, {12167, 18737, 9003, 8825, 9733, 15208}, {13824, 21012, 10506, 10208, 11059, 17280}, {15625, 23437, 12187, 11735, 12500, 19531}, {17576, 26012, 14060, 13411, 14060, 21970}, {19683, 28737, 16140, 15244, 15746, 24603}, {21952, 31610, 18439, 17242, 17561, 27440}, {24389, 34632, 20974, 19411, 19511, 30486}, {27000, 37800, 23760, 21760, 21600, 33750}, {29791, 41111, 26811, 24294, 23832, 37238}, {32768, 44564, 30146, 27021, 26214, 40960}, {35937, 48155, 33780, 29949, 28749, 44921}, {39304, 51881, 37731, 33084, 31443, 49130}, {42875, 55737, 42017, 36435, 34300, 53593}, {46656, 59719, 46656, 40007, 37324, 58320}, {50653, 63822, 50653, 43808, 40522, 63316}, {54872, 68041, 55969, 47846, 43897, 68590}, {59319, 72369, 60505, 52127, 47455, 74148}, {64000, 76800, 66560, 56660, 51200, 80000}, {68921, 81326, 71677, 61450, 55136, 86151}, {74088, 85942, 78533, 66505, 59270, 92610}, {79507, 90637, 84277, 71833, 63605, 99383}, {85184, 95406, 91998, 77440, 68147, 106480}, {91125, 100237, 98415, 83335, 72900, 113906}, {97336, 105122, 107069, 89523, 77868, 121670}, {103823, 110052, 114205, 96012, 83058, 129778}, {110592, 115015, 123863, 102810, 88473, 138240}, {117649, 120001, 131766, 109923, 94119, 147061}, {125000, 125000, 142500, 117360, 100000, 156250}, {132651, 131324, 151222, 125126, 106120, 165813}, {140608, 137795, 163105, 133229, 112486, 175760}, {148877, 144410, 172697, 141677, 119101, 186096}, {157464, 151165, 185807, 150476, 125971, 196830}, {166375, 158056, 196322, 159635, 133100, 207968}, {175616, 165079, 210739, 169159, 140492, 219520}, {185193, 172229, 222231, 179056, 148154, 231491}, {195112, 179503, 238036, 189334, 156089, 243890}, {205379, 186894, 250562, 199999, 164303, 256723}, {216000, 194400, 267840, 211060, 172800, 270000}, {226981, 202013, 281456, 222522, 181584, 283726}, {238328, 209728, 300293, 234393, 190662, 297910}, {250047, 217540, 315059, 246681, 200037, 312558}, {262144, 225443, 335544, 259392, 209715, 327680}, {274625, 233431, 351520, 272535, 219700, 343281}, {287496, 241496, 373744, 286115, 229996, 359370}, {300763, 249633, 390991, 300140, 240610, 375953}, {314432, 257834, 415050, 314618, 251545, 393040}, {328509, 267406, 433631, 329555, 262807, 410636}, {343000, 276458, 459620, 344960, 274400, 428750}, {357911, 286328, 479600, 360838, 286328, 447388}, {373248, 296358, 507617, 377197, 298598, 466560}, {389017, 305767, 529063, 394045, 311213, 486271}, {405224, 316074, 559209, 411388, 324179, 506530}, {421875, 326531, 582187, 429235, 337500, 527343}, {438976, 336255, 614566, 447591, 351180, 548720}, {456533, 346965, 639146, 466464, 365226, 570666}, {474552, 357812, 673863, 485862, 379641, 593190}, {493039, 367807, 700115, 505791, 394431, 616298}, {512000, 378880, 737280, 526260, 409600, 640000}, {531441, 390077, 765275, 547274, 425152, 664301}, {551368, 400293, 804997, 568841, 441094, 689210}, {571787, 411686, 834809, 590969, 457429, 714733}, {592704, 423190, 877201, 613664, 474163, 740880}, {614125, 433572, 908905, 636935, 491300, 767656}, {636056, 445239, 954084, 660787, 508844, 795070}, {658503, 457001, 987754, 685228, 526802, 823128}, {681472, 467489, 1035837, 710266, 545177, 851840}, {704969, 479378, 1071552, 735907, 563975, 881211}, {729000, 491346, 1122660, 762160, 583200, 911250}, {753571, 501878, 1160499, 789030, 602856, 941963}, {778688, 513934, 1214753, 816525, 622950, 973360}, {804357, 526049, 1254796, 844653, 643485, 1005446}, {830584, 536557, 1312322, 873420, 664467, 1038230}, {857375, 548720, 1354652, 902835, 685900, 1071718}, {884736, 560922, 1415577, 932903, 707788, 1105920}, {912673, 571333, 1460276, 963632, 730138, 1140841}, {941192, 583539, 1524731, 995030, 752953, 1176490}, {970299, 591882, 1571884, 1027103, 776239, 1212873}, {1000000, 600000, 1640000, 1059860, 800000, 1250000}};

    template<class PKX>
    void SetLevel(PKX *poke, int level, int growth) {
        poke->exp = expTable[level - 1][growth];
    }

    template <class PKX>
    void SetNature(PKX *poke, int option) {
        poke->nature = option;
    }

    template<class PKX>
    void SetGender(PKX *poke, int option) {
        poke->miscData = ((poke->miscData & ~0x6) | (option << 1));
    }

    template<class PKX>
    void SetForm(PKX *poke, int option) {
        poke->miscData = (poke->miscData & 0x7) | (option << 3);
    }

    template<class PKX>
    void SetHeldItem(PKX *poke, int id) {
        poke->heldItem = id;
    }

    template <class PKX>
    void SetAbility(PKX *poke, int option) {
        poke->ability = option;
    }

    template <class PKX>
    void SetFriendship(PKX *poke, int amount) {
        poke->hiddnTrnerFriendship = amount;
    }

    template<class PKX>
    void SetLanguage(PKX *poke, int languageID) {
        poke->language = languageID;
    }

    template<class PKX>
    void SetIsEgg(PKX *poke, int option) {
        poke->iv32 = (poke->iv32 & ~0x40000000u) | (option ? 0x40000000u : 0u);
    }

    template<class PKX>
    void SetPokerus(PKX *poke, int days, int strain) {
        poke->pkrus = ((poke->pkrus & ~0xF) | days);
        poke->pkrus = ((poke->pkrus & 0xF) | strain << 4);
    }

    template<class PKX>
    void SetCountry(PKX *poke, int countryID) {
        poke->country = countryID;
    }

    template<class PKX>
    void SetRegion(PKX *poke, int regionID) {
        poke->region = regionID;
    }

    template<class PKX>
    void SetConsRegion(PKX *poke, int consoleRegID) {
        poke->consoleRegion = consoleRegID;
    }

    template<class PKX>
    void SetOrigin(PKX *poke, int ver) {
        poke->version = ver;
    }

    template<class PKX>
    void SetMetLocation(PKX *poke, int loc, bool isEgg) {
        if (isEgg) {
            poke->eggLocation = loc;
            return;
        }

        else poke->metLocation = loc;
    }

    template<class PKX>
    void SetBall(PKX *poke, int option) {
        poke->ball = option;
    }

    template<class PKX>
    void SetMetLevel(PKX *poke, int value) {
        poke->metLevel = ((poke->metLevel & 0x80) | value);
    }

    template<class PKX>
    void SetMetDate(PKX *poke, bool setYear, bool setMonth, bool setDay, bool isEgg, u8 vals[]) {
        int canSet[3] = {setYear, setMonth, setDay}, setVals[3] = {vals[0], vals[1], vals[2]};

        for (int i = 0; i < 3; i++) {
            if (canSet[i] == 1) {
                if (!isEgg)
                    poke->metDate[i] = setVals[i];

                else poke->eggDate[i] = setVals[i];
            }
        }
    }

    template<class PKX>
    void SetIsFatefulEnc(PKX *poke, int option) {
        poke->fatefulEnc = ((poke->fatefulEnc & ~0x1) | (option ? 1 : 0));
    }

    template <class PKX>
    void SetIV(PKX *poke, int index, int value) {
        if (value > 31)
            return;

        poke->iv32 = (poke->iv32 & ~(0x1F << (5 * index))) | (value << (5 * index));
    }

    template <class PKX>
    void SetEV(PKX *poke, int index, int value) {
        if (value > 252)
            return;

        int count = 0;

        for (int i = 0; i < 6; i++) {
            if (poke->evs[i] == 252)
                count++;
        }

        if (count > 2 || (count == 2 && value > 6))
            return;

        poke->evs[index] = value;
    }

    template <class PKX>
    void SetContestStats(PKX *poke, int index, int value) {
        if (value > 255)
            return;

        for (int i = 0; i < 6; i++) {
            if (index == i) {
                poke->contest[i] = value;
                return;
            }
        }
    }

    template <class PKX>
    void SetMoves(PKX *poke, int index, int id, bool isRelearnable) {
        for (int i = 0; i < 4; i++) {
            if (index == i) {
                if (!isRelearnable)
                    poke->moves[i] = id;

                else poke->relearn[i] = id;
            }
        }
    }

    template <class PKX>
    void SetPPUps(PKX *poke, int index, int value) {
        for (int i = 0; i < 4; i++) {
            if (index == i)
                poke->movePPUps[i] = value;
        }
    }

    template <class PKX>
    void SetSID(PKX *poke, int value) {
        if (value > 65535)
            return;

        poke->secretID = value;
    }

    template <class PKX>
    void SetTID(PKX *poke, int value) {
        if (value > 65535)
            return;

        poke->trainerID = value;
    }

    template <class PKX>
    void SetOTName(PKX *poke, String name) {
        Process::WriteString((u32)poke->ogTrnerName, name, StringFormat::Utf16);
    }

    template <class PKX>
    void SetLatestHandler(PKX *poke, String name) {
        Process::WriteString((u32)poke->hiddnTrnerName, name, StringFormat::Utf16);
    }

    template <class PKX>
    void SetRibbons(PKX *poke, int category, int index, bool obtain) {
        poke->ribbons[category] = ((poke->ribbons[category] & ~(1 << index)) | (obtain ? 1 << index : 0));
    }
}

#endif