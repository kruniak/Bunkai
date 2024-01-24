#include "Bunkai.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Bunkai w;

    w.show();
    return a.exec();
}
