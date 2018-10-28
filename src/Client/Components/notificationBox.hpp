#pragma once

#include <Client/GUI/visual.hpp>
#include <Shared/Components/notificationText.hpp>

namespace OpenGMP
{
    class NotificationBox : public NotificationText
    {
    public:
        NotificationBox();

        void Create();
        void Update(unsigned long long now);
        void Show();
        void Hide();

        bool shown;
        bool inited;
        GUI::Visual *vis;
        GUI::ViewPoint pos;
        unsigned long long startTimeMS;
        unsigned long long durationMS;
    };
}