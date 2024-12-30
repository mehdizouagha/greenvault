#include "client.h"
#include "qdatetime.h"
#include <QSqlError>
#include <QMessageBox>
#include <QString>
Client::Client(int idcl, QString nomcl, QString prenomcl, QString emailcl, QString adressecl) {
    this->idcl = idcl;
    this->nomcl = nomcl;
    this->prenomcl = prenomcl;
    this->emailcl = emailcl;
    this->adressecl = adressecl;





    // N'oubliez pas de définir idc ici
}
Client::Client(int idcl){
    this->idcl=idcl;
}
// Getter pour idcl
int Client::getIdcl() const {
    return idcl;
}

// Setter pour idcl
void Client::setidcl(int id) {
    idcl = id;
}

// Getter pour nomcl
QString Client::getnomcl() const {
    return nomcl;
}

// Setter pour nomcl
void Client::setnomcl(const QString& nom) {
    nomcl = nom;
}

// Getter pour prenomcl
QString Client::getprenomcl() const {
    return prenomcl;
}

// Setter pour prenomcl
void Client::setprenomcl(const QString& prenom) {
    prenomcl = prenom;
}

// Getter pour emailcl
QString Client::getemailcl() const {
    return emailcl;
}

// Setter pour emailcl
void Client::setemailcl(const QString& email) {
    emailcl = email;
}

// Getter pour adressecl
QString Client::getadressecl() const {
    return adressecl;
}

// Setter pour adressecl
void Client::setadressecl(const QString& adresse) {
    adressecl = adresse;
}







bool Client::ajouter() {
    // Débogage des données avant insertion
    qDebug() << "Tentative d'ajout :"
             << "IDCL =" << idcl
             << ", NOMCL =" << nomcl
             << ", PRENOMCL =" << prenomcl
             << ", EMAILCL =" << emailcl
             << ", ADRESSECL =" << adressecl;

    // Vérification si l'IDCL existe déjà dans la base
    QSqlQuery queryCheck;
    queryCheck.prepare("SELECT COUNT(*) FROM CLIENT WHERE IDCL = :idcl");
    queryCheck.bindValue(":idcl", idcl);

    if (!queryCheck.exec()) {
        qDebug() << "Erreur SQL lors de la vérification de l'IDCL :" << queryCheck.lastError().text();
        return false;
    }

    if (queryCheck.next() && queryCheck.value(0).toInt() > 0) {
        qDebug() << "Erreur : IDCL déjà existant.";
        QMessageBox::warning(nullptr, "Erreur", "L'ID client existe déjà dans la base.");
        return false;
    }

    // Préparation de la requête pour insérer les données dans CLIENT
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (IDCL, NOMCL, PRENOMCL, EMAILCL, ADRESSECL) "
                  "VALUES (:idcl, :nomcl, :prenomcl, :emailcl, :adressecl)");
    query.bindValue(":idcl", idcl);
    query.bindValue(":nomcl", nomcl);
    query.bindValue(":prenomcl", prenomcl);
    query.bindValue(":emailcl", emailcl);
    query.bindValue(":adressecl", adressecl);

    // Exécution de la requête et gestion des erreurs
    if (!query.exec()) {
        qDebug() << "Erreur SQL lors de l'ajout du client :" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de l'ajout du client. Vérifiez les données.");
        return false;
    }

    // Ajout réussi
    qDebug() << "Ajout du client réussi.";
    return true;
}


// Vérifie si un client existe dans la table CLIENT
bool Client::existe(int idcl) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CLIENT WHERE ID = :idcl");
    query.bindValue(":idcl", idcl);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0; // Retourne true si le client existe
    }
    return false;
}

// Ajoute une association dans la table PASSER
bool Client::addToPasser(int idcl, int idc) {
    QSqlQuery query;
    query.prepare("INSERT INTO PASSER (idc, idcl, datecl) VALUES (:idc, :idcl, :datecl)");
    query.bindValue(":idc", idc);
    query.bindValue(":idcl", idcl);
    query.bindValue(":datecl", QDate::currentDate().toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout dans PASSER :" << query.lastError().text();
        return false;
    }
    return true;
}










































/*
bool Client::ajouter()
{
    QSqlQuery query;

    // Préparer la requête d'insertion
    query.prepare("INSERT INTO CLIENT (IDCL, NOMCL, PRENOMCL, EMAILCL, ADRESSECL, HISTOCL, IDC, DATECL) "
                  "VALUES (:IDCL, :NOMCL, :PRENOMCL, :EMAILCL, :ADRESSECL, :HISTOCL, :IDC, SYSDATE)");

    query.bindValue(":IDCL", idcl);
    query.bindValue(":NOMCL", nomcl);
    query.bindValue(":PRENOMCL", prenomcl);
    query.bindValue(":EMAILCL", emailcl);
    query.bindValue(":ADRESSECL", adressecl);
    query.bindValue(":HISTOCL", histocl);
    query.bindValue(":IDC", IDC);


    // Exécuter la requête
    if (query.exec()) {
        qDebug() << "Client ajouté avec succès.";
        return true;
    } else {
        qDebug() << "Erreur lors de l'ajout du client : " << query.lastError().text();
        return false;
    }
}


*/











