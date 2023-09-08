#include "Settings.h"

void Settings::LoadSettings()
{
    constexpr auto path = L"Data/SFSE/Plugins/WeaponModelFOV.ini";

    CSimpleIniA ini;
    ini.SetUnicode();

    ini.LoadFile(path);

    const char* fovValueStr = ini.GetValue("Settings", "fWeaponFOV", "120.0");
    weaponFOV = static_cast<float>(std::atof(fovValueStr));
}