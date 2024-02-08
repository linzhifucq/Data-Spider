
#ifndef QXLSX_NUMFORMATPARSER_H
#define QXLSX_NUMFORMATPARSER_H


#include "xlsxglobal.h"

QT_BEGIN_NAMESPACE_XLSX

class NumFormatParser
{
public:
    static bool isDateTime(const QString &formatCode);
};

QT_END_NAMESPACE_XLSX

#endif // QXLSX_NUMFORMATPARSER_H
