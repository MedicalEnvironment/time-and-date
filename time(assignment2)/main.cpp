#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

struct Friend {
    std::string name;
    std::tm birthday;
};

void displayNextBirthday(const std::vector<Friend>& friends) {
    std::time_t currentTime = std::time(nullptr);
    std::tm currentTm = *std::localtime(&currentTime);

    std::tm nextBirthdayTm = currentTm;
    nextBirthdayTm.tm_year += 1; // Set to next year
    std::time_t nextBirthdayTime = std::mktime(&nextBirthdayTm);

    std::vector<std::string> todayBirthdays;

    for (const auto& friendData : friends) {
        std::tm friendTm = friendData.birthday;
        friendTm.tm_year = currentTm.tm_year; // Set to current year

        std::time_t friendTime = std::mktime(&friendTm);

        if (friendTime >= currentTime && friendTime < nextBirthdayTime) {
            if (friendTm.tm_mon == currentTm.tm_mon && friendTm.tm_mday == currentTm.tm_mday) {
                todayBirthdays.push_back(friendData.name);
            } else {
                nextBirthdayTm = friendTm;
                nextBirthdayTime = friendTime;
            }
        }
    }

    std::cout << "Next birthday: ";

    if (!todayBirthdays.empty()) {
        std::cout << "Today is the birthday of ";

        for (const auto& name : todayBirthdays) {
            std::cout << name << ", ";
        }
        std::cout << std::endl;
    } else {
        std::cout << nextBirthdayTm.tm_mon + 1 << "/" << nextBirthdayTm.tm_mday << std::endl;
    }
}

int main() {
    std::vector<Friend> friends;
    std::string name;
    std::string birthdayInput;

    while (true) {
        std::cout << "Enter friend's name and birthday (year/month/day), or 'end' to finish: ";
        std::cin >> name;

        if (name == "end") {
            break;
        }

        std::cin >> birthdayInput;

        if (birthdayInput == "end") {
            break;
        }

        std::tm birthday = {};
        std::istringstream iss(birthdayInput);
        iss >> std::get_time(&birthday, "%Y/%m/%d");

        if (!iss.fail()) {
            Friend friendData;
            friendData.name = name;
            friendData.birthday = birthday;
            friends.push_back(friendData);
        } else {
            std::cout << "Invalid birthday format. Please enter in the format year/month/day." << std::endl;
        }
    }

    displayNextBirthday(friends);

    return 0;
}
