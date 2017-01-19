#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <setparameters.h>
#include <soccer_window.h>

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

private slots:
    void on_pushButton_5_clicked();

private:
    SetParameters *setparam;
    soccer_window *soccer;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
