#include "graph.h"
#include <qfile.h>
#include <qtextstream.h>
void Graph::assign_List(List& a,List value)
{
    a.flag=value.flag;
    a.ID=value.ID;
    a.StartC=value.StartC;
    a.ArrivC=value.ArrivC;
    a.startT=value.startT;
    a.consumeT=value.consumeT;
    a.arrivalT=value.arrivalT;
    a.fee=value.fee;
}
QString getHANZICity(string city)
{
    if(city=="beijing")
        return "北京";
    else if(city=="shijiazhuang")
        return "石家庄";
    else if(city.compare("jinan")==0)
        return "济南";
    else if(city.compare("huhehaote")==0)
        return "呼和浩特";
    else if(city.compare("haerbin")==0)
        return "哈尔滨";
    else if(city.compare("wulumuqi")==0)
        return "乌鲁木齐";
    else if(city.compare("nanchang")==0)
        return "南昌";
    else if(city.compare("wuhan")==0)
        return "武汉";
    else if(city.compare("liuzhou")==0)
        return "柳州";
    else if(city.compare("chengdu")==0)
        return "成都";
    else if(city.compare("xiamen")==0)
        return "厦门";
    return "无此城市。";
}

int Graph::getHANZICityNum(string city)
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
    return -1;
}

int Graph::getCityNum(string city)
{
    if(city=="beijing")
        return 0;
    else if(city=="shijiazhuang")
        return 1;
    else if(city.compare("jinan")==0)
        return 2;
    else if(city.compare("huhehaote")==0)
        return 3;
    else if(city.compare("haerbin")==0)
        return 4;
    else if(city.compare("wulumuqi")==0)
        return 5;
    else if(city.compare("nanchang")==0)
        return 6;
    else if(city.compare("wuhan")==0)
        return 7;
    else if(city.compare("liuzhou")==0)
        return 8;
    else if(city.compare("chengdu")==0)
        return 9;
    else if(city.compare("xiamen")==0)
        return 10;
    return -1;
}


string Graph::getCityName(int i)
{
    switch(i)
    {
        case 0:
            return "beijing";
        case 1:
            return "shijiazhuang";
        case 2:
            return "jinan";
        case 3:
            return "huhehaote";
        case 4:
            return "haerbin";
        case 5:
            return "wulumuqi";
        case 6:
            return "nanchang";
        case 7:
            return "wuhan";
        case 8:
            return "liuzhou";
        case 9:
            return "chengdu";
        case 10:
            return "xiamen";
    }
    return "不存在该城市";
}

Graph::Graph(void)//初始化城市结点
{
    citynode[0].start="beijing";
    citynode[1].start="shijiazhuang";
    citynode[2].start="jinan";
    citynode[3].start="huhehaote";
    citynode[4].start="haerbin";
    citynode[5].start="wulumuqi";
    citynode[6].start="nanchang";
    citynode[7].start="wuhan";
    citynode[8].start="liuzhou";
    citynode[9].start="chengdu";
    citynode[10].start="xiamen";
    for(int i=0;i<MAX;i++)
    {
        citynode[i].first=NULL;
        preAPtr[i]=NULL;
        visited[i]=0;
        Pass[i].flag=0;
        Pass[i].pass=0;
    }

}

ArcPtr Graph::init_ArcPtr(int i,int j)//创建的表节点的函数
{
    ArcPtr current;
    current=new ArcNode;//申请表节点内存

    if(current)//若内存申请成功，则进行表节点的初始化赋值
    {
        current->terminal=getCityName(j);
        current->next=NULL;
        current->way=NULL;

        if(!preAPtr[i])
        {
            citynode[i].first=current;
            preAPtr[i]=current;
        }
        else
        {
            preAPtr[i]->next=current;
            preAPtr[i]=current;
        }
    }
    return current;
}

