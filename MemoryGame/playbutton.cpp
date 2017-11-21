#include "playbutton.h"
#include <QIcon>
#include <QPushButton>
#include <QDebug>

Playbutton::Playbutton(QWidget *parent) :
    QPushButton(parent)
{
    ID_btn = ID_count;
    ANS_back = ANS_count;
}
int Playbutton::getID()
{
    return ID_btn;
}

void Playbutton::addID()
{
    ID_count++;
}
void Playbutton::Reset()
{
    ID_count = 0;
}
void Playbutton::answer(int ans)
{
    ANS_back = ans;
}
int Playbutton::answer()
{
    return ANS_back;
}
int Playbutton::ID_count = 0;
int Playbutton::ANS_count = 0;
