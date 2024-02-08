﻿#include "mFlowLoopWidget.h"
#include "ui_mFlowLoopWidget.h"
#include "mFlowLoopWidget.h"
#include "mFlowStepMenuDialog.h"
#include "TaskFlow/pageCustomtaskFlowControl.h"
#include "TaskFlow/mFcModels.h"
#include "mDownArrow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMimeData>
#include <QDrag>
#include <QMouseEvent>

const int FLOW_LOOP_WIDGET_WIDTH = 180;
const int FLOW_LOOP_WIDGET_HEIGHT = 110;

MFlowLoopWidget::MFlowLoopWidget(QWidget *parent,MControl *control,MDownArrow *arrow,MDownArrow *innerDefaultArrow,MFlowStepParams *params,bool bgnormal) :
    QWidget(parent),
    ui(new Ui::MFlowLoopWidget)
{
    ui->setupUi(this);
    setFixedSize(FLOW_LOOP_WIDGET_WIDTH,FLOW_LOOP_WIDGET_HEIGHT);
    setAttribute(Qt::WA_StyledBackground,true);
    if(bgnormal){
        setStyleSheet(m_stylesheet_QWidget_flowleftwidget_blue_normal);
    }else {
        setStyleSheet(m_stylesheet_QWidget_flowleftwidget_blue_press);
    }
    setCursor(Qt::PointingHandCursor);

    this->arrow = arrow;
    this->data = new MFlowStepData(control,params);
    this->data->widget=this;

    this->innerDefaultArrow = innerDefaultArrow;
    m_fc = static_cast<PageCustomTaskFlowControl *>(this->parentWidget());


    ui->topWidget->setStyleSheet(".QWidget{background-color: rgba(0,0,0,0);}");
    ui->bottomWidget->setStyleSheet(".QWidget{background-color: rgb(255,255,255);}");
    ui->titleLabel->setStyleSheet(m_stylesheet_QLabel_title);

    title = ui->titleLabel;
    title->setText(control->menuTip);


    setAcceptDrops(true);
    boxLayout = new QVBoxLayout(ui->bottomWidget);
    boxLayout->setContentsMargins(0,0,0,0);
    boxLayout->setSpacing(0);
    boxLayout->addWidget(innerDefaultArrow,0,Qt::AlignCenter);


}
MFlowLoopWidget::~MFlowLoopWidget()
{
    data->widgetIsDelete = true;
    delete ui;
    delete data;
}

void MFlowLoopWidget::dragEnterEvent(QDragEnterEvent *event)
{
    m_fc->dragEnterEvery(event);

}

void MFlowLoopWidget::dropEvent(QDropEvent *event)
{
    m_fc->dropEvery(this,boxLayout,event);
}
void MFlowLoopWidget::mousePressEvent(QMouseEvent *event)
{

    if(event->button()==Qt::LeftButton){
        QObject *pressObject = static_cast<QObject*>(childAt(event->pos()));
        if(pressObject){
            if("MDownArrow"==QString(pressObject->metaObject()->className())){
                // 在循环控件里，点击向下的箭头，需要屏蔽，否则会引起混乱
//                qDebug()<<"MFlowLoopWidget::mousePressEvent（In the loop control, click the down arrow, you need to shield it, otherwise it will cause confusion）";
                return;

            }
        }
        setStyleSheet(m_stylesheet_QWidget_flowleftwidget_blue_press);
        this->data->notificationType=MCONNSTANT_NOTIFICATION_TYPE_START;
        emit this->notificationToParentWidget(this->data);
        // 当前自身控件的坐标 this->pos()
        // 当前自身控件的尺寸 this->size()

        QWidget *mask = new QWidget(this);
        mask->setObjectName("mask");
        mask->setStyleSheet("QWidget#mask{background-color: rgba(255,255,255,0.1);}");

        mask->setFixedSize(this->size());
        mask->move(QPoint(0,0));
        mask->show();

        QPoint offset = event->pos();
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream<< offset ;

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/MFlowLoopWidget", itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
//        drag->setPixmap(nullptr);
        drag->setHotSpot(offset);


        if (drag->exec(Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction){
           mask->hide();
           delete mask;
           this->data->notificationType=MCONNSTANT_NOTIFICATION_TYPE_MOVE_END_SHOWCONTENT;
           emit this->notificationToParentWidget(this->data);
       } else {
           mask->hide();
           delete mask;
           this->data->notificationType=MCONNSTANT_NOTIFICATION_TYPE_OTHER_END_SHOWCONTENT;
           emit this->notificationToParentWidget(this->data);
        }
     }else {

        MFlowStepMenuDialog *menu = new MFlowStepMenuDialog(this);
        connect(menu->deleteBtn,&QPushButton::clicked,[this,menu](){

            this->data->notificationType=MCONNSTANT_NOTIFICATION_TYPE_DELETE_CURRENT_WIDGET;
            emit this->notificationToParentWidget(this->data);

            menu->deleteLater();
        });
        menu->setAttribute(Qt::WA_DeleteOnClose);
        menu->move(QCursor::pos());
        menu->show();
    }
}
void MFlowLoopWidget::updateFixedSize(){
    // 计算当前所有控件中，尺寸最宽的控件
    int final_width = 0;
    int final_height = 0;

    int max_width = 0;
    for (int i=0;i<boxLayout->count();++i) {
        max_width = boxLayout->itemAt(i)->widget()->width();
        final_height +=boxLayout->itemAt(i)->widget()->height();
        if(max_width>final_width){
            final_width = max_width;
        }
    }
    final_width =int(final_width*1.2);
    if(final_width<FLOW_LOOP_WIDGET_WIDTH){
        final_width = FLOW_LOOP_WIDGET_WIDTH;
    }
    final_height +=50;// 50是循环框top menu的高度
    if(final_height<FLOW_LOOP_WIDGET_HEIGHT){
        final_height = FLOW_LOOP_WIDGET_HEIGHT;
    }

    setFixedSize(final_width,final_height);

}

