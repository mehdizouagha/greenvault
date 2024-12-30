#ifndef PERSONEL_H
#define PERSONEL_H

#include "qcombobox.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QDate>
#include <QRegularExpression>
#include <QMessageBox>
#include <QCompleter>
#include <QStringListModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QLineEdit>
class personel
{
    QString nom, prenom, poste, mail;
    int id, telephone;
    int salaire; // Assurez-vous que salaire est de type float
    QDate date;
    QString role;

public:
    // Constructeurs
    personel();
    personel(int id, QString nom, QString prenom, QDate date, QString poste, int salaire, QString mail, int telephone , QString role);
 personel(int id);

    // Getters
    QString getNom() { return nom; }
    QString getPrenom() { return prenom; }
    QString getPoste() { return poste; }
    QString getMail() { return mail; }
    int getID() { return id; }
    int getTelephone() { return telephone; }
    int getsalaire() { return salaire; } // Changez le type de retour en float
    QDate getDate() { return date; }
    QString getrole() { return role; }

    // Setters
    void setNom(QString n) { nom = n; }
    void setPrenom(QString p) { prenom = p; }
    void setPoste(QString po) { poste = po; }
    void setMail(QString m) { mail = m; }
    void setID(int id1) { id = id1; }
    void setTelephone(int telephone1) { telephone = telephone1; }
    void setsalaire(int salaire1) { salaire = salaire1; }// Changez le type de paramètre en float
    void setDate(QDate d) { date = d; }
    void setrole(QString r) { role = r; }

    bool exporterPDF(const QString& fileName, QSqlQueryModel* model);
    QSqlQueryModel* afficherTrieParID(bool ordreCroissant);
    QSqlQueryModel*   rechercher(const QString &searchValue);
    void setupSearch();

    QMap<QString, double> statistiquesPourcentageSalaire();
    QSqlQueryModel*   rechercher_sug(const QString &searchValue);

    bool validateString(const QString &input)
    {
        QRegularExpression re("^[a-zA-ZÀ-ÿ\\s]+$");
        return re.match(input).hasMatch();
    }

    // Méthodes
    bool ajouter();
    bool supprimer(int id);
    QSqlQueryModel* afficher();
     bool modifier(int id);
      bool supprimer(int id, const QString &attribut);
      QString getUserRole(const QString &email);
      void populateComboBoxP(QComboBox *comboBox);
      void populateComboBoxE(QComboBox *comboBox);
      bool affecter(const QString &nomE, const QString &nomP, const QDate &date);
      QSqlQueryModel* afficherAffectation();
      bool supprimeraffectation(QString const &nomE,QString const &nomP);


private:
       // Model to hold the database query results
};

#endif // PERSONEL_H
