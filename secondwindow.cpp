#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "arduino.h"
#include "personel.h"
#include "calendrierconge.h"
#include "client.h"
#include <QRegularExpression>  // Inclure cet en-tête au début de votre fichier
#include <QDate>
#include <QMessageBox>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QTimer>
#include <QPrinter>
#include <QRectF>
#include <QRect>
#include <QImage>
#include <QProcess>
#include <QCoreApplication>
#include <QList>
#include <QVector>
#include <QDebug>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QAbstractItemModel>
#include <QStandardItem>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QModelIndex>
#include <QVBoxLayout>
#include <QtCharts>
#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include <QtMultimedia/QMediaPlayer>
#include <iostream>

#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include "stock.h"
#include <QMessageBox>
#include <QSqlRecord>
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>
#include <QFileDialog>
#include <QImage>
#include <QLabel>
#include <QGraphicsScene>

#include <chrono>
#include <ctime>
#include <QDate>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QRegularExpression>  // Include the necessary header
#include <QJsonDocument>
#include <QJsonObject>
#include <QAction>


MainWindow::MainWindow(const QString &email, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      useremail(email)
{
    //////////////////////////////////////////////



    /// ///////////////////////////////////////:

    ui->setupUi(this);
    Arduino* arduino= new Arduino(this);
    connect(arduino, &Arduino::weightDetected, this, &MainWindow::onWeightDetected);
    connect(ui->pushButton_etat, &QPushButton::clicked, this, &MainWindow::on_pushButton_etat_clicked);
    connect(ui->pushButton_etat, &QPushButton::clicked, this, &MainWindow::saveStateToDatabase);


////////////////////////////////youssef
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     ///////////////////////////////////////////////////////////////////
     //le slot update_label suite à la reception du signal readyRead (reception des données).
    int ret1=A1.connect_arduino1(); // lancer la connexion à arduino
    switch(ret1){
    case(0):qDebug()<< "arduino is available and connected to : "<< A1.getarduino_port_name1();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A1.getarduino_port_name1();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A1.getserial1(),SIGNAL(readyRead()),this,SLOT(update_label1()));
    ui->tableView_8->setModel(Stmp.afficher());

    displayCategoryStatistics();

    networkManager = new QNetworkAccessManager(this);  // Initialize network manager
    connect(ui->boutton_statitque, &QPushButton::clicked, this, &MainWindow::on_boutton_statitque_clicked);



    priviligae();




    QAction *iconAction1 = new QAction(this);
    QIcon icon1(":/img/Screenshot_2024-10-08_134640-removebg-preview.png");
    iconAction1->setIcon(icon1);
    ui->tabWidget->setTabIcon(0, icon1);
    ui->tabWidget->setTabText(0, "client");
    QAction *iconAction2 = new QAction(this);
    QIcon icon2(":/img/Screenshot_2024-10-08_134706-removebg-preview.png");
    iconAction2->setIcon(icon2);
    ui->tabWidget->setTabIcon(1, icon2);
    ui->tabWidget->setTabText(1, "personnel");
    QAction *iconAction3 = new QAction(this);
    QIcon icon3(":/img/Screenshot_2024-10-08_134713-removebg-preview.png");
    iconAction3->setIcon(icon3);
    ui->tabWidget->setTabIcon(2, icon3);
    ui->tabWidget->setTabText(2, "Stock");
    QAction *iconAction4 = new QAction(this);
    QIcon icon4(":/img/Screenshot_2024-10-08_134859-removebg-preview.png");
    iconAction4->setIcon(icon4);
    ui->tabWidget->setTabIcon(3, icon4);
    ui->tabWidget->setTabText(3, "Commande");
    QAction *iconAction5 = new QAction(this);
    QIcon icon5(":/img/Screenshot_2024-10-08_134930-removebg-preview.png");
    iconAction5->setIcon(icon5);
    ui->tabWidget->setTabIcon(4, icon5);
    ui->tabWidget->setTabText(4, "Equipement");

    ui->tabWidget_2->setTabText(0, "Acceuil");
    ui->tabWidget_2->setTabText(1, "Fonctionalite");
    ui->lineEdit_id->setPlaceholderText("id");

    ui->lineEdit_nom->setPlaceholderText("nom");
    ui->lineEdit_prenom->setPlaceholderText("prenom");
    // ui->dateEdit->setPlaceholderText("Date_Embauche"); //
    ui->lineEdit_poste->setPlaceholderText("poste");
    ui->lineEdit_salaire->setPlaceholderText("salaire");
    ui->lineEdit_telephone->setPlaceholderText("telephone");
    ui->lineEdit_mail->setPlaceholderText("mail");



    QAction *iconAction = new QAction(this);
    QIcon icon(":/img/Screenshot_2024-10-08_135113-removebg-preview.png");
    iconAction->setIcon(icon);
    ui->lineEdit->addAction(iconAction->icon(), QLineEdit::LeadingPosition);
    ui->lineEdit->setPlaceholderText("Rechercher");


    ui->id_client->setPlaceholderText("id");
    ui->nom1_2->setPlaceholderText("nom");
    ui->prenom1_2->setPlaceholderText("prenom");
    ui->email_2->setPlaceholderText("email");
    ui->adresse->setPlaceholderText("adresse");
    ui->IDCL_c->setPlaceholderText("id client");
    ui->IDC_c->setPlaceholderText("id commande");
    iconAction->setIcon(icon);
    ui->lineEdit_2->addAction(iconAction->icon(), QLineEdit::LeadingPosition);
    ui->lineEdit_2->setPlaceholderText("Rechercher");

    ui->tabWidget_4->setTabText(0,"Acceuil");
    ui->tabWidget_4->setTabText(1,"Fonctionalite");
    ui->id_stock->setPlaceholderText("id");
    ui->nom1_3->setPlaceholderText("nom");
    ui->categorie->setPlaceholderText("categorie");
    ui->fournisseur->setPlaceholderText("fournisseur");
  //  ui->date_ex->setPlaceholderText("date-expedition");
 //   ui->dateaq->setPlaceholderText("date-aquesition");
    ui->condition_s->setPlaceholderText("condition stock");
    ui->quantite_disp->setPlaceholderText("quantite_disponible");
   // ui->lineEdit_3->addAction(iconAction->icon(), QLineEdit::LeadingPosition);
    //ui->lineEdit_3->setPlaceholderText("Rechercher");

   /* ui->tabWidget_5->setTabText(0,"Acceuil");
    ui->tabWidget_5->setTabText(1,"Fonctionalite");
    ui->id_commande->setPlaceholderText("id");
    ui->etat_commande->setPlaceholderText("etat_commande");
    ui->date_cimmande->setPlaceholderText("date_commande");
    ui->id_client->setPlaceholderText("id_client");
    ui->id_client_2->setPlaceholderText("id_client");
    ui->id_material->setPlaceholderText("id_material");
    ui->quantite_c->setPlaceholderText("quantite commande");
    ui->date_liv->setPlaceholderText("date_livraison");
    ui->lineEdit_4->addAction(iconAction->icon(), QLineEdit::LeadingPosition);
    ui->lineEdit_4->setPlaceholderText("Rechercher");*/

    ui->tabWidget_6->setTabText(0,"Acceuil");
    ui->tabWidget_6->setTabText(1,"Fonctionalite");
    ui->id_equipement->setPlaceholderText("id");
    ui->nom_e->setPlaceholderText("nom");
    ui->categorie_2->setPlaceholderText("categorie");
    ui->etat_eq->setPlaceholderText("etat");
   // ui->date_dm->setPlaceholderText("date_dernier_maintenace");
    //ui->date_pm->setPlaceholderText("date_prochain_maintenace");
    ui->prix->setPlaceholderText("prix");
    //ui->par_suivi->setPlaceholderText("parametre_suivi");
    //ui->date_aquesition->setPlaceholderText("date-aquesition");
    ui->localisation_eq->setPlaceholderText("localisation");
    ui->fourniseureq->setPlaceholderText("fournisseur");
    ui->lineEdit_5->addAction(iconAction->icon(), QLineEdit::LeadingPosition);
    ui->lineEdit_5->setPlaceholderText("Rechercher");
    QIcon icon6(":/img/Screenshot_2024-10-09_092351-removebg-preview.png");
    iconAction->setIcon(icon6);
    //ui->comboBox_6->addItem(icon6, "word");
    QIcon icon7(":/img/Screenshot_2024-10-09_093226-removebg-preview.png");
    iconAction->setIcon(icon7);
   // ui->comboBox_6->addItem(icon7, "pdf");
    QIcon icon8(":/img/Screenshot_2024-10-09_093052-removebg-preview.png");
    iconAction->setIcon(icon8);
///////////////////////////////////////////////////////////////////////////////////////////////
  //  ui->comboBox_6->addItem(icon8, "exel");
    ///////////////////////////////////////
    ui->comboBox_7->addItem(icon6, "word");
    ui->comboBox_7->addItem(icon7, "pdf");
    ui->comboBox_7->addItem(icon8, "exel");
    ui->comboBox_8->addItem(icon6, "word");
    ui->comboBox_8->addItem(icon7, "pdf");
    ui->comboBox_8->addItem(icon8, "exel");
   /* ui->comboBox_9->addItem(icon6, "word");
    ui->comboBox_9->addItem(icon7, "pdf");
    ui->comboBox_9->addItem(icon8, "exel");*/
    ui->comboBox_10->addItem(icon6, "word");
    ui->comboBox_10->addItem(icon7, "pdf");
    ui->comboBox_10->addItem(icon8, "exel");
    ///
    ///
    ui->tabWidget_2->setTabText(2,"affectation");
    ui->tabWidget_6->setTabText(2,"affectation");
    ui->tableView_2->setModel(e.afficher());
    ui->tableView->setModel(p.afficher());
    ui->tableView_2->setModel(e.getTableModel(this));
    ui->tableView_2->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->label_22->setGeometry(100, 100, 300, 300);
    int currentX = ui->label_22->x();
    ui->label_22->move(currentX + 300, ui->label_22->y());
    QMediaPlayer player;
    std::cout << "Qt Multimedia is available." << std::endl;
    ui->tabWidget_7->setTabText(1,"QR code");
    ui->tabWidget_7->setTabText(0,"diagnostique");
    ui->tabWidget_7->setTabText(2,"statistique");
    connect(ui->tableView_2->model(), &QAbstractItemModel::dataChanged, this, &MainWindow::createChart);
    connect(ui->tableView_2->model(), &QAbstractItemModel::rowsInserted, this, &MainWindow::createChart);
    connect(ui->tableView_2->model(), &QAbstractItemModel::rowsRemoved, this, &MainWindow::createChart);
    e.populateComboBoxE(ui->comboBox_12);
    e.populateComboBoxP(ui->comboBox_14);
    p.populateComboBoxP(ui->comboBox_13);
    p.populateComboBoxE(ui->comboBox_15);
    ui->tableView_3->setModel(e.afficherAffectation());
    ui->tableView_4->setModel(p.afficherAffectation());

    ///////////////////////////////////////////////
    // Connexions des boutons
    connect(ui->pushButton_12, &QPushButton::clicked, this, &MainWindow::on_pushButton_12_clicked);
    connect(ui->pushButton_10, &QPushButton::clicked, this, &MainWindow::on_pushButton_10_clicked);
    connect(ui->pushButton_13, &QPushButton::clicked, this, &MainWindow::on_pushButton_13_clicked);

    // Connexion du timer
   // searchTimer->setInterval(500);  // Attendre 500 ms après la dernière frappe
    //connect(searchTimer, &QTimer::timeout, this, &MainWindow::searchTimer);

    // Charger le modèle initialement sans tri
    ui->tableView_5->setModel(Etmp.afficher());
    // Initialiser le comboBox_2 avec les options de tri
    connect(ui->comboBox_2, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_comboBox_2_activated);




    connect(ui->pushButton_29, &QPushButton::clicked, this, &MainWindow::on_pushButton_29_clicked);







    connect(ui->tableView_5, &QTableView::clicked, this, &MainWindow::on_tableView_clicked);
    ui->tableView_5->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);

   ui->tableView_5->setModel(Etmp.afficher());

   connect(ui->pushButton_14, &QPushButton::clicked, this, &MainWindow::on_pushButton_14_clicked);

   connect(ui->pushButton_15, &QPushButton::clicked, this, &MainWindow::on_pushButton_15_clicked);
   connect(ui->pushButton_16, &QPushButton::clicked, this, &MainWindow::on_pushButton_16_clicked);
    connect(ui->pushButton_17, &QPushButton::clicked, this, &MainWindow::on_pushButton_17_clicked);
    connect(ui->afiicher_imgb, &QPushButton::clicked, this, &MainWindow::on_afiicher_imgb_clicked);
    connect(ui->affi_img, &QPushButton::clicked, this, &MainWindow::on_affi_img_clicked);
    connect(ui->pushButton_31, &QPushButton::clicked, this, &MainWindow::on_pushButton_31_clicked);

    //on_comboBox_9_currentIndexChanged();
    on_IDR_textChanged();
}

///////////////////////////////////////////
///



void MainWindow::update_labelT() {
    // Lire les données de l'Arduino
    QByteArray rawData = A.read_from_arduino();
    qDebug() << "Data received from Arduino:" << rawData;

    // Vérifier si les données sont valides
    QString data = QString::fromUtf8(rawData).trimmed();
    bool isNumeric;
    double weight = data.toDouble(&isNumeric);

    if (isNumeric) {
        ui->label_40->setText(QString::number(weight, 'f', 2));  // Afficher le poids
        ui->label_42->setText(QString::number(1));
        qDebug() << "Weight displayed in label_40: " << weight;
    } else {
        ui->label_40->setText("Invalid data");
        qDebug() << "Invalid data received: " << data;
    }


}








void MainWindow::update_label1()
{
    QByteArray data = A1.read_from_arduino1();
    QString message = QString::fromUtf8(data).trimmed();

    qDebug() << "Received data:" << message;


    if (message == "1") {
        ui->label_41->setText("Motion Detected");
        ui->label_41->repaint();
        updateDatabase("1");
        sendDataToArduino("1");
    } else if (message == "0") {
        ui->label_41->setText("No Motion");
        ui->label_41->repaint();
        updateDatabase("0");
        sendDataToArduino("0");
    } else {
        qDebug() << "Unexpected message:" << message;
    }
}


