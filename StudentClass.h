#ifndef STUDENT_CLASS_H
#define STUDENT_CLASS_H
#include "cr.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class StudentClass: public cr
{
private:
	std::string classes;
	std::string students;
public:
	StudentClass(): classes(""), students("") {}
	StudentClass(std::string studentClasses, std::string student) : classes(studentClasses), students(student) {}
	~StudentClass() {}

	std::string getClass() const
	{
		return classes;
	}

	std::string getClassStudentName() const
	{
		return students;
	}

	friend std::ostream& operator<<(std::ostream& os, const StudentClass& student)
	{
		os << student.toString();
		return os;
	}

	std::string toString() const
	{
		std::stringstream ss;
		ss << classes << students;
		return ss.str();
	}

};
#endif
