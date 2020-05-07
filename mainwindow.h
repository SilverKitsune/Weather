#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGLWidget>
#include <QToolBar>
#include <QMenuBar>

class MainWindow : public QGLWidget
{
private:
    QToolBar *toolBar;
    QMenuBar *menuBar;
public:
    MainWindow(QGLWidget *parent = 0);


protected:

    // QWidget interface

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    // QGLWidget interface

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // MAINWINDOW_H
