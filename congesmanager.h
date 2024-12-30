#ifndef CONGESMANAGER_H
#define CONGESMANAGER_H

#include <QDate>
#include <QList>
#include <QMap>

class CongesManager
{
public:
    CongesManager() = default;

    // Ajouter un congé pour un employé entre deux dates
    void ajouterConge(int idEmploye, const QDate &dateDebut, const QDate &dateFin);

    // Obtenir la liste des congés pour un employé
    QList<QDate> getConges(int idEmploye) const;

    // Vérifier si un employé a un congé à une date donnée
    bool isCongeForDate(int idEmploye, const QDate &date) const;

    // Récupérer le type de congé d'un employé pour une date donnée
    QString getCongeForDate(int idEmploye, const QDate &date) const;

private:
    // Dictionnaire qui associe un identifiant d'employé à ses congés (sous forme de dates)
    QMap<int, QList<QDate>> conges;
};

#endif // CONGESMANAGER_H