void MainWindow::sendDataToArduino(const QString &data)
{
    QByteArray command = data.toUtf8();
    A1.write_to_arduino1(command);
    qDebug() << "Sent command to Arduino:" << command;
}

void MainWindow::updateDatabase(const QString &movementStatus)
{
    QSqlQuery query;
    query.prepare("UPDATE STOCK SET MOVEMENT = :movement WHERE IDS = :id");


    if (movementStatus == "1") {
        query.bindValue(":movement", 1);
    } else {
        query.bindValue(":movement", 0);
    }


    query.bindValue(":id", 33);


    if (query.exec()) {
        qDebug() << "Database updated successfully!";
    } else {

        qDebug() << "Error updating database:" << query.lastError().text();
    }
}


///

///

void MainWindow::onWeightDetected(double weight) {
   qDebug() << "Detected weight: " << weight;

   // Display the weight in label_40
   ui->label_40->setText(QString::number(weight, 'f', 2));  // Display the weight with 2 decimal places
}
#include <QRegularExpression>  // Inclure cet en-tête au début de votre fichier

void MainWindow::on_pushButton_Ajouter_clicked() {
    QString idcl = ui->id_client_3->text().trimmed(); // Get client ID
    QString rawData = ui->label_40->text().trimmed(); // Get weight from label_40

    // Vérification de l'ID client
    if (idcl.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter the client ID (IDCL).");
        return;
    }

    // Vérification de la validité du poids
    if (rawData.isEmpty() || rawData == "Invalid data") {
        QMessageBox::warning(this, "Error", "No valid weight detected.");
        return;
    }

    qDebug() << "Raw Data: " << rawData; // Affichage du contenu de rawData pour déboguer

    // Validation de l'ID client
    bool idIsNumeric;
    int clientId = idcl.toInt(&idIsNumeric);
    if (!idIsNumeric) {
        QMessageBox::critical(this, "Error", "Client ID (IDCL) must be a valid number.");
        return;
    }

    // Nettoyage du texte brut pour extraire le poids
    QRegularExpression regex("[^0-9.,]");  // Expression régulière pour retirer tout sauf chiffres, point ou virgule
    rawData.remove(regex);  // Enlève tout ce qui n'est pas un chiffre, un point ou une virgule
    rawData.replace(",", ".");  // Remplace les virgules par des points pour le format numérique

    qDebug() << "Cleaned Raw Data: " << rawData;  // Vérification après nettoyage

    // Vérification si le texte nettoyé est un nombre valide
    bool weightIsNumeric;
    double weight = rawData.toDouble(&weightIsNumeric);
    if (!weightIsNumeric) {
        QMessageBox::critical(this, "Error", "The detected weight is not valid.");
        return;
    }

    // Vérification si le client existe
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM CLIENT WHERE IDCL = :idcl");
    checkQuery.bindValue(":idcl", clientId);

    if (!checkQuery.exec() || !checkQuery.next() || checkQuery.value(0).toInt() == 0) {
        QMessageBox::critical(this, "Error", "Client with IDCL not found.");
        return;
    }

    // Mise à jour du poids dans la base de données
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET POIDS = :poids WHERE IDCL = :idcl");
    query.bindValue(":poids", weight);
    query.bindValue(":idcl", idcl);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Weight updated successfully.");
        qDebug() << "Weight updated: " << weight << " for IDCL: " << idcl;
    } else {
        QMessageBox::critical(this, "Error", "Failed to update weight in the database.");
        qDebug() << "SQL error: " << query.lastError().text();
    }
}



////////////////////////////////////////////////////////:yousssed

QString buffer;  // Declare a buffer to accumulate fragments

void MainWindow::update_label() {
    QByteArray data = A.read_from_arduino();  // Read data from Arduino
    qDebug() << "Raw data received from Arduino:" << data;

    buffer.append(QString::fromUtf8(data));  // Append the new fragment to the buffer

    // Check if the buffer contains the delimiter indicating complete data
    if (buffer.contains("\n")) {  // Assuming the end of data is marked by "\n"
        QString receivedData = buffer.trimmed();  // Trim spaces or newlines
        buffer.clear();  // Clear the buffer after processing the data
        qDebug() << "Complete data received:" << receivedData;

        // Split the received data into weight and state
        QStringList parts = receivedData.split(",");
        if (parts.size() == 2) {
            QString weightStr = parts[0].trimmed();  // Extract weight part
            QString stateStr = parts[1].trimmed();  // Extract state part

            double weight = weightStr.toDouble();  // Convert weight to double
            int state = stateStr.toInt();         // Convert state to integer

            qDebug() << "Extracted weight:" << weight << ", state:" << state;

            // Update the UI based on the state
            if (state == 1) {
                ui->label_40->setText("Weight Confirmed: " + QString::number(weight) + " kg");
                ui->label_42->setText(QString::number(1));
                updateDatabase1(weight, state);
                ui->label_50->clear();  // Clear any previous error messages
            } else if (state == 0) {
                ui->label_40->setText("Weight Not Confirmed: " + QString::number(weight) + " kg");
                ui->label_50->clear();  // Clear any previous error messages
            } else {
                ui->label_40->clear();
                ui->label_50->setText("Invalid state received!");
            }

            // Optional: Save weight to database
            if (!updateDatabase1(weight, state)) {
                qDebug() << "Failed to save weight and state to the database.";
            }
        } else {
            qDebug() << "Invalid data format: " << receivedData;
            ui->label_40->setText("Invalid data format received!");
        }
    } else {
        qDebug() << "Waiting for more data to complete the message.";
    }
}


void MainWindow::sendDataToArduino1(const QString &data)
{
    // Query to get the current weight (POIDS) from the database
    QSqlQuery query;
    query.prepare("SELECT POIDS FROM CLIENT WHERE IDCL = :id");
    query.bindValue(":id", 234);  // Assuming the record ID is 33, adjust as needed

    if (query.exec() && query.next()) {
        double poids = query.value("POIDS").toDouble();
        qDebug() << "Current weight from database:" << poids;

        // Check if the weight is less than 200
        if (poids < 200) {
            // Display confirmation message
            QMessageBox::information(this, "Confirmation", "Weight is less than 200. Proceeding with operation.");
            // Now send the data to Arduino
            QByteArray command ="confirmer" ;
            A.write_to_arduino(command);  // Send the data to Arduino
            qDebug() << "Sent data to Arduino:" << command;
        } else {
            QByteArray command ="non confirmer";
            A.write_to_arduino(command);
            // If the weight is greater than or equal to 200, display a warning
            QMessageBox::warning(this, "Warning", "Weight is 200 or more. Operation aborted.");
        }
    } else {
        qDebug() << "Error querying database:" << query.lastError().text();
    }
}

bool MainWindow::updateDatabase1(double weight, int state) {
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (POIDS, ETAT) VALUES (:weight, :state)");
    query.bindValue(":weight", weight);
    query.bindValue(":state", 1);

    if (query.exec()) {
        qDebug() << "Weight and state saved to database successfully.";
        return true;
    } else {
        qDebug() << "Failed to save weight and state to database: " << query.lastError();
        return false;
    }
}

/////////////////////////////////////////////////:

/*
void MainWindow::sendWeightToArduino(float POIDS) {
        if (A.connect_arduino()) {
            if (POIDS < 200){
                 QByteArray data = "confirmer";  // Command for green LED
                 A.write_to_arduino(data);
            }else{
                 QByteArray data = "non confirmer";
                 A.write_to_arduino(data);
            }

        } else {
            qDebug() << "Arduino port not open.";
        }
}
*/
/*void MainWindow::on_pushButton_20_clicked()
{
    qDebug() << "Le bouton pushButton_26 a été cliqué.";  // Débogage initial

    // Vérifier si la base de données est connectée
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Erreur : La base de données n'est pas ouverte.";
        QMessageBox::critical(this, "Erreur", "La base de données n'est pas ouverte.");
        return;
    } else {
        qDebug() << "La base de données est bien ouverte.";
    }

    QSqlQuery query;
    QString queryString = "SELECT POIDS FROM STOCK WHERE ROWNUM = 1";  // Compatible avec Oracle

    if (!query.exec(queryString)) {
        qDebug() << "Erreur lors de l'exécution de la requête SQL : " << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'exécution de la requête SQL.");
        return;
    } else {
        qDebug() << "Requête SQL exécutée avec succès.";
    }

    // Vérification si des résultats sont retournés
    if (!query.next()) {
        qDebug() << "Aucune ligne retournée par la requête SQL.";
        QMessageBox::warning(this, "Attention", "Aucune donnée trouvée dans la table STOCK.");
        return;
    } else {
        qDebug() << "Une ligne a été trouvée dans la table STOCK.";
    }

    float POIDS = query.value(0).toDouble();
    qDebug() << "Poids récupéré depuis la base de données : " << POIDS;

    QByteArray message;
    QString userMessage;
    if (POIDS > 200) {
        message = "non confirmé";
        userMessage = "Le poids est supérieur à 2 kg. Non confirmé.";
        qDebug() << "Message décidé : non confirmé";
    } else {
        message = "confirmé";
        userMessage = "Le poids est inférieur ou égal à 2 kg. Confirmé.";
        qDebug() << "Message décidé : confirmé";
    }

    // Afficher un message dans une boîte de dialogue
    QMessageBox::information(this, "Information", userMessage);


    qDebug() << "Envoi du message à l'Arduino : " << message;
    qDebug() << "Message envoyé à l'Arduino avec succès.";

     sendWeightToArduino(POIDS);

}*/




void MainWindow::on_ajouter_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QDate date = ui->dateEdit->date();
    QString poste = ui->lineEdit_poste->text();
    int salaire = ui->lineEdit_salaire->text().toInt();
    QString mail = ui->lineEdit_mail->text();
    int telephone = ui->lineEdit_telephone->text().toInt();
    QString role =ui->comboBox_6->currentText();


    // Instanciation d'un objet de la classe Client
    personel p(id, nom, prenom, date, poste, salaire, mail, telephone ,role);

    // Appel de la méthode ajouter() pour insérer l'objet dans la base de données
    bool test = p.ajouter();

    // Affichage d'une boîte de dialogue en fonction du résultat
    if (test)
    {

        //ui->tableView->setModel(p.afficher());
        ui->tableView->setModel(p.afficher());
        p.populateComboBoxP(ui->comboBox_13);
        p.populateComboBoxE(ui->comboBox_15);
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
    }
    connect(ui->modifier_3, &QPushButton::clicked, this, &MainWindow::on_modifier_3_clicked);
}


void MainWindow::priviligae(){
    personel p;
    QString role =p.getUserRole(useremail);
    qDebug() << "role :" << role;

    if (role == "client"){
        ui->tabWidget->setCurrentIndex(0);
        ui->tabWidget->setTabEnabled(1, false);  // Index starts at 0, so 1 corresponds to tab 2
        ui->tabWidget->setTabEnabled(2, false);  // Disable tab 3
        ui->tabWidget->setTabEnabled(3, false);  // Disable tab 4
        ui->tabWidget->setTabEnabled(4, false);  // Disable tab 5
    }
    if (role == "personel"){
        ui->tabWidget->setCurrentIndex(1);
        ui->tabWidget->setTabEnabled(0, false);  // Index starts at 0, so 1 corresponds to tab 2
        ui->tabWidget->setTabEnabled(2, false);  // Disable tab 3
        ui->tabWidget->setTabEnabled(3, false);  // Disable tab 4
        ui->tabWidget->setTabEnabled(4, false);  // Disable tab 5
    }
    if (role == "stock"){
        ui->tabWidget->setCurrentIndex(2);
        ui->tabWidget->setTabEnabled(0, false);  // Index starts at 0, so 1 corresponds to tab 2
        ui->tabWidget->setTabEnabled(1, false);  // Disable tab 3
        ui->tabWidget->setTabEnabled(3, false);  // Disable tab 4
        ui->tabWidget->setTabEnabled(4, false);  // Disable tab 5
    }
    if (role == "commande"){
        ui->tabWidget->setCurrentIndex(3);
        ui->tabWidget->setTabEnabled(0, false);  // Index starts at 0, so 1 corresponds to tab 2
        ui->tabWidget->setTabEnabled(1, false);  // Disable tab 3
        ui->tabWidget->setTabEnabled(2, false);  // Disable tab 4
        ui->tabWidget->setTabEnabled(4, false);  // Disable tab 5
    }
    if (role == "equipement"){
        ui->tabWidget->setCurrentIndex(4);
        ui->tabWidget->setTabEnabled(0, false);  // Index starts at 0, so 1 corresponds to tab 2
        ui->tabWidget->setTabEnabled(1, false);  // Disable tab 3
        ui->tabWidget->setTabEnabled(2, false);  // Disable tab 4
        ui->tabWidget->setTabEnabled(3, false);  // Disable tab 5
    }


}


void MainWindow::on_supprimer_clicked()
{
    int id = ui->lineEdit_id->text().toInt(); // Récupérer l'ID de l'enregistrement

    if (id == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir l'ID pour identifier l'enregistrement.");
        return;
    }

    QString attribut;
    QStringList attributs = {"nom", "prenom", "mail", "telephone", "poste", "salaire"};

    // Chercher quel champ est rempli
    for (const QString &attr : attributs) {
        QLineEdit *field = findChild<QLineEdit *>("lineEdit_" + attr);
        if (field && !field->text().isEmpty()) {
            attribut = attr;
            break;
        }
    }

    if (attribut.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir un champ pour identifier l'attribut à supprimer.");
        return;
    }

    // Appeler une méthode qui supprimera toute la ligne en fonction de l'attribut et de l'ID
    bool test = p.supprimer(id, attribut); // Méthode pour supprimer toute la ligne

    if (test) {
        ui->tableView->setModel(p.afficher()); // Rafraîchir la table
        QMessageBox::information(this, "Succès", "La ligne a été supprimée avec succès !");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression de la ligne.");
    }
}


void MainWindow::on_afficher_clicked()
{
    // Créez une instance de la classe personel
    personel p; // Assurez-vous que votre classe personel est correctement définie

    // Mettez à jour le modèle du QTableView avec les données
    ui->tableView->setModel(p.afficher()); // Appelle la méthode afficher de la classe personel

}






