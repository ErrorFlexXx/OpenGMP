#pragma once

#include "view.hpp"
#include <string>
#include <functional>

namespace OpenGMP
{
    namespace GUI
    {
        class MenuItem : public View
        {
        public:
            virtual void Select() = 0;
            virtual void Deselect() = 0;
            virtual bool Enabled();
            virtual void Enabled(bool value);

            std::string helpText;
            std::function<void()> onAction;

        protected:
            bool enabled;
        };
    }
}