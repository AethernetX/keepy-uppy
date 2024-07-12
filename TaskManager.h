#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Task
{
    public:
        std::string toString();

        friend std::ostream& operator<< (std::ostream &out, Task& task);
    
        std::string taskName;
        std::chrono::time_point<std::chrono::system_clock> date;
        int priority;
        std::chrono::hours interval;
    
    private:
        
};


class TaskManager {
    public:
        TaskManager(std::string filepath);
        ~TaskManager();

        std::vector<Task>* getTask();
    private:
        std::vector<Task> tasks{};

        std::string filepath;

        std::chrono::time_point<std::chrono::system_clock> lastSession;

        std::ifstream input;
        std::ofstream output;
};