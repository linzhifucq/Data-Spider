
#ifndef QSLOGDEST_H
#define QSLOGDEST_H

#include "QsLogLevel.h"
#include <QSharedPointer>
#include <QtGlobal>
class QString;
class QObject;

#ifdef QSLOG_IS_SHARED_LIBRARY
#define QSLOG_SHARED_OBJECT Q_DECL_EXPORT
#elif QSLOG_IS_SHARED_LIBRARY_IMPORT
#define QSLOG_SHARED_OBJECT Q_DECL_IMPORT
#else
#define QSLOG_SHARED_OBJECT
#endif

namespace QsLogging
{

class QSLOG_SHARED_OBJECT Destination
{
public:
    typedef void (*LogFunction)(const QString &message, Level level);

public:
    virtual ~Destination();
    virtual void write(const QString& message, Level level) = 0;
    virtual bool isValid() = 0;
};
typedef QSharedPointer<Destination> DestinationPtr;


enum LogRotationOption
{
    DisableLogRotation = 0,
    EnableLogRotation  = 1
};

struct QSLOG_SHARED_OBJECT MaxSizeBytes
{
    MaxSizeBytes() : size(0) {}
    explicit MaxSizeBytes(qint64 size_) : size(size_) {}
    qint64 size;
};

struct QSLOG_SHARED_OBJECT MaxOldLogCount
{
    MaxOldLogCount() : count(0) {}
    explicit MaxOldLogCount(int count_) : count(count_) {}
    int count;
};


//创建日志记录目标/输出位置。调用者与日志记录器共享这些目标的所有权。添加到日志记录器后，调用者可以丢弃这些指针。
class QSLOG_SHARED_OBJECT DestinationFactory
{
public:
    static DestinationPtr MakeFileDestination(const QString& filePath,
        LogRotationOption rotation = DisableLogRotation,//表示日志轮转选项。
        const MaxSizeBytes &sizeInBytesToRotateAfter = MaxSizeBytes(),//表示在达到指定字节数后进行日志轮转。
        const MaxOldLogCount &oldLogsToKeep = MaxOldLogCount());//表示要保留的旧日志数量。
    static DestinationPtr MakeDebugOutputDestination();//创建一个适用于调试目的的日志目的地，通常用于将日志消息输出到标准调试输出流或其他调试工具中。
    // takes a pointer to a function
    //将函数指针传递给此函数，可以创建一个自定义的日志处理函数，并将其用作日志目的地的写入操作。
    static DestinationPtr MakeFunctorDestination(Destination::LogFunction f);
    // takes a QObject + signal/slot
    //可以将一个特定的 QObject 的信号与槽连接到日志系统，以实现自定义的日志处理逻辑。
    static DestinationPtr MakeFunctorDestination(QObject *receiver, const char *member);
};

} // end namespace

#endif // QSLOGDEST_H