void MainWindow::on_modifier_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QDate date = ui->dateEdit->date();
    QString poste = ui->lineEdit_poste->text();
    int salaire = ui->lineEdit_salaire->text().toInt();
    QString mail = ui->lineEdit_mail->text();
    int telephone = ui->lineEdit_telephone->text().toInt();
    QString role=ui->comboBox_6->currentText();


    personel p(id, nom, prenom, date, poste, salaire, mail, telephone,role);


    p.setID(id);
    p.setNom(nom);
    p.setPrenom(prenom);
    p.setDate(date);
    p.setPoste(poste);
    p.setsalaire(salaire);
    p.setMail(mail);
    p.setTelephone(telephone);


    bool test = p.modifier(id);

    if (test)
    {
        ui->tableView->setModel(p.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
        ui->tableView->setModel(p.afficher());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Modification non effectuée.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);

    }

}

MainWindow::~MainWindow()
{
    delete ui;


}






// Fonction appelée lors du clic sur le bouton PDF
void MainWindow::on_pushButton_7_clicked() {
    personel p;

    // Demander à l'utilisateur de choisir l'ordre de tri
    QMessageBox msgBox;
    msgBox.setWindowTitle("Choisir l'ordre de tri");
    msgBox.setText("Veuillez choisir l'ordre de tri pour les ID:");
    QPushButton *ascButton = msgBox.addButton("Ascendant", QMessageBox::ActionRole);
    QPushButton *descButton = msgBox.addButton("Descendant", QMessageBox::ActionRole);
    msgBox.exec();

    bool ordreCroissant = (msgBox.clickedButton() == ascButton);

    QSqlQueryModel* model = p.afficherTrieParID(ordreCroissant);

    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "*.pdf");
    if (fileName.isEmpty())
        return;

    if (QFileInfo(fileName).suffix().isEmpty())
        fileName.append(".pdf");

    // Créer le QPdfWriter pour le fichier PDF
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageOrientation(QPageLayout::Portrait);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);

    if (!model) {
        QMessageBox::warning(this, "Erreur", "Aucune donnée à exporter.");
        return;
    }

    // Paramètres du tableau
    int x = 20;  // Position de départ sur l'axe X (marge gauche)
    int y = 150; // Position de départ sur l'axe Y (marge haute pour le tableau)
    int rowHeight = 60; // Hauteur des lignes augmentée
    int columnWidth = 300; // Largeur des colonnes augmentée

    // Appliquer des couleurs vertes
    QColor headerColor(34, 139, 34); // Vert foncé pour l'en-tête
    QColor altRowColor(144, 238, 144); // Vert clair pour les lignes alternées
    QColor textColor(0, 128, 0);      // Vert foncé pour le texte

    // Dessiner le titre "Liste des personnels"
    QFont titleFont("Arial", 25, QFont::Bold); // Police du titre
    painter.setFont(titleFont);
    painter.setPen(QPen(QColor(0, 128, 0))); // Couleur du texte en vert
    QString title = "Liste des personnels";
    int pageWidth = pdfWriter.width(); // Largeur de la page
    int textWidth = painter.fontMetrics().horizontalAdvance(title); // Largeur du texte
    int centeredX = (pageWidth - textWidth) / 2; // Position pour centrer le titre
    painter.drawText(centeredX, 100, title); // Dessiner le titre centré

    // Ajouter le logo plus haut, à côté du titre
    QPixmap logo(":/img/logo.png"); // Chemin vers le logo dans le dossier des ressources
    if (!logo.isNull()) {
        int logoWidth = 100;  // Largeur du logo
        int logoHeight = 120; // Hauteur du logo
        int logoX = pageWidth - logoWidth - 20; // Position à droite du titre
        int logoY = 20; // Position verticale ajustée pour le logo (plus haut)
        painter.drawPixmap(logoX, logoY, logoWidth, logoHeight, logo);
    }

    // Dessiner l'en-tête du tableau
    painter.setFont(QFont("Arial", 10));
    painter.setBrush(QBrush(headerColor)); // Couleur de fond pour l'en-tête
    painter.setPen(QPen(Qt::white)); // Texte en blanc pour l'en-tête

    for (int column = 0; column < model->columnCount(); ++column) {
        QRect rect(x + column * columnWidth, y, columnWidth, rowHeight);
        painter.drawRect(rect); // Dessiner la bordure de la cellule
        painter.drawText(rect, Qt::AlignCenter, model->headerData(column, Qt::Horizontal).toString()); // Dessiner l'en-tête
    }

    y += rowHeight; // Déplacer vers le bas après l'en-tête

    // Dessiner les données du tableau
    painter.setPen(QPen(textColor)); // Texte en vert foncé
    for (int row = 0; row < model->rowCount(); ++row) {
        QColor rowColor = (row % 2 == 0) ? Qt::white : altRowColor; // Alternance de couleur pour les lignes
        painter.setBrush(QBrush(rowColor));

        for (int column = 0; column < model->columnCount(); ++column) {
            QRect rect(x + column * columnWidth, y + row * rowHeight, columnWidth, rowHeight);
            painter.drawRect(rect); // Dessiner la bordure de la cellule
            painter.drawText(rect.adjusted(5, 0, -5, 0), Qt::AlignVCenter | Qt::AlignLeft, model->data(model->index(row, column)).toString()); // Remplir la cellule avec les données
        }
    }

    painter.end();

    QMessageBox::information(this, "Succès", "PDF généré avec succès !");
}




void MainWindow::on_pushButton_8_clicked() {
    static bool ordreCroissant = true;

    personel p;
    QSqlQueryModel *model = p.afficherTrieParID(ordreCroissant);

    ui->tableView->setModel(model);
    ordreCroissant = !ordreCroissant;
}



void MainWindow::on_modifier_2_clicked()//recherche
{
    QString id = ui->lineEdit->text();  // Récupère l'ID depuis le champ de saisie

    personel p;
    QSqlQueryModel *model = p.rechercher(id);  // Appelle la fonction de recherche par ID
    ui->tableView->setModel(model);  // Affiche le résultat dans le QTableView
}

/*void MainWindow::on_boutton_statitque_clicked()//stat
{
    qDebug() << "Bouton statistique cliqué !"; // Vérifie que le slot est appelé
    personel p;
    QMap<QString, double> stats = p.statistiquesPourcentageSalaire();

    // Créer une série de secteurs pour le graphique en camembert
    QPieSeries *series = new QPieSeries();

    // Définir quelques couleurs pour les secteurs
    QColor green1 = QColor(0, 128, 0); // Dark green
    QColor green2 = QColor(60, 179, 113); // Forest green
    QColor green3 = QColor(144, 238, 144); // Light green

    int index = 0;
    // Ajouter des secteurs pour chaque tranche de salaire
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        QPieSlice *slice = series->append(it.key(), it.value());

        // Appliquer une couleur différente pour chaque secteur
        switch (index % 3) {
            case 0: slice->setColor(green1); break;
            case 1: slice->setColor(green2); break;
            case 2: slice->setColor(green3); break;
        }

        // Afficher le pourcentage sur le graphique
        slice->setLabelVisible(true);
        slice->setLabel(QString("%1: %2%").arg(slice->label()).arg(slice->percentage() * 100, 0, 'f', 1));

        index++;
    }

    // Créer un graphique et ajouter la série des secteurs
    QChart *chart = new QChart();
   // chart->addSeries(series);


    chart->setTitle("Répartition en pourcentage des employés par tranche de salaire");

    // S'assurer que le graphique est circulaire et centré
    chart->setAnimationOptions(QChart::SeriesAnimations);  // Animation pour adoucir les transitions

    // Créer une vue de graphique
    QChartView *chartView = new QChartView(chart);
   // chartView->setRenderHint(QPainter::Antialiasing); // Activer l'anticrénelage pour des visuels plus nets

    // Configurer la taille du graphique, mais s'assurer qu'il est bien circulaire
   // chartView->setFixedSize(600, 600); // Taille fixée pour qu'il soit bien circulaire (carré)

    // Ajouter la vue à un layout et l'afficher dans le QGraphicsView
    ui->graphicsView->setScene(new QGraphicsScene());
   // ui->graphicsView->scene()->addWidget(chartView);

    // Ajuster automatiquement le graphique pour qu'il soit bien centré et visible
  //  ui->graphicsView->fitInView(chartView->sceneRect(), Qt::KeepAspectRatio);

    // Rafraîchir l'affichage
    ui->graphicsView->scene()->update();
    ui->graphicsView->show();
}

*/

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    qDebug() << "Texte changé dans le QLineEdit:" << arg1;

    // Si le texte est vide, on vide le listWidget
    if (arg1.isEmpty()) {
        qDebug() << "Le texte est vide, on vide la liste.";
        ui->listWidget->clear();
        return;
    }

    // Appeler la méthode rechercher pour obtenir les résultats
    qDebug() << "Appel de la méthode rechercher avec la valeur:" << arg1;
    personel personel;
    QSqlQueryModel* model = personel.rechercher_sug(arg1);

    // Vider le listWidget avant d'ajouter les nouvelles suggestions
    ui->listWidget->clear();

    // Vérifier le nombre de résultats
    qDebug() << "Nombre de résultats trouvés:" << model->rowCount();

    // Ajouter les résultats au listWidget
    for (int row = 0; row < model->rowCount(); ++row) {
        QString id = model->data(model->index(row, 0)).toString(); // Première colonne = ID
        QString nom = model->data(model->index(row, 1)).toString(); // Deuxième colonne = NOM
        QString poste = model->data(model->index(row, 2)).toString(); // Troisième colonne = POSTE

        // Créer une suggestion combinée avec ID, NOM et POSTE
        QString suggestion = id + " - " + nom + " - " + poste;

        // Ajouter la suggestion au listWidget
        qDebug() << "Ajouter une suggestion:" << suggestion;
        ui->listWidget->addItem(suggestion);
    }
}




/*void MainWindow::on_boutton_statitque_clicked()
{
    qDebug() << "Bouton statistique cliqué !"; // Vérifie que le slot est bien appelé

    // Récupérer les statistiques depuis la classe 'personel'
    personel p;
    QMap<QString, double> stats = p.statistiquesPourcentageSalaire();

    // Vérifier si des données sont disponibles
    if (stats.isEmpty()) {
        qDebug() << "Aucune donnée à afficher dans le graphique.";
        return; // Ne rien afficher si les données sont vides
    }

    // Créer une série pour le graphique en camembert
    QPieSeries *series = new QPieSeries();

    // Couleurs pour les tranches
    QColor green1 = QColor(0, 128, 0);       // Dark green
    QColor green2 = QColor(60, 179, 113);   // Forest green
    QColor green3 = QColor(144, 238, 144); // Light green

    // Remplir la série avec les données
    int index = 0;
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        QPieSlice *slice = series->append(it.key(), it.value());

        // Attribuer une couleur en fonction de l'index
        switch (index % 3) {
            case 0: slice->setColor(green1); break;
            case 1: slice->setColor(green2); break;
            case 2: slice->setColor(green3); break;
        }

        // Rendre les labels visibles avec le pourcentage
        slice->setLabelVisible(true);
        slice->setLabel(QString("%1: %2%")
                            .arg(it.key())
                            .arg(it.value(), 0, 'f', 1));

        index++;
    }

    // Créer le graphique et ajouter la série
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des employés par tranche de salaire");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Créer une vue pour le graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing); // Améliorer le rendu graphique

    // Configurer la vue graphique
    QGraphicsScene *scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scene()->addWidget(chartView);
    ui->graphicsView->fitInView(chartView->sceneRect(), Qt::KeepAspectRatio);

    // Afficher la scène
    ui->graphicsView->scene()->update();
    ui->graphicsView->show();

    qDebug() << "Graphique affiché avec succès.";
}


*/



void MainWindow::on_boutton_statitque_clicked()//stat
{
    personel p;
    QMap<QString, double> stats = p.statistiquesPourcentageSalaire();

    // Créer une série de secteurs pour le graphique en camembert
    QPieSeries *series = new QPieSeries();

    // Définir quelques couleurs pour les secteurs
    QColor green1 = QColor(0, 128, 0); // Dark green
    QColor green2 = QColor(60, 179, 113); // Forest green
    QColor green3 = QColor(144, 238, 144); // Light green

    int index = 0;
    // Ajouter des secteurs pour chaque tranche de salaire
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        QPieSlice *slice = series->append(it.key(), it.value());

        // Appliquer une couleur différente pour chaque secteur
        switch (index % 3) {
            case 0: slice->setColor(green1); break;
            case 1: slice->setColor(green2); break;
            case 2: slice->setColor(green3); break;
        }

        // Afficher le pourcentage sur le graphique
        slice->setLabelVisible(true);
        slice->setLabel(QString("%1: %2%").arg(slice->label()).arg(slice->percentage() * 100, 0, 'f', 1));

        index++;
    }

    // Créer un graphique et ajouter la série des secteurs
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition en pourcentage des employés par tranche de salaire");

    // S'assurer que le graphique est circulaire et centré
    chart->setAnimationOptions(QChart::SeriesAnimations);  // Animation pour adoucir les transitions

    // Créer une vue de graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing); // Activer l'anticrénelage pour des visuels plus nets

    // Configurer la taille du graphique, mais s'assurer qu'il est bien circulaire
    chartView->setFixedSize(600, 600); // Taille fixée pour qu'il soit bien circulaire (carré)

    // Ajouter la vue à un layout et l'afficher dans le QGraphicsView
    ui->graphicsView->setScene(new QGraphicsScene());
    ui->graphicsView->scene()->addWidget(chartView);

    // Ajuster automatiquement le graphique pour qu'il soit bien centré et visible
    ui->graphicsView->fitInView(chartView->sceneRect(), Qt::KeepAspectRatio);

    // Rafraîchir l'affichage
    ui->graphicsView->scene()->update();
    ui->graphicsView->show();
}









