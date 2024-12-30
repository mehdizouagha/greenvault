#include "equipement.h"
equipement::equipement(){}
equipement::equipement(int id,QString nom,QString categorie,QString etat,QString fournisseur,QString localisation,QString parametre,QDate dated,QDate datep,QDate dateaq,double p) {
    id_eq=id;
    nom_e=nom;
    categorie_e=categorie;
    etat_e=etat;
    fournisseur_e=fournisseur;
    localisation_e=localisation;
    parametre_M_e=parametre;
    Date_D_e=dated;
    Date_P_e=datep;
    Date_aq_e=dateaq;
    prix_e=p;

}
bool equipement::ajouter() {
    QRegularExpression regex("^[A-Za-z ]+$");


    if (!regex.match(nom_e).hasMatch() || !regex.match(categorie_e).hasMatch()||!regex.match(etat_e).hasMatch() ||! regex.match(fournisseur_e).hasMatch()||! regex.match(localisation_e).hasMatch()/*||! regex.match(parametre_M_e).hasMatch()*/) {
        qDebug() << "Invalid input: Name and surname should only contain letters.";
        return false;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO EQUIPEMENT (ID_EQUIPEMENT, NOM, CATEGORIE, ETAT, DATE_AQUESITION, DATE_DERNIERM, DATE_PROCHAINM, FOURNISSEUR, LOCALISATION, PRIX, PARAMETRE_SUIVI) "
                  "VALUES (:id_eq, :nom, :categorie, :etat, :date_aquesition, :date_dm, :date_pm, :fournisseur, :localisation, :prix, :parametre_suivi)");


    query.bindValue(":id_eq", id_eq);

    query.bindValue(":nom", nom_e);
    query.bindValue(":categorie", categorie_e);
    query.bindValue(":date_aquesition", Date_aq_e);
    query.bindValue(":date_dm",Date_D_e);
    query.bindValue(":date_pm", Date_P_e);
    query.bindValue(":etat", etat_e);
    query.bindValue(":fournisseur", fournisseur_e);
    query.bindValue(":localisation", localisation_e);
    // query.bindValue(":fournisseur", fournisseur_e);
    query.bindValue(":prix", prix_e);
    query.bindValue(":parametre_suivi",parametre_M_e);

    return query.exec();

}

bool equipement::supprimer(int id)
{
    QSqlQuery query;



    query.prepare("DELETE FROM EQUIPEMENT WHERE (ID_EQUIPEMENT=:id_eq) ");
    query.bindValue(":id_eq", id);


    return query.exec();
}
QSqlQueryModel* equipement::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EQUIPEMENT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));

    return model;
}

