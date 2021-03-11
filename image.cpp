#include "image.h"

Image::Image()
{



}

QByteArray Image::imgToBase64(QString imgPath)
{
    QImage img(imgPath);
    QByteArray ba;
    QBuffer buf(&ba);                   // 用QByteArray构造QBuffer
    buf.open(QIODevice::WriteOnly);
    img.save(&buf,"jpg");               // 把img写入QBuffer
    QByteArray base64 = ba.toBase64();  // 对图片做Base64编码（不包含编码头）

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QByteArray imgData = codec->fromUnicode(base64).toPercentEncoding();

    ////////////////////////////////////////////
    //下边一个关于toPercentEncoding()的演示代码
    /*
    QByteArray text = {" hello world "};
    QByteArray baa = text.toPercentEncoding("e","d");
    qDebug(baa.constData());
    */
    ////////////////////////////////////////////
    return imgData;

}

void Image::urlEncode()
{

}
