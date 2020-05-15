#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QMenuBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMenuBar *menuBar;
    QMenu *menu;
public:

    MainWindow(QMainWindow *parent = 0);

protected:

};

#endif // MAINWINDOW_H
