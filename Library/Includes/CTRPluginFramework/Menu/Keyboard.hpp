#ifndef CTRPLUGINFRAMEWORK_KEYBOARD_HPP
#define CTRPLUGINFRAMEWORK_KEYBOARD_HPP

#include <Headers.h>

namespace CTRPluginFramework {
    class KeyboardEvent {
        public:
            enum EventType {
                CharacterAdded,
                CharacterRemoved,
                InputWasCleared,
                SelectionChanged,
                KeyPressed,
                KeyDown,
                KeyReleased
            };

            // Type of the event
            EventType type{};
            // The codepoint of the character that thrown the event (used for CharacterAdded and CharacterRemoved, 0 otherwise)
            u32 codepoint{0};
            // The entry index in a custom keyboard being selected (used for SelectionChanged, 0 otherwise)
            u32 selectedIndex{0};
            // Button affected not mapped to any keyboard feature (used for ButtonPressed, ButtonHold and ButtonReleased, 0 otherwise)
            Key affectedKey{(Key)0};
        };

    class KeyboardImpl;
    class Keyboard {
        /**
         * \brief The signature of the callback called to check the input
         * \param input A void pointer to the input, must be casted to the correct type (as passed to Keyboard::Open)
         * \param error A reference to the string that hold the error message. You can edit it according to what you want to display
         * \return A boolean. Return true if the input is valid, false if it's not
         */
        using CompareCallback = bool(*)(const void*, string &);

        /**
         * \brief The signature of the callback called when the input change (user enter / delete a character)
         * \param keyboard A reference to the Keyboard object that called the callback
         */
        using OnEventCallback = void(*)(Keyboard&, KeyboardEvent &event);

        public:
            /**
             * \brief Keyboard constructor
             * \param text The message to display on the top screen if displayed
             */
            Keyboard(const string &text = "");
            Keyboard(const string &text, const vector<string> &options);
            Keyboard(const vector<string> &options);
            ~Keyboard(void);

            /**
             * \brief Set if the user can abort the keybord by pressing B. The keyboard can still abort if a sleep event happens.
             * \param canAbort Whether the user can press B to close the keyboard and abort the current operation
             */
            void CanAbort(bool canAbort) const;

            /**
             * \brief Define if the input must be hexadecimal or not. Have no effect for float, double, string
             * \param isHex If the input must be hexadecimal
             */
            void IsHexadecimal(bool isHex);

            /**
             * \brief Define a maximum input length for qwerty keyboard
             * \param maxValue The maximum count of characters that the user can type
             */
            void SetMaxLength(u32 maxValue) const;

            /**
             * \brief Define a callback to check the input. The callback is called each time the input is changed. See CompareCallback's description for more infos
             * \param callback The callback that must be called
             */
            void SetCompareCallback(CompareCallback callback) const;

            /**
             * \brief Define a callback that will be called when the user change the input. Note that if a CompareCallback is set, CompareCallback is called before OnKeyboardEvent. See OnEventCallback's description for more infos
             * \param callback
             */
            void OnKeyboardEvent(OnEventCallback callback) const;

            /**
            * \brief Set the error flag and an error message. When the error flag is set, the user can't valid the input
            * \param error The error message that must be displayed
            */
            void SetError(string error) const;

            /**
            * \brief Selects and scroll to the specified entry, must be called after Populate
            * \param entry Entry index to select, -1 to deselect all.
            */
            void ChangeSelectedEntry(int entry);

            /**
            * @brief Gets the last selected entry before the keyboard was closed
            * @return Last selected entry, or -1 if none was selected.
            */
            int GetLastSelectedEntry();

            /**
            * \brief Populate a keyboard with the strings contained in an vector
            * \param input A vector that contain a list of strings
            * \param resetScroll Set to true to reset the scroll position if the list is the same size
            */
            void Populate(const vector<string> &input, bool resetScroll = false);

            /**
            * \brief Populate a keyboard with the CustomIcons contained in an vector
            * \param input A vector that contains a list of CustomIcons (icon size must be 30x30 pixels, otherwise a red cross will be displayed)
            * \param resetScroll Set to true to reset the scroll position if the list is the same size
            */
            void Populate(const vector<CustomIcon> &input, bool resetScroll = false);

