#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <chrono>

#include <Windows.h>

//to log how often I use the command
int logger(){
    std::time_t timer{};
    std::time(&timer);

    std::ofstream outf{};

    // If we couldn't open the output file stream for writing
    if (!outf)
    {
        std::cerr << "Unable to write file!\n";
        return 1;
    }

    outf.open("log/log.txt", std::ios::app);
    outf << "ku" << "\n";
    outf << timer << "\n";
    outf.close();
    return 0;
}

//method https://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
std::string getexepath()
{
    char result[ MAX_PATH ];
    std::string path = std::string( result, GetModuleFileName( NULL, result, MAX_PATH ) );
    size_t pos = path.find_last_of('\\');
    path.erase(pos + 1, path.size());
    return path;
}


int init(){
    std::ofstream outf{ getexepath() + "Tasks.txt" };

    // If we couldn't open the output file stream for writing
    if (!outf)
    {
        std::cerr << "Unable to create file!\n";
        return 1;
    }

    std::time_t timer;
    std::time(&timer);

    outf << timer << "\n";

    return 0;
}

void help(){
    std::cout << " help: prints out the following\n add <enter string here>: adds a task\n remove: removes a task\n up: updates a task";
}

int add(std::string title){
    std::time_t timer{};
    std::time(&timer);

    std::ofstream outf{};

    // If we couldn't open the output file stream for writing
    if (!outf)
    {
        std::cerr << "Unable to write file!\n";
        return 1;
    }

    outf.open(getexepath() + "Tasks.txt", std::ios::app);
    outf << title << "\n";
    outf << timer << "\n";
    outf.close();

    return 0;
}

int rem(){
    std::ifstream inf{};
    
    if (!inf)
    {
        std::cerr << "Unable to read file!\n";
        return 1;
    }

    inf.open(getexepath() + "Tasks.txt");

    //the first string will always be the session time
    std::string session{};
    std::getline(inf, session);
    
    //convert entire file into vector
    std::vector<std::string> tasks;
    std::string str{};
    while(std::getline(inf, str)){
        tasks.push_back(str);
    }
    
    //the following will be the task name, followed by when it was last done
    for(size_t i = 0; i < tasks.size(); i++){
        std::time_t taskTime;
        std::cout << "[" << i/2 << "] " << tasks[i] << " ";
        taskTime = atoll(tasks[++i].c_str());
        std::cout << std::asctime(std::localtime(&taskTime)) << "\n";
    }

    std::cout << "enter index of task you wish to remove: \n";
    int v{};
    std::cin >> v;

    if (static_cast<long long unsigned int>(v*2) > tasks.size()){
        std::cout << "invalid index\n";
    } else {
        std::cout << "removing " << tasks[v*2];
        //idk why it won't let me do it in one line so this will have to do
        tasks.erase(tasks.begin() + (v*2));
        tasks.erase(tasks.begin() + ((v*2) + 1));
    }
    //now rewrite the file
    std::ofstream outf{};

    if (!outf)
    {
        std::cerr << "Unable to write file!\n";
        return 1;
    }

    outf.open(getexepath() + "Tasks.txt", std::ios::trunc);

    outf << session << "\n";
    
    for(size_t i = 0; i < tasks.size(); i++){
        outf << tasks[i] << "\n";
    }

    return 0;
}

