#include "login.h"
#include "ui_login.h"  // Inclure le fichier généré par Qt Designer pour l'interface
#include <QSqlQuery>
#include <QMessageBox>  // Pour afficher un message si les identifiants sont incorrects
#include "personel.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)  // Initialisation de l'interface générée
{
    ui->setupUi(this);  // Initialisation de l'interface

    // Connexion du signal du bouton "Connexion" au slot onLoginClicked
    connect(ui->pushButton, &QPushButton::clicked, this, &login::onLoginClicked);
}

login::~login()
{
    delete ui;  // Libération de l'objet ui à la destruction de la fenêtre
}

void login::onLoginClicked()
{

    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

    // Vérifier que les champs ne sont pas vides
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs !");
        return;
    }

    // Convertir le mot de passe en nombre
    bool ok;
    int numericPassword = password.toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Erreur", "Le mot de passe doit être un nombre valide !");
        return;
    }

    // Préparer la requête SQL
    QSqlQuery query;
    query.prepare("SELECT ID FROM PERSONELL WHERE MAIL = :mail AND ID = :id");
    query.bindValue(":mail", username);
    query.bindValue(":id", numericPassword);

    // Exécuter la requête
    if (query.exec()) {
        if (query.next()) {
            // Succès : Identifiants corrects
            accept();  // Fermer la fenêtre et valider la connexion
        } else {
            // Échec : Aucun résultat correspondant
            QMessageBox::warning(this, "Erreur", "Nom d'utilisateur ou mot de passe incorrect !");
        }
    } else {
        // Erreur SQL
        QMessageBox::critical(this, "Erreur", "Erreur SQL : " + query.lastError().text());
    }
}

QString login::getemail(){
   return ui->lineEditUsername->text();
}





























