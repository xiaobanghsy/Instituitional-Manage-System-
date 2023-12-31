#include "tea.h"
#include "ui_tea.h"
#include "widget.h"
#include <QtCore/QObject>
#include <QEventLoop>
#include <QInputDialog>
#include <QDebug>

tea::tea(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::tea)
{
    ui->setupUi(this);
    QString he = QString::fromStdString(User::users[iur]->getUsername());
    ui->head->setText(he);
    qDebug()<<iur;

    // connect(ui->ok,SIGNAL(clicked(bool)),this,SLOT(getText()));

    setWindowTitle("教师操作界面");
    // string st = User::users.back()->getUsername();
    // QString s = QString::fromStdString(st);
    // ui->text->setText(s);
}

void tea::paintEvent(QPaintEvent *event) //界面背景
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":://bac_bzd.jpg"));
}

tea::~tea(){
    delete ui;}

// void tea::getText()
// {
//     io = ui->text_in->toPlainText();
//     flag = true;
// }

void tea::on_bacreg_clicked()
{
    this->close();
    regi *ad = new regi();
    ad->show();
    delete this;
}
void tea::on_baclog_clicked()
{
    this->close();
    log_in *ad = new log_in();
    ad->show();
    delete this;
}

void tea::on_notice_publish_clicked() //发布通知
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

void tea::on_notice_clicked(){ //查看消息
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

void tea::on_pushButton_clicked()
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


void tea::on_course_clicked() //课程：查看所有课程
{
    QString text;
    ui->text_out->clear();
    for(auto &j:User::users[iur]->getCourse()){
        string t = j->getCourseName();
        QString st = QString::fromStdString(t);
        text = text + ' ' + st;
    }
    ui->text_out->setText(text);
}

string command_3;//存储课程名称

void tea::on_create_clicked() //创建课程
{
    bool flag = true;
    bool ok;
    QString i1 = QInputDialog::getText(NULL,"输入对话框","请输入新课程的名字",QLineEdit::Normal,"",&ok);
    command_3 = i1.toStdString();
    if(command_3 == " "){
        QMessageBox warn;
        warn.setText("输入内容为空！");
        warn.exec();
    }
    else{
        for (auto &l: User::users[iur]->getCourse())
            if (command_3 == l->getCourseName()) {
                QMessageBox warning;
                warning.setText("该课程已存在！");
                warning.exec();
                flag = false;
                break;
            }
        if(flag){
            User::users[iur]->CreateCourse(command_3, User::users[iur]->getUsername());
            QMessageBox mes;
            mes.setText("创建成功！");
            mes.exec();
        }
    }
}

void tea::on_pushButton_2_clicked() //查看课程成员
{
    QString texto = "老师:";
    bool ok;
    QString i1 = QInputDialog::getText(NULL,"查看课程成员","请输入要查询的课程的名字",QLineEdit::Normal,"",&ok);
    string course_name;
    course_name = i1.toStdString();
    for (auto &j:User::users[iur]->courses){
        if (j->getCourseName() == course_name){
            string io = j->getTeacher();
            QString iu = QString::fromStdString(io);
            texto = texto + iu +'\n' ;
            texto += "助教:";
            for(auto &t:j->assistants){
                string op = t->getUsername();
                QString oi = QString::fromStdString(op);
                texto = texto + oi + ' ';
            }
            texto = texto + '\n' + "学生:";
            for(auto &c:j->students){
                string op = c->getUsername();
                QString oi = QString::fromStdString(op);
                texto = texto + oi +' ';
            }
        }
    }
    ui->text_out->setText(texto);
}


void tea::on_pushButton_3_clicked()  //注销课程
{
    string course_name;
    bool ok;
    QString i1 = QInputDialog::getText(NULL,"注销课程","请输入要注销的课程的名字",QLineEdit::Normal,"",&ok);
    course_name = i1.toStdString();
    for (auto &j:User::users[iur]->getCourse()){
        if (j->getCourseName() == course_name){//找到了课程
            User::users[iur]->courses.erase(j);
            for(auto &t:j->assistants){
                t->courses.erase(j);
            }
            for(auto &s:j->students){
                s->courses.erase(j);
            }
            qDebug()<<"注销成功" <<'\n';
        }
    }
}


void tea::on_pushButton_4_clicked() //查看评价
{
    ui->text_out->clear(); //先重置面板内容
    bool ok;
    QString scor;
    QString text_1 = "评价:";
    text_1 += '\n';
    QString i1 = QInputDialog::getText(NULL,"查看评价","请输入查看评价的课程的名字",QLineEdit::Normal,"",&ok);
    string coursename = i1.toStdString();
    for(auto & course : User::users[iur]->courses)
    {
        if(coursename==course->getCourseName())
        {
            qDebug()<<"找到评价";
            for(auto &eva:course->evaluations){
                double sco = eva->getscores();
                scor = QString::number(sco,10,0);
                string com = eva->getComment();
                QString comment = QString::fromStdString(com);
                text_1 = text_1 + "评价:" + comment + '\n';
                qDebug() << comment <<' '<<sco;
            }
            qDebug() <<"出for循环";
            break;
        }
    }
    text_1 = text_1 + "平均得分:" + scor;
    qDebug() <<text_1;
    ui->text_out->setText(text_1);
}

void tea::on_homework_publish_clicked() //发布作业
{
    bool is;
    QString co = QInputDialog::getText(NULL,"发布作业","请输入课程名",QLineEdit::Normal,"",&is);
    string cou = co.toStdString();
    for (auto &j:User::users[iur]->courses){
        qDebug() <<"找到发布作业的课程";
        if (j->getCourseName() == cou){
            bool ok,find = false;
            QString i1 = QInputDialog::getText(NULL,"发布作业","请输入作业ID",QLineEdit::Normal,"",&ok);
            string id = i1.toStdString();
            bool bol_1;
            QString qo = QInputDialog::getText(NULL,"发布作业","请输入作业要求",QLineEdit::Normal,"",&bol_1);
            string content_1 = qo.toStdString();
            for(auto & work:j->getHomeworks()){
                if(work->getID() == id){find = true;}
            }
            if(find){
                QMessageBox tip;
                tip.setText("发布成功！");
                tip.exec();
            }
            else{
            j->publishHomework(id,content_1);
                QMessageBox tip;
            tip.setText("发布成功");
                tip.exec();

            }
        }
    }
}


void tea::on_homework_view_clicked() //查看作业
{
    bool is;
    QString co = QInputDialog::getText(NULL,"查看作业","请输入课程名",QLineEdit::Normal,"",&is);
    string cou = co.toStdString();
    QString text = "作业:";text+='\n';
    for (auto &j:User::users[iur]->courses){
        if (j->getCourseName() == cou){
            for (auto &k: j->getHomeworks()){
                QString op = QString::fromStdString(k->getcontent()),id = QString::fromStdString(k->getID());
                text = text + "作业id:" + id +' ' +"内容：" + op + '\n';
            }
        }
    }
    ui->text_out->clear();
    ui->text_out->setText(text);
}


void tea::on_pushButton_5_clicked() //查看学生作业得分(某一作业ID下的全部得分)
{
    bool is;
    QString text_1;
    QString co = QInputDialog::getText(NULL,"查看作业得分","请输入课程名",QLineEdit::Normal,"",&is);
    string cou = co.toStdString();
    for (auto &j:User::users[iur]->courses){
        if (j->getCourseName() == cou){//找到课程
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


void tea::on_pushButton_6_clicked() //给学生某次作业得分
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


