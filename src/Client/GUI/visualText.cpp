#include "visualText.hpp"
#include "visual.hpp"
#include "../Gothic/Classes/zCViewText.hpp"

using namespace OpenGMP::GUI;

VisualText::VisualText(const std::string &text, int x, int y, Visual *parent, bool virtuals)
{
    this->parent = parent;
    
    if (virtuals)
    {
        position.x = x;
        position.y = y;
    }
    else
    {
        position = Visual::PixelToVirtual(x, y);
    }
    ViewPoint parentSize = parent->GetSize();
    position.x = position.x * 0x2000 / parentSize.x;
    position.y = position.y * 0x2000 / parentSize.y;
    parent->GetZView()->CreateText(position.x, position.y, text);
    centeredX = false;
    centeredY = false;
    format = TextFormat::Left;
    shown = true;
}

Visual *VisualText::Create(const std::string &text, int x, int y)
{
    return Create(text, x, y, false);
}

Visual *VisualText::Create(const std::string &text, int x, int y, bool virtuals)
{
    Visual *newVisual = new Visual();
    newVisual->CreateText(text, x, y, virtuals);
    return newVisual;
}

void VisualText::Show()
{
    if (!shown)
    {
        zViewText->Text(text);
        shown = true;
    }
}

void VisualText::Hide()
{
    if (shown)
    {
        zViewText->Text("");
        shown = false;
    }
}

zCOLOR VisualText::GetColor()
{
    return zViewText->GetColor();
}

void VisualText::SetColor(const zCOLOR &color)
{
    zViewText->SetColor(color);
}

void VisualText::SetPosX(int val, bool virtuals)
{
    position.x = virtuals ? val : PixelToVirtualX(val) * 0x2000 / parent->GetSize().x;
    zViewText->SetPosX(position.x);
}

void VisualText::SetPosY(int val, bool virtuals)
{
    position.y = virtuals ? val : PixelToVirtualY(val) * 0x2000 / parent->GetSize().y;
    zViewText->SetPosY(position.y);
}

bool VisualText::GetCenteredX()
{
    return centeredX;
}

void VisualText::SetCenteredX(bool value)
{
    centeredX = value;
    AlignText();
}

bool VisualText::GetCenteredY()
{
    return centeredY;
}

void VisualText::SetCenteredY(bool value)
{
    centeredY = value;
    AlignText();
}

ViewPoint VisualText::GetPosition()
{
    return position;
}

View::Fonts VisualText::GetFont()
{
    return font;
}

void VisualText::SetFont(View::Fonts font)
{
    if (font == this->font)
        return;

    this->font = font;
    auto it = fontDict.find(font);
    if (it != fontDict.end())
        zViewText->SetFont(it->second);
}

TextFormat VisualText::GetFormat()
{
    return format;
}

void VisualText::SetFormat(TextFormat value)
{
    format = value;
    AlignText();
}

const std::string & VisualText::GetText()
{
    return text;
}

void VisualText::SetText(const std::string &text)
{
    this->text = text;
    zViewText->Text(this->text);
    AlignText();
}

zCViewText *VisualText::GetZViewText()
{
    return zViewText;
}

void VisualText::AlignText()
{
    if (centeredX || centeredY)
    {
        if (centeredX)
        {
            position.x = (0x2000 - parent->GetZView()->FontSize(zViewText->Text())) / 2;
            zViewText->SetPosX(position.x);
        }
        if (centeredY)
        {
            position.y = (0x2000 - parent->GetZView()->FontY()) / 2;
            zViewText->SetPosY(position.y);
        }
    }
    else
    {
        if (format == TextFormat::Center)
            zViewText->SetPosX(position.x - parent->GetZView()->FontSize(zViewText->Text()) / 2);
        else if (format == TextFormat::Right)
            zViewText->SetPosX(position.x - parent->GetZView()->FontSize(zViewText->Text()));
        else //Left
            zViewText->SetPosX(position.x);
    }
}
