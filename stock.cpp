#include "stock.h"

#include "stock.h"
#include "qsqlquery.h"
#include <QDate>
#include <QDebug>
#include <QRegularExpression>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QImage>
#include <QLabel>

#include <QVariant>
#include <QPainter>
#include <QPixmap>
#include <QFile>

stock::stock(int IDS, int QUANTS, QString NOMS, QString CATEGORIE,
             QString FOURNIS, QString CONDS, QDate DATES, QDate DATEAS, int idStock ,QString IMAGE) {

    this->IDS = IDS;
    this->QUANTS = QUANTS;
    this->NOMS = NOMS;
    this->CATEGORIE = CATEGORIE;
    this->FOURNIS = FOURNIS;
    this->CONDS = CONDS;
    this->DATES = DATES;
    this->DATEAS = DATEAS;
    this->idStock = idStock;
     this->IMAGE = IMAGE;

}

// Méthode pour ajouter un enregistrement dans la base de données
    bool stock::ajouter() {


        QSqlQuery query;

        if (!estValide(NOMS) || !estValide(CATEGORIE) || !estValide(FOURNIS) || !estValide(CONDS)) {
            QMessageBox::warning(nullptr, "Erreur de saisie", "Les champs doivent contenir uniquement des lettres alphabétiques.");
                 return false;
         }



        query.prepare("insert into STOCK (IDS, NOMS,  CATEGORIE, QUANTS, FOURNIS, CONDS,DATES, DATEAS,IMAGE) "
                      "values (:IDS, :NOMS, :CATEGORIE, :QUANTS, :FOURNIS, :CONDS, :DATES, :DATEAS, :IMAGE)");

        query.bindValue(":IDS",QString::number(IDS));
        query.bindValue(":NOMS", NOMS);

        query.bindValue(":CATEGORIE",CATEGORIE );
         query.bindValue(":QUANTS",QString::number(QUANTS));
        query.bindValue(":FOURNIS", FOURNIS);

        query.bindValue(":CONDS",CONDS);
        query.bindValue(":DATES",DATES);
        query.bindValue(":DATEAS", DATEAS);
        query.bindValue(":IMAGE", IMAGE);

        return query.exec(); // Exécute la requête et retourne le résultat

        if(query.exec()) {
            qDebug()<<"stock ajouté";
            return true;


        }
        else{
            qDebug()<<"stock n'est pas ajouté";
            return false;

        }


    };


    bool stock::estValide(const QString& str) {

        QRegularExpression static const regex("^[A-Za-zÀ-ÿ]+$"); // Inclut les lettres accentuées
        return regex.match(str).hasMatch();
    }




    bool stock::supprimer(int IDS){

    QSqlQuery query;
    QString res=QString::number(IDS);

    query.prepare("Delete from STOCK where IDS= :IDS");
    query.bindValue(":IDS", res);

    return query.exec();


    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression :" << query.lastError().text(); // Afficher l'erreur
        return false; // Retourner false en cas d'erreur
    }
    else{
        qDebug()<<"pas 'erreur";
         return true;
    }







   }


    QSqlQueryModel *stock::afficher()
    {
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select * from STOCK");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDS"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOMS"));
    model->setHeaderData (2,Qt::Horizontal, QObject::tr("CATEGORIE"));
    model->setHeaderData (3,Qt::Horizontal, QObject::tr("QUANTS"));
    model->setHeaderData (4,Qt::Horizontal, QObject::tr("FOURNIS"));
    model->setHeaderData (5,Qt::Horizontal, QObject::tr("DATEAS"));
    model->setHeaderData (6,Qt::Horizontal, QObject::tr("DATES"));

    return model;
    }


    QSqlQueryModel* stock::rechercher(const QString& text) {
        QSqlQuery query;

        // Préparer la requête pour rechercher par texte dans plusieurs colonnes
        query.prepare(" SELECT * FROM STOCK  WHERE TO_CHAR(IDS) LIKE :text or CATEGORIE  LIKE :text or NOMS  LIKE :text ");


        // Lier la valeur de recherche avec le joker pour correspondre partiellement
        query.bindValue(":text", text + "%");

        // Exécuter la requête
        if (!query.exec()) {
            qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
            return nullptr;
        }

        // Créer un modèle QSqlQueryModel
        QSqlQueryModel* model = new QSqlQueryModel();
            model->setQuery(std::move(query));

        // Définir les en-têtes des colonnes
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDS"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMS"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("CATEGORIE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTS"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("FOURNIS"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATES"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATEAS"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("CONDS"));

        return model;
    }












    bool stock::modifier(const QString& NOMS, const QString& FOURNIS,
                         const QString& CATEGORIE, int QUANTS,
                         const QDate& DATES, const QDate& DATEAS,
                         int idStock, const QString& CONDS) {
        // Vérifier que l'idStock est valide (non nul ou négatif)
        if (idStock <= 0) {
            qDebug() << "idStock non valide.";
            return false;
        }

        // Step 1: Retrieve existing values from the database
        QSqlQuery existingQuery;
        existingQuery.prepare("SELECT NOMS, FOURNIS, CATEGORIE, QUANTS, DATES, DATEAS, CONDS FROM STOCK WHERE \"IDS\" = :IDS");
        existingQuery.bindValue(":IDS", idStock);

        if (!existingQuery.exec() || !existingQuery.next()) {
            qDebug() << "Échec de la récupération des valeurs existantes :" << existingQuery.lastError().text();
            return false;
        }

        // Step 2: Store existing values
        QString currentNoms = existingQuery.value("NOMS").toString();
        QString currentFournis = existingQuery.value("FOURNIS").toString();
        QString currentCategorie = existingQuery.value("CATEGORIE").toString();
        int currentQuants = existingQuery.value("QUANTS").toInt();
        QDate currentDates = existingQuery.value("DATES").toDate();
        QDate currentDateas = existingQuery.value("DATEAS").toDate();
        QString currentConds = existingQuery.value("CONDS").toString();

        // Step 3: Prepare to construct the update query
        QStringList updateFields;

        // Dynamically construct the fields to be updated
        if (!NOMS.isEmpty()) {
            updateFields << "NOMS = :NOMS";
            currentNoms = NOMS; // Update to new value
        }

        if (!FOURNIS.isEmpty()) {
            updateFields << "FOURNIS = :FOURNIS";
            currentFournis = FOURNIS; // Update to new value
        }

        if (!CATEGORIE.isEmpty()) {
            updateFields << "CATEGORIE = :CATEGORIE";
            currentCategorie = CATEGORIE; // Update to new value
        }

        if (QUANTS >= 0) {
            updateFields << "QUANTS = :QUANTS";
            currentQuants = QUANTS; // Update to new value
        }

        if (DATES.isValid()) {
            updateFields << "DATES = :DATES";
            currentDates = DATES; // Update to new value
        }

        if (DATEAS.isValid()) {
            updateFields << "DATEAS = :DATEAS";
            currentDateas = DATEAS; // Update to new value
        }

        if (!CONDS.isEmpty()) {
            updateFields << "CONDS = :CONDS";
            currentConds = CONDS; // Update to new value
        }

       // Check if there are fields to update
       if (updateFields.isEmpty()) {
           qDebug() << "Aucun champ à mettre à jour.";
           return false; // Nothing to update
       }

       // Construct the update query
       QString queryString = "UPDATE STOCK SET " + updateFields.join(", ") + " WHERE \"IDS\" = :IDS";

       // Prepare the query
       QSqlQuery query;
       query.prepare(queryString);

       // Bind values for all fields that may have changed or need to be kept
       if (!NOMS.isEmpty()) query.bindValue(":NOMS", currentNoms);
       if (!FOURNIS.isEmpty()) query.bindValue(":FOURNIS", currentFournis);
       if (!CATEGORIE.isEmpty()) query.bindValue(":CATEGORIE", currentCategorie);
       if (QUANTS >= 0) query.bindValue(":QUANTS", currentQuants);
       if (DATES.isValid()) query.bindValue(":DATES", currentDates);
       if (DATEAS.isValid()) query.bindValue(":DATEAS", currentDateas);
       if (!CONDS.isEmpty()) query.bindValue(":CONDS", currentConds);

       // Bind the idStock value from the parameter correctly
       query.bindValue(":IDS", idStock);

       // Execute the query and check for success
       if (!query.exec()) {
           qDebug() << "Échec de la mise à jour du stock :" << query.lastError().text();
           return false;
       }

       qDebug() << "Mise à jour réussie";
       return true;
    }








   QSqlQueryModel* stock::trier(const QString& methode) {
       QSqlQuery query;


       QString queryString = "SELECT *FROM STOCK";
       if (methode == "NOMS en ordre ascendant") {
             queryString += " ORDER BY NOMS ASC";
         } else if (methode == "NOMS en ordre descendant") {
             queryString += " ORDER BY NOMS DESC";

         } else if (methode == "DATEAS en ordre ascendant") {
             queryString += " ORDER BY DATEAS ASC";
         } else if (methode == "DATEAS en ordre descendant") {
             queryString += " ORDER BY DATEAS DESC";

         } else if (methode == "DATES en ordre ascendant") {
             queryString += " ORDER BY DATES ASC";
         } else if (methode == "DATES en ordre descendant") {
             queryString += " ORDER BY DATES DESC";
         }



       query.exec(queryString);


       QSqlQueryModel* model = new QSqlQueryModel();
       model->setQuery(std::move(query));

       model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMS"));
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("DATEAS"));
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("DATES"));


       return model;
   }

