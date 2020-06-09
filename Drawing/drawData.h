#ifndef DRAWDOT_H
#define DRAWDOT_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "data.h"
#include <QOpenGLFunctions_3_3_Core>
#include <QMatrix4x4>
#include "text.h"
#include "grid.h"


class DrawData  : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

    QOpenGLContext m_context;

    /** @brief shaderProgram - шейдерная программа*/
    QOpenGLShaderProgram *shaderProgram;

    /** @brief vao - Vertex Array Object */
    QOpenGLVertexArrayObject *vao;

    /** @brief vbo - Vertex Buffer Object */
    QOpenGLBuffer *vbo;

    /** @brief data - данные считанные из файла*/
    //QList<Data> *data;

    /** @brief N - количество считанных точек*/
    int N;

    ///позиции параметров шейдеров
    int l_vertex, l_projection, l_textColor;

    /** @brief Characters - массив загруженных текстур для текста*/
    Character Characters;

    Grid *grid = nullptr;

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

    /** @brief initVertices - инициализаци вершин */
    void initVertices();

    /** @brief readData - чтение данных из файла
     *  @param fileName - путь к файлу */
    void readData(QString fileName);

signals:

public slots:
};

#endif // DRAWDOT_H
