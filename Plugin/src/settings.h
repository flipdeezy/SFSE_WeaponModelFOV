#pragma once

class Settings : public ISingleton<Settings>
{
public:
	void LoadSettings();
	float weaponFOV{ 120.0f };
};