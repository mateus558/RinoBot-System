#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :   QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QPixmap pix("Untitled1.png");
    ui->label_2->setPixmap(pix);
    ui->comboBox->addItem("Potential Fields");
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(openSetParameters()));
}

void MainWindow::openSetParameters(){
    setparam = new SetParameters;
    setparam->setAttribute( Qt::WA_DeleteOnClose );
    setparam->show();
}

MainWindow::~MainWindow(){
    delete ui;
}
