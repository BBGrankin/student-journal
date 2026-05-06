#include "Student.h"

Student::Student(const std::string& name, int age, double grade): 
        name(name), age(age), grade(grade)
    {}

const std::string& Student::getName() const{
    return name;
}

int Student::getAge() const{
    return age;
}

double Student::getGrade() const{
    return grade;
}

void Student::setAge(const int age){
    if (age > 100 || age < 0) return;
    this->age = age;
}

void Student::setGrade(const double grade){ 
    if (grade > 5. || grade < 2.) return;
    this->grade = grade;
}
