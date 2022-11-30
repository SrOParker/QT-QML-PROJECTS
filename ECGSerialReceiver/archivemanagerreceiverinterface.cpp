#include "archivemanagerreceiverinterface.h"

ArchiveManagerReceiverInterface::ArchiveManagerReceiverInterface(QObject *parent)
    : ArchiveManagerReceiver{parent}
{

}

float ArchiveManagerReceiverInterface::getDataAt(int p)
{
    return rec.getDataAt(p);
}
