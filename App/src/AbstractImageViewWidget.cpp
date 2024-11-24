#include "AbstractImageViewWidget.h"
#include <QPainter>

AbstractImageViewWidget::AbstractImageViewWidget(QWidget *parent) : QWidget(parent)
{
}

QPixmap AbstractImageViewWidget::image()
{
    return _image;
}

void AbstractImageViewWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    if (!_image.isNull())
    {
        // Scale the image to fit the widget's size
        QPixmap scaledImage = _image.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        int x = (width() - scaledImage.width()) / 2;
        int y = (height() - scaledImage.height()) / 2;
        painter.drawPixmap(x, y, scaledImage);
    }
    else
    {
        painter.drawText(rect(), Qt::AlignCenter, "Load an image");
    }
}
