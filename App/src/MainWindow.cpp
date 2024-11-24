#include "MainWindow.h"

#include "ModifiedImageViewWidget.h"
#include "SourceImageViewWidget.h"

#include <QComboBox>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTemporaryFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _actionList{ new QComboBox() },
      _centralWidget{ new QWidget() },
      _loadImageButton{ new QPushButton(QStringLiteral("Choose an image")) },
      _saveImageButton{ new QPushButton(QStringLiteral("Save the modified image")) },
      _sourceImageView(new SourceImageViewWidget()),
      _modifiedImageView(new ModifiedImageViewWidget())
{
    setupUi();
    setupActions();
    setupConnections();
}

void MainWindow::setupUi()
{
    resize(950, 800);
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
}

void MainWindow::resrtComboBox()
{
    _actionList->setCurrentIndex(0);
}

void MainWindow::onSaveClicked()
{
    // Step 1: Prompt user to select archive save location
    QString archivePath
        = QFileDialog::getSaveFileName(this, QStringLiteral("Select Archive Save Location"),
                                       QDir::homePath(), "Archive Files (*.zip);;All Files (*.*)");

    if (archivePath.isEmpty())
    {
        qDebug() << "Save operation canceled.";
        return;
    }

    // Ensure the file has a .zip extension
    if (!archivePath.endsWith(".zip", Qt::CaseInsensitive))
        archivePath += ".zip";

    // Step 2: Save the Pixmap to a temporary file
    QTemporaryFile tempImageFile;
    if (tempImageFile.open())
    {
        QString tempImagePath = tempImageFile.fileName();
        if (!_modifiedImageView->image().save(tempImagePath, "PNG"))
        {
            QMessageBox::critical(this, "Error", "Failed to save temporary image.");
            return;
        }

        // Step 3: Compress the file into an archive
        QFile archiveFile(archivePath);
        if (archiveFile.open(QIODevice::WriteOnly))
        {
            QDataStream out(&archiveFile);

            QFile imageFile(tempImagePath);
            if (imageFile.open(QIODevice::ReadOnly))
            {
                out << imageFile.readAll(); // Write image data to the archive
                imageFile.close();
                archiveFile.close();

                QMessageBox::information(this, "Success", "Image successfully saved to archive!");
            }
            else
                QMessageBox::critical(this, "Error",
                                      "Failed to open temporary image for compression.");
        }
        else
            QMessageBox::critical(this, "Error", "Failed to create archive file.");
    }
    else
        QMessageBox::critical(this, "Error", "Failed to create temporary file.");
}

void MainWindow::onOpenFileExplorer()
{
    QString path
        = QFileDialog::getOpenFileName(this, QStringLiteral("Choose an image"), QString(),
                                       "Images (*.png *.jpg *.jpeg *.bmp);;All files (*.*)");
    if (!path.isEmpty())
        emit imagePathLoaded(path);
}