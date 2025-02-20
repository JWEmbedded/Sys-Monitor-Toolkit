#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/statvfs.h>
#include <iostream>
#include <iomanip>
#include <thread>
#include <unistd.h>

class System{
public:
    float getCPUUsage();
    void getMemoryUsage();
    void getDiskUsage();
    void run();
};