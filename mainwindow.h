#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPointer>
#include <QThread>

#include "player.h"
#include "applicationcontrol.h"
#include "easytemplate.h"
#include "basegamethread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();


private:
    Ui::MainWindow *ui;

    void init();
    QThread thread_;

    //QPointer<Player> player_;
    QPointer<DnfThread> dnfThread_;

    EasyTemplate easyTemplate_;

};
#endif // MAINWINDOW_H
