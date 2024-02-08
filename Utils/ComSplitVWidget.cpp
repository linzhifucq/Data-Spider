﻿#include "ComSplitVWidget.h"
ComSplitVWidget::ComSplitVWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground,true);
    setStyleSheet(".ComSplitVWidget{background-color:rgb(221,222,225);}");

    setCursor(Qt::SplitVCursor);
}
void ComSplitVWidget::mousePressEvent(QMouseEvent *event){

    if (event->button() == Qt::LeftButton){
        this->raise();//将此按钮移动到顶层显示
        this->pressPoint =event->pos();
    }

}

void ComSplitVWidget::mouseMoveEvent(QMouseEvent *event){

    if(event->buttons() == Qt::LeftButton){
        QPoint change= event->pos() - this->pressPoint;
        int distance = change.y();
        emit moveDistance(distance);

    }
}
