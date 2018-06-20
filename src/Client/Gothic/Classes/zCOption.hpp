#pragma once

#include "../xcall.h"
#include "../Types/zSTRING.hpp"

#pragma warning(disable:4731) //Inline assembler modifies framepointer EBP

class zFILE; //Implement if needed
class zCOptionSection;
class zCOptionEntry;

enum zTOptionPaths
{
    unknownContent
};

class zCOption
{
public:
    static zCOption * GetZOptions()
    {
        return *(zCOption**)((unsigned int)0x008CD988);
    }
    
    static zCOption * GetZGameOptions()
    {
        return *(zCOption**)((unsigned int)0x008CD98C);
    }

    /*virtual*/ ~zCOption()
    {
        XCALL(0x00460570);
    }
    
    int Load(zSTRING maybeFilename)
    {
        XCALL(0x004607B0);
    }
    
    int Save(zSTRING maybeFilename)
    {
        XCALL(0x004616C0);
    }
        
    int WriteBool(class zSTRING const &, char const *, int, int)
    {
        XCALL(0x00461DE0);
    }
        
    int WriteInt(class zSTRING const &, char const *, int, int)
    {
        XCALL(0x00461E30);
    }

    int WriteDWord(class zSTRING const &, char const *, unsigned long, int)
    {
        XCALL(0x00461E60);
    }
        
    int WriteReal(class zSTRING const &, char const *, float, int)
    {
        XCALL(0x00461F90);
    }
        
    int WriteString(class zSTRING const &, char const *, class zSTRING, int)
    {
        XCALL(0x00461FD0);
    }
    
    int ReadBool(class zSTRING const &, char const *, int)
    {
        XCALL(0x00462160);
    }
    
    int ReadInt(class zSTRING const &, char const *, int)
    {
        XCALL(0x00462390);
    }
    
    unsigned long ReadDWord(class zSTRING const &, char const *, unsigned long)
    {
        XCALL(0x004624F0);
    }
    
    float ReadReal(class zSTRING const &, char const *, float)
    {
        XCALL(0x00462650);
    }
    
    zSTRING ReadString(class zSTRING const &, char const *, char const *)
    {
        XCALL(0x004627E0);
    }
    
    int EntryExists(class zSTRING const &, char const *)
    {
        XCALL(0x00462950);
    }
    
    unsigned short GetNumEntries(class zCOptionSection *)
    {
        XCALL(0x00462A20);
    }
    
    zCOptionEntry * GetEntry(class zCOptionSection *, int)
    {
        XCALL(0x00462A40)
    }
    
    int RemoveEntry(class zSTRING const &, char const *)
    {
        XCALL(0x00462A70);
    }
    
    void SetFlag(class zSTRING const &, char const *, int)
    {
        XCALL(0x00462C10);
    }
    
    zCOptionEntry * GetEntryByName(class zCOptionSection *, class zSTRING const &, int)
    {
        XCALL(0x00462D10);
    }
    
    zCOptionSection * GetSectionByName(class zSTRING const &, int)
    {
        XCALL(0x00463000);
    }
    
    int SectionExists(class zSTRING const &)
    {
        XCALL(0x00463250);
    }
    
    unsigned short GetNumSections(void)
    {
        XCALL(0x00463270);
    }
    
    zCOptionSection * GetSection(int)
    {
        XCALL(0x00463280);
    }
    
    int RemoveSection(class zSTRING const &)
    {
        XCALL(0x004632B0);
    }
    
    void InsertChangeHandler(class zSTRING const &, char const *, int(__cdecl*)(class zCOptionEntry &))
    {
        XCALL(0x00463310);
    }
    
    int WriteRaw(class zSTRING const &, char const *, void *, int, int)
    {
        XCALL(0x004634E0);
    }
    
    int ReadRaw(class zSTRING const &, char const *, void * &, void *, int)
    {
        XCALL(0x004636C0);
    }
    
    int WriteBool(class zSTRING const &, class zSTRING const &, int, int)
    {
        XCALL(0x004638A0);
    }
    
    int WriteInt(class zSTRING const &, class zSTRING const &, int, int)
    {
        XCALL(0x004638C0);
    }
    
    int WriteDWord(class zSTRING const &, class zSTRING const &, unsigned long, int)
    {
        XCALL(0x004638E0);
    }
    
    int WriteReal(class zSTRING const &, class zSTRING const &, float, int)
    {
        XCALL(0x00463900);
    }
    
    int WriteString(class zSTRING const &, class zSTRING const &, class zSTRING, int)
    {
        XCALL(0x00463930);
    }
    
    int WriteRaw(class zSTRING const &, class zSTRING const &, void *, int, int)
    {
        XCALL(0x004639E0);
    }
    
    int ReadBool(class zSTRING const &, class zSTRING const &, int)
    {
        XCALL(0x00463A00);
    }
    
    int ReadInt(class zSTRING const &, class zSTRING const &, int)
    {
        XCALL(0x00463A20);
    }
    
    unsigned long ReadDWord(class zSTRING const &, class zSTRING const &, unsigned long)
    {
        XCALL(0x00463A40);
    }
    
    float ReadReal(class zSTRING const &, class zSTRING const &, float)
    {
        XCALL(0x00463A60);
    }
    
    zSTRING ReadString(class zSTRING const &, class zSTRING const &, char const *)
    {
        XCALL(0x00463A90);
    }
    
    int ReadRaw(class zSTRING const &, class zSTRING const &, void *, int)
    {
        XCALL(0x00463AD0);
    }
    
    int AddParameters(class zSTRING)
    {
        XCALL(0x00463B00);
    }
    
    int Init(class zSTRING, bool)
    {
        XCALL(0x00463C20);
    }
    
    void ChangeDir(enum zTOptionPaths)
    {
        XCALL(0x00465160);
    }
    
    zFILE * GetDir(enum zTOptionPaths)
    {
        XCALL(0x00465250);
    }
    
    zSTRING & GetDirString(enum zTOptionPaths)
    {
        XCALL(0x00465260);
    }
    
    int Parm(class zSTRING const &)
    {
        XCALL(0x00465270);
    }
    
    zSTRING ParmValue(class zSTRING const &)
    {
        XCALL(0x00465380);
    }
    
    zSTRING ParmValueRaw(class zSTRING const &)
    {
        XCALL(0x00465580);
    }
    
    int ParmValueInt(class zSTRING const &)
    {
        XCALL(0x00465780);
    }
    
    float ParmValueFloat(class zSTRING const &)
    {
        XCALL(0x00465940);
    }
};