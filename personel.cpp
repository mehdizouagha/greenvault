#include "personel.h"
#include "qsqlerror.h"
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QMessageBox>
#include <QRegularExpression>
#include <QMessageBox>

#include <QPageSize>
#include <QLineEdit>
#include <QCompleter>
#include <QStringListModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>  // for qWarning

personel::personel()  {}

personel::personel(int id, QString nom, QString prenom,QDate date,QString poste,int salaire, QString mail,int telephone,QString role)
{
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->date = date;
    this->poste = poste;
    this->salaire = salaire;
    this->mail = mail;
    this->telephone = telephone;
    this->role=role;


}

bool personel::ajouter()
{
    if (!validateString(nom) || !validateString(prenom) || !validateString(poste)) {
        QMessageBox::warning(nullptr, "Erreur", "Les champs nom, prénom et poste doivent contenir uniquement des lettres.");
        return false;
    }

    QSqlQuery query;
   // QString res = QString::number(id);


    query.prepare("INSERT INTO PERSONELL (ID, NOM, PRENOM, DATE_EMBAUCHE, POSTE, SALAIRE, MAIL, TELEPHONE ,role ) "
                  "VALUES (:ID, :NOM, :PRENOM, :DATE_EMBAUCHE, :POSTE, :SALAIRE, :MAIL, :TELEPHONE , :role)");

    query.bindValue(":ID", id);
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":DATE_EMBAUCHE", date);
    query.bindValue(":POSTE", poste);
    query.bindValue(":SALAIRE", salaire);
    query.bindValue(":MAIL", mail);
    query.bindValue(":TELEPHONE", telephone);
    query.bindValue(":role", role);
    return query.exec();



}


QSqlQueryModel* personel::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from PERSONELL");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE_EMBAUCHE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("POSTE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("SALAIRE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("MAIL"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("TELEPHONE"));

    return model;
}



bool personel::supprimer(int id, const QString &attribut)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete from PERSONELL where ID = :id ");
    query.bindValue(":id", res);

    return query.exec();
}





