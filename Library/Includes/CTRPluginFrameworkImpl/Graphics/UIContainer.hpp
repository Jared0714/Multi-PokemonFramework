#ifndef CTRPLUGINFRAMEWORKIMPL_UICONTAINER_HPP
#define CTRPLUGINFRAMEWORKIMPL_UICONTAINER_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Graphics/Drawable.hpp"

namespace CTRPluginFramework {
    class UIContainer {
        public:
            UIContainer(void);
            ~UIContainer(void);

            void operator += (Drawable *uiControl);
            void Draw(void);
            void Update(const bool isTouchDown, const IntVector &touchPos);
            void ExecuteAll(void);

        private:
            vector<Drawable*> _uiControls;
    };
}

#endif