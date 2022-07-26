#include <CTRPluginFramework.hpp>
#include "stdafx.hpp"
#include "Helpers.hpp"

namespace CTRPluginFramework {
    u16 spwnSpecies;
    u8 spawnLv;
    u8 spwnForm;
    int pkmnID;

    int MatchPkmn(Pokemon &output, string &input) {
        int index = 0;
        output.name.clear();
        string lowerCase(input);

        for (char &character : lowerCase)
            character = tolower(character);

        // Parse our possibilities to find the matches
        for (const string &pkmn : allPkmn) {
            string::iterator iterator = lowerCase.begin();
            string::const_iterator pokeIterator = pkmn.begin();

            // Parse every letter of input while it matches the Pokémon's name
            while (iterator != lowerCase.end() && pokeIterator != pkmn.end() && *iterator == tolower(*pokeIterator)) {
                ++iterator;
                ++pokeIterator;
            }

            if (index < Helpers::AutoRegion(721, Helpers::GetVersion(802, 807))) {
                if (iterator == lowerCase.end()) {
                    output.name.push_back(pkmn);
                    output.choiceNo.push_back(index);
                }
            }

            index++;
        }

        return (output.choiceNo.size());
    }

    void PkmnInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();
        Pokemon matches;
        int count = MatchPkmn(matches, input), choice;

        // If the user removed a letter, clear the input and set an error
        if (event.type == KeyboardEvent::CharacterRemoved) {
            input = "";
            keyboard.SetError("Type a letter to search for a Pokémon.");
            return;
        }

