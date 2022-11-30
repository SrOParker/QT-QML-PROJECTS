#ifndef ARCHIVEMANAGERRECEIVERINTERFACE_H
#define ARCHIVEMANAGERRECEIVERINTERFACE_H

#include <QObject>
#include "archivemanagerreceiver.h"
class ArchiveManagerReceiverInterface : public ArchiveManagerReceiver
{
    Q_OBJECT
public:
    explicit ArchiveManagerReceiverInterface(QObject *parent = nullptr);
    Q_INVOKABLE float getDataAt(int p);

private:
    ArchiveManagerReceiver rec;

};

#endif // ARCHIVEMANAGERRECEIVERINTERFACE_H
