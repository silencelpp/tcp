#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectServer_clicked();

    void on_disconnect_clicked();

    void on_send_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *m_tcp;
};
#endif // MAINWINDOW_H
