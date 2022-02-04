#ifndef CAR_H
#define CAR_H
#include <sstream>
#include <string>
#include <iostream>
#include "Deque.h"
using namespace std;

struct Car
{
    unsigned int carId;
    Car() : carId(0) {}
    Car(unsigned int idNum) : carId(idNum) {}
    ~Car() {}

    bool operator==(const Car car) { return this->carId == car.carId; }
    bool operator!=(const Car car) { return this->carId != car.carId; }

    /** Return the Car as a string */
    string toString() const
    {
        stringstream out;
        out << carId;
        return out.str();
    }

    /** Make insertion operator friend for a Car */
    friend std::ostream& operator<< (ostream& os, const Car& c)
    {
        os << c.toString();
        return os;
    }
};
#endif // !CAR_H
