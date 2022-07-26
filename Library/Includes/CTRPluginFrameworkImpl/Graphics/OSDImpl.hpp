#ifndef CTRPLUGINFRAMEWORKIMPL_OSDIMPL_HPP
#define CTRPLUGINFRAMEWORKIMPL_OSDIMPL_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Graphics/FloatingButton.hpp"

namespace CTRPluginFramework {
    using OSDReturn = int(*)(u32, int, void*, void*, int, int, int);

    class OSDImpl {
        struct  OSDMessage {
            string text;
            int width;
            bool drawn;
            Color foreground;
            Color background;
            Clock time;
            OSDMessage(const string &str, const Color &fg, const Color &bg);
        };

        using OSDIter = vector<OSDMessage*>::iterator;

        struct DrawNotifArgs {
            OSDIter begin;
            OSDIter end;
            int posY;
        };

        public:
            static void Update(void);
            static bool Draw(void);
            static s32 DrawNotif_TaskFunc(void *arg);

            static void Lock(void);
            static bool TryLock(void);
            static void Unlock(void);

            static bool DrawSaveIcon;
            static bool MessColors;
            static u32 WaitingForScreenshot;
            static u32 FramesToPlay;
            static bool NeedToPauseFrame;
            static bool WritesToPrevFB;

            static Hook OSDHook;
            static RecursiveLock ReClock;
            static FloatingButton FloatingBtn;
            static Screen TopScreen;
            static Screen BottomScreen;
            static vector<OSDMessage*> Notifications;
            static vector<OSDCallback> Callbacks;
            static vector<OSDCallback> CallbacksTrashBin;
            static void *previousFBAddr[2][2][2];

            static bool IsFramePaused;
            static LightEvent OnNewFrameEvent;
            static LightEvent OnFramePaused;
            static LightEvent OnFrameResume;
            static Task DrawNotifTask1;
            static Task DrawNotifTask2;

            static u32 MainCallback(u32 isBottom, int arg2, void *leftFb, void *rightFb, int stride, int format, int arg7);
            static u32 MainCallback2(u32 r0, u32 *params, u32 isBottom, u32 arg);
            static Result OnTopScreenFrame();
            static Result OnBottomScreenFrame();
            static void CallbackCommon(u32 isBottom, void *leftFb, void *rightFb, int stride, int format, int swap);
            static void UpdateScreens(void);

            static int PauseFrame(void);
            static void WaitFramePaused(void);
            static void ResumeFrame(const u32 nbFrames = 0);

        private:
            friend class PluginMenu;
            friend class OSD;
            friend void KeepThreadMain(void *arg);
            static void _Initialize(void);
    };
}

#endif