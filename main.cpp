#include <iostream>
#include <string>
#include "Student.h"
#include "Utilities.h"
#include "Group.h"
#include "Commands.h"

int main(){
    bool program_is_running {true};
    Group group;
    std::string line {};
    while (program_is_running){
        std::getline(std::cin >> std::ws, line);
        command_execution(line, group, program_is_running);
    }
    return 0;
}