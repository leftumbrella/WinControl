#include "Controlled.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controlled w;
    w.show();
    return a.exec();
}