void MainWindow::on_modifier_3_clicked()//conge
{
    qDebug() << "on_modifier_3_clicked called";

      // Vérifier si la fenêtre de congé est déjà ouverte
      for (QObject *child : this->children()) {
          if (QWidget *widget = qobject_cast<QWidget *>(child)) {
              qDebug() << "Checking child widget: " << widget->objectName();
              if (widget->objectName() == "CalendrierConge") {
                  widget->show(); // Si déjà ouvert, simplement l'afficher
                  return;
              }
          }
      }

      // Si pas ouvert, créer et afficher la fenêtre CalendrierConge
      qDebug() << "Opening new CalendrierConge window";
      CalendrierConge *calendrierConge = new CalendrierConge(this);
      calendrierConge->setObjectName("CalendrierConge");  // Assurez-vous que le nom est attribué après la création de l'objet

      // Forcer la taille et la position
      calendrierConge->resize(500, 400);
      calendrierConge->move(100, 100); // Placer la fenêtre à une position visible sur l'écran
      calendrierConge->show();
}
////////////////////////////////////////////////////
void MainWindow::exportTableViewToPDF(QTableView *tableView) {
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save as PDF", "", "PDF Files (*.pdf);;All Files (*)");
    if (fileName.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageOrientation(QPageLayout::Portrait);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    painter.drawText(1000,10,"lise des equipement");
    QAbstractItemModel *model = tableView->model();

    int x = 10;
    int y = 30;
    int rowHeight = 100;
    int columnWidth = 200;

    // Set up font for the PDF
    QFont font = painter.font();
    font.setPointSize(5);
    painter.setFont(font);
    //QPainter painter(&pdfWriter);
    // painter.setBrush(QColor(220,198,250));
    // Draw column headers
    for (int column = 0; column < model->columnCount(); ++column) {
        QRect rect(x + column * columnWidth, y, columnWidth, rowHeight);
        painter.setBrush(QColor(220, 198, 250));
        painter.drawRect(rect); // Fill with purple
        painter.setBrush(Qt::NoBrush); // Reset brush for text
        painter.drawText(rect, Qt::AlignCenter, model->headerData(column, Qt::Horizontal).toString());
    }

    // Draw rows
    for (int row = 0; row < model->rowCount(); ++row) {
        QColor rowcolor =(row%2 ==0) ? QColor(240,240,240):QColor(255,255,255);
        for (int column = 0; column < model->columnCount(); ++column) {
            QRect rect(x + column * columnWidth, y + (row + 1) * rowHeight, columnWidth, rowHeight);
            painter.setBrush(rowcolor);
            painter.drawRect(rect);

            painter.setBrush(Qt::NoBrush);
            painter.drawText(rect, Qt::AlignCenter, model->data(model->index(row, column)).toString());

        }
    }

    painter.end();
    QMessageBox::information(nullptr, "Export Complete", "Data has been exported to PDF successfully.");
}
//////// ////////////////////////////////////word////////////////////////////////////////
void MainWindow::exportTableViewToWord(QTableView *tableView) {
    QString fileName = QFileDialog::getSaveFileName(this, "Save as Word Document", "", "Word Files (*.docx);;All Files (*)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Unable to open file", file.errorString());
        return;
    }

    QTextStream out(&file);
    QAbstractItemModel *model = tableView->model();

    // Write headers
    for (int column = 0; column < model->columnCount(); ++column) {
        out << model->headerData(column, Qt::Horizontal).toString() << "\t";
    }
    out << "\n";

    // Write data rows
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int column = 0; column < model->columnCount(); ++column) {
            out << model->data(model->index(row, column)).toString() << "\t";
        }
        out << "\n";
    }

    file.close();
    QMessageBox::information(this, "Export Complete", "Data has been exported to Word successfully.");
}
/////////////////////////////////////////////////////////////////////////////////////////
/*void MainWindow::exportTableViewToExcel(QTableView *tableView) {
    QAxObject *excel = new QAxObject("Excel.Application");
    excel->setProperty("Visible", false);
    QAxObject *workbook = excel->querySubObject("Workbooks")->querySubObject("Add");
    QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

    QAbstractItemModel *model = tableView->model();

    // Write headers
    for (int column = 0; column < model->columnCount(); ++column) {
        QAxObject *cell = worksheet->querySubObject("Cells(int,int)", 1, column + 1);
        cell->setProperty("Value", model->headerData(column, Qt::Horizontal).toString());
    }

    // Write data rows
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int column = 0; column < model->columnCount(); ++column) {
            QAxObject *cell = worksheet->querySubObject("Cells(int,int)", row + 2, column + 1);
            cell->setProperty("Value", model->data(model->index(row, column)).toString());
        }
    }

    workbook->dynamicCall("SaveAs(const QString&)", QFileDialog::getSaveFileName(this, "Save as Excel File", "", "Excel Files (*.xlsx);;All Files (*)"));
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
    QMessageBox::information(this, "Export Complete", "Data has been exported to Excel successfully.");
}*/



void MainWindow::on_pushButton_22_clicked()
{

    int id_eq = ui->id_equipement->text().toInt();
    //e.setid(id_eq);
    QString nom = ui->nom_e->text();
    //e.setnom(nom);
    QString categorie = ui->categorie_2->text();
    //e.setcategorie(categorie);
    QString etat = ui->etat_eq->text();
    //e.setetat(etat);
    // QString date_aq_text = ui->date_aquesition->text();
    QDate Date_aq = ui->dateEdit->date();
    //e.setdatea(Date_aq);

    //QString date_d_text=ui->date_dm->text();
    QDate Date_D= ui->dateEdit_2->date();
    //e.setdated(Date_D);

    // QString date_p_text=ui->date_pm->text();
    QDate Date_P=ui->dateEdit_3->date();
    //e.setdatep(Date_P);
    QString fournisseur = ui->fourniseureq->text();
    //e.setfournisseur(fournisseur);
    QString localisation = ui->localisation_eq->text();
    //e.setlocalisation(localisation);
    double prix = ui->prix->text().toDouble();
    //e.setprix(prix);
    QString parametre_M = ui->comboBox_11->currentText();
    //e.setparametre(parametre_M);
    equipement e(id_eq,nom,categorie,etat,fournisseur,localisation,parametre_M,Date_D,Date_P,Date_aq,prix);


    /*if (nom.isEmpty() || categorie.isEmpty() || etat.isEmpty() ||
          fournisseur.isEmpty() || localisation.isEmpty() ||
        prix <= 0 || parametre_M.isEmpty()) {
        QMessageBox::warning(this, "Error", "All fields must be filled correctly.");
        return;
    }*/
    ////////ajout////////////

    if (e.ajouter()){
        ui->tableView_2->setModel(e.afficher());
        e.populateComboBoxE(ui->comboBox_12);
        e.populateComboBoxP(ui->comboBox_14);
        clear();
        QMessageBox::information(this, "Success", "Equipment added successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to add equipment.");
    }


}
///////////suppression//////////////
void MainWindow::on_pushButton_25_clicked()
{
    int id;
    if (ui->id_equipement->text().isEmpty()) {
        id = ui->lineEdit_5->text().toInt();
    } else {
        id = ui->id_equipement->text().toInt();
    }

    if (e.supprimer(id)) {

        ui->tableView_2->setModel(e.afficher());


        QMessageBox::information(this, "Success", "Equipment deleted successfully.");
    } else {

        QMessageBox::warning(this, "Error", "Failed to delete equipment.");
    }

}

void MainWindow::on_pushButton_24_clicked()
{
    int id;
    if (ui->id_equipement->text().isEmpty()) {
        id = ui->lineEdit_5->text().toInt();
    } else {
        id = ui->id_equipement->text().toInt();
    }
    //e.setid(id);
    QString nom = ui->nom_e->text();
    //e.setnom(nom);
    QString categorie = ui->categorie_2->text();
    //e.setcategorie(categorie);
    QString etat = ui->etat_eq->text();
    //e.setetat(etat);
    // QString date_aq_text = ui->date_aquesition->text();
    QDate Date_aq =ui->dateEdit->date();
    // e.setdatea(Date_aq);

    //QString date_d_text=ui->date_dm->text();
    QDate Date_D= ui->dateEdit_2->date();
    //e.setdated(Date_D);

    //QString date_p_text=ui->date_pm->text();
    QDate Date_P=ui->dateEdit_3->date();
    //e.setdatep(Date_P);
    QString fournisseur = ui->fourniseureq->text();
    //e.setfournisseur(fournisseur);
    QString localisation = ui->localisation_eq->text();
    //e.setlocalisation(localisation);
    double prix = ui->prix->text().toDouble();
    //e.setprix(prix);
    QString parametre_M = ui->comboBox_11->currentText();
    //e.setparametre(parametre_M);
    equipement e(id,nom,categorie,etat,fournisseur,localisation,parametre_M,Date_D,Date_P,Date_aq,prix);
    if (e.modifier(id)) {

        ui->tableView_2->setModel(e.afficher());
        clear();

        QMessageBox::information(this, "Success", "Equipment modified successfully.");
    } else {

        QMessageBox::warning(this, "Error", "Failed to modify equipment.");
    }

}




void MainWindow::on_lineEdit_5_textChanged()
{
    QString partialId = ui->lineEdit_5->text();

    QSqlQueryModel* model = e.rechercherpanom(partialId);
    if (model) {
        ui->tableView_2->setModel(model);
    } else {
        QMessageBox::warning(this, "Error", "Search failed.");
    }

}
void MainWindow::on_comboBox_5_currentIndexChanged()
{
    QString methode = ui->comboBox_5->currentText();


    bool descending = ui->checkBox->isChecked();


    QSqlQueryModel* model = e.trier(methode, descending);


    ui->tableView_2->setModel(model);
}
void MainWindow::on_pushButton_23_clicked()
{
    QString exportFormat = ui->comboBox_10->currentText();

    if (exportFormat == "pdf") {
        exportTableViewToPDF(ui->tableView_2);
    } else if (exportFormat == "word") {
        exportTableViewToWord(ui->tableView_2);
        // } else if (exportFormat == "Excel") {
        //    exportTableViewToExcel(ui->tableView);
    } else {
        QMessageBox::warning(this, "Export", "Invalid export format selected.");
    }

}
void MainWindow::clear()
{

    ui->lineEdit_5->clear();
    ui->id_equipement->clear();
    ui->nom_e->clear();
    ui->categorie_2->clear();
    ui->etat_eq->clear();
    ui->dateEdit->clear();
    ui->dateEdit_2->clear();
    ui->dateEdit_3->clear();
    ui->fourniseureq->clear();
    ui->localisation_eq->clear();
    ui->prix->clear();
    // ui->comboBox_11->clear();

}
void MainWindow::on_pushButton_3_clicked()
{
    int id = ui->lineEdit_6->text().toInt();
    //e.generate_text_file(id);
    if (!e.generateQRCodeForId(id).isNull()) {

        ui->label_22->setPixmap(QPixmap::fromImage(e.generateQRCodeForId(id)));
    } else {
        qDebug() << "Failed to generate QR code for ID:" << id;
    }
    ui->label_22->setScaledContents(true);
    QString filePath = QString("C:/Users/mehdi/Documents/QRcodeimage/QRCode_%1.png").arg(id);
    if (e.generateQRCodeForId(id).save(filePath)) {
        qDebug() << "QR code saved successfully at:" << filePath;
    } else {
        qDebug() << "Failed to save QR code.";
    }
    /*QString scannedData = QString("{\"id\": %1}").arg(id);
    // e.generateQRCodeForId(id).save("qr_code.png");
     QJsonDocument doc = QJsonDocument::fromJson(scannedData.toUtf8());
     if (doc.isObject()) {
         QJsonObject jsonObj = doc.object();
         if (jsonObj.contains("id")) {
             int equipmentId = jsonObj["id"].toInt();
             qDebug() << "Scanned equipment ID:" << equipmentId;

             // Now generate the file based on the equipment ID
             e.generateTextFileFromQRCode(id);
         }
     }*/
}

/*void MainWindow::on_pushButton_4_clicked()
{


    QProcess *process = new QProcess(this);


    QString pythonPath = "C:\\Users\\mehdi\\AppData\\Local\\Programs\\Python\\Python313\\python.exe";
    QString scriptPath ="C:\\Users\\mehdi\\Documents\\rendu1009\\script1.py";


    process->start(pythonPath, QStringList() << scriptPath);


    if (!process->waitForStarted()) {
        qDebug() << "Error starting Python script!";
        return;
    }

    connect(process, &QProcess::readyReadStandardOutput, this, [process, this]() {
        QByteArray result = process->readAllStandardOutput();
        QString qrData = QString(result).trimmed();

        ui->label_3->setText(qrData);
        qDebug() << "Python script output:" << result;

    });


    connect(process, &QProcess::readyReadStandardError, this, [process]() {
        QByteArray errorOutput = process->readAllStandardError();
        qDebug() << "Python script error output:" << errorOutput;
    });

}*/
void MainWindow::on_pushButton_clicked()
{
    int id=ui->lineEdit_7->text().toInt();
    ui->label_16->setText(e.diagnostic(id));
    ui->label_17->setText(e.reparation(id));
}

