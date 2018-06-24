#include "serverWorld.hpp"
#include <cpgf/metatraits/gmetaconverter_string.h>
#include <cpgf/gmetadefine.h>
#include <cpgf/goutmain.h>
#include "../ScriptController/scriptController.hpp"

using namespace std;
using namespace cpgf;

ServerWorld::ServerWorld(const string worldName, const string worldFilename)
{
}


G_AUTO_RUN_BEFORE_MAIN()
{
    using namespace cpgf;

    GDefineMetaClass<ServerWorld>
            ::define("method::ServerWorld")
            ._constructor<void *(const string, const string)>()
            ._method("GetWorldName", &World::GetWorldname)
            ;
    ScriptController::RegisterClass(std::string("ServerWorld"));
}
