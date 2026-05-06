#pragma once
#include <vector>
#include "Student.h"

class Group{
    private:
        std::vector<Student> group;

    public:
        void print() const;

        void save_file(std::ofstream& file) const;

        void find(const std::string& name) const;

        double averageGrade() const;

        void remove_bad();

        void add_student(const std::string& name, int age, double grade);

        void load_file(std::ifstream& file);

        void sort_name();

        void sort_grade();
};
