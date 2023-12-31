#ifndef TEA_H
#define TEA_H
#include <QPainter>
#include <QWidget>
#include <QProcess>
namespace Ui {
class tea;
}

class tea : public QWidget
{
    Q_OBJECT

public:
    explicit tea(QWidget *parent = nullptr);
    ~tea();
    // void getText();
    QString io;
    bool flag = false;
    void paintEvent(QPaintEvent *event);

private slots:

    void on_bacreg_clicked();
    void on_baclog_clicked();
    void on_notice_clicked();
    void on_notice_publish_clicked();


    void on_pushButton_clicked();

    void on_course_clicked();

    void on_create_clicked();

    void on_homework_publish_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_homework_view_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::tea *ui;
};

#endif // TEA_H
