#ifndef CTRPLUGINFRAMEWORK_SYSTEM_FWKSETTINGS_HPP
#define CTRPLUGINFRAMEWORK_SYSTEM_FWKSETTINGS_HPP

#include <Headers.h>

namespace CTRPluginFramework {
    struct PluginHeader {
        u32 magic;
        u32 version;
        u32 heapVA;
        u32 heapSize;
        u32 exeSize; // Include sizeof(PluginHeader) + .text + .rodata + .data + .bss (0x1000 aligned too)
        u32 isDefaultPlugin;
        s32 *plgldrEvent;
        s32 *plgldrReply;
        u32 reserved[24];
        u32 config[32];
    };

    struct FwkSettings {
        // Plugin init options
        u32 ThreadPriority;
        bool AllowActionReplay;
        bool AllowSearchEngine;
        Time WaitTimeToBoot;
        bool CachedDrawMode;
        bool UseGameHidMemory;

        // Sound engine
        bool TryLoadSDSounds;

        // UI colors
        Color MainTextColor;
        Color WindowTitleColor;
        Color MenuSelectedItemColor;
        Color MenuUnselectedItemColor;
        Color BackgroundMainColor;
        Color BackgroundSecondaryColor;
        Color BackgroundBorderColor;
        float CursorFadeValue;

        // Keyboard colors
        struct {
            Color Background;
            Color KeyBackground;
            Color KeyBackgroundPressed;
            Color KeyText;
            Color KeyTextPressed;
            Color KeyTextDisabled;
            Color Cursor;
            Color Input;
        } Keyboard;

        // Custom Keyboard colors
        struct {
            Color BackgroundMain;
            Color BackgroundSecondary;
            Color BackgroundBorder;
            Color KeyBackground;
            Color KeyBackgroundPressed;
            Color KeyText;
            Color KeyTextPressed;
            Color ScrollBarBackground;
            Color ScrollBarThumb;
        } CustomKeyboard;

        enum Alignment_e {
            Left,
            Right,
            Center
        };

        enum Screen_e {
            Top,
            Bottom
        };

        struct {
            Color DefaultBackground;
            Color DefaultForeground;
            Screen_e Screen;
            UIntRect Area;
            u32 Margin;
            Alignment_e Alignment;
            Time LifeSpan;
        } Notifications;

        /**
         * \brief Returns a reference to the FwkSettings instance used by the framework. Allows runtime theme edition
         * \return The instance of FwkSettings
         */
        static FwkSettings &Get(void);
        static PluginHeader *Header;

        /**
         * \brief Reset all colors to their default values
         */
        static void SetThemeDefault(void);

        /**
         * \brief Set the top screen background image from a bmp file in memory
         * \param bmpData Pointer to the BMP file in memory
         * \return 0 if success
         */
        static Result SetTopScreenBackground(void *bmpData);

        /**
         * \brief Set the bottom screen background image from a bmp file in memory
         * \param bmpData Pointer to the BMP file in memory
         * \return 0 if success
         */
        static Result SetBottomScreenBackground(void *bmpData);
    };
}

#endif