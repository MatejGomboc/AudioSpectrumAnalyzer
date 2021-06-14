#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QMenuBar>
#include <QStatusBar>
#include "waterfallplot.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    QMenuBar* m_menu_bar = new QMenuBar(this);
    QStatusBar* m_status_bar = new QStatusBar(this);
    QWidget* m_central_widget = new QWidget(this);
    QGridLayout* m_central_grid_layout = new QGridLayout(m_central_widget);
    WaterfallPlot* m_waterfall_plot = new WaterfallPlot(m_central_widget);
};

#endif // MAINWINDOW_H
