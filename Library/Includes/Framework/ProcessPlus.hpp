#ifndef PROCESSPLUS_HPP
#define PROCESSPLUS_HPP

#include <CTRPluginFramework.hpp>
#include "../../../Includes/stdafx.hpp"

#include "../CTRPluginFramework/System/Process.hpp"
#include "../CTRPluginFrameworkImpl/System/ProcessImpl.hpp"

namespace CTRPluginFramework {
    class ProcessPlus {
        public:
            /**
            * \brief Safely write 8 bits
            * \param pointer The pointer to read
            * \param offset The offset to jump to
            * \param value The variable to put the value in
            */
            static void Write8(u32 pointer, u32 offset, u8 value);

            /**
            * \brief Safely write 8 bits
            * \param pointer The pointer to read
            * \param offset The offset to jump to
            * \param value The variable to put the value in
            * \param length Loop and increment up until length is reached
            */
            static void Write8(u32 pointer, u32 offset, u8 value, int length);

            /**
            * \brief Safely write 16 bits
            * \param pointer The pointer to read
            * \param offset The offset to jump to
            * \param value The variable to put the value in
            */
            static void Write16(u32 pointer, u32 offset, u16 value);

            /**
            * \brief Safely write 16 bits
            * \param pointer The pointer to read
            * \param offset The offset to jump to
            * \param value The variable to put the value in
            * \param length Loop and increment up until length is reached
            */
            static void Write16(u32 pointer, u32 offset, u16 value, int length);

            /**
            * \brief Safely write 32 bits
            * \param pointer The pointer to read
            * \param offset The offset to jump to
            * \param value The variable to put the value in
            */
            static void Write32(u32 pointer, u32 offset, u32 value);

            /**
            * \brief Safely write 32 bits
            * \param pointer The pointer to read
            * \param offset The offset to jump to
            * \param value The variable to put the value in
            * \param length Loop and increment up until length is reached
            */
            static void Write32(u32 pointer, u32 offset, u32 value, int length);

            /**
            * \brief Safely write 32 bits
            * \param address The address to write to
            * \param value The variable to put the value in
            * \param original The variable to store the initial value of the address before changes
            * \param entry Used to check for activation of entry, will revert changes upon de-activation
            * \param saved If entry is actiavted or not
            * \return True if successful, false otherwise
            */
            static bool Write32(u32 address, u32 value, u32 &original, MenuEntry *entry, bool &saved);

            /**
            * \brief Safely write 32 bits
            * \param address The address to write to
            * \param value The variable to put the values in
            */
            static bool Write32(u32 address, vector<u32> value);

            /**
            * \brief Safely write 32 bits
            * \param address The address to write to
            * \param value The variable to put the values in
            * \param length Loop and increment up until length is reached
            */
            static void Write32(u32 address, vector<u32> value, int length);

            /**
            * \brief Safely write 32 bits
            * \param address The address to write to
            * \param value The variable to put the values in
            * \param original The variable to store the initial value of the address before changes
            * \param entry Used to check for activation of entry, will revert changes upon de-activation
            * \param saved If saved or not
            * \return True if successful, false otherwise
            */
            static bool Write32(u32 address, vector<u32> value, vector<u32> &original, MenuEntry *entry, bool &saved);

            /**
            * \brief Safely write 32 bits
            * \param address The addresses to write to
            * \param value The variable to put the values in
            */
            static void Write32(vector<u32> address, vector<u32> value);

            /**
            * \brief Safely write 32 bits
            * \param address The addresses to write to
            * \param value The variable to put the values in
            * \param original The variable to store the initial value of the address before changes
            * \param entry Used to check for activation of entry, will revert changes upon de-activation
            * \param saved If saved or not
            * \return True if successful, false otherwise
            */
            static bool Write32(vector<u32> address, vector<u32> value, vector<u32> &original, MenuEntry *entry, bool &saved);

            /**
            * \brief Safely read 8 bits
            * \param address The address to read from
            * \return The value of the address
            */
            static u8 Read8(u32 address);

            /**
            * \brief Safely read 8 bits
            * \param address The addresses to read from
            * \param check An extra check, just to be safe
            * \return True if read is successful, false otherwise
            */
            bool Read8(u32 address, u8 &value, bool check);

            /**
            * \brief Safely read 16 bits
            * \param address The address to read from
            * \return The value of the address
            */
            static u16 Read16(u32 address);

            /**
            * \brief Safely read 32 bits
            * \param address The address to read from
            * \return The value of the address
            */
            static u32 Read32(u32 address);

            /**
            * \brief Safely read 32 bits
            * \param address The addresses to read from
            * \param length Loop and increment up until length is reached
            * \return The values of the addresses
            */
            static vector<u32> Read32(u32 address, int length);

            /**
            * \brief Safely read 32 bits
            * \param address The addresses to read from
            * \param check An extra check, just to be safe
            * \return True if read is successful, false otherwise
            */
            bool Read32(u32 address, u32 &value, bool check);

            /**
            * \brief Get address
            * \return The address
            */
            string Address(string text, int s);
    };
}

#endif