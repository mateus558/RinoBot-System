#include "soccer_window.h"
#include "ui_soccer_window.h"

soccer_window::soccer_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::soccer_window)
{
    ui->setupUi(this);
}

soccer_window::~soccer_window()
{
    delete ui;
}
