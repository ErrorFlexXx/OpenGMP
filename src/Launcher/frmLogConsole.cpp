#include "frmLogConsole.h"
#include "ui_frmLogConsole.h"
#include <Shared/Utils/logger.hpp>
#include <string>

using namespace OpenGMP;

FrmLogConsole::FrmLogConsole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmLogConsole)
{
    ui->setupUi(this);
    Log().SetCallbackFunction([=](int type, const std::string &message){
        if(type == Logger::Warning)
            ui->txtLog->setTextColor( QColor( "darkorange" ) );
        else if(type == Logger::Error)
            ui->txtLog->setTextColor( QColor( "red" ) );
        else
            ui->txtLog->setTextColor( QColor( "black" ) );

        ui->txtLog->append( message.c_str() ); //Insert Log Line

        //Scroll to the last message:
        QTextCursor cursor = ui->txtLog->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->txtLog->setTextCursor(cursor);
    });
}

FrmLogConsole::~FrmLogConsole()
{
    Log().ResetCallbackFunction();
    delete ui;
}

void FrmLogConsole::on_cbxLogLevel_currentIndexChanged(int index)
{
    switch(index)
    {
        case Logger::Debug:
        {
            Log() << Logger::Debug;
            LogDebug() << "Switched log level to debug.";
            break;
        }
        case Logger::Info:
        {
            Log() << Logger::Info;
            LogDebug() << "Switched log level to info.";
            break;
        }
        case Logger::Warning:
        {
            Log() << Logger::Warning;
            LogDebug() << "Switched log level to warning.";
            break;
        }
        case Logger::Error:
        {
            Log() << Logger::Error;
            LogDebug() << "Switched log level to error.";
            break;
        }
        default:
        {
            LogWarn() << "Invalid Log Level selection. Selected index out of scope! Log level unchanged!";
            break;
        }
    }
}
