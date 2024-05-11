#include "Function.h"

#include <spdlog/sinks/ostream_sink.h>

MFMAPI bool first_person_mode()
{
    auto        settings = Settings::GetSingleton();
    std::string msg      = "changed view mode";
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(R"(.\Data\SKSE\Plugins\SwitchCombatView.ini)");
    settings->first_person_mode = !settings->first_person_mode;
    Utility::Utility::PrintMSG(msg);
    logger::debug("changed view mode");
    ini.SetBoolValue("Settings", "bFirstPersonLock", settings->first_person_mode);
    (void)ini.SaveFile(R"(.\Data\SKSE\Plugins\SwitchCombatView.ini)");
}

MFMAPI bool in_combat()
{
    auto        settings = Settings::GetSingleton();
    std::string msg      = "changed combat mode";
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(R"(.\Data\SKSE\Plugins\SwitchCombatView.ini)");
    settings->in_combat = !settings->in_combat;
    Utility::Utility::PrintMSG(msg);
    logger::debug("changed combat settings");
    ini.SetBoolValue("Settings", "bInCombat", settings->in_combat);
    (void)ini.SaveFile(R"(.\Data\SKSE\Plugins\SwitchCombatView.ini)");
}

MFMAPI void ReloadConfig(char* a_msg, std::size_t a_len)
{
    std::ostringstream oss;

    auto sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(oss);
    sink->set_pattern("[%l] %v");
    spdlog::default_logger_raw()->sinks().push_back(sink);
    auto settings = Settings::GetSingleton();
    try {
        settings->LoadSettings();
    }
    catch (const std::exception&) {
        // Suppress exception.
    }

    auto msg = oss.str();
    std::memcpy(a_msg, msg.c_str(), std::min(msg.size() + 1, a_len));
    spdlog::default_logger_raw()->sinks().pop_back();
}
