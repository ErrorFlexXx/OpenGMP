#pragma once

#include "osDetect.h"
#include <string>

#ifdef OS_Windows
    #include <windows.h>
#endif

#ifdef OS_Linux
    #include <stdlib.h> //system(...)
#endif

namespace OpenGMP
{
        enum MessageType
        {
            None,
            Information,
            Question,
            Warning,
            Error,
            MessageTypeCount
        };
        
        enum Result : int
        {
            Ok = 1,
            Cancel = 2,
            Abort = 3,
            Yes = 6,
            No = 7,
            ResultCount
        };
        
        #if defined(OS_Windows)
        /**
         * @brief MessageBox_Win Windows implementation for message boxes.
         * @param title text of the title bar from the testbox.
         * @param message main text of the message box.
         * @param type of the message box (info, question, ...)
         */
        static inline Result MessageBox_Win(const std::string &title, const std::string &message, MessageType type)
        {
            unsigned int mbType;
            switch(type)
            {
                case None:
                {
                    mbType = 0;
                    break;
                }
                case Information:
                {
                    mbType = MB_ICONINFORMATION;
                    break;
                }
                case Question:
                {
                    mbType = MB_ICONQUESTION;
                    break;
                }
                case Warning:
                {
                    mbType = MB_ICONWARNING;
                    break;
                }
                case Error:
                {
                    mbType = MB_ICONERROR;
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
            
            return static_cast<Result>(::MessageBox(NULL, message.c_str(), title.c_str(), mbType));
        }
        #endif
        
        #if defined(OS_Linux)
        /**
         * @brief MessageBox_Linux Linux implementation for message boxes.
         * @param title text of the title bar from the testbox.
         * @param message main text of the message box.
         * @param type of the message box (info, question, ...)
         */
        static inline Result MessageBox_Linux(const std::string &title, const std::string &message, MessageType type)
        {
            std::string call("xmessage -title \"");
            call.append(title);
            call.append("\" ");
            
            switch(type)
            {
                case Warning:
                {
                    call.append("-bg orange -fg yellow ");
                    break;
                }
                case Error:
                {
                    call.append("-bg darkred -fg red ");
                    break;
                }
                case Question:
                {
                    call.append("-buttons Yes,No ");
                    break;
                }
                default:
                {
                    break;
                }
            }
            
            call.append(message);
            
            
            int result = system(call.c_str());
            if(type == Question && result == 101)
                return Yes;
            if(type == Question && result == 102)
                return No;
            return Ok;
        }
        #endif
        
        static inline Result MessageBox(const std::string &title, const std::string &message, MessageType type = None)
        {
            #if defined(OS_Windows)
            return MessageBox_Win(title, message, type);
            #elif defined(OS_Linux)
            return MessageBox_Linux(title, message, type);
            #endif
        }
}