#include "spectrumanalyzer.h"

SpectrumAnalyzer::SpectrumAnalyzer(QObject* parent) :
    QObject(parent)
{
    m_test_timer->setTimerType(Qt::TimerType::PreciseTimer);
    m_test_timer->setInterval(1000);
    m_test_timer->setSingleShot(false);

    QObject::connect(m_test_timer, &QTimer::timeout, this, &SpectrumAnalyzer::onTestTimerTimeout, Qt::ConnectionType::QueuedConnection);
}

void SpectrumAnalyzer::startAnalysis()
{
    m_test_timer->start();
}

void SpectrumAnalyzer::stopAnalysis()
{
    m_test_timer->stop();
}

void SpectrumAnalyzer::onTestTimerTimeout()
{
    std::vector<qreal> spectrum;
    emit analysisCompleted(spectrum);
}
