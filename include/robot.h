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

    /// setRobotPosition: setter for robot's position values, initial coordinates and heading
    /// \param coordinates array of two items, [0] = x, [1] = y
    /// \param globalHeading degrees
    void setRobotPosition(const std::pair<double, double> coordinates, double globalHeading)
    {
        this->x = coordinates.first;
        this->y = coordinates.second;

        this->heading = toRadians(globalHeading); // set heading to radian of passed deg heading
    }

    //todo stop casting user input to number types
    void consoleSetRobotPositionDebug() {
        double x, y, degrees;

        std::cout << "Enter Robot Position" << std::endl;

        std::cout << "X: ";
        std::cin >> x;

        std::cout << "Y: ";
        std::cin >> y;

        std::cout << "Global heading (degrees, float): ";
        std::cin >> degrees;

        setRobotPosition({x,y}, degrees);
    }

};

#endif