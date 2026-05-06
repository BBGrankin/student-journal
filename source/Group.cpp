#include "Group.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Utilities.h"

void Group::print() const{
    if (group.size() == 0){
        std::cout << separator << "There is no students in group\n" << separator;
        return;
    }
    std::cout << separator;
    for (std::size_t i {}; i < group.size(); ++i){
        std::cout << "Name: " << group[i].getName() << '\t'
        << "Age: " << group[i].getAge() << '\t' << '\t'
        << "Grade: " << group[i].getGrade() << '\n';
    }
    std::cout << separator;
}

void Group::save_file(std::ofstream& file) const{
    for (std::size_t i {}; i < group.size(); ++i){
        file << group[i].getName() << ' ' << group[i].getAge() 
        << ' ' << group[i].getGrade() << '\n';
    }
}

void Group::find(const std::string& name) const{
    auto nameParser = [name](const Student& x){return x.getName() == name;};
    auto pointer = std::find_if(group.begin(), group.end(), nameParser);
    if (pointer != group.end()){
        std::cout << separator << "Name: " << pointer->getName() << '\t'
        << "Age: " << pointer->getAge() << '\t' << '\t'
        << "Grade: " << pointer->getGrade() << '\n' << separator;
        return;
    }
    std::cout << separator << "Student not found\n" << separator;
}

double Group::averageGrade() const{
    if (group.size() == 0) return 0;
    double sum {};
    for (std::size_t i {}; i < group.size(); ++i){
        sum += group[i].getGrade();
    }
    return sum / static_cast<double>(group.size());
}

void Group::remove_bad(){
    auto belowAverage = [](const Student& x){return x.getGrade() < 3.;};
    auto pointer = std::remove_if(group.begin(), group.end(), belowAverage);
    if (pointer == group.end()){
        std::cout << separator << "There is no bad students\n" << separator;
        return;
    }
    group.erase(pointer, group.end());
    std::cout << separator << "Bad students removed\n" << separator;
}

void Group::add_student(const std::string& name, int age, double grade){
    Student student(name, age, grade);
    group.push_back(student);
}

void Group::load_file(std::ifstream& file){
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

void Group::sort_name(){
    auto byName = [](const Student& x, const Student& y){
        return x.getName() < y.getName();
    };
    std::sort(group.begin(), group.end(), byName);
    std::cout << separator << "Group sorted by name\n" << separator;      
}

void Group::sort_grade(){
    auto byGrade = [](const Student& x, const Student& y){
        return x.getGrade() < y.getGrade();
    };
    std::sort(group.begin(), group.end(), byGrade);
    std::cout << separator << "Group sorted by grade\n" << separator;
}
