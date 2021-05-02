#ifndef SPECTRUMANALYZER_H
#define SPECTRUMANALYZER_H

#include <QObject>
#include <vector>
#include <QTimer>

class SpectrumAnalyzer : public QObject
{
    Q_OBJECT

public:
    explicit SpectrumAnalyzer(QObject* parent = nullptr);
    void startAnalysis();
    void stopAnalysis();

signals:
    void analysisCompleted(const std::vector<qreal>& spectrum);

private slots:
    void onTestTimerTimeout();

private:
    QTimer* m_test_timer = new QTimer(this);
};

#endif // SPECTRUMANALYZER_H
