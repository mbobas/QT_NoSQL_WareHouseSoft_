#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>


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


//kontrahenci - konstruktor
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("kontrahent");
    model->select();
    ui->tableView_kontrahenci->setModel(model);
    ui->tableView_kontrahenci->show();

//magazyn konstruktor
    QSqlRelationalTableModel *model2 = new QSqlRelationalTableModel;
    model2->setTable("magazyn");
    //ktora kolumne chce polaczyc
    model2->setRelation(0, QSqlRelation("produkty", "produkt_id", "nazwa"));
    model2->select();
    ui->tableView_magazyn->setModel(model2);
    ui->tableView_magazyn->show();

//sprzedaz konstruktor
    QSqlRelationalTableModel *model3 = new QSqlRelationalTableModel;
    model3->setTable("sprzedaz");
    //ktora kolumne chce polaczyc
   model3->setRelation(1, QSqlRelation("kontrahent", "id_kontrahenta", "nazwa"));
   model3->setRelation(2, QSqlRelation("produkty", "produkt_id", "nazwa"));
   model3->setRelation(4, QSqlRelation("produkty", "produkt_id", "nazwa"));
   model3->setRelation(6, QSqlRelation("produkty", "produkt_id", "nazwa"));
    model3->select();
    ui->tableView_sprzedaz->setModel(model3);
    ui->tableView_sprzedaz->show();

//faktury konstruktor
    QSqlRelationalTableModel *model5 = new QSqlRelationalTableModel;
    model5->setTable("faktury");
    //ktora kolumne chce polaczyc
    model5->setRelation(3, QSqlRelation("produkty", "produkt_id", "nazwa"));
    model5->setRelation(5, QSqlRelation("produkty", "produkt_id", "nazwa"));
    model5->setRelation(7, QSqlRelation("produkty", "produkt_id", "nazwa"));
    model5->select();
    ui->tableView_faktury->setModel(model5);
    ui->tableView_faktury->show();

    sprzedaz_combobox_produkt_konstruktor();
    sprzedaz_combobox_produkt_konstruktor2();
    sprzedaz_combobox_produkt_konstruktor3();

//sprzedaz - combobox - kontrahent - konstruktor
        //zapytanie zwraca boola
        QSqlQuery zapytanieKontrahent;
        //query z pola tekstowego
        QString tekstKontrahent;
        tekstKontrahent = "SELECT id_kontrahenta, nazwa, nip FROM kontrahent;";
        bool sukces1 = zapytanieKontrahent.exec(tekstKontrahent);
        qDebug() << sukces1;
        //pobieramy ilosc pol
        int ile_pol1 = zapytanieKontrahent.record().count();
        //iterujemy po wszytkich rekordach zwroconych przez zpaytanie
        while(zapytanieKontrahent.next())
        {
            QString t = "";
            for (int i=0; i<ile_pol1; i++){
                t +=zapytanieKontrahent.value(i).toString()+" | ";
            }
             ui->comboBox_sprzedaz_kontrahent->addItem(t);
        }
//produkty konstruktor
//const QString &arg = "";
on_lineEdit_produkt_textChanged("");
on_lineEdit_kategorie_textChanged("");
PK_combobox_kategoria_konstruktor();
on_lineEdit_dostawa_wyszukajtowar_textChanged("");

}




MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::sprzedaz_combobox_produkt_konstruktor(){
        //zapytanie zwraca boola
        QSqlQuery zapytanie;
        //query z pola tekstowego
        QString tekst;
        tekst = "SELECT produkt_id, nazwa, cena FROM produkty;";
        bool sukces = zapytanie.exec(tekst);
        qDebug() << sukces;
        //pobieramy ilosc pol
        int ile_pol = zapytanie.record().count();
        //iterujemy po wszytkich rekordach zwroconych przez zpaytanie
        while(zapytanie.next())
        {
            QString t = "";
            for (int i=0; i<ile_pol; i++){
                t +=zapytanie.value(i).toString()+" | ";
            }
             ui->comboBox->addItem(t);
        }
}
void MainWindow::sprzedaz_combobox_produkt_konstruktor2(){
        //zapytanie zwraca boola
        QSqlQuery zapytanie;
        //query z pola tekstowego
        QString tekst;
        tekst = "SELECT produkt_id, nazwa, cena FROM produkty;";
        bool sukces = zapytanie.exec(tekst);
        qDebug() << sukces;
        //pobieramy ilosc pol
        int ile_pol = zapytanie.record().count();
        //iterujemy po wszytkich rekordach zwroconych przez zpaytanie
        while(zapytanie.next())
        {
            QString t = "";
            for (int i=0; i<ile_pol; i++){
                t +=zapytanie.value(i).toString()+" | ";
            }
             ui->comboBox_sprzedaz_2->addItem(t);
        }
}
void MainWindow::PK_combobox_kategoria_konstruktor(){

        ui->lineEdit_PK_produkt_id->setVisible(0);
        ui->lineEdit_PK_nazwa->setVisible(0);
        ui->lineEdit_PK_cena->setVisible(0);
        ui->lineEdit_PK_waga->setVisible(0);
        ui->comboBox_PK_kategoria->setVisible(0);

        //zapytanie zwraca boola
        QSqlQuery zapytanie;
        //query z pola tekstowego
        QString tekst;
        tekst = "SELECT id_kategoria, nazwa FROM kategoria;";
        bool sukces = zapytanie.exec(tekst);
        qDebug() << sukces;
        //pobieramy ilosc pol
        int ile_pol = zapytanie.record().count();
        //iterujemy po wszytkich rekordach zwroconych przez zpaytanie
        while(zapytanie.next())
        {
            QString t = "";
            for (int i=0; i<ile_pol; i++){
                t +=zapytanie.value(i).toString()+" | ";
            }
             ui->comboBox_PK_kategoria->addItem(t);
        }
}