void MainWindow::createChart(){
    // Step 1: Get data from the model (your tableview model)
    QAbstractItemModel *model = ui->tableView_2->model();
    if (!model) {
        QMessageBox::warning(this, "Error", "No data available.");
        return;
    }

    int rowCount = model->rowCount();
    if (rowCount == 0) {
        QMessageBox::warning(this, "Error", "No equipment data to display.");
        return;
    }

    // Step 2: Collect and count equipment names
    QMap<QString, int> equipmentCount;
    for (int row = 0; row < rowCount; ++row) {
        QString name = model->data(model->index(row, 1)).toString(); // Assuming the name is in column 0
        equipmentCount[name]++;
    }


    QList<QPair<QString, int>> sortedEquipment;
    for (auto it = equipmentCount.begin(); it != equipmentCount.end(); ++it) {
        sortedEquipment.append(qMakePair(it.key(), it.value()));
    }

    std::sort(sortedEquipment.begin(), sortedEquipment.end(), [](const QPair<QString, int> &a, const QPair<QString, int> &b) {
        return a.second > b.second;
    });


    QBarSet *set = new QBarSet("Equipment Count");
    QStringList categories;

    int topCount = qMin(5, sortedEquipment.size()); // Limit to top 5
    for (int i = 0; i < topCount; ++i) {
        *set << sortedEquipment[i].second;  // Add count to the bar set
        categories << sortedEquipment[i].first;  // Add name to categories
    }

    QBarSeries *series = new QBarSeries();
  //  series->append(set);

    // Step 5: Create the chart
    QChart *chart = new QChart();
   // chart->addSeries(series);
    chart->setTitle("Top 5 Most Frequent Equipment");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Step 6: Set up the axes
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
   // chart->addAxis(axisX, Qt::AlignBottom);
  //  series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
   // axisY->setTitleText("Count");
  //  chart->addAxis(axisY, Qt::AlignLeft);
   // series->attachAxis(axisY);

    // Step 7: Display the chart in a QChartView
    QChartView *chartView = new QChartView(chart);
  //  chartView->setRenderHint(QPainter::Antialiasing);

    // Step 8: Check if the chart already exists in the tab and remove it if so
    for (int i = 0; i < ui->tabWidget_7->count(); ++i) {
        if (ui->tabWidget_7->tabText(i) == "statistique") {
            ui->tabWidget_7->removeTab(i);
            break;
        }
    }

    // Step 9: Add the chart view to a new tab and display it
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);
  //  layout->addWidget(chartView);
    tab->setLayout(layout);

    // Set a fixed size for the tab widget
    tab->setMinimumSize(500, 400); // You can adjust this as needed

    // Add the new tab to the tab widget
    ui->tabWidget_7->addTab(tab, "statistique");
    ui->tabWidget_7->setCurrentWidget(tab);

    // Step 10: Optional - Ensure chart view resizes properly
 //   chartView->setRenderHint(QPainter::Antialiasing);
 //   chartView->setMinimumSize(500, 400); // Adjust size as needed

}
void MainWindow::on_pushButton_5_clicked(){


    createChart();
}
/////////////////////////////////////////////////


void MainWindow::on_pushButton_2_clicked()
{
    QString nomE=ui->comboBox_12->currentText();
    QString nomP= ui->comboBox_14->currentText();
    QDate date = ui->dateEdit_5->date();
    if (e.affecter(nomE, nomP, date)) {
        ui->tableView_3->setModel(e.afficherAffectation());
        QMessageBox::information(this, "Success", "Assignment added successfully!");

        return;
    }


     QMessageBox::information(this, "Duplicate Assignment", "This assignment already exists.");
}


void MainWindow::on_pushButton_9_clicked()
{


    QString nomE = ui->comboBox_12->currentText();
    QString nomP= ui->comboBox_14->currentText();



        if (e.supprimeraffectation(nomE,nomP)) {
            QMessageBox::information(this, "Success", "Equipment deleted successfully!");
            ui->tableView_3->setModel(e.afficherAffectation());
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete the equipment. Ensure it exists.");
        }


}


void MainWindow::on_pushButton_6_clicked()
{
    QString nomE=ui->comboBox_15->currentText();
    QString nomP= ui->comboBox_13->currentText();
    QDate date = ui->dateEdit_6->date();
    if (p.affecter(nomE, nomP, date)) {
        ui->tableView_4->setModel(p.afficherAffectation());
        QMessageBox::information(this, "Success", "Assignment added successfully!");

        return;
    }


    QMessageBox::information(this, "Duplicate Assignment", "This assignment already exists.");

}


void MainWindow::on_pushButton_26_clicked()
{
    QString nomE = ui->comboBox_15->currentText();
    QString nomP= ui->comboBox_13->currentText();



    if (p.supprimeraffectation(nomE,nomP)) {
        QMessageBox::information(this, "Success", "Equipment deleted successfully!");
        ui->tableView_4->setModel(p.afficherAffectation());
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete the equipment. Ensure it exists.");
    }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////
























void MainWindow::on_pushButton_10_clicked() {
    // Récupération des données des champs
    QString idText = ui->id_client->text().trimmed();
    QString nomcl = ui->nom1_2->text().trimmed();
    QString prenomcl = ui->prenom1_2->text().trimmed();
    QString emailcl = ui->email_2->text().trimmed();
    QString adressecl = ui->adresse->text().trimmed();

    // Validation des données
    if (idText.isEmpty() || nomcl.isEmpty() || prenomcl.isEmpty() || emailcl.isEmpty() || adressecl.isEmpty()) {
        QMessageBox::warning(this, "Champs vides", "Veuillez remplir tous les champs.");
        return;
    }

    bool idOk;
    int idcl = idText.toInt(&idOk);
    if (!idOk) {
        QMessageBox::warning(this, "Erreur ID", "L'identifiant doit être un entier valide.");
        return;
    }

    // Vérification format email
    QRegularExpression regexEmail("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$");
    if (!regexEmail.match(emailcl).hasMatch()) {
        QMessageBox::warning(this, "Erreur Email", "Veuillez entrer une adresse email valide.");
        return;
    }

    // Ajout du client
    Client C(idcl, nomcl, prenomcl, emailcl, adressecl);
    if (C.ajouter()) {
        ui->tableView_5->setModel(Etmp.afficher()); // Actualisation du tableau
        QMessageBox::information(this, "Succès", "Client ajouté avec succès.");
        resetFields(); // Réinitialiser les champs
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout du client.");
    }
}























void MainWindow::on_pushButton_12_clicked() //modifierclient
{
    int idcl = ui->id_client->text().toInt();
    if (idcl == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer l'ID du client à modifier.");
        return;
    }

    // Retrieve values from fields
    QString nomcl = ui->nom1_2->text();
    QString prenomcl = ui->prenom1_2->text();
    QString emailcl = ui->email_2->text();
    QString adressecl = ui->adresse->text();



    // Create Client object with only the ID
    Client client(idcl);

    // Call modifierClient to update the fields that are not empty
    bool success = client.modifierClient(idcl, nomcl, prenomcl, emailcl, adressecl);

    // Handle success or failure
    if (success) {
        ui->tableView_5->setModel(Etmp.afficher());  // Refresh the view
        QMessageBox::information(this, "Succès", "Client modifié avec succès !");
    } else {
        QMessageBox::warning(this, "Erreur", "La modification a échoué.");
    }

    resetFields();  // Reset fields after update
}


void MainWindow::on_pushButton_13_clicked() {
    int idcl = ui->id_client->text().toInt();
    bool test = Etmp.supprimer(idcl);
    if (test) {
        ui->tableView_5->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"), QObject::tr("Suppression effectuée\nClick cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"), QObject::tr("Suppression non effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index) {
    if (!index.isValid()) {
        qDebug() << "Index non valide.";
        return;
    }

    // Récupérer l'ID du client à partir du modèle de la table
    int idcl = ui->tableView_5->model()->data(ui->tableView_5->model()->index(index.row(), 0)).toInt();

    // Créer une boîte de dialogue pour demander si l'utilisateur veut modifier ou supprimer
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Action sur le client");
    msgBox.setText("Voulez-vous modifier ou supprimer ce client ?");

    // Ajouter des boutons personnalisés
    QPushButton *modifierButton = msgBox.addButton("Modifier", QMessageBox::YesRole);
    QPushButton *supprimerButton = msgBox.addButton("Supprimer", QMessageBox::NoRole);
    QPushButton *annulerButton = msgBox.addButton("Annuler", QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == modifierButton) {
        // Appeler la méthode de modification
        on_pushButton_12_clicked(); // L'appel ici pour déclencher la modification

    } else if (msgBox.clickedButton() == supprimerButton) {
        Client client;
        bool success = client.supprimer(idcl);
        if (success) {
            ui->tableView_5->setModel(Etmp.afficher());
            QMessageBox::information(this, "Succès", "Client supprimé de la base de données !");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression du client.");
        }
    } else if (msgBox.clickedButton() == annulerButton) {
        qDebug() << "Action annulée.";
    }
}



void MainWindow::resetFields() {

    // Remplacez ces noms par les identifiants de vos QLineEdit
    ui->id_client->clear();
    ui->nom1_2->clear();
    ui->prenom1_2->clear();
    ui->email_2->clear();
    ui->adresse->clear();


}

void MainWindow::on_charger_clicked()
{
    // Récupérer l'ID client depuis le QLineEdit
    int idClient = ui->id_client->text().toInt(); // ID du client saisi dans QLineEdit

    // Créer un objet Client avec l'ID
    Client client(idClient);

    // Créer une requête pour récupérer les informations du client depuis la base de données
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT WHERE IDCL = :id"); // Remplacez 'CLIENT' par votre nom de table réel
    query.bindValue(":id", idClient);

    if (query.exec()) {
        // Si la requête a réussi, vérifier si un client avec cet ID existe
        if (query.next()) {
            // Récupérer les données du client
            QString nom = query.value("NOMCL").toString();
            QString prenom = query.value("PRENOMCL").toString();
            QString email = query.value("EMAILCL").toString();
            QString adresse = query.value("ADRESSECL").toString();



            // Assigner les données récupérées à l'objet Client
            client.setnomcl(nom);
            client.setprenomcl(prenom);
            client.setemailcl(email);
            client.setadressecl(adresse);



            // Remplir les QLineEdit avec les données du client
            ui->nom1_2->setText(client.getnomcl());
            ui->prenom1_2->setText(client.getprenomcl());
            ui->email_2->setText(client.getemailcl());
            ui->adresse->setText(client.getadressecl());


        } else {
            // Si aucun client n'a été trouvé avec cet ID
            QMessageBox::warning(this, "Erreur", "Aucun client trouvé avec cet ID.");
        }
    } else {
        // Si la requête échoue
        QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
    }
}

void MainWindow::on_comboBox_2_activated(int index) {
    QString colonne;
    QString direction;

    // Déterminer la colonne et la direction en fonction de l'index sélectionné
    switch (index) {
    case 1:  // Trier par nom de A à Z
        colonne = "CLIENT.NOMCL";
        direction = "ASC";
        break;
    case 2:  // Trier par nom de Z à A
        colonne = "CLIENT.NOMCL";
        direction = "DESC";
        break;
    case 3:  // Trier par ID croissant
        colonne = "CLIENT.IDCL";
        direction = "ASC";
        break;
    case 4:  // Trier par ID décroissant
        colonne = "CLIENT.IDCL";
        direction = "DESC";
        break;
    case 5:  // Trier par date décroissante uniquement
        colonne = "PASSER.DATECL";
        direction = "DESC";
        break;
    default:  // Par défaut, tri par ID croissant
        colonne = "CLIENT.IDCL";
        direction = "ASC";
        break;
    }

    // Construire la requête SQL pour trier uniquement
    QString queryString = QString(
                              "SELECT CLIENT.IDCL, CLIENT.NOMCL, CLIENT.PRENOMCL, "
                              "CLIENT.EMAILCL, CLIENT.ADRESSECL, PASSER.DATECL "
                              "FROM CLIENT "
                              "INNER JOIN PASSER ON CLIENT.IDCL = PASSER.IDCL "
                              "ORDER BY %1 %2"
                              ).arg(colonne, direction);

    // Exécuter la requête
    QSqlQuery query;
    query.prepare(queryString);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Impossible de trier les données : " + query.lastError().text());
        return;
    }

    // Mettre à jour uniquement les données triées dans tableView_2
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);

    // Définir les en-têtes de colonnes comme actuellement
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDCL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMCL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOMCL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAILCL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSECL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATECL"));

    // Appliquer le modèle trié au tableView_2
    ui->tableView_5->setModel(model);
}






void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    QString partialId = ui->lineEdit_2->text();  // Assurez-vous que le texte est correctement récupéré

    // Si le champ de recherche est vide, ne pas effectuer de recherche
    QSqlQueryModel *model=Etmp.rechercher(partialId);
    if (model) {
        ui->tableView_5->setModel(model);  // Si rien n'est recherché, on vide le modèle de la table

    }

    // Si le texte a changé, on arrête le timer et on redémarre pour une nouvelle recherche après le délai
 //searchTimer->stop();
   // searchTimer->start();  // Démarre le timer pour attendre un délai avant la recherche
}

/*void MainWindow::on_searchTimeout()
{
    QString partialId = ui->lineEdit_2->text().trimmed();

    // Si le champ de recherche est toujours non vide, effectuer la recherche
    if (!partialId.isEmpty()) {
        QSqlQueryModel* model = Etmp.rechercher(partialId);
        if (model) {
            ui->tableView_5->setModel(model);
        } else {
            QMessageBox::warning(this, "Error", "Search failed.");
        }
    }
}*/
















