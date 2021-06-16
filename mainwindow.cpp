#include "mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{   
    setMenuBar(m_menu_bar);
    setStatusBar(m_status_bar);
    setCentralWidget(m_central_widget);

    m_central_grid_layout->addWidget(m_waterfall_plot);

    QAction* start_action = m_menu_bar->addAction("Start");
    connect(start_action, &QAction::triggered, this, &MainWindow::OnStartKlicked, Qt::ConnectionType::QueuedConnection);

    QAction* stop_action = m_menu_bar->addAction("Stop");
    connect(stop_action, &QAction::triggered, this, &MainWindow::OnStopKlicked, Qt::ConnectionType::QueuedConnection);

    m_test_timer->setSingleShot(false);
    m_test_timer->setInterval(30);

    setMinimumWidth(800);
    setMinimumHeight(600);

    showMaximized();
}

void MainWindow::OnStartKlicked()
{
    connect(m_test_timer, &QTimer::timeout, this, &MainWindow::OnTimerTimeout, Qt::ConnectionType::QueuedConnection);
    m_test_timer->start();
}

void MainWindow::OnStopKlicked()
{
    m_test_timer->stop();
    disconnect(m_test_timer, &QTimer::timeout, this, &MainWindow::OnTimerTimeout);
}

void MainWindow::OnTimerTimeout()
{
    QVector<qreal> data(36864);
    for (size_t i = 0; i < data.size(); i++) {
        data[i] = QRandomGenerator::global()->generateDouble();
    }
    m_waterfall_plot->addData(data.data(), data.size(), 0.005);
}
