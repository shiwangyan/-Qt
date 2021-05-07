#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "subwidget.h"//子窗口头文件

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();



public slots:

    void mySlot();
    void changeWin();
    void dealSub();
    void dealSignal(int,QString);



private:
    QPushButton b1;
    QPushButton *b2;
    QPushButton b3;

    SubWidget subWin;

};
#endif // MAINWIDGET_H
