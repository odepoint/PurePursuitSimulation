#define _USE_MATH_DEFINES
#include <fstream>
#include <algorithm>
#include <filesystem>
#include "../include/pointCreation.h"
#include "../include/lookAhead.h"
#include "../include/simulation.h"
#include "../include/pathUpdate.h"

int main()
{

    std::ofstream txtFile;


    int runs = 0;
    while (true) {

        std::string fileName;

        while(true){
            std::cout << "Enter the name of the file: ";
            std::getline(std::cin, fileName);
            fileName+=".csv";
            if(std::filesystem::exists(fileName)){

                std::cout << "File already exists\n (o)verride or (r)ename: ";
                std::string fileFix;
                std::getline(std::cin, fileFix);
                if(fileFix == "o"){
                    std::filesystem::remove(fileName);
                    break;
                }
                else
                    continue;
            }

            break;

        }

        std::cout << "How many points would you like? ";
        runs++;
        int pointsResponse;
        std::cin >> pointsResponse;

        std::vector<Point> originalPoints = generatePoints(pointsResponse);

        double b = requestCurvature();
        double a = 1 - b;
        double c = 0.001;

        std::vector<Point> unSmoothedPath = addPoints(originalPoints);
        std::vector<Point> finalPoints = smoother(unSmoothedPath, a, b, c);
        updateDistance(finalPoints);
        updateCurvature(finalPoints);
        updateVelocity(finalPoints);

        Robot robotLocation;
        robotLocation.setRobotPosition();

        double simTime = 0;
        double dT = 0.001; //ms

        std::vector<Robot> robotPositions;
        txtFile.open(fileName, std::ofstream::app);
        txtFile << "Time (ms), X (ft), Y (ft), \u03B8, \u00B0" << "\n" << simTime << "," << robotLocation.x << "," << robotLocation.y << "," << robotLocation.heading << "," << (robotLocation.heading * 180)/M_PI;
        txtFile.close();
        bool first = true;
        RateLimiter rateLimiter(50);

        while (true)
        {

            int closest = closestPoint(finalPoints, robotLocation, 0);

            auto lookAheadHelper = LookAhead(closest);
            lookAheadHelper.update(finalPoints, robotLocation);
            double arcCurvature = curvatureOfArc(robotLocation, lookAheadHelper.getIntersectionPoint(), lookAheadHelper.getLookAheadDistance());

            std::pair<double, double> wheelVelocities = targetWheelVelocities(arcCurvature, rateLimiter.limit(finalPoints[closest].targetVelocity, dT));

            std::vector<double> robotXs = { robotLocation.x };
            std::vector<double> robotYs = { robotLocation.y };

            robotLocation = computeMovement(wheelVelocities.first, wheelVelocities.second, robotLocation, dT);
            robotPositions.push_back(robotLocation);

            dT = 15;
            simTime += dT;

            if ((int)simTime % 300 == 0)
            {

                double printedHeading = (robotLocation.heading * 180) / M_PI;

                if (fabs(printedHeading) > 360)
                    printedHeading /= 360;



                std::cout << "Time: " << simTime << std::endl;
                std::cout << "X: " << robotLocation.x << std::endl;
                std::cout << "Y: " << robotLocation.y << std::endl;
                std::cout << "Heading: " << printedHeading << std::endl;

                txtFile.open(fileName, std::ofstream::app);
                txtFile << "\n" << simTime << "," << robotLocation.x << "," << robotLocation.y << "," << robotLocation.heading << "," << printedHeading;
                txtFile.close();




            }
            if(!first) {
                if ((fabs(robotLocation.leftVelocity + robotLocation.rightVelocity) < 1) ||
                    (closest > finalPoints.size() - 5) || simTime > 300000) {


                    std::cout << "Path complete" << std::endl;
                    break;
                }
            }
            first = false;
        }



        bool cont;

        bool waitingOnInput = true;

        std::cin.ignore();

        while (waitingOnInput) {

            std::cout << "Would you like to continue? y/n: ";

            std::string continueResponse;

            getline(std::cin, continueResponse);

            std::string shouldCont = shouldContinue(continueResponse);

            if (shouldCont != "invalid") {

                if (shouldCont == "continue"){
                    cont = true;
                } else {
                    cont = false;
                }


                waitingOnInput = false;


            }


        }


        if (cont)
            continue;
        else {
            return 0;
        }



    }




}
