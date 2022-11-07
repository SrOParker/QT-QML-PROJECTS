#include "cargadorimagenes.h"

CargadorImagenes::CargadorImagenes() : QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

QPixmap CargadorImagenes::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QPixmap pixmap(id);
    if (size){
        *size = pixmap.size();
    }
    return pixmap;
}
