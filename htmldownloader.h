#ifndef HTMLDOWNLOADER_H
#define HTMLDOWNLOADER_H

#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class HtmlDownloader : public QObject
{
    Q_OBJECT
public:
    HtmlDownloader(QObject *parent = nullptr);
    virtual ~HtmlDownloader();
    void setUrl(const QString &url);
    QString url() const;
    QString document() const;
    void download();
signals:
    void finished();
private slots:
    void downloadFinished(QNetworkReply *reply);
private:
    QString m_url;
    QString m_document;
    QNetworkAccessManager *m_http;
};

#endif // HTMLDOWNLOADER_H
