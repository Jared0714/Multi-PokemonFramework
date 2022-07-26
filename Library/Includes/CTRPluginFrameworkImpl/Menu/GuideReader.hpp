#ifndef CTRPLUGINFRAMEWORKIMPL_GUIDEREADER_HPP
#define CTRPLUGINFRAMEWORKIMPL_GUIDEREADER_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Graphics.hpp"
#include "CTRPluginFrameworkImpl/Menu/Menu.hpp"
#include "CTRPluginFrameworkImpl/Menu/MenuEntryImpl.hpp"
#include "CTRPluginFrameworkImpl/Menu/MenuFolderImpl.hpp"
#include "CTRPluginFrameworkImpl/Menu/MenuItem.hpp"
#include "CTRPluginFrameworkImpl/System/Events.hpp"

namespace CTRPluginFramework {
    class GuideReader {
        using EventList = vector<Event>;

        public:
            GuideReader(void);
            ~GuideReader(void){};

            bool Draw(void);
            void Open(void);
            void Close(void);
            bool IsOpen(void);

            // Return true if the Close Button is pressed, else false
            bool operator()(EventList &eventList, Time &delta);

        private:
            bool _ProcessEvent(Event &event);
            void _LoadBMP(void);

            bool _isOpen;
            Menu _menu;
            TextBox _guideTB;
            string _text;
            MenuEntryImpl *_last;
            Directory _currentDirectory;
            vector<string> _bmpList;
            int _currentBMP;
            BMPImage *_image;
    };
}

#endif