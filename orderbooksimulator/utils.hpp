#pragma once
#include <chrono>
#include <fstream>
#include <string>
#include <ctime>
#include <iostream>

//Timer type with functions begin and end
class Timer {
    private:
    std::chrono::high_resolution_clock::time_point start;

    public:
    void begin() {
        start = std::chrono::high_resolution_clock::now();

    }

    double end() {
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> total_time = finish - start;
        return total_time.count();
    }
};

