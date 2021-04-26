#ifndef WATERFALLPLOT_H
#define WATERFALLPLOT_H

#include <QGridLayout>
#include <QGraphicsView>

class WaterfallPlot : public QWidget
{
    Q_OBJECT

public:
    explicit WaterfallPlot(QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QGridLayout* m_central_grid_layout = new QGridLayout(this);
    QGraphicsView* m_graphics_view = new QGraphicsView(this);
};

#endif // WATERFALLPLOT_H
