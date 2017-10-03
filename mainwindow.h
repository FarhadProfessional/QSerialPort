#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QtSerialPort/QtSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void receiveData_WriteToFile();

private slots:
    void on_btnOpenClose_clicked();
    void on_btnBrowse_clicked();
    void statusBar_Message(QString str);
    void statusBar_Error(QString str);

private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort;
    bool Opened;
    QString filePath;
};

#endif // MAINWINDOW_H
