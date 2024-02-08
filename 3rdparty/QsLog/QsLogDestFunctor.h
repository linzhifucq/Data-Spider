
#ifndef QSLOGDESTFUNCTOR_H
#define QSLOGDESTFUNCTOR_H

#include "QsLogDest.h"
#include <QObject>

namespace QsLogging
{

class FunctorDestination : public QObject, public Destination
{
    Q_OBJECT
public:
    explicit FunctorDestination(LogFunction f);
    FunctorDestination(QObject *receiver, const char *member);

    virtual void write(const QString &message, Level level);
    virtual bool isValid();

protected:
    // // 为避免注册新的枚举类型而使用 int
    Q_SIGNAL void logMessageReady(const QString &message, int level);

private:
    LogFunction mLogFunction;
};
}

#endif // QSLOGDESTFUNCTOR_H
