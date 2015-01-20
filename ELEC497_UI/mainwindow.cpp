#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playbackmode.h"
#include "ui_playbackmode.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectCollectData_clicked()
{

}

void MainWindow::on_selectPlaybackMode_clicked()
{
    PlaybackMode w;
    w.showFullScreen();
}
