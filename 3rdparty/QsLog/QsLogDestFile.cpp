
#include "QsLogDestFile.h"
#include <QTextCodec>
#include <QDateTime>
#include <QtGlobal>
#include <iostream>

//执行日志文件大小轮转策略时保留的最大备份文件数量为10个。
const int QsLogging::SizeRotationStrategy::MaxBackupCount = 10;

QsLogging::RotationStrategy::~RotationStrategy()
{
}

QsLogging::SizeRotationStrategy::SizeRotationStrategy()
    : mCurrentSizeInBytes(0)
    , mMaxSizeInBytes(0)
    , mBackupsCount(0)
{
}
//设置初始信息
void QsLogging::SizeRotationStrategy::setInitialInfo(const QFile &file)
{
    mFileName = file.fileName();
    mCurrentSizeInBytes = file.size();
}
//将消息包含在计算中
void QsLogging::SizeRotationStrategy::includeMessageInCalculation(const QString &message)
{
    mCurrentSizeInBytes += message.toUtf8().size();
}
//判断是否应该执行轮询操作
bool QsLogging::SizeRotationStrategy::shouldRotate()
{
    return mCurrentSizeInBytes > mMaxSizeInBytes;
}

// 该算法假设备份文件的命名方式为filename.X，其中1 <= X <= mBackupsCount。所有的X都将被向上调整。
void QsLogging::SizeRotationStrategy::rotate()
{
    if (!mBackupsCount) {
        if (!QFile::remove(mFileName))
            std::cerr << "QsLog: backup delete failed " << qPrintable(mFileName);
        return;
    }

     // 1. 找到可以向上移动的最后一个现有备份
     const QString logNamePattern = mFileName + QString::fromUtf8(".%1");
     int lastExistingBackupIndex = 0;
     for (int i = 1;i <= mBackupsCount;++i) {
         const QString backupFileName = logNamePattern.arg(i);
         if (QFile::exists(backupFileName))
             lastExistingBackupIndex = qMin(i, mBackupsCount - 1);
         else
             break;
     }

     // 2. 向上移动
     for (int i = lastExistingBackupIndex;i >= 1;--i) {
         const QString oldName = logNamePattern.arg(i);
         const QString newName = logNamePattern.arg(i + 1);
         QFile::remove(newName);
         const bool renamed = QFile::rename(oldName, newName);
         if (!renamed) {
             std::cerr << "QsLog: could not rename backup " << qPrintable(oldName)
                       << " to " << qPrintable(newName);
         }
     }

     // 3. 重新命名当前的日志文件
     const QString newName = logNamePattern.arg(1);
     if (QFile::exists(newName))
         QFile::remove(newName);
     if (!QFile::rename(mFileName, newName)) {
         std::cerr << "QsLog: could not rename log " << qPrintable(mFileName)
                   << " to " << qPrintable(newName);
     }
}

QIODevice::OpenMode QsLogging::SizeRotationStrategy::recommendedOpenModeFlag()
{
    return QIODevice::Append;
}

void QsLogging::SizeRotationStrategy::setMaximumSizeInBytes(qint64 size)
{
    Q_ASSERT(size >= 0);
    mMaxSizeInBytes = size;
}

void QsLogging::SizeRotationStrategy::setBackupCount(int backups)
{
    Q_ASSERT(backups >= 0);
    mBackupsCount = qMin(backups, SizeRotationStrategy::MaxBackupCount);
}


QsLogging::FileDestination::FileDestination(const QString& filePath, RotationStrategyPtr rotationStrategy)
    : mRotationStrategy(rotationStrategy)
{
    mFile.setFileName(filePath);
    if (!mFile.open(QFile::WriteOnly | QFile::Text | mRotationStrategy->recommendedOpenModeFlag()))
        std::cerr << "QsLog: could not open log file " << qPrintable(filePath);
    mOutputStream.setDevice(&mFile);

#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))

    mOutputStream.setCodec(QTextCodec::codecForName("UTF-8"));
#endif

    mRotationStrategy->setInitialInfo(mFile);
}

void QsLogging::FileDestination::write(const QString& message, Level)
{
    mRotationStrategy->includeMessageInCalculation(message);
    if (mRotationStrategy->shouldRotate()) {
        mOutputStream.setDevice(NULL);
        mFile.close();
        mRotationStrategy->rotate();
        if (!mFile.open(QFile::WriteOnly | QFile::Text | mRotationStrategy->recommendedOpenModeFlag()))
            std::cerr << "QsLog: could not reopen log file " << qPrintable(mFile.fileName());
        mRotationStrategy->setInitialInfo(mFile);
        mOutputStream.setDevice(&mFile);
    }
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))

    mOutputStream << message << "\n";
#else
    mOutputStream << message << endl;
#endif

    mOutputStream.flush();
}

bool QsLogging::FileDestination::isValid()
{
    return mFile.isOpen();
}

