#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H
#include <QTableView>  // Assurez-vous que cette ligne est incluse

#include <QMainWindow>
#include "personel.h"
#include"equipement.h"
#include"client.h"
#include"commande.h"
#include "stock.h"
#include <QCompleter>
#include <QStringListModel>
#include <QListView>
#include <QStringListModel>
#include <QMessageBox>
#include <QSystemTrayIcon>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QGraphicsView>
#include <QUrl>
#include"arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &email, QWidget *parent = nullptr);
    ~MainWindow();
    void priviligae();
    void exportTableViewToWord(QTableView *tableView);
    void exportTableViewToPDF(QTableView *tableView);
    //void exportTableViewToExcel(QTableView *tableView);
    void clear();
    void createChart();
    void setupTableView();
    void on_tableView_clicked(const QModelIndex &index);
   void resetFields();
    void  setupConnections();
    void connectToDatabase();
    void updateClientData(QWidget *editor);
    bool ajouterCommande(int idcl, int idc);
    void modifierClient();

    ////////////
     //void sendWeightToArduino(float POIDS);
     void sendDataToArduino(const QString &data);
     void updateDatabase(const QString &movementStatus);
     bool updateDatabase1(const double weight,int state);
     void sendDataToArduino1(const QString &data);

     void animateImage();
     void showEvent(QShowEvent *event);
private slots:
     void update_label1();
     void onWeightDetected(double weight);
     void update_label();
void update_labelT();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_modifier_2_clicked();

    void on_boutton_statitque_clicked();
    void on_ajouter_clicked();
    void on_supprimer_clicked();

   void on_afficher_clicked();

    void on_modifier_clicked();


    void on_lineEdit_textChanged(const QString &arg1);



    void on_modifier_3_clicked();
    //////////////////////////
    void on_pushButton_22_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_24_clicked();




    void on_lineEdit_5_textChanged();

    void on_comboBox_5_currentIndexChanged();
    void on_pushButton_23_clicked();



    void on_pushButton_3_clicked();

   // void on_pushButton_4_clicked();

    void on_pushButton_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_26_clicked();
    ///////////////////////////// client
   void on_pushButton_10_clicked();
        // Assurez-vous que cette ligne existe
    void on_pushButton_13_clicked();
    void on_charger_clicked();


    void on_comboBox_2_activated(int index);

    void on_lineEdit_2_textChanged(const QString &arg1);
   //void on_searchTimeout();




    void on_exporter_clicked();

    void on_pushButton_29_clicked();
    void on_pushButton_34_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();

    ///////////commande////////////
    void on_AjoutCo_clicked();

    void on_supco_clicked();

    //void on_pushButton_clicked();

    void on_Commandelist_activated(const QModelIndex &index);

    void on_chercherC_clicked();

    void on_statistique_clicked();

    //  void on_comboBox_activated(const QString &arg1);

    void on_exportpdf_clicked();

    void on_pushButton_18_clicked();

    void on_etatmodifier_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    ///

    void on_pushButton_19_clicked();

    void on_IDR_textChanged(const QString &arg1);

   // void on_comboBox_9_activated(int index);

    void on_comboBox_9_currentIndexChanged(int index);

  //  void on_pushButton_20_clicked();

    void on_pushButton_Ajouter_clicked();

private:
    Ui::MainWindow *ui;
    personel p;
    QLineEdit *lineEdit;  // Your QLineEdit
    QCompleter *completer;  // Declare QCompleter as a member
    QString useremail;
    equipement e;
   Client Etmp;
    QTimer *searchTimer;
    QSqlTableModel *model;
    Commande CL;
    QByteArray data; // variable contenant les données reçues

    Arduino A;
    Arduino A1;
    bool weightDetected=false;
//stock////////////////////////////////////////////////////////////////
  void displayCategoryStatistics();
  void on_pushButton_14_clicked();
  void on_pushButton_17_clicked();
  void on_pushButton_16_clicked();
  void on_IDR_textChanged();
  void on_pushButton_15_clicked();
  void on_pushButton_32_clicked();
  //void on_comboBox_9_currentIndexChanged();
  //void on_comboBox_9_activated(int index);
  void checkExpirationAndNotify();
void setupArduino();
void saveStateToDatabase();
  void on_pushButton_31_clicked();  // Slot for SMS sending logic

  void on_afficher2_clicked();


     void on_affi_img_clicked();

     void on_afiicher_imgb_clicked();
void on_pushButton_etat_clicked();

private:
    void drawPieChart(const QMap<QString, double>& statistiques);
    void sendSmsNotification(const QString &message);  // Function to send SMS notifications
    void sendWindowsNotification(const QString &title, const QString &message);  // Send Windows notification

    class QRCodeGenerator {
    public:
        static QImage generateQRCode(const QString &data);  // Generate QR code
    };

    void startExpirationCheck(); // Start the expiration check automatically
    void onSmsReplyFinished();

private:

    stock Stmp;
    QNetworkAccessManager *networkManager; // For sending SMS




};
#endif // SECONDWINDOW_H
//////////////////////////////////////////////

