#include <fstream>
#include <algorithm>
#include <filesystem>
#include "../include/pointCreation.h"
#include "../include/lookAhead.h"
#include "../include/simulation.h"
#include "../include/pathUpdate.h"

int main() {

    std::ofstream txtFile;

    while (true) {

        std::string fileName; //TODO unusual dealloc potential pain point ?? investigate

        while (true) {
            std::cout << "Enter the name of the file: ";
            std::getline(std::cin, fileName);
            fileName += ".csv";
            if (std::filesystem::exists(fileName)) {

                std::cout << "File already exists\n (o)verride or (r)ename: ";
                std::string fileFix; // TODO all of these input yoinks are sus
                std::getline(std::cin, fileFix);
                if (fileFix == "o") {
                    std::filesystem::remove(fileName);
                    break;
                } else
                    continue;
            }

            break;

        }

        std::cout << "How many points would you like? ";
        int pointsResponse; // TODO this sucks and will break program but i dont care enough to fix it right now
        std::cin >> pointsResponse;

        std::vector<Point> originalPoints;
        originalPoints = generatePoints(pointsResponse);

        double b = requestCurvature();
        double a = 1 - b;
        double c = 0.001;

        std::vector<Point> unSmoothedPath = addPoints(originalPoints);
        std::vector<Point> finalPoints = smoother(unSmoothedPath, a, b, c);
        updateDistance(finalPoints);
        updateCurvature(finalPoints);
        updateVelocity(finalPoints);

        Robot robotLocation;
        robotLocation.consoleSetRobotPositionDebug(); // TODO this sucks and will break program but i dont care enough to fix it right now

        int simTime = 0;
        int dT = 15; //ms

        std::vector<Robot> robotPositions;
        txtFile.open(fileName, std::ofstream::app);
        txtFile << "Time (ms), X (ft), Y (ft), \u03B8, \u00B0" << "\n" << simTime << "," << robotLocation.x << ","
                << robotLocation.y << "," << robotLocation.heading << "," << (robotLocation.heading * 180) / M_PI;
        txtFile.close();

        while (true) {
            int closest = closestPoint(finalPoints, robotLocation, 0);

            auto lookAheadHelper = LookAhead(closest);
            lookAheadHelper.update(finalPoints, robotLocation);
            double arcCurvature = curvatureOfArc(robotLocation, lookAheadHelper.getIntersectionPoint(),
                                                 lookAheadHelper.getLookAheadDistance());
            auto wheelVelocities = targetWheelVelocities(arcCurvature, finalPoints[closest].targetVelocity);

            robotLocation = computeMovement(wheelVelocities.first, wheelVelocities.second, robotLocation, dT);
            robotPositions.push_back(robotLocation);

            simTime += dT;

            if (simTime % 300 == 0) { //todo get this all out of main

                double printedHeading = (robotLocation.heading * 180) / M_PI;

                if (fabs(printedHeading) > 360)
                    printedHeading /= 360;


                std::cout << "Time: " << simTime << std::endl;
                std::cout << "X: " << robotLocation.x << std::endl;
                std::cout << "Y: " << robotLocation.y << std::endl;
                std::cout << "Heading: " << printedHeading << std::endl;

                txtFile.open(fileName, std::ofstream::app);
                txtFile << "\n" << simTime << "," << robotLocation.x << "," << robotLocation.y << ","
                        << robotLocation.heading << "," << printedHeading;
                txtFile.close();


            }

            if ((fabs(robotLocation.leftVelocity) < 0.1 && fabs(robotLocation.rightVelocity) < 0.1) ||
                ((closest > finalPoints.size() - 5) && simTime >= 30000)) {
                std::cout << "Path complete" << std::endl;
                break;
            }
        }
        // todo make rest of main look like below code
        if (getContinueResponse()) { // grab user input and repeat execution if desired
            continue;
        }
        break; // break if repeat is not desired and terminate execution

    }

}