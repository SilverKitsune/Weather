#ifndef DRAWDOT_H
#define DRAWDOT_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "data.h"
#include <QOpenGLFunctions_3_3_Core>
#include <QMatrix4x4>
#include "includes/glm/glm/glm.hpp"
struct Character {
    GLuint     TextureID; // ID текстуры глифа
    glm::vec2  Size;      // Размеры глифа
    glm::vec2  Bearing;   // Смещение верхней левой точки глифа
    int     Advance;   // Горизонтальное смещение до начала следующего глифа
};


class DrawData  : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
    QOpenGLShaderProgram *shaderProgram;
    QOpenGLVertexArrayObject *vao;
    QOpenGLBuffer *vbo;
    QOpenGLBuffer *indexBuffer;
    QMatrix4x4 perspective;
    QMatrix4x4 projection;
    QList<Data> *data;
    GLfloat vertices [24];
    int N;
   // QOpenGLFunctions_3_3_Core *m_funcs {nullptr};
    QOpenGLContext m_context;
    int l_vertex, l_projection, l_textColor;
public:
    //std::map<GLchar, Character> Characters;
    Character Characters;
    DrawData(QWidget *parent = 0);

    void initializeGL() override;
    void initTextures();
    void initShaders();
    void initGeometry();

    void resizeGL(int w, int h) override;
    void paintGL() override;

    void paintData();
    void formVertices();
    void testVertices();

    void renderText(string text, GLfloat x, GLfloat y, GLfloat scale, QVector3D color);
    void readData(QString fileName);

signals:

public slots:
};

#endif // DRAWDOT_H
