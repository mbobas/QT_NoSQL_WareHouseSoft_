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

private slots:

    void on_lineEdit_kontrahenci_textChanged(const QString &arg1);

    void on_pushButton_dodajKontrahenta_clicked();

    void on_pushButton_usunKontrahenta_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
