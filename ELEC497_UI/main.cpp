#include "mainwindow.h"
#include "playbackmode.h"
#include "playbacksettings.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    PlaybackMode w;
    //PlaybackSettings w;
    w.show();

    return a.exec();
}
