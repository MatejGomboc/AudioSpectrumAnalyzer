#ifndef WATERFALLPLOT_H
#define WATERFALLPLOT_H

#include <QWidget>

class WaterfallPlot : public QWidget
{
    Q_OBJECT

public:
    explicit WaterfallPlot(QWidget* parent = nullptr);

private:
    void paintEvent(QPaintEvent* event) override;

    QPixmap m_waterfall;
};

#endif // WATERFALLPLOT_H
