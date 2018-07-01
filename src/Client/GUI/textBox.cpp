#include "textBox.hpp"
#include "visualText.hpp"
#include "../gameClient.hpp"
#include "../Systems/inputSystem.hpp"
#include "../Types/virtualKeys.hpp"
#include <Shared/Components/gameTime.hpp>
#include <functional>

using namespace OpenGMP;
using namespace OpenGMP::GUI;
using namespace OpenGMP::Components;
using namespace OpenGMP::Systems;
using namespace OpenGMP::Types;

const size_t TextBox::cursorSize = 16;
const int TextBox::cursorOffsetX = 1 - TextBox::cursorSize / 2;
const size_t TextBox::cursorOffsetY = 1;
const size_t TextBox::arrowSize = 10;

TextBox::TextBox(GameClient &gameClient, int x, int y, int w, bool fixedBorders, bool passwordText)
    : gameClient(gameClient)
    , width(w)
    , height(fontSizeDefault)
    , inputVis(x, y, w, height)
    , cursorVis(x + cursorOffsetX, y + cursorOffsetY, cursorSize, cursorSize)
    , leftArrow(x, y + (fontSizeDefault - arrowSize) / 2, arrowSize, arrowSize)
    , rightArrow(x + w - arrowSize, y + (fontSizeDefault - arrowSize) / 2, arrowSize, arrowSize)
    , keyRepeater(gameClient, [=](VirtualKeys key) { this->KeyPressedNoRepeatUpdate(key); })
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
    this->passwordText = passwordText;
    pos.x = x;
    pos.y = y;

    this->fixedBorders = fixedBorders;
    inputVis.CreateText("", 0, 0);
    cursorVis.SetBackTexture("CURSOR.TGA");
    leftArrow.SetBackTexture("L.tga");
    rightArrow.SetBackTexture("R.tga");
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

void TextBox::Update(unsigned long long now)
{
    if (!enabled)
        return;

    keyRepeater.Update(now);

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
    keyRepeater.KeyDown(key, GameTime::GetTicks());
    KeyPressedNoRepeatUpdate(key);
}

void TextBox::KeyPressedNoRepeatUpdate(VirutalKeys key)
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
    else if (key == VirtualKeys::Home)
    {
        cursorPos = 0;
    }
    else if (key == VirtualKeys::End)
    {
        cursorPos = input.length();
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

bool TextBox::GetPasswordText()
{
    return passwordText;
}

void TextBox::SetPasswordText(bool value)
{
    passwordText = value;
    UpdateInputVisual();
}

void TextBox::UpdateInputVisual()
{
    size_t sub = 0;
    if (cursorPos >= hideChars)
        sub = hideChars;

    std::string substractedText = input.substr(sub);
    int cursorLen;
    int inputLen;
    if (passwordText) //Password text - show stars
    {
        std::string starText;
        starText.insert(0, substractedText.length(), '#');
        InputText()->SetText(starText);
        cursorLen = (int)StringPixelWidth(starText.substr(0, cursorPos - sub));
        inputLen = (int)StringPixelWidth(starText);
    }
    else //No password - show text
    {
        InputText()->SetText(substractedText);
        cursorLen = (int)StringPixelWidth(substractedText.substr(0, cursorPos - sub));
        inputLen = (int)StringPixelWidth(substractedText);
    }

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
    
    if (gameClient.inputSystem.IsPressed(VirtualKeys::Shift))
        keyState[VirtualKeys::Shift] = 0xff;
    if (gameClient.inputSystem.IsPressed(VirtualKeys::Control) && 
        gameClient.inputSystem.IsPressed(VirtualKeys::Menu))
    {
        keyState[VirtualKeys::Control] = 0xff;
        keyState[VirtualKeys::Menu] = 0xff;
    }
    int result = ToUnicode((unsigned int)key, 0, keyState, buffer, 10, 0);
    if (result == 1)
        return (char)buffer[0];
    return 0;
}