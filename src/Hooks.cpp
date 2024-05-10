#include "Hooks.h"

void CameraSwitch::Hooks::InstallActorUpdateHook()
{
    REL::Relocation<std::uintptr_t> ActorUpdate{ REL::RelocationID(36357, 37348), REL::Relocate(0x6D3, 0x674) }; // Credits for the AE Offset goes to Nightfallstorm.
    auto&                           trampoline = SKSE::GetTrampoline();
    _ActorUpdateF                              = trampoline.write_call<5>(ActorUpdate.address(), ActorUpdateF);
}
