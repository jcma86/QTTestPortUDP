#ifndef WAVEVIEWERWINDOW_H
#define WAVEVIEWERWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QUdpSocket>

#include "statistics.h"

namespace Ui { class WaveViewerWindow; }

class WaveViewerWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit WaveViewerWindow(QWidget *parent = 0);
    ~WaveViewerWindow();

private slots:
    void mouseMoveEvent(QMouseEvent *event);
    void on_pushButton_clicked(bool checked);

private:
    Ui::WaveViewerWindow *ui;

    QUdpSocket *socket;
    quint16 port = 10002;

    void configureChartArea();
    void configureSocket();
    void processPendingDatagrams();

    void plotDatagram(QByteArray* datagram);
};

#endif // WAVEVIEWER_H
