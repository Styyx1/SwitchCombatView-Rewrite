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
            if (p_cam->IsInFirstPerson() && player->IsInCombat() && !view_saved && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace()) {
                // will only happen when you enter combat in 1st person
                // changes your view to third

                view_saved = false; // attempt for another fail save
                view_saved = true;
                p_cam->ForceThirdPerson();
                logger::debug("changed View");
            }
            if (p_cam->IsInThirdPerson() && !player->IsInCombat() && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace() && view_saved) {
                // checks if you are in 3rd person and if the view bool was previously changed to true.
                // if so, it sets you back to 1st person like you were before entering combat

                view_saved = true; // attempt for another fail save
                view_saved = false;
                p_cam->ForceFirstPerson();
                logger::debug("returned to init view");
            }
        }
        else if (!settings->in_combat) {
            if (p_cam->IsInFirstPerson() && player->AsActorState()->IsWeaponDrawn() && !view_saved && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace()) {
                // will only happen when you enter combat in 1st person
                // changes your view to third

                view_saved = false; // attempt for another fail save
                view_saved = true;
                p_cam->ForceThirdPerson();
                logger::debug("changed View");
            }
            if (p_cam->IsInThirdPerson() && !player->AsActorState()->IsWeaponDrawn() && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace() && view_saved) {
                // checks if you are in 3rd person and if the view bool was previously changed to true.
                // if so, it sets you back to 1st person like you were before entering combat

                view_saved = true; // attempt for another fail save
                view_saved = false;
                p_cam->ForceFirstPerson();
                logger::debug("returned to init view");
            }
        }
    }
    else {
        if (settings->in_combat) {
            if (p_cam->IsInThirdPerson() && player->IsInCombat() && !view_saved && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace()) {
                view_saved = false; // attempt for another fail save
                view_saved = true;
                p_cam->ForceFirstPerson();
                logger::debug("changed View");
            }
            if (p_cam->IsInFirstPerson() && !player->IsInCombat() && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace() && view_saved) {
                // checks if you are in 3rd person and if the view bool was previously changed to true.
                // if so, it sets you back to 1st person like you were before entering combat

                view_saved = true; // attempt for another fail save
                view_saved = false;
                p_cam->ForceThirdPerson();
                logger::debug("returned to init view");
            }
        }
        else if (!settings->in_combat) {
            if (p_cam->IsInThirdPerson() && player->AsActorState()->IsWeaponDrawn() && !view_saved && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace()) {
                // will only happen when you enter combat in 1st person
                // changes your view to third

                view_saved = false; // attempt for another fail save
                view_saved = true;
                p_cam->ForceFirstPerson();
                logger::debug("changed View");
            }
            if (p_cam->IsInFirstPerson() && !player->AsActorState()->IsWeaponDrawn() && !player->AsActorState()->IsBleedingOut() && !util->PlayerIsBeastFormRace() && view_saved) {
                // checks if you are in 3rd person and if the view bool was previously changed to true.
                // if so, it sets you back to 1st person like you were before entering combat

                view_saved = true; // attempt for another fail save
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
