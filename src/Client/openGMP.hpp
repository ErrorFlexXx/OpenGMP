#pragma once

#include <thread>

class OGMP
{
public:
    static OGMP *GetInstance();
    void Stop();                //!< Stops the OpenGMP instance (do cleantup..)

private:
    OGMP();                  //!< Object creation not from outside allowed!
    OGMP(const OGMP&);    //!< No Copy allowed!
    void Init();                //!< Initializes OpenGMP (shall be run in a independent thread)

    static OGMP *m_instance;   //!< Singleton instance of OpenGMP
    std::thread m_worker;         //!< Worker of OpenGMP for further init outside of DllAttach.
};