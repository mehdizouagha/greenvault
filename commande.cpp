#include "commande.h"
#include <QDebug>
#include <QSqlError>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QFileInfo>
#include <QThread>
#include <QTextDocument>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
// Constructeurs
Commande::Commande() : IdC(0), QuantiteC(0), etat("") {}

Commande::Commande(int idc, QDate dateLiv, int quantite, QDate dateCmd, QString status)
    :IdC(idc) ,dateLivraison(dateLiv), QuantiteC(quantite), dateCommande(dateCmd), etat(status) {}

// Ajouter une commande
bool Commande::ajouter() {
    // Vérification des champs obligatoires
    if (dateCommande.isNull() || dateLivraison.isNull() || QuantiteC <= 0 || etat.isEmpty()) {
        qDebug() << "Erreur : Tous les champs doivent être remplis et la quantité doit être positive.";
        return false;
    }

    // Vérification que la date de commande n'est pas supérieure à la date de livraison
    if (dateCommande > dateLivraison) {
        qDebug() << "Erreur : La date de commande ne peut pas être supérieure à la date de livraison.";
        return false;
    }

    // Conversion des types si nécessaire
    QString quantite_string = QString::number(QuantiteC);

    // Préparation de la requête
    QSqlQuery query;
    query.prepare("INSERT INTO COMMANDE ( IDC, DATEC, QUANC, DATECL, ETAT) "
                  "VALUES (:IDC,:DATEC, :QUANC, :DATECL, :ETAT)");

    // Liaison des valeurs aux colonnes
    query.bindValue(":IDC", IdC);
    query.bindValue(":DATEC", dateCommande);  // Date de commande
    query.bindValue(":QUANC", quantite_string); // Quantité commandée
    query.bindValue(":DATECL", dateLivraison); // Date de livraison
    query.bindValue(":ETAT", etat);            // État de la commande

    // Exécution de la requête et vérification
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion de la commande :" << query.lastError().text();
        return false;
    }

    qDebug() << "Commande ajoutée avec succès.";
    return true;
}


// Afficher les commandes
QSqlQueryModel* Commande::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM COMMANDE ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDC"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATEC"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANC"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATECL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));

    return model;
}

// Supprimer une commande


// Modifier une commande
bool Commande::modifier(int id, QDate dateLiv, int quantite, QDate dateCmd, QString status) {


    // Conversion des types si nécessaire
    QString id_string = QString::number(id);
    QString quantite_string = QString::number(quantite);

    // Préparation de la requête SQL
    QSqlQuery query;
    query.prepare("UPDATE COMMANDE SET DATEC = :DATEC, QUANC = :QUANC, "
                  "DATECL = :DATECL, ETAT = :ETAT WHERE IDC = :IDC");

    // Liaison des valeurs aux paramètres
    query.bindValue(":IDC", id_string);
    query.bindValue(":DATEC", dateCmd); // La date de commande
    query.bindValue(":QUANC", quantite_string); // La quantité
    query.bindValue(":DATECL", dateLiv); // La date de livraison
    query.bindValue(":ETAT", status); // Le statut de la commande

    // Exécution de la requête SQL
    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour de la commande :" << query.lastError().text();
        return false;
    }

    qDebug() << "Commande modifiée avec succès.";
    return true;
}


