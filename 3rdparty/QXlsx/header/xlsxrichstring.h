
#ifndef XLSXRICHSTRING_H
#define XLSXRICHSTRING_H

#include "xlsxglobal.h"
#include "xlsxformat.h"
#include <QVariant>
#include <QStringList>
#include <QSharedDataPointer>

QT_BEGIN_NAMESPACE_XLSX
class RichStringPrivate;
class RichString;
// qHash is a friend, but we can't use default arguments for friends (§8.3.6.4)
  uint qHash(const RichString &rs, uint seed = 0) Q_DECL_NOTHROW;

class QXLSX_EXPORT RichString
{
public:
    RichString();
    explicit RichString(const QString& text);
    RichString(const RichString &other);
    ~RichString();

    bool isRichString() const;
    bool isNull() const;
    bool isEmtpy() const;
    QString toPlainString() const;
    QString toHtml() const;
    void setHtml(const QString &text);

    int fragmentCount() const;
    void addFragment(const QString &text, const Format &format);
    QString fragmentText(int index) const;
    Format fragmentFormat(int index) const;

    operator QVariant() const;

    RichString &operator=(const RichString &other);
private:
    friend   uint qHash(const RichString &rs, uint seed) Q_DECL_NOTHROW;
    friend   bool operator==(const RichString &rs1, const RichString &rs2);
    friend   bool operator!=(const RichString &rs1, const RichString &rs2);
    friend   bool operator<(const RichString &rs1, const RichString &rs2);
    friend   QDebug operator<<(QDebug dbg, const RichString &rs);

    QSharedDataPointer<RichStringPrivate> d;
};

  bool operator==(const RichString &rs1, const RichString &rs2);
  bool operator!=(const RichString &rs1, const RichString &rs2);
  bool operator<(const RichString &rs1, const RichString &rs2);
  bool operator==(const RichString &rs1, const QString &rs2);
  bool operator==(const QString &rs1, const RichString &rs2);
  bool operator!=(const RichString &rs1, const QString &rs2);
  bool operator!=(const QString &rs1, const RichString &rs2);

#ifndef QT_NO_DEBUG_STREAM
  QDebug operator<<(QDebug dbg, const RichString &rs);
#endif

QT_END_NAMESPACE_XLSX

Q_DECLARE_METATYPE(QXlsx::RichString)

#endif // XLSXRICHSTRING_H
