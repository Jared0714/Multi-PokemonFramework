#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "../Library/Includes/Framework/Wrappers.hpp"

namespace CTRPluginFramework {
    extern u8 data8; extern u16 data16; extern u32 data32;

    namespace Message {
        void Completed(void);
        void Interrupted(void);
        void Warning(void);
    }

    extern string bin;
    extern string path;

    bool IsCompatible(void);
    void Settings(MenuEntry *entry);

    namespace Helpers {
        namespace Battle {
            extern vector<u32> offset;
        }

        void MenuCallback(void);
    }

    bool IsInBattle(void);
}

#include "Decryption.hpp"
#include "Lookup.hpp"

#endif