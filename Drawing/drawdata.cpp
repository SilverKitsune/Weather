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

DrawData::DrawData(QWidget *parent) : QOpenGLWidget(parent)
{
    vao = new QOpenGLVertexArrayObject();
    vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    resize(640,480);
}

void DrawData::initTextures()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    FT_Face face;
    if (FT_New_Face(ft, "C:\\Users\\Allo4ka\\Desktop\\qtprojects\\WeatherApp\\fonts\\trebuc.ttf", 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    FT_Set_Pixel_Sizes(face,0,48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

        // Load character glyph
        if (FT_Load_Char(face, '2', FT_LOAD_RENDER))
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
        Characters = character;
        // Characters[c] = character;

    FT_Done_Face(face);   // Завершение работы с шрифтом face
    FT_Done_FreeType(ft); // Завершение работы FreeType
}

/*void DrawData::renderText(string text, GLfloat x, GLfloat y, GLfloat scale, QVector3D color)
{

}*/

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

    printf("OpenGL : %s\n",
           glGetString(GL_VERSION)
    );

    initShaders();
    initTextures();



    // ** Vertex Array Object ** //
    vao->create();
    vao->bind();

    // ** Vertex Buffer Objects ** //
    vbo->create();
    vbo->bind();
    testVertices();
    shaderProgram->enableAttributeArray(l_vertex);
    shaderProgram->setAttributeBuffer(l_vertex,GL_FLOAT,0,4);
    //initTextures();
    vao->release();
    vbo->release();
    shaderProgram->release();
}

void DrawData::resizeGL(int width, int height)
{
    /* ***** Prepare Variables ***** */
    perspective.setToIdentity();
    float w = static_cast<float>(width);
    float h = static_cast<float>(height);
    float aspectRatio = w / h;

    // * ***** Set the Perspective Matrix ***** */
    perspective.perspective(65.0f, aspectRatio, 0.1f, 10.0f);
}

void DrawData::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    this->glBindTexture(GL_TEXTURE_2D, Characters.TextureID);
    shaderProgram->bind();
    vao->bind();
    shaderProgram->setUniformValue(l_textColor, 0.0,0.0,0.0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    vao->release();
    shaderProgram->release();
    update();
}

void DrawData::initShaders()
{
    QString vert = "C:\\Users\\Allo4ka\\Desktop\\qtprojects\\WeatherApp\\sh.vsh";
    QString frag = "C:\\Users\\Allo4ka\\Desktop\\qtprojects\\WeatherApp\\sh.fsh";
    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->create();
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, vert);
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, frag);
    shaderProgram->link();
    shaderProgram->bind();

    l_vertex = shaderProgram->attributeLocation("vertex");
    l_projection = shaderProgram->uniformLocation("projection");
    l_textColor = shaderProgram->uniformLocation("textColor");
}

void DrawData::initGeometry()
{


}

void DrawData::paintData()
{

}

void DrawData::testVertices()
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
    qDebug() << vertices[0] << " " << vertices[1] << " " << vertices[2] << " " << vertices[3];
    qDebug() << vertices[4] << " " << vertices[5] << " " << vertices[6] << " " << vertices[7];
    qDebug() << vertices[8] << " " << vertices[9] << " " << vertices[10] << " " << vertices[11];
    qDebug() << vertices[12] << " " << vertices[13] << " " << vertices[14] << " " << vertices[15];
    qDebug() << vertices[16] << " " << vertices[17] << " " << vertices[18] << " " << vertices[19];
    qDebug() << vertices[20] << " " << vertices[21] << " " << vertices[22] << " " << vertices[23];
    qDebug() << "*********************************" << endl;

    vbo->allocate(vertices, sizeof(vertices));

}

/*void DrawData::formVertices()
{
    N = data->at(0).pointsData.size();
}*/

void DrawData::readData(QString fileName)
{
    data = Data::readData(fileName);
}
