#include "serverClient.hpp"
//Script system includes:
#include "../ScriptController/scriptController.hpp"
#include <cpgf/metatraits/gmetaconverter_string.h>
#include <cpgf/gmetadefine.h>
#include <cpgf/goutmain.h>

using namespace RakNet;

ServerClient::ServerClient(BitStream &stream)
    : IClient(stream)
{
}

//Script interface registration:
//G_AUTO_RUN_BEFORE_MAIN()
//{
//    using namespace cpgf;

//    GDefineMetaClass<ServerClient>
//            ::define("method::ServerClient")
//            //._constructor<void *(const string, const string)>()
//            //._method<void (ServerClient*)>("AddClient", &LoginSystem::AddClient)
//            ;
//    ScriptController::RegisterClass(std::string("ServerClient"));
//}


