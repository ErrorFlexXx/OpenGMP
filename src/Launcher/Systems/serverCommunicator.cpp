#include "serverCommunicator.hpp"
#include <ZenLib/utils/logger.h>
#include <cpp-httplib/httplib.h>
#include <QThread>
#include <QDateTime>
#include <string>

#define UPDATE_BREAK_S 5 //Update all server entries every <- seconds.
#define UPDATE_INTERRUPTIBLE_PIECE_MS 100.0 //Thread interruptible in <- ms inside UPDATE_BREAK_S

using namespace std;
using namespace OpenGMP;

ServerCommunicator::ServerCommunicator(QObject *parent)
    : QObject(parent)
{}

void ServerCommunicator::SetServerList(const std::list<LServer> &serverList)
{
    this->serverList = serverList; //Copy the list.
}

void ServerCommunicator::UpdateServerLoop()
{
    run = true;
    while(run)
    {
        for(OpenGMP::LServer &server : serverList)
        {
            if(!run)
                break;
            httplib::Client client(server.hostname.c_str(), server.webPort, 1);

            QDateTime before = QDateTime::currentDateTime(); //Stop the time.
            auto res = client.Get("/status");
            QDateTime after = QDateTime::currentDateTime(); //Here we got the response.

            if (res && res->status == 200) //Server available ?
            {
                server.playerInfo = QString(res->body.c_str());
                server.pingInfo   = QString::number((int)before.msecsTo(after));
            }
            else //Server unavailable
            {
                server.playerInfo = "-";
                server.pingInfo   = "Offline";
            }
            emit UpdateServerEntry(server);
        }
        //Sleep, but be interruptible while sleeping UPDATE_BREAK_S long, if the application wants to quit.
        for(size_t i = 0; i < UPDATE_BREAK_S * (1000.0 / UPDATE_INTERRUPTIBLE_PIECE_MS) && run; i++) //Wait UPDATE_BREAK_S seconds
            QThread::msleep(UPDATE_INTERRUPTIBLE_PIECE_MS); //But be interruptable though run flag.
    }
    emit finished();
}

void ServerCommunicator::Stop()
{
    run = false;
}


