#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

using namespace CTRPluginFramework;

namespace Movement {
    namespace Gen6 {
        namespace ORAS {
            static int swap;

            void ModelSwap(void) {
                static const string s("4I7796H");
                ProcessPlus process;
                unsigned int x = stoul(process.Address(s, -5), nullptr, 16);

                if (!Process::Write32(x, CTRPluginFramework::ORAS::models[swap].id))
                    return;
            }

            void ModelSwapKB(MenuEntry *entry) { // Ty H4x0rSpooky & FunkyGamer26
                static vector<string> options;
                KeyboardPlus keyboard;

                if (options.empty()) {
                    for (const CTRPluginFramework::ORAS::Model &nickname : CTRPluginFramework::ORAS::models)
                        options.push_back(nickname.name);
                }

                if (keyboard.SetKeyboard(entry->Name() + ":", true, options, swap) != -1) {
                    ModelSwap();
                    Message::Completed();
                }
            }
        }

        void NoActionReset(MenuEntry *entry) {
            static const u32 address = (Helpers::GetVersion(0x3B9C30, 0x3D5EC8));
            static u32 original;
            static bool saved = false;

            if (!ProcessPlus::Write32(address, 0xE3A00000, original, entry, saved))
                return;
        }

        struct Locations {
            int direction;
            const char *name;
            int value;
            float x;
            float y;
        };

        static const Locations locations[63] = {
            {0, "Ambrette Town", 0x2F, 369, 495},
            {0, "Anistar City", 0xD6, 369, 495},
            {0, "Camphrier Town", 0xD, 369, 495},
            {0, "Coumarine City", 0xBE, 369, 495},
            {0, "Couriway Town", 0x28, 369, 495},
            {0, "Cyllage City", 0x9F, 369, 495},
            {0, "Day Care", 0x109, 225, 351},
            {0, "Dendemille Town", 0x21, 369, 495},
            {0, "Friend Safari", 0x163, 153, 315},
            {0, "Geosenge Town", 0x18, 369, 495},
            {0, "Kiloude City", 0xEA, 369, 495},
            {0, "Laverre City", 0xCA, 369, 495},
            {0, "Lumiose City", 0x167, 369, 495},
            {0, "Poké Ball Factory", 0x136, 279, 621},
            {0, "Pokémon Lab", 0x53, 207, 261},
            {0, "Pokémon League", 0xF4, 369, 495},
            {0, "Radiant Chamber", 0x100, 351, 423},
            {0, "Santalune City", 0x36, 369, 495},
            {0, "Santalune Forest", 0x11E, 729, 1359},
            {0, "Sea Spirit's Den", 0x15F, 333, 405},
            {0, "Shalour City", 0xAE, 369, 495},
            {0, "Snowbelle City", 0xE1, 369, 495},
            {0, "Team Flare HQ", 0x155, 711, 891},
            {0, "Terminus Cave", 0x15A, 765, 693},
            {0, "Unknown Dungeon", 0x13F, 351, 567},
            {0, "Vanville Town", 0x2, 369, 495},
            {0, "Video Studio", 0x6B, 315, 585},
            {0, "Ancient Tomb", 0x9F, 225, 333},
            {0, "Battle Resort", 0x206, 351, 441},
            {0, "Cave of Origin", 0x70, 333, 621},
            {0, "Day Care", 0x187, 225, 333},
            {0, "Desert Ruins", 0x4D, 225, 333},
            {0, "Dewford Town", 0xE8, 351, 441},
            {0, "Ever Grande City", 0x161, 351, 441},
            {0, "Fabled Cave", 0x20F, 387, 693},
            {0, "Fallarbor Town", 0xF0, 351, 441},
            {0, "Fortree City", 0x12D, 351, 441},
            {0, "Gnarled Den", 0x210, 369, 657},
            {0, "Granite Cave", 0x4E, 531, 639},
            {0, "Island Cave", 0x9E, 225, 333},
            {0, "Lilycove City", 0x135, 351, 441},
            {0, "Littleroot Town", 0xDF, 297, 333},
            {0, "Mauville City", 0x116, 351, 441},
            {0, "Meteor Falls", 0x47, 1035, 639},
            {0, "Mossdeep City", 0x14A, 351, 441},
            {0, "Nameless Cavern", 0x20E, 369, 657},
            {0, "New Mauville", 0x8B, 369, 657},
            {0, "Odale Town", 0xE4, 351, 441},
            {0, "Pacifidlog Town", 0xFD, 351, 441},
            {0, "Petalburg City", 0x103, 351, 441},
            {0, "Petalburg Woods", 0x52, 531, 1161},
            {0, "Pokémon League", 0x16C, 297, 387},
            {0, "Rustboro City", 0x11C, 351, 441},
            {0, "Rusturf Tunnel", 0x4B, 261, 369},
            {0, "Scorched Slab", 0xA7,261, 459},
            {1, "Sea Mauville", 0x92, 369, 45},
            {0, "Sealed Chambers", 0xA3, 801, 1305},
            {0, "Secret Meadow", 0x1DB, 387, 657},
            {0, "Sky Pillar", 0xB0, 639, 981},
            {0, "Slateport City", 0x109, 351, 441},
            {0, "Sootopolis City", 0x155, 351, 441},
            {0, "Verdanturf Town", 0xF6, 351, 441},
            {0, "Victory Road", 0x7B, 387, 855}
        };

