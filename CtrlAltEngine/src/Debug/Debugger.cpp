/**
@group CTRL ALT
@file Debugger.cpp
@brief Debugging information to be calculated here
Created by Jerron Teng
t.junrongjerron@digipen.edu
*/ 

#pragma once

// INCLUDES
// =========================================================================================================
#include "../Debug/Debugger.h"

namespace Debug {

    // Class encapsulating FPS calculation logic
    Debug::FrameTimer::FrameTimer() : frameCount(0), elapsedDuration(0.0), fps(0.0), deltaTime(0.0) {
        endFrameTime = std::chrono::high_resolution_clock::now();
    }

    Debug::FrameTimer::~FrameTimer() {

    }

    // this function gives access to deltaTime.
    double FrameTimer::Get_dt() {
        return this->deltaTime;
    }

    void Debug::FrameTimer::update() {
        // Get the current time
        auto startFrameTime = std::chrono::high_resolution_clock::now();
        //std::this_thread::sleep_for(std::chrono::milliseconds(8));  // Simulated workload (can be removed)

        // Calculate deltaTime (in seconds)
        deltaTime = std::chrono::duration<double>(startFrameTime - this->endFrameTime).count();

        // FPS limiting to LOW_LIMIT (60 FPS) and HIGH_LIMIT (10 FPS)
        if (deltaTime < LOW_LIMIT) {
            deltaTime = LOW_LIMIT;  // Cap at 60 FPS
        }
        else if (deltaTime > HIGH_LIMIT) {
            deltaTime = HIGH_LIMIT; // Prevent FPS from dropping too low
        }

        // Accumulate elapsed time
        this->elapsedDuration += deltaTime;
        this->frameCount++;

        // Once 60 frames have been counted, calculate FPS
        if (this->frameCount == 60) {
            this->fps = this->frameCount / elapsedDuration;  // FPS = Frames / Time

            // Round FPS to two decimal places
            this->fps = std::round(fps * 100.0) / 100.0;

            // Reset for the next batch of 60 frames
            this->frameCount = 0;
            this->elapsedDuration = 0.0;
        }

        // Update endFrameTime for the next frame
        this->endFrameTime = startFrameTime;
    }

    std::string Debug::FrameTimer::ReadFPS() {
        return std::to_string(this->fps);
    }

    int Debug::FrameTimer::GetFrameCount() {
        return frameCount;
    }
}
