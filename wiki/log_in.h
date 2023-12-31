#ifndef LOG_IN_H
#define LOG_IN_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QString>
namespace Ui {
class log_in;
}

class log_in : public QWidget
{
    Q_OBJECT

public:
    explicit log_in(QWidget *parent = nullptr);
    ~log_in();
    void paintEvent(QPaintEvent *event);
    void keypressEvent(QKeyEvent *event);

private slots:
    void on_ok_clicked();
    void on_bac_clicked();

private:
    Ui::log_in *ui;
};

#endif // LOG_IN_H