         // Else if input's length is inferior than 3, ask for more letters
        else if (input.size() < 3) {
            keyboard.SetError("Not enough letters to do the search.");
            return;
        }

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError("Nothing matches your input. Please try again.");
            return;
        }

        // If we have only one matches, complete the input
        if (count == 1) {
            pkmnID = matches.choiceNo[0] + 1;
            input = matches.name[0];
            return;
        }

        if (count == 2 && input == "Mew") {
            pkmnID = matches.choiceNo[1] + 1;
            input = matches.name[1];
            return;
        }

        // If we have less than or equal to ten matches, populate a list keyboard
        if (count > 1 && count <= 10 && input != "Mew") {
            Keyboard kb(matches.name);
            kb.CanAbort(false);
            kb.DisplayTopScreen = false;
            choice = kb.Open();

            if (choice >= 0) {
                pkmnID = matches.choiceNo[choice] + 1;
                input = matches.name[choice];
                return;
            }
        }

        // We have too much results, the user must keep typing letters
        keyboard.SetError("Too many results: " + to_string(count) + "\nType more letters to narrow down the results.");
    }

    void FindPkmnKB(MenuEntry *entry) {
        string output;

        if (KB<string>("Pokémon:", true, 11, output, "", PkmnInputChange))
            return;

        pkmnID = 0;
    }

    int abilityID;

    int MatchAbility(Ability &output, string &input) {
        int index = 0;
        output.name.clear();
        string lowerCase(input);

        for (char &character : lowerCase)
            character = tolower(character);

        // Parse our possibilities to find the matches
        for (const string &ability : allAbilities) {
            string::iterator iterator = lowerCase.begin();
            string::const_iterator itemIterator = ability.begin();

            // Parse every letter of input while it matches the ability's name
            while (iterator != lowerCase.end() && itemIterator != ability.end() && *iterator == tolower(*itemIterator)) {
                ++iterator;
                ++itemIterator;
            }

            if (index < Helpers::AutoRegion(Helpers::GetVersion(188, 191), 233)) {
                if (iterator == lowerCase.end()) {
                    output.name.push_back(ability);
                    output.choiceNo.push_back(index);
                }
            }

            index++;
        }

        return (output.choiceNo.size());
    }

    void AbilityInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();
        Ability matches;
        int count = MatchAbility(matches, input), choice;

        // If the user removed a letter, clear the input and set an error
        if (event.type == KeyboardEvent::CharacterRemoved) {
            input = "";
            keyboard.SetError("Type a letter to search for an ability.");
            return;
        }

         // Else if input's length is inferior than 3, ask for more letters
        else if (input.size() < 3) {
            keyboard.SetError("Not enough letters to do the search.");
            return;
        }

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError("Nothing matches your input. Please try again.");
            return;
        }

        // If we have only one matches, complete the input
        if (count == 1) {
            abilityID = matches.choiceNo[0] + 1;
            input = matches.name[0];
            return;
        }

        // If we have less than or equal to ten matches, populate a list keyboard
        if (count <= 10) {
            Keyboard kb(matches.name);
            kb.CanAbort(false);
            kb.DisplayTopScreen = false;
            choice = kb.Open();

            if (choice >= 0) {
                abilityID = matches.choiceNo[choice] + 1;
                input = matches.name[choice];
                return;
            }
        }

        // We have too much results, the user must keep typing letters
        keyboard.SetError("Too many results: " + to_string(count) + "\nType more letters to narrow down the results.");
    }

    void FindAbilityKB(MenuEntry *entry) {
        string output;

        if (KB<string>("Ability:", true, 16, output, "", AbilityInputChange))
            return;

        abilityID = 0;
    }

    int heldItemID;

    int MatchHeldItem(HeldItem &output, string &input) {
        static const vector<int> ignored = {112, 113, 114, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 425, 426, 621, 806, 807, 808, 809, 810, 811, 812, 813, 814, 815, 816, 817, 818, 819, 820, 821, 822, 823, 824, 825, 826, 827, 828, 829, 830, 831, 832, 833, 834, 836, 837, 838, 839, 847, 858, 860, 861, 862, 863, 864, 865, 866, 867, 868, 869, 870, 871, 872, 873, 874, 875, 876, 877, 884, 885, 886, 887, 888, 889, 890, 891, 892, 893, 894, 895, 896, 897, 898, 899, 900, 901, 902, 926, 927, 928, 929, 930, 931};        int index = 0;
        output.name.clear();
        string lowerCase(input);

        for (char &character : lowerCase)
            character = tolower(character);

        // Parse our possibilities to find the matches
        for (const string &item : allItems) {
            string::iterator iterator = lowerCase.begin();
            string::const_iterator itemIterator = item.begin();

            // Parse every letter of input while it matches the held item's name
            while (iterator != lowerCase.end() && itemIterator != item.end() && *iterator == tolower(*itemIterator)) {
                ++iterator;
                ++itemIterator;
            }

            if (index < Helpers::AutoRegion(Helpers::GetVersion(717, 775), Helpers::GetVersion(920, 959))) {
                if (*find(ignored.begin(), ignored.end(), index) != index) {
                    if (iterator == lowerCase.end()) {
                        output.name.push_back(item);
                        output.choiceNo.push_back(index);
                    }
                }
            }

            index++;
        }

        return (output.choiceNo.size());
    }

    void ItemInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();
        HeldItem matches;
        int count = MatchHeldItem(matches, input), choice;

        // If the user removed a letter, clear the input and set an error
        if (event.type == KeyboardEvent::CharacterRemoved) {
            input = "";
            keyboard.SetError("Type a letter to search for an item.");
            return;
        }

         // Else if input's length is inferior than 3, ask for more letters
        else if (input.size() < 3) {
            keyboard.SetError("Not enough letters to do the search.");
            return;
        }

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError("Nothing matches your input. Please try again.");
            return;
        }

        // If we have only one matches, complete the input
        if (count == 1) {
            heldItemID = matches.choiceNo[0] + 1;
            input = matches.name[0];
            return;
        }

        // If we have less than or equal to ten matches, populate a list keyboard
        if (count <= 10) {
            Keyboard kb;
            kb.CanAbort(false);
            kb.DisplayTopScreen = false;
            kb.Populate(matches.name);
            choice = kb.Open();

            if (choice >= 0) {
                heldItemID = matches.choiceNo[choice] + 1;
                input = matches.name[choice];
                return;
            }
        }

        // We have too much results, the user must keep typing letters
        keyboard.SetError("Too many results: " + to_string(count) + "\nType more letters to narrow down the results.");
    }

    void FindItemKB(MenuEntry *entry) {
        string output;

        if (KB<string>("Item:", true, 18, output, "", ItemInputChange))
            return;

        heldItemID = 0;
    }

    int moveID = 0;

    int MatchMove(Moves &output, string &input) {
        int index = 0;
        output.name.clear();
        string lowerCase(input);
        static const vector<int> ignored = {622, 623, 624, 625, 626, 627, 628, 629, 630, 631, 632, 633, 634, 635, 636, 637, 638, 639, 640, 641, 642, 643, 644, 645, 646, 647, 648, 649, 650, 651, 652, 653, 654, 655, 656, 657, 658, 695, 696, 697, 698, 699, 700, 701, 702, 703, 719, 723, 724, 725, 726, 727, 728};

        for (char &character : lowerCase)
            character = tolower(character);

        // Parse our possibilities to find the matches
        for (const string &moves : allMoves) {
            string::iterator iterator = lowerCase.begin();
            string::const_iterator itemIterator = moves.begin();

            // Parse every letter of input while it matches the move's name
            while (iterator != lowerCase.end() && itemIterator != moves.end() && *iterator == tolower(*itemIterator)) {
                ++iterator;
                ++itemIterator;
            }

            if (index < Helpers::AutoRegion(Helpers::GetVersion(617, 621), Helpers::GetVersion(719, 728))) {
                if (*find(ignored.begin(), ignored.end(), index) != index) {
                    if (iterator == lowerCase.end()) {
                        output.name.push_back(moves);
                        output.choiceNo.push_back(index);
                    }
                }
            }

            index++;
        }

        return (output.choiceNo.size());
    }

    void MoveInputChange(Keyboard &keyboard, KeyboardEvent &event) {
        string &input = keyboard.GetInput();
        Moves matches;
        int count = MatchMove(matches, input);

        // If the user removed a letter, clear the input and set an error
        if (event.type == KeyboardEvent::CharacterRemoved) {
            input = "";
            keyboard.SetError("Type a letter to search for a move.");
            return;
        }

         // Else if input's length is inferior than 3, ask for more letters
        else if (input.size() < 3) {
            keyboard.SetError("Not enough letters to do the search.");
            return;
        }

        // If we don't have any matches, tell the user
        if (!count) {
            keyboard.SetError("Nothing matches your input. Please try again.");
            return;
        }

        // If we have only one matches, complete the input
        if (count == 1) {
            moveID = matches.choiceNo[0] + 1;
            input = matches.name[0];
            return;
        }

        // If we have less than or equal to ten matches, populate a list keyboard
        if (count <= 10) {
            Keyboard kb(matches.name);
            kb.CanAbort(false);
            kb.DisplayTopScreen = false;
            int choice = kb.Open();

            if (choice >= 0) {
                moveID = matches.choiceNo[choice] + 1;
                input = matches.name[choice];
                return;
            }
        }

        // We have too much results, the user must keep typing letters
        keyboard.SetError("Too many results: " + to_string(count) + "\nType more letters to narrow down the results.");
    }

    void FindMoveKB(MenuEntry *entry) {
        string output;

        if (KB<string>("Move:", true, 27, output, "", MoveInputChange))
            return;

        moveID = 0;
    }
}