#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>

class Client {
private:
    int idcl;
    QString nomcl, prenomcl, emailcl, adressecl;
    int IDC;


public:
    Client() {}

    // Constructeurs
    Client(int idcl, QString nomcl, QString prenomcl, QString emailcl, QString adressecl);
    Client(int idcl);

    // Getters
    int getIdcl() const;
    QString getnomcl() const;
    QString getprenomcl() const;
    QString getemailcl() const;
    QString getadressecl() const;




    // Setters
    void setidcl(int id);
    void setnomcl(const QString& nom);
    void setprenomcl(const QString& prenom);
    void setemailcl(const QString& email);
    void setadressecl(const QString& adresse);




    // Méthodes
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool modifierClient(int idcl, const QString& nomcl, const QString& prenomcl, const QString& emailcl,
                        const QString& adressecl);
    QSqlQueryModel* trier(const QString& colonne, const QString& direction);
    QSqlQueryModel* rechercher(const QString& partialId);
    bool addToPasser(int idcl, int idc);

    bool existe(int idcl);
    bool mettreAJour();
};

#endif // CLIENT_H
