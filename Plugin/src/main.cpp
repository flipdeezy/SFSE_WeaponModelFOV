#include "REL/Relocation.h"
#include "Settings.h"
#include <Windows.h>

Settings settings;

//REL::Offset WeaponFOV_Offset(0x7A01508); // old 79FE208
REL::Relocation<std::uintptr_t> WeaponFOV_Offset{ REL::ID(891272), -0x60 };

void SetWeaponFOV(float fovValue) {
    REL::safe_write(WeaponFOV_Offset.address(), &fovValue, sizeof(float));
}

struct WeaponDraw
{
	static bool thunk(std::uintptr_t a_handler, RE::Actor* a_actor, const RE::BSFixedString& a_tag)
	{
		const auto result = func(a_handler, a_actor, a_tag);
		if (a_actor->IsPlayerRef()) {
			SetWeaponFOV(settings.weaponFOV);
		}
		return result;
	}
	static inline REL::Relocation<decltype(thunk)> func;
	static inline std::uintptr_t address{REL::Relocation<std::uintptr_t>(REL::ID(155299), 0x2C).address()};
};

class hk_FOVValChange
{
    static float HookHandler()
    {
        return settings.weaponFOV;
    }

public:
	static void Install()
	{
		REL::Relocation<std::uintptr_t> funcAddr{ REL::ID(166089), 0x61 };
		//auto funcAddr = REL::Offset{ 0x286C0C1 }; // maybe better to hook inside the function? can hook the sub here 0x286C0A0 5 byte instruction
		auto handle = DKUtil::Hook::AddCaveHook(
			funcAddr.address(),
			{ 0, 8 },
			FUNC_INFO(HookHandler),
			std::make_pair(nullptr, 0),
			std::make_pair(nullptr, 0), DKUtil::Hook::HookFlag::kRestoreAfterEpilog); // do nothing if replacing whole func kNoFlag

		handle->Enable();
		stl::write_thunk_call<WeaponDraw, 5>(WeaponDraw::address);
	}
};

DLLEXPORT constinit auto SFSEPlugin_Version = []() noexcept {
	SFSE::PluginVersionData data{};
	data.PluginVersion(Plugin::Version);
	data.PluginName(Plugin::NAME);
	data.AuthorName(Plugin::AUTHOR);
	//data.UsesSigScanning(true);
	data.UsesAddressLibrary(true);
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