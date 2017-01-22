// alarm.h 
//	Data structures for a software alarm clock.
//
//	We make use of a hardware timer device, that generates
//	an interrupt every X time ticks (on real systems, X is
//	usually between 0.25 - 10 milliseconds).
//
//	From this, we provide the ability for a thread to be
//	woken up after a delay; we also provide time-slicing.
//
//	NOTE: this abstraction is not completely implemented.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef ALARM_H
#define ALARM_H

#include "copyright.h"
#include "utility.h"
#include "callback.h"
#include "timer.h"
#include <list>
#include "thread.h"

class PlaceForSleep {
public:
    PlaceForSleep():now_interrupt(0) {};
    void PutToPlace(int input_time, Thread *t);
    bool Calling();
    bool IsEmpty();
private:
    class Place {
    public:
        Place(int input_time, Thread* t):
        sleeper(t), WhenForWake(input_time) {};
        Thread* sleeper;
        int WhenForWake;
    };
    
    int now_interrupt;
    std::list<Place> _Places;
};

// The following class defines a software alarm clock.
class Alarm : public CallBackObj {
public:
    Alarm(bool doRandomYield);	// Initialize the timer, and callback
    // to "toCall" every time slice. (periodic calling)
    ~Alarm() { delete timer; }
    
    void WaitUntil(int input_time);	// stop execution until time > now + input time
    
private:
    Timer *timer;		// timer device
    PlaceForSleep _PlaceForSleep;
    void CallBack();		// called When the hardware
    // timer generates an interrupt
};

#endif // ALARM_H
