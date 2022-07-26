#ifndef TRAINER_HPP
#define TRAINER_HPP

#include <CTRPluginFramework.hpp>

using namespace CTRPluginFramework;

namespace Trainer {
    namespace Info {
        void IDs(MenuEntry *entry);
        void Name(MenuEntry *entry);
        void CopyToName(MenuEntry *entry);
        void PlayTimeKB(MenuEntry *entry);
        void PlayTime(MenuEntry *entry);
        void LanguageKB(MenuEntry *entry);
        void Language(MenuEntry *entry);
    }

    void MoneyKB(MenuEntry *entry);
    void Money(MenuEntry *entry);
    void BattlePointsKB(MenuEntry *entry);
    void BattlePoints(MenuEntry *entry);

    namespace Pouch {
        void ItemsKB(MenuEntry *entry);
        void Items(MenuEntry *entry);
        void MedicinesKB(MenuEntry *entry);
        void Medicines(MenuEntry *entry);
        void BerriesKB(MenuEntry *entry);
        void Berries(MenuEntry *entry);
        void Unlockable(MenuEntry *entry);
    }

    namespace Gen6 {
        void ModelSwapKB(MenuEntry *entry);
        void ModelSwap(MenuEntry *entry);
        void PokeMilesKB(MenuEntry *entry);
        void PokeMiles(MenuEntry *entry);
        void Badges(MenuEntry *entry);
    }

    namespace Gen7 {
        void ZCrystals(MenuEntry *entry);
    }

    void Pokedex(MenuEntry *entry);
}

#endif