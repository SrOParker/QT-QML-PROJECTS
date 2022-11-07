#ifndef CARGADORIMAGENES_H
#define CARGADORIMAGENES_H

#include <QQuickImageProvider>

class CargadorImagenes : public QQuickImageProvider
{
public:
    CargadorImagenes();

    // QQuickImageProvider interface
public:
    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
};

#endif // CARGADORIMAGENES_H
