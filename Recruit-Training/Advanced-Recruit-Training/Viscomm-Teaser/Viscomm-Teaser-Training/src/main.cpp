#include "MainMindow.h"
#include "InformationParser.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    InformationParser parser;
    if(!parser.readJSON())
    {
        qDebug() << "Unable to read JSON file.";
        exit(1);
    }
    w.setParser_(parser);
    w.updateInformation();
    w.show();
    return a.exec();
}
