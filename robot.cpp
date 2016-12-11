#include "robot.h"

Robot::Robot(){
    channel = -1;
    centroid = Point(-1, -1);
    team_cent = Point(-1, -1);
    color_cent = Point(-1, -1);
    nick = "NULL";
    role = "NULL";
    ID = "NULL";
    low_color_team.assign(3, 0);
    upper_color_team.assign(3, 255);
    low_color.assign(3, 0);
    upper_color.assign(3, 255);
}

void Robot::set_angle(double angle)
{
    this->angle = angle;
}

double Robot::get_angle()
{
    return this->angle;
}

void Robot::set_centroid(Point p)
{
    this->centroid = p;
}

Point Robot::get_centroid()
{
    return this->centroid;
}

void Robot::set_color_cent(Point p)
{
    this->color_cent = p;
}

Point Robot::get_color_cent()
{
    return this->color_cent;
}

void Robot::set_team_cent(Point p)
{
    this->team_cent = p;
}

Point Robot::get_team_cent()
{
    return this->team_cent;
}

void Robot::set_channel(int channel)
{
    this->channel = channel;
}

void Robot::set_role(string role)
{
    this->role = role;
}

void Robot::set_nick(string nick)
{
    this->nick = nick;
}

void Robot::set_ID(string ID)
{
    this->ID = ID;
}

void Robot::set_team_low_color(vector<int> low_color){
    this->low_color_team = low_color;
}

void Robot::set_team_upper_color(vector<int> upper_color){
    this->upper_color_team = upper_color;
}

vector<int> Robot::get_team_low_color(){
    return this->low_color_team;
}

vector<int> Robot::get_team_upper_color(){
    return this->upper_color_team;
}

void Robot::set_low_color(vector<int> low_color)
{
    this->low_color = low_color;
}

void Robot::set_upper_color(vector<int> upper_color)
{
    this->upper_color = upper_color;
}

vector<int> Robot::get_low_color()
{
    return this->low_color;
}

vector<int> Robot::get_upper_color()
{
    return this->upper_color;
}

string Robot::get_nick()
{
    return this->nick;
}

string Robot::get_role()
{
    return this->role;
}

string Robot::get_ID()
{
    return this->ID;
}

