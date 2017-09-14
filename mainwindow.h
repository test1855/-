#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>

#include <QComboBox>
#include <QMessageBox>
#include <QDialog>
#include <Qcheckbox.h>
#include <QRadioButton.h>
#include <QTextEdit.h>
#include <QLabel>
#include <qevent.h>
#include <qpainter.h>
#include <qmutex.h>
#include "graph.h"



class Label: public QLabel//用于在地图上画线的类
{
public:
    PsgState * P;
    QWidget *Trans;
    void paintEvent(QPaintEvent *);
};

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = NULL);
    ~Window();
    void timerEvent(QTimerEvent *);//时间+1时的操作
    int QGetCityNum(QString city);//城市名和序号的转换
    void paintEvent(QPaintEvent *)//用于画地图
    {
        QImage Map;

        Map.load(":/photo/map.jpg");
        Pic->setPixmap(QPixmap::fromImage(Map));
    }
    void pathDialog(int[],int,int,int,int);//路线规划的日志输出
    void ChangeDialog(int[], int, int, int,int);//改变路线的日志输出
    void ChangeStateDialog();//有旅客状态改变的日志输出
    void AskDialog(int ,int ,PsgState* );//查询状态的日志输出
private:
    QComboBox *cbo_StartCity;
    QComboBox *cbo_TermiCity;
    QLineEdit *t;
    QTextEdit *ShowAllPlan;
    QTextEdit *ShowAllState;
    QRadioButton *s[3];
    QCheckBox *c[11];
    Label *Pic;
    Graph MAP;
    PsgState *Psg;
    PsgState *Cur,*Pre;
    int ask;

private slots:

    void on_sel_All();//选择路线规划的槽函数
    void on_sel_Change();//改变计划的槽函数
    void on_sel_Ask();//查询状态的槽函数
    void ChangeT0();//设置限时的输入框只有在选择第三种策略时才可以输入
    void ChangeT1();
    void ChangeT2();
};
#endif // MAINWINDOW_H




