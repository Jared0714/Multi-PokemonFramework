#ifndef CTRPLUGINFRAMEWORKIMPL_MESSAGEBOXIMPL_HPP
#define CTRPLUGINFRAMEWORKIMPL_MESSAGEBOXIMPL_HPP

#include <Headers.h>
#include "TextBox.hpp"
#include "CTRPluginFrameworkImpl/System/Events.hpp"

namespace CTRPluginFramework {
    class MessageBoxImpl {
        public:
            MessageBoxImpl(const string &title, const string &message, DialogType dtype, ClearScreen clear);
            MessageBoxImpl(const string &message, DialogType dtype, ClearScreen clear);
            ~MessageBoxImpl() {};
            bool operator()(void);

        private:
            friend MessageBox;
            void _ProcessEvent(Event &event);
            void _Draw(void);

            string _title;
            string _message;
            DialogType _dialogType;
            ClearScreen _clearScreen;
            TextBox _textbox;
            bool _exit;
            int _cursor;
            u32 _exitKey;
            IntRect _box;
    };
}

#endif