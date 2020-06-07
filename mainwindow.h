#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include "Drawing/drawdata.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    DrawData *drawData;

public:

    MainWindow(QMainWindow *parent = 0);

private:

    void createMenu();

public slots:

    void open_File();

};

#endif // MAINWINDOW_H
