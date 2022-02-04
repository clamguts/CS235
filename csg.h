#ifndef CSG_H
#define CSG_H
#include "snap.h"
#include<iostream>
#include<sstream>
#include <string>

class csg : public Snap
{
private:
	std::string course;
	std::string id;
	std::string grade;
public:
	csg() : course(""), id(""), grade("") {}
	csg(std::string courseName, std::string studentId, std::string studentGrade) :
		course(courseName), id(studentId), grade(studentGrade) {}
	~csg() {}

	std::string getCourse() const
	{
		return course;
	}

	std::string getGrade() const
	{
		return grade;
	}

	std::string getId() const
	{
		return id;
	}

	void setCourse(std::string currCourse)
	{
		course = currCourse;
	}

	void setId(std::string currId)
	{
		id = currId;
	}

	friend std::ostream& operator<<(std::ostream& os, const csg& cs)
	{
		os << cs.toString();
		return os;
	}

	std::string toString() const
	{
		std::stringstream ss;
		ss << "csg(" << course << "," << id << "," << grade << ")";
		return ss.str();
	}
};

#endif 