QSqlQueryModel* Commande::trie(QString args)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query;

    QString baseQuery = "SELECT * FROM COMMANDE  ";

    if (args == "Date commande ascendant") {
        query = baseQuery + "ORDER BY DATEC ASC";
    }
    else if (args == "Date commande descandant") {
        query = baseQuery + "ORDER BY DATEC DESC";
    }
    else if (args == "Date de livraison ascendant") {
        query = baseQuery + "ORDER BY DATECL ASC";
    }
    else if (args == "Date de livraison descandant") {
        query = baseQuery + "ORDER BY DATECL DESC";
    }

    else {
        query = baseQuery;
    }

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDC"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATEC"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANC"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATECL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ETAT"));


    return model;
}
void enregistrerAnnulationDansFichier(int idCommande,  QString &dateCommande, int quantite,  QString &dateLivraison,  QString &etat) {
    QFile fichier("C:/Users/Asus/OneDrive - ESPRIT/Bureau/ProjectsWork/ProjectsWork/historique_annulations.csv");

    // Ouvrir le fichier en mode Append (ajout)
    if (!fichier.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur : impossible d'ouvrir le fichier historique_annulations.csv";
        return;
    }

    QTextStream out(&fichier);

    // Ajouter l'entête si le fichier est vide
    if (fichier.size() == 0) {
        out << "ID Commande,Date Commande,Quantite,Date Livraison,etat\n";
    }

    // Ajouter les données de suppression
    out << idCommande << ","
        << dateCommande << ","
        << quantite << ","
        << dateLivraison << ","
        << etat << ","

        << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << "\n";
    out.flush();

    fichier.close();
    qDebug() << "Commande annulée enregistrée dans historique_annulations.csv.";
    QThread::msleep(1000);
}
bool Commande::supprimer(int id) {
    QSqlQuery query;
    // QString id_string = QString::number(id);
    query.prepare("SELECT * FROM COMMANDE WHERE IDC = :idCommande");
    query.bindValue(":idCommande", id);

    if (query.exec() && query.next()) {
        QString dateCommande = query.value("DATEC").toString();
        int quantite = query.value("QUANC").toInt();
        QString dateLivraison = query.value("DATECL").toString();
        QString etat = query.value("ETAT").toString();

        // Enregistrer dans le fichier d'annulation
        enregistrerAnnulationDansFichier(id, dateCommande, quantite, dateLivraison, etat);
    } else {
        qDebug() << "Erreur : impossible de récupérer les informations de la commande :" << query.lastError().text();
        return false;
    }

    // Supprimer la commande
    QSqlQuery deleteQuery;
    QString id_string = QString::number(id);
    deleteQuery.prepare("DELETE FROM COMMANDE WHERE IDC = :idCommande");
    deleteQuery.bindValue(":idCommande", id_string);

    if (!deleteQuery.exec()) {
        qDebug() << "Erreur lors de la suppression de la commande :" << deleteQuery.lastError().text();
        return false;
    }

    qDebug() << "Commande supprimée avec succès.";
    return true;


    return query.exec();
}
double Commande::calculerPourcentageEfficacite(QString fileName) {
    int totalCommandes = 0;   // Nombre total de commandes livrées
    int commandesDansDelai = 0; // Nombre de commandes livrées dans les délais

    // Requête SQL pour récupérer toutes les commandes livrées
    QSqlQuery query;
    query.prepare("SELECT IDC, DATEC, DATECL, DATEMODIFICATION  FROM COMMANDE WHERE ETAT='livree'");

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des commandes livrees:" << query.lastError().text();
        return -1; // Si l'exécution échoue, on retourne -1
    }

    // Création du fichier HTML pour le bilan
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier bilan pour l'écriture.";
        return -1;
    }

    QTextStream out(&file);
    out << "<html><head><title>Bilan des Commandes Livrees dans les Delais</title></head><body>";
    out << "<h1>Bilan des Commandes Livrees dans les Delais</h1>";

    // Parcours de toutes les commandes livrees pour les comparer et ajouter des détails dans le fichier
    while (query.next()) {
        QDate dateCommande = query.value("DATEC").toDate(); // Date de commande
        QDate dateLivraison = query.value("DATECL").toDate(); // Date où le client attend sa commande
        QDate dateModification = query.value("DATEMODIFICATION").toDate(); // Date de modification de l'état (date où la commande a été marquée comme livrée)
        int idCommande = query.value("IDC").toInt(); // ID de la commande

        totalCommandes++; // Augmenter le nombre total de commandes livrées

        // Calculer la différence en jours entre la date de modification et la date de livraison
        int differenceEnJours = dateLivraison.daysTo(dateModification);

        // Vérifier si la commande a été livrée dans le délai de 3 jours
        bool dansDelai = (differenceEnJours >= 3); // Si la différence est de 3 jours ou moins
        if (dansDelai) {
            commandesDansDelai++;
        }

        // Ajouter les détails de la commande dans le fichier HTML
        QString dateGeneration = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        out << "<p><b>ID Commande:</b> " + QString::number(idCommande) +
                   " <b>Date de commande:</b> " + dateCommande.toString("yyyy-MM-dd") +
                   " <b>Date de livraison:</b> " + dateLivraison.toString("yyyy-MM-dd") +
                   " <b>Date de modification de l'état (Livrée):</b> " + dateModification.toString("yyyy-MM-dd") +
                   " <b>Date de génération:</b> " + dateGeneration +
                   " <b>Status:</b> " + (dansDelai ? "Livrée dans les délais" : "Livrée en retard") +
                   "</p>";
    }

    // Calculer le pourcentage après avoir parcouru toutes les commandes
    double pourcentage = 0.0;
    if (totalCommandes > 0) {
        pourcentage = (double(commandesDansDelai) / double(totalCommandes)) * 100;
    }

    // Ajouter le pourcentage d'efficacité global
    out << "<h2>Pourcentage dEfficacite : " + QString::number(pourcentage) + "%</h2>";

    out << "<p>Total des commandes livrees: " + QString::number(totalCommandes) + "</p>";
    out << "<p>Commandes livrées dans les delais: " + QString::number(commandesDansDelai) + "</p>";

    out << "</body></html>";

    file.close();

    qDebug() << "Bilan enregistré dans le fichier HTML.";
    return pourcentage;
}
