#include "grid.h"
#include<math.h>

///TODO нормально преобразовать координаты

// ********************************************************************************** //

void Grid::setScale(float sx, float sy)
{
    scaleX = sx;
    scaleY = sy;
}

// *********************************************************************************** //

Grid::Grid(QObject *parent) : QObject(parent)
{
    vbo_vertices = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    ibo_vertices = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    textures = new QVector<Character>();
    text_vert = nullptr; //new QVector<QVector<GLfloat>>(10);
    scaleX = 1;
    scaleY = 1;
    scaleMap = 150;

    centreOfWidget.x = -2;
    centreOfWidget.y = -2;
}

// *********************************************************************************** //

Grid::~Grid()
{
    vbo_vertices->destroy();
    ibo_vertices->destroy();
    textures->clear();
    delete textures;
    points->clear();
    delete points;
}

// ********************************************************************************** //

void Grid::formVertices()
{
    text_vert = new QVector<QVector<GLfloat>>(10);
    int n = points->at(0).pD->size();
    GLfloat *vertices = new GLfloat [n*2];
    GLuint *index_vertices = new GLuint [(points->at(0).Ni - 1)*(points->at(0).Nj - 1)*2*3];
    if(centreOfWidget.x == -2)
    {
        centreOfWidget.y = (points->at(0).pD->value(0).Fi() + points->at(0).pD->value(n-1).Fi())/2;
        centreOfWidget.x = (points->at(0).pD->value(0).La() + points->at(0).pD->value(n-1).La())/2;
        //FlatCoordinates *centre = PointData::toFlat(cfi, cla);
    }

    int j = 0;
    for(int i = 0; i < n; i++)
    {
        GLfloat x,y;
        x = points->at(0).pD->value(i).La(); //.flat->X();
        y = points->at(0).pD->value(i).Fi(); //.flat->Y();
        glm::vec2 coord = toOpengl(x,y,centreOfWidget.x,centreOfWidget.y);//centre->X(), centre->Y());

        x = coord.x;
        y = coord.y;
        vertices[2*i] = x;
        vertices[2*i+1] = y;
        int temp = round(points->at(0).pD->value(i).getParam());
        appendTextVert(temp / 10, x, y);
        x = x + (textures->at(temp / 10).advance >> 6) *scaleX;
        appendTextVert(temp % 10, x, y);

        if(i < n - points->at(0).Nj && ((i+1) % points->at(0).Ni != 0))
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
}

// ********************************************************************************** //

void Grid::readData(QString fileName)
{
    points = Data::readData(fileName);
    centreOfWidget.x = -2;
    centreOfWidget.y = -2;
    scaleMap = 150;
}

// ********************************************************************************** //

glm::vec2 Grid::toOpengl(float x, float y, float Cx, float Cy)
{
    //FlatCoordinates *flat  = fromGeoToFlat(geo);
    /*qDebug() << "**********";
    qDebug() << scaleX << " " << scaleY;
    qDebug() << x << " " << y << " " << Cx << " " << Cy;
    qDebug() << (x-Cx)*scaleX*scaleMap << " " << (y-Cy)*scaleY*scaleMap;
    qDebug() << "**********";*/

    return glm::vec2((x-Cx)*scaleX*scaleMap, (y-Cy)*scaleY*scaleMap);
}

// *********************************************************************************** //

void Grid::appendTextVert(int c, GLfloat x, GLfloat y)
{
    GLfloat xpos, ypos, w, h;
    xpos = x + textures->at(c).bearing.x * scaleX;
    ypos = y - (textures->at(c).size.y - textures->at(c).bearing.y)*scaleY;
    w = textures->at(c).size.x * scaleX;
    h = textures->at(c).size.y * scaleY;

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

void Grid::changeCenterOfWidget(int w, int h)
{
    float newCentreX, newCentreY;

    newCentreX = w*scaleX - 1;
    newCentreY =  1 - h*scaleY ;
    // this->height();
    float la, fi;
    la = newCentreX/(2.0*scaleMap*scaleX) + centreOfWidget.x;
    fi = newCentreY/(2.0*scaleMap*scaleY) + centreOfWidget.y;
    qDebug() << la << " " << fi;
    setCentre(la,fi);
}

// *********************************************************************************** //

int Grid::getSizeOfTextVertAt(int i)
{
    if(text_vert)
        return text_vert->at(i).size();
    else return -1;
}

// *********************************************************************************** //

void Grid::allocateVboTextAt(int i, QOpenGLBuffer *vbo)
{
    vbo->bind();
    GLfloat *data_i = text_vert->value(i).data();
    vbo->allocate(data_i, text_vert->value(i).size()*sizeof(GLfloat));
    vbo->release();
}

// *********************************************************************************** //

void Grid::deleteTextVert()
{
    if(text_vert)
    {
        text_vert->clear();
        delete text_vert;
    }
}

// *********************************************************************************** //

void Grid::appendTexture(GLuint _id, glm::ivec2 _size, glm::ivec2 _bearing, int _advance)
{
    Character character = { _id, _size, _bearing, _advance };
    textures->append(character);
}

// *********************************************************************************** //

glm::vec2 Grid::fromPixelsToGeo(int x, int y)
{
    float GLx, GLy;
    GLx = x*scaleX - 1;
    GLy =  1 - y*scaleY;

    float la, fi;
    la = GLx/(2.0*scaleMap*scaleX) + centreOfWidget.x;
    fi = GLy/(2.0*scaleMap*scaleY) + centreOfWidget.y;
    return glm::vec2(la,fi);
}

// *********************************************************************************** //

