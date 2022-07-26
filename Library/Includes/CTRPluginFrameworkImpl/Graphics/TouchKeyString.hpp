#ifndef CTRPLUGINFRAMEWORKIMPL_TOUCHKEYSTRING_KEYBOARD_HPP
#define CTRPLUGINFRAMEWORKIMPL_TOUCHKEYSTRING_KEYBOARD_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Graphics.hpp"
#include "CTRPluginFrameworkImpl/Graphics/Drawable.hpp"

namespace CTRPluginFramework {
    class TouchKeyString {
        public:
            TouchKeyString(const string &content, IntRect ui, bool enabled = true);
            TouchKeyString(const CustomIcon &icon, IntRect ui, bool isEnabled);
            ~TouchKeyString() {}

            void Enable(bool enable = true);
            void ForcePressed(bool force);
            bool CanUse(void);
            void Draw(void);
            void Update(const bool touchIsDown, const IntVector &touchPos);
            void Scroll(float amount);
            void GetPosition(u16 &posX, float& posY);
            void SetPosition(u16 posX, float posY);
            int operator()(void);

        private:
            string _content;
            CustomIcon _icon;
            IntRect _uiProperties;

            bool _isPressed;
            bool _wasPressed;
            bool _isForcePressed;
            bool _isIcon;
            bool _execute;
            bool _enabled;
            u16 _posX;
            float _contentLength;
            float _posY;

            TouchKeyString(IntRect ui, bool isEnabled);
    };
}

#endif