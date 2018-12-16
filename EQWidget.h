#ifndef EQWIDGET_H
#define EQWIDGET_H

#include <QWidget>
#include "AudioPlayer.h"
#include <QSlider>
#include <QVBoxLayout>

class EQWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EQWidget(QString const& path, QWidget *parent = nullptr);

signals:

public slots:
    void setLowGain(int n);
    void setMidGain(int n);
    void setHighGain(int n);

private:
    AudioPlayer *_player;
    QSlider *_low;
    QSlider *_mid;
    QSlider *_high;
    QLayout* _layout;
};

#endif // EQWIDGET_H
