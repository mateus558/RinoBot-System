#ifndef SETCOLORRANGE_H
#define SETCOLORRANGE_H

#include <QWidget>
#include <QMessageBox>
#include <QCloseEvent>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vision.h>

namespace Ui {
class SetColorRange;
}

class SetColorRange : public QWidget
{
    Q_OBJECT

public:
    explicit SetColorRange(QWidget *parent = 0);
    void set_vision(Vision *eye, int cam_id = 0);
    void set_camid(int cam_id);
    void set_robot(string robot);
    ~SetColorRange();

public slots:
    void updateVisionUI(QImage);

private slots:
    void on_horizontalSlider_sliderMoved(int position);
    void on_horizontalSlider_2_sliderMoved(int position);
    void on_horizontalSlider_3_sliderMoved(int position);
    void on_horizontalSlider_4_sliderMoved(int position);
    void on_horizontalSlider_5_sliderMoved(int position);
    void on_horizontalSlider_6_sliderMoved(int position);
    void closeEvent(QCloseEvent *event);
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    string robot;
    Vision *eye;
    int cam_id;
    Ui::SetColorRange *ui;
};

#endif // SETCOLORRANGE_H
