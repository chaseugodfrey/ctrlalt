///**
//@group CTRL ALT
//@file Debugger.h
//@brief Debugging information to be calculated here
//Created by Jerron Teng
//t.junrongjerron@digipen.edu
//*/ 
//
//#pragma once 
//#ifndef DEBUGGER_H
//#define DEBUGGER_H
//#include "thread" //Simulated workload for FPS
//#include <iostream>
//#include <string>
//#include <cmath> //Find approximate
//
//
//namespace Debug {
//
//        void fpsUpdate(std::string *fps_string);
//}
//#endif
#pragma once
#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <thread>
#include <iostream>
#include <string>
#include <cmath>  // For rounding FPS
#include <chrono> // For time handling

#define LOW_LIMIT 0.01667  // 60 FPS (1/60)
#define HIGH_LIMIT 0.1     // 10 FPS (1/10)

namespace Debug {
    extern double deltaTime;

    void fpsUpdate(std::string* fps_string);
}

#endif
