#pragma once

namespace Utility
{
    class Utility
    {
    public:
        uintptr_t PlayerSingletonAddress;
        uintptr_t UISingletonAddress;
        uintptr_t MenuControlsSingletonAddress;

        static Utility* GetSingleton()
        {
            static Utility playerStatus;
            return &playerStatus;
        }

        static RE::PlayerCharacter* GetPlayer()
        {
            REL::Relocation<RE::NiPointer<RE::PlayerCharacter>*> singleton{ Utility::GetSingleton()->PlayerSingletonAddress };
            return singleton->get();
        }

        static RE::MenuControls* GetMenuControls()
        {
            REL::Relocation<RE::NiPointer<RE::MenuControls>*> singleton{ Utility::GetSingleton()->MenuControlsSingletonAddress };
            return singleton->get();
        }

        static bool PlayerIsBeastFormRace()
        {
            auto menuControls = Utility::GetSingleton()->GetMenuControls();
            return menuControls->InBeastForm();
        }

        void CacheGameAddresses()
        {
            auto utility = Utility::GetSingleton();

            // Cache player singleton address
            utility->PlayerSingletonAddress       = RELOCATION_ID(517014, 403521).address();
            utility->UISingletonAddress           = RELOCATION_ID(514178, 400327).address();
            utility->MenuControlsSingletonAddress = RELOCATION_ID(515124, 401263).address();
        }
    };

}
