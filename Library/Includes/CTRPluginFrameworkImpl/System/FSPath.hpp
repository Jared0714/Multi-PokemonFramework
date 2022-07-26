#ifndef CTRPLUGINFRAMEWORKIMPL_FSPATH_HPP
#define CTRPLUGINFRAMEWORKIMPL_FSPATH_HPP

#include <Headers.h>

namespace CTRPluginFramework {
    #define PATH_LENGTH_MAX 256

    struct FSPath {
        FSPath(string path);
        int Error{0};
        s32 Units{0};
        vector<u16> Utf16Path;


        operator FS_Path() {
            FS_Path fspath;

            if (Error == 0) {
                fspath.type = PATH_UTF16;
                fspath.size = (Units + 1) * sizeof(u16);
                fspath.data = (const u8*)Utf16Path.data();
                return fspath;
            }

            fspath.type = PATH_EMPTY;
            fspath.size = 0;
            fspath.data = nullptr;
            return fspath;
        }

        static int SdmcFixPath(string &path);
        static Mutex FSMutex;
        static string CurrentWorkingDirectory;
    };
}

#endif