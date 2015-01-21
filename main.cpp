#include "snapping.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    snapping w;

    w.show();
    return a.exec();
}
