#include "waterfallplot.h"
#include <QPainter>
#include <QPaintEvent>
#include <QElapsedTimer>

WaterfallPlot::WaterfallPlot(QWidget* parent) :
    QWidget(parent)
{
}

void WaterfallPlot::addData(const qreal data[], size_t count, qreal scroll_fraction)
{
    if (count == 0) {
        return;
    }

    QElapsedTimer timer;
    timer.start();

    if (m_waterfall.isNull()) {
        m_waterfall = QImage(count, 2048, QImage::Format::Format_ARGB32);
        m_waterfall.fill(Qt::GlobalColor::black);
        qDebug() << "new";
    }

    if (count != m_waterfall.width()) {
        m_waterfall = m_waterfall.scaledToWidth(count);
        qDebug() << "resized";
    }

    QImage waterfall_crop = m_waterfall.copy(0, 0, m_waterfall.width(), m_waterfall.height() - 1);

    QPainter painter;
    painter.begin(&m_waterfall);
    painter.drawImage(0, 1, waterfall_crop);
    painter.end();

    for (size_t i = 0; i < count; i++) {
        QColor color = getColorFromValue(data[i]);
        m_waterfall.setPixelColor(i, 0, color);
    }

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
    painter.drawImage(0, 0, m_waterfall, 0, 0, width(), height());
    painter.end();

    quint64 time_ms = timer.elapsed();
    qDebug() << "paintEvent, time(ms):" << time_ms;
}

QColor WaterfallPlot::getColorFromValue(qreal value)
{
    if (value < 0) {
        value = 0;
    } else if (value > 1) {
        value = 1;
    }

    return QColor::fromHsvF(value, 1.0, 1.0);
}
