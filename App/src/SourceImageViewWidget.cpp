#include "SourceImageViewWidget.h"

SourceImageViewWidget::SourceImageViewWidget(QWidget *parent) : AbstractImageViewWidget(parent)
{
}

void SourceImageViewWidget::onPathImageLoaded(const QString &path)
{
    _image = QPixmap(path);

    if (_image.isNull())
    {
        qWarning("Failed to load image from path: %s", qPrintable(path));
        return;
    }

    emit sorceImageLoaded(_image);
    update();
}