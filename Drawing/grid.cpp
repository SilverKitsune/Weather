#include "grid.h"
#include<math.h>

///TODO преобразовать координаты
///TODO вывести текстом попадающие на экран температуры
///TODO удаление объектов

// ********************************************************************************** //

Grid::Grid(QObject *parent) : QObject(parent)
{
    vao_v = new QOpenGLVertexArrayObject();
    vao_t = new QOpenGLVertexArrayObject();
    vbo_vertices = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    ibo_vertices = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    vbo_textures = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    textures = new QVector<Character>();
    text_vert = nullptr; //new QVector<QVector<GLfloat>>(10);
    needToUpdate = false;
    scaleX = 1;
    scaleY = 1;
    scaleMap = 150;

    centreOfGrid.x = -2;
    centreOfGrid.y = -2;
}

// ********************************************************************************** //

void Grid::formVertices()
{
    text_vert = new QVector<QVector<GLfloat>>(10);
    int n = points->at(0).pD->size();
    GLfloat *vertices = new GLfloat [n*2];
    GLuint *index_vertices = new GLuint [(points->at(0).Ni - 1)*(points->at(0).Nj - 1)*2*3];
    //float cfi, cla; //координаты центра сетки
    if(centreOfGrid.x == -2)
    {
        centreOfGrid.y = (points->at(0).pD->value(0).Fi() + points->at(0).pD->value(n-1).Fi())/2;
        centreOfGrid.x = (points->at(0).pD->value(0).La() + points->at(0).pD->value(n-1).La())/2;
        //FlatCoordinates *centre = PointData::toFlat(cfi, cla);
    }

    int j = 0;
    for(int i = 0; i < n; i++)
    {
        GLfloat x,y;
        x = points->at(0).pD->value(i).La(); //.flat->X();
        y = points->at(0).pD->value(i).Fi(); //.flat->Y();
        glm::vec2 coord = toOpengl(x,y,centreOfGrid.x,centreOfGrid.y);//centre->X(), centre->Y());

        x = coord.x;
        y = coord.y;
        vertices[2*i] = x;
        vertices[2*i+1] = y;
        int temp = round(points->at(0).pD->value(i).getParam());
        appendTextVert(temp / 10, x, y);
        x = x + (textures->at(temp / 10).Advance >> 6) *scaleX;
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
    ibo_vertices->allocate(index_vertices, j*sizeof(GLuint));
    ibo_vertices->release();

    delete [] vertices;
    delete [] index_vertices;
    needToUpdate = false;
}

// ********************************************************************************** //

void Grid::readData(QString fileName)
{
    points = Data::readData(fileName);
    needToUpdate = true;
}

// ********************************************************************************** //

glm::vec2 Grid::toOpengl(float x, float y, float Cx, float Cy)
{
    //FlatCoordinates *flat  = fromGeoToFlat(geo);
   /* qDebug() << "**********";
    qDebug() << scaleX << " " << scaleY;
    qDebug() << x << " " << y << " " << Cx << " " << Cy;
    qDebug() << (x-Cx)*scaleX << " " << (y-Cy)*scaleY;
    qDebug() << "**********";*/
    return glm::vec2((x-Cx)*scaleX*scaleMap, (y-Cy)*scaleY*scaleMap);
}

// *********************************************************************************** //

void Grid::appendTextVert(int c, GLfloat x, GLfloat y)
{
    GLfloat xpos, ypos, scale = 0.005, w, h;
    xpos = x + textures->at(c).Bearing.x * scale;
    ypos = y - (textures->at(c).Size.y - textures->at(c).Bearing.y)*scale;
    w = textures->at(c).Size.x * scale;
    h = textures->at(c).Size.y * scale;

    /*qDebug() << "********** " << c << " **********";
    qDebug() << xpos << " " << ypos + h;
    qDebug() << xpos << " " << ypos;
    qDebug() << xpos + w << " " << ypos;
    qDebug() << xpos << " " << ypos + h;
    qDebug() << xpos + w << " " << ypos;
    qDebug() << xpos + w << " " << ypos + h;*/

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

