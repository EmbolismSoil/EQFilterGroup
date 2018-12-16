#include <QApplication>
#include <QAudioDecoder>
#include <QMediaContent>
#include <QAudioOutput>
#include <QUrl>
#include <QBuffer>
#include "AudioPlayer.h"
#include "EQWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EQWidget widget("/home/lee/github/DJ/radio/薛凯琪 - 奇洛李维斯回信.mp3");
    widget.show();

    return a.exec();
}
