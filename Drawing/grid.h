#ifndef GRID_H
#define GRID_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "data.h"
#include "includes/glm/glm/glm.hpp"


/** @brief Character - структура дляя хранения текстуры глифа */
struct Character {
    GLuint     TextureID; // ID текстуры глифа
    glm::vec2  Size;      // Размеры глифа
    glm::vec2  Bearing;   // Смещение верхней левой точки глифа
    int     Advance;   // Горизонтальное смещение до начала следующего глифа
};

class Grid : public QObject
{
    Q_OBJECT

    float scale = 0.004;
    QVector<QVector<GLfloat>> *text_vert;
    //Text text;
public:
QList<Data> *points = nullptr;
    /** @brief vao_v - Vertex Array Object */
    QOpenGLVertexArrayObject *vao_v;

    /** @brief vao_t - Vertex Array Object */
    QOpenGLVertexArrayObject *vao_t;

    /** @brief vbo_vertices - Vertex Buffer Object */
    QOpenGLBuffer *vbo_vertices = nullptr;

    /** @brief vbo_textures - Vertex Buffer Object */
    QOpenGLBuffer *vbo_textures = nullptr;

    /** @brief ibo_vertices - Index Buffer Object */
    QOpenGLBuffer *ibo_vertices;

    /** @brief Characters - массив загруженных текстур для текста*/
    QVector<Character> *textures;

    explicit Grid(QObject *parent = nullptr);

    void initTextures();

    void formVertices();

    void readData(QString fileName);

    glm::vec2 fromGeoToOpengl(GeoCoordinates geo, float Cx, float Cy);

    void appendTextVert(int c, GLfloat x, GLfloat y);

    bool isEmpy() {return points;}

    int getSizeOfTextVertAt(int i)
    {
        return text_vert->at(i).size();
    }

    void allocateVboTextAt(int i, QOpenGLBuffer *vbo)
    {
        vbo->bind();
        vbo->allocate(text_vert->at(i).data(), text_vert->at(i).size()*sizeof(GLfloat));
        vbo->release();
    }

signals:

};

#endif // GRID_H
