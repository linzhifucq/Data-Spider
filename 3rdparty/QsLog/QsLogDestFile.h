
#ifndef QSLOGDESTFILE_H
#define QSLOGDESTFILE_H

#include "QsLogDest.h"
#include <QFile>
#include <QTextStream>
#include <QtGlobal>
#include <QSharedPointer>

namespace QsLogging
{
class RotationStrategy
{
public:
    virtual ~RotationStrategy();
    //用于设置日志轮转策略的初始信息
    virtual void setInitialInfo(const QFile &file) = 0;
    //将消息包含在计算中
    virtual void includeMessageInCalculation(const QString &message) = 0;
    //判断是否应该执行日志轮转操作，返回布尔值
    virtual bool shouldRotate() = 0;
    //执行轮转操作
    virtual void rotate() = 0;
    //QIODevice::OpenMode是用于指定设备打开模式的枚举类型，这个函数返回推荐的打开模式
    virtual QIODevice::OpenMode recommendedOpenModeFlag() = 0;
};

// 永远不会对文件进行轮转，而是覆盖现有文件
class NullRotationStrategy : public RotationStrategy
{
public:
    virtual void setInitialInfo(const QFile &) {}
    virtual void includeMessageInCalculation(const QString &) {}
    virtual bool shouldRotate() { return false; }
    virtual void rotate() {}
    virtual QIODevice::OpenMode recommendedOpenModeFlag() { return QIODevice::Truncate; }
};

//在达到一定大小后进行轮转，并保留不超过 10 个备份文件，并将内容追加到现有文件中
class SizeRotationStrategy : public RotationStrategy
{
public:
    SizeRotationStrategy();
    static const int MaxBackupCount;

    virtual void setInitialInfo(const QFile &file);
    virtual void includeMessageInCalculation(const QString &message);
    virtual bool shouldRotate();
    virtual void rotate();
    virtual QIODevice::OpenMode recommendedOpenModeFlag();

    void setMaximumSizeInBytes(qint64 size);
    void setBackupCount(int backups);

private:
    QString mFileName;
    qint64 mCurrentSizeInBytes;
    qint64 mMaxSizeInBytes;
    int mBackupsCount;
};

typedef QSharedPointer<RotationStrategy> RotationStrategyPtr;


class FileDestination : public Destination
{
public:
    FileDestination(const QString& filePath, RotationStrategyPtr rotationStrategy);
    virtual void write(const QString& message, Level level);
    virtual bool isValid();

private:
    QFile mFile;
    QTextStream mOutputStream;
    QSharedPointer<RotationStrategy> mRotationStrategy;
};

}

#endif // QSLOGDESTFILE_H
