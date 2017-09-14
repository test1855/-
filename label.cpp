#include "mainwindow.h"
extern int time;
void getCor(int &x,int &y,string city)//这11个城市在地图上的坐标
{
    if(city=="beijing") x=415,y=210;
    else if(city=="wulumuqi") x=213,y=180;
    else if(city=="haerbin") x=500,y=164;
    else if(city=="huhehaote") x=371,y=200;
    else if(city=="shijiazhuang") x=394,y=238;
    else if(city=="wuhan") x=389,y=280;
    else if(city=="nanchang") x=406,y=305;
    else if(city=="chengdu") x=298,y=305;
    else if(city=="xiamen") x=426,y=355;
    else if(city=="liuzhou") x=345,y=380;
    else if(city=="jinan") x=424,y=249;
}



void Label::paintEvent(QPaintEvent *event)//在地图上画线及交通工具
{
    QLabel::paintEvent(event);

    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(5);
    painter.setPen(pen);
    int x1,y1,x2,y2;

    if(P)//如果有需要在地图上标出的旅客
    {

        if(P->state!=6)//如果未到达目的地
        {
            getCor(x1,y1,P->FPlan->items.StartC);
            getCor(x2,y2,P->FPlan->items.ArrivC);
            painter.drawLine(x1, y1, x2, y2);//在起点和终点之间划线


            if(P->state==1||P->state==5)
            {
                if(Trans) delete Trans;
                Trans=new QWidget(this);
                QLabel *trans=new QLabel(Trans);
                QImage T;
                if(P->FPlan->items.flag==0) T.load(":/photo/plane.jpg");//根据交通工具载入不同的图片
                else if(P->FPlan->items.flag==1) T.load(":/photo/train.jpg");
                else T.load(":/photo/bus.jpg");
                trans->setPixmap(QPixmap::fromImage(T));
                Trans->hide();
                Trans->move(x1-15,y1-15);
                Trans->show();

            }
            else if(P->state==2||P->state==3||P->state==4)//在两城市之间时移动
            {
                if(Trans) delete Trans;
                Trans=new QWidget(this);
                QLabel *trans=new QLabel(Trans);
                QImage T;
                if(P->FPlan->items.flag==0) T.load(":/photo/plane.jpg");
                else if(P->FPlan->items.flag==1) T.load(":/photo/train.jpg");
                else T.load(":/photo/bus.jpg");
                trans->setPixmap(QPixmap::fromImage(T));
                int x,y;
                x = x1  - 15 + (x2 - x1) * P->OnTime / P->FPlan->items.consumeT;
                y = y1  - 15 + (y2 - y1) * P->OnTime / P->FPlan->items.consumeT;
                Trans->move(x,y);
                Trans->show();
            }
        }
        else//到达终点
        {
            if(Trans) delete Trans;
            Trans=new QWidget(this);
            QLabel *trans=new QLabel(Trans);
            QImage T;
            T.load(":/photo/smile.jpg");
            trans->setPixmap(QPixmap::fromImage(T));
            getCor(x1,y1,P->ArrivC);
            Trans->move(x1-15,y1-15);
            Trans->show();
        }
    }








}
