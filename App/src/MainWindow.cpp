#include "MainWindow.h"

#include "ModifiedImageViewWidget.h"
#include "SourceImageViewWidget.h"
#include "archiver.h"

#include <QComboBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _actionList{ new QComboBox() },
      _centralWidget{ new QWidget() },
      _loadImageButton{ new QPushButton(QStringLiteral("Choose an image")) },
      _saveImageButton{ new QPushButton(QStringLiteral("Save the modified image")) },
      _imageProcessingButton{ new QPushButton(QStringLiteral("Image processing task")) },
      _compressDecompressButton{ new QPushButton(QStringLiteral("Compress/Decompress task")) },
      _archivator{ new Archiver(this) },
      _sourceImageView(new SourceImageViewWidget()),
      _modifiedImageView(new ModifiedImageViewWidget())
{
    resize(950, 800);
    setCentralWidget(_centralWidget);

    showMenuView();
    setupActions();
    setupConnections();
}

void MainWindow::setupActions()
{
    _actionList->addItem(QStringLiteral("Default"), static_cast<int>(Action::Default));
    _actionList->addItem(QStringLiteral("HMirror"), static_cast<int>(Action::HorizontalMirror));
    _actionList->addItem(QStringLiteral("VMirror"), static_cast<int>(Action::HorizontalMirror));
    _actionList->addItem(QStringLiteral("Blur"), static_cast<int>(Action::Blur));
}

void MainWindow::setupConnections()
{
    connect(_loadImageButton, &QPushButton::clicked, this, &MainWindow::onOpenFileExplorer);
    connect(this, &MainWindow::imagePathLoaded, _sourceImageView,
            &SourceImageViewWidget::onPathImageLoaded);
    connect(this, &MainWindow::imagePathLoaded, this, &MainWindow::resrtComboBox);
    connect(_sourceImageView, &SourceImageViewWidget::sorceImageLoaded, _modifiedImageView,
            &ModifiedImageViewWidget::setImage);
    connect(_actionList, &QComboBox::currentIndexChanged, _modifiedImageView,
            &ModifiedImageViewWidget::onActionChanged);
    connect(_saveImageButton, &QPushButton::clicked, this, &MainWindow::onSaveClicked);
    connect(_imageProcessingButton, &QPushButton::clicked, this,
            &MainWindow::showImageProcessingView);
    connect(_compressDecompressButton, &QPushButton::clicked, this,
            &MainWindow::showCompressDecompressView);
}

void MainWindow::showMenuView()
{
    QVBoxLayout *mainVLayout = new QVBoxLayout();
    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    buttonsLayout->addWidget(_imageProcessingButton);
    buttonsLayout->addWidget(_compressDecompressButton);

    mainVLayout->addLayout(buttonsLayout);
    _centralWidget->setLayout(mainVLayout);
}

void MainWindow::showImageProcessingView()
{
    // TODO: TBD
    _centralWidget = new QWidget();
    setCentralWidget(_centralWidget);

    QVBoxLayout *mainVLayout = new QVBoxLayout();

    QHBoxLayout *viewImageLayout = new QHBoxLayout();
    QHBoxLayout *controlLayout = new QHBoxLayout();

    viewImageLayout->addWidget(_sourceImageView);
    viewImageLayout->addWidget(_modifiedImageView);

    controlLayout->addWidget(_loadImageButton);
    controlLayout->addWidget(_saveImageButton);
    controlLayout->addWidget(_actionList);

    mainVLayout->addLayout(viewImageLayout);
    mainVLayout->addLayout(controlLayout);
    _centralWidget->setLayout(mainVLayout);
}

void MainWindow::showCompressDecompressView()
{
    // TODO: TBD
    _centralWidget = new QWidget();
    setCentralWidget(_centralWidget);

    _archivator->showUi(_centralWidget);
}

void MainWindow::resrtComboBox()
{
    _actionList->setCurrentIndex(0);
}

void MainWindow::onSaveClicked()
{
    auto pixMap = _modifiedImageView->image();

    if (pixMap.isNull())
    {
        QMessageBox::warning(this, "Error", "Image is empty!");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this, "Save image", QDir::homePath(),
                                                    "Image (*.png *.jpg *.bmp)");

    if (filePath.isEmpty())
        return;

    if (!pixMap.save(filePath))
        QMessageBox::critical(this, "Error", "Failed to save image.");
    else
        QMessageBox::information(this, "Success", "Image saved successfully.");
}

void MainWindow::onOpenFileExplorer()
{
    QString path
        = QFileDialog::getOpenFileName(this, QStringLiteral("Choose an image"), QString(),
                                       "Images (*.png *.jpg *.jpeg *.bmp);;All files (*.*)");
    if (!path.isEmpty())
        emit imagePathLoaded(path);
}
