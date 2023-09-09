#include "SFSE/Stub.h"
#include "RE.h"
#include "Settings.h"
#include "sfse_common/Relocation.h"
#include "sfse_common/SafeWrite.h"

std::atomic<bool> shouldTerminateThread = false;
std::atomic<bool> isThreadRunning = false;
std::thread fovThread;

static std::atomic<float> g_weaponFOV(110.0f); 
const RelocAddr<uintptr_t*> WeaponFOV_Offset = 0x79FD448;

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

namespace Handler
{
    struct WeaponDraw
    {
        static bool thunk(RE::Actor* a_actor)
        {
            const auto result = func(a_actor);            
            if (!isThreadRunning.load()) {
                isThreadRunning.store(true);
                fovThread = std::thread(WeaponFOVMonitor);
                fovThread.detach();
            }            
            return result;
        }
        static inline std::add_pointer_t<decltype(thunk)> func;
    };

    struct WeaponSheathe
    {
        static bool thunk(RE::Actor* a_actor)
        {
            const auto result = func(a_actor);
            isThreadRunning.store(false);
            if (fovThread.joinable()) {
                fovThread.join();
            }
            return result;
        }
        static inline std::add_pointer_t<decltype(thunk)> func;
    };

    void Install()
    {
        SFSE::AllocTrampoline(28);
        stl::write_thunk_call<WeaponDraw>(0x025F726C);
        stl::write_thunk_call<WeaponSheathe>(0x025F73A3);
        INFO("Hooked WeaponDraw and WeaponSheathe");
    }
}

namespace
{
    void MessageCallback(SFSE::MessagingInterface::Message* a_msg) noexcept
    {
        if (a_msg->type == SFSE::MessagingInterface::kPostLoad) {
            Handler::Install();
            Settings::GetSingleton()->LoadSettings();
            g_weaponFOV.store(Settings::GetSingleton()->weaponFOV);
        }
    }
}

DLLEXPORT constinit auto SFSEPlugin_Version = []() noexcept {
    SFSE::PluginVersionData data{};
    data.PluginVersion(Plugin::Version);
    data.PluginName(Plugin::NAME);
    data.AuthorName(Plugin::AUTHOR);
    data.UsesSigScanning(true);
    data.HasNoStructUse(true);
    data.CompatibleVersions({ RUNTIME_VERSION_1_7_23 });

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
