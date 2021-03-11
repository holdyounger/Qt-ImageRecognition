#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString baiduTokenUrl = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&"
                              "client_id=%1&client_secret=%2&";

const char * client_id = "vD7MDv9lbdhb1uvllvTuWeU1";
const char * secret_id = "MFu9X7ewuuNZXcYG1U2zQdL2lhH67F4j";

const QString baiduImageUrl = "https://aip.baidubce.com/rest/2.0/image-classify/v1/animal?access_token=%1";

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
    initStyle();


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
    connect(this->runBtn,SIGNAL(clicked()),this,SLOT(runRecog()));
}

void MainWindow::initControl()
{
    // 申请内存
    mainWidget = new QWidget(this);
    runBtn = new QPushButton("开始识别");
    lineEditOutput = new QLineEdit;
    imgLabel = new QLabel;
    bottomBtnHbox = new QHBoxLayout;
    mainVbox = new QVBoxLayout;

    // 设置label图片自适应大小
    imgLabel->setScaledContents(true);
    imgLabel->setMaximumSize(QSize(450,450));
    imgLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    lineEditOutput->setPlaceholderText(tr("识别结果在这里展示"));
    lineEditOutput->setAlignment(Qt::AlignCenter);
    lineEditOutput->setStyleSheet("font-weight:900;font-family:黑体;font-size:20px;border-radius: 5px;border:2px solid gray");
    lineEditOutput->setEnabled(false);

    runBtn->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    lineEditOutput->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    bottomBtnHbox->addWidget(runBtn);
    bottomBtnHbox->addWidget(lineEditOutput);

    //临时修改，添加一个水平布局，让图片居中
    // 遗留Bug
//    QHBoxLayout *tempHBox;
//    tempHBox->addSpacerItem(new QSpacerItem(this->width()/10,0));


    mainVbox->addWidget(imgLabel);
    mainVbox->addLayout(bottomBtnHbox);
    mainVbox->setStretch(0,6);
    mainVbox->setSpacing(10);
    mainVbox->setStretch(1,1);


    QGridLayout mainLayout;

    mainWidget->setLayout(mainVbox);

    setCentralWidget(mainWidget);

}

void MainWindow::initStyle()
{
    setWindowTitle("动物识别");
    setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarMenuButton));

    //读取qss文件
    QFile File(":/qss/new2.qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = (File.readAll());
    setStyleSheet(styleSheet);
}

void MainWindow::openImageSlot()
{
    // 获取项目工作路径
    QString curPath = QApplication::applicationDirPath();
    QStringList pathList = curPath.split('/');
    QString workPath;
    for (auto i = 0; i < pathList.size() - 1;i++)
        workPath += (pathList[i] + '/');
    QString openPath = workPath + "Image_recognition_demo0311/img/";
    imgPath = QFileDialog::getOpenFileName(this,"选择一张图片",openPath
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

void MainWindow::runRecog()
{

    if(!imgLabel->text().isEmpty() || imgPath.isEmpty()){
        QMessageBox::critical(this,"警告","还没有打开图片哦~","确认");
    return;
    }
    QByteArray img = Image::imgToBase64(imgPath);  // img = XXXXXX
    QByteArray imgData = "image=" +img;            // body


    //获取access_token
    QByteArray replyData;                           // 保存回复信息

    QString url = QString(baiduTokenUrl).arg(client_id).arg(secret_id);


    QMap<QString,QString> header;                   // 封装头部信息

    header.insert(QString("Content-Type"),
                  QString("application/x-www-form-urlencoded"));

    bool result= Http::post_sync(url,header,imgData,replyData);
    QString accessToken;
    if(result)
    {
        QJsonObject obj = QJsonDocument::fromJson(replyData).object();  //应该在fromJson之后判断一下是不是json对象
        accessToken = obj.value("access_token").toString();
    }

    QString imgurl = baiduImageUrl.arg(accessToken);

    result = Http::post_sync(imgurl,header,imgData,replyData);
    if(result)
    {
        QJsonObject obj = QJsonDocument::fromJson(replyData).object();  //应该在fromJson之后判断一下是不是json对象
        //qDebug() << obj;
        QJsonValue Jsonval = obj.value("result");
        //qDebug() << Jsonval << "first";
        if(Jsonval.isArray())
        {
            QJsonValue first = Jsonval.toArray().at(0);
            if(first.isObject())
            {
                qDebug()<< "查询结果（" << first.toObject().value("name").toString()  << ')'<< endl;
                lineEditOutput->setText(first.toObject().value("name").toString());
                lineEditOutput->setStyleSheet("font-weight:900;font-family:黑体;font-size:20px;border-radius: 5px;border:2px solid green");
                return;
            }
        }
    }
    lineEditOutput->setText("Unkown");
    lineEditOutput->setStyleSheet("font-weight:900;font-family:黑体;font-size:20px;border-radius: 5px;border:2px solid red");

}

