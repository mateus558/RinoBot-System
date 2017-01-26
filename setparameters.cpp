#include <iostream>
#include <utility>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "setparameters.h"
#include "ui_setparameters.h"
#include "settingsdialog.h"

using namespace std;

SetParameters::SetParameters(QWidget *parent) : QMainWindow(parent),    ui(new Ui::SetParameters)
{
    eye = new Vision;
    conf = new ConfigRobots;
    set_team_color = new SetColorRange;
    serial_settings_dialog = new SettingsDialog;

    eye->set_mode(0);
    ui->setupUi(this);
    eye->set_camid(ui->spinBox->value());
    connect(ui->configRobots, SIGNAL(clicked(bool)), this, SLOT(on_configRobots_clicked()));
    connect(serial_settings_dialog, SIGNAL(serial_settings(SettingsDialog::Settings)), this, SLOT(updateSerialSettings(SettingsDialog::Settings)));
    connect(eye, SIGNAL(processedImage(QImage)), this, SLOT(updateVisionUI(QImage)));
    connect(eye, SIGNAL(framesPerSecond(double)), this, SLOT(updateFPS(double)));
}

SetParameters::~SetParameters()
{
    delete eye;
    delete ui;
}

void SetParameters::updateSerialSettings(SettingsDialog::Settings settings){
    this->serial_settings = settings;
}

