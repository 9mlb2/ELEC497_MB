#ifndef PLAYBACKSETTINGS_H
#define PLAYBACKSETTINGS_H

#include <QDialog>

namespace Ui {
class PlaybackSettings;
}

class PlaybackSettings : public QDialog
{
    Q_OBJECT

public:
    explicit PlaybackSettings(QWidget *parent = 0);
    ~PlaybackSettings();

private:
    Ui::PlaybackSettings *ui;
};

#endif // PLAYBACKSETTINGS_H
