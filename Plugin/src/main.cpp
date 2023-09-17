#include "REL/Relocation.h"
#include "Settings.h"
#include <Windows.h>

Settings settings;
REL::Offset WeaponFOV_Offset(0x79FE208);

void SetWeaponFOV(float fovValue) {
    REL::safe_write(WeaponFOV_Offset.address(), &fovValue, sizeof(float));
}

class hk_FOVValChange
{
    static float HookHandler()
    {
        return settings.weaponFOV;
    }

public:
	static void Install()
	{
		auto funcAddr = REL::Offset{ 0x286C0C1 }; // maybe better to hook inside the function? can hook the sub here 0x286C0A0 5 byte instruction
		auto handle = DKUtil::Hook::AddCaveHook(
			funcAddr.address(),
			{ 0, 8 },
			FUNC_INFO(HookHandler),
			std::make_pair(nullptr, 0),
			std::make_pair(nullptr, 0), DKUtil::Hook::HookFlag::kRestoreAfterEpilog); // do nothing if replacing whole func kNoFlag

		handle->Enable();
	}
};

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
		case SFSE::MessagingInterface::kPostPostLoad:
			{
				settings.LoadSettings();
				hk_FOVValChange::Install();
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