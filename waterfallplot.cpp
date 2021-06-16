#include "waterfallplot.h"
#include <QPainter>
#include <QPaintEvent>
#include <QElapsedTimer>

WaterfallPlot::WaterfallPlot(QWidget* parent) :
    QWidget(parent)
{
}

void WaterfallPlot::addData(const qreal data[], size_t count, qreal new_min_freq, qreal new_max_freq)
{
    if (count == 0) {
        return;
    }

    if (new_min_freq == new_max_freq) {
        return;
    }

    if (new_min_freq > new_max_freq) {
        qreal temp_freq = new_max_freq;
        new_max_freq = new_min_freq;
        new_min_freq = temp_freq;
    }

    if (m_waterfall.isNull()) {
        m_waterfall = QImage(count, 1, QImage::Format_ARGB32);
    } else {
        int new_height = (m_waterfall.height() < 1024) ? (m_waterfall.height() + 1) : m_waterfall.height();
        if ((new_max_freq < m_min_freq) || (new_min_freq > m_max_freq)) {
            m_waterfall = QImage(count, new_height, QImage::Format_ARGB32);
            m_waterfall.fill(Qt::GlobalColor::black);
        } else {
            int scaled_old_width = m_waterfall.width() * (m_max_freq - m_min_freq) / (new_max_freq - new_min_freq);
            int offset_of_old = count * (m_min_freq - new_min_freq) / (new_max_freq - new_min_freq);
            QImage new_waterfall = ;
        }
    }

    QPainter painter;
    painter.begin(&m_waterfall);

    for (size_t i = 0; i < count; i++) {
        QColor color = getColorFromValue(data[i]);
        painter.setPen(QPen(color));
        painter.drawPoint(i, 0);
    }

    painter.end();

    m_min_freq = new_min_freq;
    m_max_freq = new_max_freq;

    update();

    QElapsedTimer timer;
    timer.start();

    quint64 time_ms = timer.elapsed();
    qDebug() << "addData, time(ms):" << time_ms;
}

void WaterfallPlot::paintEvent(QPaintEvent* event)
{
    QElapsedTimer timer;
    timer.start();

    QPainter painter;
    painter.begin(this);
    painter.drawImage(0, 0, m_waterfall, 0, 0, width(), height());
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
