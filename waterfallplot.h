#ifndef WATERFALLPLOT_H
#define WATERFALLPLOT_H

#include <QWidget>

class WaterfallPlot : public QWidget
{
    Q_OBJECT

public:
    explicit WaterfallPlot(QWidget* parent = nullptr);
    void addData(const qreal data[], size_t count, qreal scroll_fraction);

private:
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    QColor getColorFromValue(qreal value);

    QPixmap m_waterfall;
};

#endif // WATERFALLPLOT_H
