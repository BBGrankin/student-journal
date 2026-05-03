#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <string_view>
#include <sstream>

const std::string_view string {"----------\n"};

enum class Command{
    Add, Print, Find, Average, RemoveBad, Save, Load, Exit, Unknown
};

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
    else return Command::Unknown;
}

class Student{
    private:
        std::string name;
        int age;
        double grade;
    
    public:
        Student(const std::string& name, int age, double grade): name(name), age(age), grade(grade)
        {}

        const std::string& getName() const{
            return name;
        }

        int getAge() const{
            return age;
        }

        double getGrade() const{
            return grade;
        }

        void setAge(const int age){
            if (age > 100 || age < 0) return;
            this->age = age;
        }

        void setGrade(const double grade){ 
            if (grade > 5. || grade < 2.) return;
            this->grade = grade;
        }
};

class Group{
    private:
        std::vector<Student> group;

    public:
        void print() const{
            if (group.size() == 0){
                std::cout << string << "There is no students in group\n" << string;
                return;
            }
            std::cout << string;
            for (std::size_t i {}; i < group.size(); ++i){
                std::cout << "Name: " << group[i].getName() << '\t'
                << "Age: " << group[i].getAge() << '\t' << '\t'
                << "Grade: " << group[i].getGrade() << '\n';
            }
            std::cout << string;
        }

        void save_file(std::ofstream& file) const{
            for (std::size_t i {}; i < group.size(); ++i){
                file << group[i].getName() << ' ' << group[i].getAge() 
                << ' ' << group[i].getGrade() << '\n';
            }
        }

        void find(const std::string& name) const{
            for (std::size_t i {}; i < group.size(); ++i){
                if (group[i].getName() == name){
                    std::cout << string << "Name: " << group[i].getName() << '\t'
                    << "Age: " << group[i].getAge() << '\t' << '\t'
                    << "Grade: " << group[i].getGrade() << '\n' << string;
                    return;
                }
            }
            std::cout << string << "Student not found\n" << string;
        }

        double averageGrade() const{
            if (group.size() == 0) return 0;
            double sum {};
            for (std::size_t i {}; i < group.size(); ++i){
                sum += group[i].getGrade();
            }
            return sum / static_cast<double>(group.size());
        }

        void remove_bad(){
            int count {};
            std::size_t i {};
            while (i < group.size()){
                if (group[i].getGrade() < 3.) {
                    group.erase(group.begin() + i);
                    ++count;
                }
                else ++i;
            }
            if (count > 0) std::cout << string << "Bad students removed\n" << string;
            else std::cout << string << "There is no bad students\n" << string;
        }

        void add_student(const std::string& name, int age, double grade){
            Student student(name, age, grade);
            group.push_back(student);
        }

        void load_file(std::ifstream& file){
            group.clear();
            std::string name {};
            int age {};
            double grade {};
            try{ 
                while (file >> name >> age >> grade){
                    add_student(name, age, grade);
                }
            }
            catch (const std::exception& e) {
                throw std::invalid_argument("Couldn`t load file");
            }
        }
};

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
            std::cout << string << "Student added\n" << string;
        }
        catch(const std::exception& e){
            std::cout << string << e.what() << '\n' << string;
        }
    }

    void find (const std::vector<std::string>& tokens, const Group& group){
        if (tokens.size() != 2){
            std::cout << string << "Wrong number of parameters\n" << string;
            return;
        }
        group.find(tokens[1]);
    }

    void save (const std::vector<std::string>& tokens, const Group& group){
        if (tokens.size() != 2){
            std::cout << string << "Wrong number of parameters\n" << string;
            return;
        }
        std::ofstream file {tokens[1]};
        if (!file){
            std::cout << string << "Couldn`t open file\n" << string;
            return;
        }
        group.save_file(file);
        file.close();
        std::cout << string << "Saved successfully\n" << string;
    }

    void load (const std::vector<std::string>& tokens, Group& group){
        if (tokens.size() != 2){
            std::cout << string << "Wrong number of parameters\n" << string;
            return;
        }
        std::ifstream file {tokens[1]};
        if (!file){
            std::cout << string << "Couldn`t open file\n" << string;
            return;
        }
        try {
            group.load_file(file);
        }
        catch(const std::exception& e) {
            std::cerr << string << e.what() << '\n' << string;
            return;
        }
        file.close();
        std::cout << string << "Loaded successfully\n" << string;
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
        case Command::Average: std::cout << string << group.averageGrade() << '\n' << string;
            break;
        case Command::RemoveBad: group.remove_bad();
            break;
        case Command::Exit: state = false;
            break;
        case Command::Save: CommandsExecution::save(tokens, group);
            break;
        case Command::Load: CommandsExecution::load(tokens, group);
            break;
        case Command::Unknown: std::cout << string << "Unknown command\n" << string;
    }
}

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