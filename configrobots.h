#ifndef CONFIGROBOTS_H
#define CONFIGROBOTS_H

#include <QWidget>
#include <setcolorrange.h>

namespace Ui {
class ConfigRobots;
}

class ConfigRobots : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigRobots(QWidget *parent = 0);
    void set_camid(int cam_id);
    void set_vision(Vision *eye, int cam_id = 0);
    ~ConfigRobots();

private slots:
    void on_configColorRange_clicked();

    void on_save_clicked();

private:
    int cam_id;
    Vision *eye;
    Ui::ConfigRobots *ui;
    SetColorRange *set_color;
};

#endif // CONFIGROBOTS_H
