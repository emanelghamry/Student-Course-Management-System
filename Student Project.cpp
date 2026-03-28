#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Person.h"
using namespace std;
// ===== Save students to file =====
void saveToFile(const map<int, Student>& students) {
    ofstream outFile("students.txt");
    if (!outFile) {
        cout << "Error opening file!\n";
        return;
    }

    for (const auto& pair : students) {
        outFile << pair.second.getId() << ","
            << pair.second.getName() << ","
            << pair.second.getGpa() << ","
            << pair.second.coursesToString() << "\n";
    }
    outFile.close();
    cout << "Data saved successfully!\n";
}
void loadFromFile(map<int, Student>& students) {
    ifstream inFile("students.txt");
    if (!inFile) {
        cout << "File not found!\n";
        return;
    }

    students.clear();
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idStr, name, gpaStr, coursesStr;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, gpaStr, ',');
        getline(ss, coursesStr, '\n');

        int id = stoi(idStr);
        double gpa = stod(gpaStr);

        Student s(id, name, gpa);
        s.stringToCourses(coursesStr);
        students[id] = s;
    }

    inFile.close();
    cout << "Data loaded successfully!\n";
}

int main() {
    map<int, Student> students; 
    int choice;               
    loadFromFile(students);
    while (true) {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Remove Student\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Display All Students\n";
        cout << "5. Enroll Student in Course\n";
        cout << "6. Show Student Courses\n";
        cout << "7. Sort Students by GPA\n";
        cout << "8. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        ////////////////////////////////////////   Add Student    /////////////////////////
        if (choice == 1) { 
            int id;
            string name;
            double gpa;

            cout << "Enter ID: ";
            cin >> id;
            cin.ignore();

            if (students.find(id) != students.end()) {
                cout << "Student with this ID already exists.\n";
                continue;
            }

            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter GPA: ";
            cin >> gpa;

            if (gpa < 0.0 || gpa > 4.0) {
                cout << "Invalid GPA! Must be 0.0 - 4.0\n";
                continue;
            }

            students[id] = Student(id, name, gpa);
            cout << "Student added successfully.\n";
        }
        ////////////////////////////  Remove Student  /////////////////////////////
        else if (choice == 2) { 
            int id;
            cout << "Enter ID of student to remove: ";
            cin >> id;
            auto search = students.find(id);
            if (search != students.end()) {
                students.erase(search);
                cout << "Student removed successfully.\n";
            }
            else {
                cout << "Student with this ID not found.\n";
            }
        }
        //////////////////////////////  Search Student by ID ///////////////////////////////
        else if (choice == 3) {
            int id;
            cout << "Enter ID to search: ";
            cin >> id;
            auto search = students.find(id);
            if (search != students.end()) {
                cout << "ID: " << search->second.getId()
                    << ", Name: " << search->second.getName()
                    << ", GPA: " << search->second.getGpa() << endl;
            }
            else {
                cout << "Student not found.\n";
            }
        }
       ///////////////////////////////////////  Display All Students /////////////////////////////////////
        else if (choice == 4) { 
            if (students.empty()) cout << "No students found.\n";
            else {
                for (auto& pair : students)
                    cout << "ID: " << pair.second.getId()
                    << ", Name: " << pair.second.getName()
                    << ", GPA: " << pair.second.getGpa() << endl;
            }
        }
        /////////////////////////////////////////// Enroll Student in Course ///////////////////////////////
        else if (choice == 5) { 
            int id;
            cout << "Enter ID to enroll course: ";
            cin >> id;
            cin.ignore();
            auto search = students.find(id);
            if (search != students.end()) {
                string course;
                cout << "Enter Course Name: ";
                getline(cin, course);
                search->second.EnrollCourse(course);
            }
            else {
                cout << "Student not found.\n";
            }
        }
        /////////////////////////////////// Show Student Courses /////////////////////////////
        else if (choice == 6) { 
            int id;
            cout << "Enter ID to show courses: ";
            cin >> id;
            auto search = students.find(id);
            if (search != students.end())
                search->second.showCourses();
            else
                cout << "Student not found.\n";
        }
        ///////////////////////////////// Sort Students by GPA ///////////////////////////////
        else if (choice == 7) {
            if (students.empty()) cout << "No students found.\n";
            else {
                vector<Student> sortedStudents;
                for (auto& pair : students) sortedStudents.push_back(pair.second);
                sort(sortedStudents.begin(), sortedStudents.end(),
                    [](const Student& a, const Student& b) {
                        return a.getGpa() > b.getGpa();
                    });
                for (auto& s : sortedStudents)
                    cout << "ID: " << s.getId()
                    << ", Name: " << s.getName()
                    << ", GPA: " << s.getGpa() << endl;
            }
        }
        ///////////////////////////////// Save & Exit //////////////////////////////////////
        else if (choice == 8) {
            saveToFile(students);
            cout << "Exiting program.\n";
            break;
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}