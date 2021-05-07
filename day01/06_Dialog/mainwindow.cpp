#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>
#include <QtDebug>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(400,400);
    QMenuBar *mBar = menuBar();
    setMenuBar(mBar);           //创建菜单栏

    QMenu *menu = mBar->addMenu("对话框");//添加一个“对话框”按钮

    QAction *p1 = menu->addAction("模态对话框");//添加一个“模态对话框”的按键

    connect(p1, &QAction::triggered,//让按键起作用
            [=]()
    {
        QDialog dlg;
        dlg.exec();
        qDebug()<<"111111";
    }
    );

    QAction *p2 = menu->addAction("非模态对话框");
    connect(p2,&QAction::triggered,
            [=]()
    {
        //把对话框作为一个成员变量，对话框才能一直存在
        //dlg.show();
        //qDebug()<<"111111";

        //用局部变量的方法，动态分配内存
        //但是运行时才会回收内存，所以可能会因为不断点击“非模态对话框”导致内存不断被占用
        //QDialog *p = new QDialog(this);
        //p->show();

        QDialog *p = new QDialog;
        p->setAttribute(Qt::WA_DeleteOnClose);
        p->show();
    }
    );

    QAction *p3 = menu->addAction("关于对话框");
    connect(p3, &QAction::triggered,
            [=]()
    {
        QMessageBox::about(this,"about","关于qt");
    }
    );

    QAction *p4 = menu->addAction("问题对话框");
    connect(p4, &QAction::triggered,
            [=]()
    {
        int ret =QMessageBox::question(this,
                                       "question", "Are you ok?",
                                       QMessageBox::Ok |
                                       QMessageBox::Cancel|
                                       QMessageBox::No|
                                       QMessageBox::Yes
                                       );
        switch(ret)
        {
        case QMessageBox::Yes :
            qDebug()<< "i am ok";
            break;
        case QMessageBox::No:
            qDebug()<<"i am bad";
            break;
        case QMessageBox::Ok :
            qDebug()<< "i am ok";
            break;
        case QMessageBox::Cancel:
            qDebug()<<"i am bad";
            break;
        default:
            break;
        }
    }
    );

    QAction *p5 = menu->addAction("文件对话框");
    connect(p5,&QAction::triggered,
            [=]()
    {
        QString path = QFileDialog::getOpenFileName(
                    this,
                    "open",
                    "../",
                    "souce(*.cpp *.h);;"
                    "Text(*.txt);;"
                    "All(*.*)"

                    );
        qDebug()<<path;
    }
    );
}

MainWindow::~MainWindow()
{
}

