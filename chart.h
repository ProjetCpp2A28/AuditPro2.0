#ifndef CHART_H
#define CHART_H

#include <QSqlDatabase>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include <QList>
#include <QMap>

class chart
{
public:
    chart();
    QStringList getnbrReclamations();
};

#endif // CHART_H
