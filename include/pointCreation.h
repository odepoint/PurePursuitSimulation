#ifndef _pointCreation_h
#define _pointCreation_h
#include <iostream>
#include "mathLib.h"



std::vector<Point> smoother(std::vector<Point> path, double weight_data, double weight_smooth, double tolerance);
std::vector<Point> addPoints(std::vector<Point> originalPoints);





#endif