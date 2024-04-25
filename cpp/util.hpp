#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <list>
#include <tuple>
#include <cstdlib>
#include <regex>
#include <random>
#include <chrono>
#include <thread>

using namespace std;

inline void debug(int t)
{
    std::this_thread::sleep_for(std::chrono::seconds(t));
    return;
}

