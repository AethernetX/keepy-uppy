#include "TaskManager.h"

#include <sstream>

std::ostream& operator<< (std::ostream& out, Task& task){
    out << task.toString();
    return out;
}

std::string Task::toString(){
    std::stringstream str{};

    str << taskName << '\n';
    str << std::chrono::duration_cast<tam::days>(date.time_since_epoch()).count() << '\n';
    str << priority << '\n';
    str << interval;

    return str.str();
}

TaskManager::TaskManager(std::string filePath){
    filepath = filePath;

    //load tasks into tasks vector
    input.open(filepath);

    if (!input)
    {
        std::cerr << "Unable to read file!\n";
        // could just init a file?
    }

    if(input.peek() == std::ifstream::traits_type::eof()){
        std::cout << input.gcount() << " empty file\n";
    } else {
        std::string str;
        //we know the first line will be the session

        while(std::getline(input, str)){
            Task t {}; 
            t.taskName = str;
            std::getline(input, str);
            t.date = std::chrono::system_clock::now();
            std::getline(input, str);
            t.priority = atoi(str.c_str());
            std::getline(input, str);
            t.interval = atoi(str.c_str());
            tasks.push_back(t);
        }
        input.close();
    }
}

TaskManager::~TaskManager(){
    output.open(filepath, std::ofstream::trunc);
    for (auto i : tasks)
    {
        output << i << '\n';
    }

    output.close();
}