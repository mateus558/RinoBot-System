#include "robot.h"

void Robot::set_centroid(Point p)
{
    this->centroid = p;
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

Point Robot::get_centroid()
{
    return this->centroid;
}

string Robot::get_role()
{
    return this->role;
}

string Robot::get_ID()
{
    return this->ID;
}

