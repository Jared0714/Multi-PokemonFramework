#ifndef CTRPLUGINFRAMEWORK_COLOR_HPP
#define CTRPLUGINFRAMEWORK_COLOR_HPP

#include <algorithm>
#include <string>
#include "types.h"

using namespace std;

namespace CTRPluginFramework {
    class Color {
        public:
            enum class BlendMode {
                Alpha,
                Add,
                Sub,
                Mul,
                None
            };

            constexpr Color(void) : a(255), b(0), g(0), r(0) {}
            constexpr Color(u32 color) : raw(color) {}
            constexpr Color(u8 red, u8 green, u8 blue, u8 alpha = 255) : a(alpha), b(blue), g(green), r(red) {}

            inline u32 ToU32(void) const {return raw;};
            Color &Fade(float fading);
            Color Blend(const Color &color, BlendMode mode) const;

            inline bool operator == (const Color &right) const {return raw == right.raw;}
            inline bool operator != (const Color &right) const {return raw != right.raw;}
            bool operator < (const Color &right) const;
            bool operator <= (const Color &right) const;
            bool operator > (const Color &right) const;
            bool operator >= (const Color &right) const;
            Color operator + (const Color &right) const;
            Color operator - (const Color &right) const;
            Color operator * (const Color &right) const;
            Color &operator += (const Color &right);
            Color &operator -= (const Color &right);
            Color &operator *= (const Color &right);

            operator string() const {
                char strColor[5] = {0};
                strColor[0] = 0x1B;
                strColor[1] = max((u8)1, r);
                strColor[2] = max((u8)1, g);
                strColor[3] = max((u8)1, b);
                return strColor;
            }

            union {
                u32 raw;

                struct {
                    u8 a;
                    u8 b;
                    u8 g;
                    u8 r;
                };
            };

            static const Color Black;
            static const Color White;
            static const Color Red;
            static const Color Lime;
            static const Color Blue;
            static const Color Yellow;
            static const Color Cyan;
            static const Color Magenta;
            static const Color Silver;
            static const Color Gray;
            static const Color Maroon;
            static const Color Olive;
            static const Color Green;
            static const Color Purple;
            static const Color Teal;
            static const Color Navy;

            static const Color BlackGrey;
            static const Color Brown;
            static const Color DarkGrey;
            static const Color DeepSkyBlue;
            static const Color DimGrey;
            static const Color DodgerBlue;
            static const Color Gainsboro;
            static const Color ForestGreen;
            static const Color LimeGreen;
            static const Color Orange;
            static const Color SkyBlue;
            static const Color Turquoise;
    };
}

#endif