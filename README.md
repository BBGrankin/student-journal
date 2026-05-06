# GroupManager

Console C++ practice project for managing a group of students.

## Features

- Add students
- Print all students
- Find student by name
- Calculate average grade
- Remove bad students
- Save group to file
- Load group from file
- Sort students by name
- Sort students by grade

## Commands

- add <name> <age> <grade>
- print
- find <name>
- average
- remove_bad
- save <filename>
- load <filename>
- sort_name
- sort_grade
- exit

## Example

- add Boris 21 4.5
- add Smith 20 4.8
- add Ivan 19 2.5
- print
- sort_grade
- print
- save data/students.txt
- exit

## Build

~~~bash
make
~~~

## Test
~~~bash
make test
~~~

## Clean
~~~bash
make clean
~~~
Works only on Linux and macOS, on Windows works in Git Bash

## Run

Linux/macOS
~~~bash
./group_manager
~~~
Windows
~~~bash
.\group_manager.exe
~~~

## Project structure

main.cpp

include/
 - Student.h
 - Group.h
 - Command.h
 - Utils.h

source/
 - Student.cpp
 - Group.cpp
 - Command.cpp

## Notes

This is a learning project. The parser supports single-word names only.