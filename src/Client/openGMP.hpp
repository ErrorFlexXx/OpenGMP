#pragma once

#include <thread>

class OpenGMP
{
public:
    static OpenGMP *GetInstance();
    void Stop();                //!< Stops the OpenGMP instance (do cleantup..)

private:
    OpenGMP();                  //!< Object creation not from outside allowed!
    OpenGMP(const OpenGMP&);    //!< No Copy allowed!
    void Init();                //!< Initializes OpenGMP (shall be run in a independent thread)

    static OpenGMP *m_instance;   //!< Singleton instance of OpenGMP
    std::thread m_worker;         //!< Worker of OpenGMP for further init outside of DllAttach.
};