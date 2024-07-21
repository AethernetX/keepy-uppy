#include "TaskManager.h"

using namespace std::chrono_literals;

int main(){
    TaskManager taskmanager = TaskManager("Example.txt");

    taskmanager.remove();

    //const auto now = std::chrono::system_clock::now();

//    std::string str {"477960"};

//    int sesh = atoi(str.c_str());

//    std::chrono::hours hour = static_cast<std::chrono::hours>(sesh);
    
//    std::cout << std::chrono::duration_cast<tam::days>(now.time_since_epoch() - hour).count();
}