#ifndef FESTIVALPLAZA_HPP
#define FESTIVALPLAZA_HPP

#include <CTRPluginFramework.hpp>

using namespace CTRPluginFramework;

namespace Plaza {
    namespace GlobalTradeStation {
        void ConfigurationKB(MenuEntry *entry);
        void Configuration(MenuEntry *entry);
        void BypassLimit(MenuEntry *entry);
    }

    void CurrentRank(MenuEntry *entry);
    void FCCollected(MenuEntry *entry);

    namespace Profile {
        void CurrentFC(MenuEntry *entry);
        void GuestsInteracted(MenuEntry *entry);
        void FacilitiesHosted(MenuEntry *entry);
        void MissionsParticipated(MenuEntry *entry);
    }

    void ImageCrashCounter(MenuEntry *entry);
    void AvoidSoftban(MenuEntry *entry);
}

#endif