ArcPtr Graph::create_ArcPtr(int i,int j,QTextStream& txtInput)//创建表节点，并将文件中中读取的起始点，时刻表的信息存储在表节点中
{
    QString Str;
    List xList;
    ArcPtr current;
    ListPtr curway;
    ListPtr preway=NULL,latway=NULL;

 //   string s;
    current=init_ArcPtr(i,j);//调用表节点申请函数

    while(xList.flag!=2)
    {
        Str = txtInput.readLine(' ');
        QStringList qlist = Str.split(" ");
        xList.flag=(qlist.at(0)).toInt();
        xList.ID=(qlist.at(1)).toStdString();
        xList.startT=(qlist.at(2)).toInt();
        xList.consumeT=(qlist.at(3)).toInt();
        xList.arrivalT=(qlist.at(4)).toInt();
        xList.fee=(qlist.at(5)).toInt();
        xList.StartC=getCityName(i);
        xList.ArrivC=current->terminal;
        //读取文件信息
        curway=new ListNode;//创建信息链表，储存时刻表信息
        assign_List(curway->items,xList);//进行链表赋值
        curway->next=NULL;

        if(preway)//若申请内存成功
        {
            for(latway=current->way,preway=NULL; latway ;latway=latway->next)//遍历链表，按金钱从小到大的插入新创建的链表
            {
                if((latway->items).fee > (curway->items).fee )
                {
                    if(preway)
                    {
                        preway->next=curway;
                        curway->next=latway;
                    }
                    else
                    {
                        current->way=curway;
                        curway->next=latway;
                        preway=curway;
                    }
                    break;
                }
                else
                {
                    preway=latway;
                }
            }

            if(!latway)
                preway->next=curway;
        }
        else
        {
            current->way=curway;
            preway=curway;
        }
    }
//    if(!txtInput.atEnd())
//    {
//        txtInput.readLine();
//    }
    return current;//返回表节点指针
}


void Graph::CreatGraph()//创建图函数
{
    string s;
    QString Str;
    int sid,eid,count=0;
    QFile f(":/timetable/TimeTable.txt");
    if(f.open(QFile::ReadOnly))
    {

        QTextStream txtInput(&f);


        while(!txtInput.atEnd())
        {
            Str = txtInput.readLine(' ');//读取起点和终点

            QStringList list = Str.split(" ");
            sid=getCityNum((list.at(0)).toStdString());
            eid=getCityNum((list.at(1)).toStdString());
            create_ArcPtr(sid,eid,txtInput);//调用创建表节点函数
            count++;
        }
    }
}

Graph::~Graph()//图表的析构函数，释放内存
{
    ArcPtr p=NULL,tempp=NULL;
    ListPtr a=NULL,tempa=NULL;
    for(int i=0;i<MAX;i++)
    {
        p=citynode[i].first;
        for(;p;p=p->next)
        {
            tempp=p;
            for(a=p->way;a;a=a->next)
            {
                tempa=a;
                delete tempa;
            }
            delete tempp;
        }
    }
}

void Graph::Money()//最省钱策略
{
    int i,Cheap=0;//i用于循环，Cheap是最后筛选出的最省钱的路线的序号
    int ttlMoneyMin,ttlMoney;//ttlMoneyMin是所有路线中最省钱的路线的花费，ttlMoney是当前路线耗费的最少金钱
    ttlMoneyMin=0;
    ArcPtr p=NULL;//用于最后生成路线
    ListPtr cur=NULL,pre=NULL;

    if(All)//如果遍历之后一可达路线的话
    {
        p=All[0].first;
        for(p=All[0].first;p!=NULL;p=p->next)//计算第一条路线的最小花费，由于交通方式按花费由小到大排列，只需算第一种交通方式即可
        {
            ttlMoneyMin=ttlMoneyMin+p->way->items.fee;
        }

        for(i=1;i<(pathNum<60000?pathNum:60000);i++) //计算剩余路线的最小花费，并将所有路线中最小花费比较得到最省钱路线。
        {
            ttlMoney=0;
            for(p=All[i].first;p!=NULL;p=p->next)
            {
                ttlMoney=ttlMoney+p->way->items.fee;
            }
            if(ttlMoneyMin>ttlMoney)
            {
                ttlMoneyMin=ttlMoney;
                Cheap=i;
            }
        }



        for(p=(All[Cheap]).first;p!=NULL;p=p->next)//生成花费最小的路线
        {
            cur=new ListNode;
            assign_List(cur->items,p->way->items);
            if(PATH==NULL)
            {
                PATH=cur;
                pre=PATH;
            }
            else
            {
                pre->next=cur;
                pre=cur;
            }
            cur->next=NULL;
            cur=NULL;
        }
    }
    else PATH=NULL;


}

