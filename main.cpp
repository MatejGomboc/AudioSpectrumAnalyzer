#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);

    application.setWindowIcon(QIcon(":/icon.svg"));

    QFile style_sheet(":/style.qss");
    style_sheet.open(QFile::ReadOnly);
    application.setStyleSheet(style_sheet.readAll());
    style_sheet.close();

    MainWindow main_window;
    main_window.show();

    return application.exec();
}
