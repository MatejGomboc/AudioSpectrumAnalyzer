#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    resize(1024, 1024);
    showMaximized();

    setMenuBar(m_menu_bar);
    setStatusBar(m_status_bar);
    setCentralWidget(m_central_widget);

    m_central_grid_layout->addWidget(m_waterfall_plot);

    QVector<qreal> spectrum;
    for (size_t i = 0; i < 1024; i++) {
        spectrum.push_back(static_cast<qreal>(i) / 1023.0);
    }
    m_waterfall_plot->addData(spectrum.data(), spectrum.size());
}