void Graph::Time()//最省时间策略
{
    int i,Save=0;//i用于循环，Save表示在许多路径里挑选出的最省时间的路径
    int ttlTimeMin,ttlTime;//ttlMoneyMin是所有路线中最时间的路线的用时，ttlMoney是当前路线耗费的最少用时
    int arrivT,SarrivT;//从到达城市A到到达下一个城市的时间，从到达城市A到到达下一个城市的最短时间
    ttlTimeMin=0;
    ArcPtr p=NULL;
    List Short1,Short2;//算到达时间需要
    ListPtr cur=NULL,pre=NULL,q=NULL;

    if(All)
    {
        p=All[0].first;//算第一条路线的最短时间，从上第一个交通工具开始计时
        q=p->way;
        for(q=q->next;q!=NULL;q=q->next)
        {
            if(q->items.consumeT<p->way->items.consumeT)//将用时最短的换到第一个交通工具
            {
                assign_List(Short1,q->items);
                assign_List(q->items,p->way->items);
                assign_List(p->way->items,Short1);
            }
        }
        ttlTimeMin=p->way->items.consumeT;
        for(p=p->next;p!=NULL;p=p->next)
        {
            q=p->way;
            if(q->items.startT>=Short1.arrivalT) SarrivT=q->items.startT-Short1.arrivalT+q->items.consumeT;
            else SarrivT=q->items.startT-Short1.arrivalT+q->items.consumeT+24;
            for(q=q->next;q!=NULL;q=q->next)
            {
                if(q->items.startT>=Short1.arrivalT) arrivT=q->items.startT-Short1.arrivalT+q->items.consumeT;
                else arrivT=q->items.startT-Short1.arrivalT+q->items.consumeT+24;
                if(SarrivT>arrivT)//将用时最短的交换到交通方式链表的第一个
                {
                    SarrivT=arrivT;
                    assign_List(Short2,q->items);
                    assign_List(q->items,p->way->items);
                    assign_List(p->way->items,Short2);
                }
            }
            ttlTimeMin=ttlTimeMin+SarrivT;
            assign_List(Short1,Short2);
        }



        for(i=1;i<(pathNum<60000?pathNum:60000);i++)//算剩余路径每条路线的最短时间，并比较得出用时最短的路线
        {
            p=(All[i]).first;
            q=p->way;
            for(q=q->next;q!=NULL;q=q->next)
            {
                if(q->items.consumeT<p->way->items.consumeT)
                {
                    assign_List(Short1,q->items);
                    assign_List(q->items,p->way->items);
                    assign_List(p->way->items,Short1);
                }
            }
            ttlTime=Short1.consumeT;

            for(p=p->next;p!=NULL;p=p->next)
            {
                q=p->way;
                if(q->items.startT>=Short1.arrivalT) SarrivT=q->items.startT-Short1.arrivalT+q->items.consumeT;
                else SarrivT=q->items.startT-Short1.arrivalT+q->items.consumeT+24;
                for(q=q->next;q!=NULL;q=q->next)
                {
                    if(q->items.startT>=Short1.arrivalT) arrivT=q->items.startT-Short1.arrivalT+q->items.consumeT;
                    else arrivT=q->items.startT-Short1.arrivalT+q->items.consumeT+24;
                    if(SarrivT>arrivT)//将用时最短的交换到交通方式链表的第一个
                    {
                        SarrivT=arrivT;
                        assign_List(Short2,q->items);
                        assign_List(q->items,p->way->items);
                        assign_List(p->way->items,Short2);
                    }
                }
                ttlTime=ttlTime+SarrivT;
                assign_List(Short1,Short2);

            }
            if(ttlTimeMin>ttlTime)
            {
                ttlTimeMin=ttlTime;
                Save=i;
            }
        }
        for(p=(All[Save]).first;p!=NULL;p=p->next)//生成最省时间路径
        {
            cur=new ListNode;
            assign_List(cur->items,p->way->items);
            if(PATH==NULL)
            {
                PATH=cur;
                pre=PATH;
            }
            else
            {
                pre->next=cur;
                pre=cur;
            }
            cur->next=NULL;
            cur=NULL;
        }

    }
    else PATH=NULL;


}

