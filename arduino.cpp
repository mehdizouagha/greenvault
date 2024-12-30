/*
 * #include "arduino.h"
#include "qregularexpression.h"
#include "qsqlerror.h"
#include "qsqlquery.h"

Arduino::Arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
    serial1=new QSerialPort;
}
Arduino::Arduino(QObject*parent ) :QObject(parent)
{
    data="";
    arduino_port_name="COM3";
    arduino_is_available=false;
    serial=new QSerialPort;
    serial1=new QSerialPort;
}
QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
   return serial;
}
QString Arduino::getarduino_port_name1()
{
    return arduino_port_name1;
}

QSerialPort *Arduino::getserial1()
{
   return serial1;
}
int Arduino::connect_arduino()
{   // recherche du port sur lequel la carte arduino identifée par  arduino_uno_vendor_id
    // est connectée
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                       == arduino_uno_producy_id) {
                   arduino_is_available = true;
                   arduino_port_name1=serial_port_info.portName();
               } } }
        qDebug() << "arduino_port_name is :" << arduino_port_name;
        if(arduino_is_available){ // configuration de la communication ( débit...)
            serial->setPortName(arduino_port_name);
            if(serial->open(QSerialPort::ReadWrite)){
                serial->setBaudRate(QSerialPort::Baud9600); // débit : 9600 bits/s
                serial->setDataBits(QSerialPort::Data8); //Longueur des données : 8 bits,
                serial->setParity(QSerialPort::NoParity); //1 bit de parité optionnel
                serial->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
                serial->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;
}
int Arduino::connect_arduino1() {
    qDebug() << "Starting connect_arduino1()...";
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Checking port:" << serial_port_info.portName();
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            qDebug() << "Vendor ID:" << serial_port_info.vendorIdentifier()
                     << "Product ID:" << serial_port_info.productIdentifier();
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                qDebug() << "Arduino found on port:" << arduino_port_name;
            }
        }
    }

    if (arduino_is_available) {
        serial1->setPortName(arduino_port_name);
        if (serial1->open(QSerialPort::ReadWrite)) {
            serial1->setBaudRate(QSerialPort::Baud9600);
            serial1->setDataBits(QSerialPort::Data8);
            serial1->setParity(QSerialPort::NoParity);
            serial1->setStopBits(QSerialPort::OneStop);
            serial1->setFlowControl(QSerialPort::NoFlowControl);
            qDebug() << "Connected to serial1 on port:" << arduino_port_name;
            return 0;
        } else {
            qDebug() << "Failed to open serial1.";
            return 1;
        }
    }

    qDebug() << "No Arduino available for serial1.";
    return -1;
}
int Arduino::close_arduino()

{

    bool serialClosed = true;

        if (serial->isOpen()) {
            serial->close();
            serialClosed = false;
        }

        if (serial1->isOpen()) {
            serial1->close();
            serialClosed = false;
        }

        return serialClosed ? 0 : 1;  // Return 0 if all ports are closed


}

void Arduino::readWeightFromSensor() {
    QByteArray rawData = serial->readAll();  // Read all available data
    qDebug() << "Raw data received from Arduino: " << rawData;

    // Convert the data to a QString for processing
    QString rawDataStr = QString::fromUtf8(rawData).trimmed();
    accumulatedData.append(rawDataStr.toUtf8());  // Convert QString to QByteArray and accumulate

    qDebug() << "Accumulated data: " << accumulatedData;

    // Convert accumulatedData to a QString for regex matching
    QString accumulatedDataStr = QString::fromUtf8(accumulatedData);

    // Regular expression to extract a floating-point number after "Poids"
    QRegularExpression regex("Poids\\s*[:]?\\s*(-?\\d*\\.?\\d+)");
    QRegularExpressionMatch match = regex.match(accumulatedDataStr);

    if (match.hasMatch()) {
        QString weight = match.captured(1);  // Extract the weight number
        qDebug() << "Extracted weight: " << weight;

        // Emit the weight as a double
        emit weightDetected(weight.toDouble());  // Emit as double

        // Clear the accumulated data for the next reading
        accumulatedData.clear();
    } else {
        qDebug() << "No weight data found.";
    }
}


bool Arduino::saveWeightToDatabase(double weight) {
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (POIDS) VALUES (:weight)");
    query.bindValue(":weight", weight);

    if (query.exec()) {
        qDebug() << "Weight saved to database successfully.";
        return true;
    } else {
        qDebug() << "Failed to save weight to database: " << query.lastError();
        return false;
    }
}

 QByteArray Arduino::read_from_arduino()
{
     if (!serial->isOpen()) {
         qDebug() << "serial1 is not open!";
         return 0;
     }
    if(serial->isReadable()){
         data=serial->readAll(); //récupérer les données reçues

         return data;
    }
 }


void Arduino::write_to_arduino( QByteArray d)

{

    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }


}
QByteArray Arduino::read_from_arduino1()
{
    if (!serial1->isOpen()) {
        qDebug() << "serial1 is not open!";
        return 0;
    }
   if(serial1->isReadable()){
        data=serial1->readAll(); //récupérer les données reçues

        return data;
   }
}


void Arduino::write_to_arduino1( QByteArray d)

{

   if(serial1->isWritable()){
       serial1->write(d);  // envoyer des donnés vers Arduino
   }else{
       qDebug() << "Couldn't write to serial!";
   }


}
*/
#include <QLabel>

