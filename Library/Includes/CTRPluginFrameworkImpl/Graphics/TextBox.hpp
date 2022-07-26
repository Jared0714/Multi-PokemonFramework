#ifndef CTRPLUGINFRAMEWORK_TEXTBOX_HPP
#define CTRPLUGINFRAMEWORK_TEXTBOX_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Graphics.hpp"
#include "CTRPluginFrameworkImpl/Graphics/Drawable.hpp"
#include "CTRPluginFrameworkImpl/System.hpp"

namespace CTRPluginFramework {
    class TextBox : public Drawable {
        public:
            TextBox();
            TextBox(const string &title, const string &text, const IntRect &box);
            ~TextBox() {}

            void Open(void) const;
            void Close(void) const;
            bool IsOpen(void) const;
            bool ProcessEvent(Event &event);
            void Update(const string &title, string &text);
            void Draw(void) override;
            void DrawConst(void) const;
            void Update(const bool isTouchDown, const IntVector &pos) override;

        private:
            friend class MessageBoxImpl;
            void _GetTextInfos(void);
            u8 *_GetWordWidth(u8 *str, float& width);

            vector<u8*> _newline;
            string _title;
            const string *_text;
            IntRect _box;
            IntRect _border;
            mutable bool _isOpen;
            bool _displayScrollbar;
            bool _drawBox;
            bool _fastscroll;

            u32 _currentLine;
            u32 _maxLines;
            u32 _scrollbarSize;
            u32 _scrollCursorSize;
            u32 _maxScrollCursorPosY;
            float _scrollPadding;
            float _scrollPosition;
            Clock _inputClock;
    };
}

#endif