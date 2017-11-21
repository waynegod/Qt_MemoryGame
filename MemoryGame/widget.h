#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void set_btn();
    void set_game();
    void uiset();
    void readygame();
    void resetgame();
    ~Widget();

public slots:
    void TimerSec();
    void playtime();

private slots:
    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void slotGetNumber();

    void on_PB_range_DW_clicked();

    void on_PB_range_UP_clicked();

    void on_PB_amount_DW_clicked();

    void on_PB_amount_UP_clicked();

    void on_PB_sec_DW_clicked();

    void on_PB_sec_UP_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_PB_home_play_clicked();

private:
    Ui::Widget *ui;
    QTimer *Timer_play, *Timer_sec;
    int font_ID_mvboli;
    QString font_data_mvboli;

};

#endif // WIDGET_H
