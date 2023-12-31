#include "admin.h"
#include "ui_admin.h"
#include "ass.h"
#include "ui_ass.h"
#include "widget.h"
#include <QtCore/QObject>
#include <QEventLoop>
#include <QInputDialog>
#include <QDebug>

admin::admin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::admin)
{
    ui->setupUi(this);
    setWindowTitle("教务操作界面");
    QString he = QString::fromStdString(User::users[iur]->getUsername());
    ui->head->setText(he);
    qDebug()<<iur;
}

admin::~admin()
{
    delete ui;
}

void admin::on_bacreg_clicked()
{
    this->close();
    regi *ad = new regi();
    ad->show();
    delete this;
}


void admin::on_baclog_clicked()
{
    this->close();
    log_in *ad = new log_in();
    ad->show();
    delete this;
}



void admin::on_notice_clicked()//发通知
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
        ID = "(教务) "+ID;
        Notice *temp=new Notice(ID,publisher,content);
        Notice::notices.push_back(temp);
        for(auto &j:User::users)
        {
            j->receiveNotice(*temp);
        }
        }
    }
}


void admin::on_pushButton_2_clicked() //查看所有课程
{
    QString text = "所有课程：";
    text += '\n';
    for (auto &j: Course::courses){
        string course_name_s = j->getCourseName();
        QString course_name = QString::fromStdString(course_name_s);
        text = text + course_name +' ';
    }
    ui->text_out->clear();
    ui->text_out->setText(text);
}


void admin::on_pushButton_6_clicked() //查看所有老师
{
    QString text = "所有老师：";
    text += '\n';
    for (auto &j:User::users){
        if(j->getIdentity() == 1){
        string name_s = j->getUsername();
        QString name = QString::fromStdString(name_s);
        text = text + name +' ';
        }
    }
    ui->text_out->clear();
    ui->text_out->setText(text);
}


void admin::on_pushButton_9_clicked() //所有助教
{
    QString text = "所有助教：";
    text += '\n';
    for (auto &j:User::users){
        if(j->getIdentity() == 2){
            string name_s = j->getUsername();
            QString name = QString::fromStdString(name_s);
            text = text + name +' ';
        }
    }
    ui->text_out->clear();
    ui->text_out->setText(text);
}


void admin::on_pushButton_3_clicked() //学生
{
    QString text = "所有学生：";
    text += '\n';
    for (auto &j:User::users){
        if(j->getIdentity() == 3){
            string name_s = j->getUsername();
            QString name = QString::fromStdString(name_s);
            text = text + name +' ';
        }
    }
    ui->text_out->clear();
    ui->text_out->setText(text);
}


void admin::on_pushButton_5_clicked() //查看老师任课
{
    bool find = true;
    bool is;
    QString co = QInputDialog::getText(NULL,"查找老师任课","请输入老师名字",QLineEdit::Normal,"",&is);
    string cou = co.toStdString();
    QString text = co +"任课：" + '\n';
    for(auto &t : User::users){
        if(t->getUsername()  == cou && t->getIdentity() == 1){
            find = false;
            for(auto course:t->courses){
                string course_name_s = course->getCourseName();
                QString course_name = QString::fromStdString(course_name_s);
                text = text + course_name +' ';
            }
        }
    }
    if(find){
        QMessageBox warn;
        warn.setText("未找到该老师！");
        warn.exec();
    }
}


void admin::on_pushButton_8_clicked() //助教
{
    bool find = true;
    bool is;
    QString co = QInputDialog::getText(NULL,"查寻助教课程","请输入助教名字",QLineEdit::Normal,"",&is);
    string cou = co.toStdString();
    QString text = co +"加入课程：" + '\n';
    for(auto &t : User::users){
        if(t->getUsername()  == cou && t->getIdentity() == 2){
            find = false;
            for(auto course:t->courses){
                string course_name_s = course->getCourseName();
                QString course_name = QString::fromStdString(course_name_s);
                text = text + course_name +' ';
            }
        }
    }
    if(find){
        QMessageBox warn;
        warn.setText("未找到该助教！");
        warn.exec();
    }
}




void admin::on_pushButton_7_clicked() //学生
{
    bool find = true;
    bool is;
    QString co = QInputDialog::getText(NULL,"查寻学生课程","请输入学生名字",QLineEdit::Normal,"",&is);
    string cou = co.toStdString();
    QString text = co +"加入课程：" + '\n';
    for(auto &t : User::users){
        if(t->getUsername()  == cou && t->getIdentity() == 3){
            find = false;
            for(auto course:t->courses){
                string course_name_s = course->getCourseName();
                QString course_name = QString::fromStdString(course_name_s);
                text = text + course_name +' ';
            }
        }
    }
    if(find){
        QMessageBox warn;
        warn.setText("未找到该学生！");
        warn.exec();
    }
}


void admin::on_pushButton_10_clicked() //解散课程
{
    string course_name;
    bool ok;
    QString i1 = QInputDialog::getText(NULL,"解散课程","请输入要解散的课程的名字",QLineEdit::Normal,"",&ok);
    course_name = i1.toStdString();
    for (auto &j:Course::courses){
        if (j->getCourseName() == course_name){//找到了课程
            for(auto &t:User::users){
                if(t->getUsername() == j->getTeacher()){
                    t->courses.erase(j);
                }
            }
            for(auto &t:j->assistants){
                t->courses.erase(j);
            }
            for(auto &s:j->students){
                s->courses.erase(j);
            }
            qDebug()<<"解散成功" <<'\n';
        }
    }
}


void admin::on_pushButton_11_clicked() //管理 //加入
{
    string name;
    bool ok;
    QString i1 = QInputDialog::getText(NULL,"将学生加入课程","请输入学生名字",QLineEdit::Normal,"",&ok);
    name = i1.toStdString();
    for(auto &y:User::users){
        if(y->getUsername() == name){
            bool is;
            QString co = QInputDialog::getText(NULL,"将学生加入课程","请输入课程名字",QLineEdit::Normal,"",&is);
            string cou = co.toStdString();
            bool teas;
            QString te = QInputDialog::getText(NULL,"将学生加入课程","请输入教师名字",QLineEdit::Normal,"",&teas);
            string tea = te.toStdString();
            y->addCourse(cou,tea);
            QMessageBox tip;
            tip.setText("操作成功!");
            tip.exec();
        }
    }
}


void admin::on_pushButton_12_clicked() //退出学生
{
    string name;
    bool ok;
    QString i1 = QInputDialog::getText(NULL,"将学生加入课程","请输入学生名字",QLineEdit::Normal,"",&ok);
    name = i1.toStdString();
    for(auto &y:User::users){
        if(y->getUsername() == name){
            bool is;
            QString co = QInputDialog::getText(NULL,"将学生加入课程","请输入课程名字",QLineEdit::Normal,"",&is);
            string cou = co.toStdString();
            for(auto &course:y->courses){
                if(course->getCourseName() == cou){
                    y->courses.erase(course);
                }
            }
            QMessageBox tip;
            tip.setText("操作成功!");
            tip.exec();
        }
    }
}

