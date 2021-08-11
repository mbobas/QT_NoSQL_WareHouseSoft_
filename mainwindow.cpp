#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //oddajemy baze o danym typie
    // dla bazy posgres wiecej zmiennym, http, login, pass
    QSqlDatabase baza = QSqlDatabase::addDatabase("QSQLITE");

    //jesli plik nie zostanie odnaleziony to QT tworzy nowa baze
    //baza danych musi byc w katalogu build lub pelna sciezka
    //\QT\build-nienazwany-Desktop_Qt_5_15_1_MinGW_64_bit-Debug

    baza.setDatabaseName("hurtownia_v5.db");
    if(!baza.open()) {
        qDebug()<<"Blad polaczenia";
    }else {
        qDebug()<<"Polaczono z hurtownia.db";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEdit_kontrahenci_textChanged(const QString &arg1)
{
    QString wyszukajKontrahenta;
    wyszukajKontrahenta="nazwa LIKE '%" + arg1 +"%'";

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("kontrahent");
    model->setFilter(wyszukajKontrahenta);
    model->select();

    ui->tableView_kontrahenci->setModel(model);
    ui->tableView_kontrahenci->show();

}

void MainWindow::on_pushButton_dodajKontrahenta_clicked()
{
    QString nazwa, nip, tel, ulica, kod_pocztowy, miasto;
    bool dostawca, odbiorca;
    nazwa = ui->lineEdit_nazwaKontrahenta->text();
    nip = ui->lineEdit_nip->text();
    tel = ui->lineEdit_tel->text();
    ulica = ui->lineEdit_ulica->text();
    kod_pocztowy = ui->lineEdit_kod_pocztowy->text();
    miasto = ui->lineEdit_Miasto->text();
    dostawca = ui->radioButton_dostawca->isChecked();
    odbiorca = ui->radioButton_odbiorca->isChecked();

    if (!nazwa.isEmpty() && !nip.isEmpty() && !tel.isEmpty() && !ulica.isEmpty() && !kod_pocztowy.isEmpty() && !miasto.isEmpty() && (dostawca == true || odbiorca ==true ) ) {
        QSqlQuery zapytanie;
        zapytanie.prepare("INSERT INTO kontrahent(nazwa, nip, tel, ulica, kod_pocztowy, miasto, dostawca, odbiorca) VALUES (:nazwa, :nip, :tel, :ulica, :kod_pocztowy, :miasto, :dostawca, :odbiorca);");
        // ('Michal Gulczynski', 8810205891, '785612622', 'Testowa 14', '87-100', 'Torun', FALSE, TRUE);
        zapytanie.bindValue(":nazwa", nazwa);
        zapytanie.bindValue(":nip", nip);
        zapytanie.bindValue(":tel", tel);
        zapytanie.bindValue(":ulica", ulica);
        zapytanie.bindValue(":kod_pocztowy", kod_pocztowy);
        zapytanie.bindValue(":miasto", miasto);
        zapytanie.bindValue(":dostawca", dostawca);
        zapytanie.bindValue(":odbiorca", odbiorca);

        bool sukces = zapytanie.exec();
        ui->label_komunikatDodaniaKontrahenta->setText("Kontrahent dodany");
    } else {
        ui->label_komunikatDodaniaKontrahenta->setText("Błędne dane");
    }

}

void MainWindow::on_pushButton_usunKontrahenta_clicked()
{
    QString nazwa, nip;
    nazwa = ui->lineEdit_nazwaKontrahenta_usun->text();
    nip = ui->lineEdit_nipkontrahenta_usun->text();


    QSqlQuery zapytanie;
    zapytanie.prepare("DELETE from kontrahent WHERE nazwa=:nazwa AND nip=:nip;");
    // ('Michal Gulczynski', 8810205891, '785612622', 'Testowa 14', '87-100', 'Torun', FALSE, TRUE);
    zapytanie.bindValue(":nazwa", nazwa);
    zapytanie.bindValue(":nip", nip);


    bool sukces = zapytanie.exec();
    qDebug() << sukces;
}
