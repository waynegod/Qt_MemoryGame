#include "widget.h"
#include "ui_widget.h"
#include "playbutton.h"
#include "topiclist.h"
#include <QDebug>
#include <QMessageBox>
#include <QFontDatabase>

int *pose ,*qus ,*ans;
int range ,amount ,sec;
int ans_count = 1;
int ans_wrong = 0;
float count_time = 0;
bool game_Enabled;
bool game_over;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);//跳至頁面0
    Timer_play = new QTimer();//遊戲時間計時器
    connect(Timer_play,SIGNAL(timeout()),this,SLOT(playtime()));
    Timer_sec = new QTimer();//準備時間計時器
    connect(Timer_sec,SIGNAL(timeout()),this,SLOT(TimerSec()));
    font_ID_mvboli = QFontDatabase::addApplicationFont(":/fonts/Resourcesbox/mvboli.ttf");
    font_data_mvboli = QFontDatabase::applicationFontFamilies(font_ID_mvboli).at(0);
}

void Widget::uiset()
{
    QPixmap playicon(":/icon/Resourcesbox/button/btplay.png");
    ui->PB_home_play->setMaximumSize(QSize(ui->PB_home_play->size()));
    ui->PB_home_play->setFocusPolicy(Qt::NoFocus);
    ui->PB_home_play->setFlat(true);

    ui->PB_home_play->setIcon(playicon);
    ui->PB_home_play->setIconSize(ui->PB_home_play->size());
    //ui->PB_home_play->setIconSize(QSize(playicon.size().scaled(ui->PB_home_play->size(),Qt::IgnoreAspectRatio)));
    qDebug()<<playicon.size();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_PB_home_play_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);//跳至頁面1
}

void Widget::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);//跳至頁面2

    range = ui->label_range->text().toInt();//取得設定值
    amount = ui->label_amount->text().toInt();//取得設定值
    sec = ui->label_sec->text().toInt();//取得設定值

    game_Enabled = false;
    game_over =false;

    set_btn();//設置遊戲按鈕數量
    readygame();//預備
    set_game();
}

void Widget::readygame()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowFlags(Qt::Tool);

    dialog->setStyleSheet(
                "background-color:qradialgradient(spread:reflect, cx:0.5, cy:0.5, radius:0.9, fx:0.5, fy:0.5, stop:0.5 rgba(25, 255, 131, 208), stop:0.710227 rgba(255, 255, 255, 0));\nborder-style: outset;"
                );
                /*
                "background-color:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.7, fx:0.5, fy:0.5, stop:0.242938 rgba(62, 255, 41, 250), stop:1 rgba(255, 255, 255, 255));"
                "border-style: outset;");*/
    QPushButton *dialog_OK = new QPushButton();
    dialog_OK->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    dialog_OK->setText(tr("START!!"));
    dialog->resize(ui->stackedWidget->size().width() /1.5 ,ui->stackedWidget->size().height() / 2);
    QFont font_mvboli(font_data_mvboli);

    font_mvboli.setPixelSize(ui->stackedWidget->size().width() / 8);
    dialog_OK->setFont(QFont(font_mvboli));

    QHBoxLayout *lay = new QHBoxLayout(dialog);
    lay->addWidget(dialog_OK);
    connect(dialog_OK,SIGNAL(clicked(bool)),dialog,SLOT(close()));
    dialog->exec();
}

void Widget::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);//跳至頁面1
    resetgame();
}

void Widget::resetgame()//重製遊戲
{
    ui->timerbar->setValue(0);
    ans_count = 1;
    Timer_sec->stop();
    for (int i = 0;i < ui->playbox->count();)//重製按鈕
    {
        Playbutton *button = qobject_cast<Playbutton *>(ui->playbox->itemAt(0)->widget());
        button->Reset();
        delete button;
    }
}

void Widget::slotGetNumber()//按下遊戲中的按鈕
{
    Playbutton *button = (Playbutton *)sender();
    if (button->answer() ==  ans_count && game_Enabled)
    {
        if (ans_count == ui->label_amount->text().toInt())
        {
            Timer_play->stop();

            QMessageBox msgBox;
            msgBox.setWindowTitle("勝利~~!");
            msgBox.setText(QString("時間：%1s \n是否繼續?").arg(count_time / 10));
            msgBox.setStandardButtons (QMessageBox::Yes | QMessageBox::Reset);
            //QPushButton *connectButton = msgBox.addButton(tr("Connect"), QMessageBox::ActionRole);

            //msgBox.setDefaultButton(QMessageBox::No);
            //msgBox.addButton(tr("back"),QMessageBox::AcceptRole);
            int chose = msgBox.exec();

            switch (chose) {
            case QMessageBox::Yes:
                on_pushButton_9_clicked();
                break;
            case QMessageBox::Reset:
                on_pushButton_9_clicked();
                break;
            }
            count_time = 0;
        }
        ans_count++;
    }
}

