#include "customtablemodel.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QObject>

CustomTableModel::CustomTableModel(QObject *parent)
 : QAbstractTableModel(parent)
{

}

void CustomTableModel::updateData(const QString &searchText, const QString &selectedFeature) {
    // Préparez la requête SQL en fonction des critères de recherche.
    QString queryStr = "SELECT * FROM RAPPORTS_AUDITS WHERE " + selectedFeature + " LIKE :searchText";
    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":searchText", "%" + searchText + "%");

    // Exécutez la requête SQL.
    if (query.exec()) {
        // Effacez les données existantes du modèle.
        queryModel.clear();

        // Configurez le modèle avec les résultats de la recherche.
        queryModel.setQuery(query);

        // Mettez à jour le modèle.
        this->beginResetModel();
        this->endResetModel();
    } else {
        QMessageBox::warning(this, "Invalid Input", "Erreur lors de l'exécution de la requête : ");


    }
}
