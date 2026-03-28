#pragma once
#include <iostream>
#include <vector>
using namespace std;
#include <string>
#include <map>
#include<set>
class Person {
protected:
	string name;
};
class Student :public Person {
private:
	int id;
	double gpa;
	set<string> courses;
public:
	Student();
	Student(int ide, string n, double gpa);
	int getId()const;
	string getName()const;
	double getGpa()const;
	void EnrollCourse(const string& course);
	void showCourses();
	// ===== Save courses as string (for file) =====
	string coursesToString() const;
	void stringToCourses(const string& s);
};




