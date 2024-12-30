#ifndef CALENDRIERCONGE_H
#define CALENDRIERCONGE_H

#include <QWidget>
#include <QCalendarWidget>
#include <QDateEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

class CongesManager;
class Personnel;  // Assuming you have the Personnel class

class CalendrierConge : public QWidget
{
    Q_OBJECT

public:
    explicit CalendrierConge(QWidget *parent = nullptr);
    ~CalendrierConge();

private slots:
    void ajouterConge();  // Slot to add leave
    void afficherConge(); // Slot to display leave for a selected date
    void fermerCalendrier(); // Slot to close the calendar

private:
    QCalendarWidget *calendar;      // Calendar widget
    QDateEdit *dateDebutEdit;       // DateEdit widget for start date
    QDateEdit *dateFinEdit;         // DateEdit widget for end date
    CongesManager *congesManager;   // Manager for handling leaves
};

#endif // CALENDRIERCONGE_H
