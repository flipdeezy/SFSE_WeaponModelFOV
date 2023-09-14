#include "REL/Relocation.h"
#include "Settings.h"
#include <Windows.h>

std::atomic<bool> shouldTerminateThread = false;
std::atomic<bool> isThreadRunning = false;
std::thread fovThread;

Settings settings;
static std::atomic<float> g_weaponFOV(120.0f);
REL::Relocation<uintptr_t> WeaponFOV_Offset = 0x79FE208;

void SetWeaponFOV(float fovValue) {
    REL::safe_write(WeaponFOV_Offset.address(), &fovValue, sizeof(float));
}

void WeaponFOVMonitor() {
    while (!shouldTerminateThread) {
        float currentFOV = *reinterpret_cast<float*>(WeaponFOV_Offset.address());
        //if (currentFOV != settings.weaponFOV) {
            SetWeaponFOV(g_weaponFOV);
        //}
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

DLLEXPORT constinit auto SFSEPlugin_Version = []() noexcept {
	SFSE::PluginVersionData data{};
	data.PluginVersion(Plugin::Version);
	data.PluginName(Plugin::NAME);
	data.AuthorName(Plugin::AUTHOR);
	data.UsesSigScanning(true);
	//data.UsesAddressLibrary(true);
	data.HasNoStructUse(true);
	//data.IsLayoutDependent(true);
	data.CompatibleVersions({ SFSE::RUNTIME_LATEST });
	return data;
}();

namespace
{
	void MessageCallback(SFSE::MessagingInterface::Message* a_msg) noexcept
	{
		switch (a_msg->type) {
		case SFSE::MessagingInterface::kPostLoad:
			{
				settings.LoadSettings();
				if (!fovThread.joinable()) {
                	SetWeaponFOV(g_weaponFOV);
					//fovThread = std::thread(WeaponFOVMonitor);
                }
				break;
			}
		default:
			break;
		}
	}
}

DLLEXPORT bool SFSEAPI SFSEPlugin_Load(const SFSE::LoadInterface* a_sfse)
{
	SFSE::Init(a_sfse);
	DKUtil::Logger::Init(Plugin::NAME, std::to_string(Plugin::Version));
	INFO("{} v{} loaded", Plugin::NAME, Plugin::Version);
	SFSE::AllocTrampoline(1 << 10);
	SFSE::GetMessagingInterface()->RegisterListener(MessageCallback);   
	return true;
}
