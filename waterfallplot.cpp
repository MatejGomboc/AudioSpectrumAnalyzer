#include "waterfallplot.h"
#include <QPainter>
#include <QPaintEvent>
#include <QElapsedTimer>

WaterfallPlot::WaterfallPlot(QWidget* parent) :
    QWidget(parent),
    m_waterfall(1024, 1024)
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
    if (count == 0) {
        return;
    }

    QElapsedTimer timer;
    timer.start();

    int strip_thickness = m_waterfall.rect().height() * scroll_fraction;
    m_waterfall.scroll(0, strip_thickness, m_waterfall.rect());

    QPainter painter;
    painter.begin(&m_waterfall);

    if (count == 1) {
        painter.setPen(QPen(Qt::PenStyle::NoPen));
        QColor color = getColorFromValue(data[0]);
        painter.setBrush(QBrush(color, Qt::SolidPattern));
        painter.drawRect(0, 0, m_waterfall.rect().width(), strip_thickness);

    } else if (count == m_waterfall.rect().width() + 1) {
        for (size_t i = 0; i < count; i++) {
            QColor color = getColorFromValue(data[i]);
            painter.setPen(QPen(color));
            painter.drawLine(i, 0, i, strip_thickness);
        }

    } else if (count > m_waterfall.rect().width() + 1) {
        QVector<qreal> values(m_waterfall.rect().width() + 1, 0.0);
        QVector<int> nums(m_waterfall.rect().width() + 1, 0);
        for (size_t i = 0; i < count; i++) {
            int pixel_idx = (m_waterfall.rect().width() * i) / (count - 1);
            values[pixel_idx] += data[i];
            nums[pixel_idx]++;
        }
        for (size_t i = 0; i < m_waterfall.rect().width() + 1; i++) {
            qreal average = values[i] / nums[i];
            QColor color = getColorFromValue(average);
            painter.setPen(QPen(color));
            painter.drawLine(i, 0, i, strip_thickness);
        }

    } else {
        int interval_start = 0;
        QColor color = getColorFromValue(data[0]);
        for (size_t i = 0; i < count - 1; i++) {
            int interval_end = (m_waterfall.rect().width() * (i + 1)) / (count - 1);
            int interval_width = interval_end - interval_start;
            qreal slope = (data[i + 1] - data[i]) / interval_width;
            for (size_t j = 0; j < interval_width; j++) {
                painter.setPen(QPen(color));
                painter.drawLine(interval_start + j, 0, interval_start + j, strip_thickness);
                color = getColorFromValue(slope * j + data[i]);
            }
            interval_start = interval_end;
        }
    }

    painter.end();
    update();

    quint64 time_ms = timer.elapsed();
    qDebug() << "addData, time(ms):" << time_ms;
}

void WaterfallPlot::paintEvent(QPaintEvent* event)
{
    QElapsedTimer timer;
    timer.start();

    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0, 0, width(), height(), m_waterfall);
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
