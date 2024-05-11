#pragma once

namespace CameraSwitch
{
    class ViewChanger
    {
    public:
        void Change();

        virtual ~ViewChanger() {}

        static ViewChanger* GetSingleton()
        {
            static ViewChanger singleton;
            return &singleton;
        }

    private:
    protected:
        static void                                           ActorUpdateF(RE::Actor* a_actor, float a_zPos, RE::TESObjectCELL* a_cell);
        inline static REL::Relocation<decltype(ActorUpdateF)> _ActorUpdateF;
    };

}; // namespace CameraSwitch
