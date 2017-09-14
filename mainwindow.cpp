#include "mainwindow.h"
#include <qinputdialog.h>
#include <fstream>
extern int PsgNum;
extern int time;
extern int isChange;
extern QString getWay(int); //用于将存储在旅客状态类里的交通方式由数字转换成QString
extern QString getHANZICity(string);//用于将存储为string的拼音格式的城市转换成QString的格式
Window::Window(QWidget *parent):
    QMainWindow(parent)
{
    fstream outfile("diary.txt",ios::out);//先打开输出日志的文件以清空内容
    outfile.close();
    MAP.CreatGraph();//读取并以邻接表的形式存储时刻表
    MAP.initNum();
    Psg=NULL;
    Cur=NULL;
    Pre=NULL;
    ask=0;
    QGridLayout *gridLayout = new QGridLayout;//出发城市和到达城市部分的布局


    gridLayout->setColumnStretch(0, 3);
    gridLayout->setColumnStretch(1, 3);
    gridLayout->setColumnStretch(2, 3);
    gridLayout->setColumnStretch(3, 3);


    QLabel *lbl_caption = new QLabel(QWidget::tr("出发城市"));
    cbo_StartCity = new QComboBox();

    cbo_StartCity->addItem(QWidget::tr("北京"));
    cbo_StartCity->addItem(QWidget::tr("石家庄"));
    cbo_StartCity->addItem(QWidget::tr("济南"));
    cbo_StartCity->addItem(QWidget::tr("呼和浩特"));
    cbo_StartCity->addItem(QWidget::tr("哈尔滨"));
    cbo_StartCity->addItem(QWidget::tr("乌鲁木齐"));
    cbo_StartCity->addItem(QWidget::tr("南昌"));
    cbo_StartCity->addItem(QWidget::tr("武汉"));
    cbo_StartCity->addItem(QWidget::tr("柳州"));
    cbo_StartCity->addItem(QWidget::tr("成都"));
    cbo_StartCity->addItem(QWidget::tr("厦门"));


    gridLayout->addWidget(lbl_caption, 0, 0);
    gridLayout->addWidget(cbo_StartCity, 0, 1);

    QLabel *lb2_caption = new QLabel(QWidget::tr("到达城市"));
    cbo_TermiCity = new QComboBox();

    cbo_TermiCity->addItem(QWidget::tr("北京"));
    cbo_TermiCity->addItem(QWidget::tr("石家庄"));
    cbo_TermiCity->addItem(QWidget::tr("济南"));
    cbo_TermiCity->addItem(QWidget::tr("呼和浩特"));
    cbo_TermiCity->addItem(QWidget::tr("哈尔滨"));
    cbo_TermiCity->addItem(QWidget::tr("乌鲁木齐"));
    cbo_TermiCity->addItem(QWidget::tr("南昌"));
    cbo_TermiCity->addItem(QWidget::tr("武汉"));
    cbo_TermiCity->addItem(QWidget::tr("柳州"));
    cbo_TermiCity->addItem(QWidget::tr("成都"));
    cbo_TermiCity->addItem(QWidget::tr("厦门"));

    gridLayout->addWidget(lb2_caption, 0, 2);
    gridLayout->addWidget(cbo_TermiCity, 0, 3);

    QGridLayout *PassLayout = new QGridLayout; //经过城市部分的布局
    PassLayout->setRowStretch(0, 1);
    PassLayout->setRowStretch(1, 1);
    PassLayout->setRowStretch(2, 1);
    PassLayout->setRowStretch(3, 1);

    PassLayout->setColumnStretch(0, 1);
    PassLayout->setColumnStretch(1, 1);
    PassLayout->setColumnStretch(2, 1);
    PassLayout->setColumnStretch(3, 1);


    QLabel *lb3_caption = new QLabel(QWidget::tr("经过"));
    QLabel *lb4_caption = new QLabel(QWidget::tr("城市"));


    c[0]=new QCheckBox("北京");
    c[1]=new QCheckBox("石家庄");
    c[2]=new QCheckBox("济南");
    c[3]=new QCheckBox("呼和浩特");
    c[4]=new QCheckBox("哈尔滨");
    c[5]=new QCheckBox("乌鲁木齐");
    c[6]=new QCheckBox("南昌");
    c[7]=new QCheckBox("武汉");
    c[8]=new QCheckBox("柳州");
    c[9]=new QCheckBox("成都");
    c[10]=new QCheckBox("厦门");
    PassLayout->addWidget(lb3_caption, 1, 0);
    PassLayout->addWidget(lb4_caption, 2, 0);
    PassLayout->addWidget(c[0], 0, 1);
    PassLayout->addWidget(c[1], 0, 2);
    PassLayout->addWidget(c[2], 0, 3);
    PassLayout->addWidget(c[3], 1, 1);
    PassLayout->addWidget(c[4], 1, 2);
    PassLayout->addWidget(c[5], 1, 3);
    PassLayout->addWidget(c[6], 2, 1);
    PassLayout->addWidget(c[7], 2, 2);
    PassLayout->addWidget(c[8], 2, 3);
    PassLayout->addWidget(c[9], 3, 1);
    PassLayout->addWidget(c[10], 3, 2);


    QGridLayout *StraLayout = new QGridLayout;//策略选择的布局
    StraLayout->setRowStretch(0, 1);//行
    StraLayout->setRowStretch(1, 1);
    StraLayout->setRowStretch(2, 1);
    StraLayout->setColumnStretch(0, 1);
    StraLayout->setColumnStretch(1, 1);
    StraLayout->setColumnStretch(2, 1);

    QLabel *lb5_caption = new QLabel(QWidget::tr("策略选择"));
    s[0] = new QRadioButton("金钱最少策略");
    s[1] = new QRadioButton("时间最短策略");
    s[2] = new QRadioButton("限时金钱最少策略");
    t=new QLineEdit;
    QRegExp regx("[0-9]+$");//设置只能输入数字
    QValidator *validator = new QRegExpValidator(regx, t );

    t->setReadOnly(true);
    t->setValidator(validator);

    StraLayout->addWidget(lb5_caption, 1, 0);
    StraLayout->addWidget(s[0], 0, 1);
    StraLayout->addWidget(s[1], 1, 1);
    StraLayout->addWidget(s[2], 2, 1);
    StraLayout->addWidget(t, 2, 2);


    QHBoxLayout *bomLayout = new QHBoxLayout;//三个动作按钮的布局
    QPushButton *btn = new QPushButton(QWidget::tr("规划路线"));
    QPushButton *Xbtn = new QPushButton(QWidget::tr("修改路线"));
    QPushButton *Abtn = new QPushButton(QWidget::tr("查询状态"));
    bomLayout->addWidget(Xbtn);
    bomLayout->addWidget(btn);
    bomLayout->addWidget(Abtn);

    QHBoxLayout *QbomLayout = new QHBoxLayout;//退出按钮的布局
    QPushButton *Qbtn = new QPushButton(QWidget::tr("退出"));
    QbomLayout->addStretch();
    QbomLayout->addStretch();
    QbomLayout->addWidget(Qbtn);


    QGridLayout *rightLayout = new QGridLayout;//右半部分的布局
    rightLayout->setRowStretch(0, 15);//行
    rightLayout->setRowStretch(1, 24);
    rightLayout->setRowStretch(2, 18);
    rightLayout->setRowStretch(3, 10);
    rightLayout->setRowStretch(4, 28);
    rightLayout->setRowStretch(5, 4);

    ShowAllPlan = new QTextEdit;
    ShowAllPlan->setReadOnly (true);
    rightLayout->addWidget(ShowAllPlan, 4, 0);
    rightLayout->addLayout(QbomLayout, 5, 0);
    rightLayout->addLayout(gridLayout,0,0);
    rightLayout->addLayout(PassLayout,1,0);
    rightLayout->addLayout(bomLayout,3,0);
    rightLayout->addLayout(StraLayout,2,0);


    QGridLayout *LeftLayout = new QGridLayout;//左半部分的布局
    LeftLayout->setColumnStretch(0, 8);
    LeftLayout->setColumnStretch(1, 3);

    Pic = new Label;
    Pic->P=NULL;
    Pic->Trans=NULL;
    QImage Map;

    Map.load(":/photo/map.jpg");
    Pic->setPixmap(QPixmap::fromImage(Map));
    LeftLayout->addWidget(Pic,0,0);
    ShowAllState = new QTextEdit;
    ShowAllState->setReadOnly (true);
    ShowAllState->setPlainText("当前时间：0:00.");
    LeftLayout->addWidget(ShowAllState,1,0);





    QGridLayout *mainLayout = new QGridLayout;//总体布局

    mainLayout->setRowStretch(0, 3);//行
    mainLayout->setRowStretch(1, 32);
    mainLayout->setColumnStretch(0, 2);
    mainLayout->setColumnStretch(1, 31);
    mainLayout->setColumnStretch(2, 13);

    mainLayout->addLayout(LeftLayout,1,1);
    mainLayout->addLayout(rightLayout,1,2);

    QWidget *mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
    startTimer(7000);//每7秒推进一个小时

    connect(btn, SIGNAL(clicked()), this, SLOT(on_sel_All()));//将用户选择规划路线与“规划路线”按钮连接
    connect(Xbtn, SIGNAL(clicked()), this, SLOT(on_sel_Change()));//将用户选择更改路线与“修改路线”按钮连接
    connect(Abtn, SIGNAL(clicked()), this, SLOT(on_sel_Ask()));//将用户选择查询状态与“查询状态”按钮连接
    connect(s[0],SIGNAL(clicked()),this,SLOT(ChangeT0()));
    connect(s[1],SIGNAL(clicked()),this,SLOT(ChangeT1()));
    connect(s[2],SIGNAL(clicked()),this,SLOT(ChangeT2()));//设置限时的输入框只有在选择第三种策略时才可以输入
    connect(Qbtn,SIGNAL(clicked()),this,SLOT(close()));//退出的按钮
}



