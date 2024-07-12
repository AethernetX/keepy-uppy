#include "TaskManager.h"

std::ostream& operator<< (std::ostream& out, Task& task){
    out << task.toString();
    return out;
}

std::string Task::toString(){
    return taskName;
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
            tasks.push_back(t);
        }
        input.close();
    }
}

TaskManager::~TaskManager(){
    output.open(filepath);
    for (auto i : tasks)
    {
        output << i << '\n';
    }

    output.close();
}