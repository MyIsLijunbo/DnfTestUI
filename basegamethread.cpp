#include "basegamethread.h"
#include "GlobalValue.h"
#include "qdebug.h"

#include <QMessageBox>
#include <QTimer>



DnfThread::DnfThread(QObject *parent)
    : BaseGameThread(parent)
    , application_(new ApplicationControl(this))
    , player_(new Player(this))
    , behaviorAnalysis_(new GameBehaviorAnalysis(this))
    , screenCaptureWin_(new ScreenCaptureWin(this))
{
    connect(this,&DnfThread::GetPhotosPath,this,&DnfThread::getPhotos);
}

void DnfThread::startWorkInAThread()
{
    // dnf 游戏窗口设置为前台程序
    bool succ = application_->ShowApplication(tr("地下城与勇士：创新世纪"));
    if (!succ)
    {
        emit SendMessageBox("没有找到地下城与勇士游戏 窗口， 请启动游戏 并 重启 脚本！");
        return;
    }
    int x, y, width, height;
    application_->GetWindowPosion(x, y, width, height);
    application_->SetWindowPosion(0, 0, width, height);

    player_->peripheralControl_->KeyBoardEvent(KeyBoardToCode_["N"],PeripheralControl::KeyBordDown);
    player_->peripheralControl_->KeyBoardEvent(KeyBoardToCode_["N"],PeripheralControl::KeyBordUp);
    player_->peripheralControl_->MouseLeftClick(240, 38 , 1);
    player_->peripheralControl_->MouseLeftClick(220, 102 , 1);
    player_->peripheralControl_->MouseLeftClick(225, 207 , 1);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DnfThread::timeTask);
    timer->start(10);
}

void DnfThread::getPhotos(const QString path)
{
    cv::Mat srcImage = cv::imread(path.toStdString());
    picture_.Mark(srcImage);
}

void DnfThread::timeTask()
{
    QString srcImagePath = g_AppPath + "/photos/photos.png";
    screenCaptureWin_->ScreenCapture(application_->handle_,srcImagePath);
    // 初始化图片处理对象
    cv::Rect playerRoi, entryRoi;
    float score;

    cv::Mat srcImage = cv::imread(srcImagePath.toStdString());
    qDebug()<< "srcImage image size : "<< srcImage.cols << srcImage.rows;

    cv::Mat player = cv::imread(g_AppPath.toStdString() + "/player/player.png");

    picture_.Mark(player);
    picture_.Match(srcImage, playerRoi, score);
    QPoint playerXY = QPoint(playerRoi.x,playerRoi.y);
    qDebug()<< "player image size : "<< player.cols << player.rows;
    qDebug()<< "playerXY :"<< playerXY.x() << " " << playerXY.y() << " " << score;

    cv::Mat entry = cv::imread(g_AppPath.toStdString() +"/entry/entry.png");

    picture_.Mark(entry);
    picture_.Match(srcImage, entryRoi, score);
    QPoint entryXY = QPoint(entryRoi.x,entryRoi.y);
    qDebug()<< "entry image size : "<< entry.cols << entry.rows;
    qDebug()<< "entryXY :"<< entryXY.x() << " " << entryXY.y() << " " << score;

    if (score < 0.5)
    {
        qDebug()<< "游戏入口查找失败!";
        if (behaviorAnalysis_->keyBoardCode == 0)
        {
            return;
        }

        player_->InsertPlayerEvent(0,behaviorAnalysis_->keyBoardCode,PeripheralControl::KeyBordUp,1);
        player_->Play();
        player_->PlayOver();
        behaviorAnalysis_->keyBoardCode = 0;
        return;
    }

    static int number = 0;
    ++number;
    std::string writeName = QString::number(number,10).toStdString() + "_" +QString::number(score).toStdString() +"_beijing.png";
    cv::imwrite(writeName,srcImage);

    quint64 keycode  = behaviorAnalysis_->PlayerEntryBehaviorAnalysis(playerXY,entryXY);

    if (0 == keycode)
    {
        return;
    }

    player_->InsertPlayerEvent(0,keycode,PeripheralControl::KeyBordDown,1);
    player_->Play();
    player_->PlayOver();
}



