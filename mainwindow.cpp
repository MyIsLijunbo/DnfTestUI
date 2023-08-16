#include "mainwindow.h"
#include "qdebug.h"
#include "ui_mainwindow.h"
#include "GlobalValue.h"
#include "yolo.h"

using namespace cv;
Mat preprocess(Mat gray)
{
    //1.Sobel算子，x方向求梯度
    Mat sobel;
    Sobel(gray, sobel, CV_8U, 1, 0, 3);

    //2.二值化
    Mat binary;
    threshold(sobel, binary, 0, 255, THRESH_OTSU + THRESH_BINARY);

    //3.膨胀和腐蚀操作核设定
    Mat element1 = getStructuringElement(MORPH_RECT, Size(30, 9));
    //控制高度设置可以控制上下行的膨胀程度，例如3比4的区分能力更强,但也会造成漏检
    Mat element2 = getStructuringElement(MORPH_RECT, Size(24, 4));

    //4.膨胀一次，让轮廓突出
    Mat dilate1;
    dilate(binary, dilate1, element2);

    //5.腐蚀一次，去掉细节，表格线等。这里去掉的是竖直的线
    Mat erode1;
    erode(dilate1, erode1, element1);

    //6.再次膨胀，让轮廓明显一些
    Mat dilate2;
    dilate(erode1, dilate2, element2);

    //7.显示中间图片
    //imshow("binary.jpg", binary);
    //imshow("dilate1.jpg", dilate1);
    //imshow("erode1.jpg", erode1);
    //imshow("dilate2.jpg", dilate2);

    return dilate2;
}


vector<RotatedRect> findTextRegion(Mat img)
{
    vector<RotatedRect> rects;
    //1.查找轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(img, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));

    //2.筛选那些面积小的
    for (int i = 0; i < contours.size(); i++)
    {
        //计算当前轮廓的面积
        double area = contourArea(contours[i]);

        //面积小于1000的全部筛选掉
        if (area < 1000)
            continue;

        //轮廓近似，作用较小，approxPolyDP函数有待研究
        double epsilon = 0.001 * arcLength(contours[i], true);
        Mat approx;
        approxPolyDP(contours[i], approx, epsilon, true);

        //找到最小矩形，该矩形可能有方向
        RotatedRect rect = minAreaRect(contours[i]);

        //计算高和宽
        int m_width = rect.boundingRect().width;
        int m_height = rect.boundingRect().height;

        //筛选那些太细的矩形，留下扁的
        if (m_height > m_width * 1.2)
            continue;

        //符合条件的rect添加到rects集合中
        rects.push_back(rect);

    }
    return rects;
}

void detect(Mat img)
{
    //1.转化成灰度图
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    //2.形态学变换的预处理，得到可以查找矩形的轮廓
    Mat dilation = preprocess(gray);

    //3.查找和筛选文字区域
    vector<RotatedRect> rects = findTextRegion(dilation);

    //4.用绿线画出这些找到的轮廓
    for(int i = 0; i<rects.size(); i++)
    {
        Point2f P[4];
        rects[i].points(P);
        for (int j = 0; j <= 3; j++)
        {
            line(img, P[j], P[(j + 1) % 4], Scalar(0, 255, 0), 2);
        }
    }

    //5.显示带轮廓的图像
    imshow("img", img);
}
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
    , player_(new Player())
    , dnfThread_(new DnfThread())
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    // 初始化线程
    dnfThread_->moveToThread(&thread_);
    connect(&thread_, &QThread::finished, dnfThread_, &QObject::deleteLater);
    connect(&thread_, &QThread::started, dnfThread_, &DnfThread::startWorkInAThread);

    thread_.start();
    emit dnfThread_->GetPhotosPath("");
    // 初始化ui控件
    ui->comboBox_2->insertItem(0,"按键");
    ui->comboBox_2->insertItem(1,"按下");
    ui->comboBox_2->insertItem(2,"弹起");
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
   player_->Play();
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
    string sImagePath = "E:/yuantu4.png";
    string tempImagePath = "E:/juese4.png";

    cv::Rect roi;
    float sroc = 0;
    Mat srcImg = imread(sImagePath);	//读取照片
    Mat tempImg = imread(tempImagePath);	//读取照片

    easyTemplate_.Mark(tempImg);
    easyTemplate_.Match(srcImg,roi,sroc);

    qDebug()<< "roi :"<<roi.x << " "<< roi.y <<" "<< roi.width <<" " <<roi.height <<" " <<sroc ;
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
}



