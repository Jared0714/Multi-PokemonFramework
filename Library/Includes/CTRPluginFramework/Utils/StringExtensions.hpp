#ifndef CTRPLUGINFRAMEWORK_UTILS_STRINGEXTENSIONS_HPP
#define CTRPLUGINFRAMEWORK_UTILS_STRINGEXTENSIONS_HPP

#include <Headers.h>
#include "CTRPluginFramework/Graphics/Color.hpp"

using namespace std;

namespace CTRPluginFramework {
    // Return a string with the charcter that reset the color (0x18)
    string ResetColor(void);

    // Allows to use the flags from Render::FontDrawMode to draw text in different modes.
    string ToggleDrawMode(u32 flags);

    // Makes the text draw function skip to the specified X pixel.
    string SkipToPixel(u16 px);

    // Aligns the string to the center of the specified borders. (Default values = top window size)
    string CenterAlign(const string &str, u16 leftBorder = 35, u16 rightBorder = 370);

    // Aligns the string to the right of the specified borders. (Default values = top window size)
    string RightAlign(const string &str, u16 leftBorder = 35, u16 rightBorder = 370);

    // Adds a visual horizontal separator that takes an entire line.
    string HorizontalSeparator();

    string operator << (const string &left, const char *right);
    string operator << (const string &left, const string &right);

    template <typename T, typename enable_if<!is_same<T, const char *>::value && !is_same<T, Color>::value>::type* = nullptr>
    string operator << (const string &left, T right) {
        return (left + to_string(right));
    }
}

#endif