#ifndef TEXT_H
#define TEXT_H

#include <QObject>
#include <QtGui/QSurfaceFormat>
#include <QtGui/qopengl.h>
#include "includes/glm/glm/glm.hpp"

class Text : public QObject
{
    Q_OBJECT
    int c;

public:
    explicit Text(QObject *parent = nullptr);

signals:

};


#endif // TEXT_H
