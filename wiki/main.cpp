#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    User *user = new User("Admin",1);
    User::users.push_back(user);
    Number++;
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