void MainWindow::sprzedaz_combobox_produkt_konstruktor3(){
        //zapytanie zwraca boola
        QSqlQuery zapytanie;
        //query z pola tekstowego
        QString tekst;
        tekst = "SELECT produkt_id, nazwa, cena FROM produkty;";
        bool sukces = zapytanie.exec(tekst);
        qDebug() << sukces;
        //pobieramy ilosc pol
        int ile_pol = zapytanie.record().count();
        //iterujemy po wszytkich rekordach zwroconych przez zpaytanie
        while(zapytanie.next())
        {
            QString t = "";
            for (int i=0; i<ile_pol; i++){
                t +=zapytanie.value(i).toString()+" | ";
            }
             ui->comboBox_sprzedaz_3->addItem(t);
        }
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
        if (sukces) {
            ui->label_komunikatDodaniaKontrahenta->setText("Kontrahent dodany");
        }else {
            ui->label_komunikatDodaniaKontrahenta->setText("Niepoprawne dane");
        }

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

void MainWindow::on_lineEdit_magazyn_wyszukajtowar_textChanged(const QString &arg1)
{
    QString wyszukajWMagazynie;
    wyszukajWMagazynie="nazwa LIKE '%" + arg1 +"%'";

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel;
    model->setTable("magazyn");
    //ktora kolumne chce polaczyc
    model->setRelation(0, QSqlRelation("produkty", "produkt_id", "nazwa"));
    model->setFilter(wyszukajWMagazynie);
    model->select();

    ui->tableView_magazyn->setModel(model);
    ui->tableView_magazyn->show();

}

void MainWindow::on_checkBox_sprzed_1_clicked(bool checked)
{
    if (checked) {
        counterSprzedaz=counterSprzedaz+1;
        ui->comboBox->setEnabled(1);
    }else {
        counterSprzedaz=counterSprzedaz-1;
        ui->comboBox->setEnabled(0);
         ui->lineEdit_sprzedaz_cena1->setEnabled(0);
    }
    qDebug() << counterSprzedaz;
}

void MainWindow::on_checkBox_sprzed_2_clicked(bool checked)
{
    if (checked) {
        counterSprzedaz=counterSprzedaz+1;
        ui->comboBox_sprzedaz_2->setEnabled(1);
    }else {
        counterSprzedaz=counterSprzedaz-1;
        ui->comboBox_sprzedaz_2->setEnabled(0);
        ui->lineEdit_sprzedaz_cena_2->setEnabled(0);
    }
    qDebug() << counterSprzedaz;
}

void MainWindow::on_checkBox_sprzed_3_clicked(bool checked)
{
    if (checked) {
        counterSprzedaz=counterSprzedaz+1;
        ui->comboBox_sprzedaz_3->setEnabled(1);
    }else {
        counterSprzedaz=counterSprzedaz-1;
        ui->comboBox_sprzedaz_3->setEnabled(0);
         ui->lineEdit_sprzedaz_cena1_3->setEnabled(0);
    }
    qDebug() << counterSprzedaz;
}
double MainWindow::cena_produktu_sprzedaz(QString produkt) {
    double cena;
    //zapytanie zwraca boola
    QSqlQuery zapytanie;
    //query z pola tekstowego
    QString tekst;
    tekst = "SELECT cena FROM produkty WHERE produkt_id="+produkt+";";
    bool sukces = zapytanie.exec(tekst);
    qDebug() << sukces;
    //pobieramy ilosc pol
    int ile_pol = zapytanie.record().count();
    //iterujemy po wszytkich rekordach zwroconych przez zpaytanie
    while(zapytanie.next())
    {
        QString t = "";
        for (int i=0; i<ile_pol; i++){
            t +=zapytanie.value(i).toString();
            //qDebug() << t;
        }
        cena = t.toDouble();
        //qDebug() << cena;
    }
    return cena;
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    ui->lineEdit_sprzedaz_cena1->setEnabled(1);
    QString wybrany_produkt;
    wybrany_produkt=arg1;
    qDebug() << wybrany_produkt;
    produkt1=wybrany_produkt.remove(wybrany_produkt.indexOf(" "), wybrany_produkt.length());
    qDebug() << produkt1;
    qDebug() << cena_produktu_sprzedaz(produkt1);
    cena1 = cena_produktu_sprzedaz(produkt1);
    odswiezCeneBruttoINetto();
}

void MainWindow::on_comboBox_sprzedaz_2_activated(const QString &arg1)
{
    ui->lineEdit_sprzedaz_cena_2->setEnabled(1);
    QString wybrany_produkt;
    wybrany_produkt=arg1;
    qDebug() << wybrany_produkt;
    produkt2=wybrany_produkt.remove(wybrany_produkt.indexOf(" "), wybrany_produkt.length());
    qDebug() << produkt2;
    cena2 = cena_produktu_sprzedaz(produkt2);
    odswiezCeneBruttoINetto();
}

void MainWindow::on_comboBox_sprzedaz_3_activated(const QString &arg1)
{
    ui->lineEdit_sprzedaz_cena1_3->setEnabled(1);
    QString wybrany_produkt;
    wybrany_produkt=arg1;
    qDebug() << wybrany_produkt;
    produkt3=wybrany_produkt.remove(wybrany_produkt.indexOf(" "), wybrany_produkt.length());
    qDebug() << produkt3;
    cena3 = cena_produktu_sprzedaz(produkt3);
    odswiezCeneBruttoINetto();
}

void MainWindow::on_comboBox_sprzedaz_kontrahent_activated(const QString &arg1)
{
    QString wybrany_kontrahent;
    wybrany_kontrahent=arg1;
    qDebug() << wybrany_kontrahent;
    id_kontrahenta=wybrany_kontrahent.remove(wybrany_kontrahent.indexOf(" "), wybrany_kontrahent.length());
    qDebug() << id_kontrahenta;
    odswiezCeneBruttoINetto();
}

void MainWindow::odswiezCeneBruttoINetto() {
    razemN=sumaN1+sumaN2+sumaN3;
    razemB=razemN*VAT;
    ui->label_sprzed_suma_razemnetto->setText(QString::number(razemN));
    ui->label_sprzed_suma_razembrutto->setText(QString::number(razemB));
}

void MainWindow::on_lineEdit_sprzedaz_cena1_textChanged(const QString &arg1)
{
    sumaN1=cena1*arg1.toDouble();
    ui->label_sprzed_sum1->setText(QString::number(sumaN1));
    ui->label_sprzed_sumb1->setText(QString::number(sumaN1*VAT));
    odswiezCeneBruttoINetto();
}

void MainWindow::on_lineEdit_sprzedaz_cena_2_textChanged(const QString &arg1)
{
    sumaN2=cena2*arg1.toDouble();
    ui->label_sprzed_sum2->setText(QString::number(sumaN2));
    ui->label_sprzed_sumb2->setText(QString::number(sumaN2*VAT));
    odswiezCeneBruttoINetto();
}

void MainWindow::on_lineEdit_sprzedaz_cena1_3_textChanged(const QString &arg1)
{
    sumaN3=cena3*arg1.toDouble();
    ui->label_sprzed_sum3->setText(QString::number(sumaN3));
    ui->label_sprzed_sumb3->setText(QString::number(sumaN3*VAT));
    odswiezCeneBruttoINetto();
}

void MainWindow::on_pushButton_sprzedaz_clicked()
{

    ilosc_pozycji = QString::number(counterSprzedaz);
    data_sprzedazy ="2021-08-12";

    QString ilosc1_2;
    ilosc1_2 = ui->lineEdit_sprzedaz_cena1->text();
    QString ilosc2_2;
    ilosc2_2 = ui->lineEdit_sprzedaz_cena_2->text();
    QString ilosc3_2;
    ilosc3_2 = ui->lineEdit_sprzedaz_cena1_3->text();

    if (counterSprzedaz == 0 || id_kontrahenta.isEmpty()){
        ui->label_sprzed_komunikat->setText("Wybierz co najmniej jedn produkt i kontrahenta, aby sprzedać");
    }

    if(counterSprzedaz == 1 && !id_kontrahenta.isEmpty() && !ilosc1_2.isEmpty() && !produkt1.isEmpty() && ilosc1_2 != "0") {
        QSqlQuery zapytanie;
        zapytanie.prepare("INSERT INTO sprzedaz(id_kontrahenta, produkt1_id, ilosc1, produkt2_id, ilosc2, produkt3_id, ilosc3, data_sprzedazy, ilosc_pozycji) VALUES (:id_kontrahenta, :produkt1, :ilosc1_2, 34, 1, 34, 1, :data_sprzedazy, :ilosc_pozycji);");
        zapytanie.bindValue(":id_kontrahenta", id_kontrahenta);
        zapytanie.bindValue(":produkt1", produkt1);
        zapytanie.bindValue(":ilosc1_2", ilosc1_2);
        zapytanie.bindValue(":produkt2", produkt2);
        zapytanie.bindValue(":ilosc2_2", ilosc2_2);
        zapytanie.bindValue(":produkt3", produkt3);
        zapytanie.bindValue(":ilosc3_2", ilosc3_2);
        zapytanie.bindValue(":data_sprzedazy", data_sprzedazy);
        zapytanie.bindValue(":ilosc_pozycji", ilosc_pozycji);
        bool sukces = zapytanie.exec();
        qDebug() << sukces;
        if (sukces) {
            ui->label_sprzed_komunikat->setText("Sprzedano 1 produkt");
        }
    } else {
        ui->label_sprzed_komunikat->setText("Sprawdz lub wybierz jeszcze raz watości");
    }
     if(counterSprzedaz == 2 && !id_kontrahenta.isEmpty() && !ilosc1_2.isEmpty() && !produkt1.isEmpty() && !ilosc2_2.isEmpty() && !produkt2.isEmpty() && ilosc1_2 != "0" && ilosc2_2 != "0" ) {
        QSqlQuery zapytanie;
        zapytanie.prepare("INSERT INTO sprzedaz(id_kontrahenta, produkt1_id, ilosc1, produkt2_id, ilosc2, produkt3_id, ilosc3, data_sprzedazy, ilosc_pozycji) VALUES (:id_kontrahenta, :produkt1, :ilosc1_2, :produkt2, :ilosc2_2, 34, 1, :data_sprzedazy, :ilosc_pozycji);");
        zapytanie.bindValue(":id_kontrahenta", id_kontrahenta);
        zapytanie.bindValue(":produkt1", produkt1);
        zapytanie.bindValue(":ilosc1_2", ilosc1_2);
        zapytanie.bindValue(":produkt2", produkt2);
        zapytanie.bindValue(":ilosc2_2", ilosc2_2);
        zapytanie.bindValue(":produkt3", produkt3);
        zapytanie.bindValue(":ilosc3_2", ilosc3_2);
        zapytanie.bindValue(":data_sprzedazy", data_sprzedazy);
        zapytanie.bindValue(":ilosc_pozycji", ilosc_pozycji);
        bool sukces = zapytanie.exec();
        qDebug() << sukces;
        if (sukces) {
            ui->label_sprzed_komunikat->setText("Sprzedano 2 produkty");
        }
    }else {
         ui->label_sprzed_komunikat->setText("Sprawdz lub wybierz jeszcze raz watości");
    }

     if(counterSprzedaz == 3 && !id_kontrahenta.isEmpty() && !ilosc1_2.isEmpty() && !produkt1.isEmpty() && !ilosc2_2.isEmpty() && !produkt2.isEmpty() && !ilosc3_2.isEmpty() && !produkt3.isEmpty() && ilosc1_2 != "0" && ilosc2_2 != "0" && ilosc3_2 != "0") {
        QSqlQuery zapytanie;
        zapytanie.prepare("INSERT INTO sprzedaz(id_kontrahenta, produkt1_id, ilosc1, produkt2_id, ilosc2, produkt3_id, ilosc3, data_sprzedazy, ilosc_pozycji) VALUES (:id_kontrahenta, :produkt1, :ilosc1_2, :produkt2, :ilosc2_2, :produkt3, :ilosc3_2, :data_sprzedazy, :ilosc_pozycji);");
        zapytanie.bindValue(":id_kontrahenta", id_kontrahenta);
        zapytanie.bindValue(":produkt1", produkt1);
        zapytanie.bindValue(":ilosc1_2", ilosc1_2);
        zapytanie.bindValue(":produkt2", produkt2);
        zapytanie.bindValue(":ilosc2_2", ilosc2_2);
        zapytanie.bindValue(":produkt3", produkt3);
        zapytanie.bindValue(":ilosc3_2", ilosc3_2);
        zapytanie.bindValue(":data_sprzedazy", data_sprzedazy);
        zapytanie.bindValue(":ilosc_pozycji", ilosc_pozycji);
        bool sukces = zapytanie.exec();
        qDebug() << sukces;
        if (sukces) {
            ui->label_sprzed_komunikat->setText("Sprzedano 3 produkty");
        }
    }else {
         ui->label_sprzed_komunikat->setText("Sprawdz lub wybierz jeszcze raz watości");
        }

}

void MainWindow::on_lineEdit_sprzedaz_wyszukajtowar_textChanged(const QString &arg1)
{
    QString wyszukajWMagazynie;
    wyszukajWMagazynie="kontrahent_nazwa_4 LIKE '%" + arg1 +"%' OR data_sprzedazy LIKE '%" + arg1 +"%'";

    QSqlRelationalTableModel *model4 = new QSqlRelationalTableModel;
    model4->setTable("sprzedaz");
    //ktora kolumne chce polaczyc
    model4->setRelation(1, QSqlRelation("kontrahent", "id_kontrahenta", "nazwa"));
    model4->setRelation(2, QSqlRelation("produkty", "produkt_id", "nazwa"));
    model4->setRelation(4, QSqlRelation("produkty", "produkt_id", "nazwa"));
    model4->setRelation(6, QSqlRelation("produkty", "produkt_id", "nazwa"));
    model4->setFilter(wyszukajWMagazynie);
    model4->select();
    ui->tableView_sprzedaz->setModel(model4);
    ui->tableView_sprzedaz->show();


}

void MainWindow::on_lineEdit_faktury_wyszukaj_textChanged(const QString &arg1)
{
    QString wyszukajFakture;
    wyszukajFakture="nazwa_kontrahenta LIKE '%" + arg1 +"%' OR nip LIKE '%" + arg1 +"%'";

    QSqlRelationalTableModel *model5 = new QSqlRelationalTableModel;
    model5->setTable("faktury");
    //ktora kolumne chce polaczyc
    model5->setRelation(3, QSqlRelation("produkty", "produkt_id", "nazwa"));
    model5->setRelation(5, QSqlRelation("produkty", "produkt_id", "nazwa"));
    model5->setRelation(7, QSqlRelation("produkty", "produkt_id", "nazwa"));
    model5->setFilter(wyszukajFakture);
    model5->select();
    ui->tableView_faktury->setModel(model5);
    ui->tableView_faktury->show();
}

void MainWindow::on_lineEdit_produkt_textChanged(const QString &arg1)
{
    QString wyszukajProdukt;
    wyszukajProdukt="nazwa LIKE '%" + arg1 +"%'";

    QSqlTableModel *model6 = new QSqlTableModel;
    model6->setTable("produkty");
    model6->setFilter(wyszukajProdukt);
    model6->select();

    ui->tableView_produkty->setModel(model6);
    ui->tableView_produkty->show();
}

void MainWindow::on_lineEdit_kategorie_textChanged(const QString &arg1)
{
    QString wyszukajProdukt;
    wyszukajProdukt="nazwa LIKE '%" + arg1 +"%'";

    QSqlTableModel *model6 = new QSqlTableModel;
    model6->setTable("kategoria");
    model6->setFilter(wyszukajProdukt);
    model6->select();

    ui->tableView_kategorie->setModel(model6);
    ui->tableView_kategorie->show();
}

void MainWindow::on_comboBox_PK_kategoria_activated(const QString &arg1)
{
    QString wybrana_kategoria;
    wybrana_kategoria=arg1;
    qDebug() << wybrana_kategoria;
    kategoria=wybrana_kategoria.remove(wybrana_kategoria.indexOf(" "), wybrana_kategoria.length());
    qDebug() << kategoria;
}

void MainWindow::clearFieldsPK(){
    ui->lineEdit_PK_produkt_id->clear();
    ui->lineEdit_PK_nazwa->clear();
    ui->lineEdit_PK_cena->clear();
    ui->lineEdit_PK_waga->clear();
}
void MainWindow::on_radioButton_dodajProdukt_clicked(bool checked)
{
    if (checked) {
        pk_check=1;
        ui->lineEdit_PK_produkt_id->setVisible(0);
        ui->lineEdit_PK_nazwa->setVisible(1);
        ui->lineEdit_PK_cena->setVisible(1);
        ui->lineEdit_PK_waga->setVisible(1);
        ui->comboBox_PK_kategoria->setVisible(1);
        clearFieldsPK();
    }
}

void MainWindow::on_radioButton_dodajKategori_clicked(bool checked)
{
    if (checked) {
    pk_check=2;
    ui->lineEdit_PK_produkt_id->setVisible(0);
    ui->lineEdit_PK_nazwa->setVisible(1);
    ui->lineEdit_PK_cena->setVisible(0);
    ui->lineEdit_PK_waga->setVisible(0);
    ui->comboBox_PK_kategoria->setVisible(0);
    clearFieldsPK();
    }
}


void MainWindow::on_radioButton_usunProdukt_clicked(bool checked)
{
    if (checked) {
    pk_check=3;
    ui->lineEdit_PK_produkt_id->setVisible(1);
    ui->lineEdit_PK_nazwa->setVisible(1);
    ui->lineEdit_PK_cena->setVisible(0);
    ui->lineEdit_PK_waga->setVisible(0);
    ui->comboBox_PK_kategoria->setVisible(0);
    clearFieldsPK();
    }
}

void MainWindow::on_radioButton_usunKategori_clicked(bool checked)
{
    if (checked) {
    pk_check=4;
    ui->lineEdit_PK_produkt_id->setVisible(0);
    ui->lineEdit_PK_nazwa->setVisible(0);
    ui->lineEdit_PK_cena->setVisible(0);
    ui->lineEdit_PK_waga->setVisible(0);
    ui->comboBox_PK_kategoria->setVisible(1);
    clearFieldsPK();
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (pk_check==1){
        QString nazwa  = ui->lineEdit_PK_nazwa->text();
        QString wagaString  = ui->lineEdit_PK_waga->text();
        QString cenaString  = ui->lineEdit_PK_cena->text();

        double waga = wagaString.toDouble();
        double cena = cenaString.toDouble();

        //dodaj produkt
        QSqlQuery zapytanie;
        zapytanie.prepare("INSERT INTO produkty(nazwa, waga, cena, id_kategoria) VALUES (:nazwa, :waga, :cena, :id_kategoria);");
        zapytanie.bindValue(":nazwa", nazwa);
        zapytanie.bindValue(":waga", waga);
        zapytanie.bindValue(":cena", cena);
        zapytanie.bindValue(":id_kategoria", kategoria);
        bool sukces = zapytanie.exec();
        qDebug() << sukces;
        if (sukces) {
            ui->label_PK->setText("Dodano prdukt");
        }else {
            ui->label_PK->setText("Błąd. Nie dodano prduktu.");
        }
    }
    if (pk_check==2){
        QString nazwa  = ui->lineEdit_PK_nazwa->text();
        //dodaj kategorię
        QSqlQuery zapytanie;
        zapytanie.prepare("INSERT INTO kategoria(nazwa) VALUES (:nazwa);");
        zapytanie.bindValue(":nazwa", nazwa);
        bool sukces = zapytanie.exec();
        qDebug() << sukces;
        if (sukces) {
            ui->label_PK->setText("Dodano kategorię");
        }else {
            ui->label_PK->setText("Błąd. Nie dodano kategorii.");
        }
    }

}
QString MainWindow::query(QString query){
    QSqlQuery zapytanie;
    //query z pola tekstowego
    QString tekst;
    tekst = query;
    QString t = "";

    bool sukces = zapytanie.exec(query);
    qDebug() << sukces;

    int ile_pol = zapytanie.record().count();

    //iterujemy po wszytkich rekordach zwroconych przez zpaytanie
    while(zapytanie.next())
    {
        for (int i=0; i<ile_pol; i++){
            t +=zapytanie.value(i).toString();
    }

}
}
void MainWindow::on_lineEdit_dostawa_wyszukajtowar_textChanged(const QString &arg1)
{
//    QString wyszukajDostawy;
//    wyszukajDostawy="nazwa LIKE '%" + arg1 +"%'";

//    QSqlRelationalTableModel *model = new QSqlRelationalTableModel;
//    model->setTable("dostawa");
//    //ktora kolumne chce polaczyc
//    model->setRelation(2, QSqlRelation("kontrahent", "id_kontrahenta", "nazwa"));
//    model->setFilter(wyszukajDostawy);
//    model->select();

//    ui->tableView_dostawy->setModel(model);
//    ui->tableView_dostawy->show();
//    ui->tableWidget->clear();



//zapytanie zwraca boola
//QSqlQuery zapytanie;
//    //query z pola tekstowego
//    QString tekst;
//    tekst = arg1;

//    bool sukces = zapytanie.exec("SELECT * FROM DOSTAWA WHERE data_dostawy LIKE '%"+tekst+"%';");
//    qDebug() << sukces;

//    int ile_pol = zapytanie.record().count();
//    ui->tableWidget_dostawa->setColumnCount(ile_pol);
//    ui->tableWidget_dostawa->setRowCount(0);

//    //pobieramy ilosc pol
//    int wiersz =0;
//    //iterujemy po wszytkich rekordach zwroconych przez zpaytanie
//    while(zapytanie.next())
//    {
//        ui->tableWidget_dostawa->insertRow(wiersz);
//        for (int i=0; i<ile_pol; i++){
//            ui->tableWidget_dostawa->setItem(wiersz,i, new QTableWidgetItem(zapytanie.value(i).toString()+" "));
//        }

//    wiersz++;

//    }
        QSqlQuery zapytanie;
        //query z pola tekstowego
        QString tekst;
        tekst = arg1;

        bool sukces = zapytanie.exec("SELECT * FROM DOSTAWA WHERE data_dostawy LIKE '%"+tekst+"%';");
        qDebug() << sukces;

        int ile_pol = zapytanie.record().count();
        ui->tableWidget_dostawa->setColumnCount(ile_pol);
        ui->tableWidget_dostawa->setRowCount(0);

        //pobieramy ilosc pol
        int wiersz =0;
        //iterujemy po wszytkich rekordach zwroconych przez zpaytanie
        while(zapytanie.next())
        {
            ui->tableWidget_dostawa->insertRow(wiersz);
            for (int i=0; i<1; i++){
                ui->tableWidget_dostawa->setItem(wiersz,i, new QTableWidgetItem(zapytanie.value(i).toString()+" "));
            }
            for (int i=1; i<2; i++){
                //query("SELECT nazwa FROM KONTRAHENT WHERE id_kontrahenta=7;");
                ui->tableWidget_dostawa->setItem(wiersz,i, new QTableWidgetItem(zapytanie.value(i).toString()+" "));
            }

        wiersz++;

        }
}
