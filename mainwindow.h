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


private slots:
    void openImageSlot();
    void aboutQtSlot();

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
    QLineEdit *LineEoutput;





};
#endif // MAINWINDOW_H
