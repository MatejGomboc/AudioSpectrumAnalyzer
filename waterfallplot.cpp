#include "waterfallplot.h"

WaterfallPlot::WaterfallPlot(QWidget* parent) :
    QWidget(parent)
{
    m_central_grid_layout->addWidget(m_graphics_view);
    m_central_grid_layout->setContentsMargins(0, 0, 0, 0);

    m_graphics_view->setScene(new QGraphicsScene(m_graphics_view->rect(), this));
    m_graphics_view->setAlignment(Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignLeft);

    QLinearGradient gradient;
    gradient.setStart(0, 0);
    gradient.setFinalStop(m_graphics_view->scene()->width(), 0);
    gradient.setColorAt(0, Qt::GlobalColor::red);
    gradient.setColorAt(1, Qt::GlobalColor::blue);
    m_graphics_view->scene()->addRect(0, 0, m_graphics_view->scene()->width(), m_graphics_view->scene()->height(), QPen(Qt::PenStyle::NoPen), gradient);
}

void WaterfallPlot::resizeEvent(QResizeEvent* event)
{
}
