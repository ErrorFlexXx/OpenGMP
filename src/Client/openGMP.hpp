#pragma once

class OGMP
{
public:
    static void Startup();  //!< Initializes OpenGMP
    static void Stop();     //!< Stops the OpenGMP instance (do cleanup..)

private:
    OGMP();                  //!< Object creation not from outside allowed!
    OGMP(const OGMP&);    //!< No Copy allowed!
    
    static bool inited;
};