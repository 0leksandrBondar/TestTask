#pragma once

#include "AbstractImageViewWidget.h"

#include <QPainter>
#include <QPixmap>
#include <QString>

class SourceImageViewWidget final : public AbstractImageViewWidget
{
    Q_OBJECT

public:
    explicit SourceImageViewWidget(QWidget *parent = nullptr);

    void onPathImageLoaded(const QString &path);

signals:
    void sorceImageLoaded(const QPixmap &pixmap);
};