bool equipement::modifier(int id)
{
    QSqlQuery query;
    QString queryString = "UPDATE EQUIPEMENT SET ";
    bool firstField = true;


    if (!nom_e.isEmpty()) {
        if (!firstField) queryString += ", ";
        queryString += "NOM=:nom";
        firstField = false;
    }
    if (!categorie_e.isEmpty()) {
        if (!firstField) queryString += ", ";
        queryString += "CATEGORIE=:categorie";
        firstField = false;
    }
    if (!etat_e.isEmpty()) {
        if (!firstField) queryString += ", ";
        queryString += "ETAT=:etat";
        firstField = false;
    }
    if (!fournisseur_e.isEmpty()) {
        if (!firstField) queryString += ", ";
        queryString += "FOURNISSEUR=:fournisseur";
        firstField = false;
    }
    if (!localisation_e.isEmpty()) {
        if (!firstField) queryString += ", ";
        queryString += "LOCALISATION=:localisation";
        firstField = false;
    }
    if (!Date_aq_e.isNull()) {
        if (!firstField) queryString += ", ";
        queryString += "DATE_AQUESITION=:date_aquesition";
        firstField = false;
    }
    if (!Date_D_e.isNull()) {
        if (!firstField) queryString += ", ";
        queryString += "DATE_DERNIERM=:date_dm";
        firstField = false;
    }
    if (!Date_P_e.isNull()) {
        if (!firstField) queryString += ", ";
        queryString += "DATE_PROCHAINM=:date_pm";
        firstField = false;
    }
    if (prix_e!=0) {
        if (!firstField) queryString += ", ";
        queryString += "PRIX=:prix";
        firstField = false;
    }
    if (!parametre_M_e.isEmpty()) {
        if (!firstField) queryString += ", ";
        queryString += "PARAMETRE_SUIVI=:parametre";
        firstField = false;
    }


    if (firstField) {

        return false;
    }


    queryString += " WHERE ID_EQUIPEMENT=:id_eq";


    query.prepare(queryString);


    if (!nom_e.isEmpty()) query.bindValue(":nom", nom_e);
    if (!categorie_e.isEmpty()) query.bindValue(":categorie", categorie_e);
    if (!etat_e.isEmpty()) query.bindValue(":etat", etat_e);
    if (!fournisseur_e.isEmpty()) query.bindValue(":fournisseur", fournisseur_e);
    if (!localisation_e.isEmpty()) query.bindValue(":localisation", localisation_e);
    if (!Date_aq_e.isNull()) query.bindValue(":date_aquesition", Date_aq_e);
    if (!Date_D_e.isNull()) query.bindValue(":date_dm", Date_D_e);
    if (!Date_P_e.isNull()) query.bindValue(":date_pm", Date_P_e);
    if (!parametre_M_e.isEmpty()) query.bindValue(":parametre", parametre_M_e);
    if (prix_e != 0) query.bindValue(":prix", prix_e);

    query.bindValue(":id_eq", id);

    return query.exec();
}
QSqlQueryModel* equipement::rechercher(const QString &partialId) {
    QSqlQuery query;


    query.prepare("SELECT * FROM EQUIPEMENT WHERE TO_CHAR(ID_EQUIPEMENT) LIKE :partialId");
    query.bindValue(":partialId", partialId + "%");
    if (!query.exec()) {
        qDebug() << "Search failed, SQL error:" << query.lastError().text();
        return nullptr;
    }
    // Fill model with results
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(std::move(query));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EQUIPEMENT"));
    //model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    //model->setHeaderData(2, Qt::Horizontal, QObject::tr("CATEGORIE"));


    return model;
}
QSqlQueryModel* equipement::rechercherpanom(const QString &input) {
    QSqlQuery query;

    // Prepare the SQL query with a LIKE condition for both ID_EQUIPEMENT and NOM
    query.prepare("SELECT * FROM EQUIPEMENT WHERE TO_CHAR(ID_EQUIPEMENT) LIKE :partialId OR NOM LIKE :nom");

    // Bind the input value to both fields with wildcard for partial matching
    query.bindValue(":partialId", input + "%");
    query.bindValue(":nom", input + "%");

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Search failed, SQL error:" << query.lastError().text();
        return nullptr;
    }

    // Create and populate the model with the query results
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Optionally, set the headers for the columns
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EQUIPEMENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CATEGORIE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_AQUESITION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));

    // Return the populated model
    return model;
}

QSqlQueryModel* equipement::trier(const QString& methode, bool descending) {
    QSqlQuery query;

    QString queryString = "SELECT * FROM EQUIPEMENT";
    QString orderDirection = descending ? "DESC" : "ASC";

    if (methode == "nom") {
        queryString += " ORDER BY NOM " + orderDirection;
    } else if (methode == "date") {
        queryString += " ORDER BY DATE_AQUESITION " + orderDirection;

    }else if(methode == "prix"){
        queryString += " ORDER BY PRIX " + orderDirection;

    }
    else {

        qWarning() << "Invalid sort method provided: " << methode;
        queryString += " ORDER BY ID_EQUIPEMENT " + orderDirection;
    }

    query.exec(queryString);

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);
    /*model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EQUIPEMENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CATEGORIE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_AQUESITION")); // Assuming DATE_AQUESITION is in the query*/

    return model;
}

QSqlTableModel* equipement::getTableModel(QObject *parent)
{
    QSqlTableModel *model = new QSqlTableModel(parent);
    model->setTable("EQUIPEMENT");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    return model;
}
QImage equipement::generateQRCode(const QString &data, const quint16 size, const quint16 borderSize,
                                  qrcodegen::QrCode::Ecc errorCorrection) {

    QrCodeGenerator qrGenerator;

    QImage qrImage = qrGenerator.generateQr(data, size, borderSize, errorCorrection);

    return qrImage;
}

