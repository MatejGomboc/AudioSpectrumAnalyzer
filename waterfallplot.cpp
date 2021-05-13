#include "waterfallplot.h"
#include <QPainter>
#include <QPaintEvent>


WaterfallPlot::WaterfallPlot(QWidget* parent) :
    QWidget(parent),
    m_waterfall(width(), height())
{
    QPainter painter;
    painter.begin(&m_waterfall);
    painter.fillRect(m_waterfall.rect(), QBrush(Qt::GlobalColor::black));
    painter.end();
}

void WaterfallPlot::addData(const qreal data[], size_t count, qreal scroll_fraction)
{
    if (count < 2) {
        return;
    }

    QPainter painter;
    painter.begin(&m_waterfall);

    painter.fillRect(m_waterfall.rect(), QBrush(Qt::GlobalColor::black));

    qreal interval_width = static_cast<qreal>(m_waterfall.rect().width()) / (count - 1);
    int strip_thickness = m_waterfall.rect().height() * scroll_fraction;

    for (size_t i = 0; i < count - 1; i++) {
        QLinearGradient gradient;

        gradient.setStart(0, 0);
        gradient.setFinalStop(interval_width, 0);

        gradient.setColorAt(0, getColorFromValue(data[i]));
        gradient.setColorAt(1, getColorFromValue(data[i + 1]));

        painter.setPen(QPen(Qt::PenStyle::NoPen));
        painter.setBrush(gradient);

        painter.drawRect(interval_width * i, 0, interval_width, strip_thickness);
    }

    painter.end();
    update();
}

void WaterfallPlot::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0, 0, width(), height(), m_waterfall);
    painter.end();
}

QColor WaterfallPlot::getColorFromValue(qreal value)
{
    if (value < 0) {
        value = 0;
    } else if (value > 1) {
        value = 1;
    }

    return QColor::fromHsv(value * 359, 255, 255, 255);
}
