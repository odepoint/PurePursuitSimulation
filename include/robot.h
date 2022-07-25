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