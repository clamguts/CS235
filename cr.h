#ifndef CR_H
#define CR_H
#include<iostream>
#include<sstream>
#include <string>
#include "cdh.h"

class cr : public cdh 
{
private:
	std::string name;
	std::string room;
public:
	cr() : name(""), room("") {}
	cr(std::string courseName, std::string courseRoom) :
		name(courseName), room(courseRoom) {}
	~cr() {}

	std::string getRoom() const
	{
		return room;
	}

	friend std::ostream& operator<<(std::ostream& os, const cr& cr)
	{
		os << cr.toString();
		return os;
	}

	std::string toString() const
	{
		std::stringstream ss;
		ss << "cr(" << name << "," << room << ")";
		return ss.str();
	}
};

#endif 