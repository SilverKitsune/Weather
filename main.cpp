#include "Drawing/drawdot.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DrawDot w;
    w.show();

    return a.exec();
}
