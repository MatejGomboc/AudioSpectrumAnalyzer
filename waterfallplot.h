#ifndef WATERFALLPLOT_H
#define WATERFALLPLOT_H

#include <QWidget>

class WaterfallPlot : public QWidget
{
    Q_OBJECT

public:
    explicit WaterfallPlot(QWidget* parent = nullptr);
    void addData(const qreal data[], size_t count, qreal new_min_freq, qreal new_max_freq);

private:
    void paintEvent(QPaintEvent* event) override;
    QColor getColorFromValue(qreal value);

    QImage m_waterfall;
    qreal m_min_freq = 0;
    qreal m_max_freq = 0;
};

#endif // WATERFALLPLOT_H
