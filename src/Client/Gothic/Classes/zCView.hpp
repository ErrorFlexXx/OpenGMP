#pragma once

#include "../Types/zCOLOR.hpp"
#include "../Types/zSTRING.hpp"
#include "../xcall.h"

enum zTviewID
{
    VIEW_SCREEN,
    VIEW_VIEWPORT,
    VIEW_ITEM
};

class zCView
{
public:
    static zCView *GetScreen()
    {
        return *(zCView**)(0x00AB6468);
    }

    zCView(void)
    {
        XCALL(0x007A5640);
    }
    
    zCView(int,int,int,int,enum zTviewID)
    {
        XCALL(0x007A5700);
    }

    /*virtual*/ ~zCView(void)
    {
        XCALL(0x007A57C0);
    }

    static void StdPrintwin(class zSTRING const &)
    {
        XCALL(0x007A5F00);
    }

    static void PrintDebug(class zSTRING const &)
    {
        XCALL(0x007ABA90);
    }

    static void SetShowDebug(int)
    {
        XCALL(0x007ABAB0);
    }

    static int GetShowDebug(void)
    {
        XCALL(0x007ABAC0);
    }

    static void ChangeMode(void)
    {
        XCALL(0x007ABD90);
    }

    static void SetNextMode(void)
    {
        XCALL(0x007ABDA0);
    }

    static void SetMode(int,int,int,struct HWND__ * *)
    {
        XCALL(0x007ABDB0);
    }

    void Init(void)
    {
        XCALL(0x007A5990);
    }

    void Init(int,int,int,int,enum zTviewID)
    {
        XCALL(0x007A5B20);
    }

    void Init(int,int,class zSTRING const &,enum zTviewID)
    {
        XCALL(0x007A5CC0);
    }

    void Create(class zSTRING const &,enum zCView::zEViewFX,enum zCView::zEViewFX,float,int)
    {
        XCALL(0x007A6810);
    }

    /*virtual*/ int nax(int)
    {
        XCALL(0x007A5E00);
    }
    
    /*virtual*/ int nay(int)
    {
        XCALL(0x007A5E40);
    }

    /*virtual*/ int anx(int)
    {
        XCALL(0x007A5E80);
    }

    /*virtual*/ int any(int)
    {
        XCALL(0x007A5EC0);
    }

    void SetAutoScroll(float)
    {
        XCALL(0x007A5F20);
    }

    void SetTransparency(int)
    {
        XCALL(0x007A6060);
    }

    void SetAlphaBlendFunc(enum zTRnd_AlphaBlendFunc const &)
    {
        XCALL(0x007A6070);
    }

    void SetColor(struct zCOLOR const &)
    {
        XCALL(0x007A6080);
    }

    zCOLOR GetColor(void)
    {
        XCALL(0x007A6090);
    }

    void Setflags(int)
    {
        XCALL(0x007A60A0);
    }
    
    void ClrFlags(int)
    {
        XCALL(0x007A60B0);
    }

    int HasFlag(int)
    {
        XCALL(0x007A60D0);
    }

    void InsertBack(class zCTexture *)
    {
        XCALL(0x007A60F0);
    }

    void InsertBack(class zSTRING const &)
    {
        XCALL(0x007A6130);
    }

    void InitPrintwin(void)
    {
        XCALL(0x007A6230);
    }

    /*virtual*/ void Blit(void)
    {
        XCALL(0x007A63C0);
    }

    /*virtual*/ void DrawItems(void)
    {
        XCALL(0x007A6750);
    }

    void Top(void)
    {
        XCALL(0x007A6790);
    }

    void ForceOpen(void)
    {
        XCALL(0x007A6990);
    }

    void Open(void)
    {
        XCALL(0x007A6C00);
    }

    void Close(void)
    {
        XCALL(0x007A6E30);
    }

    void RecalcChildsSize(void)
    {
        XCALL(0x007A74D0);
    }

    void RecalcChildsPos(void)
    {
        XCALL(0x007A7540);
    }

    void SetPos(int,int)
    {
        XCALL(0x007A75B0);
    }

    void GetPos(int &,int &)
    {
        XCALL(0x007A7660);
    }

    void GetPixelPos(int &,int &)
    {
        XCALL(0x007A76C0);
    }

    void Move(int,int)
    {
        XCALL(0x007A76E0);
    }

    void SetSize(int,int)
    {
        XCALL(0x007A77A0);
    }

    void GetSize(int &,int &)
    {
        XCALL(0x007A7810);
    }

    void GetPixelSize(int &,int &)
    {
        XCALL(0x007A7830);
    }

    void GetExtends(int &,int &,int &,int &)
    {
        XCALL(0x007A7860);
    }

    void GetScreenExtends(int &,int &,int &,int &)
    {
        XCALL(0x007A78A0);
    }

    void GetPixelExtends(float &,float &,float &,float &)
    {
        XCALL(0x007A7910);
    }

    int IsIn(int,int)
    {
        XCALL(0x007A7960);
    }

    zCView * GetItem(int,int)
    {
        XCALL(0x007A79F0);
    }

    zCViewText * CreateText(int,int,class zSTRING const &,float,struct zCOLOR &,int,int)
    {
        XCALL(0x007A7AB0);
    }

    void CheckTimedText(void)
    {
        XCALL(0x007A7C50);
    }

    void PrintTimed(int,int,class zSTRING const &,float,struct zCOLOR *)
    {
        XCALL(0x007A7D20);
    }

