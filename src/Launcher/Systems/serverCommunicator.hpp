#pragma once

#include <Launcher/Objects/lserver.hpp>
#include <QObject>
#include <list>

class FrmMain;

namespace OpenGMP
{
    class ServerCommunicator : public QObject
    {
        Q_OBJECT

    public:
        explicit ServerCommunicator(QObject *parent = 0);

        void SetServerList(const std::list<LServer> &serverList);

    signals:
        /**
         * @brief UpdateServerEntry signal emitted to main thread, if a server entry got an update.
         * @param server entry, which values shall be updated in frmMain.
         */
        void UpdateServerEntry(const OpenGMP::LServer &server);
        void finished();

    public slots:
        void Stop();
        void UpdateServerLoop();

    private:
        volatile bool run;
        std::list<LServer> serverList; //!< Copy of serverList, this system works with.
    };
}
