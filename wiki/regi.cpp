#include "regi.h"
#include "qpainter.h"
#include "ui_regi.h"
#include "widget.h"
#include <QKeyEvent>
#include <QApplication>
regi::regi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::regi)
{
    ui->setupUi(this);
    setWindowTitle("注册");
    ui->id->setPlaceholderText("请输入您的用户名");
    connect(this,SIGNAL(regi::enterpressed()),this,SLOT(regi::on_ok_clicked()));
}

regi::~regi()
{
    delete ui;
}

void regi::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap("://background.jpg"));
}

void regi::pressevent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){
        emit enterpressed();
    }
}



void regi::on_ok_clicked()
{
    QString in = ui->id->text();
    string _username = in.toStdString();
    int _identity = ui->identity->currentIndex();
    _identity+=1;
    bool flag = true;
    for (auto &_users: User::users){
        if (_username.compare(_users->getUsername())==0) {
            flag = false;
            break;
    }
}
    if(!flag){
    QMessageBox warn;
        warn.setText("该账户已存在，请登录！");
        warn.exec();
        this->close();
        log_in*ad = new log_in();
        ad->show();
    }
    else{
        User *user = new User(_username, _identity);
        User::users.push_back(user);
        iur = Number;
        Number++;
        this->close();
        if(_identity == 1){
            tea *te = new tea();
            te->show();
        }
        else if(_identity == 2){
            ass *as = new ass();
            as->show();
        }
        else {
            stu *st = new stu();
            st->show();
        }
    }
    delete this;
}


void regi::on_bac_clicked()
{
    this->close();
    Widget *ne = new Widget();
    ne->show();
}

