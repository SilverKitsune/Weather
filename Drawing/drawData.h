#ifndef DRAWDOT_H
#define DRAWDOT_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include "data.h"
#include "grid.h"
#include <QToolTip>

class DrawData  : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

    QOpenGLContext m_context;

    /** @brief shaderProgram - шейдерная программа*/
    QOpenGLShaderProgram *shaderProgram_g, *shaderProgram_t;

    ///позиции параметров шейдеров
    int l_vertex, l_text, l_projection, l_textColor;

    Grid *grid;

public:

    ~DrawData()
    {
        delete grid;
    }

    DrawData(QWidget *parent = 0);

    /** @brief initializeGL - инициализация виджета*/
    void initializeGL() override;

    /** @brief initTextures - инициализация текстур текста*/
    void initTextures();

    /** @brief initShaders - инициализация шейдеров*/
    void initShaders();

    /** @brief resizeGL - изменение размера окна
     *  @param w - новая ширина
     *  @param h - новая высота */
    void resizeGL(int w, int h) override;

    /** @brief paintGL - отрисовка виджета
     *  @todo */
    void paintGL() override;

    /** @brief readData - чтение данных из файла
     *  @param fileName - путь к файлу */
    void readData(QString fileName);

    /** @brief paintTemperatureGrgid - отрисовка сетки с температурой*/
    void paintTemperatureGrgid();

    /** @brief initTemperatureGrid - инициализация сетки */
    void initTemperatureGrid();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

public:
    bool event(QEvent *event) override;
};

#endif // DRAWDOT_H
