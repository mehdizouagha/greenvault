#include "congesmanager.h"

void CongesManager::ajouterConge(int idEmploye, const QDate &dateDebut, const QDate &dateFin)
{
    QDate currentDate = dateDebut;
    while (currentDate <= dateFin) {
        conges[idEmploye].append(currentDate);
        currentDate = currentDate.addDays(1);
    }
}

QList<QDate> CongesManager::getConges(int idEmploye) const
{
    return conges.value(idEmploye, QList<QDate>());
}

bool CongesManager::isCongeForDate(int idEmploye, const QDate &date) const
{
    return conges.contains(idEmploye) && conges[idEmploye].contains(date);
}

QString CongesManager::getCongeForDate(int idEmploye, const QDate &date) const
{
    if (isCongeForDate(idEmploye, date)) {
        return "Congé"; // You can replace this with the actual type of the leave if needed
    }
    return QString();  // Return empty string if no leave is found for the date
}
