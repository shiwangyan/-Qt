#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include "domxml.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //开始 车辆管理页面
    on_actionCar_triggered();

    //运行数据库
    connectDB();

    //初始化数据
    initData();

    DomXML::createXML("../demo.xml");   //创建空的xml文件


//    QStringList list;
//    list << "二汽神龙" << "毕加索" << "39" << "2" << "78";
//    DomXML::appendXML("../demo.xml",list);

//    QStringList fList;
//    QStringList bList;
//    QStringList pList;
//    QStringList nList;
//    QStringList tList;

//    DomXML::readXML("../demo.xml", fList, bList, pList, nList, tList);
//    for(int i = 0;i <fList.size();i++)
//    {
//        QString str = QString("%1:%2:卖出了%3,单价:%4，总价:%5")
//                .arg(fList.at(i))
//                .arg(bList.at(i))
//                .arg(nList.at(i))
//                .arg(pList.at(i))
//                .arg(tList.at(i));
//        qDebug()<<str;
//    }



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionCar_triggered()
{
    //切换到车辆管理页面
    ui->stackedWidget->setCurrentWidget(ui->car);
    ui->label->setText("车辆管理");



}

void MainWindow::on_actionCalc_triggered()
{
    //切换到销售统计页面
    ui->stackedWidget->setCurrentWidget(ui->calc);
    ui->label->setText("销售统计");
}



//连接数据库
void MainWindow:: connectDB()
{
    //添加数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("car");
    //打开数据库
    if(!db.open())
    {
        QMessageBox::warning(this, "数据库打开失败", db.lastError().text());
        return;
    }
}

//初始化数据
void MainWindow::initData(){
    QSqlQueryModel *queryModel = new QSqlQueryModel(this); //新建模型

    queryModel->setQuery("select name from factory"); //sql语句

    ui->comboBoxFactory->setModel(queryModel);

    ui->labelLast->setText("O");    //剩余数量
    ui->lineEditTotal->setEnabled(false);//金额

}

//厂家下拉框槽函数
void MainWindow::on_comboBoxFactory_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "请选择厂家")
    { //内容清空
        ui->comboBoxBrand->clear();         //品牌下拉框清空
        ui->lineEditPrice->clear();         //报价清空
        ui->labelLast->setText("0");        //剩余数量清空
        ui->lineEditTotal->clear();         //金额清空
        ui->spinBox->setValue(0);           //数量选择框清空
        ui->spinBox->setEnabled(false);     //数量选择框禁用
        ui->buttonSure->setEnabled(false);  //确定按钮禁用

    }
    else
    {
        ui->comboBoxBrand->clear();
        QSqlQuery query;
        QString sql = QString("select name from brand where factory = '%1'").arg(arg1);
        //select name from brand where factory ='一汽大众';
        //执行sql语句
        query.exec(sql);

        //获取内容
        while( query.next() )
        {
            QString name = query.value(0).toString();
            ui ->comboBoxBrand->addItem(name);
        }
        ui->spinBox->setEnabled(true); //数量选择框禁用

    }
}

void MainWindow::on_comboBoxBrand_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;
    QString sql = QString("select price, last from brand where factory = '%1' and name = '%2'")
            .arg(ui->comboBoxFactory->currentText())//厂家下拉框当前选中内容
            .arg(arg1);
    //select price, last from brand where factory ='一汽大众' and name = '奥迪A6';
    //执行sql语句
    query.exec(sql);

    //获取内容
    while( query.next() )
    {
        //报价
        int price = query.value("price").toInt();
        //剩余数
        int last = query.value("last").toInt();

        //更新到对应的空间
        ui->lineEditPrice->setText( QString:: number(price));
        ui->labelLast->setText( QString::number(last));

    }
}

