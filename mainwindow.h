#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include "data.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QList<Data> *data;

public:

    MainWindow(QMainWindow *parent = 0);

private:

    void createMenu();

public slots:

    void open_File();

};

#endif // MAINWINDOW_H
