#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class HtmlDownloader;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void downloadFinished();
    void on_btnDownload_clicked();
    void on_btnCalculateIsr_clicked();
private:
    void loadSettings();
    void saveSettings();

    Ui::MainWindow *ui;
    HtmlDownloader *m_downloader;
};

#endif // MAINWINDOW_H
