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

    /**
     * @brief StartClient signal, that starts a client. Normally linked to ClientStore slot start.
     * @param server to start a client for.
     */
    void StartClient(const OpenGMP::LServer &server);

private slots:

    void on_btnTest_clicked();

    /**
     * @brief StartSelectedClient slot to start a selected client (via contextSelectedItem ptr var.)
     */
    void StartSelectedClient();

    /**
     * @brief customMenuRequested slot for the context menu of the tree widget.
     * @param pos that was clicked at.
     */
    void CustomMenuRequested(QPoint pos);

    /**
     * @brief TreeWidgetItemDoubleClicked slot for tree widget item double clicked.
     * @param item that has been double clicked.
     * @param column. Unused.
     */
    void TreeWidgetItemDoubleClicked(QTreeWidgetItem *item, int column);

    /******************************************
     * Server Communicator update slots:
     ******************************************/
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

    /******************************************
     * Client store progress status bar slots:
     ******************************************/
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

    /*****************
     * Menu bar slots:
     *****************/
    /**
     * @brief on_actionLog_Console_triggered Menu entry opening the log console.
     */
    void on_actionLog_Console_triggered();

    /**
     * @brief on_actionExit_triggered Menu entry closing the application.
     */
    void on_actionExit_triggered();

    /**
     * @brief on_actionMainSettings_triggered Menu entry opening the main settings dialog.
     */
    void on_actionMainSettings_triggered();

private:
    Ui::FrmMain *ui;
    OpenGMP::ServerCommunicator *serverCommunicatorTask; //!<Task to update all server entries in a loop.
    QThread *serverCommunicator;    //!< Thread to decouple comm. from the ui thread.
    std::string serverListName;     //!< Filename of serverlist.
    FrmLogConsole frmLogConsole;    //!< Log Console window.
    OpenGMP::ClientStore clientStore;   //!< Client store object.
    QThread *clientStoreThread;     //!< Thread to do ui decoupled actions.
    QProgressBar *progressBar;      //!< Progressbar located in the status bar.
    QLabel *progressText;           //!< Text shown in the status bar.
    QTreeWidgetItem *contextSelectedItem; //!< Currently selected tree item, if any.

    /**
     * @brief SetupServerCommunicator setup of signal/slots for server communicator thread.
     *   Does start the actual thread, too.
     */
    void SetupServerCommunicator();

    /**
     * @brief SetupClientStore setup of signal/slots for the client store thread.
     *   Does start the actual thread, too.
     */
    void SetupClientStore();

    /**
     * @brief SetupTreeViewActions setup of the context menu and double click handler for the serverlist tree view.
     */
    void SetupTreeViewActions();
};
