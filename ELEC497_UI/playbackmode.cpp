#include "playbackmode.h"
#include "ui_playbackmode.h"

#include <QtMultimedia> //videoplayer lib
#include <QVideoSurfaceFormat>
#include <QGraphicsVideoItem>
#include <QVideoWidget>
#include <QtWidgets>
#include <QStyle>
#include <QComboBox>


PlaybackMode::PlaybackMode(QWidget *parent) :
    QWidget(parent)
    , mediaPlayer(0, QMediaPlayer::VideoSurface)
    , playButton(0)
    , positionSlider(0)
    //, rateBox(0)
    //, errorLabel(0)
    , ui(new Ui::PlaybackMode)
    , m(QSize(400,400),QImage::Format_RGB32) //constructor for left heatmap
    , m2(QSize(400,400),QImage::Format_RGB32) // constructor for right heat map

{
    ui->setupUi(this);

    QVideoWidget *videoWidget = new QVideoWidget;

    //QAbstractButton *openButton = new QPushButton(tr("Open..."));
    connect(ui->openButton, SIGNAL(clicked()), this, SLOT(openFile()));

    /*ui->playButton = new QPushButton(this);
    ui->playButton->setEnabled(false);
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(on_playButton_clicked()));
*/
    positionSlider = new QSlider(Qt::Horizontal);
    ui->positionSlider->setRange(0, 0);


    /*ui->rateBox = new QComboBox(this);
    ui->rateBox->addItem("0.5x", QVariant(0.5));
    ui->rateBox->addItem("1.0x", QVariant(1.0));
    ui->rateBox->addItem("2.0x", QVariant(2.0));
    ui->rateBox->setCurrentIndex(1);

    connect(ui->rateBox, SIGNAL(activated(int)), SLOT(updateRate()));*/
    connect(ui->positionSlider, SIGNAL(sliderMoved(int)),this, SLOT(setPosition(int)));
    //connect(&mediaPlayer,SIGNAL(changeRate(qreal)), this, SLOT(setPlaybackRate(qreal)));
    //errorLabel = new QLabel;
    //errorLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
/*
    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(ui->openButton);
    controlLayout->addWidget(ui->playButton);
    controlLayout->addWidget(ui->positionSlider);

    QBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(videoWidget);
    layout->addLayout(controlLayout);
    //layout->addWidget(errorLabel);

    setLayout(layout);
*/
    QGridLayout *grid = new QGridLayout(ui->videoWidget);
    grid->setSpacing(20);
    grid->addWidget(videoWidget);
    grid->addWidget(ui->positionSlider);
    //grid->addWidget(ui->rateBox);
    //grid->addWidget(ui->playButton);

    //HEAT MAPS
    LFootMask.load("C:/Users/Meghan/Documents/Queens_14-15/Fall_Semester/ELEC497/ELEC497_UI/leftFootMask.png"); // location of foot mask
    RFootMask.load("C:/Users/Meghan/Documents/Queens_14-15/Fall_Semester/ELEC497/ELEC497_UI/rightFootMask.png");
    Lscene = new QGraphicsScene(); //create empty scene
    Rscene = new QGraphicsScene();

    vec = new vector<DataPoint>;
    vec2 = new vector<DataPoint>;

    m.genMap(*vec); // left foot heat map
    m2.genMap(*vec2); // right foot heat map

    Lscene->setSceneRect(m.rect()); //set the scene's view rectangle to the image's
    pix = QPixmap::fromImage(m); //create a pixmap from the image
    pix = pix.scaled(ui->leftRender->size());
    pixItem = Lscene->addPixmap(pix); //add the pixmap to the scene
    ui->leftRender->setSceneRect(pix.rect()); //set the renderviews view rectangle
    ui->leftRender->setScene(Lscene); //set the renderViews scene

    Rscene->setSceneRect(m2.rect());
    pix2 = QPixmap::fromImage(m2);
    pix2 = pix2.scaled(ui->rightRender->size());
    pixItem2 = Rscene->addPixmap(pix2);
    ui->rightRender->setSceneRect(pix2.rect());
    ui->rightRender->setScene(Rscene);
    //HEAT MAPS

    mediaPlayer.setVideoOutput(videoWidget);
    //connect(&mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)),
            //this, SLOT(mediaStateChanged(QMediaPlayer::State)));
    connect(&mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(&mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    //connect(&mediaPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(handleError()));
}

void PlaybackMode::openFile()
{
    //errorLabel->setText("");

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath());
    ui->vidPath->setText(fileName);
    vidPathText = fileName;
    mediaPlayer.setMedia(QUrl::fromLocalFile(fileName)); // load media to mediaPlayer

    if (!fileName.isEmpty()) {
        mediaPlayer.setMedia(QUrl::fromLocalFile(fileName));
        ui->playButton->setEnabled(true);
    }
}


void PlaybackMode::on_vidStop_clicked()
{
    mediaPlayer.stop();
}

void PlaybackMode::on_pauseButton_clicked()
{
    mediaPlayer.pause();

}
/*
void PlaybackMode::on_rewindButton_clicked()
{
    //mediaPlayer.playbackRate(1.0);
}

void PlaybackMode::mediaStateChanged(QMediaPlayer::State state)
{
    mediaPlayer.play();
    switch(state) {
    case QMediaPlayer::PlayingState:
        ui->playButton1->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        ui->playButton1->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

*/
void PlaybackMode::positionChanged(qint64 position)
{
    ui->positionSlider->setValue(position);
}

void PlaybackMode::durationChanged(qint64 duration)
{
    ui->positionSlider->setRange(0, duration);
}

void PlaybackMode::setPosition(int position)
{
    mediaPlayer.setPosition(position);
}

/*
void PlaybackMode::handleError()
{
    playButton->setEnabled(false);
    errorLabel->setText("Error: " + mediaPlayer.errorString());
}*/

void PlaybackMode::on_playButton_clicked()
{
   //mediaPlayer.play();

    switch(mediaPlayer.state()) {
    case QMediaPlayer::PlayingState:
        mediaPlayer.pause();

        break;
    default:
        mediaPlayer.play();
        break;
    }
}
/*
qreal PlaybackMode::playbackRate() const
{
    return ui->rateBox->itemData(ui->rateBox->currentIndex()).toDouble();
}

void PlaybackMode::setPlaybackRate(float rate)
{
    for (int i = 0; i < ui->rateBox->count(); ++i) {
        if (qFuzzyCompare(rate, float(ui->rateBox->itemData(i).toDouble()))) {
            ui->rateBox->setCurrentIndex(i);
            return;
        }
    }

    ui->rateBox->addItem(QString("%1x").arg(rate), QVariant(rate));
    ui->rateBox->setCurrentIndex(ui->rateBox->count() - 1);
}

void PlaybackMode::updateRate()
{
    emit changeRate(playbackRate());
}




void PlaybackMode::on_rateBox_activated(int index)
{
    on_rateBox_currentIndexChanged(playbackRate(index));
}

void PlaybackMode::on_rateBox_currentIndexChanged(int index)
{
    on_rateBox_currentIndexChanged(playbackRate(index));
}
*/

PlaybackMode::~PlaybackMode()
{
    delete ui;
}

void PlaybackMode::on_bookmarkButton_clicked()
{

}

void Player::durationChanged(qint64 duration)
{
    this->duration = duration/1000;
    slider->setMaximum(duration / 1000);
}

void Player::positionChanged(qint64 progress)
{
    if (!slider->isSliderDown()) {
        slider->setValue(progress / 1000);
    }
    updateDurationInfo(progress / 1000);
}
