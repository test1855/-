#include "mainwindow.h"
#include <QDesktopWidget>
#include <QApplication>
#include <qtextcodec.h>

int time = 0;   //旅行模拟系统的当前时间
int PsgNum = 0; //旅客数
int isChange = 0;   //是否有旅客状态变化，如果有则为1
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window *mainWindow = new Window;

    mainWindow->resize(1100, 700);//设定主界面窗口大小
    mainWindow->move((a.desktop()->width() - 1100)/2,(a.desktop()->height() - 700)/2);//将窗口居中放置
    mainWindow->setWindowTitle(QWidget::tr("旅行模拟查询系统"));
    mainWindow->show();


    return a.exec();
}