int Graph::DFSMoney(ListPtr &cur, ListPtr &pre, ArcPtr p, int &exist, int &t, int Limit)
{
    int t1=t,t2=t,M=0;
    ListPtr C,add=NULL,ppre=NULL;
    if(p==NULL) return 0;
    C=p->way;
    while(C)
    {
        t1=t;
        if(cur==NULL)
        {
            t1+=C->items.consumeT;
        }
        else
        {
            if(C->items.startT>pre->items.arrivalT) t1+=C->items.startT-pre->items.arrivalT+C->items.consumeT;
            else t1+=C->items.startT-pre->items.arrivalT+C->items.consumeT+24;
        }
        if(t1<=Limit)
        {
            t=t1;
            if(p->next==NULL) exist=1;
            add=new ListNode;
            assign_List(add->items,C->items);
            add->next=NULL;
            if(cur==NULL)
            {
                ppre=add;
                cur=add;
                pre=add;
                add=NULL;
            }
            else
            {
                ppre=pre;
                pre->next=add;
                pre=add;
                add=NULL;
            }
            M=C->items.fee+DFSMoney(cur,pre,p->next,exist,t,Limit);
            if(exist==1&&t<=Limit) return M;
            else
            {
                    if(ppre->next)
                    {
                        delete ppre->next;
                        ppre->next=NULL;
                        pre=ppre;
                    }
                    else
                    {
                        delete ppre;
                        cur=NULL;
                        pre=NULL;
                    }


                C=C->next;
                t=t2;
            }
        }
        else C=C->next;
    }
    return 32767;

}

void Graph::Time_Money(int Limit)//满足时间条件里最省钱
{
    int i;
    int ttlMoneyMin=32767,ttlMoney=32767;
    int ttlTime;

    ArcPtr p=NULL;
    ListPtr cur=NULL,pre=NULL;

    int exist=0;//是否存在
   if(All)
    {
        for(i=0;i<(pathNum<60000?pathNum:60000);i++)
        {
            p=All[i].first;
            exist=0;
            ttlTime=0;
            cur=NULL,pre=NULL;
            //小的DFS
            ttlMoney=DFSMoney(cur,pre,p,exist,ttlTime,Limit);
            //如果存在，则与当前金钱比较，如果满足，则赋值给PATH
            if(exist==1)
            {
                if(ttlMoneyMin>ttlMoney)
                {
                    ListPtr TEMP;
                    while(PATH)
                    {
                        TEMP=PATH;
                        PATH=PATH->next;
                        delete TEMP;
                    }
                    PATH=cur;
                }
                else
                {
                    ListPtr TEMP;
                    while(cur)
                    {
                        TEMP=cur;
                        cur=cur->next;
                        delete TEMP;
                    }
                    cur=NULL;
                }
            }
        }
    }
}


void Graph::initNum()
{
    for(int i=0;i<MAX;i++)
    {
        visited[i]=0;
        Pass[i].flag=0;
        Pass[i].pass=0;
    }

    All = NULL;

    PATH = NULL;
    pathNum = 0;

    Cur.first=NULL;
}

