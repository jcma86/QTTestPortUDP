#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "aboutwindow.h"
#include "waveviewerwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMenu *toolsMenu;
    QAction *aboutAct;
    QAction *waveViewerAct;

    AboutWindow *aboutWindow = nullptr;
    WaveViewerWindow *waveViewerWindow = nullptr;

    void createActions();
    void createMenus();
    void createWindows();

    void showAbout();
    void showWaveViewer();
};
#endif // MAINWINDOW_H
