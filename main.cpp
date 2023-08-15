#include "mainwindow.h"

#include <QApplication>
#include <opencv2/opencv.hpp>
#include <vector>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    // 读取图像
//    Mat image = imread("E:/QtProject/DnfTestUI/build-DnfTestUI-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/debug/logo.png");

//    // 转换为灰度图像
//    Mat gray;
//    cvtColor(image, gray, COLOR_BGR2GRAY);

//    // 检测特征点
//    std::vector<KeyPoint> keypoints;
//    Ptr<FeatureDetector> detector = ORB::create();
//    detector->detect(gray, keypoints);

//    // 绘制特征点
//    Mat output;
//    drawKeypoints(image, keypoints, output);

//    // 显示结果
//    imshow("Output", output);
//    waitKey(0);
//    cv::Mat image = cv::imread("E:/QtProject/DnfTestUI/build-DnfTestUI-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/debug/logo.png");
//    cv::namedWindow("windows");

//    Mat srcImg = imread("E:/QtProject/DnfTestUI/build-DnfTestUI-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/debug/logo.png");
//    Mat midImg;
//    Mat dstImg = srcImg.clone();
//    namedWindow("yuan_tu", WINDOW_NORMAL);
//    imshow("yuan_tu", srcImg);

//    //	灰度化

//    cvtColor(srcImg, midImg,COLOR_BGR2GRAY);
//    namedWindow("huidutu", WINDOW_NORMAL);
//    imshow("huidutu", midImg);

//    //	中值滤波

//    medianBlur(midImg, midImg, 9);
//    namedWindow("lvbohou", WINDOW_NORMAL);
//    imshow("lvbohou", midImg);

//    //	二值化

//    threshold(midImg, midImg, 100, 255, 0);
//    namedWindow("erzhitu", WINDOW_NORMAL);
//    imshow("erzhitu", midImg);

//    //	形态学滤波，开运算

//    Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));
//    morphologyEx(midImg, midImg, MORPH_OPEN, element);
//    namedWindow("yunsuanhou", WINDOW_NORMAL);
//    imshow("yunsuanhou", midImg);

//    //	轮廓提取
//    //	（注：六角螺母的外层轮廓为i=2时的轮廓，若只要该轮廓，将i替换为2即可）

//    std::vector<std::vector<Point>> contours;
//    findContours(midImg, contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
//    Mat midImg1 = Mat::zeros(midImg.rows, midImg.cols, CV_8UC3);
//    for (int i = 0; i < contours.size(); i++)
//    {
//        Scalar color(255, 255, 255);
//        drawContours(midImg1, contours, i, color, 2);
//    }
//    namedWindow("lunkuotu", WINDOW_NORMAL);
//    imshow("lunkuotu", midImg1);


//    //	创建最小包围矩形及获取中心点图像坐标
//    //	（注：六角螺母的外层轮廓为i=2时的轮廓，若只要该轮廓，将i替换为2即可）

//    for (int i = 0; i < contours.size(); i++)
//    {
//        //每个轮廓
//        std::vector<Point> points = contours[i];
//        //对给定的2D点集，寻找最小面积的包围矩形
//        RotatedRect box = minAreaRect(Mat(points));
//        Point2f vertex[4];
//        //将box 中存储的4 个顶点的坐标 存储到vertex[0]~vertex[3]中去
//        box.points(vertex);

//        //打印中心点位置及外接矩形角度
//        std::cout << "中心点位置（第" << i << "条轮廓）：" << box.center <<  std::endl;
//        std::cout << "外接矩形角度（第" << i << "条轮廓）：" << box.angle <<  std::endl;

//        //绘制出最小面积的包围矩形
//        line(dstImg, vertex[0], vertex[1], Scalar(200, 255, 200), 3, LINE_AA);
//        line(dstImg, vertex[1], vertex[2], Scalar(200, 255, 200), 3, LINE_AA);
//        line(dstImg, vertex[2], vertex[3], Scalar(200, 255, 200), 3, LINE_AA);
//        line(dstImg, vertex[3], vertex[0], Scalar(200, 255, 200), 3, LINE_AA);

//        //绘制中心的光标，为了容易理解，此处为手动计算中心点，也可以直接使用 box.center
//        Point center, l, r, u, d;
//        center.x = (vertex[0].x + vertex[2].x) / 2.0;
//        center.y = (vertex[0].y + vertex[2].y) / 2.0;
//        l.x = center.x - 10;
//        l.y = center.y;
//        r.x = center.x + 10;
//        r.y = center.y;
//        u.x = center.x;
//        u.y = center.y - 10;
//        d.x = center.x;
//        d.y = center.y + 10;
//        line(dstImg, l, r, Scalar(200, 255, 200), 2, LINE_AA);
//        line(dstImg, u, d, Scalar(200, 255, 200), 2, LINE_AA);
//    }
//    namedWindow("【最小包围矩形及获取中心点】", WINDOW_NORMAL);
//    imshow("【最小包围矩形及获取中心点】", dstImg);
//    cv::waitKey(0);


    return a.exec();
}
