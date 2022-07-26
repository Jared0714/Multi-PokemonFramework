#ifndef CTRPLUGINFRAMEWORKIMPL_NUMERICTEXTBOX_HPP
#define CTRPLUGINFRAMEWORKIMPL_NUMERICTEXTBOX_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Graphics/Drawable.hpp"

namespace CTRPluginFramework {
    class NumericTextBox : public Drawable {
        public:
            enum class Type {
                Bits8,
                Bits16,
                Bits32,
                Float,
            };

            NumericTextBox(int posX, int posY, int width, int height);
            void SetValue(u8 val);
            void SetValue(u16 val);
            void SetValue(u32 val);
            void SetValue(float val);

            void UseHexadecimal(bool useHex);

            void Clear(void);
            void Draw(void) override;
            void Update(const bool isTouchDown, const IntVector &touchPos) override;
            bool operator()(void) override;

            bool IsEnabled;
            bool IsVisible;
            Type ValueType;

            union {
                u8 Bits8;
                u16 Bits16;
                u32 Bits32;
                float Float;
            };

        private:
            bool _execute;
            bool _isTouched;
            bool _isHexadecimal;
            IntRect _rectPos;
            string _text;

            void _UpdateVal(void);
    };
}

#endif