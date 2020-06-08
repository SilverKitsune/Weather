#include "grid.h"

//TODO преобразовать координаты
//TODO вывести текстом попадающие на экран температуры

//TODO сформировать вершины
//TODO инициализировать шейдеры, загрузить в них вершины
//TODO нарисовать вершины

Grid::Grid(QObject *parent) : QObject(parent)
{

}

Grid::Grid(QString fileName)
{
    points = Data::readData(fileName);
}

void Grid::formVisible(int w, int h)
{

}
