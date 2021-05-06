#include "mywidget.h"

#include <QApplication>

//QApplication应用程序类
//Qt头文件没有.h
//头文件和类名一样
//前两个字母大写
int main(int argc, char *argv[])
{
    //有且只有一个应用程序类的对象
    QApplication a(argc, argv);

    //MyWidget继承于QWidget,QWidget是一个窗口基类
    //所以MyWidget也是窗口类
    //w就是一个窗口
    MyWidget w;

    //窗口是默认隐藏的，需要人为显示
    w.show();

    //函数作用：让程序一直执行，等待用户操作
    //等待事件的发生
    return a.exec();

    //等价于下面两句话
    //a.exec();
    //return 0;
}
