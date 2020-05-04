#include "drawdot.h"
#include "iostream"
#include <QOpenGLBuffer>
#include <math.h>
//#define M_PI 100

DrawDot::DrawDot()
{
    shaderProgram = new QGLShaderProgram( this );
}

void DrawDot::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,800,600,0,0,1);
    initShaders();
}

void DrawDot::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void DrawDot::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //glEnable(GL_CULL_FACE);
        glClearDepth(1.0);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glBegin(GL_TRIANGLES);
          //glColor3ub(255, 255, 255);
        glVertex2f(0.0,1.0);
        glVertex2f(-1,-1);
        glVertex2f(1,-1);
        glEnd();
        //glFlush();
}

//void DrawDot::mouseMoveEvent(QMouseEvent *event)
//{

//}

//void DrawDot::mousePressEvent(QMouseEvent *event)
//{

//}

//void DrawDot::wheelEvent(QWheelEvent *event)
//{

//}

void DrawDot::initShaders()
{
    if(!shaderProgram->addShaderFromSourceCode(QGLShader::Vertex,"vertexsh2.vsh"))
        std::cout << "not added";
    else std::cout << "added";
    /*if(!shaderProgram->addShaderFromSourceCode(QGLShader::Vertex,"vertexsh.vsh"))
        std::cout << "not added";
    else std::cout << "added";*/
    /*if (!shaderProgram->addShaderFromSourceCode(QGLShader::Fragment,
                                                    "void main(void)\n{gl_FragColor = vec4(1, 0, 0, 1);}"))
            close();

        // Compile fragment shader
        if (!shaderProgram->addShaderFromSourceCode(QGLShader::Vertex,
                                                    "void main(void)\n{gl_Position = ftransform();}"))
            close();*/

        // Link shader pipeline
        if (!shaderProgram->link())
            close();

        // Bind shader pipeline for use
        if (!shaderProgram->bind())
            close();
}
