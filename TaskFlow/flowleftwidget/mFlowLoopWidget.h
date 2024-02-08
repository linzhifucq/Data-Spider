﻿#ifndef M_FLOW_LOOP_WIDGET_H
#define M_FLOW_LOOP_WIDGET_H

#include <QWidget>
QT_BEGIN_NAMESPACE;
class QLabel;
class QVBoxLayout;
QT_END_NAMESPACE;
class PageCustomTaskFlowControl;
class MFlowStepData;
class MFlowStepParams;
class MDownArrow;
class MControl;

namespace Ui {
class MFlowLoopWidget;
}

class MFlowLoopWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MFlowLoopWidget(QWidget *parent,MControl *menu,MDownArrow *arrow,MDownArrow *innerDefaultArrow,MFlowStepParams *params=nullptr,bool bgnormal=false);
    ~MFlowLoopWidget();

    MDownArrow * arrow;//附属的箭头，位于widget之上，方向朝下
    MDownArrow * innerDefaultArrow; // 初始化时默认的箭头

    MFlowStepData* data;
    QVBoxLayout *boxLayout;
    QLabel *title;

    void updateFixedSize();
    QWidget *currentParentWidget;//当前窗体在历经拖拽等一系列动作后，最新的父窗体
private:
    PageCustomTaskFlowControl *m_fc;

protected:

    void mousePressEvent(QMouseEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
//    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;


signals:
    void notificationToParentWidget(MFlowStepData* data); // 与PageCustomTaskFlowControl 的onNotificationFromChildWidget(int) 形成信号发送接收关系

public slots:


private:
    Ui::MFlowLoopWidget *ui;
};

#endif // M_FLOW_LOOP_WIDGET_H
