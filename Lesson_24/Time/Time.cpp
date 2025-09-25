#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class Task {
public:
    std::string name;
    std::time_t start_time;
    std::time_t end_time;

    Task(const std::string& task_name, std::time_t start)
        : name(task_name), start_time(start), end_time(0) {
    }

    void end(std::time_t end) {
        end_time = end;
    }

    double duration_in_hours() const {
        return difftime(end_time, start_time) / 3600.0;
    }
};

class TimeManager {
private:
    std::vector<Task> tasks;
    Task* current_task;

public:
    TimeManager() : current_task(nullptr) {}

    void begin(const std::string& task_name) {
        if (current_task != nullptr) {
            current_task->end(std::time(nullptr));
            tasks.push_back(*current_task);
            delete current_task;
        }
        current_task = new Task(task_name, std::time(nullptr));
        std::cout << "Starting task: " << current_task->name << std::endl;
    }

    void end() {
        if (current_task != nullptr) {
            current_task->end(std::time(nullptr));
            tasks.push_back(*current_task);
            delete current_task;
            current_task = nullptr;
            std::cout << "Task ended." << std::endl;
        }
        else {
            std::cout << "No current task to end." << std::endl;
        }
    }

    void status() const {
        std::cout << "Finished tasks:" << std::endl;
        for (const auto& task : tasks) {
            std::cout << task.name << " - Duration: " << task.duration_in_hours() << " hours" << std::endl;
        }
        if (current_task != nullptr) {
            std::cout << "Current task: " << current_task->name << std::endl;
        }
        else {
            std::cout << "No current task." << std::endl;
        }
    }

    void exit() {
        std::cout << "Exiting program." << std::endl;
        end();
    }
};

int main() {
    TimeManager manager;
    std::string command;

    std::cout << "Welcome to the Time Manager!" << std::endl;

    while (true) {
        std::cout << "Enter command (begin, end, status, exit): ";
        std::cin >> command;

        if (command == "begin") {
            std::string task_name;
            std::cout << "Enter task name: ";
            std::cin.ignore();
            std::getline(std::cin, task_name);
            manager.begin(task_name);
        }
        else if (command == "end") {
            manager.end();
        }
        else if (command == "status") {
            manager.status();
        }
        else if (command == "exit") {
            manager.exit();
            break;
        }
        else {
            std::cout << "Unknown command. Please try again." << std::endl;
        }
    }

    return 0;
}