void MainWindow::on_pushButton_34_clicked() {
    // Préparer la requête SQL pour obtenir les statistiques par jour
    QSqlQuery query;
    query.prepare(R"(
        SELECT
            TO_CHAR("DATECL", 'Day') AS "Jour",
            COUNT(*) AS "Nombre_Commandes"
        FROM
            "PASSER"
        GROUP BY
            TO_CHAR("DATECL", 'Day')
        ORDER BY
            COUNT(*) DESC
    )");

    if (query.exec()) {
        // Créer une série pour le graphique en barres
        QBarSeries *series = new QBarSeries();

        // Préparer les données
        QStringList categories; // Catégories (jours)
        QBarSet *set = new QBarSet("Nombre de commandes");

        int maxValue = 0; // Variable pour suivre la valeur maximale

        while (query.next()) {
            QString day = query.value("Jour").toString().simplified(); // Nom du jour
            int count = query.value("Nombre_Commandes").toInt();

            // Ajouter les données au graphique
            *set << count;
            categories << day;

            // Mettre à jour la valeur maximale
            if (count > maxValue) {
                maxValue = count;
            }
        }

        // Ajouter les données à la série
        series->append(set);

        // Créer un axe X avec les catégories (jours)
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);

        // Créer un axe Y pour les valeurs (nombre de commandes)
        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Nombre de commandes");
        axisY->setLabelFormat("%d");
        axisY->setRange(0, maxValue + 5); // Ajouter une marge au maximum

        // Créer le graphique
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques des commandes par jour");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        // Ajouter les axes au graphique
        chart->addAxis(axisX, Qt::AlignBottom);
       chart->addAxis(axisY, Qt::AlignLeft);
       series->attachAxis(axisX);
           series->attachAxis(axisY);

        // Afficher la légende
       chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        // Créer un QChartView pour afficher le graphique
        QChartView *chartView = new QChartView(chart);
   chartView->setRenderHint(QPainter::Antialiasing);

        // Afficher le graphique dans un conteneur (par exemple, un QVBoxLayout dans `groupBox_11`)
        QLayout *layout = ui->groupBox_11->layout();
        if (layout) {
            // Nettoyer les anciens widgets
            QLayoutItem *item;
            while ((item = layout->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
        } else {
            layout = new QVBoxLayout(ui->groupBox_11);
            ui->groupBox_11->setLayout(layout);
        }

      layout->addWidget(chartView);

        // Rendre visible le groupBox_11
        ui->groupBox_11->setVisible(true);
    } else {
        // Gérer les erreurs SQL
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer les statistiques : " + query.lastError().text());
    }
}





void MainWindow::on_pushButton_35_clicked() //historique
{
    // Créer un modèle pour afficher les résultats de la requête
    QSqlQueryModel *model = new QSqlQueryModel(this);

    // Préparer la requête SQL pour récupérer les informations souhaitées
    QSqlQuery query;
    query.prepare(
        "SELECT C.IDCL AS \"ID Client\", C.NOMCL AS \"Nom\", C.PRENOMCL AS \"Prénom\", "
        "TO_CHAR(P.DATECL, 'YYYY-MM-DD HH24:MI:SS') AS \"Date et Heure d'ajout\" "
        "FROM CLIENT C "
        "JOIN PASSER P ON C.IDCL = P.IDCL "
        "ORDER BY C.IDCL ASC"
        );

    // Exécuter la requête
    if (query.exec()) {
        // Assigner le modèle avec les résultats de la requête SQL
        model->setQuery(query);

        // Vérifier si la requête a retourné des résultats
        if (model->rowCount() > 0) {
            // Affecter le modèle à la vue tableView_3
            ui->tableView_7->setModel(model);

            // Ajuster la taille des colonnes
            ui->tableView_7->resizeColumnsToContents();

            // Sélection par ligne
            ui->tableView_7->setSelectionBehavior(QAbstractItemView::SelectRows);

            // Sélection unique
            ui->tableView_7->setSelectionMode(QAbstractItemView::SingleSelection);

            // Étendre la dernière colonne pour remplir la vue
            ui->tableView_7->horizontalHeader()->setStretchLastSection(true);
        } else {
            // Si aucune donnée n'est récupérée, afficher un message
            QMessageBox::information(this, "Aucune donnée", "Aucun client trouvé.");
        }
    } else {
        // Si la requête échoue, afficher un message d'erreur
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer les données des clients : " + query.lastError().text());
    }
}




void MainWindow::on_pushButton_29_clicked() {
    // Définir le modèle pour le QTableView
    QSqlQueryModel *model = new QSqlQueryModel(this);

    // Requête SQL pour récupérer les clients fidèles
    QString query = R"(
        SELECT
            "IDCL" AS "ID Client",
            COUNT(*) AS "Nombre de Commandes",
            CASE
                WHEN COUNT(*) = 3 THEN '30%'
                WHEN COUNT(*) = 4 THEN '40%'
                WHEN COUNT(*) >= 5 THEN '50%'
                ELSE '0%'
            END AS "Points de Fidélité"
        FROM
            "PASSER"
        GROUP BY
            "IDCL"
        HAVING
            COUNT(*) >= 3
        ORDER BY
            COUNT(*) DESC;
    )";

    // Exécuter la requête et définir le modèle
    model->setQuery(query);

    // Vérifier les erreurs SQL
    if (model->lastError().isValid()) {
        qDebug() << "Erreur SQL:" << model->lastError().text();
        return;
    }

    // Définir les en-têtes de colonne
    model->setHeaderData(0, Qt::Horizontal, "ID Client");
    model->setHeaderData(1, Qt::Horizontal, "Nombre de Commandes");
    model->setHeaderData(2, Qt::Horizontal, "Points de Fidélité");

    // Associer le modèle au QTableView
    ui->tableView_6->setModel(model);

    // Ajuster la taille des colonnes pour une meilleure visibilité
    ui->tableView_6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}








void MainWindow::on_exporter_clicked()
{
    // Ouvrir une boîte de dialogue pour choisir l'emplacement et le nom du fichier PDF
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer en tant que PDF", "", "Fichiers PDF (*.pdf);;Tous les fichiers (*)");
    if (fileName.isEmpty()) {
        return;
    }

    // Créer un QPdfWriter pour générer le PDF
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageOrientation(QPageLayout::Portrait);
    pdfWriter.setPageSize(QPageSize(QPageSize::A3)); // Augmenter la taille de la page à A3
    pdfWriter.setResolution(300);

    // Créer un QPainter pour dessiner dans le PDF
    QPainter painter(&pdfWriter);

    // Appliquer un fond de couleur vert clair à toute la page
    painter.setBrush(QBrush(QColor(144, 238, 144)));  // Vert clair en RGB
    painter.setPen(Qt::NoPen);  // Pas de bordure pour l'arrière-plan
    painter.drawRect(0, 0, pdfWriter.width(), pdfWriter.height());  // Dessiner le fond sur toute la page

    // Obtenir le modèle de données de la table
    QAbstractItemModel *model = ui->tableView_5->model();
    if (!model) {
        QMessageBox::warning(this, "Erreur", "Aucune donnée à exporter.");
        return;
    }

    int x = 20;   // Position X de départ (ajustée pour A3)
    int y = 250;   // Position Y de départ
    int rowHeight = 60;  // Hauteur des lignes (réduite)
    int columnWidth = 350;  // Largeur des colonnes (réduite pour mieux s'adapter à la page A3)

    // Définir une police plus petite pour le texte
    QFont font = painter.font();
    font.setPointSize(7);  // Réduire la taille de la police à 7 points pour améliorer la lisibilité
    painter.setFont(font);

    // Appliquer une couleur de fond pour l'en-tête des colonnes
    painter.setBrush(QBrush(Qt::darkGreen));  // Fond léger pour l'en-tête des colonnes
    painter.setPen(Qt::green);

    // Dessiner les en-têtes des colonnes
    for (int column = 0; column < model->columnCount(); ++column) {
        QRect rect(x + column * columnWidth, y, columnWidth, rowHeight);
        painter.drawRect(rect);  // Dessiner la bordure de la cellule
        painter.drawText(rect, Qt::AlignCenter, model->headerData(column, Qt::Horizontal).toString());
    }

    y += rowHeight;  // Déplacer la position Y après les en-têtes

    // Appliquer une couleur de fond différente pour chaque ligne de données
    painter.setBrush(QBrush(Qt::white));  // Fond blanc pour les lignes de données
    painter.setPen(QPen(Qt::black));  // Bordure noire

    // Identifier l'index de la colonne `idcl` et de la colonne numéro 9
    int idclColumnIndex = 0;  // Assurez-vous que cet index correspond à la colonne `idcl`
    int column9Index = 8;  // La colonne numéro 9 (en comptant à partir de 0)

    // Dessiner les lignes de données
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int column = 0; column < model->columnCount(); ++column) {
            QRect rect(x + column * columnWidth, y + (row) * rowHeight, columnWidth, rowHeight);

            // Colorer la colonne `idcl` en marron clair (RGB: 210, 180, 140)
            if (column == idclColumnIndex) {
                painter.setBrush(QBrush(QColor(210, 180, 140)));  // Marron clair
            }
            // Colorer la colonne numéro 9 en bleu ciel clair (RGB: 135, 206, 250)
            else if (column == column9Index) {
                painter.setBrush(QBrush(QColor(135, 206, 250)));  // Bleu ciel clair
            }
            else {
                painter.setBrush(QBrush(Qt::white));  // Autres colonnes en fond blanc
            }

            painter.drawRect(rect);  // Dessiner la bordure de la cellule
            painter.drawText(rect, Qt::AlignCenter, model->data(model->index(row, column)).toString());
        }
    }

    // Ajouter un titre ou un logo en haut du PDF
    painter.setPen(QPen(QColor(139, 69, 19)));  // Définir la couleur du texte en vert foncé (RGB: 0, 128, 0)
    font.setPointSize(24);  // Augmenter la taille du titre pour le haut du PDF
    painter.setFont(font);
    painter.drawText(960, 150, "Données Exportées:");  // Ajouter un titre

    // Ajouter un logo ou une image dans le coin supérieur droit
    //QPixmap logo("C:/Users/youss/Downloads/Gmail/logo.png");
   // painter.drawPixmap(3200, 0, 150, 150, logo);  // Dessiner l'image à une taille appropriée

    // Ajouter la "signature" en bas de la page (aligné à droite)
    QFont signatureFont("Bradley Hand ITC", 25);  // Utiliser une police cursive ou de signature
    painter.setFont(signatureFont);
    painter.setPen(QPen(QColor(0, 50, 0)));  // Une couleur de texte plus foncée pour la signature

    // Calculer la position de "Smart Conservation" en bas à droite de la page
    int signatureX = pdfWriter.width() - painter.fontMetrics().boundingRect("Smart Conservation").width() - 20;  // 20 pixels de marge à droite
    int signatureY = pdfWriter.height() - 50;  // Un peu au-dessus du bas de la page

    painter.drawText(signatureX, signatureY, "Smart Conservation");

    // Terminer l'impression
    painter.end();

    // Afficher un message de confirmation
    QMessageBox::information(this, "Exportation réussie", "Les données ont été exportées vers un fichier PDF avec succès.");
}

bool MainWindow::ajouterCommande(int idcl, int idc) {
    // Vérifier que idcl et idc sont des entiers valides
    if (idcl <= 0 || idc <= 0) {
        qDebug() << "Erreur : idcl ou idc invalide.";
        QMessageBox::warning(nullptr, "Erreur", "Les IDs doivent être des entiers valides.");
        return false;
    }

    // Préparer la requête pour insérer dans la table PASSER
    QSqlQuery query;
    query.prepare("INSERT INTO PASSER (IDCL, IDC, DATECL) VALUES (:idcl, :idc, SYSDATE)");

    // Lier les valeurs des champs IDCL et IDC
    query.bindValue(":idcl", idcl);  // Assurez-vous que idcl est bien un entier
    query.bindValue(":idc", idc);    // Assurez-vous que idc est bien un entier

    // Exécution de la requête
    if (!query.exec()) {
        qDebug() << "Erreur SQL lors de l'insertion de la commande :" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de l'enregistrement de la commande : " + query.lastError().text());
        return false;
    }

    qDebug() << "Commande insérée avec succès.";
    return true;
}




void MainWindow::on_pushButton_11_clicked() {
    // Récupération des données des champs
    QString idclText = ui->IDCL_c->text().trimmed();
    QString idcText = ui->IDC_c->text().trimmed();

    // Validation des données
    if (idclText.isEmpty() || idcText.isEmpty()) {
        QMessageBox::warning(this, "Champs vides", "Veuillez remplir tous les champs.");
        return;
    }

    bool idclOk, idcOk;
    int idcl = idclText.toInt(&idclOk);
    int idc = idcText.toInt(&idcOk);

    if (!idclOk || !idcOk) {
        QMessageBox::warning(this, "Erreur", "L'ID client et l'ID commande doivent être des entiers valides.");
        return;
    }

    // Appel à la méthode ajouterCommande pour insérer la commande
    if (ajouterCommande(idcl, idc)) {
        QMessageBox::information(this, "Succès", "Commande enregistrée avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'enregistrement de la commande.");
    }
}

