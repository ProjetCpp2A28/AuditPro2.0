#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QAbstractTableModel>
#include <QSqlQueryModel>

class CustomTableModel
{
    Q_OBJECT
public:
    CustomTableModel(QObject *parent = nullptr);
    void updateData(const QString &searchText, const QString &selectedFeature);
private:
    QSqlQueryModel queryModel;

};

#endif // CUSTOMTABLEMODEL_H
