#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QString>  // Pour gérer les chaînes de caractères

namespace Ui {
class login;  // Déclaration de la classe générée par le fichier .ui
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);  // Constructeur
    ~login();  // Destructeur
    QString getemail();


private slots:
    void onLoginClicked();  // Slot qui sera appelé lors du clic sur le bouton de connexion


private:
    Ui::login *ui;  // Pointeur vers l'interface utilisateur générée par Qt Designer
};

#endif // LOGIN_H
