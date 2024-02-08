
#ifndef XLSXRELATIONSHIPS_H
#define XLSXRELATIONSHIPS_H



#include "xlsxglobal.h"

#include <QList>
#include <QString>
#include <QIODevice>

QT_BEGIN_NAMESPACE_XLSX

struct XlsxRelationship
{
    QString id;
    QString type;
    QString target;
    QString targetMode;
};

class  Relationships
{
public:
    Relationships();

    QList<XlsxRelationship> documentRelationships(const QString &relativeType) const;
    QList<XlsxRelationship> packageRelationships(const QString &relativeType) const;
    QList<XlsxRelationship> msPackageRelationships(const QString &relativeType) const;
    QList<XlsxRelationship> worksheetRelationships(const QString &relativeType) const;

    void addDocumentRelationship(const QString &relativeType, const QString &target);
    void addPackageRelationship(const QString &relativeType, const QString &target);
    void addMsPackageRelationship(const QString &relativeType, const QString &target);
    void addWorksheetRelationship(const QString &relativeType, const QString &target, const QString &targetMode=QString());

    void saveToXmlFile(QIODevice *device) const;
    QByteArray saveToXmlData() const;
    bool loadFromXmlFile(QIODevice *device);
    bool loadFromXmlData(const QByteArray &data);
    XlsxRelationship getRelationshipById(const QString &id) const;

    void clear();
    int count() const;
    bool isEmpty() const;

private:
    QList<XlsxRelationship> relationships(const QString &type) const;
    void addRelationship(const QString &type, const QString &target, const QString &targetMode=QString());

    QList<XlsxRelationship> m_relationships;
};

QT_END_NAMESPACE_XLSX

#endif // XLSXRELATIONSHIPS_H