void Window::on_sel_All()//当用户选择规划路线时
{

    QString str1,str2;//用于输出弹窗语句
    QString SCity,TCity;//起点和终点城市
    int ER[2]={0,0};//用于在输出日志中判断用户进行何种操作，如规划的路线不存在，用户没有选择按此线路出发等等
    int strategy=0, dec=0;//策略和限制时间

    MAP.RinitNum();//初始化遍历时用到的变量
    if(cbo_StartCity->currentText() == cbo_TermiCity->currentText())
    {
        str1 = "起点和终点不能相同";
        QMessageBox::information(this, tr("错误"), str1);
    }
    else
    {
        SCity=cbo_StartCity->currentText();
        TCity=cbo_TermiCity->currentText();
        if((s[0]->isChecked())==false&&(s[1]->isChecked())==false&&(s[2]->isChecked())==false)
        {
            str1 = "还没有选择策略";
            QMessageBox::information(this, tr("错误"), str1);
            return;
        }
        else
        {
            if((s[0]->isChecked())==true) strategy = 1;
            else if((s[1]->isChecked())==true) strategy = 2;
            else if((s[2]->isChecked())==true)
            {
                strategy = 3;
                str2 = t->text();
                bool ok;
                dec=str2.toInt(&ok,10);
                if(dec <= 0)
                {

                    str1 = "限制时间必须大于0";
                    QMessageBox::information(this, tr("错误"), str1);

                    return;
                }
            }
            if(c[QGetCityNum(TCity)]->isChecked()==true)
            {
                str1 = "不能经过终点";
                QMessageBox::information(this, tr("错误"), str1);
                return;

            }
            else//读取旅客选择的经过城市
            {

                for(int i = 0; i < MAX; i++)
                {
                    if(c[i]->isChecked()==true)
                    {
                        MAP.Pass[i].pass=1;
                        str1+="经过为"+c[i]->text();
                    }
                }
                str1="确认成功，正在为您规划路线。";
                QMessageBox::information(this, tr("成功"), str1);
            }

        }


        MAP.Cur.start=SCity.toStdString();
        MAP.Cur.first=NULL;
        MAP.DFS(QGetCityNum(SCity),QGetCityNum(TCity));//DFS

        //根据策略选路

        switch (strategy){
            case 1:
                MAP.Money();
            break;
            case 2:
                MAP.Time();
            break;
            case 3:
                MAP.Time_Money(dec);
        }
        if(MAP.PATH==NULL)
        {

            str1 = "没有满足条件的路线";
            QMessageBox::information(this, tr("查找失败"), str1);
            ER[0]=1;
        }
        else
        {
            //屏幕上输出
            MAP.OutPutPlan(str1);
            ShowAllPlan->setText(str1);
            //询问是否
            QMessageBox::StandardButton reply;
            str2 = "生成的路线已显示在右下角文本框，是否按此线路出行？";
            reply = QMessageBox::question(this, tr("是否出发？"),
                                               str2,
                                               QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {

                Pic->P=NULL;
                PsgNum++;//乘客数+1
                Cur = new PsgState(MAP.PATH,MAP.getHANZICityNum(TCity.toStdString())); //添加一个乘客到链表中
                if(Psg==NULL)
                {
                    Psg=Cur;
                    Pre=Cur;
                    Cur=NULL;
                }
                else
                {
                    Pre->nextPsg=Cur;
                    Pre=Cur;
                    Cur=NULL;
                }
                str2 = "记录成功，你的号码是"+QString("%1").arg(PsgNum);
                ask=0;//表示不是查询或修改的情况，在地图上显示时限时最新的旅客状态
                QMessageBox::information(this, tr("成功"), str2);
            }
            else ER[1]=1;
        }

       pathDialog(ER,QGetCityNum(SCity),QGetCityNum(TCity),strategy,dec);//日志输出

    }

}



void Window::ChangeT2()
{
    t->setReadOnly(false);

}
void Window::ChangeT0()
{
    t->setReadOnly(true);
}
void Window::ChangeT1()
{
    t->setReadOnly(true);
}


int Window::QGetCityNum(QString city)  //城市名与序号的转化
{
    if(city=="北京")
        return 0;
    else if(city=="石家庄")
        return 1;
    else if(city.compare("济南")==0)
        return 2;
    else if(city.compare("呼和浩特")==0)
        return 3;
    else if(city.compare("哈尔滨")==0)
        return 4;
    else if(city.compare("乌鲁木齐")==0)
        return 5;
    else if(city.compare("南昌")==0)
        return 6;
    else if(city.compare("武汉")==0)
        return 7;
    else if(city.compare("柳州")==0)
        return 8;
    else if(city.compare("成都")==0)
        return 9;
    else if(city.compare("厦门")==0)
        return 10;
    else
        return -1;
}

void Window::timerEvent(QTimerEvent *)
{

    PsgState *p=Psg; //便于输出旅客状态

    time=(time+1)%24;  //当前时间+1
    QString showState="当前时间："+QString("%1").arg(time)+":00.\n";

    isChange=0;
    while(p)
    {
        p->ChangeState();\
        p->OutState(showState);
        p=p->nextPsg;
    }
    ShowAllState->setText(showState);
    if(ask==0) Pic->P=Pre;//如果ask为0则在地图上显示最新添加的旅客的状态，否则显示用户查询或更改路线的旅客的状态

    Pic->update();
    if(isChange==1) ChangeStateDialog();//一旅客状态改变时在日志里输出

}


void Window::on_sel_Change()
{

    QString str1,str2; //用于弹窗输出
    QString TCity;//终点城市
    string SCity;//起点城市
    int strategy=0, dec=0;//策略和若为第三种策略时的限制时间
    int ER[2]={0,0};//用于在输出日志中判断用户进行何种操作，如该旅客不存在，规划的路线不存在，用户没有选择按此线路出发等等
    MAP.RinitNum();//初始化遍历所需的数据
    PsgState *a = Psg;//便于查找要修改的旅客


    TCity=cbo_TermiCity->currentText();//获取终点城市
    if((s[0]->isChecked())==false&&(s[1]->isChecked())==false&&(s[2]->isChecked())==false)
    {
        str1 = "还没有选择策略";
        QMessageBox::information(this, tr("错误"), str1);
        return;
    }
    else
    {
        if((s[0]->isChecked())==true) strategy = 1;
        else if((s[1]->isChecked())==true) strategy = 2;
        else if((s[2]->isChecked())==true)
        {
            strategy = 3;
            str2 = t->text();
            bool ok;
            dec=str2.toInt(&ok,10);
            if(dec <= 0)
            {
                str1 = "限制时间必须大于0";
                QMessageBox::information(this, tr("错误"), str1);

                return;
            }
        }
        if(c[QGetCityNum(TCity)]->isChecked()==true)
        {
            str1 = "不能经过终点";
            QMessageBox::information(this, tr("错误"), str1);
            return;
        }
        else//获取经过城市信息
        {
            for(int i = 0; i < MAX; i++)
            {
                if(c[i]->isChecked()==true)
                {
                    MAP.Pass[i].pass=1;
                    str1+="经过为"+c[i]->text();
                }
            }
            bool ok;
            int num=QInputDialog::getInt(this,tr("请输入"),tr("请输入要修改的旅客序号"),1,1,1000,1,&ok);

            if (ok)
            {
                if(num>PsgNum||num==0)
                {
                    QMessageBox::information(this, tr("错误"), "不存在该旅客");
                    ER[0]=1;
                }
                else
                {
                    while(a)
                    {
                        if(a->Num==num) break;
                        a=a->nextPsg;
                    }
                    if(a->state==1||a->state==5) SCity=a->FPlan->items.StartC;//根据状态选择旅客使用新路线的起点
                    else if(a->state==6) SCity=a->ArrivC;
                    else SCity=a->FPlan->items.ArrivC;
                    str1="确认成功，正在为您规划路线。";
                    QMessageBox::information(this, tr("成功"), str1);
                    MAP.Cur.start=SCity;
                    MAP.Cur.first=NULL;
                    MAP.DFS(MAP.getCityNum(SCity),QGetCityNum(TCity));//DFS

                    //根据策略选路

                    switch (strategy){
                        case 1:
                            MAP.Money();
                        break;
                        case 2:
                            MAP.Time();
                        break;
                        case 3:
                            MAP.Time_Money(dec);
                    }
                    if(MAP.PATH==NULL)
                    {
                        str1 = "没有满足条件的路线";
                        QMessageBox::information(this, tr("查找失败"), str1);
                        ER[1]=1;
                    }
                    else
                    {
                        //屏幕上输出
                        MAP.OutPutPlan(str1);
                        ShowAllPlan->setText(str1);
                        //询问是否
                        QMessageBox::StandardButton reply;
                        str2 = "生成的路线已显示在右下角文本框，是否按此线路出行？";
                        reply = QMessageBox::question(this, tr("是否出发？"),
                                                       str2,
                                                       QMessageBox::Yes | QMessageBox::No);
                        if (reply == QMessageBox::Yes)//根据状态释放旧路线，将新路线连接
                        {
                            Pic->P=NULL;
                            ListPtr Free=NULL,Temp=NULL;
                            if(a->state==1)//若旅客未出发，则直接更改并释放旧路线
                            {
                                Free=a->FPlan;
                                a->FPlan=MAP.PATH;
                                a->Plan=MAP.PATH;
                                while(Free!=NULL)
                                {
                                    Temp=Free;
                                    Free=Free->next;
                                    delete Temp;
                                }
                            }
                            else if(a->state==5)//若旅客在等待换乘，则替换未出行的部分
                            {
                                Free=a->FPlan;
                                a->FPlan=MAP.PATH;
                                ListPtr Find=a->Plan;

                                while(Find->next!=Free) Find=Find->next;
                                Find->next=MAP.PATH;

                                while(Free!=NULL)
                                {
                                    Temp=Free;
                                    Free=Free->next;
                                    delete Temp;
                                }
                            }
                            else if(a->FPlan==NULL)//若已到达终点，则将新计划接在后面
                            {
                                ListPtr Find=a->Plan;
                                while(Find->next!=NULL) Find=Find->next;
                                Find->next=MAP.PATH;
                                a->FPlan=MAP.PATH;
                                while(Free!=NULL)
                                {
                                    Temp=Free;
                                    Free=Free->next;
                                    delete Temp;
                                }
                            }
                            else//若在两城市之间，则将新计划接在该旅行到达之后
                            {
                                Free=a->FPlan->next;
                                a->FPlan->next=MAP.PATH;
                                while(Free!=NULL)
                                {
                                    Temp=Free;
                                    Free=Free->next;
                                    delete Temp;
                                }
                            }
                            a->ArrivC=MAP.getCityName(MAP.getHANZICityNum(TCity.toStdString()));//修改该乘客要到达的城市
                            ask=0;
                            str2 = "修改成功";
                            QMessageBox::information(this, tr("成功"), str2);
                            Pic->P=a;
                            ask=1;//表示在查询/修改另外一个人，或添加新的旅客之前都在地图上显示该旅客状态
                        }
                        else
                        {
                            ER[0]=1;
                            ER[1]=1;
                        }
                    }

                }
                ChangeDialog(ER,num,QGetCityNum(TCity),strategy,dec);//日志输出
            }
        }
    }
}


void Window::on_sel_Ask()
{
    bool ok;
    PsgState *a = Psg;//便于查找该旅客
    int num=QInputDialog::getInt(this,tr("请输入"),tr("请输入要查询的旅客序号"),1,1,1000,1,&ok);
    int ER=0;
    if (ok)
    {
        if(num>PsgNum||num==0)
        {
            QMessageBox::information(this, tr("错误"), "不存在该旅客");
            ER=1;
        }
        else
        {
            while(a)
            {
                if(a->Num==num) break;
                a=a->nextPsg;
            }
            Pic->P=a;
            ask=1;
            Pic->update();//更新地图
            QString str,str1;
            str="旅客"+QString("%1").arg(num);
            a->OutPlan(str1);
            ShowAllPlan->setText(str+str1);
            QString showState="当前时间："+QString("%1").arg(time)+":00.\n";
            a->OutState(showState);//输出旅客全部计划
            showState+="该旅客的计划已输出在右下角，当前位置可在图中看到。";
            QMessageBox::information(this, tr("查询结果"), showState);
        }
            AskDialog(ER,num,a);

    }
}
void Window::pathDialog(int ER[],int SCity,int TCity,int strategy,int LimitTime)
{
    //ER[0]为1说明没路，ER[1]为1说明旅客选择不出发，两个都是0说名旅客查到路并出发，SCity是起点城市，TCity是终点城市，strategy是策略有1 2 3
    //经过城市直接调用MAP.Pass[i],如果它的pass是1，则序号为i的城市是要求经过的城市，然后生成的路线是MAP.PATH
    QFile diary("diary.txt");
    if(diary.open(QFile::WriteOnly|QFile::Append))
    {
        QString str;
        QTextStream out(&diary);
        str="☆--------------------------------------------------------------------------------------☆\r\n";
        out<<str;
        str="用户在"+QString("%1").arg(time)+":00进行了路线查询\r\n";
        out<<str;
        str="起点："+getHANZICity(MAP.getCityName(SCity))+"终点："+getHANZICity(MAP.getCityName(TCity))+"\r\n";
        out<<str;
        str="经过城市：";
        if(MAP.Pass[0].pass==1) str+="北京\t";
        if(MAP.Pass[1].pass==1) str+="石家庄\t";
        if(MAP.Pass[2].pass==1) str+="济南\t";
        if(MAP.Pass[3].pass==1) str+="呼和浩特\t";
        if(MAP.Pass[4].pass==1) str+="哈尔滨\t";
        if(MAP.Pass[5].pass==1) str+="乌鲁木齐\t";
        if(MAP.Pass[6].pass==1) str+="南昌\t";
        if(MAP.Pass[7].pass==1) str+="武汉\t";
        if(MAP.Pass[8].pass==1) str+="柳州\t";
        if(MAP.Pass[9].pass==1) str+="成都\t";
        if(MAP.Pass[10].pass==1) str+="厦门\t";
        str+="\r\n";
        out<<str;
        str="策略：";
        switch(strategy)
        {
            case 1:
                str+="最省钱策略";
                break;
            case 2:
                str+="最省时间策略";
                break;
            case 3:
                str+="限时最省钱策略 限时为"+QString("%1").arg(LimitTime);
                break;

        }
        str+="\r\n";
        out<<str;
        str="查询结果为：";

        //在这里判断a是否为空 若为空则说不存在此路线 否则输出路线
        if(ER[0]==1)
        {
            str+="不存在此路线\r\n";
            out<<str;
        }

        else
        {

           str+="\r\n";
           out<<str;

           int Time=0;
           int feee=0;

           ListPtr a=NULL;
           a=MAP.PATH;
           while(a!=NULL)
           {
               str=getWay(a->items.flag)+" "+QString::fromStdString(a->items.ID)+" "+getHANZICity(a->items.StartC)+"->"
                       +getHANZICity(a->items.ArrivC)+" 出发时间为:"+QString("%1").arg(a->items.startT)
                       +":00 到达时间为："+QString("%1").arg(a->items.arrivalT)+":00 费用为:"+QString("%1").arg(a->items.fee)
                       +" 所需时间为："+QString("%1").arg(a->items.consumeT)+"\r\n";

                out<<str;


             Time=Time+a->items.consumeT;
             feee=feee+a->items.fee;
             if(a->next)
             {
                if((a->next->items.startT-a->items.arrivalT)<0)

                  Time=Time+(a->next->items.startT-a->items.arrivalT+24);

                else
                  Time=Time+(a->next->items.startT-a->items.arrivalT);
             }

             a=a->next;
            }
            str="总时间："+QString("%1").arg(Time)+"\r\n";
            out<<str;

            str="总费用："+QString("%1").arg(feee)+"\r\n";
            out<<str;
            if(ER[1]==0)
            {
              str="用户选择按照该路线出发，分配的账号为"+QString("%1").arg(PsgNum)+"\r\n";
              out<<str;
            }
            else
            {
                str="用户未按该路线出发\r\n";
                out<<str;

            }

            diary.close();
    }
}

}

void Window::AskDialog(int ER,int num, PsgState* a)
{
    //查询的号码为num，ER为1说明没查到，为0说明查到了，并且a是这个被查到的旅客，输出a的路线Plan和状态
    QFile diary("diary.txt");

    if(diary.open(QFile::WriteOnly|QFile::Append))
      {
        QString str;
        QTextStream out(&diary);
        str="☆--------------------------------------------------------------------------------------☆\r\n";
        out<<str;
        str="用户在"+QString("%1").arg(time)+":00进行了旅客"+QString("%1").arg(num)+"状态查询,查询结果：\r\n";
        out<<str;

        if(ER==1)
        {

            str="不存在您所查询的旅客\r\n";
            out<<str;
        }

        else
         {

                   switch (a->state)
                   {
                       case 1:
                           str="未出发 "+getHANZICity(a->Plan->items.StartC)+"\r\n";
                           out<<str;
                           break;
                       case 2:
                           str="飞机上 "+QString::fromStdString(a->FPlan->items.ID)+" "+getHANZICity(a->Plan->items.StartC)+"->"+getHANZICity(a->Plan->items.ArrivC)+"\r\n";
                           out<<str;
                           break;
                       case 3:
                           str="火车上 "+QString::fromStdString(a->FPlan->items.ID)+" "+getHANZICity(a->Plan->items.StartC)+"->"+getHANZICity(a->Plan->items.ArrivC)+"\r\n";
                           out<<str;
                           break;
                       case 4:
                           str="汽车上 "+QString::fromStdString(a->FPlan->items.ID)+" "+getHANZICity(a->Plan->items.StartC)+"->"+getHANZICity(a->Plan->items.ArrivC)+"\r\n";
                           out<<str;
                           break;
                       case 5:
                           str="等待换乘 "+getHANZICity(a->Plan->items.StartC)+"\r\n";
                           out<<str;
                           break;
                       case 6:
                           str="已到达 "+getHANZICity(a->ArrivC)+"\r\n";
                           out<<str;
                           break;
                       }
                       str="已出发时间："+QString("%1").arg(a->Gotime)+"\r\n";
                       out<<str;
                       str="该旅客路线为：\r\n";
                       out<<str;
                       int Time=0;
                       int feee=0;

                       ListPtr b=NULL;
                       b=MAP.PATH;
                       while(b!=NULL)
                       {


                               str=getWay(b->items.flag)+" "+QString::fromStdString(b->items.ID)+" "+getHANZICity(b->items.StartC)+"->"
                                +getHANZICity(b->items.ArrivC)+" 出发时间为:"+QString("%1").arg(b->items.startT)
                                +":00 到达时间为："+QString("%1").arg(b->items.arrivalT)+":00 费用为:"+QString("%1").arg(b->items.fee)
                                +" 所需时间为："+QString("%1").arg(b->items.consumeT)+"\r\n";

                              out<<str;


                         Time=Time+b->items.consumeT;
                         feee=feee+b->items.fee;
                         if(b->next)
                         {
                            if((b->next->items.startT-b->items.arrivalT)<0)

                              Time=Time+(b->next->items.startT-b->items.arrivalT+24);

                            else
                              Time=Time+(b->next->items.startT-b->items.arrivalT);
                         }

                         b=b->next;
                        }
                        str="总时间："+QString("%1").arg(Time)+"\r\n";
                        out<<str;
                        str="总费用："+QString("%1").arg(feee)+"\r\n";
                        out<<str;

            }


            diary.close();
}
}

void Window::ChangeStateDialog()
{
    //输出所有旅客的状态，第一个旅客的地址为Psg
    QFile diary("diary.txt");
    if(diary.open(QFile::WriteOnly|QFile::Append))
    {
        QTextStream out(&diary);
        QString str;
        str="☆--------------------------------------------------------------------------------------☆\r\n";
        out<<str;

        str="有旅客状态改变：\r\n";
        out<<str;
        PsgState* a=Psg;
        while(a)
        {

          str="旅客"+QString("%1").arg(a->Num)+"号状态为：";
          out<<str;
          switch (a->state)
          {
          case 1:
              str="未出发 "+getHANZICity(a->Plan->items.StartC)+"\r\n";
              out<<str;
              break;
          case 2:
              str="飞机上 "+QString::fromStdString(a->FPlan->items.ID)+" "+getHANZICity(a->Plan->items.StartC)+"->"+getHANZICity(a->Plan->items.ArrivC)+"\r\n";
              out<<str;
              break;
          case 3:
              str="火车上 "+QString::fromStdString(a->FPlan->items.ID)+" "+getHANZICity(a->Plan->items.StartC)+"->"+getHANZICity(a->Plan->items.ArrivC)+"\r\n";
              out<<str;
              break;
          case 4:
              str="汽车上 "+QString::fromStdString(a->FPlan->items.ID)+" "+getHANZICity(a->Plan->items.StartC)+"->"+getHANZICity(a->Plan->items.ArrivC)+"\r\n";
              out<<str;
              break;
          case 5:
              str="等待换乘 "+getHANZICity(a->Plan->items.StartC)+"\r\n";
              out<<str;
              break;
          case 6:
              str="已到达 "+getHANZICity(a->ArrivC)+"\r\n";
              out<<str;
              break;
           }
           str="已出发时间："+QString("%1").arg(a->Gotime)+"\r\n";
           out<<str;

            a=a->nextPsg;
    }

    diary.close();
    }
}

void Window::ChangeDialog(int ER[], int num, int TCity, int strategy,int LimitTime)
{
    //num,表示查的号码，ER是10的时候表示没有这个人，01时表示没有路线，11时表示有路线不出发（路线为MAP.PATH可以直接用），00表示出发。
    QFile diary("diary.txt");
    if(diary.open(QFile::WriteOnly|QFile::Append))
    {
        QTextStream out(&diary);
        QString str;

        str="☆--------------------------------------------------------------------------------------☆\r\n";
        out<<str;

        str="用户在"+QString("%1").arg(time)+":00申请改变路线\r\n";
        out<<str;
        if((ER[0]==1)&&(ER[1]==0))
        {
            str="不存在用户所查询的旅客\r\n";
            out<<str;
        }
        else
        {
            str="想要改变旅客号为"+QString("%1").arg(num)+"\r\n";
            out<<str;
            str="终点："+getHANZICity(MAP.getCityName(TCity))+"\r\n";
            out<<str;
            str="经过城市：";
            if(MAP.Pass[0].pass==1) str+="北京\t";
            if(MAP.Pass[1].pass==1) str+="石家庄\t";
            if(MAP.Pass[2].pass==1) str+="济南\t";
            if(MAP.Pass[3].pass==1) str+="呼和浩特\t";
            if(MAP.Pass[4].pass==1) str+="哈尔滨\t";
            if(MAP.Pass[5].pass==1) str+="乌鲁木齐\t";
            if(MAP.Pass[6].pass==1) str+="南昌\t";
            if(MAP.Pass[7].pass==1) str+="武汉\t";
            if(MAP.Pass[8].pass==1) str+="柳州\t";
            if(MAP.Pass[9].pass==1) str+="成都\t";
            if(MAP.Pass[10].pass==1) str+="厦门\t";
            str+="\r\n";
            out<<str;
            str="策略：";
            switch(strategy)
            {
                case 1:
                    str+="最省钱策略";
                    break;
                case 2:
                    str+="最省时间策略";
                    break;
                case 3:
                    str+="限时最省钱策略 限时为"+QString("%1").arg(LimitTime);
                    break;

            }
            str+="\r\n";
            out<<str;
            str="查询结果为：";

            //在这里判断a是否为空 若为空则说不存在此路线 否则输出路线
            if((ER[0]==0)&&(ER[1]==1))
            {
                str+="不存在此路线\r\n";
                out<<str;
            }

            else
            {
               str+="\r\n";
               out<<str;
               int Time=0;
               int feee=0;

               ListPtr a=NULL;
               a=MAP.PATH;
               while(a!=NULL)
               {
                   str=getWay(a->items.flag)+" "+QString::fromStdString(a->items.ID)+" "+getHANZICity(a->items.StartC)+"->"
                           +getHANZICity(a->items.ArrivC)+" 出发时间为:"+QString("%1").arg(a->items.startT)
                           +":00 到达时间为："+QString("%1").arg(a->items.arrivalT)+":00 费用为:"+QString("%1").arg(a->items.fee)
                           +" 所需时间为："+QString("%1").arg(a->items.consumeT)+"\r\n";

                    out<<str;


                 Time=Time+a->items.consumeT;
                 feee=feee+a->items.fee;
                 if(a->next)
                 {
                    if((a->next->items.startT-a->items.arrivalT)<0)

                      Time=Time+(a->next->items.startT-a->items.arrivalT+24);

                    else
                      Time=Time+(a->next->items.startT-a->items.arrivalT);
                 }

                 a=a->next;
                }
                str="总时间："+QString("%1").arg(Time)+"\r\n";
                out<<str;

                str="总费用："+QString("%1").arg(feee)+"\r\n";
                out<<str;
                if((ER[0]==0)&&(ER[1]==0))
                {
                  str="用户选择按照更改后的路线出发\r\n";
                  out<<str;
                }

                else
                {
                    str="用户未按该路线出发\r\n";
                    out<<str;
                }

        //在这里判断a是否为空 若为空则说不存在此路线 否则输出路线




        }

            diary.close();
}



}
}

Window::~Window()
{


    delete cbo_StartCity;
    delete cbo_TermiCity;
    delete t;
    delete ShowAllPlan;
    delete ShowAllState;
    for(int i=0;i<3;i++) delete s[i];
    for(int i=0;i<11;i++) delete c[i];


    delete Pic;
    PsgState * a=Psg;
    while(Psg)
    {
        a=Psg;
        Psg=Psg->nextPsg;
        delete a;
    }
}
