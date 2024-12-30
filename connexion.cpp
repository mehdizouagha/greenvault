#include "connexion.h"
//#include "personel.h"

#include <QSqlDatabase>
#include <QDebug>

Connection::Connection() {}

bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test = false;

    db.setDatabaseName("integration_projet"); // insérer le nom de la source de données ODBC
    db.setUserName("projet");    // insérer le nom de l'utilisateur
    db.setPassword("14445133");  // insérer le mot de passe de cet utilisateur

    if (db.open()) {
        test = true;
        qDebug() << "Connexion réussie à la base de données:" << db.databaseName();
    } else {
        qDebug() << "Échec de la connexion.";
    }

    return test;
}

void Connection::closeConnection()
{
    db.close();
}
