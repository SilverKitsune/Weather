#include "mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QApplication>
#include <QFileDialog>
#include <QMenuBar>

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
    resize(800,600);
    createMenu();
}

void MainWindow::createMenu()
{
    QMenu *file;
    file = menuBar()->addMenu("&File");

    file->addAction("&Open", this, SLOT(open_File()));



}

void MainWindow::open_File()
{

    QString fileName = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath(),
                                "(*.grb);;All files (*.*)");
    qDebug() << fileName;

    data = Data::readData(fileName);


    qDebug() << "was read";

}

