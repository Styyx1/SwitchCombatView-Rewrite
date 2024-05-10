#include "Logging.h"
#include "SKSE/Interfaces.h"
#include "Settings.h"
#include "Manager.h"
#include <Hooks.h>
#include "Utility.h"

void Listener(SKSE::MessagingInterface::Message* message) noexcept
{
    if (message->type == SKSE::MessagingInterface::kInputLoaded) {
        // Settings::LoadSettings();
        
        CameraSwitch::Hooks::InstallActorUpdateHook();
        logger::info("Hook installed");
    }
    if (message->type <=> SKSE::MessagingInterface::kDataLoaded == 0) {
        auto settings = Settings::GetSingleton();
        settings->LoadSettings();
    }
}

SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
    InitializeLogging();

    const auto plugin{ SKSE::PluginDeclaration::GetSingleton() };
    const auto version{ plugin->GetVersion() };

    logger::info("{} {} is loading...", plugin->GetName(), version);
    Init(skse);
    SKSE::AllocTrampoline(64);
    Utility::Utility::GetSingleton()->CacheGameAddresses();
    if (const auto messaging{ SKSE::GetMessagingInterface() }; !messaging->RegisterListener(Listener))
        return false;

    logger::info("{} has finished loading.", plugin->GetName());

    return true;
}