    void PrintTimedCX(int,class zSTRING const &,float,struct zCOLOR *)
    {
        XCALL(0x007A7DB0);
    }

    void PrintTimedCY(int,class zSTRING const &,float,struct zCOLOR *)
    {
        XCALL(0x007A7F00);
    }

    void PrintTimedCXY(class zSTRING const &,float,struct zCOLOR *)
    {
        XCALL(0x007A7FC0);
    }

    void PrintMessage(class zSTRING const &,class zSTRING const &,float,struct zCOLOR &)
    {
        XCALL(0x007A8140);
    }

    void PrintMessageCXY(class zSTRING const &,class zSTRING const &,float,struct zCOLOR &)
    {
        XCALL(0x007A8450);
    }

    void PrintSelection(class zSTRING const &,class zSTRING const &,struct zCOLOR &,struct zCOLOR &)
    {
        XCALL(0x007A8BB0);
    }

    void Dialog(int,int,class zSTRING const &,float,struct zCOLOR *)
    {
        XCALL(0x007A8D40);
    }

    void DialogCX(int,class zSTRING const &,float,struct zCOLOR *)
    {
        XCALL(0x007A8E10);
    }

    void DialogCY(int,class zSTRING const &,float,struct zCOLOR *)
    {
        XCALL(0x007A8E70);
    }

    void DialogCXY(class zSTRING const &,float,struct zCOLOR *)
    {
        XCALL(0x007A8F60);
    }

    void DialogMessage(class zSTRING const &,class zSTRING const &,float,struct zCOLOR &)
    {
        XCALL(0x007A8FB0);
    }

    void DialogMessageCXY(class zSTRING const &,class zSTRING const &,float,struct zCOLOR &)
    {
        XCALL(0x007A9240);
    }

    void DialogSelection(class zSTRING const &,class zSTRING const &,struct zCOLOR &,struct zCOLOR &,float)
    {
        XCALL(0x007A94D0);
    }

    void SetFont(class zCFont *)
    {
        XCALL(0x007A98F0);
    }

    void SetFontColor(struct zCOLOR const &)
    {
        XCALL(0x007A9910);
    }

    void SetFont(class zSTRING const &)
    {
        XCALL(0x007A9920);
    }

    class zCFont * GetFont(void)
    {
        XCALL(0x007A9950);
    }

    class zSTRING GetFontName(void)
    {
        XCALL(0x007A9960);
    }

    int FontY(void)
    {
        XCALL(0x007A99F0);
    }

    int FontSize(class zSTRING &)
    {
        XCALL(0x007A9A10);
    }

    void Print(int,int,class zSTRING const &)
    {
        XCALL(0x007A9A40);
    }

    void PrintCX(int,class zSTRING const &)
    {
        XCALL(0x007A9E50);
    }

    void PrintCY(int,class zSTRING const &)
    {
        XCALL(0x007A9F40);
    }

    void PrintCXY(class zSTRING const &)
    {
        XCALL(0x007AA030);
    }

    void ClrPrintwin(void)
    {
        XCALL(0x007AA140);
    }

    void DefPrintwin(int,int,int,int)
    {
        XCALL(0x007AA730);
    }

    void Printwin(class zSTRING const &)
    {
        XCALL(0x007AA8D0);
    }

    class zSTRING Input(int)
    {
        XCALL(0x007AACC0);
    }

    class zSTRING Input(int,class zSTRING &)
    {
        XCALL(0x007AAD60);
    }

    class zSTRING Input(int,int,int,class zSTRING &)
    {
        XCALL(0x007AB310);
    }

    int InputNumber(int,int)
    {
        XCALL(0x007AB5E0);
    }

    void InsertItem(class zCView *,int)
    {
        XCALL(0x007ABAD0);
    }

    void RemoveItem(class zCView *)
    {
        XCALL(0x007ABD10);
    }

    /*virtual*/ void Line(int,int,int,int,struct zCOLOR const &)
    {
        XCALL(0x007ABF70);
    }

    /*virtual*/ int ClipLine(int &,int &,int &,int &)
    {
        XCALL(0x007AC060);
    }

    void Render(void)
    {
        XCALL(0x007AC210);
    }

protected:
    void ApplyOpenClose(class zVEC2 &,class zVEC2 &)
    {
        XCALL(0x007A6F40);
    }

    void UpdateOpen(void)
    {
        XCALL(0x007A71C0);
    }

    void UpdateClose(void)
    {
        XCALL(0x007A7210);
    }

    void UpdateOpenZoom(void)
    {
        XCALL(0x007A72C0);
    }

    void UpdateCloseZoom(void)
    {
        XCALL(0x007A73C0);
    }

private:
    unsigned char load[0x100];

    class zCViewText * CreateText(int,int,class zSTRING const &)
    {
        XCALL(0x007AA2B0);
    }

    class zSTRING GetFirstText(void)
    {
        XCALL(0x007AA420);
    }

    void Nextline(class zSTRING const &,float,struct zCOLOR *,int *)
    {
        XCALL(0x007AA4A0);
    }

    void PrintChars(int,int,class zSTRING const &)
    {
        XCALL(0x007A9B10);
    }

    void BlitText(void)
    {
        XCALL(0x007A62A0);
    }

    void CalcPixelPos(int &,int &)
    {
        XCALL(0x007A7680);
    }

    void CheckAutoScroll(void)
    {
        XCALL(0x007A5F60);
    }
};