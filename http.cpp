#include "http.h"



Http::Http()
{

}


bool Http::post_sync(QString url, QMap<QString, QString> header, QByteArray &requestData, QByteArray &replyData)
{
    QNetworkAccessManager manager;

    QNetworkRequest request;

    request.setUrl(url);

    QMapIterator<QString,QString> it(header);

    while(it.hasNext())
    {
        it.next();
        request.setRawHeader(it.key().toLatin1(),it.value().toLatin1());
    }


    QNetworkReply * reply = manager.post(request,requestData);
    QEventLoop l;
    connect(reply,&QNetworkReply::finished,&l, &QEventLoop::quit);
    l.exec();               // 死循环

    if(reply != nullptr && reply->error() == QNetworkReply::NoError)
        replyData = reply->readAll();
    else
        return false;
}
