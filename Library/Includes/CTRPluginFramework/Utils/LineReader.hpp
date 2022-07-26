#ifndef CTRPLUGINFRAMEWORK_UTILS_LINEREADER_HPP
#define CTRPLUGINFRAMEWORK_UTILS_LINEREADER_HPP

#include <Headers.h>

namespace CTRPluginFramework {
    class File;
    class LineReader {
        public:
            LineReader(File &file);
            ~LineReader(void);

            bool operator()(string &line);

        private:
            File &_file;
            u32 _offsetInBuffer;
            u32 _dataInBuffer;
            char *_buffer;
    };

    class StringLineReader {
        public:
            StringLineReader(const string &str);
            bool operator()(string &line);

        private:
            const string &_strin;
            u32 _offset;
    };
}

#endif