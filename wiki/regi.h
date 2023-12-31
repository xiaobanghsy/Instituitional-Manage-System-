#ifndef REGI_H
#define REGI_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QString>
namespace Ui {
class regi;
}

class regi : public QWidget
{
    Q_OBJECT

public:
    explicit regi(QWidget *parent = nullptr);
    ~regi();
    void paintEvent(QPaintEvent *event);
    void pressevent(QKeyEvent *event);

private slots:
    void on_ok_clicked();
    void on_bac_clicked();
signals:
    void enterpressed();
private:
    Ui::regi *ui;
};

#endif // REGI_H
