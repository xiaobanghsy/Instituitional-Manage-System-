#include "stu.h"
#include "ui_stu.h"
#include "widget.h"
#include <QtCore/QObject>
#include <QEventLoop>
#include <QInputDialog>
#include <QDebug>
stu::stu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::stu)
{
    // connect(this,&stu::show,this,&stu::on_notice_clicked());
    // connect(this,&stu::activateWindow(),this,&stu::on_notice_clicked);

    ui->setupUi(this);
    setWindowTitle("学生操作界面");
    QString he = QString::fromStdString(User::users[iur]->getUsername());
    ui->head->setText(he);
    qDebug()<<iur;
}

void stu::paintEvent(QPaintEvent *event) //界面背景
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":://bac_bzd.jpg"));
}

stu::~stu()
{
    delete ui;
}

void stu::on_baclog_clicked()//跳转登录
{
    this->close();
    log_in *ad = new log_in();
    ad->show();
    delete this;
}


void stu::on_bacreg_clicked() //跳转注册
{
    this->close();
    regi *ad = new regi();
    ad->show();
    delete this;
}


void stu::on_logoff_clicked()//注销
{
    for (auto &j: User::users.back()->getCourse()){
        j->dismissCourse(j->getCourseName());}
    User::users.erase(User::users.begin()+iur);
    Number++;
    Widget *wi = new Widget();
    wi->show();
    this->close();
    delete this;
}


void stu::on_notice_clicked() //查看消息
{
    QString text;
    ui->text_out->clear();
    for(Notice unread:User::users[iur]->unreadNotices)
    {
        string l1= unread.getID(),l2 = unread.getPublisher(),l3= unread.getContent();
        QString q1 = QString::fromStdString(l1),q2 = QString::fromStdString(l2),q3 = QString::fromStdString(l3);
        text = text + "未读消息：" + q1 + ' '+ q2 +' '+ ':' + q3 + '\n';
    }
    for(Notice read:User::users[iur]->readNotices)
    {
        string l1= read.getID(),l2 = read.getPublisher(),l3= read.getContent();
        QString q1 = QString::fromStdString(l1),q2 = QString::fromStdString(l2),q3 = QString::fromStdString(l3);
        text = text + "已读消息：" + q1 + ' '+ q2 +' '+ ':' + q3 + '\n';
    }
    ui->text_out->setText(text);
    for(auto &j:User::users[iur]->unreadNotices){
        User::users[iur]->readNotices.push_back(j);
        User::users[iur]->unreadNotices.clear();
    }
}

string command_2;//存储课程名称

void stu::on_pushButton_2_clicked() //查看课程
{
    QString text = "你加入的课程:";
    text += '\n';
    ui->text_out->clear();
    for(auto &j:User::users[iur]->getCourse()){
        string t = j->getCourseName(),tex =j->getTeacher();
        QString st = QString::fromStdString(t),te = QString::fromStdString(tex);
        text = text + ' ' + st +':' + te + '\n';
    }
    ui->text_out->setText(text);
}


void stu::on_pushButton_3_clicked() //查看课程成员
{
    QString text = "老师:";
    bool ok;
    QString i1 = QInputDialog::getText(NULL,"查看课程成员","请输入要查询的课程的名字",QLineEdit::Normal,"",&ok);
    command_2 = i1.toStdString();
    for (auto &j:User::users[iur]->courses){
        if (j->getCourseName() == command_2){
            string io = j->getTeacher();
            QString iu = QString::fromStdString(io);
            text = text + iu + '\n' + "助教:";

            for(auto &t:j->assistants){
                qDebug() << t->getUsername();
                string op = t->getUsername();
                QString oi = QString::fromStdString(op);
                text = text + oi + ' ';
            }
            text= text + '\n' + "学生:";
            for(auto &c:j->students){
                qDebug() << c->getUsername();
                string op = c->getUsername();
                QString oi = QString::fromStdString(op);
                text =text + oi + ' ';
            }
        }
    }
    ui->text_out->setText(text);
}

void stu::on_pushButton_4_clicked() //退出课程
{
    bool ok;
    QString i1 = QInputDialog::getText(NULL,"退出课程","请输入要退出的课程的名字",QLineEdit::Normal,"",&ok);
    command_2 = i1.toStdString();
    for (auto &j:User::users[iur]->getCourse()){
        if (j->getCourseName() == command_2){
            User::users[iur]->leaveCourse(j->getCourseName(),j->getTeacher());
            break;
        }
    }
}

