#ifndef CTRPLUGINFRAMEWORKIMPL_ACTIONREPLAY_ARCODE_HPP
#define CTRPLUGINFRAMEWORKIMPL_ACTIONREPLAY_ARCODE_HPP

#include <Headers.h>

namespace CTRPluginFramework {
    namespace ActionReplayPriv {
        u32 Str2U32(const string &str, bool &error);
    }

    class File;
    class MenuItem;
    class MenuFolderImpl;
    class LineWriter;

    class ARCode {
        public:
            bool HasError;
            u8 Type;
            u32 Left;
            u32 Right;
            vector<u32> Data;
            string Text;

            ARCode(const ARCode &code);
            ARCode(u8 type, u32 left, u32 right);
            ARCode(const string &line, bool &error);
            string ToString(void) const;

            bool IsCodeWithData(void) const;
            bool Update(const string &line);
            bool Update(void);
    };

    using ARCodeVector = vector<ARCode>;
    using HookVector = vector<Hook>;

    struct ARCodeContext {
        ARCodeContext();
        bool hasError;
        u32 storage[2];
        ARCodeVector codes;
        HookVector *hooks;
        bool Update(void);
        void Clear(void);
    };

    extern const vector<u8> g_codeTypes;

    void ActionReplay_OpenCheatsFile(File &output, bool create);

    /**
     * \brief Check if the code type is supported by this handler
     * \param left Left code value
     * \return True if the code type is valid
     */
    bool ActionReplay_CheckCodeTypeValidity(u32 left);

    /**
     * \brief Check if the line has a valid code pattern (hex) 00000000 00000000
     * \param line The line to check
     * \return True if the line has correct hex values
     */
    bool ActionReplay_IsHexCode(const string &line);

    /**
    * \brief Check if the line passed is a valid code
    * \param line The string to check
    * \return True if the line is a valid code
    */
    bool ActionReplay_IsValidCode(const string &line);

    void ActionReplay_ProcessString(string &str, bool canNewLine = true);
    void ActionReplay_LoadCodes(MenuFolderImpl *dst);
    bool ActionReplay_WriteToFile(LineWriter &file, MenuItem *item);
}

#endif