            /**
            * \brief Open a keyboard which is populated with strings
            * \return -1 : user abort / not populated. -2 : closed by sleep event. >= 0 : index of the user choice in the vector
            */
            int Open(void) const;

            /**
            * \brief Open the keyboard and wait for user input
            * \param output Where to place the user's input
            * \return -1 : user abort / error. -2 : closed by sleep event. 0 : Success
            */
            int Open(u8 &output) const;

            /**
            * \brief Open the keyboard and wait for user input
            * \param output Where to place the user's input
            * \param start The keyboard will start with this value as input
            * \return -1 : user abort / error. -2 : closed by sleep event. 0 : Success
            */
            int Open(u8 &output, u8 start) const;

            /**
            * \brief Open the keyboard and wait for user input
            * \param output Where to place the user's input
            * \return -1 : user abort / error. -2 : closed by sleep event. 0 : Success
            */
            int Open(u16 &output) const;

            /**
            * \brief Open the keyboard and wait for user input
            * \param output Where to place the user's input
            * \param start The keyboard will start with this value as input
            * \return -1 : user abort / error. -2 : closed by sleep event. 0 : Success
            */
            int Open(u16 &output, u16 start) const;

            /**
            * \brief Open the keyboard and wait for user input
            * \param output Where to place the user's input
            * \return -1 : user abort / error. -2 : closed by sleep event. 0 : Success
            */
            int Open(u32 &output) const;

            /**
            * \brief Open the keyboard and wait for user input
            * \param output Where to place the user's input
            * \param start The keyboard will start with this value as input
            * \return -1 : user abort / error. -2 : closed by sleep event. 0 : Success
            */
            int Open(u32 &output, u32 start) const;

            /**
            * \brief Open the keyboard and wait for user input
            * \param output Where to place the user's input
            * \return -1 : user abort / error. -2 : closed by sleep event. 0 : Success
            */
            int Open(u64 &output) const;

            /**
            * \brief Open the keyboard and wait for user input
            * \param output Where to place the user's input
            * \param start The keyboard will start with this value as input
            * \return -1 : user abort / error. -2 : closed by sleep event. 0 : Success
            */
            int Open(u64 &output, u64 start) const;

            /**
            * \brief Open the keyboard and wait for user input
            * \param output Where to place the user's input
            * \return -1 : user abort / error. -2 : closed by sleep event. 0 : Success
            */
            int Open(float &output) const;

            /**
            * \brief Open the keyboard and wait for user input
            * \param output Where to place the user's input
            * \param start The keyboard will start with this value as input
            * \return -1 : user abort / error. -2 : closed by sleep event. 0 : Success
            */
            int Open(float &output, float start) const;

            /**
            * \brief Open the keyboard and wait for user input
            * \param output Where to place the user's input
            * \return -1 : user abort / error. -2 : closed by sleep event. 0 : Success
            */
            int Open(double &output) const;

            /**
            * \brief Open the keyboard and wait for user input
            * \param output Where to place the user's input
            * \param start The keyboard will start with this value as input
            * \return -1 : user abort / error. -2 : closed by sleep event. 0 : Success
            */
            int Open(double &output, double start) const;

            /**
            * \brief Open the keyboard and wait for user input
            * \param output Where to place the user's input
            * \return -1 : user abort / error. -2 : closed by sleep event. 0 : Success
            */
            int Open(string &output) const;

            /**
            * \brief Open the keyboard and wait for user input
            * \param output Where to place the user's input
            * \param start The keyboard will start with this value as input
            * \return -1 : user abort / error. -2 : closed by sleep event. 0 : Success
            */
            int Open(string &output, const string &start) const;

            /**
            * \brief Forcefully close the keyboard without any regard to the error flag. (This can only be called from an OnKeyboardEvent callback)
            */
            void Close(void) const;

            /**
            * \brief Get a reference to the Keyboard's input string
            * \return A reference to the Keyboard's input string
            */
            string &GetInput(void) const;

            /**
            * \brief Get a reference to the top screen's message string
            * \return A reference to the top screen's message string
            */
            string &GetMessage(void) const;

            /**
            * \brief This property define if the top screen must be displayed or not. Note that when disabled, errors messages can't be displayed
            */
            bool DisplayTopScreen;

        private:
            unique_ptr<KeyboardImpl> _keyboard;
            bool _hexadecimal;
            mutable bool _isPopulated;
    };
}

#endif