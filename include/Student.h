#pragma once
#include <string>

class Student{
    private:
        std::string name;
        int age;
        double grade;
    
    public:
        Student(const std::string& name, int age, double grade);

        const std::string& getName() const;
        int getAge() const;
        double getGrade() const;

        void setAge(const int age);
        void setGrade(const double grade);
};