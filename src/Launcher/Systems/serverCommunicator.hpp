#pragma once

#include <Launcher/Objects/lserver.hpp>
#include <QObject> //To allow being called in a thread.
#include <list>

class FrmMain;

namespace OpenGMP
{
    /**
     * @brief The ServerCommunicator class is a thread worker querying informations from servers
     *   on a regular basis and handover informations to the ui thread.
     */
    class ServerCommunicator : public QObject
    {
        Q_OBJECT

    public:
        explicit ServerCommunicator(QObject *parent = 0);

        /**
         * @brief SetServerList sets the serverlist to use with.
         * @param serverList which is copied to this instance (thread decoupling)
         */
        void SetServerList(const std::list<LServer> &serverList);

    signals:
        /**
         * @brief UpdateServerEntry signal emitted to main thread, if a server entry got an update.
         * @param server entry, which values shall be updated in frmMain.
         */
        void UpdateServerEntry(const OpenGMP::LServer &server);

        /**
         * @brief finished signal is called if the worker loop ends.
         */
        void finished();

    public slots:
        /**
         * @brief Stop signal this worker, it shall stop now.
         */
        void Stop();

        /**
         * @brief UpdateServerLoop worker task. Loop interruptible by run attribute.
         */
        void UpdateServerLoop();

    private:
        volatile bool run;              //!< Run flag of UpdateServerLoop.
        std::list<LServer> serverList;  //!< Owned copy of serverList, this system works with.
    };
}
