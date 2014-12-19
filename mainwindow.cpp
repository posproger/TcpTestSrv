#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");

    m_core = new MTestCore();
    m_core->moveToThread(m_core);
    //connect(m_core,SIGNAL(),this,SLOT());
    connect(this,SIGNAL(checkStatistics()),m_core,SLOT(checkStatisticsSlot()));
    m_core->start();

    connect(ui->pbStart,SIGNAL(clicked()),this,SLOT(checkStatisticsSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkStatisticsSlot(void) {
    emit checkStatistics();
}

