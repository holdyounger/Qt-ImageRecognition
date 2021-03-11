#include "mainwindow.h"

#include <QApplication>
#include <QProcess>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QProcess p(nullptr);

    // 获取项目工作路径
    QString curPath = QApplication::applicationDirPath();
    QStringList pathList = curPath.split('/');
    QString workPath;
    for (auto i = 0; i < pathList.size() - 1;i++)
        workPath += (pathList[i] + '/');
    workPath += "Image_recognition_demo0311/setting/";


    p.setWorkingDirectory(workPath);
    QString command = workPath + "autoHooks.bat";       // 在这里设置你要处理的bat文件
    p.start(command);
    if(!p.waitForFinished())
    {
        qDebug() << "批处理执行出错，错误原因：" << p.errorString()  << endl;
        a.exec();
    }
    MainWindow w;
    w.show();

    return a.exec();
}