/*

bool Client::ajouter() {
    QSqlQuery query;

    // Préparation de la requête SQL
    query.prepare("INSERT INTO CLIENT (IDCL, NOMCL, PRENOMCL, EMAILCL, ADRESSECL, HISTOCL, IDC) "
                  "VALUES (:IDCL, :NOMCL, :PRENOMCL, :EMAILCL, :ADRESSECL, :HISTOCL, :IDC)");

    // Lier les valeurs
    query.bindValue(":IDCL", QString::number(idcl));
    query.bindValue(":NOMCL", nomcl);
    query.bindValue(":PRENOMCL", prenomcl);  // Corrected typo here
    query.bindValue(":EMAILCL", emailcl);
    query.bindValue(":ADRESSECL", adressecl);
    query.bindValue(":HISTOCL", histocl);
    query.bindValue(":IDC", QString::number(IDC));

    // Exécution de la requête
    if (query.exec()) {
        qDebug() << "Client ajouté avec succès";
        return true;
    } else {
        qDebug() << "Erreur lors de l'ajout du client : " << query.lastError().text();
        return false;
    }
}

*/
bool Client::supprimer(int idcl)
{
    QSqlQuery query;
    QString res=QString::number(idcl);
    query.prepare("delete from client where IDCL= :idcl");
    query.bindValue(":idcl",res);
    return query.exec();
}
QSqlQueryModel * Client::afficher()
{

    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("idcl"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nomcl"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenomcl"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("emailcl"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("adressecl"));


    return model;
}


/*bool Client::modifierClient(int idcl, QString nomcl, QString prenomcl, QString emailcl, QString adressecl, QString histocl, int IDC)
{
    QSqlQuery query;

    // Préparation de la requête SQL pour mettre à jour le client
    query.prepare("UPDATE CLIENT SET "
                  "NOMCL = :nomcl, "
                  "PRENOMCL= :prenomcl, "
                  "EMAILCL = :emailcl, "
                  "ADRESSECL = :adressecl, "
                  "HISTOCL = :histocl, "
                  "IDC = :IDC "
                  "WHERE IDCL = :idcl");


    // Liaison des nouvelles valeurs
    query.bindValue(":idcl", idcl);
    query.bindValue(":nomcl", nomcl);
    query.bindValue(":prenomcl", prenomcl);
    query.bindValue(":emailcl", emailcl);
    query.bindValue(":adressecl", adressecl);
    query.bindValue(":histocl", histocl);
    query.bindValue(":IDC", IDC);

    // Exécution de la requête SQL
    if (query.exec()) {
        // Utilisation des setters pour mettre à jour l'état interne de l'objet
        setidcl(idcl);                 // Met à jour l'ID du client
        setnomcl(nomcl);               // Met à jour le nom du client
        setprenomcl(prenomcl);         // Met à jour le prénom du client
        setemailcl(emailcl);           // Met à jour l'email du client
        setadressecl(adressecl);       // Met à jour l'adresse du client
        sethistocl(histocl);           // Met à jour l'historique d'achat du client
        setIDC(IDC);                   // Met à jour l'IDC du client
        return true;                   // Indique que la mise à jour a réussi
    }

    return false; // Indique que la mise à jour a échoué
}

*/
bool Client::modifierClient(int idcl, const QString& nomcl, const QString& prenomcl, const QString& emailcl,
                            const QString& adressecl) {
    QSqlQuery query;
    QString queryString = "UPDATE CLIENT SET ";

    bool firstUpdate = true;

    if (!nomcl.isEmpty()) {
        queryString += (firstUpdate ? "" : ", ") + QString("NOMCL = :nomcl");
        firstUpdate = false;
    }
    if (!prenomcl.isEmpty()) {
        queryString += (firstUpdate ? "" : ", ") + QString("PRENOMCL = :prenomcl");
        firstUpdate = false;
    }
    if (!emailcl.isEmpty()) {
        queryString += (firstUpdate ? "" : ", ") + QString("EMAILCL = :emailcl");
        firstUpdate = false;
    }
    if (!adressecl.isEmpty()) {
        queryString += (firstUpdate ? "" : ", ") + QString("ADRESSECL = :adressecl");
        firstUpdate = false;
    }




    queryString += " WHERE IDCL = :idcl";
    query.prepare(queryString);
    query.bindValue(":idcl",idcl);

    if (!nomcl.isEmpty()) query.bindValue(":nomcl", nomcl);
    if (!prenomcl.isEmpty()) query.bindValue(":prenomcl", prenomcl);
    if (!emailcl.isEmpty()) query.bindValue(":emailcl", emailcl);
    if (!adressecl.isEmpty()) query.bindValue(":adressecl", adressecl);



    if (query.exec()) {
        if (!nomcl.isEmpty()) setnomcl(nomcl);
        if (!prenomcl.isEmpty()) setprenomcl(prenomcl);
        if (!emailcl.isEmpty()) setemailcl(emailcl);
        if (!adressecl.isEmpty()) setadressecl(adressecl);



        return true;
    }

    qDebug() << "Erreur lors de la mise à jour : " << query.lastError().text();
    return false;
}

/*
QSqlQueryModel* Client::trier(const QString& colonne, const QString& direction) {
    QSqlQuery query;

    // Construire la requête SQL avec une jointure
    QString queryString =
        "SELECT CLIENT.IDCL, CLIENT.NOMCL, CLIENT.PRENOMCL, CLIENT.EMAILCL, CLIENT.ADRESSECL, "
        "PASSER.DATECL "
        "FROM CLIENT "
        "LEFT JOIN PASSER ON CLIENT.IDCL = PASSER.IDCL " // Jointure entre CLIENT et PASSER
        "ORDER BY " + colonne + " " + direction;

    query.prepare(queryString);

    // Exécuter la requête
    if (!query.exec()) {
        qDebug() << "Erreur de la requête SQL : " << query.lastError().text();
        return nullptr;  // En cas d'erreur, renvoyer nullptr
    }

    // Créer un modèle pour afficher les données
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);

    // Vérifiez si les résultats de la requête ont été chargés correctement
    if (model->rowCount() == 0) {
        qDebug() << "Aucun résultat trouvé.";
    }

    // Définir les en-têtes des colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDCL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMCL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOMCL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAILCL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSECL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATECL"));

    return model;
}
*/



QSqlQueryModel* Client::trier(const QString& colonne, const QString& direction) {
    QSqlQuery query;

    // Construire la requête SQL avec une jointure
    QString queryString =
        "SELECT CLIENT.IDCL, CLIENT.NOMCL, PASSER.DATECL "
        "FROM CLIENT "
        "INNER JOIN PASSER ON CLIENT.IDCL = PASSER.IDCL " // Jointure entre CLIENT et PASSER
        "ORDER BY " + colonne + " " + direction;

    query.prepare(queryString);

    // Exécuter la requête
    if (!query.exec()) {
        qDebug() << "Erreur de la requête SQL : " << query.lastError().text();
        return nullptr;  // En cas d'erreur, renvoyer nullptr
    }

    // Créer un modèle pour afficher les données
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);

    // Vérifiez si les résultats de la requête ont été chargés correctement
    if (model->rowCount() == 0) {
        qDebug() << "Aucun résultat trouvé.";
    }

    // Définir les en-têtes des colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDCL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMCL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATECL"));

    return model;
}





















