#ifndef VIDEO4LINUXCONFIG_H
#define VIDEO4LINUXCONFIG_H

#include <QWidget>
#include <vector>
#include "vision.h"
#include <QMessageBox>

namespace Ui {
class video4linuxConfig;
}

class video4linuxConfig : public QWidget
{
    Q_OBJECT

public:
    explicit video4linuxConfig(QWidget *parent = 0);
    void set_camid(int cam_id);
    std::pair<std::vector<std::string>, std::vector<int> > read_default_calib();
    ~video4linuxConfig();

public slots:
    void updateVisionUI(QImage);

private slots:
    void showEvent(QShowEvent *event);

    void closeEvent(QCloseEvent *event);

    void on_bright_slider_sliderMoved(int position);

    void on_contrast_slider_sliderMoved(int position);

    void on_saturation_slider_sliderMoved(int position);

    void on_white_bal_slider_sliderMoved(int position);

    void on_sharpness_slider_sliderMoved(int position);

    void on_exposure_slider_sliderMoved(int position);

    void on_focus_slider_sliderMoved(int position);

    void on_pushButton_2_clicked();

    void on_setToDefault_clicked();

    void on_gain_slider_sliderMoved(int position);

    void on_Init_Capture_btn_clicked();

private:
    Ui::video4linuxConfig *ui;
    Vision *eye;
    int cam_id;
};

#endif // VIDEO4LINUXCONFIG_H
