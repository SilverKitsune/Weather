#ifndef GRID_H
#define GRID_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "data.h"
#include "includes/glm/glm/glm.hpp"


/** @brief Character - структура дляя хранения текстуры глифа */
struct Character
{
    /** @brief TextureID - ID текстуры глифа */
    GLuint textureID;

    /** @brief Size - размеры глифа*/
    glm::vec2 size;

    /** @brief Bearing - Смещение верхней левой точки глифа */
    glm::vec2 bearing;

    /** @brief Advance - горизонтальное смещение до начала следующего глифа */
    int advance;
};

class Grid : public QObject
{
    Q_OBJECT

    /** @brief scaleX - масштаб по оси X */
    float scaleX;

    /** @brief scaleY - масштаб по оси Y */
    float scaleY;

    /** @brief scaleMap - масштаб карты */
    float scaleMap;

    /** @brief centreOfGrid - географические координаты центра виджета */
    glm::vec2 centreOfWidget;

    /** @brief text_vert - координаты текста*/
    QVector<QVector<GLfloat>> *text_vert;

    /** @brief points - данные о температуре*/
    QList<Data> *points = nullptr;

    /** @brief Characters - массив загруженных текстур для текста*/
    QVector<Character> *textures;

    /** @brief appendTextVert - добавление элемента в вектор с координатами текста
     *  @param c - цифра
     *  @param x - координата X правого угла
     *  @param y - координата Y правого угла */
    void appendTextVert(int c, GLfloat x, GLfloat y);

public:

    void setMapScale(float zoom) { scaleMap *= zoom;}

    void changeCenterOfWidget(int w, int h);

    float getScaleX() {return scaleX;}

    float getScaleY() {return scaleY;}

    /** @brief ibo_vertices - Index Buffer Object */
    QOpenGLBuffer *ibo_vertices;

    /** @brief vbo_vertices - Vertex Buffer Object */
    QOpenGLBuffer *vbo_vertices = nullptr;

    explicit Grid(QObject *parent = nullptr);

    ~Grid();

    /** @brief getMapScale возвращает текущий масштаб карты
     *  @return масштаб карты */
    float getMapScale() {return scaleMap;}

    /** @brief getCentreOfWidget
     *  @return географические координаты, соответствующие центру виджета */
    glm::vec2 getCentreOfWidget() {return centreOfWidget;}

    /** @brief setCentre - изменение географиесой координаты центра виджета
     *  @param la
     *  @param fi */
    void setCentre(float la, float fi)
    {
        centreOfWidget.x = la;
        centreOfWidget.y = fi;
    }

    /** @brief setScale изменяет масштаб по осям X и Y
     *  @param sx - новый масштаб по оси Х
     *  @param sy - новый масштаб по Y */
    void setScale(float sx, float sy);

    /** @brief initTextures - формироавние текстур символов */
    void initTextures();

    /** @brief formVertices - формирование вершин для отрисовки */
    void formVertices();

    /** @brief readData - чтение данных из файла
     *  @param fileName - имя файла */
    void readData(QString fileName);

    /** @brief toOpengl - перевод географических координат в экранные
     *  @param x
     *  @param y
     *  @param Cx
     *  @param Cy
     *  @return */
    glm::vec2 toOpengl(float x, float y, float Cx, float Cy);

    /** @brief isEmpy - возвращает false, если данные были загружены, иначе - true
     *  @return false, если данные были загружены, иначе - true */
    bool isEmpy() {return !points;}

    /** @brief getSizeOfTextVertAt - получение количества повторений цифры i среди значений температуры
     *  @param i - цифра
     *  @return количество повторений цифры i */
    int getSizeOfTextVertAt(int i);

    /** @brief allocateVboTextAt - заполнение буфера координатами цифры i
     *  @param i - цифра
     *  @param vbo - указатель на буфер */
    void allocateVboTextAt(int i, QOpenGLBuffer *vbo);

    /** @brief deleteTextVert - очистка вектора с координатами текста*/
    void deleteTextVert();

    /** @brief appendTexture - добавление сгенерированной текстуры
     *  @param _id - идентификатор текстуры
     *  @param _size - размеры глифа
     *  @param _bearing - смещение верхней левой точки глифа
     *  @param _advance - горизонтальное смещение до следующего глифа */
    void appendTexture(GLuint _id, glm::ivec2 _size, glm::ivec2 _bearing, int _advance);

    /** @brief getTextureID - возвращает идентификатор текстуры цифры i
     *  @param i - цифра
     *  @return идентификатор текстуры i */
    GLuint getTextureID(int i) { return textures->at(i).textureID; }

    /** @brief fromPixelsToGeo - перевод из экранных координат в географические
     *  @param x
     *  @param y
     *  @return */
    glm::vec2 fromPixelsToGeo(int x, int y);
};

#endif // GRID_H
