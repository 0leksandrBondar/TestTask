#pragma once

#include "AbstractImageViewWidget.h"

class ModifiedImageViewWidget final : public AbstractImageViewWidget
{
    Q_OBJECT

public:
    explicit ModifiedImageViewWidget(QWidget *parent = nullptr);

    void setImage(const QPixmap &image);

    void onActionChanged(int action);

private:
    void applyBlurEffect();
    void applyMirrorEffect(bool verticalMirror);
};
