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

void Robot::set_low_color(vector<int> low_color)
{
    this->low_color = low_color;
}

void Robot::set_upper_color(vector<int> upper_color)
{
    this->upper_color = upper_color;
}

vector<int> Robot::get_low_color(){
    return low_color;
}

vector<int> Robot::get_upper_color(){
    return upper_color;
}

string Robot::get_nick()
{
    return nick;
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

