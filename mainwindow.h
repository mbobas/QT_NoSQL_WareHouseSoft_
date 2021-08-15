#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    const double VAT = 1.23;
    int counterSprzedaz = 0,  ilosc1=0, ilosc2=0, ilosc3=0, pk_check=0;
    int counterDostawa;
    QString produkt1, produkt2, produkt3,  id_kontrahenta;
    QString data_sprzedazy, data_dostawy, ilosc_pozycji, kategoria;
    double cena1=0, cena2=0, cena3=0, sumaN1=0, sumaN2=0, sumaN3=0, sumaB1=0, sumaB2=0, sumaB3=0, razemN=0, razemB=0;

private slots:

    void on_lineEdit_kontrahenci_textChanged(const QString &arg1);

    void on_pushButton_dodajKontrahenta_clicked();

    void on_pushButton_usunKontrahenta_clicked();

    void on_lineEdit_magazyn_wyszukajtowar_textChanged(const QString &arg1);

    void on_comboBox_activated(const QString &arg1);

    void on_checkBox_sprzed_1_clicked(bool checked);


    void on_checkBox_sprzed_2_clicked(bool checked);

    void on_checkBox_sprzed_3_clicked(bool checked);

    void dostawa_combobox_produkt_konstruktor();
    void dostawa_combobox_produkt_konstruktor2();
    void dostawa_combobox_produkt_konstruktor3();

    void sprzedaz_combobox_produkt_konstruktor();
    void sprzedaz_combobox_produkt_konstruktor2();
    void sprzedaz_combobox_produkt_konstruktor3();


    void on_comboBox_sprzedaz_2_activated(const QString &arg1);

    void on_comboBox_sprzedaz_3_activated(const QString &arg1);

    void on_comboBox_sprzedaz_kontrahent_activated(const QString &arg1);

    void on_lineEdit_sprzedaz_cena1_textChanged(const QString &arg1);

    double cena_produktu_sprzedaz(QString produkt);

    void on_lineEdit_sprzedaz_cena_2_textChanged(const QString &arg1);

    void on_lineEdit_sprzedaz_cena1_3_textChanged(const QString &arg1);

    void odswiezCeneBruttoINetto();

    void on_pushButton_sprzedaz_clicked();

    void on_lineEdit_sprzedaz_wyszukajtowar_textChanged(const QString &arg1);

    void on_lineEdit_faktury_wyszukaj_textChanged(const QString &arg1);

    void on_lineEdit_produkt_textChanged(const QString &arg1);

    void on_lineEdit_kategorie_textChanged(const QString &arg1);

    void on_comboBox_PK_kategoria_activated(const QString &arg1);

    void PK_combobox_kategoria_konstruktor();

    void on_radioButton_dodajProdukt_clicked(bool checked);

    void on_radioButton_dodajKategori_clicked(bool checked);

    void on_radioButton_usunProdukt_clicked(bool checked);

    void on_radioButton_usunKategori_clicked(bool checked);

    void on_pushButton_clicked();

    void clearFieldsPK();

    void on_lineEdit_dostawa_wyszukajtowar_textChanged(const QString &arg1);

    QString query(QString query);
    QString queryWithComa(QString query);

    void on_lineEdit_dostawa_wyszukajtowar_kontrahent_textChanged(const QString &arg1);

    void on_checkBox_dostawa_1_clicked(bool checked);

    void on_checkBox_dostawa_2_clicked(bool checked);

    void on_checkBox_dostawa_3_clicked(bool checked);

    void on_comboBox_dostawa1_activated(const QString &arg1);

    void on_comboBox_dostawa2_activated(const QString &arg1);

    void on_comboBox_dostawa3_activated(const QString &arg1);

    void sprzedaz_kontrahent_combobox_konstruktor();
    void dostawa_kontrahent_combobox_konstruktor();



    void on_lineEdit_dostawa_cena1_textChanged(const QString &arg1);

    void on_comboBox_dostawa_kontrahent_activated(const QString &arg1);

    void on_tabWidget_tabBarClicked(int index);

    void on_lineEdit_dostawa_cena2_textChanged(const QString &arg1);

    void on_lineEdit_dostawa_cena3_textChanged(const QString &arg1);

    void on_pushButton_dostawa_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
