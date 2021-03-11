#ifndef HTTP_H
#define HTTP_H
#include <QString>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>



class Http : public QObject
{
    Q_OBJECT
public:
    Http();

   static bool post_sync(QString url,QMap<QString,QString> header,QByteArray &requestData,QByteArray& replyData);

};

#endif // HTTP_H
