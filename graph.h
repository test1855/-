#ifndef GRAPH
#define GRAPH
# include<iostream>
# include<string>
# include<windows.h>
# include<qstring.h>
#include <qfile.h>
#include <qtextstream.h>
using namespace std;


#define MAX 11

typedef struct List {
    string StartC;//出发城市
    string ArrivC;//到达城市
    int flag;//交通方式
    int startT;//出发时间
    int consumeT;//用时
    int arrivalT;//到达时间
    string ID;//交通工具的ID
    int fee;//价格
} List;

/*时刻表节点、指针*/
typedef struct ListNode {
    List items;
    struct ListNode* next;
} ListNode;
typedef ListNode* ListPtr;

/*表节点*/
typedef struct ArcNode {
    string terminal;	//终点信息
    ListPtr way;		//交通方式，链表，并且按金钱由小到大排序
    struct ArcNode* next;
} ArcNode;
typedef ArcNode* ArcPtr;

/*头结点*/
typedef struct VNode {
    string start;
    ArcPtr first;
} VNode;

typedef struct PassCity {
    int flag;
    int pass;
}*CityPtr;


class Graph {
    private:
        VNode citynode[MAX];
        ArcPtr preAPtr[MAX];
        int visited[MAX];//标记城市是否被遍历
        int pathNum;//遍历后生成的路径数量
    public:

        void OutPutPlan(QString &);//用于输出生成的计划
        ListPtr PATH;//最终生成的路线
        VNode *All;//存放不考虑交通工具的所有可达路径
        VNode Cur;//遍历的当前路径
        struct PassCity Pass[MAX];//记录经过城市信息
        ArcPtr init_ArcPtr(int i,int j);
        ArcPtr create_ArcPtr(int i,int j,QTextStream& myFile);
        Graph();
        void CreatGraph();
        int getCityNum(string);//城市名和序号的转换
        int getHANZICityNum(string);//汉字的城市名和序号的转换
        string getCityName(int);//城市序号和城市名的转换
        void RinitNum();
        void initNum();
        void assign_List(List& ,List);
        void Copy(ArcPtr& ,ArcPtr );
        void DFS(int,int);//参数是起始城市序号和终止城市序号
        void Money();//最省钱策略
        void Time();//最省时间策略
        void Time_Money(int);//限时最省钱策略
        int DFSMoney(ListPtr &,ListPtr &,ArcPtr ,int &,int& ,int );
        ~Graph();
};

class PsgState {


    public:
        ListPtr Plan;//该旅客的总计划
        int Gotime;//已经出发时间
        int state;//状态
        int Num;//序号
        int OnTime;//该用户在当前交通工具上的时间
        string ArrivC;//目的地
        ListPtr FPlan;//旅客还未出发和正在旅行的部分，根据旅客的状态动态变化，便于计算旅客状态
        PsgState();
        PsgState(ListPtr,int);
        void ChangeState();//时间改变时的状态改变
        void OutState(QString &);//输出旅客状态
        void OutPlan(QString &);//输出旅客计划
        PsgState* nextPsg;//下一个旅客的地址
        ~PsgState();
        string getCityName(int);

};



#endif // GRAPH

