#ifndef SNAP_H
#define SNAP_H
#include<iostream>
#include<sstream>
#include <string>

class Snap
{
private:
	std::string studentName;
	std::string studentId;
	std::string address;
	std::string phone;

public:
	Snap() : studentName(""), studentId(""), address(""), phone("") {}
	Snap(std::string studentName, std::string studentId, std::string studentAddress, std::string studentPhone) :
		studentName(studentName), studentId(studentId), address(studentAddress), phone(studentPhone) {}
	~Snap() {}

	std::string getName() const
	{
		return studentName;
	}

	std::string getStudentId() const
	{
		return studentId;
	}

	std::string getAddress() const
	{
		return address;
	}

	std::string getPhone() const
	{
		return phone;
	}

	friend std::ostream& operator<<(std::ostream& os, const Snap& sn)
	{
		os << sn.toString();
		return os;
	}

	std::string toString() const
	{
		std::stringstream ss;
		ss << studentId << "," << studentName << "," << address << "," << phone;
		return ss.str();
	}

	std::string scheduleToString() const
	{
		std::stringstream ss;
		ss << studentName << ", " << studentId << ", " << address << ", " << phone;
		return ss.str();
	}

};

#endif 

