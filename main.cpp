#include "login.h"
#include "secondwindow.h"  // Assurez-vous que SecondWindow est correctement importé
#include "connexion.h"     // Pour la gestion de la connexion à la base de données
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    Connection c;
    bool test = c.createconnection();  // Crée la connexion à la base de données

    // Crée une fenêtre de connexion modale
    login loginWindow;

    // Utilise exec() pour rendre la fenêtre modale
    if (loginWindow.exec() == QDialog::Accepted) {
        // Si l'utilisateur se connecte avec succès, établir la connexion à la base de données

        // Vérifie si la connexion est réussie
        if (test) {
            QString email = loginWindow.getemail();
            qDebug() << "email:" << email;
            MainWindow w(email);

            // Affiche la fenêtre principale
            w.show();

            // Affiche un message de succès de connexion
            QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                     QObject::tr("Connection successful.\nClick OK to continue."),
                                     QMessageBox::Ok);

            // Lancer la boucle principale de l'application pour la fenêtre principale
            return a.exec();  // Démarre la boucle principale de l'application
        } else {
            // En cas d'échec de la connexion à la base de données
            QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                                  QObject::tr("Connection failed.\nPlease check your connection and try again."),
                                  QMessageBox::Ok);
        }
    }

    // Si l'utilisateur annule la connexion ou autre, quitter l'application
    return 0;
}
