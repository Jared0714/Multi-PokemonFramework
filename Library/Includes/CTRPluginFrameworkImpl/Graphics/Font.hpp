#ifndef CTRPLUGINFRAMEWORKIMPL_FONT_HPP
#define CTRPLUGINFRAMEWORKIMPL_FONT_HPP

#include <Headers.h>

namespace CTRPluginFramework {
    struct Glyph {
        float xOffset;
        float xAdvance;
        u8 *glyph;
        float Width(void) const;
    };

    class Font {
        public:
            static Glyph *GetGlyph(u8 *&c);
            static Glyph *GetGlyph(char c);

        private:
            friend void Initialize(void);
            static void Initialize(void);

            // Cache a new glyph
            static Glyph *CacheGlyph(u32 glyphIndex);
            static Mutex _mutex;
    };
}

#endif