bool personel::modifier(int id)
{
    if (!validateString(nom) || !validateString(prenom) || !validateString(poste)) {
        QMessageBox::warning(nullptr, "Erreur", "Les champs nom, prénom et poste doivent contenir uniquement des lettres.");
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE PERSONELL SET NOM = :nom, PRENOM = :prenom, DATE_EMBAUCHE = :date_embauche, POSTE = :poste, SALAIRE = :salaire, MAIL = :mail, TELEPHONE = :telephone WHERE id = :ID");
    query.bindValue(":ID", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_embauche", date);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);
    query.bindValue(":mail", mail);
    query.bindValue(":telephone", telephone);

    return query.exec(); // Si tout s'est bien passé
}





QSqlQueryModel* personel::rechercher(const QString &searchValue)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Prepare the query to search by id, telephone, or nom
    query.prepare("SELECT * FROM PERSONELL WHERE ID = :value OR TELEPHONE = :value OR NOM LIKE :nomValue");

    // Bind the search value to the query for exact matches on ID and TELEPHONE
    query.bindValue(":value", searchValue);

    // Bind the search value with a wildcard at the end for NOM (starts with searchValue)
    query.bindValue(":nomValue", searchValue + "%");

    // Execute the query
    if (query.exec()) {
        // Set the query result to the model
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_EMBAUCHE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("POSTE"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("SALAIRE"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("MAIL"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("TELEPHONE"));
    }
    return model;
}


QMap<QString, double> personel::statistiquesPourcentageSalaire()
{

    QMap<QString, double> stats;
    QSqlQuery query;

    // Récupérer le nombre total de personnel
    int totalPersonnel = 0;
    query.exec("SELECT COUNT(*) FROM PERSONELL");
    if (query.next()) {
        totalPersonnel = query.value(0).toInt();
    }

    // Vérifier que le total est supérieur à zéro pour éviter la division par zéro
    if (totalPersonnel > 0) {
        // Tranche de salaire faible : moins de 2000
        query.exec("SELECT COUNT(*) FROM PERSONELL WHERE SALAIRE < 2000");
        if (query.next()) {
            int count = query.value(0).toInt();
            stats["Faible(-2000)"] = (count / static_cast<double>(totalPersonnel)) * 100;
        }

        // Tranche de salaire moyen : entre 2000 et 5000
        query.exec("SELECT COUNT(*) FROM PERSONELL WHERE SALAIRE >= 2000 AND SALAIRE < 5000");
        if (query.next()) {
            int count = query.value(0).toInt();
            stats["Moyen (2000-5000)"] = (count / static_cast<double>(totalPersonnel)) * 100;
        }

        // Tranche de salaire élevé : plus de 5000
        query.exec("SELECT COUNT(*) FROM PERSONELL WHERE SALAIRE >= 5000");
        if (query.next()) {
            int count = query.value(0).toInt();
            stats["Élevé (5000+)"] = (count / static_cast<double>(totalPersonnel)) * 100;
        }
    }

    return stats;

}

bool personel::exporterPDF(const QString& fileName, QSqlQueryModel* model) {
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setOutputFileName(fileName);
    QPainter painter(&printer);
    if (!painter.isActive()) {
        QMessageBox::warning(nullptr, "Erreur", "Impossible de dessiner sur l'imprimante.");
        return false;
    }
    int rowCount = model->rowCount();
    int columnCount = model->columnCount();
    int x = 0;
    int y = 0;
    int rowHeight = 20;
    int columnWidth = printer.pageLayout().paintRect().width() / columnCount;
    // Draw the title
    QFont titleFont = painter.font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.drawText(printer.pageLayout().paintRect(), Qt::AlignCenter, "Liste des personnels");
    y += 40; // Move down to leave space for the title
    // Set font for headers
    QFont headerFont = painter.font();
    headerFont.setPointSize(12);
    headerFont.setBold(true);
    painter.setFont(headerFont);
    painter.setPen(Qt::green); // Set text color for headers
    // Draw the table headers
    for (int col = 0; col < columnCount; ++col) {
        painter.drawText(x, y, columnWidth, rowHeight, Qt::AlignCenter, model->headerData(col, Qt::Horizontal).toString());
        x += columnWidth;
    }
    y += rowHeight;
    x = 0;
    // Set font for table data
    QFont dataFont = painter.font();
    dataFont.setPointSize(10);
    painter.setFont(dataFont);
    painter.setPen(Qt::black); // Set text color for data
    // Draw the table data
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < columnCount; ++col) {
            QString data = model->data(model->index(row, col)).toString();
            painter.drawText(x, y, columnWidth, rowHeight, Qt::AlignCenter, data);
            x += columnWidth;
        }
        y += rowHeight;
        x = 0;
    }
    return true;
}


QSqlQueryModel* personel::afficherTrieParID(bool ordreCroissant)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryStr = "SELECT * FROM PERSONELL ORDER BY ID";

    queryStr += ordreCroissant ? " ASC" : " DESC"; // Sort order based on ordreCroissant

    model->setQuery(queryStr);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_EMBAUCHE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("POSTE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("TELEPHONE"));

    return model;
}
#include <QDebug>



QSqlQueryModel* personel::rechercher_sug(const QString &critere) {
    QSqlQuery query;
    QString queryString = "SELECT id, nom, poste FROM PERSONELL WHERE id LIKE '%" + critere + "%' OR nom LIKE '%" + critere + "%' OR poste LIKE '%" + critere + "%'";

    query.prepare(queryString);
    query.exec();

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);
    return model;
}


