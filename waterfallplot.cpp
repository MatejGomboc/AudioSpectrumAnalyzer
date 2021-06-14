#include "waterfallplot.h"
#include <QPainter>
#include <QPaintEvent>


WaterfallPlot::WaterfallPlot(QWidget* parent) :
    QWidget(parent),
    m_waterfall(1024, 1024)
{
    QPainter painter;
    painter.begin(&m_waterfall);
    painter.fillRect(m_waterfall.rect(), QBrush(Qt::GlobalColor::black));
    painter.end();
}

void WaterfallPlot::addData(const qreal data[], size_t count)
{
    if (count < 2) {
        return;
    }

    QPainter painter;
    painter.begin(&m_waterfall);

    int strip_thickness = m_waterfall.rect().height() / 5;

    int interval_width = (m_waterfall.rect().width() + count - 1) / (count - 1);
    int interval_offset = (interval_width * (count - 1) - m_waterfall.rect().width()) / 2;

    for (size_t i = 0; i < count - 1; i++) {
        int interval_start;
        if (i == 0) {
            interval_start = 0;
        } else {
            interval_start = interval_width * i - interval_offset;
        }

        int actual_interval_width;
        if ((i == 0) || (i == count - 2)) {
            actual_interval_width = interval_width - interval_offset;
        } else {
            actual_interval_width = interval_width;
        }

        QLinearGradient gradient;
        gradient.setStart(interval_start, 0);
        gradient.setFinalStop(interval_start + actual_interval_width, 0);

        QColor color_start = getColorFromValue(data[i]);
        QColor color_end = getColorFromValue(data[i + 1]);
        gradient.setColorAt(0, color_start);
        gradient.setColorAt(1, color_end);

        painter.setPen(QPen(Qt::PenStyle::NoPen));
        painter.setBrush(gradient);

        painter.drawRect(interval_start, 0, actual_interval_width, strip_thickness);
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

    return QColor::fromHsvF(value, 1.0, 1.0, 1.0);
}
