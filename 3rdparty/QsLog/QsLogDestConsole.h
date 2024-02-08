
#ifndef QSLOGDESTCONSOLE_H
#define QSLOGDESTCONSOLE_H

#include "QsLogDest.h"

class QString;

class QsDebugOutput
{
public:
   static void output(const QString& a_message);
};

namespace QsLogging
{

// debugger sink
class DebugOutputDestination : public Destination
{
public:
    virtual void write(const QString& message, Level level);
    virtual bool isValid();
};

}

#endif // QSLOGDESTCONSOLE_H
