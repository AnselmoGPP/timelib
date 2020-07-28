
#include <chrono>
#include <thread>

// Object used for getting the time between events. Call get_delta_time() for getting the time increment between two consecutives calls to this function.
class timer;

// Object used for getting the time between events. Call start() and end() for getting the time increment between both calls.

// Get date and time (all in numbers)

// Get date and time (months and week days are strings)


// Definitions -------------------------------------------------------------------------------------------

class timer
{
public:
    long deltaTime;
    void get_delta_time();                      // Get time increment between two consecutives calls to this function
    void fps_control(unsigned int frequency);   // Argument: Desired FPS (a sleep will be activated to slow down the process)

private:
    bool first_call = true;
    std::chrono::high_resolution_clock::time_point lastTime, currentTime;
};

void timer::get_delta_time()
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

void timer::fps_control(unsigned int frequency)
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
