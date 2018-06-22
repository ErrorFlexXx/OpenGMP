#pragma once

#include "visual.hpp"
#include <string>

class zCVob;

namespace OpenGMP
{
    namespace GUI
    {
        class Visual3D : public Visual
        {
        public:
            Visual3D(int x, int y, int w, int h);
            Visual3D(int x, int y, int w, int h, bool virtuals);

            virtual void Show() override;
            virtual void Hide() override;

            void SetVob(zCVob *vob);
            void SetVisual(std::string &name);
        
        private:
            zCVob *vob;
        };
    }
}