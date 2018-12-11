#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ctime>

#define Log()      OpenGMP::Logger() //Used for Control commands e.g. Log().EnableLogfile("path.log");
//Actual logging functions:
#define LogDebug() OpenGMP::Logger(__FILE__, __FUNCTION__, __LINE__, OpenGMP::Logger::Debug)
#define LogInfo()  OpenGMP::Logger(__FILE__, __FUNCTION__, __LINE__, OpenGMP::Logger::Info)
#define LogWarn()  OpenGMP::Logger(__FILE__, __FUNCTION__, __LINE__, OpenGMP::Logger::Warning)
#define LogError() OpenGMP::Logger(__FILE__, __FUNCTION__, __LINE__, OpenGMP::Logger::Error)

namespace OpenGMP
{
    /**
     * @brief Logger - header only library class to Log messages of different kinds.
     * @author Christian Löpke <loepke@edfritsch.de>
     */
    class Logger
    {
    public:
        /**
         * @brief MessageType classifier used to differenciate the different log message types.
         */
        enum MessageType : unsigned int
        {
            Debug,      //!< used for messages that shall only be displayed in debug mode.
            Info,       //!< used for unimportant informations.
            Warning,    //!< used for runtime errors, which don't prevent the app from executing.
            Error,      //!< used for runtime errors, that quits the program execution.
            MessageTypeCount //!< used to check, if a message type is valid.            
        };
        
        Logger()
            : Logger("", "", 0, Info)
        {}
        
        Logger(const char *file, const char *function, int line, MessageType type = Info)
            : type(type)
            , file(file)
            , function(function)
            , line(line)
        {}

        /**
         * @brief ~Logger destroys this Logger (Message) instance and triggers message output.
         */
        ~Logger() { Flush(); }
        
        /**
         * @brief EnableLogfile start logging of all messages to a file.
         * @param filepath full path to logfile.
         */
        void EnableLogfile(const char *filepath)
        {
            Flush(MessageTypeCount, filepath);
        }
        
        /**
         * @brief DisableLogfile stops the logging of all messages to a file.
         */
        void DisableLogfile()
        {
            Flush(MessageTypeCount, reinterpret_cast<const char *>(-1));
        }
        
        /**
         * @brief ClearLogfile deletes the current log file and creates a new one.
         */
        void ClearLogfile()
        {
            Flush(MessageTypeCount, reinterpret_cast<const char *>(-2));
        }
        
        /**
         * @brief SetCallbackFunction installs a callback func. that gets called
         *   every time a log message is ready.
         */
        void SetCallbackFunction(std::function<void(const std::string&)> callback)
        {
            Flush(MessageTypeCount, nullptr, &callback);
        }
        
        /**
         * @brief ResetCallbackFunction removes the currently installed callback function.
         */
        void ResetCallbackFunction()
        {
            Flush(MessageTypeCount, nullptr, reinterpret_cast<std::function<void(const std::string&)>*>(-1));
        }
        
        /**
         * @brief operator<< Switch the current log level of the Logger.
         * @param const MessageType obj new log level.
         * @return reference of this logger object.
         */
        inline Logger& operator << (const MessageType obj)
        {
            Flush(obj);
            return *this;
        }

        /**
         * @brief operator<< string stream value processing.
         * @param T template argument.
         * @return reference of this Logger object.
         */
        template<typename T>
        inline Logger& operator << (const T& obj)
        {
            message << obj;
            return *this;
        }
        
    private:
        MessageType type;           //!< Type of this log message
        std::stringstream message;  //!< Text of this log message.
        std::string file;           //!< Name of file, in which this log message has been created.
        std::string function;       //!< Function name in which this log message has been created.
        std::fstream logFile;       //!< Filestream used for log file creation.
        int line;                   //!< Line number inside file, in which this message has been created.
        
