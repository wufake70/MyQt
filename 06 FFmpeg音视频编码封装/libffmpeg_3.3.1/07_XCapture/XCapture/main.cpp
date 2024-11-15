#include "xcapture.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XCapture w;
    w.show();
    return a.exec();
}
