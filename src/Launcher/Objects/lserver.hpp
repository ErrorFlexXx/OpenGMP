#pragma once

#include <Shared/Objects/server.hpp>
#include <QString>
#include <QMetaType> //For handover signal -> slot from different threads.

class QTreeWidgetItem; //Forward decl.

namespace OpenGMP
{
    /**
     * @brief The LServer class is a specialization of the Shared Server object.
     */
    class LServer : public Server
    {
    public:
        enum UiListColumns
        {
            ServernameCol = 0,
            HostnameCol,
            PortCol,
            PlayerCol,
            PingCol,
            Max
        }; //!< Column indices of the treeWidget on frmMain.

        LServer();

        QTreeWidgetItem *treeItem;  //!< tree widget item, if any.
        QString playerInfo;         //!< player text.
        QString messageInfo;        //!< message text.
        QString pingInfo;           //!< ping text.
    };
}
//Make this class queueable between threads.
Q_DECLARE_METATYPE(OpenGMP::LServer)

