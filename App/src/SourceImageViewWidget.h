#pragma once

#include "AbstractImageViewWidget.h"

class SourceImageViewWidget final : public AbstractImageViewWidget
{
    Q_OBJECT

public:
    explicit SourceImageViewWidget(QWidget *parent = nullptr);

    void onPathImageLoaded(const QString &path);

signals:
    void sorceImageLoaded(const QPixmap &pixmap);
};
