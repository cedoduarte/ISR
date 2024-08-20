#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "htmldownloader.h"
#include "util.h"
#include "logger.h"

#include <QDebug>
#include <QMessageBox>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_downloader = new HtmlDownloader(this);
    connect(m_downloader, &HtmlDownloader::finished, this, &MainWindow::downloadFinished);

    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::downloadFinished()
{
    Logger::log(m_downloader->document());
    QMessageBox::information(this, "OK", "OK");
}

void MainWindow::on_btnDownload_clicked()
{
    QString url = ui->txtUrl->text();
    if (!IsrUtil::isValidUrl(url))
    {
        QMessageBox::critical(this, "Error", "Introduce una URL válida");
        return;
    }
    m_downloader->setUrl(url);
    m_downloader->download();
}

void MainWindow::loadSettings()
{
    QSettings settings;
    settings.beginGroup("settings");
    ui->txtUrl->setText(settings.value("url", "").toString());
    ui->txtIncome->setText(settings.value("income", "0.0").toString());
    ui->txtInferiorLimit->setText(settings.value("inferiorLimit", "0.0").toString());
    ui->txtSuperiorLimit->setText(settings.value("superiorLimit", "0.0").toString());
    ui->txtFixedQuote->setText(settings.value("fixedQuote", "0.0").toString());
    ui->txtPercentage->setText(settings.value("percentage", "0.0").toString());
    settings.endGroup();
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.beginGroup("settings");
    settings.setValue("url", ui->txtUrl->text());
    settings.setValue("income", ui->txtIncome->text());
    settings.setValue("inferiorLimit", ui->txtInferiorLimit->text());
    settings.setValue("superiorLimit", ui->txtSuperiorLimit->text());
    settings.setValue("fixedQuote", ui->txtFixedQuote->text());
    settings.setValue("percentage", ui->txtPercentage->text());
    settings.endGroup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::on_btnCalculateIsr_clicked()
{
    double income = ui->txtIncome->text().toDouble();
    double inferiorLimit = ui->txtInferiorLimit->text().toDouble();
    //double superiorLimit = ui->txtSuperiorLimit->text().toDouble();
    double fixedQuote = ui->txtFixedQuote->text().toDouble();
    double percentage = ui->txtPercentage->text().toDouble();
    double isr = (income - inferiorLimit) * percentage / 100.0 + fixedQuote;
    double netIncome = income - isr;
    ui->txtIsrResult->setText(QString::number(isr));
    ui->txtNetIncome->setText(QString::number(netIncome));
}

