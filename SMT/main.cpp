#include "System/System.h"
#include "Process/ProcessManager.h"
#include <iostream>
#include <memory>

void showMainMenu() {
    std::cout << "\n=== System Management Tool ===\n"
              << "1. System Management\n"
              << "2. Process Management\n"
              << "0. Exit\n"
              << "Choose an option: ";
}

int main() {
    int choice;
    std::unique_ptr<System> systemManager(new System);
    std::unique_ptr<ProcessManager> processManager(new ProcessManager);

    while (true) {
        showMainMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                systemManager->run();    
                break;
            case 2:                
                processManager->run();    
                break;
            case 0:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid option!\n";
        }
    }

    return 0;
}
