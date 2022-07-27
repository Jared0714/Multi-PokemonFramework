#ifndef BATTLE_HPP
#define BATTLE_HPP

#include <CTRPluginFramework.hpp>

using namespace CTRPluginFramework;

namespace Battle {
    namespace Universal {
        void SlotKB(MenuEntry *entry);
        void Condition(MenuEntry *entry);
        void StatisticsKB(MenuEntry *entry);
        void Statistics(MenuEntry *entry);
        void InvincibilityKB(MenuEntry *entry);
        void Invincibility(MenuEntry *entry);
        void Item(MenuEntry *entry);
        void Attacks(MenuEntry *entry);
        void PokeView(MenuEntry *entry);
        void AccessBag(MenuEntry *entry);
        void AlwaysShiny(MenuEntry *entry);
        void ExpMultiplierKB(MenuEntry *entry);
        void ExpMultiplier(MenuEntry *entry);
        void Shiny100(MenuEntry *entry);
        void DisableShinyLock(MenuEntry *entry);
    }

    namespace Gen6 {
        void Bypass1MegaRestrict(MenuEntry *entry);
        void NoEncounters(MenuEntry *entry);
        void Spawner(MenuEntry *entry);
        void RematchLegendary(MenuEntry *entry);
        void GuaranteedCatch(MenuEntry *entry);
        void CatchTrainersPokemon(MenuEntry *entry);
    }

    namespace Gen7 {
        void AlwaysCriticalHit(MenuEntry *entry);
        void Bypass1MegaRestrict(MenuEntry *entry);
        void InfiniteZMoves(MenuEntry *entry);
        void ZMovesWithoutCrystal(MenuEntry *entry);
        void NoEncounters(MenuEntry *entry);
        void Spawner(MenuEntry *entry);
        void RematchLegendary(MenuEntry *entry);
        void RefightTrainer(MenuEntry *entry);
        void RejectTrainerBattle(MenuEntry *entry);
        void GuaranteedCatch(MenuEntry *entry);
        void CanCatchTrial(MenuEntry *entry);
        void CatchTrainersPokemon(MenuEntry *entry);
    }

    void MusicKB(MenuEntry *entry);
    void Music(MenuEntry *entry);
}

#endif