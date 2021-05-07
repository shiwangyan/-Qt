#include <QApplication>
#include <QWidget>//窗口控件基类
#include <QPushButton>

int main(int argc, char **argv)
{
    QApplication app(argc,argv);

    QWidget w;
    w.setWindowTitle("主要看气质");//设置标题



    /*如果不指定父对象，对象和对象没有关系，独立
     *   a指定b为父对象，a放b上面
     *   指定父对象有两种方式：
     *             1）setParent
     *             2）通过构造函数传参
     *   指定父对象，只需父对象显示，子对象自动显示
*/

    QPushButton b;
    b.setText("^_^");//给按钮设置内容
    b.setParent(&w);//指定父对象
    b.move(100,100);//移动坐标
    //  b.show();

    QPushButton b1(&w);//通过构造函数传参
    b1.setText("取消");
    b1.move(200,100);

    w.show();

    app.exec();
    return 0;
}
