#include "log_in.h"
#include "ui_log_in.h"
#include "widget.h"
#include <QDebug>
#include "stu.h"
#include "ui_stu.h"
#include <QtCore/QObject>
#include <QEventLoop>
#include <QInputDialog>
#include <QDebug>
#include <QKeyEvent>
#include "admin.h"
log_in::log_in(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::log_in)
{
    ui->setupUi(this);
    setWindowTitle("登录");
    ui->id->setPlaceholderText("请输入您的用户名");
}



log_in::~log_in()
{
    delete ui;
}

void log_in::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap("://background.jpg"));
}

void log_in::keypressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter){
        on_ok_clicked();
    }
}



void log_in::on_ok_clicked()
{
    QString in = ui->id->text();
    string _username = in.toStdString();
    int _identity = ui->identity->currentIndex() + 1;
    bool find=false;
    for(auto &_users:User::users)
    {
        if(_username.compare(_users->getUsername())==0 && _identity == _users->getIdentity())
        {
            find = true;
            break;
        }
    }
    for (int i = 0; i < Number; ++i) {
        if (_username.compare(User::users[i]->getUsername())==0) {
            iur = i;
            break;
        }
    }
    if(find)
    {
        this->close();
        delete this;
        if(_identity == 1){
            if(_username == "Admin"){
                bool ok;
                QString i1 = QInputDialog::getText(NULL,"Admin","请输入密码",QLineEdit::Password,"",&ok);
                string password = i1.toStdString();
                if(password == "P@sswOrd"){
                    admin *ad = new admin();
                    ad->show();
                }
                else{
                    QMessageBox warn;
                    warn.setText("密码错误！");
                    warn.exec();
                    log_in *lo = new log_in();
                    lo->show();
                }
            }
            else{
                tea *te = new tea();
                te->show();
            }
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
        else
        {
            this->close();
            delete this;
            // string st = User::users.back()->getUsername();
            // QString s = QString::fromStdString(st);
            // qDebug()<< User::users.back()->getUsername();
            // qDebug()<< User::users.back()->getIdentity();
            // qDebug()<< _username;
            // qDebug()<< _identity;
            QMessageBox warn;
            warn.setText("账户不存在！");
            warn.exec();
            Widget *ne = new Widget();
            ne->show();
        }
}

void log_in::on_bac_clicked()
{
    this->close();
    Widget *ne = new Widget();
    ne->show();
}

