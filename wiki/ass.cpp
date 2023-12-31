#include "ass.h"
#include "ui_ass.h"
#include "widget.h"
#include <QtCore/QObject>
#include <QEventLoop>
#include <QInputDialog>
#include <QDebug>

ass::ass(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ass)
{
    ui->setupUi(this);
    setWindowTitle("助教操作界面");
    QString he = QString::fromStdString(User::users[iur]->getUsername());
    ui->head->setText(he);
    qDebug()<<iur;
}

void ass::paintEvent(QPaintEvent *event) //界面背景
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":://bac_bzd.jpg"));
}

ass::~ass()
{
    delete ui;
}

void ass::on_bacreg_clicked()
{
    regi *re = new regi();
    this->close();
    re->show();
    delete this;
}

void ass::on_baclog_clicked()
{
    log_in*ad = new log_in();
    this->close();
    ad->show();
    delete this;
}


void ass::on_notice_clicked() //查看发布的通知
{
    int qst;
    QString text;
    for (int i = 0; i < Number; ++i) {
        if (User::users[i]->getIdentity()==3) {
            qst = i;
            break;
        }
    }
    for(Notice unread:User::users[qst]->unreadNotices)
    {
        string l1= unread.getID(),l2 = unread.getPublisher(),l3= unread.getContent();
        QString q1 = QString::fromStdString(l1),q2 = QString::fromStdString(l2),q3 = QString::fromStdString(l3);
        text =text + "已发布:" + q1 + ' '+ q2 +' '+ ':' + q3 + '\n';
    }
    for(Notice read:User::users[qst]->readNotices)
    {
        string l1= read.getID(),l2 = read.getPublisher(),l3= read.getContent();
        QString q1 = QString::fromStdString(l1),q2 = QString::fromStdString(l2),q3 = QString::fromStdString(l3);
        text = text + q1 + ' '+ q2 +' '+ ':' + q3;
    }
    ui->text_out->setText(text);
}


void ass::on_notice_publish_clicked()
{
    string ID,content,publisher;
    publisher = User::users[iur]->getUsername();
    bool ok;
    QString i1 = QInputDialog::getText(NULL,"输入对话框","请输入ID",QLineEdit::Normal,"",&ok);
    ID = i1.toStdString();
    if(ID == " "){
        QMessageBox warn;
        warn.setText("ID不能为空！");
        warn.exec();
    }
    else{
        bool find=false;
        for(auto &j:Notice::notices)
        {
            if(j->getID()==ID)
            {
                find=true;
            }
        }
        if(find){
            QMessageBox wa;
            wa.setText("ID已存在，请勿输入重复ID!");
        }
        else{

        bool os;
        QString i2 = QInputDialog::getText(NULL,"输入对话框","请输入通知",QLineEdit::Normal,"",&os);
        content = i2.toStdString();
        Notice *temp=new Notice(ID,publisher,content);
        Notice::notices.push_back(temp);
        for(auto &j:User::users)
        {
            j->receiveNotice(*temp);
        }

    // QEventLoop eventloop;
    // flag = false;
    // ID = io;
    // ui->text_in->clear();
    // ui->text_out->setText("请输入通知");
    // content = io;
    // flag = false;
    // string l1=ID.toStdString(),l2 = content.toStdString();
    // Notice *_notice = new Notice(l1, User::users[iur]->getUsername(), l2);
    // _notice->publishNotice(l1, User::users[iur]->getUsername(), l2);
        }
    }
}


void ass::on_notice_publish_2_clicked() //查看课程
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
string command;//存储课程名称

void ass::on_notice_publish_3_clicked() //加入课程
{
    bool ok;
    QString i1 = QInputDialog::getText(NULL,"加入课程","请输入要加入的课程的名字",QLineEdit::Normal,"",&ok);
    command = i1.toStdString();
    bool is;
    QString i2 = QInputDialog::getText(NULL,"加入课程","请输入要加入的课程的老师的名字",QLineEdit::Normal,"",&is);
    string name = i2.toStdString();
    User::users[iur]->addCourse(command, name);
}


void ass::on_notice_publish_5_clicked() //查看课程成员
{
    QString text = "老师:";
    bool ok;
    QString i1 = QInputDialog::getText(NULL,"查看课程成员","请输入要查询的课程的名字",QLineEdit::Normal,"",&ok);
    command = i1.toStdString();
    for (auto &j:User::users[iur]->courses){
        if (j->getCourseName() == command){
            string io = j->getTeacher();
            QString iu = QString::fromStdString(io);
            text = text + iu + '\n' + "助教:";

            for(auto &t:j->assistants){
                string op = t->getUsername();
                QString oi = QString::fromStdString(op);
                text = text + oi + ' ';
            }
            text= text + '\n' + "学生:";
            for(auto &c:j->students){
                string op = c->getUsername();
                QString oi = QString::fromStdString(op);
                text =text + oi + ' ';
            }
        }
    }
    ui->text_out->setText(text);
}

