#ifndef CTRPLUGINFRAMEWORK_UTILS_UTILS_HPP
#define CTRPLUGINFRAMEWORK_UTILS_UTILS_HPP

#include <Headers.h>

namespace CTRPluginFramework {
    enum class HexEditorView {
        Byte = 0,
        Integer = 1,
        Disassembler = 2
    };

    class Color;
    class Utils {
        public:
            /**
             * \brief Get a string formatted with format specifier from printf
             * \param fmt String to be formatted
             * \param ... Additional arguments
             * \return The formatted string
             */
            static string Format(const char *fmt, ...);

            /**
             * \brief Get the hexadecimal representation of a value
             * \param value The value to convert
             * \return An string with the the hexadecimal representation of value
             */
            static string ToHex(u32 value);

            /**
             * \brief Get the string representation of a float value
             * \param fpval The value to convert
             * \param precision The number of digit after the .
             * \return An string with the representation of the value. Values between -999999.f && 999999.f will be a fixed representation while anything lower / higher will be a scientific representation
             */
            static string ToString(float fpval, int precision = 2);

            /**
             * \brief Get a random number
             * \return A random number
             */
            static u32 Random(void);

            /**
             * \brief Get a random number
             * \param min Minimum value for the random number
             * \param max Maximum value for the random number
             * \return A random number between min & max
             */
            static u32 Random(u32 min, u32 max);

            /**
             * \brief Get the size of an utf8 string (max size 0x100)
             * \param str The string to count
             * \return The count of utf8 chars in the str
             */
            static u32 GetSize(const string &str);


            /**
             * \brief Open a menu which allow to browse the SD card to select a file
             * \param out The absolute path of the selected file
             * \param filter If the files must be filtered (can be an extension or a pattern that must be present in the filename)
             * \return -1 if the user aborted the operation, 0 on success
             */
            static int FilePicker(string &out, const string &filter = "");

            /**
             * \brief Open a menu which allow to browse the SD card to select a Directory
             * \param out The absolute path of the selected directory
             * \return -1 if the user aborted the operation, 0 on success
             */
            static int DirectoryPicker(string &out);

            /**
             * \brief Open the HexEditor menu at a specified address within the specified view
             * \param address The address to jump to in the HexEditor
             * \param view The type of view (can be changed when open)
             * \return The address where the cursor was when the HexEditor is closed
             */
            static u32 OpenInHexEditor(u32 address, HexEditorView view = HexEditorView::Byte);

            /**
             * \brief Remove the last char of an utf8 string (max size 0x100)
             * \param str The string to remove the char from
             * \return The codepoint value of the char removed
             */
            static u32 RemoveLastChar(string &str);

            /**
             * \brief Returns last n chars
             * \param str The string to iterate
             * \return The last n chars
             */
            static string FindExtension(string const &str, unsigned int n);

            template <typename T>
            static u32 Search(const u32 start, const u32 size, const vector<T> &pattern) {
                if (!start || !size || pattern.empty())
                    return (0);

                const u32 patternSize = pattern.size() * sizeof(T);
                const u8 *patternc = reinterpret_cast<const u8*>(pattern.data());
                const u8 *startPos = reinterpret_cast<const u8*>(start);

                u32 table[256];

                for (u32 i = 0; i < 256; i++)
                    table[i] = patternSize;

                for (u32 i = 0; i < patternSize - 1; i++)
                    table[patternc[i]] = patternSize - i - 1;

                u32 j = 0;

                while (j <= size - patternSize) {
                    const u8 c = startPos[j + patternSize - 1];

                    if (patternc[patternSize - 1] == c && memcmp(patternc, startPos + j, patternSize - 1) == 0)
                        return (reinterpret_cast<u32>(startPos + j));

                    j += table[c];
                }

                return (0);
            }

            template <typename T>
            static u32 Rsearch(const u32 start, const u32 size, const vector<T> &pattern) {
                if (!start || !size || pattern.empty())
                    return (0);

                const u32 patternSize = pattern.size() * sizeof(T);
                const u8 *patternc = reinterpret_cast<const u8*>(pattern.data());
                const u8 *startPos = reinterpret_cast<const u8*>(start);

                u32 table[256];

                for (u32 i = 0; i < 256; i++)
                    table[i] = patternSize;

                for (u32 i = 0; i < patternSize - 1; i++)
                    table[patternc[i]] = patternSize - i - 1;

                u32 j = 0;
                u32 last = 0;

                while (j <= size - patternSize) {
                    const u8 c = startPos[j + patternSize - 1];

                    if (patternc[patternSize - 1] == c && memcmp(patternc, startPos + j, patternSize - 1) == 0)
                        last = reinterpret_cast<u32>(startPos + j);

                    j += table[c];
                }

                return (last);
            }
    };
}

#endif