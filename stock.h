#ifndef STOCK_H
#define STOCK_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlError>


class stock {
private:
    QString NOMS;        // Name of the stock item
    int IDS;             // Identifier for the stock item
    QString CATEGORIE;   // Category of the stock item
    int QUANTS;          // Quantity available
    QString FOURNIS;     // Supplier information
    QString CONDS;       // Conditions related to the stock item
    QDate DATES;         // Date of entry or relevant date
    QDate DATEAS;        // Date of availability or other relevant date
    int idStock;         // Stock ID
    QString IMAGE;
    int etat;
    float poids;
public:
    // Default constructor
    stock() {}

    // Parameterized constructor
    stock(int IDS, int QUANTS, QString NOMS, QString CATEGORIE,
          QString FOURNIS, QString CONDS, QDate DATES, QDate DATEAS, int idStock,QString IMAGE);


    // Getters
    QString getNOMS() const { return NOMS; }
    int getIDS() const { return IDS; }
    QString getCATEGORIE() const { return CATEGORIE; }
    int getQUANTS() const { return QUANTS; }
    QString getFOURNIS() const { return FOURNIS; }
    QString getCONDS() const { return CONDS; }
    QDate getDATES() const { return DATES; }       // Getter for DATES
    QDate getDATEAS() const { return DATEAS; }     // Getter for DATEAS
    int getidStock() const {return idStock;}
     QString getIMAGE() const { return IMAGE; }

    // Setters
    void setNOMS(const QString& n) { NOMS = n; }
    void setIDS(int ids) { IDS = ids; }
    void setCATEGORIE(const QString& c) { CATEGORIE = c; }
    void setQUANTS(int q) { QUANTS = q; }
    void setFOURNIS(const QString& f) { FOURNIS = f; }
    void setCONDS(const QString& c) { CONDS = c; }
    void setDATES(const QDate& d1) { DATES = d1; }           // Setter for DATES
    void setDATEAS(const QDate& d) { DATEAS = d; }           // Setter for DATEAS
    void setidStock(int idS) { idStock = idS; }
    void setIMAGE(const QString& i) { IMAGE = i; }

    bool idExists(QString id);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int IDS);
    bool rechercher(int idStock);
    bool modifier(const QString& NOMS, const QString& FOURNIS,
                  const QString& CATEGORIE, int QUANTS,
                  const QDate& DATES, const QDate& DATEAS,
                  int idStock, const QString& CONDS);
    bool estValide(const QString& str);
 QSqlQueryModel* rechercher(const QString& recherche);
 class QLabel;
bool afficherQRCode(int id);
  QMap<QString, double> calculStat();
   QSqlQueryModel* trier(const QString& methode);
   void sendWindowsNotification(const std::wstring &title, const std::wstring &message);

};
#endif // STOCK_H