//////////////////////////commande/////////////////////
void MainWindow::on_AjoutCo_clicked()
{
    int id=ui->id->text().toInt();

    QDate dateLivraison = ui->DL->date();
    int quantiteC = ui->QC->text().toInt();
    QDate dateCommande = ui->DC->date();
    QString etat = ui->Etat->currentText();


    Commande commande( id,dateLivraison, quantiteC, dateCommande, etat);


    bool test= commande.ajouter();
    if(test)
    {
        ui->Commandelist->setModel(CL.afficher());
        QMessageBox :: information(nullptr,QObject::tr("OK"),
                                  QObject::tr("Ajout effectuer\n"
                                              "click cancel to exit."),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_supco_clicked()
{
    int id=ui->idsup->text().toInt();

    bool test=CL.supprimer(id);

    if(test)
    {
        ui->Commandelist->setModel(CL.afficher());
        QMessageBox :: information(nullptr,QObject::tr("OK"),
                                  QObject::tr("suppresion effectuer\n"
                                              "click cancel to exit."),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                              QObject::tr("suppresion non effectué.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_18_clicked()
{


    int idam= ui->idam->text().toInt();
    int Quantite=ui->QCM->text().toInt();
    QDate datecommande=ui->DCM->date();
    QDate datelivr=ui->DLM->date();
    QString etat=ui->EtatM->currentText();

    bool test=CL.modifier(idam,datecommande,Quantite,datelivr,etat);
    if(test)
    {
        ui->Commandelist->setModel(CL.afficher());
        QMessageBox :: information(nullptr,QObject::tr("OK"),
                                  QObject::tr("modification effectuer\n"
                                              "click cancel to exit."),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                              QObject::tr("modification non effectué.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_Commandelist_activated(const QModelIndex &index)
{
    QString val = ui->Commandelist->model()->data(index).toString();
    QSqlQuery query;


    query.prepare("SELECT IDC, DATEC, QUANC, DATECL, ETAT FROM COMMANDE WHERE IDC=:val OR QUANC=:val OR ETAT=:val");
    query.bindValue(":val", val);


    if (query.exec()) {
        while (query.next()) {

            ui->idam->setText(query.value("IDC").toString());      // ID de la commande
            ui->DCM->setDate(query.value("DATEC").toDate());       // Date de la commande
            ui->QCM->setText(query.value("QUANC").toString()); // Quantité commandée
            ui->DLM->setDate(query.value("DATECL").toDate());  // Date de livraison
            ui->EtatM->setCurrentText(query.value("ETAT").toString()); // État de la commande

        }
        int currentIndex = ui->tabWidget->currentIndex(); // Récupérer l'index de l'onglet actuel
        ui->tabWidget->setCurrentIndex(currentIndex + 1);
    } else {

        QMessageBox::critical(this, tr("Error"), query.lastError().text());
    }


}

void MainWindow::on_chercherC_clicked()
{
    QString idString = ui->idsup->text().trimmed();
    int idToSearch = idString.toInt();
    QSqlQueryModel * searchResultsModel = new QSqlQueryModel();
    if (idString.isEmpty()) {

        searchResultsModel = CL.afficher();
    }
    else {

        QSqlQuery query;
        query.prepare("SELECT * from COMMANDE WHERE IDC = :IDC");
        query.bindValue(":IDC", idToSearch);

        if (query.exec()) {
            searchResultsModel->setQuery(query);
        } else {

            QMessageBox::critical(this, "Error", "Failed to execute the search query.");
        }
    }

    ui->Commandelist->setModel(searchResultsModel);
}


void MainWindow::on_statistique_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT ETAT, COUNT (*)AS  COMMANDE from COMMANDE GROUP BY ETAT");


    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête.";

        return;
    }

    QPieSeries *series = new QPieSeries();

    while (query.next()) {
        QString type = query.value("ETAT").toString();
        int count = query.value("COMMANDE").toInt();
        series->append(type, count);
    }


    foreach (QPieSlice *slice, series->slices()) {
        QString label = QString("%1 (%2%)")
        .arg(slice->label())
            .arg(100 * slice->percentage(), 0, 'f', 1);
        slice->setLabel(label);
    }


    QChart *chart = new QChart();
  //  chart->addSeries(series);
    chart->setTitle("Statistics du client selon l'eat");


    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setAnimationOptions(QChart::AllAnimations);


    QChartView *chartView = new QChartView(chart);

   // chartView->setRenderHint(QPainter::Antialiasing);
  //  chartView->setMinimumSize(640, 480);
 //   chartView->show();

}



void MainWindow::on_exportpdf_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Enregistrer PDF"), "", tr("PDF Files (*.pdf)"));
    if (filePath.isEmpty()) {
        return; // L'utilisateur a annulé l'enregistrement
    }

    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    QPainter painter(&writer);

    // Définir la police et la taille
    QFont font("Arial", 12);
    painter.setFont(font);

    // Titre
    painter.drawText(3000, 0, "Liste des Commandes");
    painter.drawLine(100, 110, 500, 110); // Ligne sous le titre

    // Récupérer les données de la base de données
    QSqlQuery query("SELECT * FROM COMMANDE");
    int y = 130; // Position de départ pour écrire les données
    int margin = 50; // Marges

    while (query.next()) {
        // Récupérer les valeurs
        int idc = query.value("IDC").toInt();
        QString datecommande = query.value("DATEC").toString();
        int Quantite = query.value("QUANC").toInt();
        QString datelivraison = query.value("DATECL").toString();
        QString etat= query.value("ETAT").toString();


        // Écrire chaque champ sur une nouvelle ligne avec un en-tête
        painter.drawText(margin, y, QString(" Id commande: %1").arg(idc));
        y += 290; // Augmenter l'espacement entre Article ID et Nom
        painter.drawText(margin, y, QString("date de commande: %1").arg(datecommande));
        y += 290;
        painter.drawText(margin, y, QString("Quantite: %1").arg(Quantite));
        y += 290;
        painter.drawText(margin, y, QString("Date de livraison: %1").arg(datelivraison));
        y += 290;
        painter.drawText(margin, y, QString("etat: %1").arg(etat));
        y += 290;

        painter.drawLine(margin, y, 500, y); // Ligne de séparation entre les articles
        y += 290; // Espacement après la ligne de séparation

        // Vérifier si on dépasse la hauteur de la page
        if (y > writer.height() - 100) {
            painter.end();
            writer.newPage(); // Créer une nouvelle page si nécessaire
            painter.begin(&writer);
            painter.setFont(font); // Redéfinir la police
            y = 100; // Réinitialiser la position y
        }
    }

    painter.end();

    // Afficher un message de succès
    QMessageBox::information(this, tr("Succès"), tr("Les données ont été exportées vers le PDF avec succès."));
}

void MainWindow::on_pushButton_19_clicked()
{
    Commande c;
    double pourcentageEfficacite =c.calculerPourcentageEfficacite("C:/Users/Asus/OneDrive - ESPRIT/Bureau/ProjectsWork/ProjectsWork/bilan.html");

    if (pourcentageEfficacite != -1) {
        // Afficher le pourcentage d'efficacité dans une boîte de message
        QMessageBox::information(this, "Bilan d'efficacité",
                                 "Le pourcentage d'efficacité des livraisons est de " +
                                     QString::number(pourcentageEfficacite) + "%.",
                                 QMessageBox::Ok);
    }
}


void MainWindow::on_etatmodifier_clicked()
{
    int idC = ui->idmodetat->text().toInt();
    QSqlQuery query;
    query.prepare("UPDATE COMMANDE SET ETAT = 'livree', DATEMODIFICATION = SYSDATE WHERE IDC = :idC");
    query.bindValue(":idC", idC);  // Lier l'ID de la commande à la requête

    // Exécuter la requête et vérifier si elle réussit
    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour de l'état de la commande : " << query.lastError().text();
    } else {
        qDebug() << "État de la commande mis à jour avec succès.";
    }

}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1==""){
        ui->Commandelist->setModel(CL.afficher());}
    else{
        ui->Commandelist->setModel(CL.trie(arg1));
    }
}

//stock////////////////////////////////////////////////////////////////////


void MainWindow::on_pushButton_14_clicked()
{
//Récupération des informations saisies dans les 3 champs
int IDS=ui->id_stock->text().toInt();
int QUANTS=ui->quantite_disp->text().toInt();
QString NOMS=ui->nom1_3->text();
QString IMAGE=ui->immg->text();
QString CATEGORIE = ui->categorie->text(); // Récupérer la valeur de 'categorie'
QString FOURNIS = ui->fournisseur->text();     // Récupérer la valeur de 'fournis'

QString CONDS = ui->condition_s->text();
QDate DATES = ui->date_ex2->date();   // Champ pour la date
QDate DATEAS  = ui->dateaq2->date(); // Champ pour dateas
int idStock=ui->IDR->text().toInt();

stock S(IDS, QUANTS, NOMS, CATEGORIE, FOURNIS, CONDS, DATES, DATEAS, idStock ,IMAGE);
 // instancier un objet  // en utilisant les informations saisies dans l'interface
bool test=S.ajouter(); // Insérer l'objet étudiant instancié dans la table étudiant // et récupérer la valeur de retour de query.exec()


if(test)
{
    //refreshh teb3aa affichage////////////////////////////////////////////////
    ui->tableView_8->setModel(Stmp.afficher());
    QMessageBox::information(nullptr,QObject::tr("ok"),
                             QObject::tr("ajout effectué\n" "Click Cancel to exit."), QMessageBox::Cancel);}
else{
     QMessageBox::critical(nullptr,QObject::tr("not ok"),
                           QObject::tr("ajout non effectué\n" "Click Cancel to exit."), QMessageBox::Cancel);
}


}




void MainWindow::on_pushButton_17_clicked() {
int IDS =ui->id_stock->text().toInt();
bool test=Stmp.supprimer(IDS);


if(test)
{
    QMessageBox::information(nullptr,QObject::tr("ok"),
                             QObject::tr("suppression effectue\n" "Click Cancel to exit."), QMessageBox::Cancel);}
else{
     QMessageBox::critical(nullptr,QObject::tr("not ok"),
                           QObject::tr("suppression non effectué\n" "Click Cancel to exit."), QMessageBox::Cancel);
}
ui->tableView_8->setModel(Stmp.afficher());
}


void MainWindow::on_pushButton_16_clicked() {
    // Get values from UI
    QString NOMS = ui->nom1_3->text();
    int QUANTS = ui->quantite_disp->text().toInt();
    QString CATEGORIE = ui->categorie->text();
    QString FOURNIS = ui->fournisseur->text();
    QDate DATES = ui->date_ex2->date();
    QDate DATEAS = ui->dateaq2->date();
    QString CONDS = ui->condition_s->text();

    // Get ID from UI (make sure this is valid)
    int idStock = ui->IDR->text().toInt();

    // Call the modifier function
    bool test = Stmp.modifier(NOMS, FOURNIS, CATEGORIE, QUANTS, DATES, DATEAS, idStock, CONDS);

    // Refresh display

    // Show message based on success or failure
    if (test) {
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
    } else {

        QMessageBox::critical(this, QObject::tr("Not OK"),
                             QObject::tr("Modification non effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
    ui->tableView_8->setModel(Stmp.afficher());
    displayCategoryStatistics();

}



//rechercher////////////////////////////////////////////////////////////////


void MainWindow::on_IDR_textChanged() {
    stock Stmp; // Assurez-vous que `stock` est une classe correctement définie et accessible
       QString text = ui->IDR->text();
    // Appeler la méthode rechercher pour obtenir le modèle correspondant au texte saisi
    QSqlQueryModel* model = Stmp.rechercher(text);

    // Vérifier si le modèle est valide et mettre à jour la vue table
    if (model) {
        ui->tableView_8->setModel(model); // Définir le modèle sur le QTableView
    } else {
        QMessageBox::warning(this, "Erreur", "La recherche a échoué ou aucun résultat trouvé.");
    }
}






//bouton exporter//////////////////////////////////////////////////////////////////


void MainWindow::on_pushButton_15_clicked() {
    // Ouvrir une boîte de dialogue pour choisir l'emplacement de sauvegarde
    QString filePath = QFileDialog::getSaveFileName(this,
        "Enregistrer le fichier",
        QDir::homePath(),
        "Fichiers Excel (*.csv);;Tous les fichiers (*.*)"
    );

    // Vérifier si un chemin a été sélectionné
    if (filePath.isEmpty()) {
        qDebug() << "L'utilisateur a annulé la sauvegarde.";
        return;
    }

    // S'assurer que l'extension est correcte
    if (!filePath.endsWith(".csv", Qt::CaseInsensitive)) {
        filePath += ".csv";
    }

    // Ouvrir le fichier en mode écriture
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier pour écriture :" << file.errorString();
        return;
    }

    QTextStream out(&file);

    // Titre et description du fichier
    out << "Données exportées depuis la base STOCK\n";
    out << "-------------------------------------\n";

    // En-têtes organisés avec tabulation pour les colonnes
    out << QString("IDS").leftJustified(10)
        << QString("NOMS").leftJustified(20)
        << QString("QUANTS").leftJustified(10)
        << QString("FOURNIS").leftJustified(20)
        << QString("DATES").leftJustified(15)
        << QString("DATEAS").leftJustified(15)
        << QString("CONDS").leftJustified(20) << "\n";

    out << QString("-").repeated(100) << "\n";

    // Exécuter une requête SQL
    QSqlQuery query;
    query.prepare("SELECT IDS, CATEGORIE, QUANTS, FOURNIS, DATES, DATEAS, CONDS FROM STOCK");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        file.close();
        return;
    }

    // Parcourir les résultats et écrire les données avec un formatage clair
    while (query.next()) {
        out << QString::number(query.value("IDS").toInt()).leftJustified(10)
            << query.value("CATEGORIE").toString().leftJustified(20)
            << QString::number(query.value("QUANTS").toInt()).leftJustified(10)
            << query.value("FOURNIS").toString().leftJustified(20)
            << query.value("DATES").toDate().toString("yyyy-MM-dd").leftJustified(15)
            << query.value("DATEAS").toDate().toString("yyyy-MM-dd").leftJustified(15)
            << query.value("CONDS").toString().leftJustified(20) << "\n";
    }

    // Fermer le fichier
    file.close();

    // Message de confirmation
    qDebug() << "Les données ont été exportées avec succès dans" << filePath;
    QMessageBox::information(this, "Succès", "Les données ont été exportées avec succès dans un format clair et organisé !");
}




// generer qr code////////////////////////////////////////////////
/*
void MainWindow::on_pushButton_32_clicked()
{
    // Récupérer l'identifiant saisi dans le QLineEdit
    QString idText = ui->lineEdit_6->text();
    bool ok;
    int id = idText.toInt(&ok); // Convertir en entier

    // Vérifier si la conversion a réussi
    if (!ok) {
        QMessageBox::warning(this, QObject::tr("Erreur"), QObject::tr("Veuillez entrer un identifiant valide."));
        return;
    }

    // Rechercher la ligne correspondant à l'identifiant dans le modèle de stock
    QModelIndexList indexList = ui->tableView_3->model()->match(
        ui->tableView_3->model()->index(0, 0), // Commencer à la première colonne
        Qt::DisplayRole,
        id,
        1, // Limiter à 1 résultat
        Qt::MatchExactly
    );

    if (indexList.isEmpty()) {
        QMessageBox::warning(this, QObject::tr("Erreur"), QObject::tr("Aucun article trouvé avec cet identifiant."));
        return;
    }

    // Récupérer les détails de l'article de stock à partir de la ligne trouvée
    QModelIndex stockIndex = indexList.first();
    QStringList stockDetails;

    // Supposons que les colonnes sont dans cet ordre : NOMS, CATEGORIE, QUANTS, FOURNIS, DATEAS, DATES, CONDS
    for (int col = 0; col <= 6; ++col) { // Ajustez les indices selon votre modèle
        stockDetails << ui->tableView_3->model()->data(ui->tableView_3->model()->index(stockIndex.row(), col)).toString();
    }

    // Construire le texte pour le QR code dans l'ordre souhaité
    QString text = QString("NOMS: %1\nCATEGORIE: %2\nQUANTS: %3\nFOURNIS: %4\nDATEAS: %5\nDATES: %6\nCONDS: %7")
                    .arg(stockDetails[0], stockDetails[1], stockDetails[2],
                         stockDetails[3], stockDetails[4], stockDetails[5], stockDetails[6]);

    using namespace qrcodegen;

    // Créer l'objet QR Code
    QrCode qr = QrCode::encodeText(text.toUtf8().data(), QrCode::Ecc::MEDIUM);
    qint32 sz = qr.getSize();

    // Créer une image pour le QR Code
    QImage im(sz, sz, QImage::Format_RGB32);
    QRgb black = qRgb(0, 0, 0);
    QRgb white = qRgb(255, 255, 255);

    // Remplir l'image avec les modules du QR Code
    for (int y = 0; y < sz; y++) {
        for (int x = 0; x < sz; x++) {
            im.setPixel(x, y, qr.getModule(x, y) ? black : white);
        }
    }

    // Afficher le QR Code dans le QLabel
    ui->labelQRCode->setPixmap(QPixmap::fromImage(im.scaled(256, 256, Qt::KeepAspectRatio, Qt::FastTransformation), Qt::MonoOnly));
}

*/




#include <QPainter>
#include <QMap>






/*void MainWindow::on_comboBox_9_currentIndexChanged()
{
    stock Stmp;
    QString methode=ui->comboBox_9->currentText();
    QSqlQueryModel* model = Stmp.trier(methode);
    ui->tableView_8->setModel(model);

}*/

//statistique/////////////////////////////////////////////////////////


void MainWindow::displayCategoryStatistics()
{
    // Create a map to hold category names and their corresponding total quantities
    QMap<QString, int> categoryQuantities;

    // Query the database to get the total QUANTS for each CATEGORIE
    QSqlQuery query;
    query.prepare("SELECT CATEGORIE, SUM(QUANTS) AS TotalQuantity FROM STOCK GROUP BY CATEGORIE");

    if (!query.exec()) {
        qDebug() << "Database query error:" << query.lastError().text();
        return; // Exit if there's an error
    }

    // Debug: Log the number of rows returned
    qDebug() << "Number of rows returned: " << query.size();

    // Process the query results to populate the categoryQuantities map
    while (query.next()) {
        QString category = query.value("CATEGORIE").toString(); // Get category name
        int totalQuantity = query.value("TotalQuantity").toInt(); // Get total quantity for the category

        // Store the total quantity for the category in the map
        categoryQuantities[category] = totalQuantity;
    }

    // Debug: Log the contents of the categoryQuantities map
    for (auto it = categoryQuantities.constBegin(); it != categoryQuantities.constEnd(); ++it) {
        qDebug() << "Category:" << it.key() << "Quantity:" << it.value();
    }

    // Create the Pie Chart Series
    QPieSeries *series = new QPieSeries();

    // Append each category and its total quantity to the series
    for (auto it = categoryQuantities.constBegin(); it != categoryQuantities.constEnd(); ++it) {
        series->append(it.key(), it.value());
    }

    // Create a chart and add the series to it
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Product Quantity Distribution by Category");

    // Customize the slices to add labels
    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible(true);
        slice->setLabel(QString("%1: %2%").arg(slice->label()).arg(slice->percentage() * 100, 0, 'f', 1));
    }

    // Create the QChartView for displaying the pie chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Set the QChartView size to fit inside the QGraphicsView named pie_2
    chartView->setFixedSize(ui->pie_2->size());

    // Clear the previous scene and set the new scene with the chart view
    ui->pie_2->setScene(new QGraphicsScene());
    ui->pie_2->scene()->addWidget(chartView);  // Add the chart view to the scene

    // Refresh the QGraphicsView
    ui->pie_2->scene()->update();
    ui->pie_2->show();  // Ensure the pie chart is displayed
}






void MainWindow::checkExpirationAndNotify()
{
    QSqlQuery query;
    query.prepare("SELECT NOMS, DATES FROM STOCK");  // Adjust this based on your database schema

    if (!query.exec()) {
        qDebug() << "Error retrieving products:" << query.lastError().text();
        return;
    }

    QDate today = QDate::currentDate();  // Get today's date

    while (query.next()) {
        QString NOMS = query.value(0).toString();  // Assuming product name is in column 0
        QString DATES = query.value(1).toString();  // Assuming expiry date is in column 1

        // Debug: Log the raw expiry date
        qDebug() << "Raw expiry date for product" << NOMS << ":" << DATES;

        // Clean up the date string if it includes timestamp, e.g., "1999-12-31T00:00:00.000"
        if (DATES.contains("T")) {
            DATES = DATES.split("T").first();  // Keep only the date part
        }

        // Regular expression to check for valid date format YYYY-MM-DD
        QRegularExpression dateRegex("\\d{4}-\\d{2}-\\d{2}");  // Matches date like 2023-12-01
        if (DATES.isEmpty() || !DATES.contains(dateRegex)) {
            qDebug() << "Skipping invalid date format for product:" << NOMS << "Date:" << DATES;
            continue;  // Skip invalid date entries
        }

        // Convert the string to a QDate
        QDate expiryDate = QDate::fromString(DATES, "yyyy-MM-dd");

        if (!expiryDate.isValid()) {
            qDebug() << "Invalid date format for product:" << NOMS << "Date:" << DATES;
            continue;  // Skip invalid date entries
        }

        int daysToExpire = today.daysTo(expiryDate);

        // Check if the product expires in 3 days or less
        if (daysToExpire <= 3 && daysToExpire >= 0) {
            qDebug() << "Product will expire soon:" << NOMS << "in" << daysToExpire << "days";

            // Prepare the SMS message
            QString message = QString("The product '%1' will expire in %2 days.").arg(NOMS).arg(daysToExpire);

            // Send SMS via Twilio API
            sendSmsNotification(message);
        }
    }
}

void MainWindow::sendSmsNotification(const QString &message)
{
    // Twilio credentials
    QString accountSid = "AC096d45869520fbd3871432619abc58c6"; // Replace with your Account SID
    QString authToken = "5b9bae30d5b5722608a9954e5478dbde"; // Replace with your Auth Token

    // The phone number you're sending the message from (Twilio sandbox or your Twilio number)
    QString fromPhoneNumber = "+12707135412"; // Replace with your Twilio number

    // The recipient phone number (in international format)
    QString toPhoneNumber = "+21695356387"; // Replace with recipient's phone number

    // Prepare the request URL for the Twilio API
    QUrl url("https://api.twilio.com/2010-04-01/Accounts/" + accountSid + "/Messages.json");

    // Prepare the POST data for the request
    QUrlQuery query;
    query.addQueryItem("From", fromPhoneNumber); // The number you're sending from (Twilio number)
    query.addQueryItem("To", toPhoneNumber);     // The recipient's phone number
    query.addQueryItem("Body", message);         // The message content

    // Set up the network request
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Encoding the credentials (Base64 encoding)
    QString credentials = accountSid + ":" + authToken;
    QByteArray encodedCredentials = credentials.toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + encodedCredentials);

    // Send the POST request
    QNetworkReply *reply = networkManager->post(request, query.query().toUtf8());

    // Connect the finished signal to handle the reply
    connect(reply, &QNetworkReply::finished, this, &MainWindow::onSmsReplyFinished);
}

void MainWindow::onSmsReplyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply) {
        QByteArray response = reply->readAll();
        qDebug() << "SMS Response:" << response;  // Print the full response

        // Check if the status code is 200 (OK)
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "SMS sent successfully!";
            QMessageBox::information(this, "Success", "SMS sent successfully!");
        } else {
            // Capture and log detailed error information
            qDebug() << "Error sending SMS:" << reply->errorString();
            qDebug() << "HTTP Status Code: " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            qDebug() << "Response Data: " << response;

            // You can also decode the response if it's in JSON format
            QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
            if (!jsonResponse.isNull()) {
                QString errorMessage = jsonResponse["message"].toString();
                qDebug() << "Twilio Error Message:" << errorMessage;
            } else {
                qDebug() << "Response is not in JSON format.";
            }


        }

        reply->deleteLater();
    }
}





#include <QVBoxLayout>
#include <QSqlQuery>

#include <QFile>





void MainWindow::on_pushButton_31_clicked()
{
    qDebug() << "Button clicked. Checking expiration dates...";
    // Call checkExpirationAndNotify to check stock and expiration dates
    checkExpirationAndNotify();

    // Optionally, you can send a specific SMS notification if needed
    // For example, sending a custom message
    sendSmsNotification("This is a custom message from the button click.");
}






void MainWindow::on_affi_img_clicked()
{



        QString IDS = ui->img_2->text();


        if (IDS.isEmpty()) {

            ui->imgg->clear();
            return;
        }


        QSqlQuery query;
        query.prepare("SELECT IMAGE FROM STOCK WHERE IDS=:IDS");
        query.bindValue(":IDS", IDS);


        if (query.exec() && query.next()) {
            QString imageLink = query.value(0).toString();  // Get the image path from the query

            // Check if the image path is valid
            if (!imageLink.isEmpty()) {
                QPixmap pm(imageLink);  // Load the image from the file path
                if (!pm.isNull()) {
                    ui->imgg->setPixmap(pm);  // Set the image in the label
                    ui->imgg->setScaledContents(true);  // Scale the image to fit the label
                } else {
                    // Handle error if image cannot be loaded (e.g., invalid file path)
                    ui->imgg->clear();
                    qDebug() << "Error: Unable to load the image from path:" << imageLink;
                }
            } else {

                ui->imgg->clear();
                qDebug() << "Error: No image link found in the database for IDS:" << IDS;
            }
        } else {
            // Handle error if the query did not return any result (e.g., invalid ID)
            ui->imgg->clear();
            qDebug() << "Error: No result found for IDS:" << IDS;
        }
    }





void MainWindow::on_afiicher_imgb_clicked()
{

        QString filePath = QFileDialog::getOpenFileName(this, tr("Select Image File"), QDir::homePath(), tr("Image (*.jpg *.png *.jpeg)"));

             if (!filePath.isEmpty())
             {
                 ui->immg->setText(filePath);
             }
    }




















void MainWindow::on_IDR_textChanged(const QString &arg1)
{
    stock Stmp; // Assurez-vous que `stock` est une classe correctement définie et accessible
       QString text = ui->IDR->text();
    // Appeler la méthode rechercher pour obtenir le modèle correspondant au texte saisi
    QSqlQueryModel* model = Stmp.rechercher(text);

    // Vérifier si le modèle est valide et mettre à jour la vue table
    if (model) {
        ui->tableView_8->setModel(model); // Définir le modèle sur le QTableView
    } else {
        QMessageBox::warning(this, "Erreur", "La recherche a échoué ou aucun résultat trouvé.");

}
}


/*void MainWindow::on_comboBox_9_activated(int index)
{
    stock Stmp;
    QString methode=ui->comboBox_9->currentText();
    QSqlQueryModel* model = Stmp.trier(methode);
    ui->tableView_8->setModel(model);

}
*/

void MainWindow::on_comboBox_9_currentIndexChanged(int index)
{
    stock Stmp;
    QString methode=ui->comboBox_9->currentText();
    QSqlQueryModel* model = Stmp.trier(methode);
    ui->tableView_8->setModel(model);

}


Arduino A;
void MainWindow::on_pushButton_etat_clicked() {
    double weight = ui->label_40->text().toDouble(); // Retrieve weight
    if (weight > 0) {
        int state = 1;
        updateDatabase1(weight, state);

        // Update the label to display the state
        ui->label_42->setText(QString::number(state));
        return;
    } else {
        int state = 0;

        // Use QTimer to revert state after a delay
        QTimer::singleShot(5000, this, [this, state]() {
            updateDatabase1(0, state);

            // Update the label to display the reverted state
            ui->label_42->setText(QString::number(state));
            qDebug() << "State reverted to 0 after delay";
        });
    }


    // Appel de la méthode updateClientState avec le QLabel et l'ID du client

    /*
     *     if (A.updateClientState(clientId, ui->label_42)) {
        QMessageBox::information(this, "Success", "Client state updated successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to update client state.");
    }

*/
}


#include "arduino.h"
#include <QLabel>
Arduino * arduino;
void MainWindow::setupArduino() {
    // Initialiser Arduino
    arduino = new Arduino(this);
    if (arduino->connect_arduino() == 0) {
        qDebug() << "Arduino connected successfully.";

        // Connecter le signal stateChanged au QLabel
        connect(arduino, &Arduino::stateChanged, this, [this](int state) {
            ui->label_42->setText(QString::number(state));
        });

        // Lancer une vérification périodique
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, arduino, &Arduino::updateStateFromSensor);
        timer->start(100); // Vérification toutes les 100 ms
    } else {
        qDebug() << "Failed to connect to Arduino.";
    }
}
void MainWindow::saveStateToDatabase() {
    // Récupérer l'état actuel affiché sur le label
    int state = ui->label_42->text().toInt();

    // Récupérer l'ID du client (ici, depuis un champ QLineEdit nommé lineEdit_clientId)
    int clientId = ui->id_client_3->text().toInt(); // Si vous avez un QLineEdit pour saisir l'ID client

    if (clientId <= 0) { // Vérifiez que l'ID du client est valide
        qDebug() << "Invalid client ID!";
        return;
    }

    // Préparer la requête pour mettre à jour l'état
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET ETAT = :state WHERE IDCL = :id");
    query.bindValue(":state", state);
    query.bindValue(":id", clientId);

    // Exécuter la requête et afficher un message en cas de succès ou d'erreur
    if (query.exec()) {
        qDebug() << "State saved successfully for client ID:" << clientId;
    } else {
        qDebug() << "Failed to save state:" << query.lastError();
    }
}

