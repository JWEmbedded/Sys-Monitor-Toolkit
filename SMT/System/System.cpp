#include "System.h"

float System::getCPUUsage() {
    std::ifstream procStat("/proc/stat");
    std::string line;
    std::getline(procStat, line);
    std::istringstream ss(line);
    std::string cpuLabel;
    long user, nice, system, idle, iowait, irq, softirq, steal;
    ss >> cpuLabel >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    long totalIdle = idle + iowait;
    long totalNonIdle = user + nice + system + irq + softirq + steal;
    long total = totalIdle + totalNonIdle;

    static long prevTotal = 0, prevIdle = 0;
    float cpuPercentage = (total - prevTotal == 0) ? 0.0 : 
                            (1.0 * (total - prevTotal - (totalIdle - prevIdle)) / (total - prevTotal)) * 100;

    prevTotal = total;
    prevIdle = totalIdle;

    return cpuPercentage;     
}

void System::getMemoryUsage() {
    std::ifstream memInfo("/proc/meminfo");
    std::string line;
    long totalMem = 0, freeMem = 0, availableMem = 0;

    while (std::getline(memInfo, line)) {
        std::istringstream ss(line);        
        std::string key;
        long value;
        std::string unit;
        ss >> key >> value >> unit;        

        if (key == "MemTotal:") totalMem = value;
        else if (key == "MemFree:") freeMem = value;
        else if (key == "MemAvailable:") {
            availableMem = value;
            break;
        }
    }

    std::cout << "Memory Usage: " << (totalMem - availableMem) / 1024 << " MB / "
              << totalMem / 1024 << " MB" << std::endl;
}

void System::getDiskUsage() {
    struct statvfs diskInfo;
    int re = statvfs("/", &diskInfo);        
    unsigned long long totalSpace = diskInfo.f_blocks * diskInfo.f_frsize;
    unsigned long long freeSpace = diskInfo.f_bfree * diskInfo.f_frsize;
    unsigned long long usedSpace = totalSpace - freeSpace;

    std::cout << "Disk Usage : " 
                << std::fixed << std::setprecision(2)
                << usedSpace / (1024.0 * 1024 * 1024) << " GB / "
                << totalSpace / (1024.0 * 1024 * 1024) << " GB" << std::endl;    
}

void System::run() {
    char input;
    bool monitoring = true;

    // 모니터링 작업을 수행하는 별도 스레드
    std::thread monitorThread([this, &monitoring]() {
        while (monitoring) {
            system("clear");  // 화면 지우기
            std::cout << "=== System Resource Monitor ===\n\n";
            std::cout << "CPU Usage: " << getCPUUsage() << "%\n";
            getMemoryUsage();
            getDiskUsage();
            std::cout << "\nPress 'q' to quit monitoring...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));  // 1초 대기
        }
    });

    //사용자 입력 처리 루프
    while (monitoring) {
        input = std::cin.get();            
        if (input == 'q') {                
            monitoring = false;
            break;
        }
    }
    

    // 모니터링 스레드 종료 대기
    monitorThread.join();
}