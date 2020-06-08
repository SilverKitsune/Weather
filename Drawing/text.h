#ifndef TEXT_H
#define TEXT_H

#include <QObject>
#include <QtGui/QSurfaceFormat>
#include <QtGui/qopengl.h>
#include "includes/glm/glm/glm.hpp"

/** @brief Character - структура дляя хранения текстуры глифа */
struct Character {
    GLuint     TextureID; // ID текстуры глифа
    glm::vec2  Size;      // Размеры глифа
    glm::vec2  Bearing;   // Смещение верхней левой точки глифа
    int     Advance;   // Горизонтальное смещение до начала следующего глифа
};

class Text : public QObject
{
    Q_OBJECT

public:
    explicit Text(QObject *parent = nullptr);

signals:

};


#endif // TEXT_H
