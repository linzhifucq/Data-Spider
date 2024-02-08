﻿#include "Index.h"
#include "ComLineWidget.h"
#include "ReportThread.h"
#include "style.h"
#include "constant.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QAction>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QTimer>
#include <QsLog.h>

Index::Index(QWidget *parent) : QWidget(parent)
{

    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,2,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(new ComLineWidget(this));

    initUI();
    if(IS_reportHeart){
        mReportThread= new ReportThread(this);
        mReportThread->start();

    }
}
Index::~Index(){
    if(IS_reportHeart){
        if(mReportThread){
            delete mReportThread;
            mReportThread = nullptr;
        }
    }
}
void Index::initUI(){

    QWidget *boxWidget = new QWidget(this);
    QVBoxLayout *boxVLayout = new QVBoxLayout(boxWidget);
    boxVLayout->setContentsMargins(0,0,0,0);

    // 介绍行
    QWidget * introWidget = new QWidget(boxWidget);
    introWidget->setFixedHeight(50);
    QHBoxLayout *introHLayout = new QHBoxLayout(introWidget);
    introHLayout->setContentsMargins(0,0,0,0);

    QLabel *nameLabel = new QLabel(boxWidget);
    nameLabel->setStyleSheet(m_stylesheet_QLabel30);
    nameLabel->setText(QCoreApplication::applicationName());


    QLabel *summaryLabel = new QLabel(boxWidget);
    summaryLabel->setStyleSheet(".QLabel{color:rgb(64,65,66);font-family:Microsoft YaHei;font-size:16px;}");
    summaryLabel->setText("无需编程的数据采集工具");

    introHLayout->addStretch(10);
    introHLayout->addWidget(nameLabel);
    introHLayout->addSpacing(5);
    introHLayout->addWidget(summaryLabel);
    introHLayout->addStretch(10);

   // 图标行
    QWidget * imgWidget = new QWidget(boxWidget);
    imgWidget->setFixedHeight(100);
    QHBoxLayout *imgHLayout = new QHBoxLayout(imgWidget);
    imgHLayout->setContentsMargins(0,0,0,0);

    QLabel *logo = new QLabel(imgWidget);
    logo->setPixmap(QIcon(":/res/images/logo.png").pixmap(100,100));
   imgHLayout->addStretch(10);
      imgHLayout->addWidget(logo);
   imgHLayout->addStretch(10);

    // 任务提交行
    QWidget * taskWidget = new QWidget(boxWidget);
    taskWidget->setFixedHeight(50);
    QHBoxLayout *taskHLayout = new QHBoxLayout(taskWidget);
    taskHLayout->setContentsMargins(0,0,0,0);


    QLineEdit *inputLine = new QLineEdit(taskWidget);
    inputLine->setFixedSize(500,40);
    inputLine->setPlaceholderText("请输入目标网站的网址");
    inputLine->setStyleSheet(m_stylesheet_QLineEdit);
    inputLine->setClearButtonEnabled(true);
    inputLine->setFocusPolicy(Qt::FocusPolicy::ClickFocus);

    QAction *inputAction = new QAction(inputLine);
    inputAction->setIcon(QIcon(":/res/images/icon/searchblack.png"));
    inputLine->addAction(inputAction,QLineEdit::LeadingPosition);


    QPushButton *addTaskBtn = new QPushButton(taskWidget);
    addTaskBtn->setCursor(Qt::PointingHandCursor);
    addTaskBtn->setFixedSize(110,35);
    addTaskBtn->setStyleSheet(m_stylesheet_QPushButton_hollow);
    addTaskBtn->setText("新建任务");
    addTaskBtn->setIcon(QIcon(":/res/images/icon/mainwindow/add.png"));
    addTaskBtn->setIconSize(QSize(20,20));


    taskHLayout->addStretch(10);
    taskHLayout->addWidget(inputLine);
    taskHLayout->addSpacing(10);
    taskHLayout->addWidget(addTaskBtn);
    taskHLayout->addStretch(10);

    connect(addTaskBtn,&QPushButton::clicked,this,[this,inputLine](){
        QString address = inputLine->text().trimmed();
        emit this->notifyCreateTask(address);

    });

    boxVLayout->addSpacing(20);
    boxVLayout->addWidget(imgWidget);
    boxVLayout->addSpacing(10);
    boxVLayout->addWidget(introWidget);
    boxVLayout->addSpacing(15);
    boxVLayout->addWidget(taskWidget);
    boxVLayout->addSpacing(50);
    boxVLayout->addStretch(10);


    mainLayout->addWidget(boxWidget);

}