void Graph::RinitNum()
{
    for(int i=0;i<MAX;i++)
    {
        visited[i]=0;
        Pass[i].flag=0;
        Pass[i].pass=0;
    }
    ArcPtr temp=NULL;
    if(pathNum>1)
    {
        for(int i=0;i<pathNum;i++)
        {
            while(All[i].first)
            {
                temp=All[i].first;
                All[i].first=All[i].first->next;
                delete temp;
            }
        }


        delete []All;
    }
    else if(pathNum==1)
    {
        while(All->first)
        {
            temp=All->first;
            All->first=All->first->next;
            delete temp;
        }
        delete All;
    }
    All = NULL;

    PATH = NULL;
    pathNum = 0;
    ArcPtr Temp;
    while(Cur.first!=NULL)
    {
        Temp=Cur.first;
        Cur.first=Cur.first->next;
        delete Temp;
    }
    Cur.first=NULL;
}


\
void Graph::Copy(ArcPtr& a,ArcPtr b)
{
    ListPtr cur=NULL,pre=NULL,d=NULL;



    d=b->way;

    a->terminal=b->terminal;
    a->way=NULL;
    a->next=NULL;
    while(d)
    {

        cur=new ListNode;
        assign_List(cur->items,d->items);
        cur->next=NULL;
        if(a->way==NULL)
        {
            a->way=cur;
            pre=a->way;
        }
        else
        {
            pre->next=cur;
            pre=cur;

        }
        d=d->next;
    }




}

