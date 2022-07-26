#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework {
    u8 data8; u16 data16; u32 data32;

    namespace Message {
        void Completed(void) {
            MessageBox(CenterAlign("Operation has been " << Color::LimeGreen << "completed" << Color::White << "!"), DialogType::DialogOk, ClearScreen::Both)();
        }

        void Interrupted(void) {
            MessageBox(CenterAlign("Operation has been " << Color(255, 51, 51) << "interrupted" << Color::White << "!"), DialogType::DialogOk, ClearScreen::Both)();
        }

        void Warning(void) {
            MessageBox(CenterAlign("Operation has already been " << Color::Orange << "completed" << Color::White << "!"), DialogType::DialogOk, ClearScreen::Both)();
        }
    }

    string bin;
    string path;

    bool IsCompatible(void) {
        u32 titleID = Process::GetTitleID();
        u16 ver = Process::GetVersion();

        static const vector<u32> valids = {0x55D00, 0x55E00, 0x11C400, 0x11C500, 0x164800, 0x175E00, 0x1B5000, 0x1B5100};
        static const vector<Game> allGames = {Game::X, Game::Y, Game::OR, Game::AS, Game::S, Game::M, Game::US, Game::UM};
        static const vector<Group> allGroups = {Group::XY, Group::ORAS, Group::SM, Group::USUM};
        static const vector<u16> updates = {5232, 5216, 7820, 7820, 2112, 2112, 2080, 2080};

        for (unsigned int i = 0; i < valids.size(); i++) {
            if (titleID == valids[i]) {
                game = allGames[i];
                group = allGroups[(int)(i / 2)];

                if (ver == updates[i])
                    update = Update::Supported;

                bin = "/luma/plugins/00040000" + Utils::ToHex(titleID) + "/Bin/";
                path = "/luma/plugins/00040000" + Utils::ToHex(titleID);
                return true;
            }

            else {
                game = Game::None;
                group = Group::None;
            }
        }

        return false;
    }

    void Settings(MenuEntry *entry) {
        static const vector<string> options = {"Reset"};
        KeyboardPlus keyboard;
        int settings;

        if (keyboard.SetKeyboard(entry->Name() + ":", true, options, settings) != -1) {
            if (MessageBox(CenterAlign("Would you like to reset settings?"), DialogType::DialogYesNo, ClearScreen::Both)()) {
                if (File::Exists("CTRPFData.bin"))
                    File::Remove("CTRPFData.bin");

                if (File::Exists("MPFData.bin")) {
                    File::Remove("MPFData.bin");
                    Message::Completed();
                    Process::ReturnToHomeMenu();
                    return;
                }

                Message::Warning();
            }
        }
    }

    namespace Helpers {
        namespace Battle {
            vector<u32> offset(2);
        }

        void MenuCallback(void) {
            Battle::offset = {
                Helpers::AutoRegion<u32>(
                    Helpers::GetVersion<u32>(
                        {0x81FB284, 0x81FB624},
                        {0x81FB58C, 0x81FB92C}),

                    {0x30000484, 0x3000746C}
            )};
        }
    }

    bool IsInBattle(void) {
        static const u32 pointer = Helpers::AutoRegion(Helpers::GetVersion(0x81FB170, 0x81FB478), 0x30000158);
        ProcessPlus process;

        if ((process.Read32(pointer, data32, true) && data32 == 0x40001)) {
            if (group == Group::SM || group == Group::USUM) {
                if (process.Read8(pointer + 0x22, data8, true) && data8 == 3)
                    return true;

                else return false;
            }

            return true;
        }

        return false;
    }
}