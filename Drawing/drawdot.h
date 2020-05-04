#ifndef DRAWDOT_H
#define DRAWDOT_H

#include <QGLWidget>
#include <QGLShaderProgram>

class DrawDot  : public QGLWidget
{
    Q_OBJECT


        QGLShaderProgram *shaderProgram;

public:

    DrawDot();
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
//    void mouseMoveEvent(QMouseEvent *event) override;
//    void mousePressEvent(QMouseEvent *event) override;
//    void wheelEvent(QWheelEvent *event) override;
    void initShaders();

signals:

public slots:
};

#endif // DRAWDOT_H
