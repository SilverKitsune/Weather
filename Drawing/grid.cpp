#include "grid.h"
///TODO преобразовать координаты
///TODO вывести текстом попадающие на экран температуры
#include<math.h>


int getCount(int k)
{
    int i = 0;
    while(k  > 0)
    {
        i++;
        k = k/10;
    }
    return i;
}

// ********************************************************************************** //

Grid::Grid(QObject *parent) : QObject(parent)
{
    vao_v = new QOpenGLVertexArrayObject();
    vao_t = new QOpenGLVertexArrayObject();
    vbo_vertices = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    ibo_vertices = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    vbo_textures = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    textures = new QVector<Character>();
    text_vert = new QVector<QVector<GLfloat>>(10);
}

// ********************************************************************************** //

void Grid::formVertices()
{
    text_vert = new QVector<QVector<GLfloat>>(10);
    int n = points->at(0).pD->size();
    GLfloat *vertices = new GLfloat [n*2];
    GLuint *index_vertices = new GLuint [(points->at(0).Ni - 1)*(points->at(0).Nj - 1)*2*3];
    float cx, cy;
    int text_vert_count = 0;
    cy = (points->at(0).pD->value(0).Fi() + points->at(0).pD->value(n-1).Fi())/2;
    cx = (points->at(0).pD->value(0).La() + points->at(0).pD->value(n-1).La())/2;

    int j = 0;
    for(int i = 0; i < n; i++)
    {
        glm::vec2 coord = fromGeoToOpengl((GeoCoordinates)(points->at(0).pD->at(i)), cx, cy);
        GLfloat x = coord.x;
        GLfloat y = coord.y;
        vertices[2*i] = x;
        vertices[2*i+1] = y;
        int temp = round(points->at(0).pD->value(i).getParam());
        //int count = getCount(temp);
        qDebug() << i << " " << temp << " " << temp/10 <<" " << temp % 10;
        appendTextVert(temp / 10, x, y);
        x = x + (textures->at(temp / 10).Advance >> 6) *scale;
        appendTextVert(temp % 10, x, y);

        if(i < n - points->at(0).Nj && ((i+1) % points->at(0).Ni != 0)) //?
        {
            index_vertices[j++] = i;
            index_vertices[j++] = i+points->at(0).Ni;
            index_vertices[j++] = i+points->at(0).Ni+1;
            index_vertices[j++] = i;
            index_vertices[j++] = i+1;
            index_vertices[j++] = i+points->at(0).Ni+1;
        }
    }
    vbo_vertices->bind();
    vbo_vertices->allocate(vertices, n*2*sizeof(GLfloat));
    vbo_vertices->release();

    ibo_vertices->bind();
    ibo_vertices->allocate(index_vertices, (points->at(0).Ni - 1)*(points->at(0).Nj - 1)*2*3*sizeof(GLuint));
    ibo_vertices->release();

    /*vbo_textures->bind();
    vbo_textures->allocate(text_vert->at(1).data(), text_vert->at(1).size()*sizeof(GLfloat));
    vbo_textures->release();*/

    delete [] vertices;
    delete [] index_vertices;
}

// ********************************************************************************** //

void Grid::readData(QString fileName)
{
    points = Data::readData(fileName);
}

// ********************************************************************************** //

glm::vec2 Grid::fromGeoToOpengl(GeoCoordinates geo, float Cx, float Cy)
{
    //FlatCoordinates *flat  = fromGeoToFlat(geo);
    return glm::vec2((geo.La()-Cx)/2, (geo.Fi()-Cy)/2);
}

// *********************************************************************************** //

void Grid::appendTextVert(int c, GLfloat x, GLfloat y)
{
    GLfloat xpos, ypos, scale = 0.005, w, h;
    xpos = x + textures->at(c).Bearing.x * scale;
    ypos = y - (textures->at(c).Size.y - textures->at(c).Bearing.y)*scale;
    w = textures->at(c).Size.x * scale;
    h = textures->at(c).Size.y * scale;

    text_vert->data()[c].append(xpos);
    text_vert->data()[c].append(ypos + h);
    text_vert->data()[c].append(0.0);
    text_vert->data()[c].append(0.0);

    text_vert->data()[c].append(xpos);
    text_vert->data()[c].append(ypos);
    text_vert->data()[c].append(0.0);
    text_vert->data()[c].append(1.0);

    text_vert->data()[c].append(xpos + w);
    text_vert->data()[c].append(ypos);
    text_vert->data()[c].append(1.0);
    text_vert->data()[c].append(1.0);

    text_vert->data()[c].append(xpos);
    text_vert->data()[c].append(ypos + h);
    text_vert->data()[c].append(0.0);
    text_vert->data()[c].append(0.0);

    text_vert->data()[c].append(xpos + w);
    text_vert->data()[c].append(ypos);
    text_vert->data()[c].append(1.0);
    text_vert->data()[c].append(1.0);

    text_vert->data()[c].append(xpos + w);
    text_vert->data()[c].append(ypos + h);
    text_vert->data()[c].append(1.0);
    text_vert->data()[c].append(0.0);
}

// *********************************************************************************** //

