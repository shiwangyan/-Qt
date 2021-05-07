#include "mainwidget.h"
#include<QPushButton>
#include<QDebug>    //打印

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    b1.setParent(this);//指定父对象
    b1.setText("close");//给按钮设置内容
    b1.move(100,100);

    b2 = new QPushButton(this);
    b2->setText("abc");
    //b2->move(200,100);

    connect(&b1,&QPushButton::pressed,this,&MainWidget::close);

    /*  &b1：信号发出者，指针类型
     *  &QPushButton::pressed：处理的信号，&发送者的类名::信号名字
     *  this：信号接收者
     *  &MainWidget::close：槽函数，信号处理函数 &接收者的类名::信号名字
     */

    /* 自定义槽，普通函数的用法
     * Qt5:任意的成员函数，普通全局函数，静态函数大槽函数需要和信号一致（参数，返回值)
     * 由于信号都是没有返回值，所以，槽函数一定没有返回值
     */

    connect(b2, &QPushButton::pressed, this, &MainWidget::mySlot);//改变按钮的文字

    connect(b2, &QPushButton::pressed, &b1, &QPushButton::hide);//隐藏“close”按钮

    /*信号:短信
     * 槽函数:接收短信的手机
     */

    setWindowTitle("Boss");
    //this->setWindowTitle("Boss");

    b3.setParent(this);
    b3.setText("切换到子窗口");
    b3.move(50,50);

    //显示子窗口
    //subWin.show();
    connect(&b3, &QPushButton::released, this, &MainWidget::changeWin);

    //处理子窗口的信号
    //    void (SubWidget::*funSignal)() = &SubWidget::mySignal;//函数指针
    //    connect(&subWin,funSignal,this,&MainWidget::dealSub);

    //    void (SubWidget::*testSignal)(int,QString) = &SubWidget::mySignal;
    //    connect(&subWin,testSignal,this,&MainWidget::dealSignal);

    //Qt4信号连接
    //Qt4槽函数必须有slots关键字来修饰
    connect(&subWin,SIGNAL(mySignal()), this, SLOT(dealSub()));

    connect(&subWin,SIGNAL(mySignal(int,QString)),
            this,SLOT(dealSignal(int,QString)));
    //SIGNAL SLOT 将函数名字 -> 字符串  不进行错误检查
    //第一次就出错，dealSignal(int,QString)没有带参数，编译未检查出来，导致运行出错

    //Lambda表达式，匿名函数对象
    //C++11增加的新特性，项目文件: CONFIG += C++11
    //Qt配合信号一起使用，非常方便

    QPushButton *b4 = new QPushButton (this);
    b4->setText ( "Lambda表达式");
    b4->move(150,150);
    int a = 10,b = 100;
    connect (b4, &QPushButton::released,
             //=:把外部所有局部变量、类中所有成员以值传递方式
             // this:类中所有成员以值传递方式
             // &︰把外部所有局部变量，引用符号
             [=]() mutable//mutable让变量可变
    {
        b4->setText("123");
        qDebug () << "1111111";
        qDebug () << a << b;
        a = 11;
    }
    );
//    connect (b4, &QPushButton::clicked,//点击
//             [=](bool isChack)
//    {
//        qDebug () << isChack;
//    }
//    );




    resize(400,400);
}

void MainWidget::dealSignal(int a,QString str)
{
    //我使用的是5.14.2版本，不需要toUtf8()
    //qDebug() << a << str.toUtf8().data();
    qDebug() << a << str;
}

void MainWidget::mySlot()
{
    b2->setText("123");
}

void MainWidget::changeWin()
{
    //显示子窗口
    subWin.show();
    //隐藏本窗口
    this->hide();
}

void MainWidget::dealSub()
{
    //子窗口隐藏
    subWin.hide();
    //本窗口显示
    this->show();
}

MainWidget::~MainWidget()
{
}

