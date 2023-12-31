#ifndef WIDGET_H
#define WIDGET_H
#include <QtCore/QCoreApplication>
#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QMessageBox>
#include "regi.h"
#include "log_in.h"
#include "tea.h"
#include "ass.h"
#include "stu.h"
QT_BEGIN_NAMESPACE
extern int iur;
extern int Number;
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget //wiget定义
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *event);

private slots:
    void on_button_log_clicked();
    void on_but_reg_clicked();

private:
    Ui::Widget *ui;
};

#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<vector>
using namespace std;
class Course;
class Homework;
class Notice;
class Evaluate;
struct Score
{
    string content;
    int score;
};
class User
{
private:
    string Username;
    int identity; // 身份，1 表示教师，2 表示助教，3 表示学生
public:
    static vector<User*> users;
    unordered_set<Course*> courses; // 用户创建或加入的课程集合
    vector<Notice> unreadNotices; // 用户未读通知集合
    vector<Notice> readNotices; // 用户已读通知集合
    unordered_map<string, Homework*> homeworks;
    unordered_map<string, Score> scores; // 用户作业的分数，键为作业编号，值为分数
    unordered_map<string ,Evaluate*> evaluations;

    User(string username,int ident):Username(username),identity(ident){}
    string getUsername();
    int getIdentity();

    unordered_set<Course*>& getCourse();
    void addCourse(string courseName,string teacher);
    void leaveCourse(string courseName,string teacher);
    void CreateCourse(string coursename,string teacher);

    vector<Notice>& getunread();
    vector<Notice>& getRead();
    void receiveNotice(Notice unreadOne);
    void showUnread();
    void showRead();

    unordered_map<string,Homework*>& getHomeworks();
    unordered_map<string,Score>& getScores();
    void submit(string homeworkID,string content);
    void showUnFinished();
    void showFinished();
    void viewScore(string homeworkID);
    void viewAllScore(string homeworkID);

    void publishEvaluation(string,string,int);
    void viewEvaluation();

    void logoffUser(string username);

};



class Course
{
    friend void User::viewEvaluation();
private:

    string courseName;
    string teacher;
protected:

    static vector<Homework*> homeworks;

public:
    static vector<Evaluate*> evaluations;
    vector<User*> assistants;
    vector<User*> students;
    static vector<Course*> courses;
    Course(){}
    Course(string Name,string teach):courseName(Name),teacher(teach){courses.push_back(this);homeworks.clear();evaluations.clear();}
    string getCourseName();
    string getTeacher();
    unordered_set<string>& getAssistants();
    unordered_set<string>& getStudents();
    /*vector<string>& getNotices();*/
    vector<Homework*>& getHomeworks();
    void addCourse(Course*);
    void addUser(string username,int identity);
    void removeUser(string username,int identity);
    /*void publishNotice(string noticeID);*/
    void publishHomework(string homeworkID,string content);
    void dismissCourse(string coursename);
    void view(string courseName);
};
class Notice
{
private:
    string ID;
    string publisher;
    string content;
public:
    static vector<Notice*> notices;
    Notice(string ID,string publisher,string content):ID(ID),publisher(publisher),content(content){}
    string getID();
    string getPublisher();
    string getContent();
    void publishNotice(string ID,string publisher,string content);
};
class Homework : public Course
{
    friend ostream & operator << (std::ostream &,const Homework&);
private:
    string ID;
    string courseName;
    string publisher;
    string content;
public:
    Homework(string ID,string courseName,string publisher,string content):ID(ID),courseName(courseName),publisher(publisher),content(content){}
    string getID();
    string getcourseName();
    string getpublisher();
    string getcontent();
    void publishHomework(string ID,string publisher,string courseName,string content);
    void Score(string ID,string username,Score n);
};

class Evaluate : public Course
{
private:
    string courseName;
    string comment;
    int score;
public:
    Evaluate(string courseName,string comment,int score):courseName(courseName),comment(comment),score(score){}
    string getCourseName();
    string getComment();
    int getScore();
    double getscores();
    void viewEvaluations(string courseName);
};



#endif // WIDGET_H
