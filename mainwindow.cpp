#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{   
    setMenuBar(m_menu_bar);
    setStatusBar(m_status_bar);
    setCentralWidget(m_central_widget);

    m_central_grid_layout->addWidget(m_waterfall_plot);

    showMaximized();

    QVector<qreal> spectrum;
    for (size_t i = 0; i < 1000; i++) {
        spectrum.push_back(static_cast<qreal>(i) / 999.0);
    }
    m_waterfall_plot->addData(spectrum.data(), spectrum.size(), 0.1);

    spectrum.clear();
    for (size_t i = 0; i < 100; i++) {
        spectrum.push_back(static_cast<qreal>(i) / 99.0);
    }
    m_waterfall_plot->addData(spectrum.data(), spectrum.size(), 0.1);

    spectrum.clear();
    for (size_t i = 0; i < 10; i++) {
        spectrum.push_back(static_cast<qreal>(i) / 9.0);
    }
    m_waterfall_plot->addData(spectrum.data(), spectrum.size(), 0.1);

    spectrum.clear();
    spectrum.push_back(1.0);
    m_waterfall_plot->addData(spectrum.data(), spectrum.size(), 0.1);

    spectrum.clear();
    for (size_t i = 0; i < 4096; i++) {
        spectrum.push_back(static_cast<qreal>(i) / 4095.0);
    }
    m_waterfall_plot->addData(spectrum.data(), spectrum.size(), 0.1);
}