        /**
         * @brief GetDecoratedOutput - Builds the final output from type and message.
         * @return the log text.
         */
        std::string GetDecoratedOutput() const
        {
            std::string output, strMessage;
            strMessage.append(message.str());
            if(0 < strMessage.length()) //Do not prepare empty messages.
            {
                switch(type)
                {
                    case Debug:
                    {
                        output.append("[Debug]   ");
                        AddTime(output);
                        output.append(strMessage);
                        break;
                    }
                    case Info:
                    {
                        output.append("[Info]    ");
                        AddTime(output);
                        output.append(strMessage);
                        break;
                    }
                    case Warning:
                    {
                        output.append("[Warning] ");
                        AddTime(output);
                        AddFileLineTrace(output);
                        output.append(strMessage);
                        break;
                    }
                    case Error:
                    {
                        output.append("[Error]   ");
                        AddTime(output);
                        AddFileFunctionLineTrace(output);
                        output.append(strMessage);
                        break;
                    }
                    case MessageTypeCount:
                    { 
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
            return output;
        }
        
        /**
         * @brief AddTime adds a time string to a string var.
         * @return reference of in string.
         */
        std::string &AddTime(std::string &text) const
        {
            std::stringstream timeString;
            auto t  = std::time(nullptr); //Get current time
            auto tm = *std::localtime(&t);//Get local time
            timeString << "[" << std::put_time(&tm, "%H:%M:%S") << "] ";
            text.append(timeString.str());
            return text;
        }
        
        /**
         * @brief AddFileLineTrace adds the filename and codeline to a text var.
         * @return reference of in string.
         */
        std::string &AddFileLineTrace(std::string &text) const
        {
            text.append(file).append(":").append(std::to_string(line)).append(": ");
            return text;
        }
        
        /**
         * @brief AddFileFunctionLineTrace adds the filename, functionname and codeline to a text var.
         * @return reference of in string.
         */
        std::string &AddFileFunctionLineTrace(std::string &text) const
        {
            text.append(file).append(":").append(function).append(":").append(std::to_string(line)).append(": ");
            return text;
        }
        
        /**
         * @brief Flush is the function, that actually outputs the log message.
         * @param switchLogLevel used to change the current log level of the Logger.
         * @param setLogFilepath used to set the log filepath and used as control var (clear log, disable, ...)
         */
        void Flush(MessageType switchLogLevel = MessageTypeCount,
                   const char *setLogFilepath = nullptr,
                   std::function<void(const std::string&)> *setCallback = nullptr)
        {
            //Static class arguments (in header only library style)
            static MessageType logLevel = Warning;  //Default: Only output bad news.
            static bool logToFile = false;          //Default: File log disabled
            static std::string logFilepath;         //Default: No file set.
            static std::function<void(const std::string&)> callback;

            if(switchLogLevel < MessageTypeCount) //Switch requested and valid level ?
            {
                logLevel = switchLogLevel;
            }
            else if(setLogFilepath) //Switch logfile ?
            {
                if(setLogFilepath == reinterpret_cast<const char*>(-1))
                    logToFile = false;
                else if(setLogFilepath == reinterpret_cast<const char*>(-2))
                {
                    if(logToFile)
                    {
                        logFile.open(logFilepath.c_str(), std::fstream::out | std::fstream::trunc);
                        if(logFile.good())
                            logFile.close();
                        else
                            LogWarn() << "Cannot clear log file: " << logFilepath;
                    }
                    else
                        LogWarn() << "ClearLogfile called, but EnableLogfile was never called!";
                }
                else
                {
                    logToFile = true;
                    logFilepath = setLogFilepath;
                }
            }
            else if(setCallback) //Set callback function ?
            {
                if(setCallback == reinterpret_cast<std::function<void(const std::string&)>*>(-1)) //Reset ?
                    callback = [] (const std::string&) {};
                else
                    callback = *setCallback;
            }
            else if(logLevel <= type)
            {
                std::string output = GetDecoratedOutput();
                if(0 < output.length()) //Do not output empty messages
                {
                    //Log callback task:
                    if(callback)
                        callback(output);
                    //Log to std output:
                    if(type >= Warning)
                        std::cerr << output << std::endl;
                    else
                        std::cout << output << std::endl;
                    //Log to file:
                    if(logToFile)
                    {
                        logFile.open(logFilepath.c_str(), std::fstream::out | std::fstream::app);
                        if(logFile.good()) //Successfully opened ?
                        {
                            logFile << output << std::endl;
                            logFile.close();
                        }
                        else
                        {
                            LogWarn() << "Cannot write to logfile: " << logFilepath;
                        }
                    }
                }
            }
        }
    }; //class
} //namespace