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

    float scaleX;
    float scaleY;
    float scaleMap;
    bool needToUpdate;

    glm::vec2 centreOfGrid;

    QVector<QVector<GLfloat>> *text_vert;
    //Text text;
public:

    void setScale(float sx, float sy)
    {
        scaleX = sx;
        scaleY = sy;
    }

    bool isUpdated() {return !needToUpdate;}

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

    glm::vec2 toOpengl(float x, float y, float Cx, float Cy);

    void appendTextVert(int c, GLfloat x, GLfloat y);

    bool isEmpy() {return !points;}

    int getSizeOfTextVertAt(int i)
    {
        if(text_vert)
            return text_vert->at(i).size();
        else return -1;
    }

    void allocateVboTextAt(int i, QOpenGLBuffer *vbo)
    {
        vbo->bind();
        GLfloat *data_i = text_vert->value(i).data();
        vbo->allocate(data_i, text_vert->value(i).size()*sizeof(GLfloat));
        vbo->release();
    }

    void deleteTextVert()
    {
        if(text_vert)
        {
            text_vert->clear();
            delete text_vert;
        }
    }

    void debugTextVert()
    {
        for(int i = 0; i < 10; i++)
        {
            qDebug() << "|******* " << i << " *******";
            for(int j = 0; j < text_vert->at(i).size(); j++)
            {
                if(j % 24 == 0)
                    qDebug() << "|    ++++++++++ " << j/24 << " ++++++++++";
                if(j % 4 == 0)
                    qDebug() << "|        ______ " << j / 4 <<" _______";
                qDebug() << "|            " << text_vert->at(i).at(j);
            }
            qDebug() << endl;
        }
    }

signals:

};

#endif // GRID_H