void MainWindow::animateImage()
{
    // Récupérer le QLabel où l'image est déjà affichée
    QLabel *label = ui->label_53;  // Assurez-vous que ce QLabel contient déjà une image

    // Créer une animation pour déplacer l'image vers la droite
    QPropertyAnimation *animation = new QPropertyAnimation(label, "pos");
    animation->setDuration(2000); // Durée de l'animation (2 secondes)

    // Position de départ (actuelle) du QLabel
    QPoint startPos = label->pos();

    // Position finale (déplacement vers la droite)
    QPoint endPos(startPos.x() + 200, startPos.y()); // Déplacement de 200 pixels vers la droite

    // Définir les valeurs de début et de fin de l'animation
    animation->setStartValue(startPos);  // Position de départ
    animation->setEndValue(endPos);      // Position finale

    // Créer un "loop" pour que l'animation soit continue
    animation->setLoopCount(-1);  // -1 signifie que l'animation se répète indéfiniment

    // Démarrer l'animation immédiatement
    animation->start(QAbstractAnimation::DeleteWhenStopped);  // L'animation démarre directement

    // Assurez-vous que l'interface graphique se met à jour pendant l'animation
    label->repaint();  // Forcer un rafraîchissement de l'affichage du QLabel
}

void MainWindow::showEvent(QShowEvent *event)
{
    // Cette fonction est appelée dès que l'interface est affichée.
    // Démarrer l'animation dès que la fenêtre est affichée
    animateImage();
    QMainWindow::showEvent(event);  // N'oubliez pas d'appeler la fonction parente
}
