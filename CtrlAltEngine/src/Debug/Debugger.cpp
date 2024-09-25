/**
@group CTRL ALT
@file Debugger.cpp
@brief Debugging information to be calculated here
Created by Jerron Teng
t.junrongjerron@digipen.edu
*/ 

#pragma once
#include "../Debug/Debugger.h"


namespace Debug {
    auto endFrameTime = std::chrono::high_resolution_clock::now(); //Tracker for FPS, init with value first so auto knows the type
    int framecount = 0; //Counter for FPS
    std::chrono::duration<double> elapsedDurationBetweenFrames;

    void fpsUpdate(std::string *fps_string) {
        //Start of FPS Tracker
        //Get time of new frame start
        auto startFrameTime = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(8)); //Simulated workload, when rendering and stuff happens this can be removed
        framecount++;

        if ((startFrameTime - endFrameTime).count() > 0.01667f) // 1/60 
            elapsedDurationBetweenFrames += static_cast<std::chrono::duration<double>> (0.01667f);
        else
            elapsedDurationBetweenFrames += startFrameTime - endFrameTime;
        //Calculate time between frames if
        //Display difference
        if (framecount == 60) {
            auto fps = framecount / elapsedDurationBetweenFrames.count();
            //std::cout << "FPS: " << fps << std::endl;
            fps = std::ceil((fps * 100.0) / 100.0); //Round off the FPS
            *fps_string = std::to_string(fps);
            fps_string->erase(fps_string->find_last_not_of('0') + 1, std::string::npos);
            fps_string->erase(fps_string->find_last_not_of('.') + 1, std::string::npos);
            framecount = 0;                                                     //reset to 0
            elapsedDurationBetweenFrames = startFrameTime - startFrameTime;     //reset to 0
        }//End of FPS tracker, unsure if works correctly currently using simulated workload
        endFrameTime = startFrameTime;
    }
}