#include "arduino.h"
#include <QSqlError>

Arduino::Arduino(QObject* parent) : QObject(parent), serial(new QSerialPort), serial1(new QSerialPort), arduino_is_available(false)
{
    arduino_port_name = "";
    arduino_port_name1 = "";
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort* Arduino::getserial()
{
    return serial;
}

QString Arduino::getarduino_port_name1()
{
    return arduino_port_name1;
}

QSerialPort* Arduino::getserial1()
{
    return serial1;
}

int Arduino::connect_arduino_common(QSerialPort* serialPort)
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                qDebug() << "Arduino found on port:" << arduino_port_name;
                serialPort->setPortName(arduino_port_name);
                if (serialPort->open(QSerialPort::ReadWrite)) {
                    serialPort->setBaudRate(QSerialPort::Baud9600);
                    serialPort->setDataBits(QSerialPort::Data8);
                    serialPort->setParity(QSerialPort::NoParity);
                    serialPort->setStopBits(QSerialPort::OneStop);
                    serialPort->setFlowControl(QSerialPort::NoFlowControl);
                    return 0;
                } else {
                    qDebug() << "Failed to open port:" << arduino_port_name;
                    return 1;
                }
            }
        }
    }
    qDebug() << "No Arduino found.";
    return -1;
}

int Arduino::connect_arduino()
{
    return connect_arduino_common(serial);
}

int Arduino::connect_arduino1() {
    qDebug() << "Starting connect_arduino1()...";
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Checking port:" << serial_port_info.portName();
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            qDebug() << "Vendor ID:" << serial_port_info.vendorIdentifier()
                     << "Product ID:" << serial_port_info.productIdentifier();
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                qDebug() << "Arduino found on port:" << arduino_port_name;
            }
        }
    }

    if (arduino_is_available) {
        serial1->setPortName(arduino_port_name);
        if (serial1->open(QSerialPort::ReadWrite)) {
            serial1->setBaudRate(QSerialPort::Baud9600);
            serial1->setDataBits(QSerialPort::Data8);
            serial1->setParity(QSerialPort::NoParity);
            serial1->setStopBits(QSerialPort::OneStop);
            serial1->setFlowControl(QSerialPort::NoFlowControl);
            qDebug() << "Connected to serial1 on port:" << arduino_port_name;
            return 0;
        } else {
            qDebug() << "Failed to open serial1.";
            return 1;
        }
    }

    qDebug() << "No Arduino available for serial1.";
    return -1;
}

int Arduino::close_arduino()
{
    bool serialClosed = true;
    if (serial->isOpen()) {
        serial->close();
        serialClosed = false;
    }

    if (serial1->isOpen()) {
        serial1->close();
        serialClosed = false;
    }

    return serialClosed ? 0 : 1; // Return 0 if all ports are closed
}

