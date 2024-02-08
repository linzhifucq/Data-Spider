

#include "QsLogDestFunctor.h"
#include <cstddef>
#include <QtGlobal>

QsLogging::FunctorDestination::FunctorDestination(LogFunction f)
    : QObject(NULL)
    , mLogFunction(f)
{
}
//函数对象目标，连接信号与槽函数
QsLogging::FunctorDestination::FunctorDestination(QObject *receiver, const char *member)
    : QObject(NULL)
    , mLogFunction(NULL)
{
    connect(this, SIGNAL(logMessageReady(QString,int)), receiver, member, Qt::QueuedConnection);
}


void QsLogging::FunctorDestination::write(const QString &message, QsLogging::Level level)
{
    if (mLogFunction)
        mLogFunction(message, level);

    if (level > QsLogging::TraceLevel)
        emit logMessageReady(message, static_cast<int>(level));
}

bool QsLogging::FunctorDestination::isValid()
{
    return true;
}
