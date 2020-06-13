#include "drawdata.h"
#include "iostream"
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QCoreApplication>
#include <math.h>
#include <ft2build.h>

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
        qDebug() << "ERROR::FREETYPE: Could not init FreeType Library" << endl;
    FT_Face face;
    if (FT_New_Face(ft, (QCoreApplication::applicationDirPath().toUtf8() + "/fonts/trebuc.ttf"), 0, &face))
        qDebug() << "ERROR::FREETYPE: Failed to load font" << endl;

    FT_Set_Pixel_Sizes(face,0,12);


    for(char i = '0'; i <='9'; i++)
    {
        // Load character glyph
        if (FT_Load_Char(face, i, FT_LOAD_RENDER))
        {
            qDebug() << "ERROR::FREETYTPE: Failed to load Glyph" << endl;
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
    this->initializeOpenGLFunctions();
    m_context.create();
    makeCurrent();

    if (!this->isInitialized())
    {
        qDebug() << "Unable to Initialize OpenGL 3.3 Core." << endl;
        return;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.4f, 0.6f, 0.8f, 1.00f);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    initShaders();
    initTextures();
    initTemperatureGrid();
}

/*********************************************************************/

void DrawData::resizeGL(int w, int h)
{
    grid->setScale(2.0/w, 2.0/h);

    glViewport(0,0,w,h);
}

/*********************************************************************/

void DrawData::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    paintTemperatureGrgid();

}

/*********************************************************************/

void DrawData::initShaders()
{
    QString vert_g = QCoreApplication::applicationDirPath()+"/Shaders/grid.vsh";
    QString frag_g = QCoreApplication::applicationDirPath()+"/Shaders/grid.fsh";
    QString vert_t = QCoreApplication::applicationDirPath()+"/Shaders/text.vsh";
    QString frag_t = QCoreApplication::applicationDirPath()+"/Shaders/text.fsh";

    shaderProgram_g = new QOpenGLShaderProgram();
    shaderProgram_t = new QOpenGLShaderProgram();

    shaderProgram_g->create();
    shaderProgram_g->addShaderFromSourceFile(QOpenGLShader::Vertex, vert_g);
    shaderProgram_g->addShaderFromSourceFile(QOpenGLShader::Fragment, frag_g);
    shaderProgram_g->link();

    shaderProgram_t->create();
    shaderProgram_t->addShaderFromSourceFile(QOpenGLShader::Vertex, vert_t);
    shaderProgram_t->addShaderFromSourceFile(QOpenGLShader::Fragment, frag_t);
    shaderProgram_t->link();

    l_vertex = shaderProgram_g->attributeLocation("vertex");

    l_text = shaderProgram_t->attributeLocation("_text");
    l_projection = shaderProgram_t->uniformLocation("projection");
    l_textColor = shaderProgram_t->uniformLocation("textColor");
}

/*********************************************************************/

void DrawData::readData(QString fileName)
{
    grid->readData(fileName);
    update();
}

/*********************************************************************/

void DrawData::paintTemperatureGrgid()
{
    if(!grid->isEmpy())
        grid->formVertices();

    /* ********************** */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    shaderProgram_t->bind();
    glActiveTexture(GL_TEXTURE0);

    for(int i = 0; i < 10 && grid->getSizeOfTextVertAt(i) > 0; i++)
    {
        QOpenGLBuffer *vbo_textures = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        vbo_textures->create();
        grid->allocateVboTextAt(i, vbo_textures);

        glBindTexture(GL_TEXTURE_2D, grid->textures->at(i).TextureID);
        vbo_textures->bind();

        shaderProgram_t->enableAttributeArray(l_text);
        shaderProgram_t->setAttributeBuffer(l_text,GL_FLOAT,0,4);
        glDrawArrays(GL_TRIANGLES,l_text,grid->getSizeOfTextVertAt(i)/4);
        glBindTexture(GL_TEXTURE_2D, 0);

        vbo_textures->release();
        vbo_textures->destroy();

        delete vbo_textures;
    }
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

    grid->deleteTextVert();

}

/*********************************************************************/

void DrawData::initTemperatureGrid()
{
    grid->vbo_textures->create();
    grid->vbo_vertices->create();
    grid->ibo_vertices->create();
}

/*********************************************************************/