void Widget::set_btn()//設置遊戲按鈕數量
{
    ui->playbox->setMargin(0);
    ui->playbox->setSpacing(0);
    ui->playbox->setHorizontalSpacing(0);
    ui->BPlaybox->resize(ui->BPlaybox->size().width(),ui->BPlaybox->size().width());

    //QFont font_mvboli(font_data_mvboli);
    //font_mvboli.setPixelSize(50);

    for (int i = 0;i < range;i++)
    {
        for (int j = 0;j < range;j++)
        {
            Playbutton *button = new Playbutton();
            button->addID();
            button->setFocusPolicy(Qt::NoFocus);//按鍵效果(無效果)
            button->setMinimumSize(QSize(ui->BPlaybox->size().width() / range
                                         ,ui->BPlaybox->size().width() / range));//按鍵大小
            button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

            //button->setFont(QFont("",button->size().height()/13));//設定字體字型
            //button->setFont(QFont(font_mvboli));
            ui->playbox->addWidget(button,i,j);//新增button於i行j列
            connect(button, SIGNAL(clicked()), this, SLOT(slotGetNumber()));//信號
        }
    }
}

void Widget::set_game()//設置遊戲題目
{
    Topiclist type;
    pose = type.get_position(range * range);//建立按鈕總數
    qus = type.get_problem(amount);//建立題目數

    QPixmap pixmapbox[9];
    pixmapbox[0].load(":/icon/Resourcesbox/button/bticon00.png");
    pixmapbox[1].load(":/icon/Resourcesbox/button/bticon01.png");
    pixmapbox[2].load(":/icon/Resourcesbox/button/bticon02.png");
    pixmapbox[3].load(":/icon/Resourcesbox/button/bticon03.png");
    pixmapbox[4].load(":/icon/Resourcesbox/button/bticon04.png");
    pixmapbox[5].load(":/icon/Resourcesbox/button/bticon05.png");
    pixmapbox[6].load(":/icon/Resourcesbox/button/bticon06.png");
    pixmapbox[7].load(":/icon/Resourcesbox/button/bticon07.png");
    pixmapbox[8].load(":/icon/Resourcesbox/button/bticon08.png");
    pixmapbox[9].load(":/icon/Resourcesbox/button/bticon09.png");

    for (int i = 0;i < range * range;i++)
    {
        Playbutton *button = qobject_cast<Playbutton *>(ui->playbox->itemAt(i)->widget());
        button->setMaximumSize(button->size().width(),button->size().height());
        button->setIcon(pixmapbox[0]);
        button->setIconSize(QSize(button->size().width() + 10 ,button->size().width() + 10));
        for(int j = 0;j < amount ;j++)
        {
            if (*(pose + i) == *(qus + j))
            {
                button->answer(*(qus + j));
                button->setIcon(pixmapbox[button->answer()]);
                button->setIconSize(QSize(button->size().width() + 20 ,button->size().width() + 20));
            }
        }
    }
    ui->timerbar->setValue(0);
    ui->timerbar->setMaximum(sec * 100);
    Timer_sec->start(10);

}

void Widget::TimerSec()
{
    int bar = ui->timerbar->value();
    ui->timerbar->setValue(bar + 1);
    QPixmap pixmapbox;
    pixmapbox.load(":/icon/Resourcesbox/button/bticon00.png");
    if(bar == ui->timerbar->maximum())
    {
        for (int i = 0;i < range * range;i++)
        {
            Playbutton *button = qobject_cast<Playbutton *>(ui->playbox->itemAt(i)->widget());
            button->setIcon(pixmapbox);
        }
        Timer_sec->stop();//停止準備時間計時器
        game_Enabled = true;//開始遊戲信號
        Timer_play->start(100);//遊戲時間計時器
        count_time = 0;
    }
}

void Widget::playtime()
{
    count_time++;
}

void Widget::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);//跳至頁面0
}

void Widget::on_PB_range_DW_clicked()
{
    if(ui->label_range->text().toInt() > 3)
        ui->label_range->setText(QString("%1").arg(ui->label_range->text().toInt() - 1));
}
void Widget::on_PB_range_UP_clicked()
{
    if(ui->label_range->text().toInt() < 5)
        ui->label_range->setText(QString("%1").arg(ui->label_range->text().toInt() + 1));
}
void Widget::on_PB_amount_DW_clicked()
{
    if(ui->label_amount->text().toInt() > 3)
         ui->label_amount->setText(QString("%1").arg(ui->label_amount->text().toInt() - 1));
}
void Widget::on_PB_amount_UP_clicked()
{
    if(ui->label_amount->text().toInt() < 9)
        ui->label_amount->setText(QString("%1").arg(ui->label_amount->text().toInt() + 1));
}
void Widget::on_PB_sec_DW_clicked()
{
    if(ui->label_sec->text().toInt() > 1)
        ui->label_sec->setText(QString("%1").arg(ui->label_sec->text().toInt() - 1));
}
void Widget::on_PB_sec_UP_clicked()
{
    if(ui->label_sec->text().toInt() < 5)
        ui->label_sec->setText(QString("%1").arg(ui->label_sec->text().toInt() + 1));
}

void Widget::on_pushButton_2_clicked()
{
}


