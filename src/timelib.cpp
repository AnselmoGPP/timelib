#include "timelib.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

// ----- timerSet ---------------

timerSet::timerSet(int maximumFPS)
    : currentTime(std::chrono::system_clock::duration::zero()), maxFPS(maximumFPS)
{
    startTime();

    currentTimeSeconds = 0;
    deltaTime = 0;
    FPS = 0;
    frameCounter = 0;
}

void timerSet::startTime()
{
    timeZero = std::chrono::high_resolution_clock::now();
    lastTime = timeZero;
    std::this_thread::sleep_for(std::chrono::microseconds(1000));   // Avoids deltaTime == 0 (i.e. currentTime == lastTime)
}

void timerSet::computeDeltaTime()
{
    // Get deltaTime (adjust by FPS if flagged)
    currentTime = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count();

    if(maxFPS > 0)
    {
        int waitTime = 1000000/maxFPS - deltaTime;
        if(waitTime > 0)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(waitTime));
            currentTime = std::chrono::high_resolution_clock::now();
            deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count();
        }
    }

    lastTime = currentTime;

    // Get FPS
    FPS = std::round(1000000.f / deltaTime);

    // Get currentTimeSeconds
    currentTimeSeconds = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - timeZero).count() / 1000000.l;

    // Increment the frame count
    ++frameCounter;
}

void timerSet::printTimeData()
{
    std::cout << frameCounter << " | fps: " << FPS << " | " << currentTimeSeconds << std::endl;
}

long double timerSet::getDeltaTime() { return deltaTime / 1000000.l; }

long double timerSet::getTime()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(currentTime - timeZero).count() / 1000000.l;
}

long double timerSet::getTimeNow()
{
    std::chrono::high_resolution_clock::time_point timeNow = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(timeNow - timeZero).count() / 1000000.l;
}

int timerSet::getFPS() { return FPS; }

void timerSet::setMaxFPS(int newFPS) { maxFPS = newFPS; }

size_t timerSet::getFrameCounter() { return frameCounter; };

