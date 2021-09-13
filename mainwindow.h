#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QtNetwork/QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void test_machineWSService();
    void test_service1();
    ~MainWindow();

private slots:
    void replyFinished(QNetworkReply*);

    void on_actionrun_service_triggered();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* manager;
    QVector<void (MainWindow::*)()> funcs;
};
#endif // MAINWINDOW_H
