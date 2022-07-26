#ifndef CTRPLUGINFRAMEWORK_MESSAGEBOX_HPP
#define CTRPLUGINFRAMEWORK_MESSAGEBOX_HPP

#include <Headers.h>

namespace CTRPluginFramework {
    enum class DialogType {
        DialogOk,
        DialogOkCancel,
        DialogYesNo
    };

    enum class ClearScreen {
        None = 0,
        Top = 1 << 1,
        Bottom = 1 << 2,
        Both = Top | Bottom
    };

    class MessageBoxImpl;
    class MessageBox {
        public:
            MessageBox(const string &title, const string &message, DialogType dialogType = DialogType::DialogOk, ClearScreen clear = ClearScreen::None);
            MessageBox(const string &message, DialogType dialogType = DialogType::DialogOk, ClearScreen clear = ClearScreen::None);
            ~MessageBox(void);

            MessageBox &SetClear(ClearScreen screen);
            bool operator()(void) const;

        private:
            unique_ptr<MessageBoxImpl>  _messageBox;
    };
}

#endif