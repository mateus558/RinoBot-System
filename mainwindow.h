#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <setparameters.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void openSetParameters();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    SetParameters *setparam;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
