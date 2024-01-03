
#include "mainwindow.h"
#include "Scan.h"
#include "Gramme.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include<unordered_map>
using namespace std;



int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

}
