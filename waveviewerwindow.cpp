#include "waveviewerwindow.h"
#include "ui_waveviewerwindow.h"

WaveViewerWindow::WaveViewerWindow(QWidget *parent)
    : QMdiSubWindow(parent)
    , ui(new Ui::WaveViewerWindow)
{
    ui->setupUi(this);
    this->setParent(parent);

    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    this->setWindowFlag(Qt::WindowMinimizeButtonHint, false);
    this->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);

    connect(ui->chart, SIGNAL(mousePress(QMouseEvent*)), SLOT(mouseMoveEvent(QMouseEvent*)));

    configureChartArea();
    configureSocket();
}

WaveViewerWindow::~WaveViewerWindow()
{
    delete ui;
}

void WaveViewerWindow::configureChartArea()
{
    ui->chart->addGraph();
    ui->chart->addGraph();
    ui->chart->legend->setVisible(true);
    ui->chart->graph(0)->setName("min: 0, max: 0");
    ui->chart->graph(1)->setName("median: 0");

    QPen pen0;
    pen0.setStyle(Qt::SolidLine);
    pen0.setWidth(1);
    pen0.setColor(QColor(0,0,255));
    ui->chart->graph(0)->setPen(QPen(Qt::blue));

    QPen pen1;
    pen1.setStyle(Qt::DashLine);
    pen1.setWidth(2);
    pen1.setColor(QColor(250,0,0));
    ui->chart->graph(1)->setPen(pen1);
}

void WaveViewerWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x = ui->chart->xAxis->pixelToCoord(event->pos().x());
    int y = ui->chart->yAxis->pixelToCoord(event->pos().y());

    setToolTip(QString("X: %1\nY: %2").arg(x).arg(y));
}

void WaveViewerWindow::configureSocket()
{
    // Configures the UDP socket where we will receive data.
    socket = new QUdpSocket(this);

    processPendingDatagrams();
    connect(socket, &QUdpSocket::readyRead, this, &WaveViewerWindow::processPendingDatagrams);

    // Send socket to thread to prevent blocking UI.
    socketThread = new QThread(this);
    socket->moveToThread(socketThread);
}

// Method triggered when we receive data
void WaveViewerWindow::processPendingDatagrams()
{
    QHostAddress sender;
    quint16 port;
    while (socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(), &sender, &port);

        plotDatagram(&datagram);
    }
}

// Method to process the datagram and plot it.
void WaveViewerWindow::plotDatagram(QByteArray *datagram)
{
    if (!datagram) return;

    // We can use const values because we know the amount of bytes
    // that we should receive. But in this case just as a way to make
    // it a little bit more generic.
    int nBytes = sizeof(int16_t);
    int nSamples = datagram->length() / nBytes;

    QVector<double> x(nSamples), y(nSamples);
    int16_t *tmp = new int16_t[nSamples];
    int16_t min = INT16_MAX;
    int16_t max = -INT16_MAX;
    for(qsizetype i=0; i<nSamples; i+=1)
    {
        int16_t v = (int16_t)datagram->at(i * nBytes);
        min = v < min ? v : min;
        max = v > max ? v : max;

        // Adding the points to plot
        x[i] = i;
        y[i] = (double)v;
        tmp[i] = v;
    }

    double median = Statistics::findMedian2(tmp, nSamples);
    delete [] tmp;

    QVector<double> x1(2), y1(2);
    x1[0] = 0;
    x1[1] = nSamples - 1;
    y1[0] = median;
    y1[1] = median;

    ui->chart->graph(0)->setData(x, y);
    ui->chart->graph(0)->rescaleAxes();
    ui->chart->graph(1)->setData(x1, y1);

    ui->chart->graph(0)->setName("min: " + QString::number(min) + ", max: " + QString::number(max));
    ui->chart->graph(1)->setName("median: " + QString::number(median));
    ui->chart->replot();
}

void WaveViewerWindow::on_pushButton_clicked(bool checked)
{
    if (checked)
    {
        // An alternative to 'bind' is 'connectToHost' in case host is remote.
        socket->bind(QHostAddress::LocalHost, port);
        ui->pushButton->setText("Stop");
    }
    else
    {
        socket->close();
        ui->pushButton->setText("Start");
    }
}
