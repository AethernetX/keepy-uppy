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
            t.date = stringToTimepoint(str);
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

std::chrono::time_point<std::chrono::system_clock> TaskManager::stringToTimepoint(std::string string){

    std::chrono::hours conv = static_cast<std::chrono::hours>(atoi(string.c_str()));
    std::chrono::time_point<std::chrono::system_clock> timepoint {conv};
    
    return timepoint;
}

void TaskManager::add(std::string name, int interval){
    Task task{};
    task.taskName = name;
    task.date = std::chrono::system_clock::now();
    task.priority = 0;
    task.interval = interval;

    tasks.push_back(task);
}

void TaskManager::remove(){
    size_t ind{};

    print();
    std::cout << "insert an index to remove a task\n";
    std::cin >> ind;

    if(ind > tasks.size()){
        std::cout << "invalid index";
        return;
    } else {
        tasks.erase(tasks.begin() + ind);
    }
}

void TaskManager::print(){

    for(size_t i = 0; i < tasks.size(); i++){

        std::cout << '[' << i << "] : ";
        std::cout << tasks[i].taskName << '\n';
    }
}