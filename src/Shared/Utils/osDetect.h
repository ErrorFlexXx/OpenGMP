#if defined(_WIN32) || defined(WIN32) //Windows os ?
    #define OS_Windows
#elif defined(__unix__) || defined(__linux__)
    #define OS_Linux
#endif
