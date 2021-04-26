#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);

    application.setWindowIcon(QIcon(":/icon.svg"));

    MainWindow main_window;
    main_window.show();

    return application.exec();
}
