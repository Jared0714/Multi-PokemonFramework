#ifndef CTRPLUGINFRAMEWORKIMPL_COMBOBOX_HPP
#define CTRPLUGINFRAMEWORKIMPL_COMBOBOX_HPP

#include <Headers.h>
#include "CTRPluginFrameworkImpl/Graphics/Drawable.hpp"

namespace CTRPluginFramework {
    class ComboBox : public Drawable {
        public:
            ComboBox(int posX, int posY, int width, int height);
            void Add(const string &item);
            void Clear(void);
            void Draw(void) override;
            void Update(const bool isTouchDown, const IntVector &touchPos) override;
            bool operator()(void) override;

            bool IsEnabled;
            bool IsVisible;
            int SelectedItem;

        private:
            bool _execute;
            bool _isTouched;
            IntRect _rectPos;
            vector<string> _items;
    };
}

#endif