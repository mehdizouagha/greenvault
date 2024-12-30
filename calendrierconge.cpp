#include "calendrierconge.h"
#include "congesmanager.h"  // Inclure le fichier où la classe CongesManager est définie
#include "personel.h"  // Inclure le fichier où la classe Personnel est définie
#include <QDialog>
#include <QInputDialog>  // For input dialog to get the employee's ID
#include <QDateEdit>
#include <QMessageBox>  // Inclure pour afficher des messages d'information
#include <QSqlQuery>
#include <QSqlError>  // For better SQL error handling

CalendrierConge::CalendrierConge(QWidget *parent) :
    QWidget(parent),
    congesManager(new CongesManager)
{
    // Initialiser le calendrier
    calendar = new QCalendarWidget(this);
    calendar->setGridVisible(true);

    // QDateEdit pour sélectionner la date de début
    dateDebutEdit = new QDateEdit(this);
    dateDebutEdit->setCalendarPopup(true);  // Permet de sélectionner la date via un popup
    dateDebutEdit->setDate(QDate::currentDate());  // Définir la date par défaut sur la date actuelle

    // QDateEdit pour sélectionner la date de fin
    dateFinEdit = new QDateEdit(this);
    dateFinEdit->setCalendarPopup(true);
    dateFinEdit->setDate(QDate::currentDate());  // Définir la date par défaut sur la date actuelle

    // Ajouter un bouton pour ajouter un congé
    QPushButton *btnAjouterConge = new QPushButton("Ajouter Congé", this);
    connect(btnAjouterConge, &QPushButton::clicked, this, &CalendrierConge::ajouterConge);

    // Ajouter un bouton pour afficher les congés de l'employé
    QPushButton *btnAfficherConge = new QPushButton("Afficher Congé", this);
    connect(btnAfficherConge, &QPushButton::clicked, this, &CalendrierConge::afficherConge);

    // Ajouter un bouton pour fermer le calendrier
    QPushButton *btnFermer = new QPushButton("Fermer Calendrier", this);
    connect(btnFermer, &QPushButton::clicked, this, &CalendrierConge::fermerCalendrier);

    // Layout du widget
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(calendar);
    layout->addWidget(dateDebutEdit);  // Ajouter le widget de la date de début
    layout->addWidget(dateFinEdit);    // Ajouter le widget de la date de fin
    layout->addWidget(btnAjouterConge);
    layout->addWidget(btnAfficherConge);  // Ajouter le bouton d'affichage du congé
    layout->addWidget(btnFermer);
    setLayout(layout);
}

CalendrierConge::~CalendrierConge()
{
    delete congesManager;
}

void CalendrierConge::afficherConge()
{
    // Récupérer la date sélectionnée dans le calendrier
    QDate dateSelectionnee = calendar->selectedDate();

    // Demander l'ID de l'employé via QInputDialog (ou utilisez l'ID de l'utilisateur courant)
    bool ok;
    int idEmploye = QInputDialog::getInt(this, "ID Employé", "Entrez l'ID de l'employé:", 0, 0, 10000, 1, &ok);

    if (!ok) {
        // Si l'utilisateur annule l'entrée, ne pas procéder
        QMessageBox::information(this, "Entrée Annulée", "L'entrée a été annulée.");
        return;
    }

    // Vérifier si l'employé a un congé pour cette date
    QString conge = congesManager->getCongeForDate(idEmploye, dateSelectionnee);

    if (!conge.isEmpty()) {
        // Si un congé est trouvé, afficher un message
        QMessageBox::information(this, "Congé", "Le congé pris est : " + conge);
    } else {
        // Sinon, afficher qu'il n'y a pas de congé
        QMessageBox::information(this, "Congé", "Aucun congé enregistré pour cette date.");
    }
}


void CalendrierConge::fermerCalendrier()
{
    // Fermer la fenêtre du calendrier
    close();
}

void CalendrierConge::ajouterConge()
{
    // Demander l'ID de l'employé via QInputDialog
    bool ok;
    int idEmploye = QInputDialog::getInt(this, "ID Employé", "Entrez l'ID de l'employé:", 0, 0, 10000, 1, &ok);

    if (!ok) {
        // Si l'utilisateur annule l'entrée, ne pas procéder
        QMessageBox::information(this, "Entrée Annulée", "L'entrée a été annulée.");
        return;
    }

    // Vérifier si l'employé existe dans la base de données
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM PERSONELL WHERE ID = :ID");  // Note that the table name should be PERSONNEL
    query.bindValue(":ID", idEmploye);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la vérification de l'existence de l'employé: " + query.lastError().text());
        return;
    }

    query.next();
    int count = query.value(0).toInt();

    if (count == 0) {
        // Si l'employé n'existe pas
        QMessageBox::warning(this, "Erreur", "L'employé avec l'ID spécifié n'existe pas dans la base de données.");
        return;
    }

    // Récupérer les dates sélectionnées par l'utilisateur
    QDate dateDebut = dateDebutEdit->date();  // Récupérer la date de début
    QDate dateFin = dateFinEdit->date();      // Récupérer la date de fin

    // Ajouter le congé dans CongesManager
    congesManager->ajouterConge(idEmploye, dateDebut, dateFin);

    // Afficher un message pour confirmer l'ajout
    QMessageBox::information(this, "Ajouter Congé", "Congé ajouté pour l'employé.");
}
