#include "util.h"

#include <QUrl>

bool IsrUtil::isValidUrl(const QString &url)
{
    QUrl urlObject(url);
    return urlObject.isValid() && urlObject.scheme() != "";
}
