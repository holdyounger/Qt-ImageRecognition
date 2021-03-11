#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QString>
#include <QDialog>
#include <QFileDialog>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QWidget>
#include <QLineEdit>
#include <QMap>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QStyle>
#include <QStringList>
#include <QSpacerItem>
#include "http.h"
#include "image.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void initMenu();
    void initConnect();
    void initControl();
    void initStyle();

private slots:
    void openImageSlot();
    void aboutQtSlot();
    void runRecog();

private:
    Ui::MainWindow *ui;

    // 主界面
    QWidget *mainWidget;

    // 菜单栏
    QMenu *fileMenu;

    QAction *openAct;
    QAction *aboutAct;
    // 界面布局
    QHBoxLayout *bottomBtnHbox;
    QVBoxLayout *mainVbox;

    // 图片显示Label
    QLabel *imgLabel;

    // 按钮
    QPushButton *runBtn;

    // 输出框
    QLineEdit *lineEditOutput;


    QString imgPath;


};
#endif // MAINWINDOW_H
