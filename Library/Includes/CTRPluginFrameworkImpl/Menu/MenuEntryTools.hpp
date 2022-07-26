#ifndef CTRPLUGINFRAMEWORKIMPL_MENUENTRYTOOLS_HPP
#define CTRPLUGINFRAMEWORKIMPL_MENUENTRYTOOLS_HPP

#include <Headers.h>
#include "MenuEntryImpl.hpp"

namespace CTRPluginFramework {
    class MenuEntryTools : public MenuEntryImpl {
        using IconCallback = int(*)(int, int);
        using FuncPointer = void(*)(void);
        using FuncPointerA = void(*)(MenuEntryTools*);

        public:
            explicit MenuEntryTools(const string &text, FuncPointer func, IconCallback icon, void *arg = nullptr);
            explicit MenuEntryTools(const string &text, FuncPointer func, IconCallback icon, const string &note);
            explicit MenuEntryTools(const string &text, FuncPointer func, bool useCheckBox, bool isEnabled = false, const string &note = "");
            explicit MenuEntryTools(const string &text, FuncPointerA func, bool useCheckBox, bool isEnabled = false, const string &note = "");

            ~MenuEntryTools() {}

            void Enable(void) override;
            void Disable(void) override;
            void TriggerState(void);

            IconCallback Icon;
            FuncPointer Func;
            FuncPointerA FuncArg;
            bool UseCheckBox;
    };
}

#endif