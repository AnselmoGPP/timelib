
#include <chrono>
#include <thread>

// Object used for getting the time between events. Two ways:
//     get_delta_time(): Get the time increment (deltaTime) between two consecutive calls to this function.
//     start() & end(): Get the time increment (deltaTime) between a call to start() and end(). <<<<<<<<<<<<<<<<<<<<<<
class timer
{
// Get date and time (all in numbers)

// Get date and time (months and week days are strings)
};

// Class used in the render loop (OpenGL, Vulkan, etc.) for different time-related purposes (frame counting, delta time, current time, fps...)
class timerSet
{
    std::chrono::high_resolution_clock::time_point timeZero;
    std::chrono::high_resolution_clock::time_point lastTime;
    std::chrono::high_resolution_clock::time_point currentTime;

    long double currentTimeSeconds;

    long double deltaTime;

    int FPS;
    int maxFPS;

    size_t frameCounter;

public:
    timerSet(int maxFPS = 0);

    void        startTime();            // Set starting time for the chronometer (startingTime)
    void        computeDeltaTime();     // Compute frame's duration (time between two calls to this)
    void        printTimeData();        // Print relevant values

    long double getDeltaTime();         // Returns time (seconds) increment between frames (deltaTime)
    long double getTime();              // Returns time (seconds) when computeDeltaTime() was called
    long double getTimeNow();           // Returns time (seconds) since timeZero, at the moment of calling GetTimeNow()
    int         getFPS();               // Get FPS
    size_t      getFrameCounter();      // Get frame number (depends on the number of times getDeltaTime() was called)

    void        setMaxFPS(int fps);     // Given a maximum fps, put thread to sleep to get it
};

// Others -------------------------------------------------------------------

class timer_2
{
public:
    long deltaTime;
    void get_delta_time();                      // Get time increment between two consecutives calls to this function
    void fps_control(unsigned int frequency);   // Argument: Desired FPS (a sleep will be activated to slow down the process)

private:
    bool first_call = true;
    std::chrono::high_resolution_clock::time_point lastTime, currentTime;
};

void timer_2::get_delta_time()
{
    if(first_call)  // Executed only once (first call)
    {
        lastTime = std::chrono::high_resolution_clock::now();
        first_call = false;
    }

    // Time difference between current and last frame
    currentTime = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count();

    lastTime = currentTime;
}

void timer_2::fps_control(unsigned int frequency)
{
    get_delta_time();

    long desired_time = 1000000/frequency;
    if(deltaTime < desired_time)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(desired_time - deltaTime));
        currentTime = std::chrono::high_resolution_clock::now();
        deltaTime += std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count();
        lastTime = currentTime;
        //std::cout << "FPS: " << 1000000/deltaTime << '\r';
    }
}
