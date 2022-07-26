#ifndef CTRPLUGINFRAMEWORKIMPL_MENUENTRYIMPL_HPP
#define CTRPLUGINFRAMEWORKIMPL_MENUENTRYIMPL_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Menu/MenuItem.hpp"

namespace CTRPluginFramework {
    class MenuEntryImpl;

    using FuncPointer = void (*)(MenuEntry*);

    class MenuEntryImpl : public MenuItem {
        struct EntryImplFlags {
            bool state : 1;
            bool justChanged : 1;
            bool isRadio : 1;
            bool isUnselectable: 1;
        };

        public:
            MenuEntryImpl(const string &name, const string &note = "", MenuEntry *owner = nullptr);
            MenuEntryImpl(const string &name, FuncPointer func, const string &note = "", MenuEntry *owner = nullptr);
            virtual ~MenuEntryImpl();

            virtual void Enable(void);
            virtual void Disable(void);
            void SetRadio(int id);
            void SetArg(void *arg);
            void *GetArg(void) const;
            bool WasJustActivated(void) const;
            bool IsActivated(void) const;
            MenuEntry *AsMenuEntry(void) const;

            FuncPointer GameFunc;
            FuncPointer MenuFunc;

            virtual string &GetNote(void) override;
            string Note2;
            EntryImplFlags _flags;

        protected:
            friend class PluginMenuHome;
            friend class PluginMenuExecuteLoop;
            friend class MenuEntry;

            bool _TriggerState(void);
            bool _MustBeRemoved(void) const;
            bool _Execute(void);
            int _executeIndex;
            MenuEntry *_owner;

            int _radioId;
            void *_arg;
    };
}

#endif