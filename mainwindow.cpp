#include "mainwindow.h"
#include "qdebug.h"
#include "ui_mainwindow.h"
#include "GlobalValue.h"
#include "yolo.h"

#include <QMessageBox>

using namespace cv;

QString g_AppPath = "";
QMap<QString, quint64> KeyBoardToCode_ = {{"0",0x30},{"1",0x31},{"2",0x32},{"3",0x33},{"4",0x34},{"5",0x35},{"6",0x36},
                                          {"7",0x37},{"8",0x38},{"9",0x39},{"A",0x41},{"B",0x42},{"C",0x43},{"D",0x44},
                                          {"E",0x45},{"F",0x46},{"G",0x47},{"H",0x48},{"I",0x49},{"G",0x4A},{"K",0x4B},
                                          {"L",0x4C},{"M",0x4D},{"N",0x4E},{"O",0x4F},{"P",0x50},{"Q",0x51},{"R",0x52},
                                          {"S",0x53},{"T",0x54},{"U",0x55},{"V",0x56},{"W",0x57},{"X",0x58},{"Y",0x59},
                                          {"Z",0x60}};
//定义网络数组
Net_config yolo_nets[4] = {
    {0.5, 0.4, 416, 416,g_AppPath.toStdString() +"/yolov3/myData.names", g_AppPath.toStdString() + "/yolov3/yolov3.cfg", g_AppPath.toStdString() + "/yolov3/yolov3.weights", "yolov3"},
    {0.1, 0.0, 608, 608,g_AppPath.toStdString() +"/yolov4/myData.names", g_AppPath.toStdString() + "/yolov4/yolov4-tiny.cfg", g_AppPath.toStdString() + "/yolov4/yolov4-tiny.weights", "yolov4-tiny"},
    {0.1, 0.0, 320, 320,g_AppPath.toStdString() +"/yolo-fastest/myData.names", g_AppPath.toStdString() + "/yolo-fastest/yolo-fastest-xl.cfg", g_AppPath.toStdString() + "/yolo-fastest/yolo-fastest-xl.weights", "yolo-fastest"},
    {0.5, 0.4, 320, 320,g_AppPath.toStdString() +"/yolobile/myData.names", g_AppPath.toStdString() + "/yolobile/csdarknet53s-panet-spp.cfg", g_AppPath.toStdString() + "/yolobile/yolobile.weights", "yolobile"}
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
   // , player_(new Player())
    , dnfThread_(new DnfThread())
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
    thread_.quit();
    thread_.wait();
}

void MainWindow::init()
{
    // 初始化ui控件
    ui->comboBox_2->insertItem(0,"按键");
    ui->comboBox_2->insertItem(1,"按下");
    ui->comboBox_2->insertItem(2,"弹起");
    g_AppPath = qApp->applicationDirPath();
    // 初始化线程
    thread_.setParent(this);
    dnfThread_->moveToThread(&thread_);
    connect(&thread_, &QThread::finished, dnfThread_, &QObject::deleteLater);
    connect(&thread_, &QThread::started, dnfThread_, &DnfThread::startWorkInAThread);

    thread_.start();

    // 初始化信号
    connect(dnfThread_,&DnfThread::SendMessageBox,this,[=](QString info){
        QMessageBox msgBox;
        msgBox.setText(info);
        msgBox.exec();
    });
}
void MainWindow::on_pushButton_clicked()
{
     QString strCode = ui->lineEdit->displayText().toUpper();
     int type  = 0;
     int code  = KeyBoardToCode_[strCode];
     int state = ui->comboBox_2->currentIndex();
     int count = ui->lineEdit_3->displayText().toUInt();
    // player_->InsertPlayerEvent(type,code,state,count);

     QString text = tr("(键盘) %1 [%2] 次 %3 \n").arg(ui->comboBox_2->currentText()).arg(strCode).arg(count);
     ui->textEdit->insertPlainText(text);
}


void MainWindow::on_pushButton_3_clicked()
{
  // player_->Play();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::on_pushButton_5_clicked()
{
    //1.图片检测
//    string imgpath = "E:/1.png";
//    Mat srcimg = imread(imgpath);	//读取照片

//    YOLO yolo_model(yolo_nets[1]);	//选择网络
//    yolo_model.detect(srcimg);	//调用检测程序

    //图片检测界面
//    static const string kWinName = "Deep learning object detection in OpenCV C++";
//    namedWindow(kWinName, WINDOW_NORMAL);
//    imshow(kWinName, srcimg);
//    waitKey(0);
//    destroyAllWindows();
//    string sImagePath = "E:/yuantu4.png";
//    string tempImagePath = "E:/juese4.png";

//    cv::Rect roi;
//    float sroc = 0;
//    Mat srcImg = imread(sImagePath);	//读取照片
//    Mat tempImg = imread(tempImagePath);	//读取照片

//    easyTemplate_.Mark(tempImg);
//    easyTemplate_.Match(srcImg,roi,sroc);

//    qDebug()<< "roi :"<<roi.x << " "<< roi.y <<" "<< roi.width <<" " <<roi.height <<" " <<sroc ;
//    string srcPath = "E:/yuantu3.png";
//    string templPath = "E:/juese.png";
//    Mat result;
//    Mat img = imread(srcPath);
//    Mat templ = imread(templPath);

//    int resultCols = img.cols - templ.cols + 1; //col = W - w + 1
//    int resultRows = img.rows - templ.rows + 1; //row = H - h + 1

//    result.create(resultRows, resultCols, CV_32FC1);

//    int method = TM_CCORR_NORMED;
//    matchTemplate(img, templ, result, method);

//    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

//    double minVal, maxVal;
//    Point minLoc, maxLoc;
//    Point matchLoc;

//    cout << "result_channel: " << result.channels() << endl;

//    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

//    if (method == TM_SQDIFF || method == TM_SQDIFF_NORMED) {
//        matchLoc = minLoc;
//    }
//    else {
//        matchLoc = maxLoc;
//    }

//    rectangle(img, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(255, 0, 0), 2, 8, 0);

//    imshow("match-result", img);

//    waitKey(0);
//    Mat textImageSrc = imread("E:/yuantu.png");
//    detect(textImageSrc);
    //    waitKey(0);

  //  dnfThread_->startWorkInAThread();
}



