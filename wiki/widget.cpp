#include "widget.h"
#include "./ui_widget.h"
int iur=0;
int Number = 0;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event) //界面背景
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap("://background.jpg"));
}

vector<User*> User::users;
vector<Homework*> Course::homeworks;
vector<Evaluate*> Course::evaluations;
vector<Course*> Course::courses;
vector<Notice*> Notice::notices;
string User::getUsername(){return Username;}
int User::getIdentity() {return identity;}
unordered_set<Course*>& User::getCourse(){return courses;}
void User::addCourse(string courseName,string teacher)
{
    for(auto &j:Course::courses){
        if(j->getCourseName()==courseName)
        {
            j->addUser(Username,identity);
            courses.insert(j);
            break;
        }
    }
}

void User::leaveCourse(string courseName,string teacher)
{
    for(auto &i: courses){
        if(courseName.compare(i->getCourseName())==0 && teacher.compare(i->getTeacher())==0){
            i->removeUser(Username,identity);
            qDebug()<<"leavecourse";
        }
    }
}
vector<Notice>& User::getunread(){return unreadNotices;}
vector<Notice>& User::getRead(){return readNotices;}
void User::receiveNotice(Notice unreadOne){unreadNotices.push_back(unreadOne);}
void User::showUnread()
{
    for(Notice unread:unreadNotices)
    {
        cout<<unread.getID()<<" "<<unread.getPublisher()<<" "<<unread.getContent()<<endl;
    }
}
void User::showRead()
{
    for(Notice read:readNotices)
    {
        cout<<read.getID()<<" "<<read.getPublisher()<<" "<<read.getContent()<<endl;
    }
}
unordered_map<string,Homework*>& User::getHomeworks(){return homeworks;}
unordered_map<string,Score>& User::getScores(){return scores;}
void User::submit(string homeworkID,string content)
{
    if(homeworks.count(homeworkID)==0){cout<<"无此作业"<<endl;return;}
        Score temp;
        temp.score=100;
        temp.content=content;
        scores.insert(make_pair(homeworkID,temp));
}
    void User::showUnFinished()
    {
        int num=0;
        bool find=false;
        for(auto &iter:homeworks)
        {
            for(auto &ite : scores)
            {
                if(ite.first==iter.first){find=true;}
            }
            if(!find){cout<<*iter.second;num++;}
            find=false;
        }
        if(num==0){cout<<"全部完成"<<endl;}
        }
        void User::showFinished()
        {
            int num=0;
            bool find=false;
            for(auto &iter:homeworks)
            {
                for(auto &ite : scores)
                {
                    if(ite.first==iter.first){find=true;}
                }
                if(find){cout<<*iter.second;num++;}
                find=false;
            }
            if(num==0){cout<<"全部完成"<<endl;}
            }
            void User::viewScore(string homeworkID)
            {
                if(scores.count(homeworkID)==0){cout<<"无此作业的评分"<<endl;return;}
                        else{cout<<scores[homeworkID].score<<endl;}
                }
                void User::viewAllScore(string homeworkID)
                {
                    int num=0;
                    bool find=false;
                    for(auto & it:users)
                    {
                        for (auto &iter: it->homeworks)
                        {
                            for (auto &ite: it->scores)
                            {
                                if (ite.first == iter.first&&it->getIdentity()==3) { find = true; }
                                if(find)
                                {
                                    cout<<it->getUsername()<<" 得分"<<ite.second.score<<endl;
                                }
                            }
                        }
                    }
                }
                void User::publishEvaluation(string Coursename,string content,int score){
                    Evaluate *temp=new Evaluate(Coursename,content,score);
                    evaluations.insert(make_pair(Coursename,temp));
                    Course::evaluations.push_back(temp);
                }
                void User::viewEvaluation(){
                    for(auto &j:(Course::evaluations)){
                        cout<<j->getScore()<<j->getComment()<<endl;
                    }
                }
                void User::logoffUser(string username){
                    for(int i=0;i<Number;i++)
                    {if(users[i]->getUsername()==username)
                            users.erase(users.begin()+i);
                    }
                }
                void User::CreateCourse(string coursename,string teacher){
                    Course *temp=new Course(coursename,teacher);
                    courses.insert(temp);
                    temp->addCourse(temp);
                }
                //Course
                string Course::getCourseName()
                {
                    return courseName;
                }
                string Course::getTeacher(){
                    return teacher;
                }
                unordered_set<string>& Course::getAssistants(){
                    unordered_set<string> temp;
                    for(auto &j:assistants){
                        temp.insert(j->getUsername());
                    }
                    return temp;
                }
                unordered_set<string>& Course::getStudents(){
                    unordered_set<string> temp;
                    for(auto &j:students){
                        temp.insert(j->getUsername());
                    }
                    return temp;
                }
                vector<Homework*>& Course::getHomeworks(){
                    return homeworks;
                }
                void Course::addCourse(Course* a)
                {
                    courses.push_back(a);
                }
                void Course::addUser(string username,int identity){
                    for(auto &j:User::users){
                        if(j->getUsername()==username){
                            if(identity==2){
                                assistants.push_back(j);
                                break;
                            }
                            else{
                                students.push_back(j);
                                break;
                            }
                        }
                    }
                }
                void Course::removeUser(string username,int identity){
                    for(auto &j:User::users){
                        if(j->getUsername()==username){
                            j->courses.erase(this);
                            if(identity==2){
                                for(int i=0;i<assistants.size();i++){
                                    if(assistants[i]->getUsername()==username){
                                        assistants.erase(assistants.begin()+i);
                                        qDebug() <<"assistant cleared";
                                        break;
                                    }
                                }
                            }
                            else{
                                for(int i=0;i<students.size();i++){
                                    if(students[i]->getUsername()==username){
                                        students.erase(students.begin()+i);
                                        qDebug() << "student cleared";
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                void Course::publishHomework(string homeworkID,string content){
                    Homework *temp=new Homework(homeworkID,courseName,teacher,content);
                    homeworks.push_back(temp);
                    for(auto &j:students)
                        j->homeworks.insert(make_pair(homeworkID,temp));
                }
                void Course::dismissCourse(string coursename){
                    Course *temp;
                    for(int i=0;i<courses.size();i++)
                        if(courses[i]->getCourseName()==coursename){
                            temp=courses[i];
                            courses.erase(courses.begin()+i);break;}
                    for(auto &j:assistants)
                        j->courses.erase(temp);
                    for(auto &j:students)
                        j->courses.erase(temp);

                }
                void Course::view(string courseName){
                    cout<<"teacher:"<<endl;
                    cout<<teacher<<endl;
                    cout<<"assistants:"<<endl;
                    for(auto &j:assistants)
                        cout<<j->getUsername()<<endl;
                    cout<<"students:"<<endl;
                    for(auto &j:students)
                        cout<<j->getUsername()<<endl;

                }
                //Notice
                string Notice::getID(){return ID;}
                string Notice::getPublisher(){return publisher;}
                string Notice::getContent(){return content;}
                void Notice::publishNotice(string ID,string publisher,string content)
                {
                    bool find=false;
                    for(auto &j:notices)
                    {
                        if(j->getID()==ID)
                        {
                            find=true;
                        }
                    }
                    if(find){cout<<"通知ID不可重复，以免学生混淆"<<endl;}
    else
                    {
                        Notice *temp=new Notice(ID,publisher,content);
                        notices.push_back(temp);
                        for(auto &j:User::users)
                        {
                            if(j->getIdentity()==3)
                            {
                                j->receiveNotice(*temp);
                            }
                        }
                    }
                }
                //homework
                ostream & operator << (std::ostream & out,const Homework& temp)
                {
                    out<<temp.ID<<" "<<temp.courseName<<" "<<temp.publisher<<" "<<temp.content<<endl;
                    return out;
                }
                string Homework::getID(){return ID;}
                string Homework::getcourseName(){return courseName;}
                string Homework::getpublisher(){return publisher;}
                string Homework::getcontent(){return content;}
                void Homework::publishHomework(string ID,string publisher,string courseName,string content)
                {
                    bool find=false;
                    for(auto &j:homeworks)
                    {
                        if(j->getID()==ID)
                        {
                            find=true;
                        }
                    }
                    if(find){cout<<"作业ID不可重复，以免学生混淆"<<endl;}
    else
                    {
                        Homework *temp = new Homework(ID, courseName, publisher, content);
                        homeworks.push_back(temp);
                        for (auto &j: User::users)
                        {
                            if (j->getIdentity() == 3)
                            {
                                j->homeworks.insert(make_pair(temp->getID(), temp));
                            }
                        }
                    }
                }
                void Homework::Score(string ID,string username,struct Score n)
                {
                    for(auto & thisuser : User::users)
                    {
                        if(username==thisuser->getUsername())
                        {
                            for(auto &tempscore:thisuser->scores){
                                if(tempscore.first == ID){
                                    tempscore.second = n;
                                }
                            }
                        }
                    }
                }
                string Evaluate::getCourseName(){return courseName;}
                string Evaluate::getComment(){return comment;}
                int Evaluate::getScore(){return  score;}
                double Evaluate::getscores()
                {
                    double get=0;
                    int sum=0;
                    for(auto &iter:evaluations)
                    {
                        get+=iter->getScore();
                        sum++;
                    }
                    get/=sum;
                    return get;
                }
                void Evaluate::viewEvaluations(string courseName)
                {
                    double score=0;
                    for(auto &it:evaluations)
                    {
                        cout<<"Comment:"<<endl;
                        cout<<it->getComment()<<endl;
                        cout<<"Score: "<<it->getScore()<<endl;
                        score=it->getscores();
                    }
                    cout<<"平均得分："<<score<<endl;
                }

void Widget::on_button_log_clicked()
{
    this->close();
    log_in *log = new log_in();
    log->show();
}

void Widget::on_but_reg_clicked()
{
    this->close();
    regi *reg = new regi();
    reg->show();
}

