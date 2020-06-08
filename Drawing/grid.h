#ifndef GRID_H
#define GRID_H

#include <QObject>
#include "data.h"
#include "text.h"

class Grid : public QObject
{
    Q_OBJECT
    QList<Data> *points;
    Text text;
public:

    explicit Grid(QObject *parent = nullptr);
    Grid(QString fileName);
    void paintGrid();
    void paintText();
    void formVisible(int w, int h);



signals:

};

#endif // GRID_H