void Arduino::readWeightFromSensor()
{
    QByteArray rawData = serial->readAll();
    qDebug() << "Raw data received from Arduino: " << rawData;

    QString rawDataStr = QString::fromUtf8(rawData).trimmed();
    accumulatedData.append(rawDataStr.toUtf8());
    qDebug() << "Accumulated data: " << accumulatedData;

    QString accumulatedDataStr = QString::fromUtf8(accumulatedData);

    QRegularExpression regex("Poids\\s*[:]?\\s*(-?\\d*\\.?\\d+)");
    QRegularExpressionMatch match = regex.match(accumulatedDataStr);

    if (match.hasMatch()) {
        QString weight = match.captured(1);
        qDebug() << "Extracted weight: " << weight;
        emit weightDetected(weight.toDouble());
        accumulatedData.clear();
    } else {
        qDebug() << "No weight data found.";
    }
}

bool Arduino::saveWeightToDatabase(double weight)
{
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (POIDS) VALUES (:weight)");
    query.bindValue(":weight", weight);

    if (query.exec()) {
        qDebug() << "Weight saved to database successfully.";
        return true;
    } else {
        qDebug() << "Failed to save weight to database: " << query.lastError();
        return false;
    }
}

QByteArray Arduino::read_from_arduino()
{
    if (!serial->isOpen()) {
        qDebug() << "serial is not open!";
        return QByteArray();
    }
    if (serial->isReadable()) {
        data = serial->readAll();
        return data;
    }
    return QByteArray();
}

void Arduino::write_to_arduino(QByteArray data)
{
    if (serial->isWritable()) {
        serial->write(data);
    } else {
        qDebug() << "Couldn't write to serial!";
    }
}

QByteArray Arduino::read_from_arduino1()
{
    if (!serial1->isOpen()) {
        qDebug() << "serial1 is not open!";
        return QByteArray();
    }
    if (serial1->isReadable()) {
        data = serial1->readAll();
        return data;
    }
    return QByteArray();
}

void Arduino::write_to_arduino1(QByteArray data)
{
    if (serial1->isWritable()) {
        serial1->write(data);
    } else {
        qDebug() << "Couldn't write to serial!";
    }
}





bool Arduino::updateClientState(int clientId, QLabel* label) {
    if (!serial->isReadable()) {
        qDebug() << "Serial is not readable!";
        return false;
    }

    QByteArray data = read_from_arduino();
    qDebug() << "Raw data from Arduino:" << data;

    QString rawDataStr = QString::fromUtf8(data).trimmed();
    QRegularExpression regex("Poids\\s*[:]?\\s*(-?\\d+)");
    QRegularExpressionMatch match = regex.match(rawDataStr);

    int state = 0; // Par défaut, état = 0
    if (match.hasMatch()) {
           state = 1;
           int weight = match.captured(1).toInt(); // Extract weight if needed
           qDebug() << "Extracted weight:" << weight << ", Computed state:" << state;
       } else {
           qDebug() << "No valid data received from Arduino!";
       }

    // Mise à jour du QLabel
    if (label) {
        label->setText(QString::number(state));
    }

    // Mise à jour de la base de données
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET ETAT = :state WHERE IDCL = :id");
    query.bindValue(":state", state);
    query.bindValue(":id", clientId);

    if (query.exec()) {
        qDebug() << "Database updated successfully for client ID:" << clientId;
        return true;
    } else {
        qDebug() << "Database update failed:" << query.lastError();
        return false;
    }
}
void Arduino::updateStateFromSensor() {
    if (!serial->isReadable()) {
        qDebug() << "Serial is not readable!";
        return;
    }

    QByteArray data = read_from_arduino();
    qDebug() << "Raw data from Arduino:" << data;

    QString rawDataStr = QString::fromUtf8(data).trimmed();
    QRegularExpression regex("Poids\\s*[:]?\\s*(-?\\d+)");
    QRegularExpressionMatch match = regex.match(rawDataStr);

    int state = 0; // Par défaut, état = 0
    if (match.hasMatch()) {
        state = 1;
        int weight = match.captured(1).toInt(); // Extract weight if needed
        qDebug() << "Extracted weight:" << weight << ", Computed state:" << state;
    } else {
        qDebug() << "No valid data received from Arduino!";
    }

    qDebug() << "Computed state:" << state;
    emit stateChanged(state); // Émettre l'état mis à jour
}
