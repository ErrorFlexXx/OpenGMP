#include "serverStorage.hpp"
#include <Launcher/Objects/jsonFile.hpp>
#include <Launcher/Objects/lserver.hpp>
#include <json/json.hpp>
#include <cpp-httplib/httplib.h>
#include <QString>

using namespace std;
using namespace OpenGMP;
using namespace nlohmann;
using namespace httplib;

bool ServerStorage::LoadCachedServerlist(const std::string &filename, list<LServer> &serverlist)
{
    JsonFile file(filename.c_str());
    if(!file.Load()) return false;
    json j = file.ReadJson();

    for(json &obj : j)
    {
        LServer server;
        server.FromJson(obj);
        serverlist.push_back(server);
    }
    return true;
}

bool ServerStorage::StoreCachedServerList(const std::string &filename, list<LServer> &serverlist)
{
    json j;

    for(LServer &server : serverlist)
    {
        j.push_back(server.ToJson()); //Create Json objects and pushback to array j
    }

    JsonFile file(filename.c_str());
    file.Clear();
    file.WriteJson(j);
    return file.Save();
}

bool ServerStorage::LoadWebServerlist(const std::string &host, const std::string &url, list<LServer> &serverlist)
{
    SSLClient client(host.c_str(), 443);
    auto res = client.Get(url.c_str());
    if (res && res->status == 200)
    {
        json j = json::parse(res->body);
        for(json &obj : j)
        {
            LServer server;
            server.FromJson(obj);
            if(!Exists(server, serverlist))
                serverlist.push_back(server);
        }
        return true;
    }
    return false;
}

bool ServerStorage::Exists(const LServer &server, const list<LServer> &serverlist)
{
    for(const LServer &check : serverlist)
        if(check == server)
            return true;
    return false;
}