QString personel::getUserRole(const QString &email) {
    QSqlQuery query;

    // Prepare the SQL query to select the user role based on the email
    query.prepare("SELECT role FROM personell WHERE mail = :email");
    query.bindValue(":email", email);

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return QString();
    }

    // Fetch the result
    if (query.next()) {
        return query.value(0).toString();
    } else {
        qDebug() << "No user found with email:" << email;
        return QString();
    }
}
void personel::populateComboBoxP(QComboBox *comboBox) {
    // Clear existing items

    QSqlQuery query;
    query.prepare("SELECT  NOM FROM personell");
    if (!query.exec()) {
        qDebug() << "Error fetching equipment:" << query.lastError().text();
        return;
    }
    comboBox->clear();
    while (query.next()) {
        QString equipmentName = query.value("NOM").toString();
        qDebug() << "Retrieved equipment name:" << equipmentName;
        comboBox->addItem(equipmentName);
    }
}
void personel::populateComboBoxE(QComboBox *comboBox) {
    // Clear existing items

    QSqlQuery query;
    query.prepare("SELECT  NOM FROM EQUIPEMENT");
    if (!query.exec()) {
        qDebug() << "Error fetching equipment:" << query.lastError().text();
        return;
    }
    comboBox->clear();
    while (query.next()) {
        QString equipmentName = query.value("NOM").toString();
        qDebug() << "Retrieved equipment name:" << equipmentName;
        comboBox->addItem(equipmentName);
    }
}
bool personel::affecter(const QString &nomE, const QString &nomP, const QDate &date) {
    QSqlQuery query;

    // Step 1: Get ID_EQUIPEMENT for the given equipment name
    query.prepare("SELECT ID_EQUIPEMENT FROM EQUIPEMENT WHERE NOM LIKE :nom");
    query.bindValue(":nom", nomE);
    if (!query.exec() || !query.next()) {  // Execute and check if a result is available
        qDebug() << "Error fetching ID_EQUIPEMENT:" << query.lastError().text();
        return false;
    }
    int idE = query.value(0).toInt();  // Get the ID_EQUIPEMENT

    // Step 2: Get ID for the given personnel name
    query.prepare("SELECT ID FROM PERSONELL WHERE NOM LIKE :nom");
    query.bindValue(":nom", nomP);
    if (!query.exec() || !query.next()) {  // Execute and check if a result is available
        qDebug() << "Error fetching ID:" << query.lastError().text();
        return false;
    }
    int idP = query.value(0).toInt();  // Get the ID

    // Step 3: Insert the assignment into the MAINTENIR1 table
    query.prepare("INSERT INTO MAINTENIR1 (IDE, IDP, DATE_ASS,NOMP,NOME) VALUES (:ide, :idp, :date,:nomp,:nome)");
    query.bindValue(":ide", idE);
    query.bindValue(":idp", idP);
    query.bindValue(":date", date);
    query.bindValue(":nomp",nomP);
    query.bindValue(":nome",nomE);

    if (!query.exec()) {  // Execute and check if successful
        qDebug() << "Error inserting assignment into MAINTENIR1:" << query.lastError().text();
        return false;
    }

    return true;  // All operations successful
}
QSqlQueryModel* personel::afficherAffectation() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM MAINTENIR1");
    //model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));

    return model;
}
bool personel::supprimeraffectation(QString const &nomE,QString const &nomP) {
    QSqlQuery query;
    query.prepare("SELECT ID_EQUIPEMENT FROM EQUIPEMENT WHERE NOM = :nomE");
    query.bindValue(":nomE", nomE);
    if (!query.exec() || !query.next()) {
        //QMessageBox::warning(this, "Error", "Failed to find the equipment ID.");
        return false;
    }
    int idE = query.value(0).toInt();

    query.prepare("SELECT ID FROM PERSONELL WHERE NOM = :nomP");
    query.bindValue(":nomP", nomP);
    if (!query.exec() || !query.next()) {
        //QMessageBox::warning(this, "Error", "Failed to find the personnel ID.");
        return false;
    }
    int idP = query.value(0).toInt();


    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM MAINTENIR1 WHERE IDE = :idE AND IDP = :idP");
    deleteQuery.bindValue(":idE", idE);
    deleteQuery.bindValue(":idP", idP);

    if (!deleteQuery.exec()) {
        qDebug() << "Error deleting assignment:" << deleteQuery.lastError().text();
        return false;
    }

    return true;
}







