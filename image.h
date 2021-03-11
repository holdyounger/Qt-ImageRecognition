#ifndef IMAGE_H
#define IMAGE_H


#include <QBuffer>
#include <QByteArray>
#include <QString>
#include <QImage>
#include <QTextCodec>
class Image
{
public:
    Image();
    static QByteArray imgToBase64(QString imgPath);
    void urlEncode();


};

#endif // IMAGE_H
