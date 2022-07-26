#ifndef CTRPLUGINFRAMEWORKIMPL_SEARCHMENU_HPP
#define CTRPLUGINFRAMEWORKIMPL_SEARCHMENU_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Graphics.hpp"
#include "CTRPluginFrameworkImpl/Graphics/UIContainer.hpp"
#include "CTRPluginFrameworkImpl/Menu/Menu.hpp"
#include "CTRPluginFrameworkImpl/Menu/SearchMenu.hpp"
#include "CTRPluginFrameworkImpl/Search/Search32.hpp"

namespace CTRPluginFramework {
    class PluginMenuSearch {
        using EventList = vector<Event>;

        public:
            PluginMenuSearch(HexEditor &hexEditor);
            ~PluginMenuSearch() {}

            bool operator()(EventList &eventList, Time &delta);
            void GetRegionsList(vector<Region> &list);
            void RestoreSearchState(void);

        private:
            void _ProcessEvent(Event &event);
            void _RenderTop(void);
            void _RenderBottom(void);
            void _Update(Time delta);

            void _ListRegion(void);
            void _PopulateSearchType(bool isFirstSearch);

            void _searchBtn_OnClick(void);
            void _resetBtn_OnClick(void);
            void _undoBtn_OnClick(void);
            void _cancelBtn_OnClick(void);

            static s32 _ShowProgressWindow(void *arg);

            // Members
            vector<Region> _regionsList{};
            list<Search*> _searchHistory{};
            Search *_currentSearch;
            HexEditor &_hexEditor;
            Task _progressTask{_ShowProgressWindow, nullptr, Task::AppCores};

            bool _inSearch;
            bool _inEditor;
            bool _firstRegionInit;
            bool _hexInput;
            int _step;

            // UIComponent
            SearchMenu _searchMenu;
            ComboBox _memoryRegions;
            ComboBox _searchSize;
            ComboBox _searchType;
            ComboBox _compareType;

            NumericTextBox _startRangeTextBox;
            NumericTextBox _endRangeTextBox;
            NumericTextBox _valueTextBox;

            Button _searchBtn;
            Button _cancelBtn;
            Button _undoBtn;
            Button _resetBtn;
            Button _hexBtn;

            UIContainer _uiContainer;
    };
}

#endif