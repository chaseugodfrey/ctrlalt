///**
//@group CTRL ALT
//@file Debugger.cpp
//@brief Debugging information to be calculated here
//Created by Jerron Teng
//t.junrongjerron@digipen.edu
//*/ 
//
//#pragma once
//#include "../Debug/Debugger.h"
//
//
//namespace Debug {
//    auto endFrameTime = std::chrono::high_resolution_clock::now(); //Tracker for FPS, init with value first so auto knows the type
//    int framecount = 0; //Counter for FPS
//    std::chrono::duration<double> elapsedDurationBetweenFrames{ 0 };
//
//    void fpsUpdate(std::string *fps_string) {
//        //Start of FPS Tracker
//        //Get time of new frame start
//        auto startFrameTime = std::chrono::high_resolution_clock::now();
//        std::this_thread::sleep_for(std::chrono::milliseconds(8)); //Simulated workload, when rendering and stuff happens this can be removed
//        framecount++;
//
//        if ((startFrameTime - endFrameTime).count() > 0.01667f) // 1/60 
//            elapsedDurationBetweenFrames += static_cast<std::chrono::duration<double>> (0.01667f);
//        else
//            elapsedDurationBetweenFrames += startFrameTime - endFrameTime;
//        //Calculate time between frames if
//        //Display difference
//        if (framecount == 60) {
//            auto fps = framecount / elapsedDurationBetweenFrames.count();
//            //std::cout << "FPS: " << fps << std::endl;
//            fps = std::ceil((fps * 100.0) / 100.0); //Round off the FPS
//            *fps_string = std::to_string(fps);
//            fps_string->erase(fps_string->find_last_not_of('0') + 1, std::string::npos);
//            fps_string->erase(fps_string->find_last_not_of('.') + 1, std::string::npos);
//            framecount = 0;                                                     //reset to 0
//            //elapsedDurationBetweenFrames = startFrameTime - startFrameTime;     //reset to 0
//            elapsedDurationBetweenFrames = std::chrono::duration<double>(0);
//        }//End of FPS tracker, unsure if works correctly currently using simulated workload
//        endFrameTime = startFrameTime;
//    }
//}

#include "../Debug/Debugger.h"

namespace Debug {
    // Definition of deltaTime
    double deltaTime = 0.0;

    // Class encapsulating FPS calculation logic
    class FrameTimer {
    public:
        FrameTimer() : frameCount(0), elapsedDuration(0.0) {
            endFrameTime = std::chrono::high_resolution_clock::now();
        }

        void update(std::string* fps_string) {
            // Get the current time
            auto startFrameTime = std::chrono::high_resolution_clock::now();
            std::this_thread::sleep_for(std::chrono::milliseconds(8));  // Simulated workload (can be removed)

            // Calculate deltaTime (in seconds)
            deltaTime = std::chrono::duration<double>(startFrameTime - endFrameTime).count();

            // FPS limiting to LOW_LIMIT (60 FPS) and HIGH_LIMIT (10 FPS)
            if (deltaTime < LOW_LIMIT) {
                deltaTime = LOW_LIMIT;  // Cap at 60 FPS
            }
            else if (deltaTime > HIGH_LIMIT) {
                deltaTime = HIGH_LIMIT; // Prevent FPS from dropping too low
            }

            // Accumulate elapsed time
            elapsedDuration += deltaTime;
            frameCount++;

            // Once 60 frames have been counted, calculate FPS
            if (frameCount == 60) {
                double fps = frameCount / elapsedDuration;  // FPS = Frames / Time

                // Round FPS to two decimal places
                fps = std::round(fps * 100.0) / 100.0;

                // Convert FPS to string and format it
                *fps_string = std::to_string(fps);
                fps_string->erase(fps_string->find_last_not_of('0') + 1, std::string::npos);
                fps_string->erase(fps_string->find_last_not_of('.') + 1, std::string::npos);

                // Reset for the next batch of 60 frames
                frameCount = 0;
                elapsedDuration = 0.0;
            }

            // Update endFrameTime for the next frame
            endFrameTime = startFrameTime;
        }

    private:
        int frameCount;  // Number of frames counted
        double elapsedDuration;  // Accumulated time between frames
        std::chrono::time_point<std::chrono::high_resolution_clock> endFrameTime;  // End time of the last frame
    };

    // Instantiate a FrameTimer object to manage FPS
    static FrameTimer frameTimer;

    // Wrapper function to update FPS and deltaTime
    void fpsUpdate(std::string* fps_string) {
        frameTimer.update(fps_string);
    }
}
