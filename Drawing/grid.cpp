#include "grid.h"
//TODO преобразовать координаты
//TODO вывести текстом попадающие на экран температуры

//TODO сформировать вершины
//TODO инициализировать шейдеры, загрузить в них вершины
//TODO нарисовать вершины

// ********************************************************************************** //

Grid::Grid(QObject *parent) : QObject(parent)
{
    vao = new QOpenGLVertexArrayObject();
    vbo_vertices = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    ibo_vertices = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    vbo_textures = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    ibo_textures = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
}

// ********************************************************************************** //

void Grid::initGrid()
{
    vao->create();
    vao->bind();

    vbo_vertices->create();
    vbo_vertices->bind();

    ibo_vertices->create();
    ibo_vertices->bind();


    vao->release();
    ibo_vertices->release();
    vbo_vertices->release();


}

// ********************************************************************************** //

void Grid::formVertices()
{
    int n = points->at(0).pD->size();
    qDebug() << n*2;
    GLfloat *vertices = new GLfloat [n*2];
    GLuint *index_vertices = new GLuint [(points->at(0).Ni - 1)*(points->at(0).Nj - 1)*2*3];

    qDebug() << (points->at(0).Ni - 1)*(points->at(0).Nj - 1)*2*3;
    float cx, cy;

    cy = (points->at(0).pD->value(0).Fi() + points->at(0).pD->value(n-1).Fi())/2;
    cx = (points->at(0).pD->value(0).La() + points->at(0).pD->value(n-1).La())/2;

    for(int i = 0, j = 0; i < n; i++)
    {
        glm::vec2 coord = fromGeoToOpengl((GeoCoordinates)(points->at(0).pD->at(i)), cx, cy);
        vertices[2*i] = coord.x;
        vertices[2*i+1] = coord.y;

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
    ibo_vertices->bind();
    vbo_vertices->allocate(vertices, n*2*sizeof(GLfloat));
    ibo_vertices->allocate(index_vertices, (points->at(0).Ni - 1)*(points->at(0).Nj - 1)*2*3*sizeof(GLuint));

    ibo_vertices->release();
    vbo_vertices->release();

    delete [] vertices;
    delete [] index_vertices;
}

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
