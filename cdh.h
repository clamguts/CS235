#ifndef CDH_H
#define CDH_H
#include<iostream>
#include<sstream>
#include <string>
#include "csg.h"

class cdh : public csg
{
private: 
	std::string courseName;
	std::string day;
	std::string time;
public:
	cdh() : courseName(""), day(""), time("") {}
	cdh(std::string name, std::string courseDay, std::string courseTime) :
		courseName(name), day(courseDay), time(courseTime) {}
	~cdh() {}

	std::string getCourseName() const
	{
		return courseName;
	}

	std::string getDay() const
	{
		return day;
	}

	std::string getTime() const
	{
		return time;
	}

	void setDay(std::string courseDay)
	{
		day = courseDay;
	}

	friend std::ostream& operator<<(std::ostream& os, const cdh& cd)
	{
		os << cd.toString();
		return os;
	}

	std::string toString() const
	{
		std::stringstream ss;
		ss << courseName << "," << day << "," << time;
		return ss.str();
	}

	std::string cdhToString() const
	{
		std::stringstream ss;
		ss << courseName << " " << day << " " << time << ",";
		return ss.str();
	}
};
#endif 
