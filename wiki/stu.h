#ifndef STU_H
#define STU_H
#include <QPainter>
#include <QWidget>
#include "log_in.h"
#include "regi.h"
namespace Ui {
class stu;
}

class stu : public QWidget
{
    Q_OBJECT

public:
    // stu::stu(QWidget *parent):QWidget(parent){
    //     connect(this,&stu::show(),this,&stu::read);
    //     connect(this,&stu::activateWindow(),this,&stu::read);
    // }

    explicit stu(QWidget *parent = nullptr);

    ~stu();

    void paintEvent(QPaintEvent *event);

private slots:
    void on_baclog_clicked();
    void on_bacreg_clicked();

    void on_logoff_clicked();

    void on_notice_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::stu *ui;
};

#endif // STU_H
