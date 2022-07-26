#ifndef CTRPLUGINFRAMEWORKIMPL_PLUGINMENUHOTKEYS_HPP
#define CTRPLUGINFRAMEWORKIMPL_PLUGINMENUHOTKEYS_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Graphics/Button.hpp"

namespace CTRPluginFramework {
    class HotkeysModifier {
        public:
            HotkeysModifier(u32 &keys, const string &message);
            ~HotkeysModifier(void);

            void operator()(void);

        private:
            void _DrawTop(void) const;
            void _DrawBottom(void);
            void _Update(void);

            u32 &_keys;
            vector<Button> _checkboxs;
            const string _message;
    };
}

#endif