int update(){
    std::ifstream inf{};
    
    if (!inf)
    {
        std::cerr << "Unable to read file!\n";
        return 1;
    }

    inf.open(getexepath() + "Tasks.txt");

    //the first string will always be the session time
    std::string session{};
    std::getline(inf, session);
    
    //convert entire file into vector
    std::vector<std::string> tasks;
    std::string str{};
    while(std::getline(inf, str)){
        tasks.push_back(str);
    }
    
    //the following will be the task name, followed by when it was last done
    for(size_t i = 0; i < tasks.size(); i++){
        std::time_t taskTime;
        std::cout << "[" << i/2 << "] " << tasks[i] << " ";
        taskTime = atoll(tasks[++i].c_str());
        std::cout << std::asctime(std::localtime(&taskTime)) << "\n";
    }

    std::cout << "enter index of task you wish to update: \n";
    int v{};
    std::cin >> v;

    if (static_cast<long long unsigned int>(v*2) > tasks.size()){
        std::cout << "invalid index\n";
    } else {
        std::cout << "updated " << tasks[v*2];
        std::time_t timer;
        std::time(&timer);
        std::stringstream ss;
        ss << timer;
        tasks[v*2 + 1] = ss.str();
    }

    //close the file
    

    //now rewrite the file
    std::ofstream outf{};

    if (!outf)
    {
        std::cerr << "Unable to write file!\n";
        return 1;
    }

    outf.open(getexepath() + "Tasks.txt", std::ios::trunc);

    outf << session << "\n";
    
    for(size_t i = 0; i < tasks.size(); i++){
        outf << tasks[i] << "\n";
    }

    return 0;
}

int print(){

    std::ifstream inf{};
    
    if (!inf)
    {
        std::cerr << "Unable to read file!\n";
        return 1;
    }

    inf.open(getexepath() + "Tasks.txt");

    //the first string will always be the session time
    std::string session{};
    std::getline(inf, session);
    
    //convert entire file into vector
    std::vector<std::string> tasks;
    std::string str{};
    while(std::getline(inf, str)){
        tasks.push_back(str);
    }

    //current time
    std::time_t timer{};
    std::time(&timer);

    std::time_t prevTime;
    prevTime = atoll(session.c_str());
    
    std::cout << "The last time this command was used was: " << std::asctime(std::localtime(&prevTime)) << "\n";

    //the following will be the task name, followed by when it was last done
    for(size_t i = 0; i < tasks.size(); i++){
        std::time_t taskTime;
        std::cout << "[" << i/2 << "] " << tasks[i] << " ";
        taskTime = atoll(tasks[++i].c_str());
        double timeSince{difftime(timer, taskTime)/86400};
        if(timeSince > 3){
            std::cout << "\x1b[91m";
        } else {
            std::cout << "\x1b[92m";
        }
        std::cout << std::asctime(std::localtime(&taskTime)) << "\x1b[0;m \n";
    }

    //close the file
    

    //now rewrite the file
    std::ofstream outf{};

    if (!outf)
    {
        std::cerr << "Unable to write file!\n";
        return 1;
    }

    outf.open(getexepath() + "Tasks.txt", std::ios::trunc); 

    outf << timer << "\n";
    
    for(size_t i = 0; i < tasks.size(); i++){
        outf << tasks[i] << "\n";
    }
    
    return 0;
}

int main(int argc, char *argv[])
{

    //there's probably a more elegant solution than the following
    std::string com1 {};
    if(argc >= 2){
        com1 = argv[1];
    }

    std::ifstream inf{ getexepath() + "Tasks.txt" };
    
    // if the user has no task file
    if(!inf){
        if(init() != 0){
            return 1;
        }
        std::cout << "You have no tasks yet!\ntype help for more information";
        return 0;
    }

    //print tasks
    if(argc < 2){

        if(inf.gcount() == 1){
            std::cout << "You have no tasks yet!\ntype help for more information";
            return 0;
        }

        #ifdef LOG
            if(logger() == 1){
                return 1;
            }
        #endif

        if(print() == 1){
            return 1;
        }
        return 0;
    } else if (argc == 2){

        if(com1 == "help"){
            help();
            return 0;
        } else if(com1 == "remove"){
            if(rem() == 1){
                return 1;
            }
            return 0;
        } else if(com1 == "up"){
            if(update() == 1){
                return 1;
            }
        } 
        else {
            std::cout << "Unknown command, type help for more info \n";
        }

    } else if (argc == 3){ 

        if(com1 == "add"){
            if(add(argv[2]) == 1){
                return 1;
            }
            return 0;
        }

    } else {
        std::cout << "ERROR: Unknown amount of arguments\n";
        help();
    }
}


/*
    functions:
    default
    -- shows current tasks and when they were last done

    add
    -- adds a new task to keep up

    remove
    -- removes an existing task
    -- prints an error if there is none or not found

    help
    -- puts a useful help information

    up
    -- updates tasks
*/