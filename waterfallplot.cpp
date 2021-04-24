#include "waterfallplot.h"

WaterfallPlot::WaterfallPlot(QWidget* parent) :
    QWidget(parent)
{
    m_grid_layout->setContentsMargins(0, 0, 0, 0);
    m_grid_layout->addWidget(m_graphics_view);

    m_graphics_view->setScene(m_graphics_scene);

    m_graphics_scene->setBackgroundBrush(QBrush(Qt::GlobalColor::black, Qt::BrushStyle::SolidPattern));
    m_graphics_scene->addText("Hi there!");
}
