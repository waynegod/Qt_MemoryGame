#ifndef TOPICLIST_H
#define TOPICLIST_H
#include <QVector>

class Topiclist
{
public:
    Topiclist();
    //static int number;
    int *get_problem(int lentgh);
    int *get_position(int amount);
    void topic_reset();

private:


};

#endif // TOPICLIST_H
