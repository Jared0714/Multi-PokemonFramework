#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <CTRPluginFramework.hpp>

using namespace CTRPluginFramework;

namespace Movement {
    namespace Gen6 {
        void UnlockLocations(MenuEntry *entry);
        void CanUseFlyAnywhere(MenuEntry *entry);
        void TeleportationKB(MenuEntry *entry);
        void Teleportation(MenuEntry *entry);
        void SpeedUp(MenuEntry *entry);
        void BypassWalls(MenuEntry *entry);
        void NoActionReset(MenuEntry *entry);
    }

    namespace Gen7 {
        void GetAllMounts(MenuEntry *entry);
        void CameraZoomOut(MenuEntry *entry);
        void RemovePlayerShadow(MenuEntry *entry);
        void SpeedUp(MenuEntry *entry);
        void BypassWalls(MenuEntry *entry);
        void TimeOfDay(MenuEntry *entry);
    }
}

#endif