#include "person.h"
using namespace std;
#pragma once
#include "Person.h"
#include <iostream>
#include <set>
#include <string>
#include <sstream>
Student::Student()
{
	id = 0;
	name = "";
	gpa = 0.0;
}

Student::Student(int ide, string n, double gpa)
{
	id = ide;
	name = n;
	this->gpa = gpa;
}
int Student::getId()const {
	return id;
}
string Student::getName() const{
	return name;
}
double Student::getGpa() const{
	return gpa;
}
void Student::EnrollCourse( const string& course)
{
	auto result = courses.insert(course);
	if (result.second) {
		cout << "Course added successfully.\n";
	}
	else {
		cout << "Course already exists.\n";

	}

}
void Student::showCourses()
{
	if (courses.empty()) {
		cout << "No courses found.\n";
		return;
	}
	cout << "Courses enrolled:\n";
	for (const auto& course : courses) {
		cout << " - " << course << endl;
	}
}
string Student::coursesToString() const
{
	string s;
	for (auto c : courses)
		s += c + ";"; // الفصل بين الكورسات بـ ";"
	return s;
}
void Student::stringToCourses(const string& s)
{
	courses.clear();
	stringstream ss(s);
	string course;
	while (getline(ss, course, ';')) {
		if (!course.empty())
			courses.insert(course);
	}
}


