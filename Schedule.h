#ifndef SCHOOL_SCHEDULE_H
#define SCHOOL_SCHEDULE_H
#include<iostream>
#include<sstream>
#include <vector>
#include <string>
#include "StudentClass.h"

class SchoolSchedule: public StudentClass
{
private:
	std::vector<Snap> studentSchedule;
	std::vector<cdh> scheduleInfo;
	std::vector<cr> scheduleRoom;
	std::vector<csg> scheduleCourse;
    std::vector<StudentClass> studentClasses;
public:
	SchoolSchedule() {}
	SchoolSchedule(std::vector<Snap> schedule, std::vector<cdh> info, std::vector<cr> room, std::vector<csg> course, std::vector<StudentClass> classes) :
		studentSchedule(schedule), scheduleInfo(info), scheduleRoom(room), scheduleCourse(course), studentClasses(classes) {}
	~SchoolSchedule() {}


	friend std::ostream& operator<<(std::ostream& os, const SchoolSchedule& schedule)
	{
		os << schedule.toString();
		return os;
	}

	std::string toString() const
	{
		std::stringstream ss;
		std::string currStudent = studentSchedule.at(0).getName();
		for (unsigned int i = 0; i < studentSchedule.size(); ++i)
		{
			if (currStudent != studentSchedule.at(i).getName())
			{
				ss << std::endl;
			}
			ss << studentSchedule.at(i).scheduleToString() << std::endl;
			for (unsigned int j = 0; j < scheduleInfo.size(); ++j)
			{
				for (unsigned int k = 0; k < studentClasses.size(); ++k)
				if (scheduleInfo.at(j).getCourseName() == studentClasses.at(k).getClass()
				&& studentClasses.at(k).getClassStudentName() == studentSchedule.at(i).getName())
				{
					ss << "  " << scheduleInfo.at(j).cdhToString() << " " << scheduleRoom.at(j).getRoom() << std::endl;
				}
			}
			currStudent = studentSchedule.at(i).getName();
		}
		return ss.str();
	}
};
#endif 