//数据选择框槽函数
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    //更新剩余数量
    //1)厂家
    QString factoryStr = ui->comboBoxFactory->currentText();
    //2)品牌
    QString brandstr = ui->comboBoxBrand->currentText();
    if(0 == arg1)
    {
        ui->buttonSure->setEnabled(false);
    }
    else
    {
        ui->buttonSure->setEnabled(true);
    }

    QSqlQuery query;
    QString sql = QString("select last from brand where factory = '%1' and name = '%2'")
            .arg(factoryStr)//厂家下拉框当前选中内容
            .arg(brandstr);
    //执行数据库
    query.exec(sql);
    int last;
    while(query.next())
    {
        last = query.value("last").toInt(); //剩余
    }

    if(arg1 > last) //如果选择的数目大小， 剩余数据，中断程序
    {
        ui->spinBox->setValue(last);
        return;
    }


    //解决剩余数量不正确的废弃方案
    //    if(arg1 == 0)//如果等于0
    //    {
    //       // ui->spinBox->setValue(last);
    //        return;
    //    }


    int tempNum = last - arg1;
    ui->labelLast->setText( QString::number(tempNum) );//剩余数量
    //qDebug() << QString::number(tempNum);


    //金额
    int price = ui->lineEditPrice->text().toInt(); //报价
    int sum = price * arg1;
    ui->lineEditTotal->setText( QString::number(sum) );



}

void MainWindow::on_buttonCancel_clicked()
{
    // on_comboBoxFactory_currentIndexChanged("请选择厂家");
    ui->comboBoxFactory->setCurrentIndex(0);

    //视频中需要下面这句话把剩余数量清零
    //但是在我这边不需要下面这句话也可以正常能归零的
    //推测可能是版本问题，我使用的版本是5.14.2
    // ui->labelLast->setText("0");


}

void MainWindow::on_buttonSure_clicked()
{
    //获取信息
    //1)销售数据
    int num = ui->spinBox->value();
    //2)剩余
    int last = ui->labelLast->text().toInt();
    //3)厂家
    QString factoryStr = ui->comboBoxFactory->currentText();
    //4)品牌
    QString brandstr = ui->comboBoxBrand->currentText();
    //获取数据库的销量
    QSqlQuery query;
    QString sql = QString("select sell from brand where factory = '%1' and name = '%2'")
            .arg(factoryStr)//厂家下拉框当前选中内容
            .arg(brandstr);//品牌下拉框当前选中内容
    //执行数据库
    query.exec(sql);

    int sell;
    while( query.next() )
    {
        sell = query.value("sell").toInt();
    }
    //更新数据库，剩余数量， 销售总量
    sell += num;

    sql = QString("update brand set sell = %1, last = %2 where factory = '%3' and name = '%4'")
            .arg(sell)//销售总量
            .arg(last)//剩余数量
            .arg(factoryStr)//厂家下拉框当前选中内容
            .arg(brandstr);//品牌下拉框当前选中内容
    //执行数据库
    query.exec(sql);

    //把确认后的数据，更新到xml中
    QStringList list;
    //下面注释掉的是视频源代码，我将其替换成更易读的代码
//    list << ui->comboBoxFactory->currentText()
//         << ui->comboBoxBrand->currentText()
//         << ui->lineEditPrice->text()
//         << QString::number(num)
//         << ui->lineEditTotal->text();

    list << factoryStr                  //厂家
         << brandstr                    //品牌
         << ui->lineEditPrice->text()   //单价
         << QString::number(num)        //销售数量
         << ui->lineEditTotal->text();  //总价


    DomXML::appendXML( "../demo.xml", list);

        QStringList fList;
        QStringList bList;
        QStringList pList;
        QStringList nList;
        QStringList tList;

        DomXML::readXML("../demo.xml", fList, bList, pList, nList, tList);
        for(int i = 0;i <fList.size();i++)
        {
            QString str = QString("%1:%2:卖出了%3,单价:%4，总价:%5")
                    .arg(fList.at(i))
                    .arg(bList.at(i))
                    .arg(nList.at(i))
                    .arg(pList.at(i))
                    .arg(tList.at(i));
            ui->textEdit->append(str);
            qDebug()<<str;
        }

    ui->buttonSure->setEnabled(false);  //确定按钮禁用
    on_buttonCancel_clicked();
}
