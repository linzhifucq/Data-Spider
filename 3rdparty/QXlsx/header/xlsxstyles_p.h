
#ifndef XLSXSTYLES_H
#define XLSXSTYLES_H

#include <QSharedPointer>
#include <QHash>
#include <QList>
#include <QMap>
#include <QStringList>
#include <QVector>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QIODevice>

// class StylesTest;

#include "xlsxglobal.h"
#include "xlsxformat.h"
#include "xlsxabstractooxmlfile.h"

QT_BEGIN_NAMESPACE_XLSX

class Format;
class XlsxColor;

struct XlsxFormatNumberData
{
    XlsxFormatNumberData() : formatIndex(0) {}

    int formatIndex;
    QString formatString;
};

class Styles : public AbstractOOXmlFile
{
public:
    Styles(CreateFlag flag);
    ~Styles();
    void addXfFormat(const Format &format, bool force=false);
    Format xfFormat(int idx) const;
    void addDxfFormat(const Format &format, bool force=false);
    Format dxfFormat(int idx) const;

    void saveToXmlFile(QIODevice *device) const override;
    bool loadFromXmlFile(QIODevice *device) override;

    QColor getColorByIndex(int idx);

private:
    friend class Format;
    // friend class ::StylesTest;

    void fixNumFmt(const Format &format);

    void writeNumFmts(QXmlStreamWriter &writer) const;
    void writeFonts(QXmlStreamWriter &writer) const;
    void writeFont(QXmlStreamWriter &writer, const Format &font, bool isDxf = false) const;
    void writeFills(QXmlStreamWriter &writer) const;
    void writeFill(QXmlStreamWriter &writer, const Format &fill, bool isDxf = false) const;
    void writeBorders(QXmlStreamWriter &writer) const;
    void writeBorder(QXmlStreamWriter &writer, const Format &border, bool isDxf = false) const;
    void writeSubBorder(QXmlStreamWriter &writer, const QString &type, int style, const XlsxColor &color) const;
    void writeCellXfs(QXmlStreamWriter &writer) const;
    void writeDxfs(QXmlStreamWriter &writer) const;
    void writeDxf(QXmlStreamWriter &writer, const Format &format) const;
    void writeColors(QXmlStreamWriter &writer) const;

    bool readNumFmts(QXmlStreamReader &reader);
    bool readFonts(QXmlStreamReader &reader);
    bool readFont(QXmlStreamReader &reader, Format &format);
    bool readFills(QXmlStreamReader &reader);
    bool readFill(QXmlStreamReader &reader, Format &format);
    bool readBorders(QXmlStreamReader &reader);
    bool readBorder(QXmlStreamReader &reader, Format &format);
    bool readSubBorder(QXmlStreamReader &reader, const QString &name, Format::BorderStyle &style, XlsxColor &color);
    bool readCellXfs(QXmlStreamReader &reader);
    bool readDxfs(QXmlStreamReader &reader);
    bool readDxf(QXmlStreamReader &reader);
    bool readColors(QXmlStreamReader &reader);
    bool readIndexedColors(QXmlStreamReader &reader);

    bool readCellStyleXfs(QXmlStreamReader &reader);

    QHash<QString, int> m_builtinNumFmtsHash;
    QMap<int, QSharedPointer<XlsxFormatNumberData> > m_customNumFmtIdMap;
    QHash<QString, QSharedPointer<XlsxFormatNumberData> > m_customNumFmtsHash;
    int m_nextCustomNumFmtId;
    QList<Format> m_fontsList;
    QList<Format> m_fillsList;
    QList<Format> m_bordersList;
    QHash<QByteArray, Format> m_fontsHash;
    QHash<QByteArray, Format> m_fillsHash;
    QHash<QByteArray, Format> m_bordersHash;

    QVector<QColor> m_indexedColors;
    bool m_isIndexedColorsDefault;

    QList<Format> m_xf_formatsList;
    QHash<QByteArray, Format> m_xf_formatsHash;

    QList<Format> m_dxf_formatsList;
    QHash<QByteArray, Format> m_dxf_formatsHash;

    bool m_emptyFormatAdded;
};

QT_END_NAMESPACE_XLSX

#endif // XLSXSTYLES_H
