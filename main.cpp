#include "interface.h"
#include <QApplication>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFileInfo ths(argv[0]);
    Interface w(ths.fileName());
    w.show();

    return a.exec();
}
