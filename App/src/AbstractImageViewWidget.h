#pragma once

#include <QPixmap>
#include <QWidget>

class AbstractImageViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractImageViewWidget(QWidget *parent = nullptr);
    [[nodiscard]] QPixmap image();

protected:
    void paintEvent(QPaintEvent *event) override;

    QPixmap _image;
    QPixmap _sourceImage;
};
