#ifndef CTRPLUGINFRAMEWORK_LINEWRITER_HPP
#define CTRPLUGINFRAMEWORK_LINEWRITER_HPP

#include <Headers.h>

namespace CTRPluginFramework {
    class File;
    class LineWriter {
        public:
            LineWriter(File &output);
            LineWriter(const LineWriter &right) = delete;
            LineWriter(LineWriter &&right) = delete;
            ~LineWriter(void);

            LineWriter &operator << (const string &input);
            LineWriter &operator = (const LineWriter &right) = delete;
            LineWriter &operator = (LineWriter &&right) = delete;

            static const string &endl(void);
            void Flush(void);
            void Close(void);

        private:
            File &_output;
            u32 _offsetInBuffer;
            u8 *_buffer;
    };
}

#endif