void Graph::DFS(int Start, int Termi)
{
    VNode check=Cur;//用于检查经过的城市是否已经路过但标记为没路过的
    ArcPtr a=NULL,preb=NULL,curb=NULL,c=NULL,prec=NULL;
    visited[Start]=1;//当前城市标记为已遍历
    ArcPtr p=citynode[Start].first,s=NULL;
    while(p)//当还有点没有被遍历时遍历
    {
        if(pathNum>=60000) return;//路线数过大时停止遍历，返回现有路线
        if(Cur.first==NULL)//先将该边添加到生成的路径中
        {
            a=new ArcNode;
            Copy(a,p);
            Cur.first=a;
        }
        else
        {
            for(c=Cur.first;c!=NULL;c=c->next)
            {
                prec=c;
            }
            a=new ArcNode;
            Copy(a,p);
            prec->next=a;
        }


        if(getCityNum(p->terminal)==Termi)//如果已经到了终点
        {
            int ok=1;
            for(int i=0;i<MAX; i++)//检查需要经过的城市是否经过
            {
                if(Pass[i].pass==1&&Pass[i].flag==0)
                {
                    ok=0;
                    break;
                }
            }
            if(ok==1)//需要经过的都遍历到了，将该满足条件的路径保存到All中，All保存所有可以到达终点的路径
            {

                if(All==NULL)
                {
                    while(All==NULL) (All)=new VNode;


                }
                else
                {
                    VNode* AllNew = new VNode[pathNum+1];
                    for(int O=0;O<pathNum;O++)
                    {
                        AllNew[O].first=All[O].first;
                        AllNew[O].start=All[O].start;
                    }


                    if(pathNum==1) delete All;
                    else delete[] All;
                    All = AllNew;
                }
                    All[pathNum].first=NULL;
                    All[pathNum].start=Cur.start;

                    for(s=Cur.first;s!=NULL;s=s->next)
                    {
                        curb=new ArcNode;
                        Copy(curb,s);
                        curb->next=NULL;
                        if(All[pathNum].first==NULL)
                        {
                            All[pathNum].first=curb;
                            preb=curb;
                        }
                        else
                        {
                            preb->next=curb;
                            preb=curb;
                        }
                        curb=NULL;

                    }
                pathNum++;//可达路径数+1

            }
            if(Cur.first->next==NULL)//已经到终点就不需要继续深度遍历，将该城市释放，并遍历下一个城市
            {
                free(Cur.first);
                Cur.first=NULL;
            }
            else
            {
                for(c=Cur.first;c->next!=NULL;c=c->next)
                {
                    prec=c;
                }

                prec->next=NULL;
                free (c);
            }

            p=p->next;
            continue;
        }
        for(int i=0;i<MAX;i++) //检查该地点是否为旅客要求经过地点
        {
            if(getCityNum(p->terminal)==i&&Pass[i].pass==1&&Pass[i].flag==0)//如果是则记录，并将到达经过城市的前一个城市标为未遍历过，以便
            {                                                               //当经过的城市没有别的路走时可以返回来之前的城市
                Pass[i].flag=1;
                visited[Start]=0;
                break;
            }
        }
        check=Cur;
        for(int i=0;i<MAX;i++) //为防止无限循环，检查是否有已经经过的且为旅客要求经过的城市标记为未经过并将其改正
        {
            if(getHANZICityNum(check.start)==i&&Pass[i].pass==1&&Pass[i].flag==0)
            {
                Pass[i].flag=1;
                visited[i]=1;
                break;
            }
        }
        ArcPtr CHECK=check.first;
        while(CHECK!=NULL)//为防止无限循环，检查是否有已经经过的且为旅客要求经过的城市标记为未经过并将其改正
        {
            for(int i=0;i<MAX;i++)
            {
                if(getCityNum(CHECK->terminal)==i&&Pass[i].pass==1&&Pass[i].flag==0)
                {
                    Pass[i].flag=1;

                    visited[i]=1;
                    break;
                }
            }
            CHECK=CHECK->next;
        }
        int u=getCityNum(p->terminal);
        if(!visited[u])
        {
            DFS(u,Termi);//递归遍历
        }
        if(Cur.first->next==NULL)//在路径中释放该点
        {
            free(Cur.first);
            Cur.first=NULL;
        }
        else
        {
            for(c=Cur.first;c->next!=NULL;c=c->next)
            {
                prec=c;
            }
            visited[getCityNum(prec->way->items.ArrivC)]=1;
            prec->next=NULL;
            free (c);
        }
        p=p->next;
    }
    for(int i=0;i<MAX;i++) //检查该地点是否为旅客要求经过地点，若是，则更改经过的标记
    {
        if(Start==i)
        {
            Pass[i].flag=0;
            break;
        }
    }

    visited[Start]=0;//将该地标为未遍历

}

QString getWay(int i)
{
    switch(i)
    {
        case 0:
            return "飞机";
        case 1:
            return "火车";
        case 2:
            return "汽车";

    }
    return "错误";
}

void Graph::OutPutPlan(QString &str1)
{
    int timee=0;
    int feee=0;

    //cout.width(12);
    str1="路线为：\n";
    ListPtr path=PATH;
    while(path!=NULL)
    {

      str1+=getWay(path->items.flag)+" "+QString::fromStdString(path->items.ID)+" "+getHANZICity(path->items.StartC)+"->"+
              getHANZICity(path->items.ArrivC)+" 出发时间为:"+QString("%1").arg(path->items.startT)+":00 到达时间为："+QString("%1").arg(path->items.arrivalT)+
              ":00 费用为:"+QString("%1").arg(path->items.fee)+" 所需时间为："+QString("%1").arg(path->items.consumeT)+"\n";

      timee=timee+path->items.consumeT;
      feee=feee+path->items.fee;
      if(path->next)
      {
        if((path->next->items.startT-path->items.arrivalT)<0)

         timee=timee+(path->next->items.startT-path->items.arrivalT+24);

        else
          timee=timee+(path->next->items.startT-path->items.arrivalT);
      }

      path=path->next;
    }
    str1+="总时间："+QString("%1").arg(timee)+"\n";

    str1+="总费用："+QString("%1").arg(feee)+"\n";
}
