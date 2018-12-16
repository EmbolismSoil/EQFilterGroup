#include "EQWidget.h"

EQWidget::EQWidget(QString const& path, QWidget *parent) : QWidget(parent)
{
    _player = new AudioPlayer(path, this);
    _low = new QSlider(this);
    _mid = new QSlider(this);
    _high = new QSlider(this);
    _layout = new QVBoxLayout(this);

    _low->setOrientation(Qt::Horizontal);
    _low->setMinimum(0);
    _low->setMaximum(200);
    _low->setSingleStep(1);
    _low->setValue(100);

    _mid->setOrientation(Qt::Horizontal);
    _mid->setMinimum(0);
    _mid->setMaximum(200);
    _mid->setSingleStep(1);
    _mid->setValue(100);

    _high->setOrientation(Qt::Horizontal);
    _high->setMinimum(0);
    _high->setMaximum(200);
    _high->setSingleStep(1);
    _high->setValue(100);

    connect(_low, SIGNAL(valueChanged(int)), this, SLOT(setLowGain(int)));
    connect(_mid, SIGNAL(valueChanged(int)), this, SLOT(setMidGain(int)));
    connect(_high, SIGNAL(valueChanged(int)), this, SLOT(setHighGain(int)));
    _layout->addWidget(_low);
    _layout->addWidget(_mid);
    _layout->addWidget(_high);
    setLayout(_layout);
    _player->play();
}

void EQWidget::setLowGain(int n)
{
    float gain = float(n) / 100;
    _player->setLowGain(gain);
}

void EQWidget::setMidGain(int n)
{
    float gain = float(n) / 100;
    _player->setMidGain(gain);
}

void EQWidget::setHighGain(int n)
{
    float gain = float(n) / 100;
    _player->setHighGain(gain);
}
