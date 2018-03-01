#include "informationwindow.h"
#include "ui_informationwindow.h"

InformationWindow::InformationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationWindow)
{
    ui->setupUi(this);
    //pegando as imagens e passando para os labels, para adicionar as fotinhas
    QPixmap gandalf("/home/bruno/Downloads/gandalf.jpg");
    QPixmap leona("/home/bruno/Downloads/leona.jpg");
    QPixmap presto("/home/bruno/Downloads/presto.jpg");
    ui->imgGandalflbl->setPixmap(gandalf);
    ui->imgGandalflbl->setScaledContents(true);
    ui->imgLeonalbl->setPixmap(leona);
    ui->imgLeonalbl->setScaledContents(true);
    ui->imgPrestolbl->setPixmap(presto);
    ui->imgPrestolbl->setScaledContents(true);

    ui->imgGandalflbl_2->setPixmap(gandalf);
    ui->imgGandalflbl_2->setScaledContents(true);
    ui->imgLeonalbl_2->setPixmap(leona);
    ui->imgLeonalbl_2->setScaledContents(true);
    ui->imgPrestolbl_2->setPixmap(presto);
    ui->imgPrestolbl_2->setScaledContents(true);

    updateData();
}

InformationWindow::~InformationWindow()
{
    delete ui;
}

void InformationWindow::closeEvent(QCloseEvent *event){
    emit close();
}

void InformationWindow::on_valueFilterchangebtn_clicked()
{
    if(ui->filterspb->value() <= 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Invalid");
        msgBox.exec();
    }
    else
    {
        ui->frequencyFilterlbl->setText("Frequency: " + QString::number(ui->filterspb->value()));
    }
}

void InformationWindow::on_startFilterbtn_clicked()
{
//    vector<int> flagChop = data.eye->get_();
//    if(flagChop == 0) //se a flag estiver falsa (off), vira true (on)
//    {
//        eye->set_LPF_flag(1);
//        ui->startFilterbtn->setStyleSheet("background-color: green");
//        ui->startFilterbtn->setText("On");
//        ui->frequencyFilterlbl->setVisible(true);
//        ui->filterspb->setVisible(true);
//        ui->valueFilterchangebtn->setVisible(true);
//    }else{
//        eye->set_LPF_flag(0);
//        ui->startFilterbtn->setText("Off");
//        ui->startFilterbtn->setStyleSheet("background-color: red");
//        ui->frequencyFilterlbl->setVisible(false);
//        ui->filterspb->setVisible(false);
//        ui->valueFilterchangebtn->setVisible(false);
//    }

}

void InformationWindow::on_velocityMaxGandalfbtn_clicked()
{
    if(ui->velocityMaxGandalfspb->value() <= 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Invalid");
        msgBox.exec();
    }
    else
    {
        ui->velocityMaxGandalflbl->setText("Speed Máx: " + QString::number(ui->velocityMaxGandalfspb->value()));
    }
}

void InformationWindow::on_velocityMaxLeonabtn_clicked()
{
    if(ui->velocityMaxLeonaspb->value() <= 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Invalid");
        msgBox.exec();
    }
    else
    {
        ui->velocityMaxLeonalbl->setText("Speed Máx: " + QString::number(ui->velocityMaxLeonaspb->value()));
    }

}

void InformationWindow::on_velocityMaxPrestobtn_clicked()
{
    if(ui->velocityMaxPrestospb->value() <= 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Invalid");
        msgBox.exec();
    }
    else
    {
        ui->velocityMaxPrestolbl->setText("Speed Máx: " + QString::number(ui->velocityMaxPrestospb->value()));
    }

}

void InformationWindow::on_pidbtn_clicked()
{
    if(ui->pidspb->value() <= 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Invalid");
        msgBox.exec();
    }
    else
    {
        ui->pidlbl->setText("PID: " + QString::number(ui->pidspb->value()));
    }

}

