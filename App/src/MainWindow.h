#pragma once

#include <QMainWindow>

class SourceImageViewWidget;
class ModifiedImageViewWidget;
class QPushButton;
class QGraphicsScene;
class QComboBox;

enum class Action
{
    Default,
    HorizontalMirror,
    VerticalMirror,
    Blur,
};

class MainWindow final : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void setupUi();
    void setupActions();
    void setupConnections();

    void resrtComboBox();

    void onSaveClicked();
    void onOpenFileExplorer();

signals:
    void imagePathLoaded(const QString &path);

private:
    QComboBox *_actionList{ nullptr };
    QWidget *_centralWidget{ nullptr };
    QPushButton *_loadImageButton{ nullptr };
    QPushButton *_saveImageButton{ nullptr };
    SourceImageViewWidget *_sourceImageView{ nullptr };
    ModifiedImageViewWidget *_modifiedImageView{ nullptr };
};