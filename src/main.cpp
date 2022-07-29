#include <fstream>
#include <algorithm>
#include <filesystem>
#include "../include/pointCreation.h"
#include "../include/lookAhead.h"
#include "../include/simulation.h"
#include "../include/pathUpdate.h"

using namespace std;

///
/// \param outputFile
/// \param outputFileName
/// \param simTime
/// \param robotLocation
void writePositionData(ofstream outputFile, string outputFileName, int simTime, Robot robotLocation)
{
    outputFile.open(outputFileName, ofstream::app);
    outputFile << "Time (ms), X (ft), Y (ft), \u03B8, \u00B0" << "\n" << simTime << "," << robotLocation.x << ","
            << robotLocation.y << "," << robotLocation.heading << "," << (robotLocation.heading * 180) / M_PI;
    outputFile.close();
}
//todo dump into struct
/// log program data
/// \param simTime
/// \param robotLocation
/// \param printedHeading
void consoleLogPositionData(int simTime, Robot robotLocation, double printedHeading){
    cout << "Time: " << simTime << endl;
    cout << "X: " << robotLocation.x << endl;
    cout << "Y: " << robotLocation.y << endl;
    cout << "Heading: " << printedHeading << endl;
}

void checkOutputFileExists(bool doIncrement = false) {
    if (filesystem::exists(outputFilename)) {
        cout << "Previous output is present\n (o)verwrite (s)ave additional file";
        string fileFix; // TODO all of these input yoinks are sus
        getline(cin, fileFix);
        if (fileFix == "o") {
            filesystem::remove(outputFilename);
            break;
        }
        if (fileFix == "s") {
            checkOutputFileExists( doIncrement = true);
        }
    }
}

int main() {

    ofstream outputFile;

    const string outputFilename = "output";

        checkOutputFileExists();

        cout << "How many points would you like? ";
        int pointsResponse; // TODO this sucks and will break program but i dont care enough to fix it right now
        cin >> pointsResponse;

        vector<Point> originalPoints;
        originalPoints = generatePoints(pointsResponse);

        double b = requestCurvature();
        double a = 1 - b;
        double c = 0.001;

        vector<Point> unSmoothedPath = addPoints(originalPoints);
        vector<Point> finalPoints = smoother(unSmoothedPath, a, b, c);
        updateDistance(finalPoints);
        updateCurvature(finalPoints);
        updateVelocity(finalPoints);

        Robot robotLocation;
        robotLocation.consoleSetRobotPositionDebug(); // TODO this sucks and will break program but i dont care enough to fix it right now

        int simTime = 0;
        int dT = 15; //ms

        writePositionData(fileName);

        vector<Robot> robotPositions;

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

                consoleLogPositionData(simTime, robotLocation, printedHeading);

                outputFile.open(fileName, ofstream::app);
                outputFile << "\n" << simTime << "," << robotLocation.x << "," << robotLocation.y << ","
                        << robotLocation.heading << "," << printedHeading;
                outputFile.close();


            }

            if ((fabs(robotLocation.leftVelocity) < 0.1 && fabs(robotLocation.rightVelocity) < 0.1) ||
                ((closest > finalPoints.size() - 5) && simTime >= 30000)) {
                cout << "Path complete" << endl;
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