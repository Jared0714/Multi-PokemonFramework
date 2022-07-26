#ifndef CTRPLUGINFRAMEWORK_SCREENIMPL_HPP
#define CTRPLUGINFRAMEWORK_SCREENIMPL_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Graphics/BMPImage.hpp"
#include "CTRPluginFrameworkImpl/System/Services/Gsp.hpp"

namespace CTRPluginFramework {
    using namespace CTRPluginFrameworkImpl::Services::GSP;

    enum {
        SCREENSHOT_TOP = 1,
        SCREENSHOT_BOTTOM = 2,
        SCREENSHOT_BOTH = SCREENSHOT_TOP | SCREENSHOT_BOTTOM
    };

    class Color;
    class ScreenImpl {
        public:
            enum LCDSetup {
                WidthHeight = 0x5C,
                FramebufferA1 = 0x68,
                FramebufferA2 = 0x6C,
                Format = 0x70,
                Select = 0x78,
                Stride = 0x90,
                FramebufferB1 = 0x94,
                FramebufferB2 = 0x98
            };

            static ScreenImpl *Top;
            static ScreenImpl *Bottom;

            ScreenImpl(u32 lcdSetupInfo, u32 fillColorAddress, bool isTopScreen = false);

            bool IsTopScreen(void);
            bool Is3DEnabled(void);

            void Flash(Color &color);

            static void Clean(void);
            static void SwitchFrameBuffers(bool game);
            static void ApplyFading(void);
            static u32 AcquireFromGsp(bool fade = true);
            static u32 CheckGspFrameBuffersInfo(void);

            void Fade(const float fade);
            void Flush(void);
            void Invalidate(void);

            void Clear(bool applyFlagForCurrent);
            void Copy(void);
            void Debug(void);

            u32 Acquire(bool fade = true);
            u32 ImportFromGsp(void);

            void Release(void);
            void Acquire(u32 left, u32 right, u32 stride, u32 format, bool backup = false);
            void SwapBuffer(void);
            void SwapBufferInternal(void);
            u32 GetBacklight(void);
            void SetBacklight(u32 value);

            GSPGPU_FramebufferFormat GetFormat(void) const;
            u16 GetWidth(void) const;
            u32 GetStride(void) const;
            u32 GetRowSize(void) const;
            u32 GetBytesPerPixel(void) const;
            u32 GetFrameBufferSize(void) const;
            u32 GetCurrentBufferID(void) const;

            void GetFrameBufferInfos(int &rowstride, int &bpp, GSPGPU_FramebufferFormat &format) const;

            u8 *GetLeftFrameBuffer(bool current = false);
            u8 *GetLeftFrameBuffer(int posX, int posY);
            u8 *GetRightFrameBuffer(bool current = false);
            u8 *GetRightFrameBuffer(int posX, int posY);
            void GetPosFromAddress(u32 address, int &posX, int &posY);

        private:
            friend class Renderer;
            friend void CTRPluginFrameworkImpl::Services::GSP::Update(u32 threadId, Handle eventHandle, Handle sharedMemHandle);
            friend void KeepThreadMain(void*);

            static void Initialize(void);
            static void ApplyCtrpfScreens(void);

            u32 _LCDSetup;
            u32 _FillColor;
            u32 _backlightOffset;
            u32 _currentBuffer;
            u32 _leftFrameBuffers[2];
            u32 _rightFrameBuffers[2];

            const u16 _width;
            u32 _stride;
            u32 _rowSize;
            u32 _bytesPerPixel;
            bool _isTopScreen;
            bool _isGspAcquired{false};
            GSPGPU_FramebufferFormat _format;
            FrameBufferInfoShared _frameBufferInfo{};
            FrameBufferInfoShared _gameFrameBufferInfo{};
    };
}

#endif