void InformationWindow::on_strategybtn_clicked()
{
    /*    string strategy = ui->strategy_options->currentText().toUtf8().constData();

        cout << strategy << endl;

        char num_strategy;

        if(strategy == "Test")
            num_strategy = 0;
        else if (strategy == "Strategy 1")
            num_strategy = 1;
        else if (strategy == "Strategy 2")
            num_strategy = 2;

        fuzzy->set_strategy(num_strategy);
    */
        switch(ui->strategycbx->currentIndex())
        {
        case 0:
            ui->currentStrategylbl->setText("Current: 2");
            break;
        case 1:
            ui->currentStrategylbl->setText("Current: 1");
            break;
        case 2:
            ui->currentStrategylbl->setText("Current: Text");
            break;
        }

}

void InformationWindow::updateData(InfoParameters data){
    this->data = data;
    updateData();
}

void InformationWindow::updateData(){
    //informações das variaveis, receberam os gets para depois manipular as variaveis e exibir as informações
    QString channel, velocity, velocityMax, posicao;

    //manipulating gandalf
    channel = "Canal: " +  QString::number(data.robots[GANDALF].channel);
    ui->channelGandalflbl->setText(channel);
    velocity = "Speed: (" +  QString::number(data.robots[GANDALF].vel_strategy.first) + " , " + QString::number(data.robots[GANDALF].vel_strategy.second) + ")";
    ui->velocityGandalflbl->setText(velocity);
    velocityMax =  "Speed Máx: " + QString::number(data.robots[GANDALF].vel_max);
    ui->velocityMaxGandalflbl->setText(velocityMax);

    //manipulating leona
    channel = "Canal: " +  QString::number(data.robots[LEONA].channel);
    ui->channelLeonalbl->setText(channel);
    velocity = "Speed: (" +  QString::number(data.robots[LEONA].vel_strategy.first) + " , " + QString::number(data.robots[LEONA].vel_strategy.second) + ")";
    ui->velocityLeonalbl->setText(velocity);
    velocityMax =  "Speed Máx: " + QString::number(data.robots[LEONA].vel_max);
    ui->velocityMaxLeonalbl->setText(velocityMax);

    //manipulating presto
    channel = "Canal: " +  QString::number(data.robots[PRESTO].channel);
    ui->channelPrestolbl->setText(channel);
    velocity = "Speed: (" +  QString::number(data.robots[PRESTO].vel_strategy.first) + " , " + QString::number(data.robots[PRESTO].vel_strategy.second) + ")";
    ui->velocityPrestolbl->setText(velocity);
    velocityMax =  "Speed Máx: " + QString::number(data.robots[PRESTO].vel_max);
    ui->velocityMaxPrestolbl->setText(velocityMax);

    //manipulating gandalf
    posicao = "Posição: (" +  QString::number(data.robots[GANDALF].x) + " , " + QString::number(data.robots[GANDALF].y) + ")";
    ui->positionGandalflbl->setText(posicao);
    velocity = "Speed: (" +  QString::number(data.robots[GANDALF].vel_vision.first) + " , " + QString::number(data.robots[GANDALF].vel_vision.second) + ")";
    ui->velocityGandalflbl_2->setText(velocity);

    //manipulating leona
    posicao = "Posição: (" +  QString::number(data.robots[LEONA].x) + " , " + QString::number(data.robots[LEONA].y) + ")";
    ui->positionLeonalbl->setText(posicao);
    velocity = "Speed: (" +  QString::number(data.robots[LEONA].vel_vision.first) + " , " + QString::number(data.robots[LEONA].vel_vision.second) + ")";
    ui->velocityLeonalbl_2->setText(velocity);

    //manipulating presto
    posicao = "Posição: (" +  QString::number(data.robots[PRESTO].x) + " , " + QString::number(data.robots[PRESTO].y) + ")";
    ui->positionPrestolbl->setText(posicao);
    velocity = "Speed: (" +  QString::number(data.robots[PRESTO].vel_vision.first) + " , " + QString::number(data.robots[PRESTO].vel_vision.second) + ")";
    ui->velocityPrestolbl_2->setText(velocity);

    //manipulating ball
    posicao = "Posição: (" +  QString::number(data.ball.x) + " , " + QString::number(data.ball.y) + ")";
    ui->positionBalllbl->setText(posicao);
    velocity = "Speed: (" +  QString::number(data.ball.vel_vision.first) + " , " + QString::number(data.ball.vel_vision.second) + ")";
    ui->velocityBalllbl->setText(velocity);
}
