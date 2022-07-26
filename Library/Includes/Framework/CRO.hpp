#ifndef CRO_HPP
#define CRO_HPP

#include <CTRPluginFramework.hpp>
#include "../../../Includes/stdafx.hpp"

#include "../CTRPluginFramework/System/Process.hpp"
#include "../CTRPluginFrameworkImpl/System/ProcessImpl.hpp"

namespace CTRPluginFramework {
    namespace CRO {
        /**
        * \brief Enable permissions of CRO data
        * \param address The address to toggle
        * \param enabled Enable permissions
        */
        bool Toggle(u32 address, bool enabled);

        /**
        * \brief Safely write 32 bits
        * \param address The address to write to
        * \param value The variable to put the value in
        */
        bool Write32(u32 address, u32 value);

        /**
        * \brief Safely write 32 bits
        * \param address The address to write to
        * \param value The variable to put the value in
        * \param original The variable to store the initial value of the address before changes
        */
        bool Write32(u32 address, u32 value, u32 &original);

        /**
        * \brief Safely write 32 bits
        * \param address The address to write to
        * \param value The variable to put the values in
        */
        bool Write32(u32 address, vector<u32> value);

        /**
        * \brief Safely read 32 bits
        * \param address The addresses to read from
        * \return The value of the address
        */
        u32 Read32(u32 address);

        /**
        * \brief Safely read 32 bits
        * \param address The addresses to read from
        * \param length Loop and increment up until length is reached
        * \return The values of the addresses
        */
        vector<u32> Read32(u32 address, int length);
    }
}

#endif