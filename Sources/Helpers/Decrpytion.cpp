#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework {
    u32 pokePointer;

    u32 GetPokePointer(void) {
        pokePointer = (group == Group::XY || group == Group::ORAS ? Helpers::GetVersion(0x8C861C8, 0x8C9E134) : Helpers::GetVersion(0x330D9838, 0x33015AB0));
        return pokePointer;
    }

    void Unshuffle(u8 *shuffled, u8 *poke, u32 sv) {
        Process::CopyMemory(poke, shuffled, 0xE8);

        for (short block = 0; block < 4; block++) {
            for (short i = 0; i < 56; i++)
                *(poke + i + 8 + 56 * block) = *(shuffled + i + 8 + 56 * blockPosition[block][sv]);
        }
    }
}