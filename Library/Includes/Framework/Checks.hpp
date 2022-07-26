#ifndef CHECKS_HPP
#define CHECKS_HPP

#include <CTRPluginFramework.hpp>
#include "../../../Includes/stdafx.hpp"

namespace CTRPluginFramework {
    using FuncPointer = void(*)(MenuEntry*);

    enum class Game : int {None, X, Y, OR, AS, S, M, US, UM};
    enum class Group : int {None, XY, ORAS, SM, USUM};
    enum class Update : int {Unsupported, Supported};

    extern Game game;
    extern Group group;
    extern Update update;

    namespace Helpers {
        FuncPointer ChooseEntry(FuncPointer func1, FuncPointer func2);

        template <typename T>
        T PickGame(T game1, T game2) {
            return ((game == Game::X || game == Game::OR || game == Game::S || game == Game::US) ? game1 : game2);
        }

        template <typename T>
        T GetVersion(T version1, T version2) {
            return ((group == Group::XY || group == Group::SM) ? version1 : version2);
        }

        template<typename T>
        vector<T> GetVersion(vector<T> version1, vector<T> version2) {
            return ((group == Group::XY || group == Group::SM) ? version1 : version2);
        }

        template <typename T>
        T AutoRegion(T region1, T region2) {
            return ((group == Group::XY || group == Group::ORAS) ? region1 : region2);
        }

        template <typename T>
        vector<T> AutoRegion(vector<T> region1, vector<T> region2) {
            return ((group == Group::XY || group == Group::ORAS) ? region1 : region2);
        }
    }
}

#endif