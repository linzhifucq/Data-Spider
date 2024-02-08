

#include "QsLog.h"
#include "QsLogDest.h"
#ifdef QS_LOG_SEPARATE_THREAD
#include <QThreadPool>
#include <QRunnable>
#endif
#include <QMutex>
#include <QVector>
#include <QDateTime>
#include <QtGlobal>
#include <cstdlib>
#include <stdexcept>

namespace QsLogging
{
typedef QVector<DestinationPtr> DestinationList;

static const char TraceString[] = "TRACE";
static const char DebugString[] = "DEBUG";
static const char InfoString[]  = "INFO ";
static const char WarnString[]  = "WARN ";
static const char ErrorString[] = "ERROR";
static const char FatalString[] = "FATAL";
//没有使用 Qt::ISODate 格式。ISO 8601 格式包括日期和时间的表示，并且可以精确到秒，但不包括毫秒。
static const QString fmtDateTime("yyyy-MM-ddThh:mm:ss.zzz");

static Logger* sInstance = 0;

static const char* LevelToText(Level theLevel)
{
    switch (theLevel) {
        case TraceLevel:
            return TraceString;
        case DebugLevel:
            return DebugString;
        case InfoLevel:
            return InfoString;
        case WarnLevel:
            return WarnString;
        case ErrorLevel:
            return ErrorString;
        case FatalLevel:
            return FatalString;
        case OffLevel:
            return "";
        default: {
            Q_ASSERT(!"bad log level");
            return InfoString;
        }
    }
}

#ifdef QS_LOG_SEPARATE_THREAD //假设单独的线程
class LogWriterRunnable : public QRunnable
{
public:
    LogWriterRunnable(QString message, Level level);
    virtual void run();

private:
    QString mMessage;
    Level mLevel;
};
#endif

class LoggerImpl
{
public:
    LoggerImpl();

#ifdef QS_LOG_SEPARATE_THREAD
    QThreadPool threadPool;
#endif
    QMutex logMutex;
    Level level;
    DestinationList destList;
    bool includeTimeStamp;
    bool includeLogLevel;
};

#ifdef QS_LOG_SEPARATE_THREAD
LogWriterRunnable::LogWriterRunnable(QString message, Level level)
    : QRunnable()
    , mMessage(message)
    , mLevel(level)
{
}

void LogWriterRunnable::run()
{
    Logger::instance().write(mMessage, mLevel);
}
#endif


LoggerImpl::LoggerImpl()
    : level(InfoLevel)
    , includeTimeStamp(true)
    , includeLogLevel(true)
{
    // 假设至少有文件和控制台
    destList.reserve(2);
#ifdef QS_LOG_SEPARATE_THREAD
    threadPool.setMaxThreadCount(1);
    threadPool.setExpiryTimeout(-1);
#endif
}


Logger::Logger()
    : d(new LoggerImpl)
{
}

Logger& Logger::instance()
{
    if (!sInstance)
        sInstance = new Logger;

    return *sInstance;
}

void Logger::destroyInstance()
{
    delete sInstance;
    sInstance = 0;
}

// 试图从字符串日志消息中提取级别。如果可用，conversionSucceeded 将包含转换结果。
Level Logger::levelFromLogMessage(const QString& logMessage, bool* conversionSucceeded)
{
    if (conversionSucceeded)
        *conversionSucceeded = true;

    if (logMessage.startsWith(QLatin1String(TraceString)))
        return TraceLevel;
    if (logMessage.startsWith(QLatin1String(DebugString)))
        return DebugLevel;
    if (logMessage.startsWith(QLatin1String(InfoString)))
        return InfoLevel;
    if (logMessage.startsWith(QLatin1String(WarnString)))
        return WarnLevel;
    if (logMessage.startsWith(QLatin1String(ErrorString)))
        return ErrorLevel;
    if (logMessage.startsWith(QLatin1String(FatalString)))
        return FatalLevel;

    if (conversionSucceeded)
        *conversionSucceeded = false;
    return OffLevel;
}

Logger::~Logger()
{
#ifdef QS_LOG_SEPARATE_THREAD
    d->threadPool.waitForDone();
#endif
    delete d;
    d = 0;
}

void Logger::addDestination(DestinationPtr destination)
{
    Q_ASSERT(destination.data());
    d->destList.push_back(destination);
}

void Logger::setLoggingLevel(Level newLevel)
{
    d->level = newLevel;
}

Level Logger::loggingLevel() const
{
    return d->level;
}

void Logger::setIncludeTimestamp(bool e)
{
    d->includeTimeStamp = e;
}

bool Logger::includeTimestamp() const
{
    return d->includeTimeStamp;
}

void Logger::setIncludeLogLevel(bool l)
{
    d->includeLogLevel = l;
}

bool Logger::includeLogLevel() const
{
    return d->includeLogLevel;
}

//创建完整的日志消息并将其传递给记录器
void Logger::Helper::writeToLog()
{
    const char* const levelName = LevelToText(level);
    QString completeMessage;
    Logger &logger = Logger::instance();
    if (logger.includeLogLevel()) {
        completeMessage.
                append(levelName).
                append(' ');
    }
    if (logger.includeTimestamp()) {
        completeMessage.
                append(QDateTime::currentDateTime().toString(fmtDateTime)).
                append(' ');
    }
    completeMessage.append(buffer);
    Logger::instance().enqueueWrite(completeMessage, level);
}

Logger::Helper::~Helper()
{
    try {
        writeToLog();
    }
    catch(std::exception&) {
        // 不应该从一个日志输出位置抛出异常
        Q_ASSERT(!"exception in logger helper destructor");
        throw;
    }
}

// 将消息发送到任务队列或直接写入。
void Logger::enqueueWrite(const QString& message, Level level)
{
#ifdef QS_LOG_SEPARATE_THREAD
    LogWriterRunnable *r = new LogWriterRunnable(message, level);
    d->threadPool.start(r);
#else
    write(message, level);
#endif
}

//将消息发送到所有目标位置。如果消息级别对目标位置的处理有用，那么将该消息级别一并传递。
void Logger::write(const QString& message, Level level)
{
    QMutexLocker lock(&d->logMutex);
    for (DestinationList::iterator it = d->destList.begin(),
        endIt = d->destList.end();it != endIt;++it) {
        (*it)->write(message, level);
    }
}

}
