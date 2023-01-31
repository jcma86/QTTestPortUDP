#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent)
    : QMdiSubWindow(parent)
    , ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    this->setParent(parent);
    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    this->setWindowFlag(Qt::WindowMinimizeButtonHint, false);
    this->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
