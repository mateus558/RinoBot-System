#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qRegisterMetaType<SettingsDialog::Settings>("SettingsDialog::Settings");

    setparam = new SetParameters;
    soccer = new soccer_window;

    ui->setupUi(this);
    QPixmap pix("Untitled1.png");
    ui->logo->setPixmap(pix);
    ui->strategy_choosen->addItem("Potential Fields");
    connect(ui->setParameters, SIGNAL(clicked(bool)), this, SLOT(openSetParameters()));
    connect(setparam, SIGNAL(serialSettings(SettingsDialog::Settings)), soccer, SLOT(receiveSerialSettings(SettingsDialog::Settings)), Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSetParameters()
{
    setparam->show();
}



void MainWindow::on_pushButton_5_clicked()
{
    soccer->show();
}
