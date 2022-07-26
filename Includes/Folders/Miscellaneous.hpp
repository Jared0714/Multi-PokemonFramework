#ifndef MISCELLANEOUS_HPP
#define MISCELLANEOUS_HPP

#include <CTRPluginFramework.hpp>

using namespace CTRPluginFramework;

namespace Misc {
    void IsRenamable(MenuEntry *entry);
    void LearnAnyTeachables(MenuEntry *entry);
    void GetDayCareEgg(MenuEntry *entry);
    void FastDialogs(MenuEntry *entry);

    namespace Gen6 {
        void InstantEggHatch(MenuEntry *entry);
        void ViewValuesInSummary(MenuEntry *entry);
        void NoOutlines(MenuEntry *entry);
    }

    namespace Gen7 {
        void InstantEggHatch(MenuEntry *entry);
        void ViewValuesInSummary(MenuEntry *entry);
        void NoOutlines(MenuEntry *entry);
    }

    void BypassTextRestricts(MenuEntry *entry);
    void CustomKeyboardConfig(MenuEntry *entry);
    void CustomKeys(MenuEntry *entry);
}

#endif