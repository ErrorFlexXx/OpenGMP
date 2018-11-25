#pragma once

#include <string>
#include <vector>

namespace OpenGMP
{
    class Server;

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
        static bool LoadCachedServerlist(std::string &configPath, std::vector<Server> &serverlist);

        /**
         * @brief StoreCachedServerList strores server elements to a json file.
         * @param configPath full path to json file.
         * @param serverlist to store the server elements in.
         * @return true, on successfull write, false otherwise.
         */
        static bool StoreCachedServerList(std::string &configPath, std::vector<Server> &serverlist);

        /**
         * @brief LoadWebServerlist loads server objects from an remote json file.
         * @param host to connect to.
         * @param url to the json file on this host.
         * @param serverlist to store read elements in.
         * @return true on successfull read, false otherwise.
         */
        static bool LoadWebServerlist(std::string &host, std::string &url, std::vector<Server> &serverlist);
    };
}
