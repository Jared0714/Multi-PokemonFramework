#ifndef CTRPLUGINFRAMEWORKIMPL_HEXEDITOR_HPP
#define CTRPLUGINFRAMEWORKIMPL_HEXEDITOR_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Graphics.hpp"
#include "CTRPluginFrameworkImpl/System.hpp"
#include "CTRPluginFrameworkImpl/Menu/KeyboardImpl.hpp"
#include "CTRPluginFrameworkImpl/Menu/SubMenu.hpp"

namespace CTRPluginFramework {
    class HexEditor {
        using EventList = vector<Event>;

        enum {
            ByteV = 0,
            IntegerV = 1,
            AsmV = 2
        };

        enum {
            DirtySrc = 1,
            DirtyMemory = 1 << 1,
            DirtyMemoryCache = 1 << 2,
            DirtyCursor = 1 << 3,
            DirtyViewCache = 1 << 4,
            DirtyCursorAddress = 1 << 5,
            DirtyCursorPos = 1 << 6,
            DirtyCursorCache = 1 << 7,
            InvalidSrc = 1 << 8,
            UpdateView = DirtySrc | DirtyMemory
        };

        struct Item {
            u32 address;

            union {
                u32 value32;
                float valueF;
                u8 b[4];
            };

            char addrCache[9]{0};
            string valueCache;
            string dataCache;
        };

        struct Context {
            u32 _flags;
            u32 _address;
            u32 _cursorAddress;
            s16 _cursorX;
            s16 _cursorY;
            u16 _cursorPosX;
            u16 _cursorPosY;
            char _cursorAddressStr[9]{0};

            Clock _clock;
            Time _latency{Milliseconds(200)};
            vector<Item> _items;

            bool ScrollUp(u32 stride, bool updateCursor);
            bool ScrollDown(u32 stride, bool updateCursor);
        };

        struct IView {
            virtual ~IView() = default;
            virtual void Draw(void) = 0;
            virtual void ProcessEvent(Event& event) = 0;
            virtual void UpdateView(void) = 0;
            virtual void EditValueAtCursor(u32 val) = 0;

            void ProcessEventsCommon(Context& _ctx, Event& event, s16 maxX);

            u8 ItemsPerLine{0};
            u8 DigitPerLine{0};
            u8 TotalItems{0};
            u8 Stride{0};
        };

        struct ByteView : IView {
            ByteView(Context& ctx);

            void Draw(void) override;
            void ProcessEvent(Event& event) override;
            void UpdateView(void) override;
            void EditValueAtCursor(u32 val) override;

            Context &_ctx;
        };

        struct IntegerView : IView {
            IntegerView(Context &ctx);

            void Draw(void) override;
            void ProcessEvent(Event &event) override;
            void UpdateView(void) override;
            void EditValueAtCursor(u32 val) override;

            Context &_ctx;
        };

        struct FloatView : IView {
            FloatView(Context &ctx);

            void Draw(void) override;
            void ProcessEvent(Event &event) override;
            void UpdateView(void) override;
            void EditValueAtCursor(u32 val) override;

            Context &_ctx;
        };

        struct AsmView : IView {
            AsmView(Context &ctx);

            void Draw(void) override;
            void ProcessEvent(Event &event) override;
            void UpdateView(void) override;
            void EditValueAtCursor(u32 val) override;

            Context &_ctx;
        };

        public:
            HexEditor(u32 target);
            ~HexEditor();

            bool operator()(EventList &eventList);
            bool Goto(u32 address, bool updateCursor = false);
            void SetView(u32 view);
            void Refresh(void);
            u32 GetCursorAddress(void);

        private:
            void _ProcessEvent(Event &event);
            static s32 _RenderTop(void *arg);
            void _RenderBottom(void);
            void _Update(void);
            void _CreateCheat(void);
            void _MoveBackward(void);
            void _MoveForward(void);
            void _SaveThisAddress(void);
            void _BrowseHistory(void);
            void _ClearHistory(void);
            void _ApplyChanges(void);
            void _DiscardChanges(void);
            u32 _PromptForAddress(int mode);
            void _JumpTo(int mode);
            void _GotoPreviousRegion(void);
            void _GotoNextRegion(void);
            Item &_GetSelectedItem(void);

            u32 _viewId{0};
            IView *_viewCurrent;
            IView *_views[4]{nullptr};
            Context _ctx;
            SubMenu _submenu;
            KeyboardImpl _keyboard;
            Task _renderTask;
            int _indexHistory;
            vector<u32> _history{};
    };
}

#endif