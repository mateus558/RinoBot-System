#include "setparameters.h"
#include "ui_setparameters.h"

SetParameters::SetParameters(QWidget *parent) : QMainWindow(parent),    ui(new Ui::SetParameters){
    eye = new Vision;
    conf = new ConfigRobots;
    ui->setupUi(this);

    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_2_clicked()));
    connect(eye, SIGNAL(processedImage(QImage)), this, SLOT(updateVisionUI(QImage)));
    connect(eye, SIGNAL(framesPerSecond(double)), this, SLOT(updateFPS(double)));
}

void SetParameters::updateVisionUI(QImage img){
    if(!img.isNull()){
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void SetParameters::updateFPS(double val){
    ui->lcdNumber->display(val);
}

void SetParameters::on_pushButton_clicked(){
    if(eye == NULL){
        eye = new Vision;
    }

    if(!eye->open_camera()){
        QMessageBox msgBox;
        msgBox.setText("The camera could not be opened!");
        msgBox.exec();
    }
    eye->Play();
}

void SetParameters::on_pushButton_2_clicked(){
    eye->Stop();
    eye->release_cam();
    conf->show();
}

SetParameters::~SetParameters(){
    delete eye;
    delete ui;
}



