#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction menu;

    initMenu();
    initControl();


    // 绑定信号槽
    initConnect();



}

MainWindow::~MainWindow()
{
    delete ui;


}

void MainWindow::initMenu()
{
    //QMenuBar *menuBar = this->menuBar();
    //add three menus
    fileMenu =new QMenu(tr("文件(&F)"),this);


    //add actions and add it into corresponding menu
    openAct = new QAction(tr("打开文件(&O)"),this);
    aboutAct = new QAction(tr("关于Qt"),this);

    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(aboutAct);



    menuBar()->addMenu(fileMenu);

}

void MainWindow::initConnect()
{
    connect(this->openAct,SIGNAL(triggered()),this,SLOT(openImageSlot()));
    connect(this->aboutAct,SIGNAL(triggered()),this,SLOT(aboutQtSlot()));
}

void MainWindow::initControl()
{
    // 申请内存
    mainWidget = new QWidget(this);
    runBtn = new QPushButton("开始识别");
    LineEoutput = new QLineEdit;
    imgLabel = new QLabel;
    bottomBtnHbox = new QHBoxLayout;
    mainVbox = new QVBoxLayout;

    // 设置label图片自适应大小
    imgLabel->setScaledContents(true);
    imgLabel->setMaximumSize(QSize(300,300));

    LineEoutput->setPlaceholderText(tr("识别结果在这里展示"));

    bottomBtnHbox->addWidget(runBtn);
    bottomBtnHbox->addWidget(LineEoutput);

    mainVbox->addWidget(imgLabel);
    mainVbox->addLayout(bottomBtnHbox);


    QGridLayout mainLayout;

    mainWidget->setLayout(mainVbox);



    setCentralWidget(mainWidget);

}

void MainWindow::openImageSlot()
{
    qDebug() << "打开文件" << endl;
    QString imgPath = QFileDialog::getOpenFileName(this,"选择一张图片",
                                                   QCoreApplication::applicationFilePath()
                                                   ,tr("Images (*.png *.xpm *.jpg)"));
    if(imgPath.isEmpty()){
        QMessageBox::warning(this,"提示","请选择一张图片","确认");
    }

    QPixmap img(imgPath);

    imgLabel->setPixmap(img);


}

void MainWindow::aboutQtSlot()
{
    QMessageBox::aboutQt(this);
}

