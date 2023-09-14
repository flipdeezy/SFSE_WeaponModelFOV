<<<<<<< HEAD
#include <Windows.h>
#include <string>

class Settings
{
public:
    void LoadSettings();
    float weaponFOV{ 110.0f };
};

void Settings::LoadSettings()
{
    const wchar_t* path = L"Data/SFSE/Plugins/WeaponModelFOV.ini";
    wchar_t buffer[256];
    
    GetPrivateProfileStringW(L"Settings", L"fWeaponFOV", L"110.0", buffer, sizeof(buffer) / sizeof(wchar_t), path);
    
    weaponFOV = static_cast<float>(_wtof(buffer));
}
=======
#pragma once

class Settings : public ISingleton<Settings>
{
public:
	void LoadSettings();
	float weaponFOV{ 120.0f };
};
>>>>>>> 11ad18d6b375ff01709996cfabff128af874a1fc
