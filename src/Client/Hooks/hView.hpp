#pragma once

#include "../hook.hpp"
#include <map>

class zCView;
class zCVob;
class zCWorld;
class zCCamera;

namespace OpenGMP
{
    namespace Hooks
    {
        class HView
        {
        public:
            HView();
            static HView *GetInstance();
            void DoHook();
            void UndoHook();
                       
            static bool inited;
            static HView *instance; //Singleton instance
            Hook hookDrawItems;
            static std::map<zCView*, zCVob*> vobRenderList;
            static zCWorld *rndrWorld;
            static zCVob *camVob;
            static zCCamera *camera;

            void DrawItems();

        private:
            /**
            * @brief private copy contructor -- copy forbidden for singleton.
            */
            HView(HView &cpy);
        };
    }
}