void stu::on_pushButton_5_clicked() //评价课程
{
    string course_name;
    bool flag = true;//判断是否找到课程
    bool ok;
    QString i1 = QInputDialog::getText(NULL,"评价课程","请输入要评价的课程的名字",QLineEdit::Normal,"",&ok);
    course_name = i1.toStdString();
    for (auto &j:User::users[iur]->courses){
        if (j->getCourseName() == course_name){
            flag = false;
            bool op;
            QString sco = QInputDialog::getText(NULL,"评分","请输入您的评分(100分制)",QLineEdit::Normal,"",&op);
            int score = sco.toInt();
            bool da;
            QString eva = QInputDialog::getText(NULL,"评价","请输入您的评语",QLineEdit::Normal,"",&da);
            string evaluate = eva.toStdString();
            User::users[iur]->publishEvaluation(j->getCourseName(), evaluate, score);
            QMessageBox tip;
            tip.setText("评价成功！");
            tip.exec();
        }
    }
    if(flag){QMessageBox warn;
        warn.setText("未找到该课程！");
        warn.exec();
    }
}


void stu::on_pushButton_6_clicked() //加入课程
{
    bool ok;
    QString i1 = QInputDialog::getText(NULL,"加入课程","请输入要加入的课程的名字",QLineEdit::Normal,"",&ok);
    command_2 = i1.toStdString();

    bool is;
    QString i2 = QInputDialog::getText(NULL,"加入课程","请输入要加入的课程的老师的名字",QLineEdit::Normal,"",&is);
    string name = i2.toStdString();
    User::users[iur]->addCourse(command_2, name);
    QMessageBox tip;
    tip.setText("加入成功！");
    tip.exec();
}


void stu::on_pushButton_8_clicked() //查看某作业的评分
{
    bool b1;
    QString q1 = QInputDialog::getText(NULL,"查看得分","请输入查看的课程的名字",QLineEdit::Normal,"",&b1);
    string s1 = q1.toStdString();
    for (auto &j: User::users[iur]->getCourse())
        if (j->getCourseName() == s1){
            bool b2;
            QString q2 = QInputDialog::getText(NULL,"查看得分","请输入查看的作业的ID",QLineEdit::Normal,"",&b2);
            string s2 = q2.toStdString();
            if(User::users[iur]->scores.count(s2)==0){
                QMessageBox warn;
                warn.setText("无此作业的评分");
                warn.exec();
            }
            else{
                int sco = User::users[iur]->scores[s2].score;
                QString co ="你的得分是:" + QString::number(sco,10,0);
                ui->text_out->clear();
                ui->text_out->setText(co);
            }
        }
}


void stu::on_pushButton_7_clicked() //提交作业
{
    bool find = true;
    bool flag = true;
    bool b1;
    QString q1 = QInputDialog::getText(NULL,"提交作业","请输入课程的名字",QLineEdit::Normal,"",&b1);
    string s1 = q1.toStdString();
    for (auto &j: User::users[iur]->getCourse()){
        if (j->getCourseName() == s1){
            flag = false;
            bool b2;
            QString q2 = QInputDialog::getText(NULL,"提交作业","请输入作业的ID",QLineEdit::Normal,"",&b2);
            string s2 = q2.toStdString();
            bool b3;
            for(auto &ho:User::users[iur]->scores){
                if(ho.first == s2){
                    QMessageBox oi;
                    oi.setText("你已提交该作业，将覆盖原作业");
                    oi.exec();
                    find = false;
                    bool bol_1;
                    QString qstr = QInputDialog::getText(NULL,"提交作业","请输入作业内容",QLineEdit::Normal,"",&bol_1);
                    string qstr_str = qstr.toStdString();
                    ho.second.content = qstr_str;
                    ho.second.score = 100;
                    QMessageBox impo;
                    impo.setText("覆盖成功！");
                    impo.exec();
                }
            }
            if(find){
                QString q3 = QInputDialog::getText(NULL,"提交作业","请输入作业内容",QLineEdit::Normal,"",&b3);
                string s3 = q3.toStdString();
                User::users[iur]->submit(s2,s3);
                QMessageBox tip;
                tip.setText("提交成功！");
                tip.exec();
            }
        }
    }
    if(flag){
        QMessageBox warn;
        warn.setText("未找到课程作业！");
        warn.exec();
    }
}

void stu::on_pushButton_9_clicked() //查看作业
{
    QString text_1 = "未完成作业";text_1+='\n';
    QString text_2 = "已完成作业";text_2+='\n';
    bool b1;
    QString q1 = QInputDialog::getText(NULL,"查看得分","请输入查看的课程的名字",QLineEdit::Normal,"",&b1);
    string s1 = q1.toStdString();
    for (auto &j: User::users[iur]->courses)
        if (j->getCourseName() == s1){
            for(auto &ho:j->getHomeworks()){
                bool find = true;
                for(auto &ts:User::users[iur]->scores){
                    if(ts.first == ho->getID()){
                        find = false;
                    }
                }
                if(find){
                    text_1 = text_1 + QString::fromStdString(ho->getID()) + ' ' + QString::fromStdString(ho->getcontent()) +'\n';
                }
                else{
                    text_2 = text_2 + QString::fromStdString(ho->getID()) + ' ' + QString::fromStdString(ho->getcontent()) +'\n';
                }
            }
        }
    text_1 += text_2;
    ui->text_out->clear();
    ui->text_out->setText(text_1);
}

