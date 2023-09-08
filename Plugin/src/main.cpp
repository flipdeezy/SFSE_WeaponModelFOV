#include "SFSE/Stub.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <thread>
#include "RE.h"
#include "Settings.h"

static std::atomic<float> g_weaponFOV(110.0f); 
std::atomic<bool> shouldTerminateThread = false;
std::atomic<bool> isThreadRunning = false;
std::thread fovThread;

uintptr_t GetModuleBaseAddress(const wchar_t* moduleName) {
    DWORD procID = GetCurrentProcessId();
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);
    
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32W modEntry = {};
        modEntry.dwSize = sizeof(modEntry);
        
        if (Module32FirstW(hSnap, &modEntry)) {
            do {
                if (_wcsicmp(modEntry.szModule, moduleName) == 0) {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32NextW(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

const uintptr_t WeaponFOV_Offset = 0x79FD448;

void SetWeaponFOV(float fovValue) {
    uintptr_t starfieldBase = GetModuleBaseAddress(L"Starfield.exe");
    if (starfieldBase == 0) {
        ERROR("Failed to get Starfield.exe base address");
        return;
    }
    
    float* weaponFOVAddress = reinterpret_cast<float*>(starfieldBase + WeaponFOV_Offset);
    if (!weaponFOVAddress) {
        ERROR("Invalid Weapon FOV address");
        return;
    }

    HANDLE hProcess = GetCurrentProcess();
    if (!WriteProcessMemory(hProcess, weaponFOVAddress, &fovValue, sizeof(float), nullptr)) {
        ERROR("Failed to write to Weapon FOV address");
    }
}

// Temporary solution until I can find a better way to hook the FOV weapon model or a proper game update
void WeaponFOVMonitor() {
    while (!shouldTerminateThread) {
        float currentFOV = *reinterpret_cast<float*>(GetModuleBaseAddress(L"Starfield.exe") + WeaponFOV_Offset);
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
            SetWeaponFOV(g_weaponFOV.load());
            
            // Start the thread if it's not already running
            if (!isThreadRunning) {
                shouldTerminateThread = false;
                fovThread = std::thread(WeaponFOVMonitor);
                fovThread.detach();
                isThreadRunning = true;
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
            SetWeaponFOV(g_weaponFOV.load());

            // Stop the thread
            shouldTerminateThread = true;
            isThreadRunning = false;
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
            uintptr_t starfieldBase = GetModuleBaseAddress(L"Starfield.exe");
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
