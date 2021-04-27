#include "waterfallplot.h"
#include <QPainter>
#include <QResizeEvent>
#include <QPaintEvent>


WaterfallPlot::WaterfallPlot(QWidget* parent) :
    QWidget(parent),
    m_waterfall(width(), height())
{
    QPainter painter;
    painter.begin(&m_waterfall);
    painter.fillRect(m_waterfall.rect(), QBrush(Qt::GlobalColor::black));

    QLinearGradient gradient;
    gradient.setStart(m_waterfall.rect().left(), m_waterfall.rect().top());
    gradient.setFinalStop(m_waterfall.rect().right(), m_waterfall.rect().top());
    gradient.setColorAt(0, Qt::GlobalColor::red);
    gradient.setColorAt(1, Qt::GlobalColor::blue);

    painter.setBrush(gradient);
    painter.drawRect(m_waterfall.rect().left(), m_waterfall.rect().top(), m_waterfall.rect().width(), m_waterfall.rect().height() / 10);

    painter.end();
}

void WaterfallPlot::resizeEvent(QResizeEvent* event)
{
    m_waterfall = m_waterfall.scaled(event->size());
}

void WaterfallPlot::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0, 0, m_waterfall);
    painter.end();
}
