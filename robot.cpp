#include "robot.h"

void Robot::set_centroid(Point p){
    this->centroid = p;
}

void Robot::set_channel(int channel){
    this->channel = channel;
}

void Robot::set_role(string role){
    this->role = role;
}

void Robot::set_nick(string nick){
    this->nick = nick;
}

Point Robot::get_centroid(){
    return this->centroid;
}

string Robot::get_role(){
    return this->role;
}

string Robot::get_ID(){
    return this->ID;
}

