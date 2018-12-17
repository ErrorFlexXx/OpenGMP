#include "zipFile.hpp"
#include "logger.hpp"
#include <physfs.h>
#include <cstring>

using namespace OpenGMP;

ZipFile::ZipFile(const std::string &filename)
    : File(filename)
{}

ZipFile::ZipFile(const std::string &filename, const std::string &directory)
    : File(filename, directory)
{}

ZipFile::ZipFile(const File &copy)
    : File(copy)
{}

static void modTimeToStr(PHYSFS_sint64 modtime, char *modstr, size_t strsize)
{
    const char *str = "unknown modtime";
    if (modtime != -1)
    {
        time_t t = (time_t) modtime;
        str = ctime(&t);
    } /* if */

    strncpy(modstr, str, strsize);
    modstr[strsize-1] = '\0';
    strsize = strlen(modstr);
    while ((modstr[strsize-1] == '\n') || (modstr[strsize-1] == '\r'))
        modstr[--strsize] = '\0';
} /* modTimeToStr */

int dumpFileFailure(const char *fname, PHYSFS_File *out, PHYSFS_File *in)
{
    LogError() << "dumpFile failed: " << PHYSFS_GETERROR();
    PHYSFS_delete(fname);
    if (in != nullptr)
        PHYSFS_close(in);
    if (out != nullptr)
    {
        if (!PHYSFS_close(out))
            LogError() << "PHYSFS_close failed: " << PHYSFS_GETERROR();
    }
    return 0; //Failure!
}

static int dumpFile(const char *fname)
{
    PHYSFS_File *out = nullptr;
    PHYSFS_File *in = nullptr;

    if ((in = PHYSFS_openRead(fname)) == nullptr)
    {
        return dumpFileFailure(fname, out, in);
    }
    else if ((out = PHYSFS_openWrite(fname)) == nullptr)
        return dumpFileFailure(fname, out, in);
    else
    {
        char modstr[64];
        PHYSFS_sint64 size = PHYSFS_fileLength(in);
        PHYSFS_Stat stat;
        if(0 == PHYSFS_stat(fname, &stat))
            LogWarn() << "PHYSFS_stat failed: " << PHYSFS_GETERROR();

        modTimeToStr(stat.modtime, modstr, sizeof (modstr));

        while (!PHYSFS_eof(in))
        {
            static char buf[64 * 1024];
            PHYSFS_sint64 br = PHYSFS_readBytes(in, buf, sizeof (buf));
            if (br == -1)
            {
                return dumpFileFailure(fname, out, in);
            }
            else
            {
                PHYSFS_sint64 bw = PHYSFS_writeBytes(out, buf, br);
                if (bw != br)
                {
                    return dumpFileFailure(fname, out, in);
                }
                else
                    size -= bw;
            } /* else */
        } /* while */

        if (size != 0)
        {
            return dumpFileFailure(fname, out, in);
        }
    } /* else */

    if (in != nullptr)
        PHYSFS_close(in);

    if (out != nullptr)
    {
        if (!PHYSFS_close(out))
            LogError() << "PHYSFS_close failed: " << PHYSFS_GETERROR();
    } /* if */
    return 1; //OK
} /* dumpFile */

static PHYSFS_EnumerateCallbackResult unpackCallback(void *_depth, const char *origdir, const char *str)
{
    int depth = *((int*) _depth);
    const int len = strlen(origdir) + strlen(str) + 2;
    char *fname = (char *) malloc(len);
    if (fname == nullptr)
    {
        LogError() << "malloc out of memory!";
        return PHYSFS_ENUM_ERROR; //Failure!
    }
    else
    {
        if (strcmp(origdir, "/") == 0)
            origdir = "";

        snprintf(fname, len, "%s/%s", origdir, str);

        PHYSFS_Stat stat;
        if(0 == PHYSFS_stat(fname, &stat))
        {
            LogError() << "PHYSFS_stat failed: " << PHYSFS_GETERROR();
            return PHYSFS_ENUM_ERROR; //Failure!
        }

        //printf("%s ", fname);
        if (stat.filetype == PHYSFS_FILETYPE_DIRECTORY)
        {
            depth++;
            //printf("(directory)\n");
            if (!PHYSFS_mkdir(fname))
                LogError() << "PHYSFS_mkdir failed: " << PHYSFS_GETERROR();
            else
            {
                if(0 == PHYSFS_enumerate(fname, unpackCallback, nullptr))
                {
                    LogError() << "PHYSFS_enumerate failed: " << PHYSFS_GETERROR();
                    return PHYSFS_ENUM_ERROR; //Failure!
                }
            }
        } /* if */

        else if (stat.filetype == PHYSFS_FILETYPE_DIRECTORY)
        {
            //printf("(symlink)\n");
            /* !!! FIXME: ?  if (!symlink(fname, */
        } /* else if */

        else  /* ...file. */
        {
            dumpFile(fname);
        } /* else */

        free(fname);
        return PHYSFS_ENUM_OK;
    } /* else */
} /* unpackCallback */

bool ZipFile::Extract(const std::string &to)
{
    if(!PHYSFS_init(to.c_str()))
    {
        LogError() << "PHYSFS_init failed: " << PHYSFS_GETERROR();
        return false;
    }

    if(!PHYSFS_setWriteDir(to.c_str()))
    {
        LogError() << "PHYSFS_setWriteDir failed: " << PHYSFS_GETERROR();
        return false;
    }

    if(!PHYSFS_mount(Fullpath().c_str(), NULL, 1))
    {
        LogError() << "PHYSFS_mount failed: " << PHYSFS_GETERROR();
        return false;
    }

    PHYSFS_permitSymbolicLinks(1);

    int result = PHYSFS_enumerate("/", unpackCallback, nullptr);
    if(result == 0)
        LogError() << "PHYSFS_enumerate failed: " << PHYSFS_GETERROR();

    PHYSFS_deinit();

    return (result != 0);
}
