
#ifndef XLSXRICHSTRING_P_H
#define XLSXRICHSTRING_P_H



#include "xlsxrichstring.h"

QT_BEGIN_NAMESPACE_XLSX

class RichStringPrivate : public QSharedData
{
public:
    RichStringPrivate();
    RichStringPrivate(const RichStringPrivate &other);
    ~RichStringPrivate();

    QByteArray idKey() const;

    QStringList fragmentTexts;
    QList<Format> fragmentFormats;
    QByteArray _idKey;
    bool _dirty;
};

QT_END_NAMESPACE_XLSX

#endif // XLSXRICHSTRING_P_H
