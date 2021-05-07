#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("小弟");
    b.setParent(this);
    b.setText("切换到主窗口");
    b.move(300,100);

    connect(&b, &QPushButton::clicked, this, &SubWidget::sendSlot);

    resize(400,400);
}

void SubWidget::sendSlot()
{
    emit mySignal();
    emit mySignal(250,"我是子窗口");
}
