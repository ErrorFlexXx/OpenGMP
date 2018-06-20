#include "menuItem.hpp"

using namespace OpenGMP::GUI;

bool MenuItem::Enabled()
{
    return enabled;
}

void MenuItem::Enabled(bool value)
{
    enabled = value;
}