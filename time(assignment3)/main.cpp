#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <thread>

void countdownTimer(int minutes, int seconds) {
    std::time_t startTime = std::time(nullptr);
    std::time_t endTime = startTime + minutes * 60 + seconds;

    while (std::time(nullptr) < endTime) {
        std::time_t remainingTime = endTime - std::time(nullptr);
        int remainingMinutes = remainingTime / 60;
        int remainingSeconds = remainingTime % 60;

        std::cout << std::setw(2) << std::setfill('0') << remainingMinutes << ":"
                  << std::setw(2) << std::setfill('0') << remainingSeconds << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "DING! DING! DING!" << std::endl;
}

int main() {
    int minutes, seconds;

    std::cout << "Enter the number of minutes: ";
    std::cin >> minutes;

    std::cout << "Enter the number of seconds: ";
    std::cin >> seconds;

    countdownTimer(minutes, seconds);

    return 0;
}
