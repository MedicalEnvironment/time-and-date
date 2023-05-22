#include <iostream>
#include <ctime>
#include <string>
#include <vector>

struct Task {
    std::string name;
    std::time_t startTime;
    std::time_t endTime;
};

void completeTask(Task& task) {
    task.endTime = std::time(nullptr);
}

void displayStatus(const std::vector<Task>& tasks, const Task& currentTask) {
    std::cout << "Completed tasks:" << std::endl;
    for (const auto& task : tasks) {
        int hours = static_cast<int>((task.endTime - task.startTime) / 3600);
        std::cout << "Task: " << task.name << ", Duration: " << hours << " hours" << std::endl;
    }

    if (!currentTask.name.empty()) {
        std::time_t currentDuration = std::time(nullptr) - currentTask.startTime;
        int currentHours = static_cast<int>(currentDuration / 3600);
        int currentMinutes = static_cast<int>((currentDuration % 3600) / 60);
        int currentSeconds = static_cast<int>(currentDuration % 60);
        std::cout << "Currently running task: " << currentTask.name << ", Duration: "
                  << currentHours << " hours / " << currentMinutes << " minutes / "  << currentSeconds << " seconds" << std::endl;
    } else {
        std::cout << "No currently running task." << std::endl;
    }
}

int main() {
    std::vector<Task> completedTasks;
    Task currentTask;

    std::string command;

    while (true) {
        std::cout << "Enter a command (begin, end, status, exit): ";
        std::cin >> command;

        if (command == "begin") {
            std::string taskName;
            std::cout << "Enter the name of the task: ";
            std::cin.ignore();
            std::getline(std::cin, taskName);

            if (!currentTask.name.empty()) {
                completeTask(currentTask);
                completedTasks.push_back(currentTask);
            }

            currentTask.name = taskName;
            currentTask.startTime = std::time(nullptr);
        } else if (command == "end") {
            if (!currentTask.name.empty()) {
                completeTask(currentTask);
                completedTasks.push_back(currentTask);
                currentTask = Task();
            }
        } else if (command == "status") {
            displayStatus(completedTasks, currentTask);
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }

    return 0;
}