/*void equipement::generate_text_file(int equipment_id) {
    // Directory to save text files
    std::string output_dir = "equipment_files";
    fs::create_directories(output_dir);

    // Assuming you already have an existing database connection 'db' from your Qt application
    QSqlDatabase db = QSqlDatabase::database();  // Fetch the existing database connection

    // Check if the connection is valid
    if (!db.isOpen()) {
        std::cerr << "Error: Database connection is not open!" << std::endl;
        return;
    }

    // Query to fetch the equipment data for the specific ID
    QSqlQuery query;
    query.prepare("SELECT NOM, CATEGORIE, ETAT, TO_CHAR(DATE_AQUESITION, 'YYYY-MM-DD') AS DATE_AQUESITION, "
                  "TO_CHAR(DATE_DERNIERM, 'YYYY-MM-DD') AS DATE_DERNIERM, "
                  "TO_CHAR(DATE_PROCHAINM, 'YYYY-MM-DD') AS DATE_PROCHAINM, FOURNISSEUR, LOCALISATION, PRIX, PARAMETRE_SUIVI "
                  "FROM MEHDI.EQUIPEMENT WHERE ID_EQUIPEMENT = :id");
    query.bindValue(":id", equipment_id);

    if (!query.exec()) {
        std::cerr << "Error executing query: " << query.lastError().text().toStdString() << std::endl;
        return;
    }

    // Fetch the result and write to a file
    if (query.next()) {
        QString file_name = QString::fromStdString(output_dir) + "/equipment_" + QString::number(equipment_id) + ".txt";
        std::ofstream file(file_name.toStdString());

        file << "ID: " << query.value(0).toInt() << std::endl;
        file << "Name: " << query.value(1).toString().toStdString() << std::endl;
        file << "Category: " << query.value(2).toString().toStdString() << std::endl;
        file << "State: " << query.value(3).toString().toStdString() << std::endl;
        file << "Acquisition Date: " << query.value(4).toString().toStdString() << std::endl;
        file << "Last Maintenance: " << query.value(5).toString().toStdString() << std::endl;
        file << "Next Maintenance: " << query.value(6).toString().toStdString() << std::endl;
        file << "Supplier: " << query.value(7).toString().toStdString() << std::endl;
        file << "Location: " << query.value(8).toString().toStdString() << std::endl;
        file << "Price: " << query.value(9).toDouble() << std::endl;
        file << "Tracking Parameter: " << query.value(10).toString().toStdString() << std::endl;

        std::cout << "File generated: " << file_name.toStdString() << std::endl;

        file.close();
    } else {
        std::cout << "No data found for ID " << equipment_id << std::endl;
    }
}*/


QImage equipement::generateQRCodeForId(const int &id) {

    QSqlQuery query;
    query.prepare("SELECT NOM, CATEGORIE, ETAT, TO_CHAR(DATE_AQUESITION, 'YYYY-MM-DD') AS DATE_AQUESITION, "
                  "TO_CHAR(DATE_DERNIERM, 'YYYY-MM-DD') AS DATE_DERNIERM, "
                  "TO_CHAR(DATE_PROCHAINM, 'YYYY-MM-DD') AS DATE_PROCHAINM, FOURNISSEUR, LOCALISATION, PRIX, PARAMETRE_SUIVI "
                  "FROM EQUIPEMENT WHERE ID_EQUIPEMENT = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error retrieving equipment details:" << query.lastError();
        return QImage();
    }


    if (query.next()) {
        QString equipmentDetails = QString("{"
                                           "\"id\": \"%1\", "
                                           "\"name\": \"%2\", "
                                           "\"category\": \"%3\", "
                                           "\"state\": \"%4\", "
                                           "\"acquisition_date\": \"%5\", "
                                           "\"last_maintenance\": \"%6\", "
                                           "\"next_maintenance\": \"%7\", "
                                           "\"supplier\": \"%8\", "
                                           "\"location\": \"%9\", "
                                           "\"price\": \"%10\", "
                                           "\"tracking_parameter\": \"%11\""
                                           "}")
                                       .arg(id)
                                       .arg(query.value("NOM").toString())
                                       .arg(query.value("CATEGORIE").toString())
                                       .arg(query.value("ETAT").toString())
                                       .arg(query.value("DATE_AQUESITION").toString())
                                       .arg(query.value("DATE_DERNIERM").toString())
                                       .arg(query.value("DATE_PROCHAINM").toString())
                                       .arg(query.value("FOURNISSEUR").toString())
                                       .arg(query.value("LOCALISATION").toString())
                                       .arg(QString::number(query.value("PRIX").toDouble(), 'f', 2))
                                       .arg(query.value("PARAMETRE_SUIVI").toString());


        qDebug() << "Generated equipment details for QR code:" << equipmentDetails;

        return generateQRCode(equipmentDetails);
    }

    return QImage();
}

