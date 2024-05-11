#include "Settings.h"

void Settings::LoadSettings() noexcept
{
    logger::info("Loading settings");

    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(R"(.\Data\SKSE\Plugins\SwitchCombatViewSKSE.ini)");

    lock_third_person = ini.GetBoolValue("Settings", "bLockThirdPerson");
    in_combat         = ini.GetBoolValue("Settings", "bInCombat");
    first_person_mode = ini.GetBoolValue("Settings", "bFirstPersonLock");
    debug_logging     = ini.GetBoolValue("Log", "Debug");

    if (first_person_mode) {
        lock_third_person = false;
    }

    if (debug_logging) {
        spdlog::get("Global")->set_level(spdlog::level::level_enum::debug);
        logger::debug("Debug logging enabled");
    };
    // Load settings
    logger::info("Loaded settings");
};
