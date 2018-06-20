#include "view.hpp"
#include "../Gothic/Classes/zCView.hpp"
#include "../Gothic/Classes/zCOption.hpp"
#include "../Gothic/Classes/zCOptionSection.hpp"
#include "../Gothic/Classes/zCOptionEntry.hpp"

using namespace OpenGMP::GUI;

const std::map<View::Fonts, std::string> View::fontDict =
    {   { Default, "Font_Old_10_White.tga" },
        { Default_Hi, "Font_Old_10_White_Hi.tga" },
        { Menu, "Font_Old_20_White.tga" },
        { Menu_Hi, "Font_Old_20_White_Hi.tga" }
    };

ViewPoint View::GetScreenSize()
{
    zCView *screen = zCView::GetScreen();
    ViewPoint screenSize;

    screen->GetSize(screenSize.x, screenSize.y);

    if (screenSize.x <= 0 || screenSize.y <= 0) //Invalid screen size ?
    {
        //Try read screen size via ini.
        zCOption *options = zCOption::GetZOptions();
        zCOptionSection *section = options->GetSectionByName("VIDEO", 1);
        screenSize.x = options->GetEntryByName(section, "zVidResFullscreenX", 1)->GetVarValue()->ToInt();
        screenSize.y = options->GetEntryByName(section, "zVidResFullscreenY", 1)->GetVarValue()->ToInt();
    }

    return screenSize;
}

ViewPoint View::PixelToVirtual(int x, int y)
{
    ViewPoint screenSize = GetScreenSize();
    ViewPoint virtualSize;

    virtualSize.x = x * 0x2000 / screenSize.x;
    virtualSize.y = y * 0x2000 / screenSize.y;

    return virtualSize;
}

ViewPoint View::PixelToVirtual(ViewPoint point)
{
    return PixelToVirtual(point.x, point.y);
}

int View::PixelToVirtualX(int x)
{
    ViewPoint screenSize = GetScreenSize();
    int virtualX;

    virtualX = x * 0x2000 / screenSize.x;

    return virtualX;
}

int View::PixelToVirtualY(int y)
{
    ViewPoint screenSize = GetScreenSize();
    int virtualY;

    virtualY = y * 0x2000 / screenSize.y;

    return virtualY;
}
