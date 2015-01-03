#include <QApplication>
#include <QFile>
#include "mainwindow.h"


int main(int argc, char **argv)
{
    QApplication app(argc,argv);
    MainWindow w;
    w.resize(512, 512);
//    QFile file("styleSheet/darkOrange");
//    file.open(QFile::ReadOnly);
//    QString stylesheet = QLatin1String(file.readAll());
//    w.setStyleSheet(stylesheet);
    w.setWindowTitle(QString("Plain Scene"));
    w.show();
    app.exec();
}
