#include "TaskManager.h"

using namespace std::chrono_literals;

int main(){
    //TaskManager taskmanager = TaskManager("Example.txt");

    const auto now = std::chrono::system_clock::now();

    //std::string str {"477960"};

    //int sesh = atoi(str.c_str());

    std::cout << std::chrono::duration_cast<std::chrono::hours>(477960h - now.time_since_epoch()).count();
}

/*
incase I forgor:
    - correct output for tostring
    - parser for commands
    - maybe one simple command like add
*/