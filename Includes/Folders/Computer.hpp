#ifndef COMPUTER_HPP
#define COMPUTER_HPP

#include <CTRPluginFramework.hpp>

using namespace CTRPluginFramework;

namespace Computer {
    void PCBackup(MenuEntry *entry);

    namespace Editor {
        bool Setup(void);
        void Initialize(MenuEntry *entry);
        bool IsValid(u32 pointer, PK6 *pkmn);
        bool IsValid(u32 pointer, PK6 *pkmn, MenuEntry *entry);
        void Shinify(MenuEntry *entry);
        void Species(MenuEntry *entry);
        void IsNicknamed(MenuEntry *entry);
        void Nickname(MenuEntry *entry);
        void Gender(MenuEntry *entry);
        void Level(MenuEntry *entry);
        void Nature(MenuEntry *entry);
        void Form(MenuEntry *entry);
        void HeldItem(MenuEntry *entry);
        void Ability(MenuEntry *entry);
        void Friendship(MenuEntry *entry);
        void Language(MenuEntry *entry);
        void IsEgg(MenuEntry *entry);
        void Pokerus(MenuEntry *entry);
        void Country(MenuEntry *entry);
        void Region(MenuEntry *entry);
        void ConsoleRegion(MenuEntry *entry);
        void OriginGame(MenuEntry *entry);
        void MetLocation(MenuEntry *entry);
        void Ball(MenuEntry *entry);
        void MetLevel(MenuEntry *entry);
        void MetDate(MenuEntry *entry);
        void IsFatefulEncounter(MenuEntry *entry);
        void EggMetLoc(MenuEntry *entry);
        void EggMetDate(MenuEntry *entry);
        void IVs(MenuEntry *entry);
        void EVs(MenuEntry *entry);
        void Contest(MenuEntry *entry);
        void CurrentMoves(MenuEntry *entry);
        void PPUps(MenuEntry *entry);
        void RelearnMoves(MenuEntry *entry);
        void SID(MenuEntry *entry);
        void TID(MenuEntry *entry);
        void OTName(MenuEntry *entry);
        void LatestHandler(MenuEntry *entry);
        void Ribbons(MenuEntry *entry);
    }

    void Cloning(MenuEntry *entry);
    void CopyPokemonInTrade(MenuEntry *entry);
    void KeepOriginalPokemonKB(MenuEntry *entry);
    void KeepOriginalPokemon(MenuEntry *entry);
    void UnlockEveryBox(MenuEntry *entry);

    namespace Gen6 {
        void PCAnywhere(MenuEntry *entry);
    }

    namespace Gen7 {
        void PCAnywhere(MenuEntry *entry);
    }
}

#endif