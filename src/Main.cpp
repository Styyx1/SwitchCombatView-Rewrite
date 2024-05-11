#include "Logging.h"
#include "Manager.h"
#include "SKSE/Interfaces.h"
#include "Settings.h"
#include "Utility.h"
#include <Hooks.h>

void Listener(SKSE::MessagingInterface::Message* message) noexcept
{
    if (message->type <=> SKSE::MessagingInterface::kDataLoaded == 0) {
        auto settings = Settings::GetSingleton();
        settings->LoadSettings();
        CameraSwitch::Hooks::InstallActorUpdateHook();
        logger::info("Hook installed");
    }
}

SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
    InitializeLogging();

    const auto plugin{ SKSE::PluginDeclaration::GetSingleton() };
    const auto version{ plugin->GetVersion() };

    logger::info("{} {} is loading...", plugin->GetName(), version);
    Init(skse);
    Utility::Utility::GetSingleton()->CacheGameAddresses();
    SKSE::AllocTrampoline(64);
    Utility::Utility::GetSingleton()->CacheGameAddresses();
    if (const auto messaging{ SKSE::GetMessagingInterface() }; !messaging->RegisterListener(Listener))
        return false;

    logger::info("{} has finished loading.", plugin->GetName());

    return true;
}
