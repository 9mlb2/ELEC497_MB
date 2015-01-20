#ifndef PLAYBACKMODE_H
#define PLAYBACKMODE_H

#include <QWidget>
#include <QMultimedia>
#include <QtWidgets>
#include <QtMultimediaWidgets>
#include <QMediaPlayer>

#include <QtGui/QMovie>

#include "heatmap.h"

#include "datapoint.h"

namespace Ui {
class PlaybackMode;
}

class QGraphicsVideoItem;
class QAbstractButton;
class QSlider;
class QLabel;
class QComboBox;

class PlaybackMode : public QWidget
{
    Q_OBJECT

public:
    PlaybackMode(QWidget *parent = 0);
    ~PlaybackMode();

    HeatMap m; //left foot
    HeatMap m2; // right foot
    vector<DataPoint>* vec;
    vector<DataPoint>* vec2;
    QPixmap pix;
    QPixmap pix2;
    QGraphicsScene *Lscene;
    QGraphicsScene *Rscene;
    QGraphicsItem* pixItem;
    QGraphicsItem* pixItem2;
    //float fudger; // what is this "fudger" for?
    QImage LFootMask;
    QImage RFootMask;

    QString vidPathText;
    //qreal playbackRate() const;
    //QGraphicsVideoItem *videoItem; // for playing video

public slots:
    void openFile();
    //void play();
    //void setPlaybackRate(float rate);

signals:
   // void changeRate(qreal rate);

private slots:
   // void on_vidPath_returnPressed();
    void on_pauseButton_clicked();
   /* void on_rewindButton_clicked();
    void mediaStateChanged(QMediaPlayer::State state);*/

    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    //void handleError();

    void on_playButton_clicked();
    void on_vidStop_clicked();
   // void updateRate();

    //void on_rateBox_activated(int index);

    //void on_rateBox_currentIndexChanged(int index);

    void on_bookmarkButton_clicked();

private:
    Ui::PlaybackMode *ui;

    QMediaPlayer mediaPlayer;
    QAbstractButton *playButton;
    QSlider *positionSlider;
   // QComboBox *rateBox;
   // QLabel *errorLabel;

};

#endif // PLAYBACKMODE_H
