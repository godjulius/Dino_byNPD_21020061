#ifndef TIMER_H
#define TIMER_H

#include "CommonFunc.h"

class Timer {

private:

    double startTick;
    double pauseTick;
    bool isPaused;
    bool isStarted;
public:

    Timer();

    ~Timer() { ; };

    void start();

    double getTick();

};

#endif