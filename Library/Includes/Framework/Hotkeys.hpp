#ifndef HOTKEYS_HPP
#define HOTKEYS_HPP

#include <CTRPluginFramework.hpp>
#include "../../../Includes/stdafx.hpp"

#include "../CTRPluginFramework/System/Process.hpp"
#include "../CTRPluginFrameworkImpl/System/ProcessImpl.hpp"

namespace CTRPluginFramework {
    MenuEntry *EntryWithHotkey(MenuEntry *entry, const Hotkey &hotkey);
    MenuEntry *EntryWithHotkey(MenuEntry *entry, const vector<Hotkey> &hotkeys);
}

#endif