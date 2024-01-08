#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("tcp Server");
    m_server = new QTcpServer(this);
    //检查是否有新的连接
    connect(m_server,&QTcpServer::newConnection,this,[=](){
        m_socket = m_server->nextPendingConnection();
        ui->record->append("成功与客户端建立连接");
        //检查是否有客户端数据
        connect(m_socket,&QTcpSocket::readyRead,this,[=](){
            QString revMessage = m_socket->readAll();
            ui->record->append("客户端：" + revMessage);
        });
        connect(m_socket,&QTcpSocket::disconnected,this,[=](){
            ui->record->append("客户端已经断开了连接...");
            m_socket->deleteLater();
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startServer_clicked()
{
    unsigned short port = ui->port->text().toInt();
    m_server->listen(QHostAddress::Any,port);
    ui->startServer->setEnabled(false);
}


void MainWindow::on_send_clicked()
{
    QString sendMsg = ui->sendMessage->toPlainText();
    m_socket->write(sendMsg.toUtf8());
    ui->record->append("服务端：" + sendMsg);
    ui->sendMessage->clear();
}

