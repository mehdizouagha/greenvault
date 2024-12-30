/*#ifndef ARDUINO_H
#define ARDUINO_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QSerialPort>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QByteArray>
#include "qsqlerror.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QRegularExpression>

class Arduino : public QObject

{
   Q_OBJECT
public:
explicit Arduino(QObject *parent = nullptr);
  // explicit Arduino( QObject *parent=nullptr);
    Arduino();
    int connect_arduino(); // permet de connecter le PC à Arduino
    int close_arduino(); // permet de femer la connexion
    void write_to_arduino( QByteArray ); // envoyer des données vers arduino
    QByteArray read_from_arduino();  //recevoir des données de la carte Arduino
    QSerialPort* getserial();   // accesseur
    QString getarduino_port_name();
    bool saveWeightToDatabase(double weight);
   // bool saveWeightToDatabase(double weight);
    void readWeightFromSensor();
  //  QByteArray getWeightData();
    void write_to_arduino1( QByteArray d);
    QByteArray read_from_arduino1();
    int connect_arduino1();
    QSerialPort *getserial1();
    QString getarduino_port_name1();
    //~Arduino(); // Déstructeur si nécessaire
//signals:
    void weightDetected(const double &weight);
private:


QSerialPort * serial; //Cet objet rassemble des informations (vitesse, bits de données, etc.)
QSerialPort * serial1;
//et des fonctions (envoi, lecture de réception,…) sur ce qu’est une voie série pour Arduino.
static const quint16 arduino_uno_vendor_id=9025;
static const quint16 arduino_uno_producy_id=67;
QString arduino_port_name;
QString arduino_port_name1;
bool arduino_is_available;
QByteArray data;  // contenant les données lues à partir d'Arduino
  // Declare accumulatedData as a QByteArray
  // Declare accumulatedData as a QString
QByteArray accumulatedData;
};



#endif // ARDUINO_H
*/




#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QObject>
#include <QRegularExpression>
#include <QString>
#include <QByteArray>

class Arduino : public QObject
{
    Q_OBJECT

public:
    explicit Arduino(QObject *parent = nullptr);
    int connect_arduino(); // Connecte au premier port série
    int connect_arduino1(); // Connecte au deuxième port série
    int close_arduino(); // Ferme les connexions série
    void write_to_arduino(QByteArray data); // Envoie des données à Arduino
    QByteArray read_from_arduino(); // Lit les données du premier port série
    void write_to_arduino1(QByteArray data); // Envoie des données au deuxième Arduino
    QByteArray read_from_arduino1(); // Lit les données du deuxième port série
    bool saveWeightToDatabase(double weight); // Sauvegarde le poids dans la base de données
    void readWeightFromSensor(); // Lit le poids à partir du capteur
public slots:
    void updateStateFromSensor(); // Lire les données et émettre l'état

    QSerialPort* getserial();  // Accesseur pour le premier port série
    QSerialPort* getserial1(); // Accesseur pour le deuxième port série
    QString getarduino_port_name(); // Accesseur pour le nom du premier port série
    QString getarduino_port_name1(); // Accesseur pour le nom du deuxième port série
bool updateClientState(int clientId, QLabel* label);
signals:
    void weightDetected(double weight); // Signal pour émettre le poids détecté
signals:
    void stateChanged(int state);
private:
    QSerialPort *serial;  // Premier port série
    QSerialPort *serial1; // Deuxième port série
    QString arduino_port_name; // Nom du port du premier Arduino
    QString arduino_port_name1; // Nom du port du deuxième Arduino
    bool arduino_is_available; // Indicateur si Arduino est disponible
    QByteArray data; // Données reçues du port série
    QByteArray accumulatedData; // Données accumulées pour traitement

    static const quint16 arduino_uno_vendor_id = 9025; // Vendor ID pour Arduino
    static const quint16 arduino_uno_producy_id = 67; // Product ID pour Arduino

    int connect_arduino_common(QSerialPort* serialPort); // Fonction commune pour connecter un Arduino
};

#endif // ARDUINO_H