QSqlQueryModel* Client::rechercher(const QString &partialSearch) {
    QSqlQuery query;

    // Préparer la requête SQL pour rechercher à la fois par IDCL et NOMCL
    query.prepare("SELECT * FROM CLIENT WHERE IDCL LIKE :partialSearch OR NOMCL LIKE :partialSearch");

    // Lier la valeur du paramètre :partialSearch à la recherche partielle
    query.bindValue(":partialSearch", partialSearch + "%");  // Ajout du caractère '%' pour rechercher par début

    // Exécuter la requête
    if (!query.exec()) {
        qDebug() << "Recherche échouée, erreur SQL : " << query.lastError().text();
        return nullptr;  // En cas d'échec de la requête, retourner nullptr
    }

    // Créer et remplir le modèle avec les résultats de la requête
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);  // Pas besoin de std::move ici

    // Définir les en-têtes des colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDCL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMCL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOMCL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAILCL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSECL"));

    //model->setHeaderData(5, Qt::Horizontal, QObject::tr("IDC"));

    // Retourner le modèle
    return model;
}




bool Client::mettreAJour() {
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET nom = :nom, prenom = :prenom, adresse = :adresse WHERE email = :email");
    query.bindValue(":nom", this->nomcl);
    query.bindValue(":prenom", this->prenomcl);
    query.bindValue(":adresse", this->adressecl);

    query.bindValue(":email", this->emailcl);

    return query.exec(); // Retourne true si la mise à jour est réussie
}
