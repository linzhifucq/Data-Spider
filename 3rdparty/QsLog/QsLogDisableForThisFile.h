#ifndef QSLOGDISABLEFORTHISFILE_H
#define QSLOGDISABLEFORTHISFILE_H

#include <QtDebug>


#undef QLOG_TRACE
#undef QLOG_DEBUG
#undef QLOG_INFO
#undef QLOG_WARN
#undef QLOG_ERROR
#undef QLOG_FATAL

#define QLOG_TRACE() if (1) {} else qDebug()
#define QLOG_DEBUG() if (1) {} else qDebug()
#define QLOG_INFO()  if (1) {} else qDebug()
#define QLOG_WARN()  if (1) {} else qDebug()
#define QLOG_ERROR() if (1) {} else qDebug()
#define QLOG_FATAL() if (1) {} else qDebug()

#endif // QSLOGDISABLEFORTHISFILE_H
