#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GlobalValue.h"
#include "yolo.h"
using namespace cv;

string applicationPath = "E:/QtProject/DnfTestUI/build-DnfTestUI-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/debug/";
//定义网络数组
Net_config yolo_nets[4] = {
    {0.5, 0.4, 416, 416,applicationPath +"yolov3/myData.names", applicationPath + "yolov3/yolov3.cfg", applicationPath + "yolov3/yolov3.weights", "yolov3"},
    {0.1, 0.0, 608, 608,applicationPath +"yolov4/myData.names", applicationPath + "yolov4/yolov4-tiny.cfg", applicationPath + "yolov4/yolov4-tiny.weights", "yolov4-tiny"},
    {0.1, 0.0, 320, 320,applicationPath +"yolo-fastest/myData.names", applicationPath + "yolo-fastest/yolo-fastest-xl.cfg", applicationPath + "yolo-fastest/yolo-fastest-xl.weights", "yolo-fastest"},
    {0.5, 0.4, 320, 320,applicationPath +"yolobile/myData.names", applicationPath + "yolobile/csdarknet53s-panet-spp.cfg", applicationPath + "yolobile/yolobile.weights", "yolobile"}
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , application_(new ApplicationControl(this))
    , player_(new Player())
{
    ui->setupUi(this);
    ui->comboBox_2->insertItem(0,"按键");
    ui->comboBox_2->insertItem(1,"按下");
    ui->comboBox_2->insertItem(2,"弹起");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
     QString strCode = ui->lineEdit->displayText().toUpper();
     int type  = 0;
     int code  = KeyBoardToCode_[strCode];
     int state = ui->comboBox_2->currentIndex();
     int count = ui->lineEdit_3->displayText().toUInt();
     player_->InsertPlayerEvent(type,code,state,count);

     QString text = tr("(键盘) %1 [%2] 次 %3 \n").arg(ui->comboBox_2->currentText()).arg(strCode).arg(count);
     ui->textEdit->insertPlainText(text);
}


void MainWindow::on_pushButton_3_clicked()
{
    application_->ShowApplication(tr("地下城与勇士：创新世纪"));
   player_->Play();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::on_pushButton_5_clicked()
{
    //1.图片检测
    string imgpath = "E:/1.png";
    Mat srcimg = imread(imgpath);	//读取照片

    YOLO yolo_model(yolo_nets[1]);	//选择网络
    yolo_model.detect(srcimg);	//调用检测程序

    //图片检测界面
    static const string kWinName = "Deep learning object detection in OpenCV C++";
    namedWindow(kWinName, WINDOW_NORMAL);
    imshow(kWinName, srcimg);
    waitKey(0);
    destroyAllWindows();
}