        int placesAvailable = 0;
        static int place, direction;
        static float coords[2];

        void TeleportationKB(MenuEntry *entry) {
            static vector<string> options;
            KeyboardPlus keyboard;

            for (const Locations &nickname : locations) {
                if (placesAvailable < ((group == Group::XY) ? 27 : 63)) {
                    if (group == Group::ORAS) {
                        if (placesAvailable > 26)
                            options.push_back(nickname.name);
                    }

                    if (group == Group::XY)
                        options.push_back(nickname.name);

                    placesAvailable++;
                }

                else break;
            }

            if (keyboard.SetKeyboard(entry->Name() + ":", true, options, place) != -1) {
                coords[0] = locations[place + Helpers::GetVersion(0, 27)].x;
                coords[1] = locations[place + Helpers::GetVersion(0, 27)].y;
                Message::Completed();
            }
        }

        void Teleportation(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x8803BCA, 0x8803C20, 0x8C67192, 0x8C671A0, 0x8C671A8},
                    {0x8803BCA, 0x8803C20, 0x8C6E886, 0x8C6E894, 0x8C6E89C}
            )};

            if (entry->Hotkeys[0].IsDown()) {
                if (Process::Read16(address[1], data16) && data16 == 0x5544) {
                    if (Process::Write16(address[0], locations[place + Helpers::GetVersion(0, 27)].value)) {
                        if (Process::Write8(address[2], locations[place + Helpers::GetVersion(0, 27)].direction)) {
                            for (int i; i < 2; i++)
                                Process::WriteFloat(address[i + 3], coords[i]);
                        }
                    }
                }
            }
        }

        void UnlockLocations(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x8C7A81C, 0x8C81F24);
            static const vector<u8> flags = {Helpers::GetVersion<u8>({0xF7, 0xFF, 0xF}, {0xCA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0xFB, 0x81})};
            int length = 0;

            for (int i = 0; i < flags.size(); i++) {
                if (Process::Read8(address + i, data8) && data8 != flags[i])
                    Process::Write8(address + i, flags[i]);

                else length++;
            }

            if (length == flags.size()) {
                Message::Warning();
                return;
            }

            Message::Completed();
        }

        void CanUseFlyAnywhere(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x8C61CF0, 0x8C69330);

            if (Process::Read32(address, data32) && data32 == Helpers::GetVersion(0x6B65C4, 0x7007C0))
                Process::Write32(address, Helpers::GetVersion(0x6B6A30, 0x700C38));
        }

        void SpeedUp(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x8092DE4, 0x8092F34},
                    {0x80845E8, 0x808475C}
            )};

            vector<vector<u32>> check(2, vector<u32>(2));

            if (entry->IsActivated()) {
                vector<vector<u32>> check = {{0x13A05006, 0x3A05004}, {0x13A0500A, 0x3A05007}};

                if (CRO::Read32(address[0], 2) == check[0]) {
                    if (CRO::Read32(address[1], 2) == check[1]) {
                        if (CRO::Write32(address[0], {0x13A05003, 0x3A05002})) {
                            if (!CRO::Write32(address[1], {0x13A05005, 0x3A05003}))
                                return;
                        }
                    }
                }
            }

            if (!entry->IsActivated()) {
                vector<vector<u32>> check = {{0x13A05003, 0x3A05002}, {0x13A05005, 0x3A05003}};

                if (CRO::Read32(address[0], 2) == check[0]) {
                    if (CRO::Read32(address[1], 2) == check[1]) {
                        if (CRO::Write32(address[0], {0x13A05006, 0x3A05004})) {
                            if (!CRO::Write32(address[1], {0x13A0500A, 0x3A05007}))
                                return;
                        }
                    }
                }
            }
        }

        void BypassWalls(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x53ED50, Helpers::PickGame<u32>(0x80B5820, 0x80B5824), Helpers::PickGame<u32>(0x80B3A1C, 0x80B3A20)},
                    {0x579820, 0x80BB414, 0x80B87F8}
            )};

            static vector<u32> original(4);
            static bool saved = false;

            if (ProcessPlus::Write32(address[0], {0xE3A01000, 0xE12FFF1E, 0xE3A06000, 0xE12FFF1E}, original, entry, saved)) {
                if (entry->IsActivated()) {
                    if (CRO::Read32(address[1]) == 0xE1A01000) {
                        if (CRO::Read32(address[2]) == 0xE1A06000) {
                            if (CRO::Write32(address[1], Helpers::GetVersion(Helpers::PickGame(0xEBF8914A, 0xEBF89139), 0xEBF83D01))) {
                                if (!CRO::Write32(address[2], Helpers::GetVersion(Helpers::PickGame(0xEBF898CD, 0xEBF898CC), 0xEBF8480A)))
                                    return;
                            }
                        }
                    }
                }

                if (!entry->IsActivated()) {
                    if (CRO::Read32(address[1]) == Helpers::GetVersion(Helpers::PickGame(0xEBF8914A, 0xEBF89139), 0xEBF83D01)) {
                        if (CRO::Read32(address[2]) == Helpers::GetVersion(Helpers::PickGame(0xEBF898CD, 0xEBF898CC), 0xEBF8480A)) {
                            if (CRO::Write32(address[1], 0xE1A01000)) {
                                if (!CRO::Write32(address[2], 0xE1A06000))
                                    return;
                            }
                        }
                    }
                }
            }
        }
    }

    namespace Gen7 {
        void GetAllMounts(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x330D7810, 0x330138D0);

            if (Process::Read32(address, data32) && (data32 & ~0xFFF00000) != 0x3FF80) {
                if (Process::Read32(address, data32)) {
                    data32 &= 0xFFF00000;
                    data32 += 0x3FF80;
                    Process::Write32(address, data32);
                }

                Message::Completed();
                return;
            }

            else Message::Warning();
        }

        void CameraZoomOut(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x597724, 0x8037B18, 0x59773C},
                    {0x5BBF80, 0x803B920, 0x5BBF98}
            )};

            static u32 patch[7] = {0xED940A1C, 0xED9F1A03, 0xEE300A01, 0xED840A1C, 0xE2840004, 0xE12FFF1E, 0};

            if (entry->WasJustActivated())
                Process::Patch(address[0], patch, 0x1C);

            if (entry->IsActivated()) {
                if (CRO::Read32(address[1]) == 0xE2840004)
                    CRO::Write32(address[1], Helpers::GetVersion<u32>(0xEBFAEB01, 0xEBFAA996));

                if (entry->Hotkeys[0].IsPressed())
                    Process::Write32(address[2], 0xC4BB8000);

                if (entry->Hotkeys[1].IsPressed())
                    Process::Write32(address[2], 0);
            }

            if (!entry->IsActivated())
                Process::Patch(address[0], 0, 0x1C);
        }

        void RemovePlayerShadow(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x39CA54, Helpers::PickGame(0x3AB574, 0x3AB578));
            static u32 original;
            static bool saved = false;

            if (!ProcessPlus::Write32(address, 0, original, entry, saved))
                return;
        }

        void SpeedUp(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x39C394, Helpers::PickGame(0x3AAEB0, 0x3AAEB4));
            static u32 original;
            static bool saved = false;

            if (!ProcessPlus::Write32(address, 0x3FB33333, original, entry, saved))
                return;
        }

        void BypassWalls(MenuEntry *entry) {
            static const vector<u32> address = {
                Helpers::GetVersion<u32>(
                    {0x39E560, 0x39E694},
                    {Helpers::PickGame<u32>(0x3AD228, 0x3AD22C), Helpers::PickGame<u32>(0x3AD35C, 0x3AD360)}
            )};

            static vector<vector<u32>> original(2, vector<u32>(2));
            static bool saved[2] = {false, false};

            if (ProcessPlus::Write32(address[0], {0xE1A00000, 0xE1A00000}, original[0], entry, saved[0])) {
                if (!ProcessPlus::Write32(address[1], {0xE1A00000, 0xE1A00000}, original[1], entry, saved[1])) {
                    return;
                }
            }
        }

        static u8 time;

        void TimeOfDay(MenuEntry *entry) {
            static const u32 address = Helpers::GetVersion(0x330D9238, 0x330154B0);

            if (KB<u8>("Time of Day:\n\nChoose an offset between 1-24 hours\n\n" << Color::SkyBlue << "12H" << Color::White << " - Moon" << Color::Orange << " 24H" << Color::White << " - Sun", true, false, 2, time, 0, 1, 24, Callback8)) {
                Process::Write32(address, time * 3600);
                Message::Completed();
            }
        }
    }
}