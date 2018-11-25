#include "serverStorage.hpp"
#include <Shared/Objects/server.hpp>

using namespace std;
using namespace OpenGMP;

bool ServerStorage::LoadCachedServerlist(std::string &configPath, vector<Server> &serverlist)
{
    return false;
}

bool ServerStorage::StoreCachedServerList(std::string &configPath, vector<Server> &serverlist)
{
    return false;
}

bool ServerStorage::LoadWebServerlist(std::string &host, std::string &url, vector<Server> &serverlist)
{
    return false;
}
