#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <cstdint>
#include <ctime>

//representing tasks??
struct task {
    std::string name;
    std::time_t prevTime;
};

int init(){
    std::ofstream outf{ "Tasks.txt" };

    // If we couldn't open the output file stream for writing
    if (!outf)
    {
        std::cerr << "Unable to create file!\n";
        return 1;
    }

    //flushing for sanity sake
    std::flush(outf);
    return 0;
}

void help(){
    std::cout << " help: prints out the following\n add <enter string here>: adds a task(NOT WORKING)\n remove [index]: removes a task(NOT WORKING)\n";
}

int add(){
    std::time_t timer{};
    std::time(&timer);

    std::ofstream outf{ "Tasks.txt" };

    // If we couldn't open the output file stream for writing
    if (!outf)
    {
        std::cerr << "Unable to create file!\n";
        return 1;
    }

    outf << timer;
    return 0;
}

int print(){

    std::ifstream inf{};
    
    inf.open("Tasks.txt");

    //the first string will always be the session time
    std::string session{};
    std::getline(inf, session);
    
    //convert entire file into vector
    std::vector<std::string> tasks;
    std::string str{};
    while(std::getline(inf, str)){
        tasks.push_back(str);
    }

    std::time_t prevTime;
    prevTime = atoll(session.c_str());
    
    std::cout << "The last time this command was used was: " << std::asctime(std::localtime(&prevTime)) << "\n";

    //the following will be the task name, followed by when it was last done
    for(size_t i = 0; i < tasks.size(); i++){
        std::cout << "[" << i << "] " << tasks[i] << "\n";
    }

    //close the file
    

    //now rewrite the file
    std::ofstream outf{};

    outf.open("Tasks.txt", std::ios::trunc);

    std::time_t timer{};
    std::time(&timer);

    outf << timer << "\n";
    
    for(size_t i = 0; i < tasks.size(); i++){
        outf << tasks[i] << "\n";
    }
    
    return 0;
}

int main(int argc, char *argv[])
{
    std::ifstream inf{ "Tasks.txt" };
    
    // if the user has no task file
    if(!inf){
        int r = init();
        if(r != 0){
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

        int x = print();
        if(x == 1){
            return 1;
        }
        return 0;
    } else {
        //there's probably a more elegant solution than the following
        std::string com1 {argv[1]};

        if(com1 == "help"){
            help();
            return 0;
        } else if(com1 == "add"){
            int x = add();
            if(x == 1){
                return 1;
            }
            return 0;
        }

        //std::cout << "Have " << argc << " arguments:\n";
        //for (int i = 0; i < argc; ++i) {
            //std::cout << argv[i] << "\n";
        //}
    }
}

/*
TODO: 
format tasks that haven't been handled for too long
adding tasks
removing tasks


*/

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


MACROS
will produce console outputs and in future work in 
their respective command lines

ERROR (red)

*/