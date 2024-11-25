#pragma once

#include <QObject>

class QWidget;
class QPushButton;

class Archiver : public QObject
{
    Q_OBJECT
public:
    Archiver(QObject *parent = nullptr);

    void showUi(QWidget *parent);

signals:
    void selectFileToCompressClicked();
    void selectFileToDecompressClicked();

private:
    void setupConnections();

    void compressData();
    void decompressData();

private:
    QPushButton *_selectFileToCompressButton;
    QPushButton *_selectFileToDecompressButton;
};
