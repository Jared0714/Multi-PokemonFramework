#ifndef CTRPLUGINFRAMEWORKIMPL_PLUGINMENUHOME_HPP
#define CTRPLUGINFRAMEWORKIMPL_PLUGINMENUHOME_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Graphics.hpp"
#include "CTRPluginFrameworkImpl/System.hpp"
#include "CTRPluginFrameworkImpl/Menu/MenuFolderImpl.hpp"
#include "CTRPluginFrameworkImpl/Menu/MenuEntryImpl.hpp"
#include "CTRPluginFrameworkImpl/Menu/MenuItem.hpp"

namespace CTRPluginFramework {
    class PluginMenuHome {
        using EventList = vector<Event>;

        public:
            PluginMenuHome(string &name, bool ShowNoteBottom);
            ~PluginMenuHome() {}

            bool operator()(EventList &eventList, int &mode, Time &delta);
            void Append(MenuItem *item) const;
            void Refresh(void);
            void UnStar(MenuItem *item);
            void Init(void);
            void AddPluginVersion(u32 version);
            void Close(MenuFolderImpl *folder);
            void UpdateNote(void);
            bool ShowNoteBottom;

        private:
            friend class PluginMenuImpl;
            friend string &PluginMenu::Title(void);

            void _ProcessEvent(Event &event);
            void _RenderTop(void);
            void _RenderBottom(void);
            void _Update(Time delta);
            void _StarItem(void);
            void _TriggerEntry(void);
            void _showStarredBtn_OnClick(void);
            void _controllerBtn_OnClick(void);
            void _keyboardBtn_OnClick(void);
            void _actionReplayBtn_OnClick(void);
            void _gameGuideBtn_OnClick(void);
            void _searchBtn_OnClick(void);
            void _toolsBtn_OnClick(void);
            void _InfoBtn_OnClick(void);

            // Members
            MenuFolderImpl *_root;
            MenuFolderImpl *_folder;
            MenuFolderImpl *_starred;
            MenuFolderImpl *_starredConst;

            int _mode;
            int _starMode;
            int _selector;
            int _selectedTextSize;
            float _maxScrollOffset;
            float _scrollOffset;
            Clock _scrollClock;
            bool _reverseFlow;
            bool _showVersion;
            int _versionPosX;
            string _versionStr;

            TextBox _noteTB;

            // Mode buttons
            Button _showStarredBtn;
            Button _hidMapperBtn;
            Button _gameGuideBtn;
            Button _searchBtn;
            Button _arBtn;
            Button _toolsBtn;

            Button _keyboardBtn;
            Button _controllerBtn;

            // Entry button
            Button _AddFavoriteBtn;
            Button _InfoBtn;
    };
}

#endif