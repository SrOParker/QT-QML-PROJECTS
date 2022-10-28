#include "systeminfo.h"
#ifdef Q_OS_WIN
    #include "systeminfowindows.h"
#elif define Q_OS_LINUX
    #include "systeminfolinux.h"
#elif define Q_OS_MAC
    #include "systeminfomac.h";
#endif

SystemInfo::SystemInfo()
{

}

SystemInfo &SystemInfo::instancia()
{
#ifdef Q_OS_WIN
     static SystemInfoWindows singleton;
#elif define Q_OS_LINUX
     static SystemInfoLinux singleton;
#elif define Q_OS_MAC
     static SystemInfoMac singleton;
#endif

     return singleton;

}

SystemInfo::~SystemInfo()
{

}
