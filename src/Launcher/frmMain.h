#pragma once

#include <Launcher/Systems/jsonFile.hpp>
#include <Launcher/Systems/serverCommunicator.hpp>
#include <Launcher/Objects/lserver.hpp>
#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include <list>
#include <mutex>

namespace Ui {
    class FrmMain;
}

class QTreeWidgetItem;

class FrmMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrmMain(QWidget *parent = nullptr);
    ~FrmMain();

    OpenGMP::LServer &GetServerFromTreeItem(QTreeWidgetItem *item);
    void UpdateFrmServerList();
    void CreateDefaultConfig();
    std::mutex serverListMutex;             //!< Mutex to protect the serverList
    std::list<OpenGMP::LServer> serverList;  //!< List of known servers.
    OpenGMP::JsonFile config;               //!< Json parser object for configurations.

signals:
    /**
     * @brief UpdatedServerList updates the serverlist for other threads.
     * @param serverList which is now current.
     */
    void UpdatedServerList(const std::list<OpenGMP::LServer> &serverList);

private slots:
    void on_btnTest_clicked();
    void on_actionExit_triggered();
    void on_actionMainSettings_triggered();

    /**
     * @brief UpdateServerEntry updates the form data of a server entry in the treeView.
     * @param server object data to update with.
     */
    void UpdateServerEntry(const OpenGMP::LServer &server);

private:
    Ui::FrmMain *ui;
    OpenGMP::ServerCommunicator *serverCommunicatorTask; //!<Task to update all server entries in a loop.
    QThread *serverCommunicator; //!< Thread to decouple comm. from the ui thread.
};
