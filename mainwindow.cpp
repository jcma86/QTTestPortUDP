#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();
    createWindows();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Creates the items for the Tools menu.
void MainWindow::createActions()
{
    waveViewerAct = new QAction("Wave Viewer", this);
    connect(waveViewerAct, &QAction::triggered, this, &MainWindow::showWaveViewer);

    aboutAct = new QAction("About...", this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::showAbout);
}

// Creates the menu "Tools"
void MainWindow::createMenus()
{
    toolsMenu = menuBar()->addMenu("Tools");
    toolsMenu->addAction(waveViewerAct);
    toolsMenu->addAction(aboutAct);
}

// An alternative is to create the window when
// the user selects the option from the Tools menu.
void MainWindow::createWindows()
{
    waveViewerWindow = new WaveViewerWindow(ui->mdiArea);
    aboutWindow = new AboutWindow(ui->mdiArea);

    waveViewerWindow->hide();
    aboutWindow->hide();
}

void MainWindow::showAbout()
{
    aboutWindow->show();
}

void MainWindow::showWaveViewer()
{
    waveViewerWindow->show();
}
