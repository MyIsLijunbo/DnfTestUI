#include "basegamethread.h"
#include "GlobalValue.h"
#include "qdebug.h"

DnfThread::DnfThread(QObject *parent)
    :BaseGameThread(parent)
    ,application_(new ApplicationControl(this))
    ,player_(new Player(this))
    ,behaviorAnalysis_(new GameBehaviorAnalysis(this))
    ,screenCaptureWin_(new ScreenCaptureWin(this))
{
    connect(this,&DnfThread::GetPhotosPath,this,&DnfThread::getPhotos);
}

void DnfThread::startWorkInAThread()
{
    // dnf 游戏窗口设置为前台程序
    application_->ShowApplication(tr("地下城与勇士：创新世纪"));

    while (true)
    {
        //Sleep(100);
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
                continue;
            }

            player_->InsertPlayerEvent(0,behaviorAnalysis_->keyBoardCode,PeripheralControl::KeyBordUp,1);
            player_->Play();
            player_->PlayOver();
            behaviorAnalysis_->keyBoardCode = 0;
            continue;
        }

        static int number = 0;
        ++number;
        std::string writeName = QString::number(number,10).toStdString() + "_" +QString::number(score).toStdString() +"_beijing.png";
        cv::imwrite(writeName,srcImage);

        quint64 keycode  = behaviorAnalysis_->PlayerEntryBehaviorAnalysis(playerXY,entryXY);

        if (0 == keycode)
        {
            continue;
        }

        player_->InsertPlayerEvent(0,keycode,PeripheralControl::KeyBordDown,1);
        player_->Play();
        player_->PlayOver();
        // 初始化系统事件对象
        // player_->InsertPlayerEvent(0,"")
        // 图片截图，图片识别事先准备好的角色图片，游戏入口图片，技能图片。
        // 根据图片识别结果生成游戏动作。
        // 运行游戏动作。
        // 校验动作。
    }
}

void DnfThread::getPhotos(const QString path)
{
    cv::Mat srcImage = cv::imread(path.toStdString());
    picture_.Mark(srcImage);
}

void DnfThread::debug(QString &info)
{
    qDebug()<<info;
    emit printDebug(info);
}