void ass::on_notice_publish_6_clicked()//退出课程
{
    bool ok;
    QString i1 = QInputDialog::getText(NULL,"退出课程","请输入要退出的课程的名字",QLineEdit::Normal,"",&ok);
    command = i1.toStdString();
    for (auto &j:User::users[iur]->getCourse()){
        if (j->getCourseName() == command){
            User::users[iur]->leaveCourse(j->getCourseName(),j->getTeacher());
            break;
        }
    }
}


void ass::on_notice_publish_4_clicked() //评价
{
    bool ok;
    QString i1 = QInputDialog::getText(NULL,"评价课程","请输入要评价的课程的名字",QLineEdit::Normal,"",&ok);
    command = i1.toStdString();
    for (auto &j:User::users[iur]->getCourse()){
        if (j->getCourseName() == command){
            bool ok;
            QString sco = QInputDialog::getText(NULL,"评分","请输入您的评分",QLineEdit::Normal,"",&ok);
            int score = sco.toInt();
            bool da;
            QString eva = QInputDialog::getText(NULL,"评价","请输入您的评语",QLineEdit::Normal,"",&da);
            string evaluate = eva.toStdString();
            User::users[iur]->publishEvaluation(j->getCourseName(), evaluate, score);
        }
    }
}




void ass::on_notice_publish_7_clicked()//注销
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


void ass::on_notice_publish_8_clicked() //查看某次作业的全部分数
{
    bool is;
    QString text_1;
    QString co = QInputDialog::getText(NULL,"查看作业得分","请输入课程名",QLineEdit::Normal,"",&is);
    string cou = co.toStdString();
    for (auto &j:User::users[iur]->getCourse()){
        if (j->getCourseName() == cou){
            bool ok;
            QString c1 = QInputDialog::getText(NULL,"查看作业得分","请输入作业ID",QLineEdit::Normal,"",&ok);
            string ID = c1.toStdString();
            bool find=false;
            for(auto & it:User::users)
            {
                for (auto &iter: it->homeworks)
                {
                    for (auto &ite: it->scores)
                    {
                        if (ite.first == iter.first&&it->getIdentity()==3) { find = true; }
                        if(find)
                        {
                            QString str_1 = QString::fromStdString(it->getUsername());
                            QString str_2 = QString::number(ite.second.score,10,0);
                            QString str = str_1 + "得分:" + str_2 + '\n';
                            text_1 += str;
                        }
                    }
                }
            }
        }
    }
    ui->text_out->clear();
    ui->text_out->setText(text_1);
}


void ass::on_notice_publish_9_clicked()//给作业评分
{
    bool is;
    QString co = QInputDialog::getText(NULL,"给学生作业得分","请输入课程名",QLineEdit::Normal,"",&is);
    string cou = co.toStdString();
    for (auto &j:User::users[iur]->courses){
        if (j->getCourseName() == cou){
            bool ok;
            QString c1 = QInputDialog::getText(NULL,"给学生作业得分","请输入学生姓名",QLineEdit::Normal,"",&ok);
            string name = c1.toStdString();
            for (auto &temp: j->students)
                if (name ==temp->getUsername()) {
                    qDebug() << "找到学生";
                    bool al;
                    QString qsID = QInputDialog::getText(NULL,"给学生作业得分","请输入作业ID",QLineEdit::Normal,"",&al);
                    string ID = qsID.toStdString();
                    unordered_map <string,Score> change;
                    change=temp->getScores();
                    string content;
                    for(auto &s:temp->scores){
                        if(s.first == ID){
                            content = s.second.content;
                        }
                    }
                    QString qcontent = "提交内容:" + QString::fromStdString(content);
                    qDebug()<<"弹窗前";
                    //弹窗显示作业内容
                    QMessageBox tips;
                    tips.setText(qcontent);
                    tips.exec();
                    bool nan;
                    QString fin = QInputDialog::getText(NULL,"给该作业打分","请输入评分",QLineEdit::Normal,"",&nan);
                    int yes = fin.toInt();
                    string ye = fin.toStdString();
                    for(auto &to:temp->scores){
                        if(to.first == ID){ //找到该ID的作业
                            to.second.score = yes;//评分
                        }
                    }
                    // temp->getHomeworks()[ID]->Score(temp->getHomeworks()[ye]->getID(),temp->getUsername(),change[ID]);
                }
        }
    }
}



