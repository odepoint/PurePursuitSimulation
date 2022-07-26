#ifndef _point_h
#define _point_h


struct Point
{

    double x;
    double y;
    double distance;
    double curvature;
    double maxVelocity;
    double targetVelocity;

    Point(double inputX = 0, double inputY = 0)
    {
        x = inputX;
        y = inputY;
    }

    void copyPoint(double inputX, double inputY, double inputDistance, double inputCurvature, double inputMaxVelocity, double inputTargetVelocity)
    {

        x = inputX;
        y = inputY;
        distance = inputDistance;
        curvature = inputCurvature;
        maxVelocity = inputMaxVelocity;
        targetVelocity = inputTargetVelocity;
    }

    
    Point pointDiff(Point endPoint) const
    {

        double diffX = endPoint.x - x;
        double diffY = endPoint.y - y;

        Point pointDiff(diffX, diffY);
        return pointDiff;
    }

};


#endif