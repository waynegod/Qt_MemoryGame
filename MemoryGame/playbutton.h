#ifndef PLAYBUTTON_H
#define PLAYBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QIcon>

class Playbutton : public QPushButton
{
    Q_OBJECT
public:
    explicit Playbutton(QWidget *parent = nullptr);
    static int ID_count;
    static int ANS_count;
    int getID();
    int answer();
    void addID();
    void Reset();
    void answer(int ans);

signals:

public slots:

private:
    int ID_btn = 0;
    int ANS_back = 0;
};

#endif // PLAYBUTTON_H
