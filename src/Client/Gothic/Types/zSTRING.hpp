#pragma once

#include "../xcall.h"
#include <Shared/Components/string.hpp>
#include <string>

int __cdecl operator==(class zSTRING const &, char const * const);
int __cdecl operator==(class zSTRING const &, class zSTRING const &);

class zSTRING
{
public:
    /////////////////////////////////
    // Constructors and Destructor //
    /////////////////////////////////
    zSTRING()
    {
        XCALL(0x00402AF0);
    }
    
    zSTRING(zSTRING const &)
    {
        XCALL(0x00416500);
    }

    zSTRING(class zSTRING const *)
    {
        XCALL(0x007928D0);
    }

    zSTRING(char const *)
    {
        XCALL(0x004010C0);
    }

    zSTRING(const OpenGMP::String &text)
        :zSTRING(text.text)
    {
    }

    zSTRING(const std::string &text)
        : zSTRING(text.c_str())
    {
    }
        
    zSTRING(double number, int precision)
    {
        XCALL(0x00454680);
    }

    zSTRING(float number, int precision)
    {
        XCALL(0x00435970);
    }
        
    zSTRING(unsigned long)
    {
        XCALL(0x00461E90);
    }

    zSTRING(int)
    {
        XCALL(0x00435870);
    }

    zSTRING(char)
    {
        XCALL(0x0051AC80);
    }

    zSTRING(long)
    {
        XCALL(0x006CFE50);
    }
        
    ~zSTRING()
    {
        XCALL(0x00401160);
    }

    //////////////////////////
    // Methods (modifying)  //
    //////////////////////////

    zSTRING & Lower()
    {
        XCALL(0x0046A9F0);
    }

    zSTRING & Upper()
    {
        XCALL(0x0046AB00);
    }
        
    zSTRING & UpperFirstLowerRest()
    {
        XCALL(0x0046AC10);
    }
        
    zSTRING & Align(enum zTSTR_ALIGN, int availCharWidth , char fillChar)
    {
        XCALL(0x0046AD60);
    }
       
    int Insert(unsigned int, class zSTRING const &)
    {
        XCALL(0x0046B400);
    }
        
    int Overwrite(unsigned int, class zSTRING const &)
    {
        XCALL(0x0046B6A0);
    }

    int DeleteRight(unsigned int length)
    {
        XCALL(0x0046B990);
    }
        
    int Delete(unsigned int, unsigned long)
    {
        XCALL(0x0046BAA0);
    }

    int Delete(class zSTRING const &, enum zTSTR_KIND)
    {
        XCALL(0x0046BCF0);
    }

    int Copy(unsigned int, unsigned long)
    {
        XCALL(0x0046BFC0);
    }

    zSTRING Copied(unsigned int, unsigned long) const
    {
        XCALL(0x0046C170);
    }

    int Copy(class zSTRING const &, enum zTSTR_KIND const &)
    {
        XCALL(0x0046C2D0);
    }

    void TrimLeft(char)
    {
        XCALL(0x0046C630);
    }

    void TrimRight(char)
    {
        XCALL(0x0046C770);
    }

    bool __cdecl Sprintf(char const *, ...)
    {
        XCALL(0x0046CC60);
    }

    void Clear()
    {
        XCALL(0x0059D010);
    }

    /////////////////////////////
    // Methods (not modifying) //
    /////////////////////////////

    char * ToChar() const
    {
        XCALL(0x004639D0);
    }
    zSTRING PickWord(unsigned int, class zSTRING const &, class zSTRING const &) const
    {
        XCALL(0x0046AF80);
    }

    char const * PickWordPos(unsigned int, class zSTRING const &, class zSTRING const &) const
    {
        XCALL(0x0046B1D0);
    }

    zSTRING PickWord_Old(int, class zSTRING const &) const
    {
        XCALL(0x0046B340);
    }

    zSTRING Inserted(unsigned int, class zSTRING const &) const
    {
        XCALL(0x0046B520);
    }


    zSTRING Overwritten(unsigned int, class zSTRING const &) const
    {
        XCALL(0x0046B890);
    }

    zSTRING Deleted(unsigned int, unsigned long) const
    {
        XCALL(0x0046BBB0);
    }

    zSTRING Deleted(class zSTRING const &, enum zTSTR_KIND) const
    {
        XCALL(0x0046BEE0);
    }

    zSTRING Copied(class zSTRING const &, enum zTSTR_KIND const &) const
    {
        XCALL(0x0046C550);
    }
        
    int Search(int, char const *, unsigned int) const
    {
        XCALL(0x0046C920);
    }

    int Length(void) const
    {
        XCALL(0x0059D0E0);
    }
        
    int Search(class zSTRING const &, unsigned int) const
    {
        XCALL(0x00492680);
    }
    
    float ToFloat(void) const
    {
        XCALL(0x004936C0);
    }

    long ToInt(void) const
    {
        XCALL(0x0059D0F0);
    }
        
    int Search(char const *, unsigned int) const
    {
        XCALL(0x0059D110);
    }

    bool IsEmpty(void) const
    {
        XCALL(0x00674210);
    }

    int SearchRev(class zSTRING const &, unsigned int) const
    {
        XCALL(0x0046CA20);
    }

    ///////////////////////////
    // Operators             //
    ///////////////////////////
    zSTRING & operator=(class zSTRING const &)
    {
        XCALL(0x0059CEB0);
    }
            
    zSTRING & operator=(char const *)
    {
        XCALL(0x004CFAF0);
    }
    
    zSTRING &operator+=(char const *)
    {
        XCALL(0x0067A7B0);
    }
    
    char & operator[](unsigned int)
    {
        XCALL(0x00445A20);
    }

private:
     unsigned char load[4 * 5];
};

