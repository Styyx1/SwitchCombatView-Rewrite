#include "Manager.h"
#include "Settings.h"
#include "Utility.h"

void CameraSwitch::ViewChanger::Change()
{
    const auto  player   = RE::PlayerCharacter::GetSingleton();
    const auto  p_cam    = RE::PlayerCamera::GetSingleton();
    auto        util     = Utility::Utility::GetSingleton();
    auto        settings = Settings::GetSingleton();
    static bool view_saved{ false };
    if (!settings->first_person_mode) {
        if (settings->in_combat) {
            if (p_cam->IsInFirstPerson() && player->IsInCombat() && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace()) {
                // will only happen when you enter combat in 1st person
                // changes your view to third
                if (!view_saved) {
                    p_cam->ForceThirdPerson();
                    view_saved = true;
                    logger::debug("changed View");
                }
                else if (view_saved && p_cam->IsInFirstPerson()) {
                    p_cam->ForceThirdPerson();
                    // this will block changing to first person if you changed to 3rd automatically previously
                }
            }
            if (p_cam->IsInThirdPerson() && !player->IsInCombat() && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace()) {
                if (view_saved) {
                    p_cam->ForceFirstPerson();
                    view_saved = false;
                    p_cam->Update();
                    logger::debug("returned to init view");
                }
                // checks if you are in 3rd person and if the view bool was previously changed to true.
                // if so, it sets you back to 1st person like you were before entering combat 
            }
        }
        else if (!settings->in_combat) {
            if (p_cam->IsInFirstPerson() && player->AsActorState()->IsWeaponDrawn() && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace()) {
                // will only happen when you draw a weapon (or spell, or unarmed) in 1st person
                // changes your view to third
                if (!view_saved) {
                    p_cam->ForceThirdPerson();
                    view_saved = true;
                    logger::debug("changed View");
                }
                else if (view_saved && p_cam->IsInFirstPerson()) {
                    p_cam->ForceThirdPerson();
                    // this will block changing to first person if you changed to 3rd automatically previously
                }
            }
            if (p_cam->IsInThirdPerson() && !player->AsActorState()->IsWeaponDrawn() && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace() && view_saved) {
                // checks if you are in 3rd person and if the view bool was previously changed to true.
                // if so, it sets you back to 1st person like you were before entering combat

                p_cam->ForceFirstPerson();
                view_saved = false;
                p_cam->Update();
                logger::debug("returned to init view");
            }
        }
    }
    else if(settings->first_person_mode)
        {
        if (settings->in_combat) {
            if (p_cam->IsInThirdPerson() && player->IsInCombat() && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace()) {
                if (!view_saved) {
                    p_cam->ForceFirstPerson();
                    view_saved = true;
                    logger::debug("changed View");
                }
                else if (view_saved && p_cam->IsInThirdPerson()) {
                    p_cam->ForceFirstPerson();
                }  
            }
            if (p_cam->IsInFirstPerson() && !player->IsInCombat() && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace() && view_saved) {
                // checks if you are in 3rd person and if the view bool was previously changed to true.
                // if so, it sets you back to 1st person like you were before entering combat

                view_saved = false;
                p_cam->ForceThirdPerson();
                logger::debug("returned to init view");
            }
        }
        else if (!settings->in_combat) {
            if (p_cam->IsInThirdPerson() && player->AsActorState()->IsWeaponDrawn() && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace()) {
                // will only happen when you enter combat in 1st person
                // changes your view to third
                if (!view_saved) {
                    p_cam->ForceFirstPerson();
                    view_saved = true;
                    logger::debug("changed View");
                }
                else if (view_saved && p_cam->IsInThirdPerson()) {
                    p_cam->ForceFirstPerson();
                }  
            }
            if (p_cam->IsInFirstPerson() && !player->AsActorState()->IsWeaponDrawn() && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace() && view_saved) {
                // checks if you are in 3rd person and if the view bool was previously changed to true.
                // if so, it sets you back to 1st person like you were before entering combat
                view_saved = false;
                p_cam->ForceThirdPerson();
                logger::debug("returned to init view");
            }
        }
    }
};

void CameraSwitch::ViewChanger::ActorUpdateF(RE::Actor* a_actor, float a_zPos, RE::TESObjectCELL* a_cell)
{
    auto switcher = CameraSwitch::ViewChanger::GetSingleton();
    switcher->Change();
    return _ActorUpdateF(a_actor, a_zPos, a_cell);
}
