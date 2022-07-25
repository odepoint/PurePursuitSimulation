#ifndef _pathUpdate_h
#define _pathUpdate_h


#include "robot.h"

void updateDistance(std::vector<Point>& path);
void updateCurvature(std::vector<Point>& path);
void updateVelocity(std::vector<Point>& path, double pathMaxVelocity = 50, double turnSpeed = 50);
int closestPoint(std::vector<Point>& path, Robot robotLocation, int previousClosestIndex);
double curvatureOfArc(Robot robotLocation, Point lookAheadPoint, double lookAheadDistance);
std::pair<double, double> targetWheelVelocities(double curvature, double targetVelocity);

#endif