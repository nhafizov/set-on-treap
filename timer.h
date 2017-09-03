#include "time.h"

class Timer {
 private:
    clock_t _start = 0;
    clock_t _end = 0;
    bool resetted = true;
    bool running = false;

 public:
    Timer() {}

    void start() {
        if (!running) {
            if (resetted) {
                _start = clock();
            } else {
                _start = clock();
            }
            running = true;
            resetted = false;
        }
    }

    void stop() {
        if (running) {
            _end = clock();
            running = false;
        }
    }

    void restart() {
        auto preRunning = running;
        if (preRunning) stop();
        resetted = true;
        _start = 0;
        _end = 0;
        if (preRunning)
            start();
    }

    double getTime() {
        if (running)
            return (static_cast<double>(clock() - _start) / CLOCKS_PER_SEC);
        else
            return static_cast<double>(_end - _start) / CLOCKS_PER_SEC;
    }
};