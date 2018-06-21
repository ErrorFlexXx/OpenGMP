#include "textBox.hpp"
#include "visualText.hpp"
#include <Shared/gameTime.hpp>
#include "../Core/inputHandler.hpp"
#include "../Core/Enumeration/virtualKeys.hpp"

using namespace OpenGMP;
using namespace OpenGMP::GUI;

const size_t TextBox::cursorSize = 16;
const size_t TextBox::cursorOffsetX = 1 - TextBox::cursorSize / 2;
const size_t TextBox::cursorOffsetY = 1;
const size_t TextBox::arrowSize = 10;

TextBox::TextBox(int x, int y, int w, bool fixedBorders)
    : width(w)
    , height(fontSizeDefault)
    , inputVis(x, y, w, height)
    , cursorVis(x + cursorOffsetX, y + cursorOffsetY, cursorSize, cursorSize)
    , leftArrow(x, y + (height - arrowSize) / 2, arrowSize, arrowSize)
    , rightArrow(x + w - arrowSize, y + (height - arrowSize) / 2, arrowSize, arrowSize)
{
    characterLimit = 512;
    allowSpaces = true;
    allowSymbols = true;
    onlyNumbers = false;
    hideChars = 0;
    cursorPos = 0;
    leftArrowShown = false;
    rightArrowShown = false;
    enabled = false;
    pos.x = x;
    pos.y = y;

    this->fixedBorders = fixedBorders;
    inputVis.CreateText("", 0, 0);
    cursorVis.SetBackTexture("CURSOR.TGA");
    leftArrow.SetBackTexture("L.TGA");
    rightArrow.SetBackTexture("R.TGA");
}

void TextBox::Show()
{
    inputVis.Show();
    if (enabled)
        cursorVis.Show();
    if (leftArrowShown)
        leftArrow.Show();
    if (rightArrowShown)
        rightArrow.Show();
}

void TextBox::Hide()
{
    inputVis.Hide();
    cursorVis.Hide();
    leftArrow.Hide();
    rightArrow.Hide();
}

VisualText *TextBox::InputText()
{
    return inputVis.Texts().front();
}

void TextBox::Update(long now)
{
    if (!enabled)
        return;

    if (now > cursorTime)
    {
        if (cursorVis.Shown())
            cursorVis.Hide();
        else
            cursorVis.Show();
        cursorTime = now + 300 * TICKS_PER_MILLISECOND;
    }
}

void TextBox::KeyPressed(VirtualKeys key)
{
    if (!enabled)
        return;

    if (key == VirtualKeys::Back) //Backspace, delete char behind the cursor
    {
        if (0 < cursorPos) //If there is a char, that can be deleted
        {
            input.erase(cursorPos - 1, 1);
            cursorPos--;
        }
    }
    else if (key == VirtualKeys::Delete)
    {
        if (cursorPos < input.length())
            input.erase(cursorPos, 1);
    }
    else if (key == VirtualKeys::Left)
    {
        if (0 < cursorPos)
            cursorPos--;
    }
    else if (key == VirtualKeys::Right)
    {
        if (cursorPos < input.length())
            cursorPos++;
    }
    else
    {
        if (characterLimit < input.length())
            return;

        char c = GetCharFromKey(key);
        if (c == 0)
            return;
        if (!View::GothicContainsChar(c))
            return;
        if (onlyNumbers && !isdigit(c))
            return;
        if (!allowSpaces && isspace(c))
            return;
        if (!allowSymbols && (!isdigit(c) && !isalpha(c))) //No alphabetic, nor digit ? -> symbol assumed...
            return;
        if (fixedBorders && StringPixelWidth(input) + View::OGMPGetCharWidth(c) > width)
            return;

        input.insert(input.begin() + cursorPos, c);
        cursorPos++;
    }
    cursorVis.Show();
    UpdateInputVisual();
}

bool TextBox::Enabled()
{
    return enabled;
}

void TextBox::Enabled(bool value)
{
    enabled = value;
    if (value)
        cursorVis.Show();
    else
        cursorVis.Hide();
}

std::string TextBox::Input()
{
    return input;
}

void TextBox::Input(const std::string &value)
{
    input.clear();
    input.append(value);
    cursorPos = 0;
    UpdateInputVisual();
}

void TextBox::UpdateInputVisual()
{
    size_t sub = 0;
    if (cursorPos >= hideChars)
        sub = hideChars;

    std::string substractedText = input.substr(sub);
    InputText()->SetText(substractedText);
    int cursorLen = (int)StringPixelWidth(substractedText.substr(0, cursorPos - sub));
    int inputLen = (int)StringPixelWidth(substractedText);

    if (fixedBorders)
        cursorVis.SetPosX(pos.x + cursorOffsetX + cursorLen - sub);
    else
    {
        bool changed = false;
        if (cursorLen + startPos > width)
            startPos = width - cursorLen;
        else if (cursorLen + startPos < 0)
            startPos = -cursorLen;
        else if (leftArrowShown && inputLen + startPos < width)
            startPos = width - inputLen;

        InputText()->SetPosX(startPos);
        cursorVis.SetPosX(pos.x + cursorOffsetX + cursorLen + startPos);

        if (startPos < 0)
        {
            if (!leftArrowShown)
            {
                leftArrow.Show();
                width -= 10; pos.x += 10;
                leftArrowShown = true;
                changed = true;
            }
        }
        else
        {
            if (leftArrowShown)
            {
                leftArrow.Hide();
                width += 10; pos.x -= 10;
                leftArrowShown = false;
                changed = true;
            }
        }

        if (inputLen + startPos > width)
        {
            if (!rightArrowShown)
            {
                rightArrow.Show();
                width -= 10;
                rightArrowShown = true;
                changed = true;
            }
        }
        else
        {
            if (rightArrowShown)
            {
                rightArrow.Hide();
                width += 10;
                rightArrowShown = false;
                changed = true;
            }
        }

        if (changed)
        {
            inputVis.SetPosX(pos.x);
            inputVis.SetWidth(width);
            UpdateInputVisual();
        }
    }
}

char TextBox::GetCharFromKey(VirtualKeys key)
{
    wchar_t buffer[10] = {};
    BYTE keyState[256] = {};
    
    if (InputHandler::IsPressed(VirtualKeys::Shift))
        keyState[VirtualKeys::Shift] = 0xff;
    if (InputHandler::IsPressed(VirtualKeys::Control) && InputHandler::IsPressed(VirtualKeys::Menu))
    {
        keyState[VirtualKeys::Control] = 0xff;
        keyState[VirtualKeys::Menu] = 0xff;
    }
    int result = ToUnicode((unsigned int)key, 0, keyState, buffer, 10, 0);
    if (result == 1)
        return (char)buffer[0];
    return 0;
}