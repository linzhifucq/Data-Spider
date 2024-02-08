INCLUDEPATH += $$PWD
#DEFINES += QS_LOG_LINE_NUMBERS    # 使日志自动记录文件和行号信息
#DEFINES += QS_LOG_DISABLE         # 将日志记录代码替换为一个空操作
#DEFINES += QS_LOG_SEPARATE_THREAD # 使日志消息在一个单独的线程中排队并写入。
SOURCES += $$PWD/QsLogDest.cpp \
    $$PWD/QsLog.cpp \
    $$PWD/QsLogDestConsole.cpp \
    $$PWD/QsLogDestFile.cpp \
    $$PWD/QsLogDestFunctor.cpp

HEADERS += $$PWD/QsLogDest.h \
    $$PWD/QsLog.h \
    $$PWD/QsLogDestConsole.h \
    $$PWD/QsLogLevel.h \
    $$PWD/QsLogDestFile.h \
    $$PWD/QsLogDisableForThisFile.h \
    $$PWD/QsLogDestFunctor.h

OTHER_FILES += \
    $$PWD/QsLogChanges.txt \
    $$PWD/QsLogReadme.txt \
    $$PWD/LICENSE.txt
