#ifndef CTRPLUGINFRAMEWORK_PLUGINMENU_HPP
#define CTRPLUGINFRAMEWORK_PLUGINMENU_HPP

#include <memory>
#include <string>
#include <vector>

#include "CTRPluginFramework/Menu/MenuEntry.hpp"
#include "CTRPluginFramework/Menu/MenuFolder.hpp"
#include "CTRPluginFramework/System/Time.hpp"

namespace CTRPluginFramework {
    class PluginMenuImpl;
    class PluginMenu {
        using CallbackPointer = void(*)(void);
        using OnOpeningCallback = bool(*)(void);
        using OnScreenshotCallback = bool(*)(void);
        using FrameCallback = void(*)(Time);
        using DecipherPointer = void(*)(string&, void*);

        public:
            explicit PluginMenu(string name = "CTRPluginFramework", string about = "", u32 menuType = 0);

            /**
             * \brief Create a new PluginMenu
             * \param name The name of the main folder
             * \param major The major version number of the plugin version
             * \param minor The minor version number of the plugin version
             * \param revision The revision version number of the plugin version
             * \param about Text to display in About
             */
            PluginMenu(string name, u32 major, u32 minor, u32 revision, string about = "", u32 menuType = 0);
            ~PluginMenu(void);

            void Append(MenuEntry *item) const;
            void Append(MenuFolder *item) const;

            void operator += (const MenuEntry *entry) const;
            void operator += (const MenuFolder *folder) const;
            void operator += (CallbackPointer callback) const;
            void operator -= (CallbackPointer callback) const;

            void Callback(CallbackPointer callback) const;
            int Run(void) const;

            /**
             * \brief Get all entries present at the root of the menu
             * \return A vector with pointers to all MenuEntry objects
             */
            vector<MenuEntry*> GetEntryList(void) const;

            /**
             * \brief Get all folders present at the root of the menu
             * \return A vector with pointers to all MenuFolder objects
             */
            vector<MenuFolder*> GetFolderList(void) const;

            /**
            * \brief Enable or disable the Hex Editor in Tools
            * \param isEnabled If HexEditor must be enabled or not
            */
            void SetHexEditorState(bool isEnabled) const;

            /**
            * \brief Choose to display or not the "plugin ready" message
            * \param showMsg If the message must be displayed or not
            */
            void ShowWelcomeMessage(bool showMsg) const;

            /**
             * \brief Check if the menu is currently open
             * \return True if the menu is open, false otherwise
             */
            bool IsOpen(void);

            /**
             * \brief Check if the menu was opened since last Func execution
             * \return True if the menu was opened, false otherwise
             */
            bool WasOpened(void);

            /**
             * \brief Get a reference to the PluginMenu currently running
             * \return A reference to a PluginMenu that is currently running
             */
            static PluginMenu *GetRunningInstance(void);

            /**
             * \brief Forces the opening of the menu
             */
            static void ForceOpen(void);

            /**
             * \brief If set to true, the plugin's loop will only be executed 1 per top screen's frame
             * \param useSync Whether to wait for the top screen's frame or not
             */
            void SynchronizeWithFrame(const bool useSync);

            /**
             * \brief If a callback is set, the callback will be called - Must be set before calling Run when the menu is opened for the first time
             */
            CallbackPointer OnFirstOpening;

            /**
             * \brief If a callback is set, the callback will be called  - Must be set before calling Run when the menu is opened. Ideal to put the code that refresh the UI. Return true from the callback to proceed with menu opening, return false otherwise.
             */
            OnOpeningCallback OnOpening;

            /**
             * \brief The callback set will be called at each frame rendered while the menu is open. Ideal to put some UI effect. The function will receive the Time elapsed since last frame. Must be set before calling Run
             */
            FrameCallback OnNewFrame;

            /**
             * \brief Returns the reference of the PluginMenu title string
             * \return The reference of the PluginMenu title string
             */
            string &Title();

            /**
             * \brief Returns the reference of the screenshot path string, ScreenshotUpdatePaths needs to be called afterwards.
             * \return the reference of the screenshot path string
             */
            static string &ScreenshotPath();

            /**
             * \brief Returns the reference of the screenshot file prefix string, ScreenshotUpdatePaths needs to be called afterwards.
             * \return the reference of the screenshot file prefix string
             */
            static string &ScreenshotFilePrefix();

            /**
             * \brief Updates the paths after modifying the path and prefix strings.
             */
            static void ScreenshotUpdatePaths();

            /**
             * \brief Gets the screenshot settings references, can be read or written to.
             * \param enabled Screenshot feature enabled reference
             * \param hotkey Screenshot feature hotkey reference
             */
            static void ScreenshotSettings(bool **enabled, u32 **hotkey);

            /**
             * \brief Sets the screenshot callback, called whenever an screenshot is taken. If the callback function returns false, the screenshot will be aborted.
             * \param callback The callback function
             */
            static void ScreenshotSetcallback(OnScreenshotCallback callback);

            /**
             * @brief Checks if the background images have been loaded successfully.
             * \param isTopScreen Set to true to check the top screen background, set to false to check the bottom screen.
             * \return Wether a background image was loaded for the specified screen.
             */
            static bool IsBackgroundLoaded(bool isTopScreen);


        private:
            unique_ptr<PluginMenuImpl> _menu;
    };
}

#endif