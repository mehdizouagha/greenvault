#ifndef COMMANDE_H
#define COMMANDE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Commande
{
private:
    int IdC;
    QDate dateLivraison;
    int QuantiteC;
    QDate dateCommande;
    QString etat;

public:
    // Constructeurs
    Commande();
    Commande(int, QDate, int, QDate, QString);

    // Getters
    int getIdC() { return IdC; }
    QDate getDateLivraison() { return dateLivraison; }
    int getQuantiteC() { return QuantiteC; }
    QDate getDateCommande() { return dateCommande; }
    QString getEtat() { return etat; }

    // Setters
    void setIdC(int id) { IdC = id; }
    void setDateLivraison(QDate date) { dateLivraison = date; }
    void setQuantiteC(int quantite) { QuantiteC = quantite; }
    void setDateCommande(QDate date) { dateCommande = date; }
    void setEtat(QString status) { etat = status; }

    // Méthodes
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool modifier(int, QDate, int, QDate, QString);
    QSqlQueryModel*  trie(QString args);
    double calculerPourcentageEfficacite(QString fileName);
    void modifierEtatCommande(int idCommande, const QString& nouvelEtat);
};

#endif // COMMANDE_H
