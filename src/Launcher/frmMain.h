#pragma once

#include <Launcher/Systems/serverCommunicator.hpp>
#include <Launcher/Systems/clientStore.hpp>
#include <Launcher/Objects/jsonFile.hpp>
#include <Launcher/Objects/lserver.hpp>
#include <Launcher/frmLogConsole.h>
#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include <list>
#include <mutex>

namespace Ui {
    class FrmMain;
}

class QTreeWidgetItem;
class QLabel;
class QProgressBar;

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

    void StartClient(const OpenGMP::LServer &server);

public slots:
    /**
     * @brief ProgressBegin slot initializing a shown progress.
     * @param text to show initially.
     */
    void ProgressBegin(const QString &text);

    /**
     * @brief ProgressUpdate slot updating a progress visualization on the form.
     * @param progress percentual progress.
     * @param text descriptive text.
     */
    void ProgressUpdate(int progress, const QString &text);

    /**
     * @brief ProgressUpdate updating a progress visualization on the form.
     * @param progress percentual progress.
     */
    void ProgressUpdate(int progress);

    /**
     * @brief ProgressFinished removes the status bar.
     */
    void ProgressFinished();

private slots:
    void on_btnTest_clicked();
    void on_actionExit_triggered();
    void on_actionMainSettings_triggered();

    /**
     * @brief UpdateServerEntry updates the form data of a server entry in the treeView.
     * @param server object data to update with.
     */
    void UpdateServerEntry(const OpenGMP::LServer &server);

    /**
     * @brief UpdateServerEntryNowOnline same as UpdateServerEntry, but with additional tasks.
     *   Updates the local store with new server informations (e.g. Name/Version).
     * @param server
     */
    void UpdateServerEntryNowOnline(const OpenGMP::LServer &server);

    /**
     * @brief UpdateServerEntryNowOffline updates a server entry. Server moved from on-, to offline.
     * @param server entry to update.
     */
    void UpdateServerEntryNowOffline(const OpenGMP::LServer &server);

    void on_actionLog_Console_triggered();

private:
    Ui::FrmMain *ui;
    OpenGMP::ServerCommunicator *serverCommunicatorTask; //!<Task to update all server entries in a loop.
    QThread *serverCommunicator;    //!< Thread to decouple comm. from the ui thread.
    std::string serverListName;     //!< Filename of serverlist.
    FrmLogConsole frmLogConsole;    //!< Log Console window.
    OpenGMP::ClientStore clientStore;   //!< Client store object.
    QThread *clientStoreThread;     //!< Thread to do ui decoupled actions.
    QProgressBar *progressBar;
    QLabel *progressText;
};
