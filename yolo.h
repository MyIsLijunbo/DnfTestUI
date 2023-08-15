#ifndef YOLO_H
#define YOLO_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <opencv2/dnn.hpp>	//调用dnn模块
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace dnn;
using namespace std;

//结构体定义：网络配置参数
struct Net_config
{
    float confThreshold; // 置信度阈值
    float nmsThreshold;  // 非极大值抑制（重叠率）阈值
    int inpWidth;
    int inpHeight;
    string classesFile;	//类别文件名
    string modelConfiguration;	//模型配置文件
    string modelWeights;	//模型权重
    string netname;	//模型名称
};

//定义yolo类
class YOLO
{
public:
    YOLO(Net_config config);
    void detect(Mat& frame);	//检测函数
private:
    float confThreshold;	//类别置信度阈值
    float nmsThreshold;		//重叠率阈值
    int inpWidth;	//图片宽度
    int inpHeight;	//图片高度
    char netname[20];	//网络名称
    vector<string> classes;	//存储类别的数组
    Net net;	//深度学习模型读取
    void postprocess(Mat& frame, const vector<Mat>& outs);	//后处理函数
    void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame);	//画框
};



#endif // YOLO_H
