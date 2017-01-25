#include <iostream>
#include "cph.h"

using namespace std;


CPH::CPH(){

}

void CPH::run(){

}

bool CPH::isStopped() const
{
    return this->stop;
}

void CPH::Play(){
    if(!isRunning()){
        if(isStopped())
            stop = false;
        start(LowPriority);
    }
}

void CPH::Stop(){

}

void CPH::msleep(int ms){
    struct timespec ts = {ms / 1000, (ms % 1000) * 1000 * 1000};
    nanosleep(&ts, NULL);
}
