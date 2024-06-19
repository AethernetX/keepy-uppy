#include <fstream>
#include <iostream>
#include <string>

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

    std::time_t timer;

    //print tasks
    if(argc < 2){

        if(inf.gcount() == 1){
            std::cout << "You have no tasks yet!\ntype help for more information";
            return 0;
        }

        // get the last time the command was used
        std::string str{};
        std::getline(inf, str);

        time_t x{atoll(str.c_str())};
        std::time(&timer);

        std::cout << "the current time is: " << std::asctime(std::localtime(&timer));
        std::cout << "the last time this command was used was: " << std::asctime(std::localtime(&x));
        
        while(std::getline(inf, str)){
            std::cout << str << "\n";
        }
        return 0;
    } else {
        //there's probably a more elegant solution than the following
        std::string com1 {argv[1]};

        if(com1 == "help"){
            help();
            return 0;
        } else if(com1 == "add"){

            std::time(&timer);

            std::ofstream outf{ "Tasks.txt" };

            // If we couldn't open the output file stream for writing
            if (!outf)
            {
                std::cerr << "Unable to create file!\n";
                return 1;
            }

            outf << timer;

            //flushing for sanity sake
            std::flush(outf);            
            std::cout << timer;
            std::cout << std::asctime(std::localtime(&timer));
            return 0;
        }

        //std::cout << "Have " << argc << " arguments:\n";
        //for (int i = 0; i < argc; ++i) {
            //std::cout << argv[i] << "\n";
        //}
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


MACROS
will produce console outputs and in future work in 
their respective command lines

ERROR (red)

*/