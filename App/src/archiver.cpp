#include "archiver.h"

#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>

Archiver::Archiver(QObject *parent)
    : QObject(parent),
      _selectFileToCompressButton{ new QPushButton(
          QStringLiteral("Select directory to compress")) },
      _selectFileToDecompressButton{ new QPushButton(QStringLiteral("Select file to decompress")) }
{
    setupConnections();
}

void Archiver::showUi(QWidget *parent)
{
    QVBoxLayout *mainVLayout = new QVBoxLayout();
    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    buttonsLayout->addWidget(_selectFileToCompressButton);
    buttonsLayout->addWidget(_selectFileToDecompressButton);

    mainVLayout->addLayout(buttonsLayout);
    parent->setLayout(mainVLayout);
}

void Archiver::setupConnections()
{
    connect(_selectFileToCompressButton, &QPushButton::clicked, this, &Archiver::compressData);
    connect(_selectFileToDecompressButton, &QPushButton::clicked, this, &Archiver::decompressData);
}
void Archiver::compressData()
{
}

void Archiver::decompressData()
{
}
