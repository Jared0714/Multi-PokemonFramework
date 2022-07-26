#ifndef CTRPLUGINFRAMEWORKIMPL_SUBMENU_HPP
#define CTRPLUGINFRAMEWORKIMPL_SUBMENU_HPP

#include <Headers.h>

namespace CTRPluginFramework {
    class Event;
    class SubMenu {
        public:
            SubMenu(const vector<string> &options);
            ~SubMenu(void);

            int operator()(void);
            void Draw(void);
            void ProcessEvent(const Event &event);
            bool IsOpen(void);
            void ChangeOptions(const vector<string> &options);
            u32 OptionsCount(void);

        private:
            vector<string> _options;
            u32 _selector;
            bool _isOpen;
            bool _action;
            Clock _fadeClock;
    };
}

#endif