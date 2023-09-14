#include "SFSE/Stub.h"
#include "sfse_common/Relocation.h"
#include "sfse_common/SafeWrite.h"
#include "Settings.h"

Settings settings;
std::atomic<bool> shouldTerminateThread = false;
std::atomic<bool> isThreadRunning = false;
std::thread fovThread;

static std::atomic<float> g_weaponFOV(100.0f);
const RelocAddr<uintptr_t*> WeaponFOV_Offset = 0x79FE208;

void SetWeaponFOV(float fovValue) {
    safeWriteBuf(WeaponFOV_Offset.getUIntPtr(), &fovValue, sizeof(float));
}

void WeaponFOVMonitor() {
    while (!shouldTerminateThread) {
        float currentFOV = *reinterpret_cast<float*>(WeaponFOV_Offset.getUIntPtr());
        if (currentFOV != g_weaponFOV.load()) {
            SetWeaponFOV(g_weaponFOV.load());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

namespace
{
	void MessageCallback(SFSE::MessagingInterface::Message* a_msg) noexcept
	{
		switch (a_msg->type) {
		case SFSE::MessagingInterface::kPostLoad:
			{
				settings.LoadSettings();
				g_weaponFOV.store(settings.weaponFOV);
				if (!isThreadRunning.load()) {
                	isThreadRunning.store(true);
                	fovThread = std::thread(WeaponFOVMonitor);
                	fovThread.detach();
            	}            
				break;
			}
		default:
			break;
		}
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
	data.CompatibleVersions({ RUNTIME_VERSION_1_7_23, RUNTIME_VERSION_1_7_29 });

	return data;
}();

DLLEXPORT bool SFSEAPI SFSEPlugin_Load(SFSEInterface* a_sfse)
{
    SFSE::Init(a_sfse);
    DKUtil::Logger::Init(Plugin::NAME, std::to_string(Plugin::Version));
    INFO("{} v{} loaded", Plugin::NAME, Plugin::Version);
    SFSE::GetMessagingInterface()->RegisterListener(MessageCallback);
    return true;
}
