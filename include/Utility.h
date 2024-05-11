#pragma once

namespace Utility
{
    class Utility
    {
    public:
        uintptr_t PlayerSingletonAddress;
        uintptr_t UISingletonAddress;
        uintptr_t MenuControlsSingletonAddress;
        uintptr_t PlayerCameraSingletonAddress;

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

        static RE::PlayerCamera* GetPlayerCamera()
        {
            REL::Relocation<RE::NiPointer<RE::PlayerCamera>*> singleton{ Utility::GetSingleton()->PlayerCameraSingletonAddress };
            return singleton->get();
        }

        static bool PlayerIsBeastFormRace()
        {
            auto menuControls = Utility::GetSingleton()->GetMenuControls();
            return menuControls->InBeastForm();
        }

        static bool IsModCondition()
        {
            auto settings = Settings::GetSingleton();
            if (settings->first_person_mode || settings->lock_third_person)
                return true;
            else
                return false;
        }

        void CacheGameAddresses()
        {
            auto utility = Utility::GetSingleton();

            // Cache player singleton address
            utility->PlayerSingletonAddress       = RELOCATION_ID(517014, 403521).address();
            utility->UISingletonAddress           = RELOCATION_ID(514178, 400327).address();
            utility->MenuControlsSingletonAddress = RELOCATION_ID(515124, 401263).address();
            utility->PlayerCameraSingletonAddress = RELOCATION_ID(514642, 400802).address();
        }

        static void PrintMSG(std::string message) { RE::DebugNotification(message.c_str()); }
    };

} // namespace Utility
