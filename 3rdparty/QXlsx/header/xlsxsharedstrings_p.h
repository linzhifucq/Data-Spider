
#ifndef XLSXSHAREDSTRINGS_H
#define XLSXSHAREDSTRINGS_H


#include <QHash>
#include <QStringList>
#include <QIODevice>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "xlsxglobal.h"
#include "xlsxrichstring.h"
#include "xlsxabstractooxmlfile.h"

QT_BEGIN_NAMESPACE_XLSX

class XlsxSharedStringInfo
{
public:
    XlsxSharedStringInfo(int index=0, int count = 1) :
        index(index), count(count)
    {
    }

    int index;
    int count;
};

class  SharedStrings : public AbstractOOXmlFile
{
public:
    SharedStrings(CreateFlag flag);
    int count() const;
    bool isEmpty() const;
    
    int addSharedString(const QString &string);
    int addSharedString(const RichString &string);
    void removeSharedString(const QString &string);
    void removeSharedString(const RichString &string);
    void incRefByStringIndex(int idx);

    int getSharedStringIndex(const QString &string) const;
    int getSharedStringIndex(const RichString &string) const;
    RichString getSharedString(int index) const;
    QList<RichString> getSharedStrings() const;

    void saveToXmlFile(QIODevice *device) const override;
    bool loadFromXmlFile(QIODevice *device) override;

private:
    void readString(QXmlStreamReader &reader); // <si>
    void readRichStringPart(QXmlStreamReader &reader, RichString &rich); // <r>
    void readPlainStringPart(QXmlStreamReader &reader, RichString &rich); // <v>
    Format readRichStringPart_rPr(QXmlStreamReader &reader);
    void writeRichStringPart_rPr(QXmlStreamWriter &writer, const Format &format) const;

    QHash<RichString, XlsxSharedStringInfo> m_stringTable; //for fast lookup
    QList<RichString> m_stringList;
    int m_stringCount;
};

QT_END_NAMESPACE_XLSX

#endif // XLSXSHAREDSTRINGS_H
