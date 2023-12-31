#ifndef ASS_H
#define ASS_H

#include <QWidget>
#include <QPainter>
namespace Ui {
class ass;
}

class ass : public QWidget
{
    Q_OBJECT

public:
    explicit ass(QWidget *parent = nullptr);
    ~ass();
    void paintEvent(QPaintEvent *event);

private slots:
    void on_bacreg_clicked();

    void on_baclog_clicked();

    void on_notice_clicked();

    void on_notice_publish_clicked();

    void on_notice_publish_2_clicked();

    void on_notice_publish_3_clicked();

    void on_notice_publish_5_clicked();

    void on_notice_publish_6_clicked();

    void on_notice_publish_4_clicked();

    void on_notice_publish_7_clicked();

    void on_notice_publish_8_clicked();

    void on_notice_publish_9_clicked();

private:
    Ui::ass *ui;
};

#endif // ASS_H
