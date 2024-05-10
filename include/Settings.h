#pragma once

class Settings : public Singleton<Settings>
{
public:
    void LoadSettings() noexcept;

    inline static bool lock_third_person{};
    inline static bool in_combat{};
    inline static bool first_person_mode{};
    inline static bool debug_logging{};
};





