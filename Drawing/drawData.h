#ifndef DRAWDOT_H
#define DRAWDOT_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include "data.h"
#include "grid.h"

class DrawData  : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

    QOpenGLShader *shader_grid_v, *shader_grid_f, *shader_text_v, *shader_text_f;

    QOpenGLContext m_context;

    /** @brief shaderProgram - шейдерная программа*/
    QOpenGLShaderProgram *shaderProgram_g, *shaderProgram_t;

    ///позиции параметров шейдеров
    int l_vertex, l_text, l_projection, l_textColor;

    Grid *grid;

public:

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

    void paintTemperatureGrgid();

    void initTemperatureGrid();

signals:

public slots:
};

#endif // DRAWDOT_H
