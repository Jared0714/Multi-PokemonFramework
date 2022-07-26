#ifndef CTRPLUGINFRAMEWORKIMPL_KEY_KEYBOARD_HPP
#define CTRPLUGINFRAMEWORKIMPL_KEY_KEYBOARD_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Graphics.hpp"
#include "CTRPluginFrameworkImpl/Graphics/Drawable.hpp"

namespace CTRPluginFramework {
    struct KeyContent {
        KeyContent(const string &str) :
            text{str}, width{Renderer::GetTextSize(str.c_str())} {
                u8 *s = reinterpret_cast<u8*>(const_cast<char*>(str.c_str()));

                do {
                    Glyph *glyph = Font::GetGlyph(s);

                    if (glyph == nullptr)
                        break;

                    glyphs.push_back(glyph);

                }

                while (*s);
        }

        vector<Glyph*> glyphs;
        string text;
        float width;
    };

    class TouchKey : public Drawable {
        public:
            using IconCallback = int (*)(int, int, bool);

            TouchKey(TouchKey &&tk);
            TouchKey(int character, IntRect ui, bool enabled = true);
            TouchKey(const string &str, IntRect ui, int value = 0x12345678, bool enabled = true);
            TouchKey(int value, IconCallback, IntRect ui, bool enabled = true);
            ~TouchKey();

            void Clear(void);
            void Enable(bool enable = true);
            bool IsEnabled(void);
            void DrawCharacter(const Color &color);
            void Draw(void) override;
            void Update(const bool touchIsDown, const IntVector &touchPos) override;
            int operator()(string &str);

        private:
            int _character{0};
            Glyph *_glyph{nullptr};
            KeyContent *_content{nullptr};
            IconCallback _icon{nullptr};
            IntRect _uiProperties;

            u16 _posX{0};
            u16 _posY{0};

            bool _isPressed{false};
            bool _wasPressed{false};
            bool _execute{false};
            bool _enabled{true};
        };
}

#endif