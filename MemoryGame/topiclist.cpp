#include "topiclist.h"
#include <QDebug>
#include <QVector>
#include <QTime>


Topiclist::Topiclist()
{

}
int *Topiclist::get_problem(int lentgh)
{
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);//設定亂數總子，以當下時間(秒)

    static int  back_problm[25];
    for (int con = 0;con < lentgh;con++)
        back_problm[con] = con + 1;

    for(int con = 0; con < lentgh; con++)
    {
        int n1 = rand()%lentgh;//將陣列資料進行交換(打散)
        int temp = back_problm[n1];
        back_problm[n1] = back_problm[con];
        back_problm[con] = temp;
    }

    return back_problm;
}

int *Topiclist::get_position(int amount)
{

    qsrand((QDateTime::currentMSecsSinceEpoch() + QDateTime::currentMSecsSinceEpoch()) / 1000);
    static int back_position[25];
    for (int con = 0;con < amount;con++)
        back_position[con] = con + 1;

    for(int con = 0; con < amount; con++)
    {
        int n1 = rand()%amount;//將陣列資料進行交換(打散)
        int temp = back_position[n1];
        back_position[n1] = back_position[con];
        back_position[con] = temp;
    }

    /*
    for (int c = 0;c < 25;c++)
        qDebug()<<back_position[c];
*/
    return back_position;

}

void Topiclist::topic_reset()
{

}
