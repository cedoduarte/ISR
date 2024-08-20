#include "htmldownloader.h"
#include "logger.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QNetworkRequest>

HtmlDownloader::HtmlDownloader(QObject *parent)
{
    m_http = new QNetworkAccessManager(this);
    connect(m_http, &QNetworkAccessManager::finished, this, &HtmlDownloader::downloadFinished);
}

HtmlDownloader::~HtmlDownloader()
{
}

void HtmlDownloader::setUrl(const QString &url)
{
    m_url = url;
}

QString HtmlDownloader::url() const
{
    return m_url;
}

QString HtmlDownloader::document() const
{
    return m_document;
}

void HtmlDownloader::download()
{
    m_http->get(QNetworkRequest(QUrl(m_url)));
}

void HtmlDownloader::downloadFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        Logger::log(reply->errorString());
        return;
    }
    m_document = QString::fromUtf8(reply->readAll());
    emit finished();
}