void SetParameters::updateVisionUI(QImage img)
{
    if(!img.isNull()){
        ui->camera_video->setAlignment(Qt::AlignCenter);
        ui->camera_video->setPixmap(QPixmap::fromImage(img).scaled(ui->camera_video->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void SetParameters::updateFPS(double val)
{
    ui->fps_number->display(val);
}

void SetParameters::on_initCapture_clicked()
{
    int cam_id = ui->spinBox->value();

    if(eye == NULL){
        eye = new Vision;
    }

    if(!eye->open_camera(cam_id)){
        QMessageBox msgBox;
        msgBox.setText("The camera could not be opened!");
        msgBox.exec();
    }
    eye->Play();
}

void SetParameters::on_configRobots_clicked()
{
    eye->Stop();
    eye->release_cam();
    conf->set_camid(eye->get_camID());
    conf->show();
}

void SetParameters::on_readParameters_clicked()
{
    int ch;
    char cwd[1024];
    vector<Robot> robots = eye->get_robots();
    vector<int> low_color(3);
    vector<int> upper_color(3);
    vector<int> low_team_color(3);
    vector<int> upper_team_color(3);
    pair<vector<int>, vector<int> > ball_range;
    string path, role, ID;
    ifstream file, t1_file, t2_file, ball;

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        fprintf(stdout, "Current working dir: %s\n", cwd);
    else
        perror("getcwd() error");

    ball_range.first.resize(3);
    ball_range.second.resize(3);

    t1_file.open("Config/T1", fstream::in);

    if(!t1_file){
        cout << "Team 1 config could not be opened!" << endl;
    }

    t1_file >> low_team_color[0] >> low_team_color[1] >> low_team_color[2];
    t1_file >> upper_team_color[0] >> upper_team_color[1] >> upper_team_color[2];
    cout << low_team_color[0] << " " << upper_team_color[0] << endl;
    t1_file.close();
    t1_file.clear();

    for(auto itr = robots.begin(); itr != robots.end(); ++itr){
        path = "Config/" + (*itr).get_nick();
        file.open(path.c_str());

        if(!file){
            cout << (*itr).get_nick() << " config could not be opened!" << endl;
        }

        file >> low_color[0] >> low_color[1] >> low_color[2];
        file >> upper_color[0] >> upper_color[1] >> upper_color[2];
        file >> ch;
        file >> role;
        file >> ID;

        (*itr).set_team_low_color(low_team_color);
        (*itr).set_team_upper_color(upper_team_color);
        (*itr).set_low_color(low_color);
        (*itr).set_upper_color(upper_color);
        (*itr).set_ID(ID);
        (*itr).set_channel(ch);
        (*itr).set_role(role);

        file.close();
        file.clear();
    }

    t2_file.open("Config/T2", fstream::in);

    if(!t2_file){
        cout << "Team 2 config could not be opened!" << endl;
    }

    t2_file >> low_team_color[0] >> low_team_color[1] >> low_team_color[2];
    t2_file >> upper_team_color[0] >> upper_team_color[1] >> upper_team_color[2];
    cout << low_team_color[0] << " " << upper_team_color[0] << endl;
    t2_file.close();
    t2_file.clear();

    for(auto itr = robots.begin() + 3; itr != robots.end(); ++itr){
        (*itr).set_team_low_color(low_team_color);
        (*itr).set_team_upper_color(upper_team_color);
    }

    eye->set_robots(robots);

    ball.open("Config/ball", fstream::in);

    if(!ball){
        cout << "Ball config could not be opened!" << endl;
    }

    ball >> ball_range.first[0] >> ball_range.first[1] >> ball_range.first[2];
    ball >> ball_range.second[0] >> ball_range.second[1] >> ball_range.second[2];
    ball.close();
    ball.clear();

    eye->set_ball(ball_range);
}

void SetParameters::on_T1_color_clicked()
{
    eye->Stop();
    eye->release_cam();
    set_team_color->set_robot("T1");
    set_team_color->set_camid(eye->get_camID());
    set_team_color->show();
}

void SetParameters::on_T2_color_clicked()
{
    eye->Stop();
    eye->release_cam();
    set_team_color->set_robot("T2");
    set_team_color->set_camid(eye->get_camID());
    set_team_color->show();
}

void SetParameters::on_ball_color_clicked()
{
    int cam = eye->get_camID();

    eye->Stop();
    eye->release_cam();
    set_team_color->set_robot("ball");
    set_team_color->set_camid(cam);
    set_team_color->show();
}

void SetParameters::on_mapPoints_clicked()
{
    set_points("map", "map", 18);
}

void SetParameters::on_attackArrea_btn_clicked()
{
    set_points("attack_area", "attack", 8);
}

void SetParameters::on_defenseArrea_btn_clicked()
{
    set_points("defense_area", "defense", 8);
}

void press(int event, int x, int y, int flags, void* userdata)
{
    vector<Point> *args = (vector<Point>*) userdata;

    if(event == EVENT_LBUTTONDOWN){
        for(int i = 0; i < int(args->size()); ++i)
            if(args->at(i).x == x && args->at(i).y == y)
                return;
        args->push_back(Point(x, y));
    }else if(event == EVENT_RBUTTONDOWN){
        if(!args->empty())
            args->pop_back();
    }
}

void SetParameters::set_points(string fname, string area, int n_points)
{
    vector<Point> defensePoints;
    VideoCapture cam;
    Mat frame;
    fstream write_points;
    string wname = "Click on the " + area + " area points";
    bool exit = false;
    int n = 0, camid, key;

    camid = eye->get_camID();
    eye->Stop();
    eye->release_cam();

    if(!cam.isOpened()){
        cam.open(camid);
    }else cout << "Camera is already opened." << endl;

    if(!cam.isOpened()) cout << "Camera could not be opened." << endl;

    while(n != n_points && !exit){
        if(!cam.read(frame)){
            cout << "Error getting frame!" << endl;
            return;
        }

        if(frame.empty()){
            cout << "Error reading the frame!" << endl;
            return;
        }

        namedWindow(wname, 1);
        setMouseCallback(wname, press, &defensePoints);

        n = defensePoints.size();
        for(Point p : defensePoints){
            cout << p.x << " " << p.y << endl;
            circle(frame, p, 2, Scalar(0, 0, 255), 5);
        }

        imshow(wname, frame);

        key = waitKey(15);
        if(key == 1048603) exit = true;
    }

    destroyAllWindows();
    cam.release();

    if(!exit){
        string path = "Config/" + fname;
        write_points.open(path.c_str(), ofstream::out);

        for(Point p : defensePoints){
            write_points << p.x << " " << p.y << endl;
        }

        write_points.close();
     }
}

void SetParameters::on_config_serial_clicked()
{
    serial_settings_dialog->show();
}
