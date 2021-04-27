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
    gradient.setStart(0, 0);
    gradient.setFinalStop(m_waterfall.rect().width(), 0);
    gradient.setColorAt(0, Qt::GlobalColor::red);
    gradient.setColorAt(1, Qt::GlobalColor::blue);

    painter.setPen(QPen(Qt::PenStyle::NoPen));
    painter.setBrush(gradient);
    painter.drawRect(0, 0, m_waterfall.rect().width(), m_waterfall.rect().height() / 10);

    painter.end();
}

void WaterfallPlot::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0, 0, width(), height(), m_waterfall);
    painter.end();
}
