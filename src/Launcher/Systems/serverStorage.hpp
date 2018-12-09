#pragma once

#include <string>
#include <list>

namespace OpenGMP
{
    class LServer;

    /**
     * @brief The ServerStorage class is used to load and store server objects.
     */
    class ServerStorage
    {
    public:
        /**
         * @brief LoadCachedServerlist loads stored server objects from a json file.
         * @param configPath full path to json file.
         * @param serverlist gets read server items.
         * @return true, on successfull read, false otherwise.
         */
        static bool LoadCachedServerlist(const std::string &filename, std::list<LServer> &serverlist);

        /**
         * @brief StoreCachedServerList strores server elements to a json file.
         * @param configPath full path to json file.
         * @param serverlist to store the server elements in.
         * @return true, on successfull write, false otherwise.
         */
        static bool StoreCachedServerList(const std::string &filename, std::list<LServer> &serverlist);

        /**
         * @brief LoadWebServerlist loads server objects from an remote json file.
         * @param host to connect to.
         * @param url to the json file on this host.
         * @param serverlist to store read elements in.
         * @return true on successfull read, false otherwise.
         */
        static bool LoadWebServerlist(const std::string &host, const std::string &url, std::list<LServer> &serverlist);

    private:
        static bool Exists(const LServer &server, const std::list<LServer> &serverlist);
    };
}
