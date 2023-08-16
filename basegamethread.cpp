#include "basegamethread.h"


DnfThread::DnfThread(QObject *parent)
    :BaseGameThread(parent)
    ,application_(new ApplicationControl(this))
    ,player_(new Player(this))
{
    connect(this,&DnfThread::GetPhotosPath,this,&DnfThread::getPhotos);
}

void DnfThread::startWorkInAThread()
{
    // dnf 游戏窗口设置为前台程序
    application_->ShowApplication(tr("地下城与勇士：创新世纪"));

    // 初始化图片处理对象
    getPhotos("./photos/photos.png");

    cv::Mat player = cv::imread("./player/player.png");
    cv::Mat entry = cv::imread("./entry/entry.png");
    cv::Rect playerRoi, entryRoi;
    float score;
    picture_.Match(player, playerRoi, score);
    picture_.Match(player, entryRoi, score);
    // 初始化系统事件对象
   // player_->InsertPlayerEvent(0,"")
    // 图片截图，图片识别事先准备好的角色图片，游戏入口图片，技能图片。
    // 根据图片识别结果生成游戏动作。
    // 运行游戏动作。
    // 校验动作。
}

void DnfThread::getPhotos(const QString path)
{
    cv::Mat srcImage = cv::imread(path.toStdString());
    picture_.Mark(srcImage);
}
