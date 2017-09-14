#include"graph.h"
extern int PsgNum;
extern int time;
extern int isChange;
void PsgState::ChangeState()
{
    if(FPlan)
    {

        switch(state)
       {
        case 1:
            Gotime=0;
            if(time==FPlan->items.startT)
              {
                isChange=1;//表示有旅客状态改变
                switch(FPlan->items.flag)
                {
                   case 0:
                     state=2;
                     break;
                   case 1:
                     state=3;
                     break;
                   case 2:
                     state=4;
                     break;
                }
              }
            break;
        case 2:
            Gotime++;
            OnTime++;
            if(time==FPlan->items.arrivalT&&OnTime==FPlan->items.consumeT)
            {
                isChange=1;
                OnTime=0;
              FPlan=FPlan->next;
              if(FPlan)
                state=5;
              else
                state=6;

            }
            break;

        case 3:
            Gotime++;
            OnTime++;
            if(time==FPlan->items.arrivalT&&OnTime==FPlan->items.consumeT)
            {
                isChange=1;
                OnTime=0;
              FPlan=FPlan->next;
              if(FPlan)
                state=5;
              else
                state=6;


            }
            break;
        case 4:
            Gotime++;
            OnTime++;
            if(time==FPlan->items.arrivalT&&OnTime==FPlan->items.consumeT)
            {
                isChange=1;
                OnTime=0;
              FPlan=FPlan->next;
              if(FPlan)
                state=5;
              else
                state=6;


            }
            break;
        case 5:
            Gotime++;

              if(time==FPlan->items.startT)
              {
                  isChange=1;
                switch(FPlan->items.flag)
                {
                   case 0:
                     state=2;
                     break;
                   case 1:
                     state=3;
                     break;
                   case 2:
                     state=4;
                     break;
                }
              }
             break;
        case 6:
            if(FPlan)
            {
                isChange=1;
                if(time==FPlan->items.startT)
                {

                  switch(FPlan->items.flag)
                  {
                   case 0:
                     state=2;
                     break;
                   case 1:
                     state=3;
                     break;
                   case 2:
                     state=4;
                     break;
                  }
                }
                else

                    state=5;

            }
            else
              break;



        }
            //如果在已经到达的情况下FPlan不为空，则再根据情况继续判断




    }
    else
       state=6;


}
string PsgState::getCityName(int i)
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

PsgState::PsgState(ListPtr Cur,int TermiCity)
{
    Num=PsgNum;
    Plan=Cur;
    FPlan=Cur;
    Gotime=0;
    OnTime=0;
    state=1;
    ArrivC=getCityName(TermiCity);
    nextPsg=NULL;
}

PsgState::PsgState()
{
    Num=0;
    Plan=NULL;
    FPlan=NULL;
    Gotime=0;
    OnTime=0;
    state=1;
    ArrivC=" ";
}

PsgState::~PsgState()
{
    ListPtr Temp=NULL;
    while(Plan!=NULL)
    {
        Temp=Plan;
        Plan=Plan->next;
        delete Temp;
    }
}
extern QString getHANZICity(string );

void PsgState::OutState(QString &str)
{



        str+="旅客"+QString("%1").arg(Num)+"号状态：" ;

        switch(state)
        {
            case 1:

                str+= "未出发 "+getHANZICity(Plan->items.StartC)+"\n";
                break;

            case 2:

                str+= "飞机上 "+QString::fromStdString(FPlan->items.ID)+" "+getHANZICity(FPlan->items.StartC)+"->"+getHANZICity(FPlan->items.ArrivC)+"\n";
                break;

            case 3:

                str+= "火车上"+QString::fromStdString(FPlan->items.ID)+" "+getHANZICity(FPlan->items.StartC)+"->"+getHANZICity(FPlan->items.ArrivC)+"\n";
                break;

            case 4:
                str+= "汽车上"+QString::fromStdString(FPlan->items.ID)+" "+getHANZICity(FPlan->items.StartC)+"->"+getHANZICity(FPlan->items.ArrivC)+"\n";
                break;

            case 5:
                str+= "等待换乘 "+getHANZICity(FPlan->items.StartC)+"\n";
                break;

            case 6:
                str+= "已到达 "+getHANZICity(ArrivC)+"\n";
                break;

            }
            str+= "已出发时间："+QString("%1").arg(Gotime)+"\n";




}

extern QString getWay(int);

void PsgState::OutPlan(QString &str1)
{
    int timee=0;
    int feee=0;

    //cout.width(12);
    str1="路线为：\n";
    ListPtr path=Plan;
    while(path!=NULL)
    {

      str1+=getWay(path->items.flag)+" "+QString::fromStdString(path->items.ID)+" "+getHANZICity(path->items.StartC)+"->"+
              getHANZICity(path->items.ArrivC)+" 出发时间为:"+QString("%1").arg(path->items.startT)+" 到达时间为："+QString("%1").arg(path->items.arrivalT)+
              " 费用为:"+QString("%1").arg(path->items.fee)+" 所需时间为："+QString("%1").arg(path->items.consumeT)+"\n";

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
