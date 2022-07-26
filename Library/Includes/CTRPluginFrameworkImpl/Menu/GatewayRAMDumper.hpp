#ifndef CTRPLUGINFRAMEWORKIMPL_GATEWAYRAMDUMPER_HPP
#define CTRPLUGINFRAMEWORKIMPL_GATEWAYRAMDUMPER_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Search/Search.hpp"

namespace CTRPluginFramework {
    class GatewayRAMDumper {
        public:
            GatewayRAMDumper(void);
            ~GatewayRAMDumper(void) {}
            bool operator()(void);
            bool _SelectRegion();

        private:
            void _OpenFile(void);
            void _WriteHeader(void);
            void _DrawProgress(void);

            string _fileName;
            File _file;
            u32 _currentAddress;
            u32 _endAddress;
            u32 _regionIndex;
            u32 _achievedSize;
            u32 _totalSize;
            vector<Region> _regions;
    };
}

#endif