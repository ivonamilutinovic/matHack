#include "generator.h"
#include <QApplication>
#include "board.h"
#include "figures/figure_types.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Generator w;
    w.show();

    return a.exec();
}
