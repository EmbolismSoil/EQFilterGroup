#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(const QString &fname, QObject *parent)
{
    auto content = new QMediaContent(QUrl(fname));
    QMediaResource resource = content->canonicalResource();
    QAudioFormat format;

    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setCodec("audio/pcm");
    format.setSampleSize(32);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDecoder* decoder = new QAudioDecoder(this);
    decoder->setAudioFormat(format);
    decoder->setSourceFilename(fname);
    qDebug() << "isvalide: " << format.isValid();

    _output = new QAudioOutput(format, this);
    _buffer = new AudioBufferDevice(decoder, this);
    _buffer->open(QIODevice::ReadOnly);
}

void AudioPlayer::play()
{
    _output->start(_buffer);
}
