#ifndef WATERFALLPLOT_H
#define WATERFALLPLOT_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGridLayout>

class WaterfallPlot : public QWidget
{
    Q_OBJECT

public:
    explicit WaterfallPlot(QWidget* parent = nullptr);

private:
    QGridLayout* m_grid_layout = new QGridLayout(this);
    QGraphicsView* m_graphics_view = new QGraphicsView(this);
    QGraphicsScene* m_graphics_scene = new QGraphicsScene(this);
};

#endif // WATERFALLPLOT_H
