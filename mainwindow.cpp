#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serialPort = new QSerialPort();
    connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::receiveData_WriteToFile);
    Opened = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveData_WriteToFile()
{
    if (serialPort->isOpen())
    {
        QByteArray DataReceived;
        QFile LogFile(filePath + "/data.txt");
        if(!LogFile.open(QFile::Append | QFile::Text))
        {
            //Can't Open Log File.
        }
        if(serialPort->bytesAvailable())
        {
            DataReceived = serialPort->readAll(); //All Data Received Successfully.
            if(DataReceived.size() > 0)
            {
                if(LogFile.isOpen())
                {
                    QTextStream in(&LogFile);
                    in << DataReceived;
                }

                LogFile.close();
            }
            else
            {
                //Fail To Receive Data.
            }
        }
        LogFile.close();
    }
}

void MainWindow::on_btnOpenClose_clicked()
{
    if (!Opened)
    {
        Opened = true;
        serialPort->setPortName("COM1");
        serialPort->setBaudRate(QSerialPort::Baud38400);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
        serialPort->open(QIODevice::ReadWrite);
        if (serialPort->isOpen())
        {
            statusBar_Message("Successfully Opened Serial Port.");
            ui->btnOpenClose->setText("Close");
        }
        else
        {
            statusBar_Error("Fail To Open Serial Port");
        }
    }
    else
    {
        serialPort->close();
        Opened = false;
        ui->btnOpenClose->setText("Open");
        statusBar_Error("Successfully Closed Serial Port.");
    }
}

void MainWindow::on_btnBrowse_clicked()
{
    filePath.clear();
    filePath = QFileDialog::getExistingDirectory(this,tr("Select Log Path"), "C://");
    ui->txtBrowse->setText(filePath);
}

void MainWindow::statusBar_Message(QString str)
{
    ui->statusBar->clearMessage();
    ui->statusBar->setStyleSheet("color:green;");
    ui->statusBar->showMessage(str, 5000);
}

void MainWindow::statusBar_Error(QString str)
{
    ui->statusBar->clearMessage();
    ui->statusBar->setStyleSheet("color:red;");
    ui->statusBar->showMessage(str, 5000);
}
