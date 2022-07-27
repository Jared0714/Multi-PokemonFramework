#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "stdafx.hpp"

#include "PlayerSearchSystem.hpp"
#include "FestivalPlaza.hpp"
#include "Battle.hpp"
#include "Trainer.hpp"
#include "Computer.hpp"
#include "Movement.hpp"
#include "Miscellaneous.hpp"

using namespace CTRPluginFramework;

void InitMenu(PluginMenu &menu) {
    string note = Color::Orange << "Note" << Color::White << ": ";

    MenuFolder *gts = new MenuFolder("Global Trade Station");
    *gts += new MenuEntry("Configuration", Helpers::ChooseEntry(PSS::GlobalTradeStation::Configuration, Plaza::GlobalTradeStation::Configuration), Helpers::ChooseEntry(PSS::GlobalTradeStation::ConfigurationKB, Plaza::GlobalTradeStation::ConfigurationKB), note + "settings for depositing Pokémon.");
    *gts += new MenuEntry("Bypass 1 Deposit", Helpers::ChooseEntry(PSS::GlobalTradeStation::BypassLimit, Plaza::GlobalTradeStation::BypassLimit), note + "there will no longer be a limit as to how much you may deposit.");

    MenuFolder *plaza = new MenuFolder("Festival Plaza");
    *plaza += gts;
    *plaza += new MenuEntry("Current Rank", nullptr, Plaza::CurrentRank);
    *plaza += new MenuEntry("FC Collected", nullptr, Plaza::FCCollected);
    MenuFolder *records = new MenuFolder("Records");
    *records += new MenuEntry("Current FC", nullptr, Plaza::Profile::CurrentFC);
    *records += new MenuEntry("Guests Interacted With", nullptr, Plaza::Profile::GuestsInteracted);
    *records += new MenuEntry("Facilities Hosted", nullptr, Plaza::Profile::FacilitiesHosted);
    *records += new MenuEntry("Missions Participated In", nullptr, Plaza::Profile::MissionsParticipated);
    *plaza += records;
    *plaza += new MenuEntry("Image Crash Counter", Plaza::ImageCrashCounter);
    *plaza += new MenuEntry("Avoid Softban", Plaza::AvoidSoftban);

    MenuFolder *pss = new MenuFolder("Player Search System");
    *pss += gts;
    MenuFolder *profile = new MenuFolder("Profile");
    *profile += new MenuEntry("Icon", nullptr, PSS::Profile::Icons);
    *profile += new MenuEntry("Nices", nullptr, PSS::Profile::Nices);
    *profile += new MenuEntry("Wishes", nullptr, PSS::Profile::Wishes);
    *profile += new MenuEntry("Message", nullptr, PSS::Profile::Message);
    *profile += new MenuEntry("History", nullptr, PSS::Profile::History);
    *profile += new MenuEntry("Location", nullptr, PSS::Profile::Location);
    *profile += new MenuEntry("Links", nullptr, PSS::Profile::Links);
    *profile += new MenuEntry("Mini-Survey", nullptr, PSS::Profile::MiniSurvey);
    *profile += new MenuEntry("People Met", nullptr, PSS::Profile::Greets);
    *pss += profile;
    MenuFolder *opower = new MenuFolder("O-Power");
    *opower += new MenuEntry("Guage", PSS::Guage, PSS::GuageKB);
    *opower += new MenuEntry("Unlock Every Power", nullptr, PSS::UnlockEveryPower);
    *pss += opower;
    *pss += new MenuEntry("Shout-Out", nullptr, PSS::ShoutOut);
    *pss += new MenuEntry("Clear Users", PSS::ClearUsers, PSS::ClearUsersKB, note + "save the game and reload to apply the changes forever.");
    *pss += new MenuEntry("Bypass Gift & Centre Icon", PSS::BypassHackedIcons);
    menu += (group == Group::XY || group == Group::ORAS ? pss : plaza);

    MenuFolder *battle = new MenuFolder("Battle");
    MenuFolder *primary = new MenuFolder("Primary");

    *primary += new MenuFolder("Active", note + "must be in a battle to use.", vector<MenuEntry*>({
        new MenuEntry("Slot: " << Color::Gray << "0", nullptr, Battle::Universal::SlotKB),
        new MenuEntry("Condition", nullptr, Battle::Universal::Condition),
        new MenuEntry("Statistics", Battle::Universal::Statistics, Battle::Universal::StatisticsKB),
        new MenuEntry("Invincibility", Battle::Universal::Invincibility, Battle::Universal::InvincibilityKB),
        new MenuEntry("Item", nullptr, Battle::Universal::Item),
        new MenuEntry("Attacks", nullptr, Battle::Universal::Attacks),
        new MenuEntry("Exp. Multiplier", Battle::Universal::ExpMultiplier, Battle::Universal::ExpMultiplierKB)
    }));

    *primary += EntryWithHotkey(new MenuEntry("Poké View", nullptr, Battle::Universal::PokeView, note + "press the following hotkey(s) below to see the other information. Be aware that this is experiemental for now."), {Key::X, ""});
    *primary += EntryWithHotkey(new MenuEntry("Access Bag", Battle::Universal::AccessBag, note + "hold the hotkey(s) below while pressing on an action when in a battle."), {Key::R, ""});

    if (group == Group::XY || group == Group::ORAS)
        *primary += new MenuEntry("Bypass 1 Mega Restrict.", Battle::Gen6::Bypass1MegaRestrict);

    if (group == Group::SM || group == Group::USUM) {
        *primary += new MenuEntry("Always Critical Hit", Battle::Gen7::AlwaysCriticalHit);
        *primary += new MenuEntry("Bypass 1 Mega Restrict.", Battle::Gen7::Bypass1MegaRestrict);
        *primary += new MenuEntry("Infinite Z-Moves", Battle::Gen7::InfiniteZMoves);
        *primary += EntryWithHotkey(new MenuEntry("Z-Moves Without Crystal", Battle::Gen7::ZMovesWithoutCrystal, note + "activate before intiating a battle! When in battle, hold the hotkey(s) below while pressing on an action when in a battle."), {Key::L, ""});
    }

    *battle += primary;
    MenuFolder *other = new MenuFolder("Other");

    *other += new MenuFolder("Encounter", vector<MenuEntry*>({
        new MenuEntry("No Encounters", Helpers::ChooseEntry(Battle::Gen6::NoEncounters, Battle::Gen7::NoEncounters)),
        new MenuEntry("Spawner", nullptr, Helpers::ChooseEntry(Battle::Gen6::Spawner, Battle::Gen7::Spawner)),
        new MenuEntry("Shiny 100%", Battle::Universal::Shiny100),
        new MenuEntry("Disable Shiny Lock", Battle::Universal::DisableShinyLock, note + "this will allow you to remove the shiny not appearing setting on some Pokémon."),
        new MenuEntry("Rematch Legendary", nullptr, Helpers::ChooseEntry(Battle::Gen6::RematchLegendary, Battle::Gen7::RematchLegendary))
    }));

    if (group == Group::SM || group == Group::USUM) {
        *other += new MenuEntry("Re-fight Trainer", Battle::Gen7::RefightTrainer);
        *other += new MenuEntry("Reject Trainer Battle", Battle::Gen7::RejectTrainerBattle);
    }

    *other += new MenuEntry("Guaranteed Catch", Helpers::ChooseEntry(Battle::Gen6::GuaranteedCatch, Battle::Gen7::GuaranteedCatch));

    if (group == Group::SM || group == Group::USUM)
        *other += new MenuEntry("Can Catch Trial", Battle::Gen7::CanCatchTrial);

    *other += new MenuEntry("Catch Trainer's Pokémon", Helpers::ChooseEntry(Battle::Gen6::CatchTrainersPokemon, Battle::Gen7::CatchTrainersPokemon));
    *battle += other;
    *battle += new MenuEntry("Music", Battle::Music, Battle::MusicKB);
    menu += battle;

    MenuFolder *trainer = new MenuFolder("Trainer");
    MenuFolder *info = new MenuFolder("Information");
    *info += new MenuEntry("IDs", nullptr, Trainer::Info::IDs, Helpers::AutoRegion<string>("", note + "the ID that you see on your Pokémon is your TSV value."));
    (group == Group::XY || group == Group::ORAS) ? *info += EntryWithHotkey(new MenuEntry("Name", Trainer::Info::CopyToName, Trainer::Info::Name, note + "press the hotkey(s) below to copy the text from your shout-out to name."), {Key::Start | Key::A, ""}) : *info += new MenuEntry("Name", nullptr, Trainer::Info::Name);
    *info += new MenuEntry("Play Time", Trainer::Info::PlayTime, Trainer::Info::PlayTimeKB);
    *info += new MenuEntry("Language", Trainer::Info::Language, Trainer::Info::LanguageKB, note + "save and restart to apply the changes.");
    *trainer += info;
    MenuFolder *pouch = new MenuFolder("Pouch", note + "these cheats will unlock every possible item within the game, and will be automatically sorted via ID number.");
    MenuFolder *currency = new MenuFolder("Currency");
    *currency += new MenuEntry("Money", Trainer::Money, Trainer::MoneyKB);

    if (group == Group::XY || group == Group::ORAS)
        *currency += new MenuEntry("Poké Miles", Trainer::Gen6::PokeMiles, Trainer::Gen6::PokeMilesKB);

    *currency += new MenuEntry("Battle Points", Trainer::BattlePoints, Trainer::BattlePointsKB);
    *pouch += currency;
    *pouch += new MenuEntry("Items", Trainer::Pouch::Items, Trainer::Pouch::ItemsKB);
    *pouch += new MenuEntry("Medicines", Trainer::Pouch::Medicines, Trainer::Pouch::MedicinesKB);
    *pouch += new MenuEntry("Berries", Trainer::Pouch::Berries, Trainer::Pouch::BerriesKB);
    *pouch += new MenuEntry("Unlockable", nullptr, Trainer::Pouch::Unlockable);
    *trainer += pouch;
    (group == Group::XY || group == Group::ORAS ? *trainer += new MenuEntry("Badges", nullptr, Trainer::Gen6::Badges) : *trainer += new MenuEntry("Z-Crystals", nullptr, Trainer::Gen7::ZCrystals));
    *trainer += new MenuEntry("Pokédex", nullptr, Trainer::Pokedex);
    menu += trainer;

    MenuFolder *computer = new MenuFolder("Computer");
    *computer += new MenuEntry("Backup", nullptr, Computer::PCBackup);
    MenuFolder *editor = new MenuFolder("Editor");
    *editor += new MenuEntry("Setup", nullptr, Computer::Editor::Initialize, note + "this is to set up the Pokémon you would like to modify.");

    *editor += new MenuFolder("Main", vector<MenuEntry*>({
        new MenuEntry("Shiny", nullptr, Computer::Editor::Shinify),
        new MenuEntry("Species", nullptr, Computer::Editor::Species),
        new MenuEntry("Is Nicknamed", nullptr, Computer::Editor::IsNicknamed),
        new MenuEntry("Nickname", nullptr, Computer::Editor::Nickname),
        new MenuEntry("Level", nullptr, Computer::Editor::Level),
        new MenuEntry("Nature", nullptr, Computer::Editor::Nature),
        new MenuEntry("Gender", nullptr, Computer::Editor::Gender),
        new MenuEntry("Form", nullptr, Computer::Editor::Form),
        new MenuEntry("Held Item", nullptr, Computer::Editor::HeldItem),
        new MenuEntry("Ability", nullptr, Computer::Editor::Ability),
        new MenuEntry("Friendship", nullptr, Computer::Editor::Friendship),
        new MenuEntry("Language", nullptr, Computer::Editor::Language),
        new MenuEntry("Is Egg", nullptr, Computer::Editor::IsEgg),
        new MenuEntry("Pokerus", nullptr, Computer::Editor::Pokerus),
        new MenuEntry("Country", nullptr, Computer::Editor::Country),
        new MenuEntry("Region", nullptr),
        new MenuEntry("3DS Region", nullptr, Computer::Editor::ConsoleRegion)
    }));

    *editor += new MenuFolder("Obtained", vector<MenuEntry*>({
        new MenuEntry("Origin Game", nullptr, Computer::Editor::OriginGame),
        new MenuEntry("Met Location", nullptr, Computer::Editor::MetLocation),
        new MenuEntry("Ball", nullptr, Computer::Editor::Ball),
        new MenuEntry("Met Level", nullptr, Computer::Editor::MetLevel),
        new MenuEntry("Met Date", nullptr, Computer::Editor::MetDate),
        new MenuEntry("Is Fateful Encounter", nullptr, Computer::Editor::IsFatefulEncounter),
        new MenuEntry("Egg Met Location", nullptr, Computer::Editor::EggMetLoc),
        new MenuEntry("Egg Met Date", nullptr, Computer::Editor::EggMetDate)
    }));

    *editor += new MenuFolder("Stats", vector<MenuEntry*>({
        new MenuEntry("IVs", nullptr, Computer::Editor::IVs),
        new MenuEntry("EVs", nullptr, Computer::Editor::EVs, note + "keep in mind that there will be restrictions as to how much you can set per Pokémon."),
        new MenuEntry("Contest", nullptr, Computer::Editor::Contest)
    }));

    *editor += new MenuFolder("Attacks", vector<MenuEntry*>({
        new MenuEntry("Current Moves", nullptr, Computer::Editor::CurrentMoves),
        new MenuEntry("PP Ups", nullptr, Computer::Editor::PPUps),
        new MenuEntry("Relearn Moves", nullptr, Computer::Editor::RelearnMoves)
    }));

    *editor += new MenuFolder("Other", vector<MenuEntry*>({
        new MenuEntry("SID", nullptr, Computer::Editor::SID),
        new MenuEntry("TID", nullptr, Computer::Editor::TID),
        new MenuEntry("OT Name", nullptr, Computer::Editor::OTName),
        new MenuEntry("Latest (not OT) Handler", nullptr, Computer::Editor::LatestHandler),
        new MenuEntry("Ribbons", nullptr, Computer::Editor::Ribbons)
    }));

    *computer += editor;

    *computer += new MenuFolder("Cloning", vector<MenuEntry*>({
        new MenuEntry("Custom", nullptr, Computer::Cloning),
        EntryWithHotkey(new MenuEntry("Copy Pokémon in Trade", Computer::CopyPokemonInTrade, note + "this will overwrite any Pokémon sitting in slot 1 of box 1. If you understand, you may press on the following hotkeys."), {Hotkey(Key::Start, "")}),
        new MenuEntry("Keep Original Pokémon", Computer::KeepOriginalPokemon, Computer::KeepOriginalPokemonKB, note + "the Pokémon will not be affected if moved, edited or replaced, it will still be there.")
    }));

    *computer += new MenuEntry("PC Anywhere", Helpers::ChooseEntry(Computer::Gen6::PCAnywhere, Computer::Gen7::PCAnywhere), note + (group == Group::XY || group == Group::ORAS ? "tap the settings icon on the bottom screen." : "tap the settings icon from the in game menu screen."));
    *computer += new MenuEntry("Unlock Every Box", nullptr, Computer::UnlockEveryBox);
    menu += computer;

    MenuFolder *movement = new MenuFolder("Movement");

    if (group == Group::XY || group == Group::ORAS) {
        MenuFolder *etc = new MenuFolder("Etc.");

        if (group == Group::ORAS)
            *etc += new MenuEntry("Model Swap", nullptr, Movement::Gen6::ORAS::ModelSwapKB);

        *etc += new MenuEntry("No Action Reset", Movement::Gen6::NoActionReset);
        *etc += EntryWithHotkey(new MenuEntry("Teleportation", Movement::Gen6::Teleportation, Movement::Gen6::TeleportationKB, note + "hold the hotkey(s) below while moving."), {Key::L, ""});
        *etc += new MenuEntry("Unlock Locations", nullptr, Movement::Gen6::UnlockLocations);
        *etc += new MenuEntry("Can Use Fly Anywhere", Movement::Gen6::CanUseFlyAnywhere, note + "you must click on a Pokémon's summary through the 'X' menu in game.");
        *movement += etc;
    }

    if (group == Group::SM || group == Group::USUM) {
        *movement += new MenuFolder("Etc.", vector<MenuEntry*>({
            new MenuEntry("Get All Mounts", nullptr, Movement::Gen7::GetAllMounts, note + "all mounts will be registered and unlocked despite not reaching a certain point of the story."),
            EntryWithHotkey(new MenuEntry("Camera Zoom Out", Movement::Gen7::CameraZoomOut), {Hotkey(Key::L, "Zoom-Out"), Hotkey(Key::R, "Zoom-In")}),
            new MenuEntry("Remove Player Shadow", Movement::Gen7::RemovePlayerShadow)
        }));
    }

    *movement += new MenuEntry("Speed Up", Helpers::ChooseEntry(Movement::Gen6::SpeedUp, Movement::Gen7::SpeedUp), note + "only applies to walk and run speeds, and works with D-Pad.");
    *movement += new MenuEntry("Bypass Walls", Helpers::ChooseEntry(Movement::Gen6::BypassWalls, Movement::Gen7::BypassWalls));

    if (group == Group::SM || group == Group::USUM)
        *movement += new MenuEntry("Time of Day", nullptr, Movement::Gen7::TimeOfDay);

    menu += movement;

    MenuFolder *misc = new MenuFolder("Miscellaneous");
    MenuFolder *pokemon = new MenuFolder("Pokémon");
    *pokemon += new MenuEntry("Is Renamable", Misc::IsRenamable, note + "you will be able to rename any Pokémon despite it not being at your ownership.");
    *pokemon += new MenuEntry("Learn Any Teachables", Misc::LearnAnyTeachables, note + "you will be able to teach your Pokémon any moves.");
    *pokemon += new MenuEntry("Get Day Care Egg", Misc::GetDayCareEgg);
    *pokemon += new MenuEntry("Instant Egg Hatch", Helpers::ChooseEntry(Misc::Gen6::InstantEggHatch, Misc::Gen7::InstantEggHatch));

    *pokemon += new MenuFolder("Other", vector<MenuEntry*>({
        EntryWithHotkey(new MenuEntry("View Values in Summary", Helpers::ChooseEntry(Misc::Gen6::ViewValuesInSummary, Misc::Gen7::ViewValuesInSummary), note + "hold one of the following hotkey(s) to view your Individual and Effort Values."), {Hotkey(Key::L, ""), Hotkey(Key::R, "")})
    }));

    *misc += pokemon;
    *misc += new MenuEntry("Remove Outlines", Helpers::ChooseEntry(Misc::Gen6::NoOutlines, Misc::Gen7::NoOutlines), note + "removes outlines in the overworld and in battles.");
    *misc += new MenuEntry("Fast Dialogs", Misc::FastDialogs, note + "game dialogs will be sped up.");
    *misc += new MenuEntry("Bypass Text Restricts.", Misc::BypassTextRestricts);

    if ((group == Group::XY || group == Group::ORAS)) {
        *misc += new MenuFolder("Custom Game Keyboard", vector<MenuEntry*>({
            new MenuEntry("Config", nullptr, Misc::CustomKeyboardConfig, note + "for the in-game keyboard only. This overrides the 'More' section. Make sure to backup your customized keyboards so you won't have to re-enter the values."),
            EntryWithHotkey(new MenuEntry("Keys", Misc::CustomKeys, note + "press the hotkey(s) below to customize the keys. Press Y to clear keyboard. Accepting unicode values only, can be found elsewhere."), {Hotkey(Key::X, "")})
        }));
    }

    menu += misc;

    menu += new MenuEntry("Settings", nullptr, Settings, note + "resetting your settings will launch you straight back to the home menu, remember to save your game before doing so.");
}