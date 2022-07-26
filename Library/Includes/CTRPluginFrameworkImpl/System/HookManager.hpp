#ifndef CTRPLUGINFRAMEWORKIMPL_SYSTEM_HOOKMANAGER_HPP
#define CTRPLUGINFRAMEWORKIMPL_SYSTEM_HOOKMANAGER_HPP

#include <Headers.h>

namespace CTRPluginFramework {
    #define MAX_HOOKS (0x1000 / sizeof(HookWrapper))

    struct HookWrapper {
        u32 jumpCode{0};
        u32 callback{0};
        HookContext *ctx{nullptr};
    };

    struct AsmWrapper {
        HookContext *ctx{nullptr};
        u32 code[15]{0};
    };

    struct HookManager {
        HookManager(void);

        static Mutex &GetLock(void) {
            return _singleton._mutex;
        }

        static HookResult ApplyHook(HookContext &ctx);
        static HookResult DisableHook(HookContext &ctx);

        AsmWrapper &GetFreeAsmWrapper(void);
        HookWrapper &GetFreeHookWrapper(s32 &index);
        AsmWrapper &GetAsmWrapper(HookContext *ctx);

        static void Lock();
        static void Unlock();

        static void PrepareToUnmapMemory();
        static void RecoverFromUnmapMemory();

        Mutex _mutex{};
        HookWrapper *_hookWrappers{reinterpret_cast<HookWrapper*>(0x1E80000)};
        vector<AsmWrapper> _asmWrappers{};
        static HookManager _singleton;
    };
}

#endif