/*void equipement::generateTextFileFromQRCode(int equipmentId) {
    QString outputDir = "C:/Users/mehdi/Documents/equipementfile";  // Using forward slashes for cross-platform compatibility
    QDir dir;

    // Create the directory if it doesn't exist
    if (!dir.exists(outputDir)) {
        dir.mkpath(outputDir);
    }
    // Assuming you have an open database connection 'db'
    QSqlQuery query;
    query.prepare("SELECT NOM, CATEGORIE, ETAT, TO_CHAR(DATE_AQUESITION, 'YYYY-MM-DD') AS DATE_AQUESITION, "
                  "TO_CHAR(DATE_DERNIERM, 'YYYY-MM-DD') AS DATE_DERNIERM, "
                  "TO_CHAR(DATE_PROCHAINM, 'YYYY-MM-DD') AS DATE_PROCHAINM, FOURNISSEUR, LOCALISATION, PRIX, PARAMETRE_SUIVI "
                  "FROM MEHDI.EQUIPEMENT WHERE ID_EQUIPEMENT = :id");
    query.bindValue(":id", equipmentId);

    if (!query.exec()) {
        qDebug() << "Error retrieving equipment details:" << query.lastError();
        return;
    }

    // Fetch data if the query is successful
    if (query.next()) {
        QString equipmentDetails = QString("{"
                                           "\"id\": \"%1\", "
                                           "\"name\": \"%2\", "
                                           "\"category\": \"%3\", "
                                           "\"state\": \"%4\", "
                                           "\"acquisition_date\": \"%5\", "
                                           "\"last_maintenance\": \"%6\", "
                                           "\"next_maintenance\": \"%7\", "
                                           "\"supplier\": \"%8\", "
                                           "\"location\": \"%9\", "
                                           "\"price\": \"%10\", "
                                           "\"tracking_parameter\": \"%11\""
                                           "}")
                                       .arg(equipmentId)
                                       .arg(query.value("NOM").toString())
                                       .arg(query.value("CATEGORIE").toString())
                                       .arg(query.value("ETAT").toString())
                                       .arg(query.value("DATE_AQUESITION").toString())
                                       .arg(query.value("DATE_DERNIERM").toString())
                                       .arg(query.value("DATE_PROCHAINM").toString())
                                       .arg(query.value("FOURNISSEUR").toString())
                                       .arg(query.value("LOCALISATION").toString())
                                       .arg(QString::number(query.value("PRIX").toDouble(), 'f', 2))
                                       .arg(query.value("PARAMETRE_SUIVI").toString());

        // Save the details to a file
        QString fileName = QString("equipment_%1.txt").arg(equipmentId);
        QString filePath = outputDir + "/" + fileName;
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << equipmentDetails;
            file.close();
            qDebug() << "File generated:" << fileName;
        } else {
            qDebug() << "Error opening file for writing:" << file.errorString();
        }
    } else {
        qDebug() << "No data found for ID" << equipmentId;
    }
}
QString equipement::scanQRCode(const QString &imagePath) {
    // Load the image using OpenCV
    cv::Mat image = cv::imread(imagePath.toStdString(), cv::IMREAD_COLOR);
    if (image.empty()) {
        qDebug() << "Error: Could not load the image.";
        return QString();
    }

    // Create QRCodeDetector object
    cv::QRCodeDetector qrDecoder;

    // Detect and decode the QR code
    std::string decodedData;
    decodedData = qrDecoder.detectAndDecode(image);

    if (!decodedData.empty()) {
        qDebug() << "Decoded Data:" << QString::fromStdString(decodedData);
        return QString::fromStdString(decodedData);
    } else {
        qDebug() << "No QR Code detected.";
        return QString();
    }
}*/

