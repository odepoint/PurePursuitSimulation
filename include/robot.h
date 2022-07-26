#ifndef _robot_h
#define _robot_h
#include "point.h"
#include <iostream>
#include <string>
#include "mathLib.h"

struct Robot : Point
{

    double leftVelocity;
    double rightVelocity;
    double heading;

    Robot()= default;

    Robot(double inputX, double inputY, double inputHeading = 0, double inputLeftVelocity = 0, double inputRightVelocity = 0) : Point(inputX, inputY)
    {
        leftVelocity = inputLeftVelocity;
        rightVelocity = inputRightVelocity;
        heading = inputHeading;
    }
/*
    /// setRobotPosition: setter for robot's position values
    /// \param coordinates array of two items, [0] = x, [1] = y
    /// \param globalHeading degrees
    void setRobotPosition(const double coordinates[2], double globalHeading)
    {
        this->x = coordinates[0]; this->y = coordinates[1];

        this->heading = toRadians(globalHeading); // set heading to radian of passed deg heading
    }

}; */

    void setRobotPosition()
    {
        std::cout << "Enter Robot Information" << std::endl;
        std::cout << "X: ";
        double x;
        std::cin >> x;
        this->x = x;
        std::cout << "Y: ";
        double y;
        std::cin >> y;
        this->y = y;
        std::cout << "Global heading (in degrees): ";
        std::cin >> heading;
        heading *= M_PI / 180;
        this->heading = heading;
    
    }
};

#endif