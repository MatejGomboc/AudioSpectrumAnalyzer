#include "waterfallplot.h"
#include <QPainter>
#include <QPaintEvent>
#include <QElapsedTimer>

WaterfallPlot::WaterfallPlot(QWidget* parent) :
    QWidget(parent),
    m_waterfall(width(), height())
{
    QElapsedTimer timer;
    timer.start();

    QPainter painter;
    painter.begin(&m_waterfall);
    painter.fillRect(m_waterfall.rect(), QBrush(Qt::GlobalColor::black));
    painter.end();

    quint64 time_ms = timer.elapsed();
    qDebug() << "WaterfallPlot, time(ms):" << time_ms;
}

void WaterfallPlot::addData(const qreal data[], size_t count, qreal scroll_fraction)
{
    if (count < 1) {
        return;
    }

    QElapsedTimer timer;
    timer.start();

    int strip_thickness = m_waterfall.rect().height() * scroll_fraction;
    m_waterfall.scroll(0, strip_thickness, m_waterfall.rect());

    QPainter painter;
    painter.begin(&m_waterfall);

    painter.setPen(QPen(Qt::PenStyle::NoPen));

    if (count == 1) {
        QColor color = getColorFromValue(data[0]);
        painter.setBrush(QBrush(color, Qt::SolidPattern));
        painter.drawRect(0, 0, m_waterfall.rect().width(), strip_thickness);
    } else {
        for (size_t i = 0; i < count - 1; i++) {
            int interval_start = (m_waterfall.rect().width() * i) / (count - 1);
            int interval_end = (m_waterfall.rect().width() * (i + 1)) / (count - 1);
            int interval_width = interval_end - interval_start;

            QLinearGradient gradient;
            gradient.setStart(interval_start, 0);
            gradient.setFinalStop(interval_end, 0);

            QColor color_start = getColorFromValue(data[i]);
            QColor color_end = getColorFromValue(data[i + 1]);
            gradient.setColorAt(0, color_start);
            gradient.setColorAt(1, color_end);

            painter.setBrush(gradient);

            painter.drawRect(interval_start, 0, interval_width, strip_thickness);
        }
    }

    painter.end();
    update();

    quint64 time_ms = timer.elapsed();
    qDebug() << "addData, time(ms):" << time_ms;
}

void WaterfallPlot::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event)

    QElapsedTimer timer;
    timer.start();

    QPixmap waterfall_scaled(event->size());
    QPainter painter;
    painter.begin(&waterfall_scaled);
    painter.drawPixmap(0, 0, waterfall_scaled.width(), waterfall_scaled.height(), m_waterfall);
    painter.end();
    m_waterfall = waterfall_scaled;

    quint64 time_ms = timer.elapsed();
    qDebug() << "resizeEvent, size:" << event->size() << ", time(ms):" << time_ms;
}

void WaterfallPlot::paintEvent(QPaintEvent* event)
{
    QElapsedTimer timer;
    timer.start();

    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0, 0, rect().width(), height(), m_waterfall);
    painter.end();

    quint64 time_ms = timer.elapsed();
    qDebug() << "paintEvent, rect:" << event->rect() << ", time(ms):" << time_ms;
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
