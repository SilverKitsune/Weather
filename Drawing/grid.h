#ifndef GRID_H
#define GRID_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "data.h"
#include "text.h"

class Grid : public QObject
{
    Q_OBJECT

    Text text;
public:
QList<Data> *points;
    /** @brief vao - Vertex Array Object */
    QOpenGLVertexArrayObject *vao;

    /** @brief vbo_vertices - Vertex Buffer Object */
    QOpenGLBuffer *vbo_vertices;

    /** @brief vbo_textures - Vertex Buffer Object */
    QOpenGLBuffer *vbo_textures;

    /** @brief ibo_vertices - Index Buffer Object */
    QOpenGLBuffer *ibo_vertices;

    /** @brief ibo_textures - Index Buffer Object */
    QOpenGLBuffer *ibo_textures;

    explicit Grid(QObject *parent = nullptr);

    Grid(QString fileName);

    void initGrid();

    void paintGrid();

    void paintText();

    void formVertices();

    void readData(QString fileName);

    glm::vec2 fromGeoToOpengl(GeoCoordinates geo, float Cx, float Cy);

signals:

};

#endif // GRID_H
