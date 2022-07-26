#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

namespace Plaza {
    namespace GlobalTradeStation {
        static int depositConfig, getSettings[2], settings[3];
        static int optionsType;

        void ConfigurationKB(MenuEntry *entry) {
            static const vector<string> options = {"Pokemon", "Gender", "Level"};
            KeyboardPlus keyboard;

            start:
            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, depositConfig) != -1) {
                if (depositConfig == 0) {
                    FindPkmnKB(entry);
                    settings[0] = pkmnID;

                    if (settings[0] != 0)
                        Message::Completed();

                    else goto start;
                }

                else {
                    vector<vector<string>> selection = {{"Any", "Male", "Female"}, {"Any", "1 to 10", "11 to 20", "21 to 30", "31 to 40", "41 to 50", "51 to 60", "61 to 70", "71 to 80", "81 to 90", "91 or higher"}};

                    if (keyboard.SetKeyboard(options[depositConfig] + ":", true, (depositConfig == 1 ? selection[0] : selection[1]), getSettings[depositConfig - 1]) != -1) {
                        settings[depositConfig] = getSettings[depositConfig - 1];
                        Message::Completed();
                        return;
                    }

                    else goto start;
                }
            }
        }

        void Configuration(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x32A6A170, 0x32A6A174, 0x32A6A178},
                    {0x32992170, 0x32992174, 0x32992178}
            )};

            for (int i = 0; i < 3; i ++) {
                if (settings[i] > 0)
                    (i == 0) ? Process::Write16(address[0], settings[0]) : Process::Write8(address[i], settings[i]);
            }
        }

        void BypassLimit(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x330D8DAC, 0x33014DF4);

            if (Process::Read8(address, data8) && data8 != 0)
                Process::Write8(address, 0);
        }
    }

    static u16 currRank;

    void CurrentRank(MenuEntry *entry) {
        static const u32 address = Helpers::GetVersion(0x33124D8A, 0x3306119A);

        if (KB<u16>(entry->Name() + ":", true, false, 7, currRank, 0, 1, 999, Callback16)) {
            if (Process::Write16(address, currRank))
                Message::Completed();
        }
    }

    static u32 collectedFC;

    void FCCollected(MenuEntry *entry) {
        static const u32 address = Helpers::GetVersion(0x33124D5C, 0x3306116C);

        if (KB<u32>(entry->Name() + ":", true, false, 7, collectedFC, 0, 0, 9999999, Callback32)) {
            if (Process::Write32(address, collectedFC))
                Message::Completed();
        }
    }

    namespace Profile {
        static u32 currFC;

        void CurrentFC(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x33124D58, 0x33061168);

            if (KB<u32>(entry->Name() + ":", true, false, 7, currFC, 0, 0, 9999999, Callback32)) {
                if (Process::Write32(address, currFC))
                    Message::Completed();
            }
        }

        static u32 guests;

        void GuestsInteracted(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x3313D740, 0x33079B50);

            if (KB<u32>(entry->Name() + ":", true, false, 7, guests, 0, 0, 9999999, Callback32)) {
                if (Process::Write32(address, guests))
                    Message::Completed();
            }
        }

        static u16 facilsHosted;

        void FacilitiesHosted(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x3313D802, 0x33079C12);

            if (KB<u16>(entry->Name() + ":", true, false, 4, facilsHosted, 0, 0, 9999, Callback16)) {
                if (Process::Write16(address, facilsHosted))
                    Message::Completed();
            }
        }

        static u16 missions;

        void MissionsParticipated(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x3313D800, 0x33079C10);

            if (KB<u16>(entry->Name() + ":", true, false, 4, missions, 0, 0, 9999, Callback16)) {
                if (Process::Write16(address, missions))
                    Message::Completed();
            }
        }
    }

    void ImageCrashCounter(MenuEntry *entry) {
        static const vector<u32> address = {
            Helpers::GetVersion<u32>(
                {0x2FD1E0, 0x2FD1FC},
                {0x306C38, 0x306C64}
        )};

        static vector<u32> original(5);
        static bool saved[2] = {false, false};

        if (ProcessPlus::Write32(address[0], Helpers::GetVersion(0xEA000005, 0xEA000009), original[4], entry, saved[0])) {
            if (!ProcessPlus::Write32(address[1], {0xE59F1004, 0xE1A05001, Helpers::GetVersion<u32>(0xEAFFFFF6, 0xEAFFFFF2), Helpers::GetVersion<u32>(0x330D6824, 0x3301286C)}, original, entry, saved[1]))
                return;
        }
    }

    void AvoidSoftban(MenuEntry *entry) {
        static const u32 address = Helpers::GetVersion(0x45DD70, Helpers::PickGame(0x4790AC, 0x4790B0));
        static u32 original;
        static bool saved = false;

        if (!ProcessPlus::Write32(address, 0xE3A04001, original, entry, saved))
            return;
    }
}