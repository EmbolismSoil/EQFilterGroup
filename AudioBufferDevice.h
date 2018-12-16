#ifndef AUDIOBUFFERDEVICE_H
#define AUDIOBUFFERDEVICE_H

#include <QObject>
#include <QIODevice>
#include <QAudioDecoder>
#include <QQueue>
#include <QAudioBuffer>
#include <QBuffer>
#include "EQFilterGroup.h"

class AudioBufferDevice : public QIODevice
{
    Q_OBJECT
public:
    explicit AudioBufferDevice(QAudioDecoder *decoder, QObject *parent = nullptr);
    virtual bool atEnd() const override;
    virtual qint64 bytesAvailable() const override;

protected:
    virtual qint64 readData(char* data, qint64 size) override;

    virtual qint64 writeData(const char *data, qint64 maxSize);
signals:

public slots:
    void onBufferReady();
    void onFinished();
    void onErroe(QAudioDecoder::Error error);

    void setLowGain(float gain){_filter->setLowGain(gain);}
    void setMidGain(float gain){_filter->setMidGain(gain);}
    void setHighGain(float gain){_filter->setHighGain(gain);}

private:
    QAudioDecoder* _decoder;
    QQueue<QBuffer*> _queue;
    QQueue<QAudioBuffer*> _abuffer_queue;
    EQFilterGroup* _filter;
    bool _isFinished;
};

#endif // AUDIOBUFFERDEVICE_H