QString equipement::diagnostic(int id) {
    QString diagnosticMessage;
    QSqlQuery query;

    // Ensure the database connection is established
    if (!query.prepare("SELECT PARAMETRE_SUIVI FROM EQUIPEMENT WHERE ID_EQUIPEMENT = :id")) {
        qDebug() << "Failed to prepare query:" << query.lastError().text();
        return "Database query preparation error.";
    }

    query.bindValue(":id", id); // Bind the equipment ID

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return "Database query execution error.";
    }

    // Fetch the parameter value
    QString parametreSuivi;
    if (query.next()) {
        parametreSuivi = query.value("PARAMETRE_SUIVI").toString();
    } else {
        return "No data found for the given equipment ID.";
    }

    // Diagnostic logic based on the retrieved PARAMETRE_SUIVI
    if (parametreSuivi.contains("overheating", Qt::CaseInsensitive)) {
        diagnosticMessage = "The equipment is overheating.";
    } else if (parametreSuivi.contains("battery", Qt::CaseInsensitive)) {
        diagnosticMessage = "Battery is damaged";
    } else if (parametreSuivi.contains("software", Qt::CaseInsensitive)) {
        diagnosticMessage = "Software malfunction detected.";
    } else if (parametreSuivi.contains("physical_damage", Qt::CaseInsensitive)) {
        diagnosticMessage = "Physical damage detected.";
    }else if(parametreSuivi.contains("battery_overheating", Qt::CaseInsensitive)){
        diagnosticMessage = "battery is damaged maybe it coses the heat.";
    }else if(parametreSuivi.contains("software_physical_damage", Qt::CaseInsensitive)){
        diagnosticMessage = "maybe the equipment is broke or software malfucction .";
    }else if(parametreSuivi.contains("software_battery",Qt::CaseInsensitive)){
        diagnosticMessage="battery is damaged or the software is not compatible";
    }
    else {
        diagnosticMessage = "No issues detected based on available parameters.";
    }

    // Log diagnostic details for debugging
    qDebug() << "Diagnostic: " << diagnosticMessage;

    return diagnosticMessage;
}


QString equipement::reparation(int id) {
    QString repairSuggestion;
    QSqlQuery query;


    if (!query.prepare("SELECT PARAMETRE_SUIVI FROM EQUIPEMENT WHERE ID_EQUIPEMENT = :id")) {
        qDebug() << "Failed to prepare query:" << query.lastError().text();
        return "Database query preparation error.";
    }

    query.bindValue(":id", id);


    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return "Database query execution error.";
    }


    QString parametreSuivi;
    if (query.next()) {
        parametreSuivi = query.value("PARAMETRE_SUIVI").toString();
    } else {
        return "No data found for the given equipment ID.";
    }


    if (parametreSuivi.contains("overheating", Qt::CaseInsensitive)) {
        repairSuggestion = "Please check the cooling system or replace the cooling fan.";
    } else if (parametreSuivi.contains("battery", Qt::CaseInsensitive)) {
        repairSuggestion = "Replace the battery or check for issues in the power supply.";
    } else if (parametreSuivi.contains("software", Qt::CaseInsensitive)) {
        repairSuggestion = "Reinstall the software or update to the latest version.";
    } else if (parametreSuivi.contains("physical_damage", Qt::CaseInsensitive)) {
        repairSuggestion = "Assess the damage and replace broken parts.";
    }
    else if(parametreSuivi.contains("battery_overheating", Qt::CaseInsensitive)){
        repairSuggestion = "try replace the battery or check the over heat problem";
    }else if(parametreSuivi.contains("software_physical_damage", Qt::CaseInsensitive)){
        repairSuggestion = "check the software or the hardware component.";
    }else if(parametreSuivi.contains("software_battery",Qt::CaseInsensitive)){
        repairSuggestion="check the battery or update the software";
    }
    else {
        repairSuggestion = "Perform a full system check-up for a more thorough diagnosis.";
    }


    qDebug() << "Repair suggestion: " << repairSuggestion;

    return repairSuggestion;
}

/*void equipement::predictEquipmentIssue(float temperature, int operatingHours, const QString &errorCode) {
    QProcess process;



    QString pythonScript =  "C:/Users/mehdi/Documents/rendu1009/script.py";


    QStringList arguments;
    arguments << pythonScript
              << QString::number(temperature)
              << QString::number(operatingHours)
              << errorCode;

    // Start the Python process
    process.start("python", arguments);

    // Wait for the process to finish
    process.waitForFinished();

    // Capture the output from the Python script
    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();

    if (!error.isEmpty()) {
        qDebug() << "Error in prediction:" << error;
        return;
    }

    qDebug() << "Prediction Result:" << output;

    // Process the output (e.g., display it in the UI)
}
*/
void equipement::populateComboBoxE(QComboBox *comboBox) {
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
void equipement::populateComboBoxP(QComboBox *comboBox) {
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
bool equipement::affecter(const QString &nomE, const QString &nomP, const QDate &date) {
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
QSqlQueryModel* equipement::afficherAffectation() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM MAINTENIR1");
    //model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));

    return model;
}
bool equipement::supprimeraffectation(QString const &nomE,QString const &nomP) {
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

