#include "Commands.h"
#include <stdexcept>
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>

Command parseCommand(const std::vector<std::string>& tokens){
    if (tokens.size() == 0) return Command::Unknown;
    std::string line {tokens[0]};
    if (line == "add") return Command::Add;
    if (line == "print") return Command::Print;
    if (line == "find") return Command::Find;
    if (line == "average") return Command::Average;
    if (line == "remove_bad") return Command::RemoveBad;
    if (line == "save") return Command::Save;
    if (line == "load") return Command::Load;
    if (line == "exit") return Command::Exit;
    if (line == "sort_grade") return Command::SortGrade;
    if (line == "sort_name") return Command::SortName;
    else return Command::Unknown;
}

namespace CommandsExecution{
    void add (const std::vector<std::string>& tokens, Group &group){
        int age {};
        double grade {};
        try{
            if (tokens.size() != 4) throw std::invalid_argument("Wrong amount of parameters");
            try{
                age = std::stoi(tokens[2]);
                grade = std::stod(tokens[3]);
            }
            catch (const std::exception& e) {
                throw std::invalid_argument("Couldn`t transform string to number");
            }
            if (age > 100 || age < 0) throw std::invalid_argument("Are u even human? Wrong age entered");
            if (grade > 5. || grade < 2.) throw std::invalid_argument("Wrong grade enetered 2.0 <= grade <= 5.0");
            group.add_student(tokens[1], age, grade);
            std::cout << separator << "Student added\n" << separator;
        }
        catch(const std::exception& e){
            std::cout << separator << e.what() << '\n' << separator;
        }
    }

    void find (const std::vector<std::string>& tokens, const Group& group){
        if (tokens.size() != 2){
            std::cout << separator << "Wrong number of parameters\n" << separator;
            return;
        }
        group.find(tokens[1]);
    }

    void save (const std::vector<std::string>& tokens, const Group& group){
        if (tokens.size() != 2){
            std::cout << separator << "Wrong number of parameters\n" << separator;
            return;
        }
        std::ofstream file {tokens[1]};
        if (!file){
            std::cout << separator << "Couldn`t open file\n" << separator;
            return;
        }
        group.save_file(file);
        file.close();
        std::cout << separator << "Saved successfully\n" << separator;
    }

    void load (const std::vector<std::string>& tokens, Group& group){
        if (tokens.size() != 2){
            std::cout << separator << "Wrong number of parameters\n" << separator;
            return;
        }
        std::ifstream file {tokens[1]};
        if (!file){
            std::cout << separator << "Couldn`t open file\n" << separator;
            return;
        }
        try {
            group.load_file(file);
        }
        catch(const std::exception& e) {
            std::cerr << separator << e.what() << '\n' << separator;
            return;
        }
        file.close();
        std::cout << separator << "Loaded successfully\n" << separator;
    }
}

void command_execution(const std::string& line, Group& group, bool& state){
    std::vector<std::string> tokens {};
    std::string word {};
    std::istringstream iss {line};
    while (iss >> word){
        tokens.push_back(word);
    }
    if (!state) return;
    switch(parseCommand(tokens)){
        case Command::Add: CommandsExecution::add(tokens, group);
            break;
        case Command::Print: group.print();
            break;
        case Command::Find: CommandsExecution::find(tokens, group);
            break;
        case Command::Average: std::cout << separator << group.averageGrade() << '\n' << separator;
            break;
        case Command::RemoveBad: group.remove_bad();
            break;
        case Command::Exit: state = false;
            break;
        case Command::Save: CommandsExecution::save(tokens, group);
            break;
        case Command::Load: CommandsExecution::load(tokens, group);
            break;
        case Command::SortGrade: group.sort_grade();
            break;
        case Command::SortName: group.sort_name();
            break;
        case Command::Unknown: std::cout << separator << "Unknown command\n" << separator;
    }
}
