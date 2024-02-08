﻿#include "mFlowRightMouseWidget.h"
#include "Utils/models.h"
#include "mOptionBox.h"
#include "mRightSave.h"
#include "style.h"
#include "TaskFlow/mFcModels.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>

MFlowRightMouseWidget::MFlowRightMouseWidget(QWidget *parent,MFlowStepData* data) :
    QWidget(parent)
{
    m_data = data;
    m_params = static_cast<MFlowStepParamsMouse*>(data->stepparams);

    boxLayout = new QVBoxLayout(this);
    boxLayout->setContentsMargins(10,5,10,5);
    initInfoUI();
    initSenierOptionUI();
//    initRetryUI();
    MRightSave *rightSave = new MRightSave(this);
    connect(rightSave,&MRightSave::notifySave,this,&MFlowRightMouseWidget::onSave);
    boxLayout->addWidget(rightSave);
    boxLayout->addStretch(10);

}
void MFlowRightMouseWidget::onSave(bool clicked){
    Q_UNUSED(clicked);

    m_params->name = nameLine->text();

    m_params->waitSleep = waitSpin->value();


    m_params->eleXpath = eleXpathLine->text();
    m_params->eleText = eleTextLine->text();
    m_params->isLoop = loopCheck->checkState()==Qt::CheckState::Checked?true:false;

}
void MFlowRightMouseWidget::initInfoUI(){
    QWidget *infoWidget = new QWidget(this);
    infoWidget->setFixedHeight(40);
    QHBoxLayout *infoLayout = new QHBoxLayout(infoWidget);

    // 第一行
    QLabel * nameLabel = new QLabel(infoWidget);
    nameLabel->setText(tr("操作名称"));
    nameLine = new QLineEdit(infoWidget);

    nameLine->setStyleSheet(m_stylesheet_QLineEdit);
    nameLine->setText(m_params->name);
    nameLine->setFixedWidth(160);

    infoLayout->addWidget(nameLabel);
    infoLayout->addSpacing(20);
    infoLayout->addWidget(nameLine);
    infoLayout->addStretch(10);

    boxLayout->addWidget(infoWidget);

}
void MFlowRightMouseWidget::initSenierOptionUI(){

    // 高级选项
    MOptionBox *optionBox = new MOptionBox(this);
    // 执行前等待
    QLabel *waitLabel = new QLabel(optionBox->gWidget);
    waitLabel->setText("执行前等待");
    waitSpin = new QSpinBox(optionBox->gWidget);
    waitSpin->setMinimum(0);
    waitSpin->setMaximum(30);
    waitSpin->setSuffix("秒");
    waitSpin->setMaximumWidth(160);
    waitSpin->setStyleSheet(m_stylesheet_QSpinBox);
    waitSpin->setValue(m_params->waitSleep);

    optionBox->gLayout->addWidget(waitLabel,optionBox->rowStart,0);
    optionBox->gLayout->addWidget(waitSpin,optionBox->rowStart,1);
    ++optionBox->rowStart;
    QLabel *eleXpathLabel= new QLabel(optionBox->gWidget);
    eleXpathLabel->setText(tr("元素xpath"));
    eleXpathLine = new QLineEdit(optionBox->gWidget);
    eleXpathLine->setStyleSheet(m_stylesheet_QLineEdit);
    eleXpathLine->setText(m_params->eleXpath);

    optionBox->gLayout->addWidget(eleXpathLabel,optionBox->rowStart,0);
    optionBox->gLayout->addWidget(eleXpathLine,optionBox->rowStart,1);
    ++optionBox->rowStart;
      QLabel *eleTextLabel = new QLabel(optionBox->gWidget);
      eleTextLabel->setText(tr("元素标签"));
      eleTextLine = new QLineEdit(optionBox->gWidget);
      eleTextLine->setStyleSheet(m_stylesheet_QLineEdit);
      eleTextLine->setText(this->m_params->eleText);
      optionBox->gLayout->addWidget(eleTextLabel,optionBox->rowStart,0);
      optionBox->gLayout->addWidget(eleTextLine,optionBox->rowStart,1);

    ++optionBox->rowStart;
    QLabel *loopLabel = new QLabel(optionBox->gWidget);
    loopLabel->setText(tr("使用循环"));
    loopCheck = new QCheckBox(optionBox->gWidget);
    loopCheck->setText(tr("点击当前循环中设置的元素"));
    loopCheck->setChecked(m_params->isLoop);
    optionBox->gLayout->addWidget(loopLabel,optionBox->rowStart,0);
    optionBox->gLayout->addWidget(loopCheck,optionBox->rowStart,1);


    boxLayout->addWidget(optionBox);

}
MFlowRightMouseWidget::~MFlowRightMouseWidget()
{

}
