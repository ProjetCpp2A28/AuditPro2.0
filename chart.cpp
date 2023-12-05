#include "chart.h"

chart::chart()
{

}

QStringList chart::getnbrReclamations(){
    QSqlQuery query;
    QList<QString> nbreclams;

    if (!query.exec("SELECT NBR_RECLAMATIONS FROM RECLAMATION")) {
        qDebug() << "Error executing query:" << query.lastError().text();
        // handle the error
    }

    while (query.next()) {
        QString nbr = query.value(0).toString();
        nbreclams.append(nbr);
    }
    QStringList nbreclamssStringList(nbreclams);
    for (const QString &nbr : nbreclamssStringList) {
        qDebug() << "nbr: " << nbr;
    }
    return nbreclamssStringList;

}
