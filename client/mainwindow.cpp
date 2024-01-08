#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("TCP - 客户端");
    m_tcp = new QTcpSocket(this);
    //检查服务器是否回复数据
    connect(m_tcp,&QTcpSocket::readyRead,this,[=](){
        // 接收服务器发送的数据
        QByteArray recvMsg = m_tcp->readAll();
        ui->record->append("服务器Say: " + recvMsg);
    });

    //检查服务器是否连接成功
    connect(m_tcp,&QTcpSocket::connected,this,[=](){
        ui->record->append("服务器连接成功");
    });

    //检查服务器是否断开成功
    connect(m_tcp, &QTcpSocket::disconnected, this, [=]()
    {
        ui->record->append("服务器已经断开了连接, ...");
        ui->connectServer->setEnabled(true);
        ui->disconnect->setEnabled(false);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connectServer_clicked()
{
    QString ip = ui->address->text();
    unsigned short port = ui->port->text().toInt();
    m_tcp->connectToHost(QHostAddress(ip),port);
    ui->connectServer->setEnabled(false);
    ui->disconnect->setEnabled(true);
}


void MainWindow::on_disconnect_clicked()
{
    m_tcp->close();
    ui->connectServer->setEnabled(true);
    ui->disconnect->setEnabled(false);

}


void MainWindow::on_send_clicked()
{
    QString sendMsg = ui->sendMsg->toPlainText();
    m_tcp->write(sendMsg.toUtf8());
    ui->record->append("客户端：" + sendMsg);
    ui->sendMsg->clear();
}

