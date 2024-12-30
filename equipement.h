#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlQueryModel>
#include<QDate>
#include<QRegularExpression>
#include<QSqlTableModel>
#include "QrCodeGenerator.h"
#include <QImage>
#include <QPainter>
#include <QString>
#include <QProcess>
#include <QDebug>
#include <QtCore>
#include <QtSql>
#include <iostream>
#include <fstream>
#include <filesystem>
//#include<QNetworkRequest>
//#include<QNetworkAccessManager>
//#include <QNetworkReply>
#include <QUrl>
#include<QWidget>
#include <QByteArray>
#include <QProcess>
#include <QDebug>
#include <QString>

namespace fs = std::filesystem;

class equipement
{
private:
    int id_eq;
    QString nom_e, categorie_e, etat_e;
    QDate Date_aq_e,Date_D_e,Date_P_e;
    QString fournisseur_e,localisation_e;
    double prix_e;
    QString parametre_M_e;

public:
    int getid(){return id_eq;}
    int setid(int id)
    {
        id_eq=id;
        return id_eq;
    }

    QString setnom(QString nom)
    {
        nom_e=nom;
        return nom_e;
    }
    QString setcategorie(QString categorie)
    {
        categorie_e=categorie;
        return categorie_e;
    }
    QString setetat(QString etat)
    {
        etat_e=etat;
        return etat_e;
    }
    QString setfournisseur(QString fournisseur)
    {
        fournisseur_e=fournisseur;
        return fournisseur_e;
    }
    QString setlocalisation(QString localisation)
    {
        localisation_e=localisation;
        return localisation_e;
    }
    QString setparametre(QString parametre)
    {
        parametre_M_e=parametre;
        return parametre_M_e;
    }
    double setprix(double prix){
        prix_e=prix;
        return prix_e;
    }
    QDate setdated(QDate dated){
        Date_D_e=dated;
        return dated;
    }
    QDate setdatep(QDate datep){
        Date_P_e=datep;
        return Date_P_e;
    }
    QDate setdatea(QDate datea){
        Date_aq_e=datea;
        return Date_aq_e;
    }
    equipement();
    equipement(int id,QString nom,QString categorie,QString etat,QString fournisseur,QString localisation,QString parametre,QDate dated,QDate datep,QDate dateaq,double p);
    bool ajouter();

    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool modifier(int id);
    QSqlQueryModel* rechercher(const QString& partialId);
    QSqlQueryModel* trier(const QString& methode, bool descending);
    QSqlTableModel* getTableModel(QObject *parent);
    QImage generateQRCode(const QString &data, const quint16 size =1000, const quint16 borderSize = 1,
                          qrcodegen::QrCode::Ecc errorCorrection = qrcodegen::QrCode::Ecc::HIGH);
    QImage generateQRCodeForId(const int  &id);
    QSqlQueryModel* rechercherpanom(const QString &nom);
    //void generateTextFileFromQRCode(int equipmentId);
    QString diagnostic(int id) ;
    QString reparation(int id);
    //void predictEquipmentIssue(float temperature, int operating_hours, const QString &error_code);
    void populateComboBoxE(QComboBox *comboBox);
    void populateComboBoxP(QComboBox *comboBox);
    bool affecter(const QString &nomE, const QString &nomP, const QDate &date);
    QSqlQueryModel* afficherAffectation();
    bool supprimeraffectation(QString const &nomE,QString const &nomP);
};






#endif // EQUIPEMENT_H
