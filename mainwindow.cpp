#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QByteArray>
#include <QRandomGenerator>
#include <QString>
#include <QTextBrowser>
#include <QTextCodec>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //    QTextCodec* codec = QTextCodec::codecForName("utf8");
    //    QTextCodec::setCodecForLocale(codec);
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::replyFinished);
    //    void (MainWindow::*f)() = &MainWindow::test_service1;
    funcs.push_back(&MainWindow::test_service1);
    funcs.push_back(&MainWindow::test_machineWSService);
}

void MainWindow::test_machineWSService()
{
    QNetworkRequest req(QUrl("http://218.26.30.70:9090/WorkHelper/ws/machineWSService"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, QString("text/xml;charset=utf-8"));
    QString http_body = QString::fromUtf8(u8"<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:mac=\"http://machine.webService.workHelper.cnki.com/\">"
                                          "<soapenv:Header/>"
                                          "<soapenv:Body>"
                                          "<mac:GetLineServerList>"
                                          "<outUse>1</outUse>"
                                          "</mac:GetLineServerList>"
                                          "</soapenv:Body>"
                                          "</soapenv:Envelope>");
    manager->post(req, http_body.toUtf8());
}

void MainWindow::test_service1()
{
    QNetworkRequest my_req(QUrl("http://218.26.30.70:81/WebServiceDemo/Service1.asmx"));
    my_req.setHeader(QNetworkRequest::ContentTypeHeader, QString("text/xml;charset=utf-8"));
    QString soap_xml = QString::fromUtf8(u8"<?xml version=\"1.0\" encoding=\"utf-8\"?><soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soapenc=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:tns=\"http://Fantasy/WebServiceDemo/\" xmlns:types=\"http://Fantasy/WebServiceDemo/encodedTypes\" xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">  <soap:Body soap:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">    <tns:executeSql>      <serverInfo xsi:type=\"xsd:string\">192.168.3.61@ts_tools_jsdj@ts2016_new@图书论文2016@</serverInfo>      <sSql xsi:type=\"xsd:string\">select 出版者,书名,副书名,分辑,丛书名,ISBN,作者,出版日期,定价,格式,版权页,封面,其它,备注,作品语种,文件状态,处理状态,文件个数,编号,到岗时间,授权方,被授权方,授权起始时,授权结束时,文件名,副丛书名,丛书卷号,丛书作者,版本说明,载体类型,著作类型,适用读者,用途,订单年 from dbo.V_接收登记_详细信息  where 批次号 = 'xk210723'</sSql>    </tns:executeSql>  </soap:Body></soap:Envelope>");
    //    std::wstring soap_xml_w = L"<?xml version=\"1.0\" encoding=\"utf-8\"?><soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soapenc=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:tns=\"http://Fantasy/WebServiceDemo/\" xmlns:types=\"http://Fantasy/WebServiceDemo/encodedTypes\" xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">  <soap:Body soap:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">    <tns:executeSql>      <serverInfo xsi:type=\"xsd:string\">%1</serverInfo>      <sSql xsi:type=\"xsd:string\">%2</sSql>    </tns:executeSql>  </soap:Body></soap:Envelope>";
    //    QByteArray data = QByteArray((char*)soap_xml_w.c_str(), soap_xml_w.size() * 2);
    manager->post(my_req, soap_xml.toUtf8());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply* reply)
{
    QTextCodec* codec = QTextCodec::codecForName("utf8");
    //    QString all = codec->toUnicode(reply->readAll());
    auto text = new QTextBrowser(ui->tabWidget);
    text->setText(reply->readAll());
    ui->tabWidget->addTab(text, "TAB_" + QString::number(ui->tabWidget->count()));
    ui->tabWidget->setCurrentWidget(text);

    //    ui->textBrowser->setText(reply->readAll());
    reply->deleteLater();
}

void MainWindow::on_actionrun_service_triggered()
{
    auto index = QRandomGenerator::global()->QRandomGenerator::bounded(0, 2);
    qDebug() << index;
    (this->*funcs.at(index))();
}
