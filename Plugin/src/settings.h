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