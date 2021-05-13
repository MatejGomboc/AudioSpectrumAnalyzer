#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    resize(800, 600);
    showMaximized();

    setMenuBar(m_menu_bar);
    setStatusBar(m_status_bar);
    setCentralWidget(m_central_widget);

    m_central_grid_layout->addWidget(m_waterfall_plot);

    std::vector<qreal> spectrum(255, 0.5);
    m_waterfall_plot->addData(spectrum.data(), 255, 0.2);
}
