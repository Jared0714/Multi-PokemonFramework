#ifndef CTRPLUGINFRAMEWORKIMPL_PLUGINMENUTOOLS_HPP
#define CTRPLUGINFRAMEWORKIMPL_PLUGINMENUTOOLS_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Graphics.hpp"
#include "CTRPluginFrameworkImpl/System.hpp"
#include "CTRPluginFrameworkImpl/Menu/Menu.hpp"
#include "CTRPluginFrameworkImpl/Menu/MenuFolderImpl.hpp"
#include "CTRPluginFrameworkImpl/Menu/MenuEntryImpl.hpp"
#include "CTRPluginFrameworkImpl/Menu/GatewayRAMDumper.hpp"
#include "CTRPluginFrameworkImpl/Menu/HexEditor.hpp"
#include "CTRPluginFrameworkImpl/Menu/MenuItem.hpp"
#include "MenuEntryTools.hpp"

namespace CTRPluginFramework {
    class PluginMenuTools {
        using EventList = vector<Event>;

        public:
            PluginMenuTools(string &about, HexEditor &hexEditor);
            void UpdateSettings();
            void InitMenu();
            ~PluginMenuTools() {}

            bool operator()(EventList &eventList, Time &delta);
            void TriggerHexEditor(bool isEnabled) const;

        private:
            void _ProcessEvent(Event &event);
            void _RenderTop(void);
            void _RenderTopMenu(void);
            void _RenderBottom(void);
            void _Update(Time delta);

            string _about;
            MenuFolderImpl _mainMenu;
            MenuFolderImpl _miscellaneousMenu;
            MenuFolderImpl _screenshotMenu;
            MenuFolderImpl _settingsMenu;
            MenuEntryTools *_hexEditorEntry;
            HexEditor &_hexEditor;
            GatewayRAMDumper _gatewayRamDumper;
            Menu _menu;
            TextBox _abouttb;
            bool _exit;
    };
}

#endif