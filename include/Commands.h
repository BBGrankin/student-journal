#pragma once
#include "Group.h"
#include <vector>
#include <string>

enum class Command{
    Add, Print, Find, Average, 
    RemoveBad, Save, Load, Exit, 
    SortGrade, SortName, Unknown
};

Command parseCommand(const std::vector<std::string>& tokens);

void command_execution(const std::string& line, Group& group, bool& state);
