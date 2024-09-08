#pragma once
#ifndef TIME_H
#define TIME_H

#include <chrono>

class Time {
    /// <summary>
	/// Time class that handles all time-related functions
    /// </summary>
    private:
        static std::chrono::steady_clock::time_point startTime;
        static float deltaTime;
        static float lastFrameTime;

    public:
        static void Init() {
            startTime = std::chrono::steady_clock::now();
            lastFrameTime = 0.0f;
        }

        static unsigned int CALT_GetTicks() {
            auto now = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
            return static_cast<unsigned int>(duration.count());
        }

        static float CALT_GetDeltaTime() {
            return deltaTime;
        }

        static void CALT_UpdateDeltaTime() {
            float currentFrameTime = CALT_GetTicks() / 1000.0f;
            deltaTime = currentFrameTime - lastFrameTime;
            lastFrameTime = currentFrameTime;
        }
};

std::chrono::steady_clock::time_point Time::startTime;
float Time::deltaTime = 0.f;
float Time::lastFrameTime = 0.f; 

#endif // !TIME_H