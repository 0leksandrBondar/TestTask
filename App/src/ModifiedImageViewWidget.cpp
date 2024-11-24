#include "ModifiedImageViewWidget.h"
#include "MainWindow.h"

#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPainter>

ModifiedImageViewWidget::ModifiedImageViewWidget(QWidget *parent) : AbstractImageViewWidget(parent)
{
}

void ModifiedImageViewWidget::setImage(const QPixmap &image)
{
    _image = image;
    _sourceImage = image;
    update();
}

void ModifiedImageViewWidget::onActionChanged(int action)
{
    if (action == static_cast<int>(Action::Default))
    {
        _image = _sourceImage;
        update();
    }

    if (action == static_cast<int>(Action::HorizontalMirror))
        applyMirrorEffect(false);
    if (action == static_cast<int>(Action::VerticalMirror))
        applyMirrorEffect(true);
    if (action == static_cast<int>(Action::Blur))
        applyBlurEffect();
}

void ModifiedImageViewWidget::applyBlurEffect()
{
    if (_image.isNull())
    {
        qWarning() << "Image is null; cannot apply blur effect.";
        return;
    }

    QImage sourceImage = _image.toImage();
    QGraphicsScene scene;
    QGraphicsPixmapItem item(QPixmap::fromImage(sourceImage));

    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect();
    blurEffect->setBlurRadius(10);

    item.setGraphicsEffect(blurEffect);
    scene.addItem(&item);

    QImage resultImage(_image.size(), QImage::Format_ARGB32);
    resultImage.fill(Qt::transparent);

    QPainter painter(&resultImage);
    scene.render(&painter);
    painter.end();

    _image = QPixmap::fromImage(resultImage);
    update();
}

void ModifiedImageViewWidget::applyMirrorEffect(bool verticalMirror)
{
    if (_image.isNull())
    {
        qWarning() << "Image is null; cannot apply mirror effect.";
        return;
    }

    QImage sourceImage = _image.toImage();
    QImage mirroredImage;
    if (verticalMirror)
        mirroredImage = sourceImage.mirrored(false, true); // Vertical flip
    else
        mirroredImage = sourceImage.mirrored(true, false); // Horizontal flip

    _image = QPixmap::fromImage(mirroredImage);
    update();
}
