#include "drawdata.h"
#include "iostream"
#include <QOpenGLBuffer>
#include <math.h>
#include <QOpenGLShader>
#include <ft2build.h>
#include <QOpenGLTexture>
#include FT_FREETYPE_H

#define GLEW_STATIC
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/wglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "includes/glm/glm/geometric.hpp"


/*********************************************************************/

DrawData::DrawData(QWidget *parent) : QOpenGLWidget(parent)
{
    grid = new Grid();
    resize(640,480);
}

/*********************************************************************/

void DrawData::initTextures()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    FT_Face face;
    if (FT_New_Face(ft, "C:\\Users\\Allo4ka\\Desktop\\qtprojects\\WeatherApp\\fonts\\trebuc.ttf", 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    FT_Set_Pixel_Sizes(face,0,12);


    for(char i = '0'; i <='9'; i++)
    {
        // Load character glyph
        if (FT_Load_Char(face, i, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            return;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        grid->textures->append(character);
    }
    FT_Done_Face(face);   // Завершение работы с шрифтом face
    FT_Done_FreeType(ft); // Завершение работы FreeType
}

/*********************************************************************/

void DrawData::initializeGL()
{
    /* ***** Init OpenGL ***** */
    this->initializeOpenGLFunctions();
    m_context.create();
    makeCurrent();

    if (!this->isInitialized())
    {
        printf("Unable to Initialize OpenGL 3.3 Core.\n");
        exit(99);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.4f, 0.6f, 0.8f, 1.00f);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    initShaders();
    initTextures();
    grid->vbo_textures->create();
    grid->vbo_vertices->create();
    grid->ibo_vertices->create();


   /* shaderProgram_t->bind();

    grid->vbo_textures->create();
    grid->vbo_textures->bind();
    shaderProgram_t->enableAttributeArray(l_text);
    shaderProgram_t->setAttributeBuffer(l_text,GL_FLOAT,0,4);

    grid->vbo_textures->release();
    shaderProgram_t->release();*/
}

/*********************************************************************/

void DrawData::resizeGL(int width, int height)
{

}

/*********************************************************************/

void DrawData::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(grid->isEmpy())
        grid->formVertices();


    /* ********************** */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    shaderProgram_t->bind();
   // glActiveTexture(GL_TEXTURE0);
    for(int i = 0; i < 10 && grid->getSizeOfTextVertAt(i) > 0; i++)
    {
        QOpenGLBuffer *vbo_textures = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        vbo_textures->create();
        grid->allocateVboTextAt(i, vbo_textures);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, grid->textures->at(i).TextureID);
        vbo_textures->bind();

        shaderProgram_t->enableAttributeArray(l_text);
        shaderProgram_t->setAttributeBuffer(l_text,GL_FLOAT,0,4);
        glDrawArrays(GL_TRIANGLES,0,grid->getSizeOfTextVertAt(i));
        glBindTexture(GL_TEXTURE_2D, 0);
        vbo_textures->release();
        delete vbo_textures;
    }

    grid->vbo_textures->release();
    shaderProgram_t->release();

    /* ********************** */
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    shaderProgram_g->bind();
    grid->vbo_vertices->bind();
    shaderProgram_g->enableAttributeArray(l_vertex);
    shaderProgram_g->setAttributeBuffer(l_vertex,GL_FLOAT,0,2);
    grid->ibo_vertices->bind();

    glDrawElements(GL_TRIANGLES,216,GL_UNSIGNED_INT,0);

    grid->ibo_vertices->release();
    grid->vbo_vertices->release();
    shaderProgram_g->release();

}

/*********************************************************************/

void DrawData::initShaders()
{
    QString vert_g = "C:\\Users\\Allo4ka\\Desktop\\qtprojects\\WeatherApp\\grid.vsh";
    QString frag_g = "C:\\Users\\Allo4ka\\Desktop\\qtprojects\\WeatherApp\\grid.fsh";
    QString vert_t = "C:\\Users\\Allo4ka\\Desktop\\qtprojects\\WeatherApp\\text.vsh";
    QString frag_t = "C:\\Users\\Allo4ka\\Desktop\\qtprojects\\WeatherApp\\text.fsh";

    shaderProgram_g = new QOpenGLShaderProgram();
    shaderProgram_t = new QOpenGLShaderProgram();

    shaderProgram_g->create();
    shaderProgram_g->addShaderFromSourceFile(QOpenGLShader::Vertex, vert_g);
    shaderProgram_g->addShaderFromSourceFile(QOpenGLShader::Fragment, frag_g);
    shaderProgram_g->link();
    //shaderProgram_g->bind();

    shaderProgram_t->create();
    shaderProgram_t->addShaderFromSourceFile(QOpenGLShader::Vertex, vert_t);
    shaderProgram_t->addShaderFromSourceFile(QOpenGLShader::Fragment, frag_t);
    shaderProgram_t->link();
    //shaderProgram_t->bind();

    l_vertex = shaderProgram_g->attributeLocation("vertex");

    l_text = shaderProgram_t->attributeLocation("_text");
    l_projection = shaderProgram_t->uniformLocation("projection");
    l_textColor = shaderProgram_t->uniformLocation("textColor");

    qDebug() << l_vertex << "" << l_text << " " << l_textColor;
}

/*********************************************************************/

/*void DrawData::initVertices()
{
    N = 24;
    GLfloat xpos, ypos, scale = 0.005, w, h;
    xpos = 0.5 + Characters.Bearing.x * scale;
    ypos = 0.5 - (Characters.Size.y - Characters.Bearing.y)*scale;
    w = Characters.Size.x * scale;
    h = Characters.Size.y * scale;

    GLfloat vertices [N];
    vertices[0] = xpos;
    vertices[1] = ypos + h;
    vertices[2] = 0.0;
    vertices[3] = 0.0;

    vertices[4] = xpos;
    vertices[5] = ypos;
    vertices[6] = 0.0;
    vertices[7] = 1.;

    vertices[8] = xpos + w;
    vertices[9] = ypos;
    vertices[10] = 1.0;
    vertices[11] = 1.0;

    vertices[12] = xpos;
    vertices[13] = ypos + h;
    vertices[14] = 0.0;
    vertices[15] = 0.0;

    vertices[16] = xpos + w;
    vertices[17] = ypos;
    vertices[18] = 1.0;
    vertices[19] = 1.0;

    vertices[20] = xpos + w;
    vertices[21] = ypos + h;
    vertices[22] = 1.0;
    vertices[23] = 0.0;

    qDebug() << "*********************************" << endl;
    qDebug() << vertices[0]  << " " << vertices[1]  << " " << vertices[2]  << " " << vertices[3];
    qDebug() << vertices[4]  << " " << vertices[5]  << " " << vertices[6]  << " " << vertices[7];
    qDebug() << vertices[8]  << " " << vertices[9]  << " " << vertices[10] << " " << vertices[11];
    qDebug() << vertices[12] << " " << vertices[13] << " " << vertices[14] << " " << vertices[15];
    qDebug() << vertices[16] << " " << vertices[17] << " " << vertices[18] << " " << vertices[19];
    qDebug() << vertices[20] << " " << vertices[21] << " " << vertices[22] << " " << vertices[23];
    qDebug() << "*********************************" << endl;

    vbo->allocate(vertices, sizeof(vertices));

}*/

/*********************************************************************/

void DrawData::readData(QString fileName)
{
   // data = Data::readData(fileName);
    grid->readData(fileName);
    //grid->formVertices();
    update();
}

/*********************************************************************/
