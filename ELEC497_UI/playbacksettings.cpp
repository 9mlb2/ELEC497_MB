#include "playbacksettings.h"
#include "ui_playbacksettings.h"

PlaybackSettings::PlaybackSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlaybackSettings)
{
    ui->setupUi(this);

    //style for widget
    setFont (QFont ("Browallia", 12));

    ui->playbackSettingsLabel->setText("Playback Settings");
    //set font
    QFont font = ui->playbackSettingsLabel->font();
    font.setPointSize(28);
    font.setBold(true);
    ui->playbackSettingsLabel->setFont(font);
}

PlaybackSettings::~PlaybackSettings()
{
    delete ui;
}
