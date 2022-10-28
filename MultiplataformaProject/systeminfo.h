#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QtGlobal>
class SystemInfo
{
public:
    static SystemInfo& instancia();
    virtual ~SystemInfo(); //para redefinir en las hijas (virtual)

    virtual void init() = 0; //para redefinir en las hijas
    // = 0 no hay implementacion de este método en esta clase
    virtual double cpuLoad() = 0; //carga cpu actual
    virtual double memoryUsed() = 0; //memoria utilizandose

protected:
    explicit SystemInfo();
};

#endif // SYSTEMINFO_H
