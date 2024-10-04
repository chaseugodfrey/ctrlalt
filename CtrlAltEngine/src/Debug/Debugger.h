/*!
\group  	CtrlAlt
\file		Debugger.h
\author 	Jerron Teng
\par    	t.junrongjerroni@digipen.edu
\date   	Sep 08, 2024
\brief      Provides debugging utilities, specifically frame timing information.

            This file contains the FrameTimer class, which calculates the frames per second (FPS) 
            for the system. The update() function should be called in the Update loop to 
            calculate and store FPS values.
*/
#pragma once
#ifndef DEBUGGER_H
#define DEBUGGER_H

// INCLUDES
// =========================================================================================================
#include <thread>
#include <iostream>
#include <string>
#include <cmath>  // For rounding FPS
#include <chrono> // For time handling

// DEFINITIONS
// =========================================================================================================
#define LOW_LIMIT 0.01667  // 60 FPS (1/60)
#define HIGH_LIMIT 0.1     // 10 FPS (1/10)

namespace Debug {
    //extern double deltaTime; // this does not work

    class FrameTimer
    {
    public:
        /*!
        @brief Constructor for FrameTimer class
        Special scenarios: -
        @param -
        @return -
        \*________________________________________________________________*/
        FrameTimer();

        /*!
        @brief Deconstructor for FrameTimer class, default destructor
        Special scenarios: -
        @param -
        @return -
        \*________________________________________________________________*/
        ~FrameTimer();

        /*!
        @brief Updates the frame timing information.
               This function calculates the time since the last frame and updates the FPS value.
               Should be called in every frame update of the engine.
        Special scenarios: -
        @param -
        @return -
        \*________________________________________________________________*/
        void update();

        /*!
        @brief Returns FPS as a std::string
        Special scenarios: -
        @param -
        @return std::string fps
        \*________________________________________________________________*/
        std::string ReadFPS();

        /*!
        @brief Returns frameCount value
               Value of FrameCount increments each update() loop, FPS is calculated
               and returned after every 60 frames
        Special scenarios: -
        @param -
        @return int frameCount
        \*________________________________________________________________*/
        int GetFrameCount();

        /*!
        @brief Returns deltaTime value
               (WIP, deltaTime not correctly implemented)
        Special scenarios: -
        @param -
        @return double deltaTime
        \*________________________________________________________________*/
        double Get_dt();

    private:
        int frameCount;             // Number of frames counted
        double elapsedDuration;     // Accumulated time between frames
        double fps;                 // Current system's Framerate
        double deltaTime;           // DeltaTime = fps/elapsedDuration
        std::chrono::time_point<std::chrono::high_resolution_clock> endFrameTime;  // End time of the last frame
    };
}

#endif
