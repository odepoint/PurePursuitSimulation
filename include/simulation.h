#ifndef _simulation_h
#define _simulation_h


#include <vector>
#include <iostream>
#include "robot.h"
#include "rateLimiter.h"
std::vector<Point> generatePoints(int points);
double requestCurvature();
Robot computeMovement(double leftV, double rightV, Robot currentPos, double dt);
std::string shouldContinue(std::string response);


#endif