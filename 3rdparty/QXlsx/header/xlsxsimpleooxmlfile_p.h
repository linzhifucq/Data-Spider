
#ifndef XLSXSIMPLEOOXMLFILE_H
#define XLSXSIMPLEOOXMLFILE_H

#include "xlsxabstractooxmlfile.h"

#include <QString>
#include <QIODevice>

QT_BEGIN_NAMESPACE_XLSX

class SimpleOOXmlFile : public AbstractOOXmlFile
{
public:
    SimpleOOXmlFile(CreateFlag flag);

    void saveToXmlFile(QIODevice *device) const override;
    QByteArray saveToXmlData() const override;
    bool loadFromXmlData(const QByteArray &data) override;
    bool loadFromXmlFile(QIODevice *device) override;

    QByteArray xmlData;
};

QT_END_NAMESPACE_XLSX

#endif // XLSXSIMPLEOOXMLFILE_H
