#include "../include/pathUpdate.h"

void updateDistance(std::vector<Point>& path)

{

    path[0].distance = 0;

    for (int i = 1; i < path.size(); i++)
    {
        path[i].distance = path[i - 1].distance + distance_formula(path[i], path[i - 1]);
    }
}

void updateCurvature(std::vector<Point>& path)
{

    path.front().curvature = 0;
    path.back().curvature = 0;

    for (int i = 1; i < path.size() - 1; i++)
    {
        double x1 = path[i].x;
        double x2 = path[i - 1].x;
        double x3 = path[i + 1].x;

        if (x1 == x2)
            x1 += 0.001;

        double x1Squared = pow(x1, 2);
        double x2Squared = pow(x2, 2);
        double x3Squared = pow(x3, 3);

        double y1 = path[i].y;
        double y2 = path[i - 1].y;
        double y3 = path[i + 1].y;

        double y1Squared = pow(y1, 2);
        double y2Squared = pow(y2, 2);
        double y3Squared = pow(y3, 2);

        double k1 = 0.5 * (x1Squared + y1Squared - x2Squared - y2Squared) / (x1 - x2);
        double k2 = (y1 - y2) / (x1 - x2);
        double b = 0.5 * (x2Squared - 2 * x2 * k1 + y2Squared - x3Squared + 2 * x3 * k1 - y3Squared) / (x3 * k2 - y3 + y2 - x2 * k2);

        double a = k1 - k2 * b;

        double r = sqrt((pow(x1 - a, 2)) + (pow(y1 - b, 2)));

        path[i].curvature = 1 / r;
    }
}

void updateVelocity(std::vector<Point>& path, double pathMaxVelocity, double turnSpeed)
{
    //inches per second squared
    double maxAcceleration = pathMaxVelocity * 2;

    for (int i = 0; i < path.size(); i++)
    {
        if (path[i].curvature == 0)
            path[i].maxVelocity = pathMaxVelocity;
        else
            path[i].maxVelocity = std::min(pathMaxVelocity, turnSpeed / path[i].curvature);
    }

    path.back().targetVelocity = 0;

    for (int i = path.size() - 2; i >= 0; i--)
    {

        double distance = path[i + 1].distance - path[i].distance;
        double underSqrt = sqrt(pow(path[i + 1].targetVelocity, 2) + 2 * maxAcceleration * distance);

        path[i].targetVelocity = std::min(path[i].maxVelocity, underSqrt);
    }
}

int closestPoint(std::vector<Point>& path, Robot robotLocation, int previousClosestIndex)
{

    double smallestValue = 9999999999;
    Point robotPoint(robotLocation.x, robotLocation.y);
    int indexClosest = path.size() - 1;

    for (int i = previousClosestIndex; i < path.size(); i++)
    {

        double distanceBotPoint = distance_formula(path[i], robotPoint);
        if (distanceBotPoint < smallestValue)
        {
            smallestValue = distanceBotPoint;
            indexClosest = i;
        }
    }

    return indexClosest;
}





double curvatureOfArc(Robot robotLocation, Point lookAheadPoint, double lookAheadDistance)
{
    double a = -tan(robotLocation.heading);
    double b = 1;
    double c = tan(robotLocation.heading) * robotLocation.x - robotLocation.y;

    double x = fabs(a * lookAheadPoint.x + b * lookAheadPoint.y + c) / sqrt(a * a + b * b);

    double side = sin(robotLocation.heading) * (lookAheadPoint.x - robotLocation.x) - cos(robotLocation.heading) * (lookAheadPoint.y - robotLocation.y);

    if (side > 0)
        side = 1;
    else if (side < 0)
        side = -1;
    else
        side = 0;

    double curvature = 2 * x / (lookAheadDistance * lookAheadDistance);

    return curvature * side;
}

double wheelVelocity(double curvature, double targetVelocity, double trackWidth) {
    return targetVelocity * (2 + curvature * trackWidth / 2);
}

std::pair<double, double> targetWheelVelocities(double curvature, double targetVelocity)
{
    double trackWidth = 16; //tune, few inches larger than the real one

    return {wheelVelocity(curvature, targetVelocity, trackWidth), \
    wheelVelocity(curvature, targetVelocity, trackWidth)};
}

