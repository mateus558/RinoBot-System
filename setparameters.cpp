#include "setparameters.h"
#include "ui_setparameters.h"
#include <iostream>
#include <fstream>

using namespace std;

SetParameters::SetParameters(QWidget *parent) : QMainWindow(parent),    ui(new Ui::SetParameters)
{
    eye = new Vision;
    conf = new ConfigRobots;
    set_team_color = new SetColorRange;

    ui->setupUi(this);
    connect(ui->configRobots, SIGNAL(clicked(bool)), this, SLOT(on_configRobots_clicked()));
    connect(eye, SIGNAL(processedImage(QImage)), this, SLOT(updateVisionUI(QImage)));
    connect(eye, SIGNAL(framesPerSecond(double)), this, SLOT(updateFPS(double)));
}

SetParameters::~SetParameters()
{
    delete eye;
    delete ui;
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
    if(eye == NULL){
        eye = new Vision;
    }

    if(!eye->open_camera()){
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
    conf->show();
}

void SetParameters::on_readParameters_clicked()
{
    vector<Robot> robots = eye->get_robots();
    vector<int> low_color(3);
    vector<int> upper_color(3);
    vector<int> low_team_color(3);
    vector<int> upper_team_color(3);
    int ch;
    string path, role, ID;
    ifstream file, t1_file, t2_file;

    t1_file.open("Config/T1", fstream::in);

    if(!t1_file){
        cout << "Team 1 config could not be opened!" << endl;
    }

    t1_file >> low_team_color[0] >> low_team_color[1] >> low_team_color[2];
    t1_file >> upper_team_color[0] >> upper_team_color[1] >> upper_team_color[2];
    t1_file.close();
    t1_file.clear();

    for(auto itr = robots.begin(); itr != robots.end(); ++itr){
        path = "Config/" + (*itr).get_nick();
        file.open(path.c_str());

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
    cout << upper_team_color[0] << " " <<upper_team_color[1] << " " << upper_team_color[2] << endl;
    t2_file.close();
    t2_file.clear();

    for(auto itr = robots.begin() + 3; itr != robots.end(); ++itr){
        (*itr).set_team_low_color(low_team_color);
        (*itr).set_team_upper_color(upper_team_color);
    }

    eye->set_robots(robots);
}

void SetParameters::on_T1_color_clicked()
{
    eye->Stop();
    eye->release_cam();
    set_team_color->set_robot("T1");
    set_team_color->show();
}

void SetParameters::on_T2_color_clicked()
{
    eye->Stop();
    eye->release_cam();
    set_team_color->set_robot("T2");
    set_team_color->show();
}

void press(int event, int x, int y, int flags, void* userdata)
{
    vector<Point> *points = (vector<Point>*) userdata;

    if(event == EVENT_LBUTTONDOWN){
        points->push_back(Point(x, y));
    }
}

void SetParameters::on_mapPoints_clicked()
{
    vector<Point> mapPoints;
    VideoCapture cam;
    Mat frame;
    fstream write_points;
    int n = 0, camid;

    camid = eye->get_camID();
    eye->Stop();
    eye->release_cam();

    if(!cam.isOpened()){
        cam.open(camid);
    }else cout << "Camera is already opened." << endl;

    if(!cam.isOpened()) cout << "Camera could not be opened." << endl;

    while(n != 18){
        if(!cam.read(frame)){
            cout << "Error getting frame!" << endl;
            break;
        }

        if(frame.empty()){
            cout << "Error reading the frame!" << endl;
            break;
        }

        namedWindow("Click on the map points", 1);
        setMouseCallback("Click on the map points", press, &mapPoints);

        n = mapPoints.size();
        for(Point p : mapPoints){
            cout << p.x << " " << p.y << endl;
            circle(frame, p, 2, Scalar(0, 0, 255), 5);
        }

        imshow("Click on the map points", frame);

        waitKey(15);
    }

    cam.release();

    write_points.open("Config/map", ofstream::out);

    for(Point p : mapPoints){
        write_points << p.x << " " << p.y << endl;
    }

    write_points.close();
}

void SetParameters::on_attackArrea_btn_clicked()
{
    vector<Point> attackPoints;
    VideoCapture cam;
    Mat frame;
    fstream write_points;
    int n = 0, camid;

    camid = eye->get_camID();
    eye->Stop();
    eye->release_cam();

    if(!cam.isOpened()){
        cam.open(camid);
    }else cout << "Camera is already opened." << endl;

    if(!cam.isOpened()) cout << "Camera could not be opened." << endl;

    while(n != 8){
        if(!cam.read(frame)){
            cout << "Error getting frame!" << endl;
            break;
        }

        if(frame.empty()){
            cout << "Error reading the frame!" << endl;
            break;
        }

        namedWindow("Click on the attack area points", 1);
        setMouseCallback("Click on the attack area points", press, &attackPoints);

        n = attackPoints.size();
        for(Point p : attackPoints){
            cout << p.x << " " << p.y << endl;
            circle(frame, p, 2, Scalar(0, 0, 255), 5);
        }

        imshow("Click on the attack area points", frame);

        waitKey(15);
    }

    cam.release();

    write_points.open("Config/attack_area", ofstream::out);

    for(Point p : attackPoints){
        write_points << p.x << " " << p.y << endl;
    }

    write_points.close();
}

void SetParameters::on_defenseArrea_btn_clicked()
{
    vector<Point> defensePoints;
    VideoCapture cam;
    Mat frame;
    fstream write_points;
    int n = 0, camid;

    camid = eye->get_camID();
    eye->Stop();
    eye->release_cam();

    if(!cam.isOpened()){
        cam.open(camid);
    }else cout << "Camera is already opened." << endl;

    if(!cam.isOpened()) cout << "Camera could not be opened." << endl;

    while(n != 8){
        if(!cam.read(frame)){
            cout << "Error getting frame!" << endl;
            break;
        }

        if(frame.empty()){
            cout << "Error reading the frame!" << endl;
            break;
        }

        namedWindow("Click on the defense area points", 1);
        setMouseCallback("Click on the defense area points", press, &defensePoints);

        n = defensePoints.size();
        for(Point p : defensePoints){
            cout << p.x << " " << p.y << endl;
            circle(frame, p, 2, Scalar(0, 0, 255), 5);
        }

        imshow("Click on the defense area points", frame);

        waitKey(15);
    }

    cam.release();

    write_points.open("Config/defense_area", ofstream::out);

    for(Point p : defensePoints){
        write_points << p.x << " " << p.y << endl;
    }

    write_points.close();
}
