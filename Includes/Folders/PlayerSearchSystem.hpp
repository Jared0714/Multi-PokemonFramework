#ifndef PLAYERSEARCHSYSTEM_HPP
#define PLAYERSEARCHSYSTEM_HPP

#include <CTRPluginFramework.hpp>

using namespace CTRPluginFramework;

namespace PSS {
    namespace GlobalTradeStation {
        void ConfigurationKB(MenuEntry *entry);
        void Configuration(MenuEntry *entry);
        void BypassLimit(MenuEntry *entry);
    }

    namespace Profile {
        void Icons(MenuEntry *entry);
        void Nices(MenuEntry *entry);
        void Wishes(MenuEntry *entry);
        void Message(MenuEntry *entry);
        void History(MenuEntry *entry);
        void Location(MenuEntry *entry);
        void Links(MenuEntry *entry);
        void MiniSurvey(MenuEntry *entry);
        void Greets(MenuEntry *entry);
    }

    void GuageKB(MenuEntry *entry);
    void Guage(MenuEntry *entry);
    void UnlockEveryPower(MenuEntry *entry);
    void ShoutOut(MenuEntry *entry);
    void ClearUsersKB(MenuEntry *entry);
    void ClearUsers(MenuEntry *entry);
    void BypassHackedIcons(MenuEntry *entry);
}

#endif